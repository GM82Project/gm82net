/*
 * Copyright 2010-2013 Maarten Baert
 * maarten-baert@hotmail.com
 * http://www.maartenbaert.be/
 * 
 * This file is part of Http Dll 2.
 * 
 * Http Dll 2 is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * Http Dll 2 is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU Lesser General Public License for more details.
 * 
 * You should have received a copy of the GNU Lesser General Public License
 * along with Http Dll 2. If not, see <http://www.gnu.org/licenses/>.
 */

// visual studio stuff
#define NOMINMAX

#include "Socket.h"

#include "StringConversion.h"

#include <cassert>
#include <new>

#define SOCKET_MAKENONBLOCKING(s) {\
	unsigned long temp = 1;\
	ioctlsocket((s), FIONBIO, &temp);\
}
#define SOCKET_NODELAY(s) {\
    DWORD temp = 1;\
    setsockopt(s, IPPROTO_TCP, TCP_NODELAY, (char*)(&temp), sizeof(temp));\
}\

std::string SockAddrToString(sockaddr* addr) {
	
	char buffer[40];
	char *ptr = buffer + sizeof(buffer);
	
	if(addr->sa_family == AF_INET) {
		
		// IPv4
		unsigned int i;
		for(unsigned int j = 4; j > 0; ) {
			i = ((uint8_t*)(&((sockaddr_in*)(addr))->sin_addr))[--j];
			do { *(--ptr) = '0' + i % 10; } while((i /= 10) != 0);
			if(j != 0) *(--ptr) = '.';
		}
		
	} else if(addr->sa_family == AF_INET6) {
		
		// IPv6
		const char *hextable = "0123456789abcdef";
		// find leftmost longest span of zeroes longer than 1
		int span_start = -1; // inclusive
		int span_end = -1; // exclusive
		{
			int current_span_start = -1;
			for (unsigned int j = 0; j <= 8; j++) {
				// artificially put a 1 after the ip to simplify logic
				unsigned int i;
				if (j != 8)
					i = ((uint16_t*)(&((sockaddr_in6*)(addr))->sin6_addr))[j];
				else
					i = 1;
				if (current_span_start == -1 && i == 0) {
					current_span_start = j;
				} else if (i != 0 && current_span_start != -1) {
					int span_len = j - current_span_start;
					if (span_len > 1 && span_len > span_end - span_start) {
						span_start = current_span_start;
						span_end = j;
					}
					current_span_start = -1;
				}
			}
		}
		// actual encoding
		for(int j = 8; j > 0; ) {
			unsigned int i = ((uint16_t*)(&((sockaddr_in6*)(addr))->sin6_addr))[--j];
			// manually put : if at start of span or if at end and span goes to end
			if (j == span_start || (j+1 == span_end && span_end == 8)) *(--ptr) = ':';
			else if (j < span_start || j >= span_end) {
				i = (i >> 8) | ((i & 255) << 8);
				do { *(--ptr) = hextable[i & 15]; } while ((i >>= 4) != 0);
				if (j != 0) *(--ptr) = ':';
			}
		}
	}
	
	return std::string(ptr, buffer + sizeof(buffer) - ptr);
	
}

unsigned int SockAddrGetPort(sockaddr* addr) {
	
	unsigned int port = 0;
	if(addr->sa_family == AF_INET) {
		// IPv4
		port = ((sockaddr_in*)(addr))->sin_port;
	} else if(addr->sa_family == AF_INET6) {
		// IPv6
		port = ((sockaddr_in6*)(addr))->sin6_port;
	}
	
	// reverse byte order
	return ((port & 0xff) << 8) | (port >> 8);
	
}

// global

bool InitSockets() {
	static WSADATA wsadata;
	if(WSAStartup(MAKEWORD(2, 0), &wsadata) != 0) {
		return false;
	}
	if(LOBYTE(wsadata.wVersion) != 2 || HIBYTE(wsadata.wVersion) != 0) {
		WSACleanup();
		return false;
	}
	return true;
}
void CleanupSockets() {
	WSACleanup();
}

// ListeningSocket

ListeningSocket::ListeningSocket() {
	listening = false;
}

ListeningSocket::~ListeningSocket() {
	StopListening();
}

void ListeningSocket::StartListening(bool ipv6, unsigned int port, bool local) {
	
	// stop listening
	StopListening();
	
	// initialize addrinfo hints
	addrinfo hints;
	memset(&hints, 0, sizeof(hints));
	hints.ai_family = (ipv6)? AF_INET6 : AF_INET;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_protocol = IPPROTO_TCP;
	if(!local)
		hints.ai_flags = AI_PASSIVE;
	
	// get addrinfo
	addrinfo *first_addrinfo = NULL;
	std::string portstring = UIntToString(port);
	int result = getaddrinfo((local)? "localhost" : NULL, portstring.c_str(), &hints, &first_addrinfo);
	if(result != 0 || first_addrinfo == NULL) {
		return;
	}
	
	// create a socket
	s = socket(first_addrinfo->ai_family, first_addrinfo->ai_socktype, first_addrinfo->ai_protocol);
	if(s == INVALID_SOCKET) {
		freeaddrinfo(first_addrinfo);
		return;
	}
	
	// bind the socket
	result = bind(s, first_addrinfo->ai_addr, first_addrinfo->ai_addrlen);
	freeaddrinfo(first_addrinfo);
	if(result == SOCKET_ERROR) {
		closesocket(s);
		return;
	}
	
	// start listening
	result = listen(s, SOMAXCONN);
	if(result == SOCKET_ERROR) {
		closesocket(s);
		s = INVALID_SOCKET;
		return;
	}
	
	// make the socket nonblocking
	SOCKET_MAKENONBLOCKING(s);
	listening = true;
	
}

void ListeningSocket::StopListening() {
	if(listening) {
		closesocket(s);
		listening = false;
	}
}

bool ListeningSocket::CanAccept() {
	
	if(!listening) {
		return false;
	}
	
	fd_set read;
	FD_ZERO(&read);
	FD_SET(s, &read);
	
	timeval t = {0, 0};
	int result = select(0, &read, NULL, NULL, &t);
	if(result == SOCKET_ERROR) {
		closesocket(s);
		listening = false;
		return false;
	}
	
	return (FD_ISSET(s, &read))? true : false;
	
}

void ListeningSocket::Accept(Socket* socket) {
	
	socket->Reset();
	
	if(!listening) {
		socket->state = Socket::state_error;
	}
	
	SOCKET s2 = accept(s, NULL, NULL);
	if(s2 == INVALID_SOCKET) {
		socket->state = Socket::state_error;
	} else {
		SOCKET_MAKENONBLOCKING(s2);
		SOCKET_NODELAY(s2);
		socket->s = s2;
		socket->state = Socket::state_connected;
	}
	
}

// Socket

Socket::Socket() {
	state = state_notconnected;
	should_shut_down = false;
}

Socket::~Socket() {
	Reset();
}

void Socket::Reset() {
	
	if(state == state_connecting || state == state_connected || state == state_closed) {
		closesocket(s);
	}
	if(state == state_connecting) {
		freeaddrinfo(first_addrinfo);
	}
	readbuffer.Clear();
	writebuffer.Clear();
	
	state = state_notconnected;
	should_shut_down = false;
	
}

void Socket::Connect(const std::string& address, unsigned int port) {
	
	// reset the socket (only if already connected, otherwise the buffers would be cleared)
	if(state != state_notconnected) {
		Reset();
	}
	
	// initialize addrinfo hints
	addrinfo hints;
	memset(&hints, 0, sizeof(hints));
	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_protocol = IPPROTO_TCP;
	
	// get addrinfo list
	std::string portstring = UIntToString(port);
	int result = getaddrinfo(address.c_str(), portstring.c_str(), &hints, &first_addrinfo);
	if(result != 0 || first_addrinfo == NULL) {
		state = state_error;
		return;
	}
	
	// try to connect
	// connect fails because this is a nonblocking socket, this is normal
	for(current_addrinfo = first_addrinfo; current_addrinfo != NULL; current_addrinfo = current_addrinfo->ai_next) {
		s = socket(current_addrinfo->ai_family, current_addrinfo->ai_socktype, current_addrinfo->ai_protocol);
		if(s == INVALID_SOCKET) {
			continue;
		}
		SOCKET_MAKENONBLOCKING(s);
		SOCKET_NODELAY(s);
		connect(s, current_addrinfo->ai_addr, current_addrinfo->ai_addrlen);
		state = state_connecting;
		return;
	}
	
	// connecting failed
	freeaddrinfo(first_addrinfo);
	state = state_error;
	
}

void Socket::UpdateRead() {
	
	// connecting
	if(state == state_connecting) {
		
		fd_set write, except;
		FD_ZERO(&write);
		FD_SET(s, &write);
		FD_ZERO(&except);
		FD_SET(s, &except);
		
		// call select()
		timeval t = {0, 0};
		int result = select(0, NULL, &write, &except, &t);
		if(result == SOCKET_ERROR) {
			freeaddrinfo(first_addrinfo);
			state = state_error;
			return;
		}
		
		// error?
		if(FD_ISSET(s, &except)) {
			
			// connection attempt has failed, try the next address
			closesocket(s);
			for(current_addrinfo = current_addrinfo->ai_next; current_addrinfo != NULL; current_addrinfo = current_addrinfo->ai_next) {
				s = socket(current_addrinfo->ai_family, current_addrinfo->ai_socktype, current_addrinfo->ai_protocol);
				if(s == INVALID_SOCKET) {
					continue;
				}
				SOCKET_MAKENONBLOCKING(s);
				SOCKET_NODELAY(s);
				connect(s, current_addrinfo->ai_addr, current_addrinfo->ai_addrlen);
				return;
			}
			
			// connecting failed
			freeaddrinfo(first_addrinfo);
			state = state_error;
			return;
			
		}
		
		// success?
		if(FD_ISSET(s, &write)) {
			
			// connection attempt has succeeded
			freeaddrinfo(first_addrinfo);
			state = state_connected;
			
		}
		
	}
	
	// reading
	if(state == state_connected) {
		for( ; ; ) {
			
			// try to receive data
			char buffer[10240];
			int result = recv(s, buffer, sizeof(buffer), 0);
			if(result == SOCKET_ERROR) {
				if(WSAGetLastError() == WSAEWOULDBLOCK) {
					// nothing to read
					return;
				}
				closesocket(s);
				state = state_error;
				return;
			}
			
			// was the connection closed?
			if(result == 0) {
				// Note: Versions of this DLL before 2.3.4 would close the connection automatically when the other side was shut down.
				// This version doesn't do this because this allows the user to write data in state_closed (this is important for HTTP servers).
				//closesocket(s);
				state = state_closed;
				return;
			}
			
			// copy the data
			readbuffer.WriteData(buffer, result);
			if((unsigned int)(result) < sizeof(buffer)) {
				break;
			}
			
		}
	}
	
}

void Socket::UpdateWrite() {
	
	// writing
	if((state == state_connected || state == state_closed) && !writebuffer.IsAtEnd()) {
		
		// try to send data
		int result = send(s, writebuffer.GetData() + writebuffer.GetPos(), writebuffer.GetLength() - writebuffer.GetPos(), 0);
		if(result == SOCKET_ERROR) {
			if(WSAGetLastError() == WSAEWOULDBLOCK) {
				// can't write anything
				return;
			}
			closesocket(s);
			state = state_error;
			return;
		}
		
		// change the position and resize the buffer
		writebuffer.SetPos(writebuffer.GetPos() + result);
		unsigned int p = writebuffer.GetPos();
		if(p > writebuffer.GetLength() / 4) {
			memmove(writebuffer.GetData(), writebuffer.GetData() + p, writebuffer.GetLength() - p);
			writebuffer.SetPos(0);
			writebuffer.SetLength(writebuffer.GetLength() - p);
		}
		
		// shut down?
		if(should_shut_down && writebuffer.IsAtEnd()) {
			shutdown(s, SD_SEND);
		}
		
	}
	
}

void Socket::ShutDown() {
	should_shut_down = true;
}

std::string Socket::GetPeerAddress() {
	
	if(state != state_connected && state != state_closed) {
		return "";
	}
	
	sockaddr_in6 addr;
	int size = sizeof(addr);
	if(getpeername(s, (sockaddr*)(&addr), &size) == SOCKET_ERROR) {
		return "";
	}
	
	return SockAddrToString((sockaddr*)(&addr));
	
}

const char* Socket::GetReadData() {
	return readbuffer.GetData() + readbuffer.GetPos();
}

unsigned int Socket::GetReadDataLength() {
	return readbuffer.GetLength() - readbuffer.GetPos();
}

void Socket::EraseReadData(unsigned int length) {
	readbuffer.SetPos(readbuffer.GetPos() + length);
	unsigned int p = readbuffer.GetPos();
	if(p > readbuffer.GetLength() / 4) {
		memmove(readbuffer.GetData(), readbuffer.GetData() + p, readbuffer.GetLength() - p);
		readbuffer.SetPos(0);
		readbuffer.SetLength(readbuffer.GetLength() - p);
	}
}

void Socket::Write(const char* data, unsigned int length) {
	if(should_shut_down || state == state_error)
		return;
	writebuffer.WriteData(data, length);
}

unsigned int Socket::GetWriteDataLength() {
	return writebuffer.GetLength() - writebuffer.GetPos();
}

bool Socket::ReadMessage(Buffer *b) {
	readbuffer.ClearError();
	unsigned int p1 = readbuffer.GetPos();
	unsigned int len = readbuffer.ReadUIntV();
	unsigned int p2 = readbuffer.GetPos();
	readbuffer.SetPos(p1);
	if(!readbuffer.GetError() && len <= readbuffer.GetLength() - p2) {
		b->Clear();
		b->SetLength(len);
		memcpy(b->GetData(), readbuffer.GetData() + p2, len);
		EraseReadData(p2 - p1 + len);
		return true;
	} else {
		return false;
	}
}

void Socket::WriteMessage(Buffer *b) {
	if(should_shut_down || state == state_error)
		return;
	writebuffer.WriteUIntV(b->GetLength());
	writebuffer.WriteBuffer(b);
}

bool Socket::ReadMessageDelimiter(Buffer *b, char delimiter) {
	unsigned int p1 = readbuffer.GetPos();
	const char *data = readbuffer.GetData();
	for(unsigned int i = p1; i < readbuffer.GetLength(); ++i) {
		if(data[i] == delimiter) {
			b->Clear();
			b->SetLength(i - p1);
			memcpy(b->GetData(), data + p1, i - p1);
			EraseReadData(i - p1 + 1);
			return true;
		}
	}
	return false;
}

void Socket::WriteMessageDelimiter(Buffer *b, char delimiter) {
	if(should_shut_down || state == state_error)
		return;
	writebuffer.WriteBuffer(b);
	writebuffer.WriteType<char>(delimiter);
}

// UDP socket

UDPSocket::UDPSocket() {
	state = state_notstarted;
	maxmessagesize = 0;
	memset(&destination_sockaddr, 0, sizeof(destination_sockaddr));
	memset(&last_sockaddr, 0, sizeof(last_sockaddr));
}

UDPSocket::~UDPSocket() {
	Reset();
}

void UDPSocket::Reset() {
	
	if(state == state_started) {
		closesocket(s);
	}
	
	maxmessagesize = 0;
	memset(&last_sockaddr, 0, sizeof(last_sockaddr));
	
	state = state_notstarted;
	
}

void UDPSocket::Start(bool ipv6, unsigned int port) {
	
	// reset
	if(state != state_notstarted) {
		Reset();
	}
	
	// initialize addrinfo hints
	addrinfo hints;
	memset(&hints, 0, sizeof(hints));
	hints.ai_family = (ipv6)? AF_INET6 : AF_INET;
	hints.ai_socktype = SOCK_DGRAM;
	hints.ai_protocol = IPPROTO_UDP;
	hints.ai_flags = AI_PASSIVE;
	
	state = state_error;
	
	if(port == 0) {
		
		// create a socket
		s = socket(hints.ai_family, hints.ai_socktype, hints.ai_protocol);
		if(s == INVALID_SOCKET) {
			return;
		}
		
	} else {
		
		// get addrinfo
		addrinfo *first_addrinfo = NULL;
		std::string portstring = UIntToString(port);
		int result = getaddrinfo(NULL, portstring.c_str(), &hints, &first_addrinfo);
		if(result != 0 || first_addrinfo == NULL) {
			return;
		}
		
		// create a socket
		s = socket(first_addrinfo->ai_family, first_addrinfo->ai_socktype, first_addrinfo->ai_protocol);
		if(s == INVALID_SOCKET) {
			freeaddrinfo(first_addrinfo);
			return;
		}
		
		// bind the socket
		result = bind(s, first_addrinfo->ai_addr, first_addrinfo->ai_addrlen);
		freeaddrinfo(first_addrinfo);
		if(result == SOCKET_ERROR) {
			closesocket(s);
			return;
		}
		
	}
	
	// get maximum message size
	{
		int size = sizeof(maxmessagesize);
		getsockopt(s, SOL_SOCKET, SO_MAX_MSG_SIZE, (char*)(&maxmessagesize), &size);
	}
	
	// save ipv6
	this->ipv6 = ipv6;
	
	// make the socket nonblocking
	SOCKET_MAKENONBLOCKING(s);
	state = state_started;
	
}

void UDPSocket::SetDestination(std::string address, unsigned int port) {
	
	// initialize addrinfo hints
	addrinfo hints;
	memset(&hints, 0, sizeof(hints));
	hints.ai_family = (ipv6)? AF_INET6 : AF_INET;
	hints.ai_socktype = SOCK_DGRAM;
	hints.ai_protocol = IPPROTO_UDP;
	
	// get addrinfo list
	addrinfo *first_addrinfo = NULL;
	std::string portstring = UIntToString(port);
	int result = getaddrinfo(address.c_str(), portstring.c_str(), &hints, &first_addrinfo);
	if(result != 0 || first_addrinfo == NULL) {
		closesocket(s);
		state = state_error;
		return;
	}
	
	// copy
	memcpy(&destination_sockaddr, first_addrinfo->ai_addr, std::min(sizeof(destination_sockaddr), first_addrinfo->ai_addrlen));
	freeaddrinfo(first_addrinfo);
	
}

bool UDPSocket::Receive(Buffer *b) {
	
	if(state != state_started) {
		return false;
	}
	
	b->Clear();
	b->SetLength(maxmessagesize);
	
	int size = sizeof(last_sockaddr);
	int result = recvfrom(s, b->GetData(), b->GetLength(), 0, (sockaddr*)(&last_sockaddr), &size);
	if(result == SOCKET_ERROR) {
		if(WSAGetLastError() == WSAEWOULDBLOCK) {
			// nothing to receive
			b->Clear();
			return false;
		}
		closesocket(s);
		state = state_error;
		return false;
	}
	
	b->SetLength(result);
	return true;
	
}

void UDPSocket::Send(Buffer *b) {
	
	if(state != state_started) {
		return;
	}
	
	int result = sendto(s, b->GetData(), b->GetLength(), 0, (sockaddr*)(&destination_sockaddr), sizeof(destination_sockaddr));
	if(result == SOCKET_ERROR && WSAGetLastError() != WSAEWOULDBLOCK) {
		closesocket(s);
		state = state_error;
	}
	
}

unsigned int UDPSocket::GetTTL() {
	unsigned int ttl;
	int len = sizeof(ttl);
	getsockopt(s, IPPROTO_IP, IP_TTL, (char*)(&ttl), &len);
	return ttl;
}

void UDPSocket::SetTTL(unsigned int ttl) {
	setsockopt(s, IPPROTO_IP, IP_TTL, (char*)(&ttl), sizeof(ttl));
}

std::string UDPSocket::GetLastAddress() {
	return SockAddrToString((sockaddr*)(&last_sockaddr));
}

unsigned int UDPSocket::GetLastPort() {
	return SockAddrGetPort((sockaddr*)(&last_sockaddr));
}

unsigned int UDPSocket::GetMaxMessageSize() {
	return maxmessagesize;
}
