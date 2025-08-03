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

gmexport double socket_create() {
    Socket *s = NULL; // GCC is complaining for some reason ...
    s = new Socket();
    try {
        gmdata.sockets.insert(std::pair<unsigned int, Socket*>(++gmdata.idcounter_sockets, s));
    }
    catch(...) {
        delete s;
        throw;
    }
    return gmdata.idcounter_sockets;
}

gmexport double socket_destroy(double id) {
    std::map<unsigned int, Socket*>::iterator it = gmdata.sockets.find(gm_cast<unsigned int>(id));
    if(it == gmdata.sockets.end()) {
        return 0;
    }
    delete it->second;
    gmdata.sockets.erase(it);
    return 1;
}

gmexport double socket_exists(double id) {
    Socket *s = gmdata.FindSocket(gm_cast<unsigned int>(id));
    return (s == NULL)? 0 : 1;
}

gmexport double socket_get_state(double id) {
    Socket *s = gmdata.FindSocket(gm_cast<unsigned int>(id));
    if(s == NULL) return 0;
    return s->GetState();
}

gmexport double socket_reset(double id) {
    Socket *s = gmdata.FindSocket(gm_cast<unsigned int>(id));
    if(s == NULL) return 0;
    s->Reset();
    return 1;
}

gmexport double socket_connect(double id, const char* address, double port) {
    Socket *s = gmdata.FindSocket(gm_cast<unsigned int>(id));
    if(s == NULL) return 0;
    s->Connect(address, gm_cast<unsigned int>(port));
    return 1;
}

gmexport double socket_update_read(double id) {
    Socket *s = gmdata.FindSocket(gm_cast<unsigned int>(id));
    if(s == NULL) return 0;
    s->UpdateRead();
    return 1;
}

gmexport double socket_update_write(double id) {
    Socket *s = gmdata.FindSocket(gm_cast<unsigned int>(id));
    if(s == NULL) return 0;
    s->UpdateWrite();
    return 1;
}

gmexport double socket_shut_down(double id) {
    Socket *s = gmdata.FindSocket(gm_cast<unsigned int>(id));
    if(s == NULL) return 0;
    s->ShutDown();
    return 1;
}

gmexport const char* socket_get_peer_address(double id) {
    Socket *s = gmdata.FindSocket(gm_cast<unsigned int>(id));
    if(s == NULL) return "";
    gmreturnstring = s->GetPeerAddress();
    return gmreturnstring.c_str();
}

gmexport double socket_read_data(double id, double buffer_id, double bytes) {
    Socket *s = gmdata.FindSocket(gm_cast<unsigned int>(id));
    if(s == NULL) return 0;
    Buffer *b = gmdata.FindBuffer(gm_cast<unsigned int>(buffer_id));
    if(b == NULL) return 0;
    unsigned int l = gm_cast<unsigned int>(bytes);
    if(l>s->GetReadDataLength()) {
        return 0;
    }
    b->Clear();
    b->SetLength(l);
    memcpy(b->GetData(), s->GetReadData(), l);
    s->EraseReadData(l);
    return 1;
}

gmexport double socket_write_data(double id, double buffer_id) {
    Socket *s = gmdata.FindSocket(gm_cast<unsigned int>(id));
    if(s == NULL) return 0;
    Buffer *b = gmdata.FindBuffer(gm_cast<unsigned int>(buffer_id));
    if(b == NULL) return 0;
    s->Write(b->GetData(), b->GetLength());
    return 1;
}

gmexport double socket_read_message(double id, double buffer_id) {
    Socket *s = gmdata.FindSocket(gm_cast<unsigned int>(id));
    if(s == NULL) return 0;
    Buffer *b = gmdata.FindBuffer(gm_cast<unsigned int>(buffer_id));
    if(b == NULL) return 0;
    return (s->ReadMessage(b))? 1 : 0;
}

gmexport double socket_write_message(double id, double buffer_id) {
    Socket *s = gmdata.FindSocket(gm_cast<unsigned int>(id));
    if(s == NULL) return 0;
    Buffer *b = gmdata.FindBuffer(gm_cast<unsigned int>(buffer_id));
    if(b == NULL) return 0;
    s->WriteMessage(b);
    return 1;
}

gmexport double socket_read_message_delimiter(double id, double buffer_id, const char* delimiter) {
    Socket *s = gmdata.FindSocket(gm_cast<unsigned int>(id));
    if(s == NULL) return 0;
    Buffer *b = gmdata.FindBuffer(gm_cast<unsigned int>(buffer_id));
    if(b == NULL) return 0;
    return (s->ReadMessageDelimiter(b, delimiter[0]))? 1 : 0;
}

gmexport double socket_write_message_delimiter(double id, double buffer_id, const char* delimiter) {
    Socket *s = gmdata.FindSocket(gm_cast<unsigned int>(id));
    if(s == NULL) return 0;
    Buffer *b = gmdata.FindBuffer(gm_cast<unsigned int>(buffer_id));
    if(b == NULL) return 0;
    s->WriteMessageDelimiter(b, delimiter[0]);
    return 1;
}

gmexport double socket_get_read_data_length(double id) {
    Socket *s = gmdata.FindSocket(gm_cast<unsigned int>(id));
    if(s == NULL) return 0;
    return s->GetReadDataLength();
}

gmexport double socket_get_write_data_length(double id) {
    Socket *s = gmdata.FindSocket(gm_cast<unsigned int>(id));
    if(s == NULL) return 0;
    return s->GetWriteDataLength();
}
