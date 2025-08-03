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

gmexport double listener_create() {
    ///listener_create()
    //Creates and returns a new listener.
    //Listeners react to incoming connections, and are needed to connect sockets.
    
	ListeningSocket *ls = NULL;
	ls = new ListeningSocket();
	try {
		gmdata.listeningsockets.insert(std::pair<unsigned int, ListeningSocket*>(++gmdata.idcounter_listeningsockets, ls));
	}
	catch(...) {
		delete ls;
		throw;
	}
	return gmdata.idcounter_listeningsockets;
}

gmexport double listener_destroy(double id) {
    ///listener_destroy(id)
    //id: listener index
    //Destroys a listener.
    
	std::map<unsigned int, ListeningSocket*>::iterator it = gmdata.listeningsockets.find(gm_cast<unsigned int>(id));
	if(it == gmdata.listeningsockets.end()) {
		return 0;
	}
	delete it->second;
	gmdata.listeningsockets.erase(it);
	return 1;
}

gmexport double listener_exists(double id) {
    ///listener_exists(id)
    //id: listener index
    //Returns whether the listener with id exists.
    
	ListeningSocket *ls = gmdata.FindListeningSocket(gm_cast<unsigned int>(id));
	return (ls == NULL)? 0 : 1;
}

gmexport double listener_active(double id) {
    ///listener_active(id)
    //id: listener index
    //Returns whether the listener with id is listening to incoming connections.
    
	ListeningSocket *ls = gmdata.FindListeningSocket(gm_cast<unsigned int>(id));
	if(ls == NULL) return 0;
	return (ls->IsListening())? 1 : 0;
}

gmexport double listener_start(double id, double ipv6, double port, double local) {
    ///listener_start(id)
    //id: listener index
    //ipv6: whether to use ipv6, or default to ipv4
    //port: port number to listen in
    //local: whether to skip firewall warnings and expect only connections from this computer
    //Starts listening for incoming connections from other clients.
    
	ListeningSocket *ls = gmdata.FindListeningSocket(gm_cast<unsigned int>(id));
	if(ls == NULL) return 0;
	ls->StartListening(gm_cast<bool>(ipv6), gm_cast<unsigned int>(port), gm_cast<bool>(local));
	return 1;
}

gmexport double listener_stop(double id) {
    ///listener_stop(id)
    //id: listener index
    //Stops listening for incoming connections.
    
	ListeningSocket *ls = gmdata.FindListeningSocket(gm_cast<unsigned int>(id));
	if(ls == NULL) return 0;
	ls->StopListening();
	return 1;
}

gmexport double listener_can_accept(double id) {
    ///listener_can_accept(id)
    //id: listener index
    //Returns whether a connection attempt is underway.
    //Use listener_accept() to accept a connection.    
	
	ListeningSocket *ls = gmdata.FindListeningSocket(gm_cast<unsigned int>(id));
	if(ls == NULL) return 0;
	return (ls->CanAccept())? 1 : 0;
}

gmexport double listener_accept(double id, double socket_id) {    
    ///listener_accept(id,socket)
    //id: listener index
    //Connects an incoming client to a socket, completing the connection.
	
	ListeningSocket *ls = gmdata.FindListeningSocket(gm_cast<unsigned int>(id));
	if(ls == NULL) return 0;
	Socket *s = gmdata.FindSocket(gm_cast<unsigned int>(socket_id));
	if(s == NULL) return 0;
	ls->Accept(s);
	return 1;
}
