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

// visual studio stuff
#define NOMINMAX

#include "Hash.h"
#include "Buffer.h"
#include "Socket.h"
#include "HttpRequest.h"

#include <limits>
#include <cstring>
#include <float.h>
#include <stdint.h>
#include <map>
#include <string>
#include <cinttypes>

// function exported to Game Maker
#define gmexport extern "C" __declspec (dllexport)

// gm_cast - cast without throwing exceptions
template<typename A>
inline A gm_cast(double d) {
	A minval = std::numeric_limits<A>::min();
	A maxval = std::numeric_limits<A>::max();
	if(d < (double)(minval)) {
		return minval;
	}
	if(d > (double)(maxval)) {
		return maxval;
	}
	return (A)(d);
}
template<>
inline float gm_cast<float>(double d) {
	float minval = -std::numeric_limits<float>::max();
	float maxval = std::numeric_limits<float>::max();
	if(d < (double)(minval)) {
		return minval;
	}
	if(d > (double)(maxval)) {
		return maxval;
	}
	return (float)(d);
}
template<>
inline double gm_cast<double>(double d) {
	return d;
}
template<>
inline bool gm_cast<bool>(double d) {
	return (d >= 0.5);
}

struct GMData {
	
	unsigned int idcounter_buffers, idcounter_listeningsockets, idcounter_sockets, idcounter_udpsockets, idcounter_httprequests;
	std::map<unsigned int, Buffer*> buffers;
	std::map<unsigned int, ListeningSocket*> listeningsockets;
	std::map<unsigned int, Socket*> sockets;
	std::map<unsigned int, UDPSocket*> udpsockets;
	std::map<unsigned int, HttpRequest*> httprequests;
	
	GMData() {
		idcounter_buffers = 0;
		idcounter_listeningsockets = 0;
		idcounter_sockets = 0;
		idcounter_udpsockets = 0;
		idcounter_httprequests = 0;
		InitSockets();
	}
	~GMData() {
		for(std::map<unsigned int, Buffer*>::iterator it = buffers.begin(); it != buffers.end(); ++it) {
			delete it->second;
		}
		for(std::map<unsigned int, ListeningSocket*>::iterator it = listeningsockets.begin(); it != listeningsockets.end(); ++it) {
			delete it->second;
		}
		for(std::map<unsigned int, Socket*>::iterator it = sockets.begin(); it != sockets.end(); ++it) {
			delete it->second;
		}
		for(std::map<unsigned int, UDPSocket*>::iterator it = udpsockets.begin(); it != udpsockets.end(); ++it) {
			delete it->second;
		}
		for(std::map<unsigned int, HttpRequest*>::iterator it = httprequests.begin(); it != httprequests.end(); ++it) {
			delete it->second;
		}
		CleanupSockets();
	}
	inline Buffer* FindBuffer(unsigned int id) {
		std::map<unsigned int, Buffer*>::iterator it = buffers.find(id);
		return (it == buffers.end())? NULL : it->second;
	}
	inline ListeningSocket* FindListeningSocket(unsigned int id) {
		std::map<unsigned int, ListeningSocket*>::iterator it = listeningsockets.find(id);
		return (it == listeningsockets.end())? NULL : it->second;
	}
	inline Socket* FindSocket(unsigned int id) {
		std::map<unsigned int, Socket*>::iterator it = sockets.find(id);
		return (it == sockets.end())? NULL : it->second;
	}
	inline UDPSocket* FindUDPSocket(unsigned int id) {
		std::map<unsigned int, UDPSocket*>::iterator it = udpsockets.find(id);
		return (it == udpsockets.end())? NULL : it->second;
	}
	inline HttpRequest* FindHttpRequest(unsigned int id) {
		std::map<unsigned int, HttpRequest*>::iterator it = httprequests.find(id);
		return (it == httprequests.end())? NULL : it->second;
	}
	
};

extern GMData gmdata;
extern std::string gmreturnstring;
