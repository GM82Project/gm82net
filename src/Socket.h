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

#pragma once

#include "Buffer.h"

#ifdef WINVER
#undef WINVER
#endif
#ifdef _WIN32_WINNT
#undef _WIN32_WINNT
#endif
#ifdef _WIN32_WINDOWS
#undef _WIN32_WINDOWS
#endif
#ifdef _WIN32_IE
#undef _WIN32_IE
#endif

#define WINVER          0x0501
#define _WIN32_WINNT    0x0501
#define _WIN32_WINDOWS  0x0501
#define _WIN32_IE       0x0501

#include <winsock2.h>
#include <ws2tcpip.h>
#include <string>
#include <algorithm>

bool InitSockets();
void CleanupSockets();

class Socket;

class ListeningSocket {
	
	private:
	bool listening;
	SOCKET s;
	
	public:
	ListeningSocket();
	~ListeningSocket();
	
	void StartListening(bool ipv6, unsigned int port, bool local);
	void StopListening();
	bool CanAccept();
	void Accept(Socket* socket);
	
	public:
	inline bool IsListening() { return listening; }
	
};

class Socket {
	
	friend class ListeningSocket;
	
	public:
	enum enum_state {
		state_notconnected = 0,
		state_connecting = 1,
		state_connected = 2,
		//state_shutdown = 3, // removed in version 2.3.4, numbers are kept for backward compatibility
		state_closed = 4,
		state_error = 5,
	};
	
	private:
	enum_state state;
	SOCKET s;
	addrinfo *first_addrinfo, *current_addrinfo;
	Buffer readbuffer, writebuffer;
	bool should_shut_down;
	
	public:
	Socket();
	~Socket();
	
	public:
	void Reset();
	void Connect(const std::string& address, unsigned int port);
	void UpdateRead();
	void UpdateWrite();
	void ShutDown();
	
	std::string GetPeerAddress();
	
	const char* GetReadData();
	unsigned int GetReadDataLength();
	void EraseReadData(unsigned int length);
	
	void Write(const char* data, unsigned int length);
	unsigned int GetWriteDataLength();
	
	bool ReadMessage(Buffer *b);
	void WriteMessage(Buffer *b);
	bool ReadMessageDelimiter(Buffer *b, char delimiter);
	void WriteMessageDelimiter(Buffer *b, char delimiter);
	
	public:
	inline enum_state GetState() { return state; }
	
};

class UDPSocket {
	
	public:
	enum enum_state {
		state_notstarted = 0,
		state_started = 1,
		state_error = 2,
	};
	
	private:
	enum_state state;
	SOCKET s;
	unsigned int maxmessagesize;
	sockaddr_in6 destination_sockaddr, last_sockaddr;
	bool ipv6;
	
	public:
	UDPSocket();
	~UDPSocket();
	
	void Reset();
	void Start(bool ipv6, unsigned int port);
	void SetDestination(std::string address, unsigned int port);
	bool Receive(Buffer *b);
	void Send(Buffer *b);
	
	unsigned int GetTTL();
	void SetTTL(unsigned int ttl);
	
	std::string GetLastAddress();
	unsigned int GetLastPort();
	unsigned int GetMaxMessageSize();
	
	public:
	inline enum_state GetState() { return state; } 
	
};
