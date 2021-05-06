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

#include "HttpRequest.h"

#include "StringConversion.h"

#include <cassert>
#include <cstring>
#include <cstdlib>
#include <ctime>

struct HttpRequest_RNG {
	HttpRequest_RNG() {
		srand(clock());
	}
} httprequest_rng;

struct HttpRequest_UrlEncodeTable {
	unsigned char table[256];
	HttpRequest_UrlEncodeTable() {
		memset(table, 0, 256);
		for(const char *p = "!*'();:@&=+$,/?#[]%"; *p != '\0'; ++p) { table[(unsigned char)(*p)] = 1; }
		for(const char *p = "-_.~"; *p != '\0'; ++p) { table[(unsigned char)(*p)] = 2; }
		for(char c = '0'; c <= '9'; ++c) { table[(unsigned char)(c)] = 2; }
		for(char c = 'a'; c <= 'z'; ++c) { table[(unsigned char)(c)] = 2; }
		for(char c = 'A'; c <= 'Z'; ++c) { table[(unsigned char)(c)] = 2; }
	}
} httprequest_urlencodetable;

bool caseinsensitive_equal(const std::string& a, const std::string& b) {
	if(a.length() != b.length()) return false;
	return (memicmp(a.data(), b.data(), a.length()) == 0);
}

std::string HttpRequest::UrlEncode(const std::string& str, bool keepspecialchars) {
	const char *hextable = "0123456789abcdef";
	unsigned char threshold = (keepspecialchars)? 1 : 2;
	unsigned int j = 0;
	for(unsigned int i = 0; i < str.length(); ++i) {
		unsigned char c = (unsigned char) str[i];
		if(httprequest_urlencodetable.table[c] >= threshold) {
			j += 1;
		} else {
			j += 3;
		}
	}
	std::string ret(j, '\0');
	j = 0;
	for(unsigned int i = 0; i < str.length(); ++i) {
		unsigned char c = (unsigned char) str[i];
		if(httprequest_urlencodetable.table[c] >= threshold) {
			ret[j++] = c;
		} else {
			ret[j++] = '%';
			ret[j++] = hextable[c >> 4];
			ret[j++] = hextable[c & 15];
		}
	}
	return ret;
}

std::string HttpRequest::UrlDecode(const std::string& str) {
	std::string ret(str.length(), '\0');
	unsigned int j = 0;
	for(unsigned int i = 0; i < str.length(); ++i) {
		unsigned char c = (unsigned char) str[i];
		if(c == '%' && i + 2 < str.length()) {
			unsigned char a = (unsigned char) str[i + 1];
			unsigned char b = (unsigned char) str[i + 2];
			ret[j++] =
				((('0' <= a && a <= '9')? a - '0' :
				  ('a' <= a && a <= 'f')? 10 + a - 'a' :
				  ('A' <= a && a <= 'F')? 10 + a - 'A' : 0) << 4) |
				 (('0' <= b && b <= '9')? b - '0' :
				  ('a' <= b && b <= 'f')? 10 + b - 'a' :
				  ('A' <= b && b <= 'F')? 10 + b - 'A' : 0);
			i += 2;
		} else {
			ret[j++] = c;
		}
	}
	ret.resize(j);
	return ret;
}

HttpRequest::HttpRequest() {
	state = state_notconnected;
}

void HttpRequest::SetRequestHeader(const std::string& name, const std::string& value, bool replace) {
	if(replace) {
		for(unsigned int i = 0; i < requestheaders.size(); ++i) {
			if(caseinsensitive_equal(requestheaders[i].name, name)) {
				requestheaders[i].value = value;
				return;
			}
		}
	}
	Header h = {name, value};
	requestheaders.push_back(h);
}

void HttpRequest::RemoveRequestHeader(const std::string& name) {
	for(unsigned int i = requestheaders.size(); i > 0; ) {
		--i;
		if(caseinsensitive_equal(requestheaders[i].name, name)) {
			requestheaders.erase(requestheaders.begin() + i);
		}
	}
}

void HttpRequest::ClearRequestHeaders() {
	requestheaders.clear();
}

void HttpRequest::SetPostParameter(const std::string& name, const std::string& value) {
	for(unsigned int i = 0; i < postparameters.size(); ++i) {
		if(caseinsensitive_equal(postparameters[i].name, name)) {
			postparameters[i].value = value;
			return;
		}
	}
	PostParameter pp = {name, "", value};
	postparameters.push_back(pp);
}

void HttpRequest::SetPostParameterFile(const std::string& name, const std::string& filename, const std::string& value) {
	for(unsigned int i = 0; i < postparameters.size(); ++i) {
		if(caseinsensitive_equal(postparameters[i].name, name)) {
			postparameters[i].value = value;
			return;
		}
	}
	PostParameter pp = {name, filename, value};
	postparameters.push_back(pp);
}

void HttpRequest::RemovePostParameter(const std::string& name) {
	for(unsigned int i = postparameters.size(); i > 0; ) {
		--i;
		if(caseinsensitive_equal(postparameters[i].name, name)) {
			postparameters.erase(postparameters.begin() + i);
		}
	}
}

void HttpRequest::ClearPostParameters() {
	postparameters.clear();
}

void HttpRequest::Reset() {
	
	s.Reset();
	requestheaders.clear();
	postparameters.clear();
	statuscode = 0;
	responseheaders.clear();
	state = state_notconnected;
	
}

void HttpRequest::Connect(const std::string& url, bool post) {
	
	// disconnect
	if(state != state_notconnected) {
		s.Reset();
		statuscode = 0;
		responseheaders.clear();
	}
	
	// get host, port and file
	std::string host, file;
	unsigned int port;
	{
		unsigned int pos_host = (url.substr(0, 7) == "http://")? 7 : 0;
		unsigned int pos_slash = url.find('/', pos_host);
		if(pos_slash == std::string::npos) {
			pos_slash = url.length();
			file = "/";
		} else {
			file = url.substr(pos_slash);
		}
		unsigned int pos_colon = url.find(':', pos_host);
		if(pos_colon > pos_slash) {
			port = 80;
			host = url.substr(pos_host, pos_slash - pos_host);
		} else {
			std::string portstring = url.substr(pos_colon + 1, pos_slash - (pos_colon + 1));
			port = StringToUInt(portstring.data(), portstring.length());
			host = url.substr(pos_host, pos_colon - pos_host);
		}
	}
	file = UrlEncode(file, true);
	
	// write HTTP request
	{
		const char *method = (post)? "POST " : "GET ";
		const char *httpversion = " HTTP/1.0\r\n";
		s.Write(method, strlen(method));
		s.Write(file.data(), file.length());
		s.Write(httpversion, strlen(httpversion));
	}
	if(!RequestHeaderExists("Host")) {
		Header h = {"Host", host};
		requestheaders.push_back(h);
	}
	
	// write post data
	std::string sendmessagebody;
	if(post) {
		
		// use 'multipart' encoding?
		bool use_multipart = false;
		for(unsigned int i = 0; i < postparameters.size(); ++i) {
			if(!postparameters[i].filename.empty()) {
				use_multipart = true;
				break;
			}
		}
		
		std::string content_type;
		if(use_multipart) {
			
			// generate random boundary
			std::string boundary;
			for( ; ; ) {
				boundary.assign(25, '-');
				for(unsigned int i = 0; i < 15; ++i) {
					boundary.push_back('a' + rand() % 26);
				}
				for(unsigned int i = 0; i < postparameters.size(); ++i) {
					if(postparameters[i].name.find(boundary) != std::string::npos
						|| postparameters[i].filename.find(boundary) != std::string::npos
						|| postparameters[i].value.find(boundary) != std::string::npos) {
						continue;
					}
				}
				break;
			}
			
			// generate 'multipart' message body
			for(unsigned int i = 0; i < postparameters.size(); ++i) {
				sendmessagebody += "--";
				sendmessagebody += boundary;
				sendmessagebody += "\r\nContent-Disposition: form-data; name=\"";
				sendmessagebody += postparameters[i].name;
				if(!postparameters[i].filename.empty()) {
					sendmessagebody += "\"; filename=\"";
					sendmessagebody += postparameters[i].filename;
				}
				sendmessagebody += "\"\r\n\r\n";
				sendmessagebody += postparameters[i].value;
				sendmessagebody += "\r\n";
			}
			sendmessagebody += "--";
			sendmessagebody += boundary;
			sendmessagebody += "--\r\n";
			
			// set the content type
			content_type = "multipart/form-data; boundary=";
			content_type += boundary;
			
		} else {
			
			// generate 'normal' message body
			for(unsigned int i = 0; i < postparameters.size(); ++i) {
				if(i != 0) sendmessagebody += "&";
				sendmessagebody += postparameters[i].name;
				sendmessagebody += "=";
				sendmessagebody += UrlEncode(postparameters[i].value);
			}
			
			// set the content type
			content_type = "application/x-www-form-urlencoded";
			
		}
		
		SetRequestHeader("Content-Type", content_type);
		SetRequestHeader("Content-Length", UIntToString(sendmessagebody.size()));
		
	}
	
	// write headers
	for(unsigned int i = 0; i < requestheaders.size(); ++i) {
		Header *h = &requestheaders[i];
		s.Write(h->name.data(), h->name.length());
		s.Write(": ", 2);
		s.Write(h->value.data(), h->value.length());
		s.Write("\r\n", 2);
	}
	s.Write("\r\n", 2);
	s.Write(sendmessagebody.data(), sendmessagebody.length());
	
	// connect
	s.Connect(host, port);
	state = state_wait_statuscode;
	
}

void HttpRequest::Update() {
	
	if(state == state_notconnected || state == state_closed || state == state_error) {
		return;
	}
	
	s.UpdateRead();
	s.UpdateWrite();
	
	if(state == state_wait_statuscode) {
		const char *data = (const char*) s.GetReadData();
		unsigned int len = s.GetReadDataLength();
		for(unsigned int linelen = 0; linelen + 1 < len; ++linelen) {
			if(data[linelen] == '\r' && data[linelen + 1] == '\n') {
				
				// skip http version
				unsigned int i;
				for(i = 0; i < linelen; ++i) {
					if(data[i] == ' ') break;
				}
				++i;
				
				// read status code
				unsigned int j;
				for(j = i; j < linelen; ++j) {
					if(data[j] == ' ') break;
				}
				statuscode = StringToUInt(data + i, j - i);
				s.EraseReadData(linelen + 2);
				state = state_wait_headers;
				
				break;
				
			}
		}
	}
	
	if(state == state_wait_headers) {
		const char *data = (const char*)(s.GetReadData());
		unsigned int len = s.GetReadDataLength();
		unsigned int headerslen;
		for(headerslen = 0; headerslen + 3 < len; ++headerslen) {
			if(data[headerslen] == '\r' && data[headerslen + 1] == '\n'
				&& data[headerslen + 2] == '\r' && data[headerslen + 3] == '\n') {
				
				unsigned int i = 0;
				while(i < headerslen) {
					
					// find end of line
					unsigned int j;
					for(j = i; j + 1 < headerslen; ++j) {
						if(data[j] == '\r' && data[j + 1] == '\n') {
							if(j + 2 >= headerslen) break;
							if(data[j + 2] != ' ' && data[j + 2] != '\t') break;
						}
					}
					if(j + 1 >= headerslen) {
						j = headerslen;
					}
					
					// find colon
					unsigned int k;
					for(k = i; k < j; ++k) {
						if(data[k] == ':') break;
					}
					
					// read name
					Header h;
					h.name.assign(data + i, k - i);
					++k;
					
					// read value (and replace whitespace with one space character)
					{
						unsigned int s = 0;
						bool whitespace = true;
						for(unsigned int l = k; l < j; ++l) {
							if(data[l] == ' ' || data[l] == '\t') {
								if(!whitespace) {
									++s;
								}
								whitespace = true;
							} else {
								++s;
								whitespace = false;
							}
						}
						h.value.resize(s, '\0');
					}
					{
						unsigned int s = 0;
						bool whitespace = true;
						for(unsigned int l = k; l < j; ++l) {
							if(data[l] == ' ' || data[l] == '\t') {
								if(!whitespace) {
									h.value[s++] = ' ';
								}
								whitespace = true;
							} else {
								h.value[s++] = data[l];
								whitespace = false;
							}
						}
					}
					responseheaders.push_back(h);
					
					// skip \r\n characters
					i = j + 2;
					
				}
				
				s.EraseReadData(headerslen + 4);
				state = state_wait_messagebody;
				break;
				
			}
		}
	}
	
	switch(s.GetState()) {
		case Socket::state_closed: {
			s.ShutDown();
			if(state == state_wait_messagebody) {
				state = state_closed;
			} else {
				state = state_error;
			}
			break;
		}
		case Socket::state_error: {
			state = state_error;
			break;
		}
		default: { // for GCC
			break;
		}
	}
	
}

unsigned int HttpRequest::GetStatusCode() {
	return statuscode;
}

unsigned int HttpRequest::GetResponseHeaderCount() {
	return responseheaders.size();
}

std::string HttpRequest::GetResponseHeaderName(unsigned int i) {
	if(i >= responseheaders.size()) return "";
	return responseheaders[i].name;
}

std::string HttpRequest::GetResponseHeaderValue(unsigned int i) {
	if(i >= responseheaders.size()) return "";
	return responseheaders[i].value;
}

std::string HttpRequest::FindResponseHeader(const std::string& name) {
	for(unsigned int i = 0; i < responseheaders.size(); ++i) {
		if(caseinsensitive_equal(responseheaders[i].name, name)) {
			return responseheaders[i].value;
		}
	}
	return "";
}

const char* HttpRequest::GetMessageBody() {
	if(state != state_wait_messagebody && state != state_closed) {
		return NULL;
	}
	return s.GetReadData();
}

unsigned int HttpRequest::GetMessageBodyLength() {
	if(state != state_wait_messagebody && state != state_closed) {
		return 0;
	}
	return s.GetReadDataLength();
}

bool HttpRequest::RequestHeaderExists(const std::string& name) {
	for(unsigned int i = 0; i < requestheaders.size(); ++i) {
		if(caseinsensitive_equal(requestheaders[i].name, name)) {
			return true;
		}
	}
	return false;
}
