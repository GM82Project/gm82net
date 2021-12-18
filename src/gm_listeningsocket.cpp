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

gmexport double listeningsocket_create() {
	ListeningSocket *ls = NULL; // GCC is complaining for some reason ...
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

gmexport double listeningsocket_destroy(double id) {
	std::map<unsigned int, ListeningSocket*>::iterator it = gmdata.listeningsockets.find(gm_cast<unsigned int>(id));
	if(it == gmdata.listeningsockets.end()) {
		return 0;
	}
	delete it->second;
	gmdata.listeningsockets.erase(it);
	return 1;
}

gmexport double listeningsocket_exists(double id) {
	ListeningSocket *ls = gmdata.FindListeningSocket(gm_cast<unsigned int>(id));
	return (ls == NULL)? 0 : 1;
}

gmexport double listeningsocket_is_listening(double id) {
	ListeningSocket *ls = gmdata.FindListeningSocket(gm_cast<unsigned int>(id));
	if(ls == NULL) return 0;
	return (ls->IsListening())? 1 : 0;
}

gmexport double listeningsocket_start_listening(double id, double ipv6, double port, double local) {
	ListeningSocket *ls = gmdata.FindListeningSocket(gm_cast<unsigned int>(id));
	if(ls == NULL) return 0;
	ls->StartListening(gm_cast<bool>(ipv6), gm_cast<unsigned int>(port), gm_cast<bool>(local));
	return 1;
}

gmexport double listeningsocket_stop_listening(double id) {
	ListeningSocket *ls = gmdata.FindListeningSocket(gm_cast<unsigned int>(id));
	if(ls == NULL) return 0;
	ls->StopListening();
	return 1;
}

gmexport double listeningsocket_can_accept(double id) {
	ListeningSocket *ls = gmdata.FindListeningSocket(gm_cast<unsigned int>(id));
	if(ls == NULL) return 0;
	return (ls->CanAccept())? 1 : 0;
}

gmexport double listeningsocket_accept(double id, double socket_id) {
	ListeningSocket *ls = gmdata.FindListeningSocket(gm_cast<unsigned int>(id));
	if(ls == NULL) return 0;
	Socket *s = gmdata.FindSocket(gm_cast<unsigned int>(socket_id));
	if(s == NULL) return 0;
	ls->Accept(s);
	return 1;
}
