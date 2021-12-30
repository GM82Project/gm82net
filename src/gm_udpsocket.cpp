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

#include "gm.h"

gmexport double udpsocket_create() {
	UDPSocket *s = NULL; // GCC is complaining for some reason ...
	s = new UDPSocket();
	try {
		gmdata.udpsockets.insert(std::pair<unsigned int, UDPSocket*>(++gmdata.idcounter_udpsockets, s));
	}
	catch(...) {
		delete s;
		throw;
	}
	return gmdata.idcounter_udpsockets;
}

gmexport double udpsocket_destroy(double id) {
	std::map<unsigned int, UDPSocket*>::iterator it = gmdata.udpsockets.find(gm_cast<unsigned int>(id));
	if(it == gmdata.udpsockets.end()) {
		return 0;
	}
	delete it->second;
	gmdata.udpsockets.erase(it);
	return 1;
}

gmexport double udpsocket_exists(double id) {
	UDPSocket *s = gmdata.FindUDPSocket(gm_cast<unsigned int>(id));
	return (s == NULL)? 0 : 1;
}

gmexport double udpsocket_get_state(double id) {
	UDPSocket *s = gmdata.FindUDPSocket(gm_cast<unsigned int>(id));
	if(s == NULL) return 0;
	return s->GetState();
}

gmexport double udpsocket_reset(double id) {
	UDPSocket *s = gmdata.FindUDPSocket(gm_cast<unsigned int>(id));
	if(s == NULL) return 0;
	s->Reset();
	return 1;
}

gmexport double udpsocket_start(double id, double ipv6, double port) {
	UDPSocket *s = gmdata.FindUDPSocket(gm_cast<unsigned int>(id));
	if(s == NULL) return 0;
	s->Start(gm_cast<bool>(ipv6), gm_cast<unsigned int>(port));
	return 1;
}

gmexport double udpsocket_set_destination(double id, const char* address, double port) {
	UDPSocket *s = gmdata.FindUDPSocket(gm_cast<unsigned int>(id));
	if(s == NULL) return 0;
	s->SetDestination(address, gm_cast<unsigned int>(port));
	return 1;
}

gmexport double udpsocket_receive(double id, double buffer_id) {
	UDPSocket *s = gmdata.FindUDPSocket(gm_cast<unsigned int>(id));
	if(s == NULL) return 0;
	Buffer *b = gmdata.FindBuffer(gm_cast<unsigned int>(buffer_id));
	if(b == NULL) return 0;
	return (s->Receive(b))? 1 : 0;
}

gmexport double udpsocket_send(double id, double buffer_id) {
	UDPSocket *s = gmdata.FindUDPSocket(gm_cast<unsigned int>(id));
	if(s == NULL) return 0;
	Buffer *b = gmdata.FindBuffer(gm_cast<unsigned int>(buffer_id));
	if(b == NULL) return 0;
	s->Send(b);
	return 1;
}

gmexport const char* udpsocket_get_last_address(double id) {
	UDPSocket *s = gmdata.FindUDPSocket(gm_cast<unsigned int>(id));
	if(s == NULL) return "";
	gmreturnstring= s->GetLastAddress();
	return gmreturnstring.c_str();
}

gmexport double udpsocket_get_last_port(double id) {
	UDPSocket *s = gmdata.FindUDPSocket(gm_cast<unsigned int>(id));
	if(s == NULL) return 0;
	return s->GetLastPort();
}

gmexport double udpsocket_get_ttl(double id) {
	UDPSocket *s = gmdata.FindUDPSocket(gm_cast<unsigned int>(id));
	if(s == NULL) return 0;
	return s->GetTTL();
}

gmexport double udpsocket_set_ttl(double id, double ttl) {
	UDPSocket *s = gmdata.FindUDPSocket(gm_cast<unsigned int>(id));
	if(s == NULL) return 0;
	s->SetTTL(gm_cast<unsigned int>(ttl));
	return 1;
}

gmexport double udpsocket_get_max_message_size(double id) {
	UDPSocket *s = gmdata.FindUDPSocket(gm_cast<unsigned int>(id));
	if(s == NULL) return 0;
	return s->GetMaxMessageSize();
}
