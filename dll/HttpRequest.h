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

#include "Socket.h"
#include <string>
#include <vector>

class HttpRequest {
	
	public:
	enum enum_state {
		state_notconnected = 0,
		state_wait_statuscode = 1,
		state_wait_headers = 2,
		state_wait_messagebody = 3,
		state_closed = 4,
		state_error = 5,
	};
	
	private:
	struct Header {
		std::string name, value;
	};
	struct PostParameter {
		std::string name, filename, value;
	};
	
	private:
	enum_state state;
	Socket s;
	std::vector<Header> requestheaders;
	std::vector<PostParameter> postparameters;
	
	unsigned int statuscode;
	std::vector<Header> responseheaders;
	
	public:
	static std::string UrlEncode(const std::string& str, bool keepspecialchars = false);
	static std::string UrlDecode(const std::string& str);
	
	public:
	HttpRequest();
	
	void SetRequestHeader(const std::string& name, const std::string& value, bool replace = true);
	void RemoveRequestHeader(const std::string& name);
	void ClearRequestHeaders();
	
	void SetPostParameter(const std::string& name, const std::string& value);
	void SetPostParameterFile(const std::string& name, const std::string& filename, const std::string& value);
	void RemovePostParameter(const std::string& name);
	void ClearPostParameters();
	
	void Reset();
	void Connect(const std::string& url, bool post);
	void Update();
	
	unsigned int GetStatusCode();
	
	unsigned int GetResponseHeaderCount();
	std::string GetResponseHeaderName(unsigned int i);
	std::string GetResponseHeaderValue(unsigned int i);
	std::string FindResponseHeader(const std::string& name);
	
	const char* GetMessageBody();
	unsigned int GetMessageBodyLength();
	
	private:
	bool RequestHeaderExists(const std::string& name);
	
	public:
	inline enum_state GetState() { return state; }
	
};
