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
    ///socket_create()
    //Creates a new socket and returns the id.
    
    Socket *s = NULL;
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
    //socket_destroy(id)
    //id: socket index
    //Destroys a socket.
    
    std::map<unsigned int, Socket*>::iterator it = gmdata.sockets.find(gm_cast<unsigned int>(id));
    if(it == gmdata.sockets.end()) {
        return 0;
    }
    delete it->second;
    gmdata.sockets.erase(it);
    return 1;
}

gmexport double socket_exists(double id) {
    ///socket_exists(id)
    //id: socket index
    //Returns whether a socket with the given id exists.
    
    Socket *s = gmdata.FindSocket(gm_cast<unsigned int>(id));
    return (s == NULL)? 0 : 1;
}

gmexport double socket_get_state(double id) {
    ///socket_get_state(id)
    //id: socket index
    //returns: state constant
    //0 = tcp_offline (the socket is not connected)
    //1 = tcp_connecting (the socket is still trying to connect)
    //2 = tcp_connected (the socket has been connected successfully)
    //4 = tcp_closed (the connection has been closed)
    //5 = tcp_error (an error has occurred)
    
    Socket *s = gmdata.FindSocket(gm_cast<unsigned int>(id));
    if(s == NULL) return 0;
    return s->GetState();
}

gmexport double socket_reset(double id) {
    ///socket_reset(id)
    //id: socket index
    //Resets the socket to its initial state. The connection is closed if the socket is currently connected.
    
    Socket *s = gmdata.FindSocket(gm_cast<unsigned int>(id));
    if(s == NULL) return 0;
    s->Reset();
    return 1;
}

gmexport double socket_connect(double id, const char* address, double port) {
    ///socket_connect(id,address,port)
    //id: socket index
    //address: address to connect
    //port: port number to use
    //Connects the socket. Use socket_get_state() to check how the connection proceeds.
    
    Socket *s = gmdata.FindSocket(gm_cast<unsigned int>(id));
    if(s == NULL) return 0;
    s->Connect(address, gm_cast<unsigned int>(port));
    return 1;
}

gmexport double socket_receive(double id) {
    ///socket_receive(id)
    //id: socket index
    //Receives any pending data. This function should be called once per step, before reading messages.
    //You should call this even if you don't intend to receive any messages, because it is required to complete a connection or detect when an existing connection is closed.
    
    Socket *s = gmdata.FindSocket(gm_cast<unsigned int>(id));
    if(s == NULL) return 0;
    s->UpdateRead();
    return 1;
}

gmexport double socket_send(double id) {
    ///socket_send(id)
    //id: socket index
    //Sends any pending data. This function should be called once per step, after writing messages.
    //Calling this function once is not enough to guarantee that all data has been sent, you should keep calling it every step even if you only write messages once.
    
    Socket *s = gmdata.FindSocket(gm_cast<unsigned int>(id));
    if(s == NULL) return 0;
    s->UpdateWrite();
    return 1;
}

gmexport double socket_close(double id) {
    ///socket_close(id)
    //id: socket index
    //Shuts down the socket after all data has been sent.
    //You can use this function to gracefully close a connection while guaranteeing that all data that is sent will actually arrive at the other side.
    //After all the data has been received by the other side, the state of the socket at the other side will change to tcp_closed.
    //The other side should respond to this by either calling socket_close as well, or simply destroying the socket, which will change the state of this socket to tcp_closed as well.
    
    Socket *s = gmdata.FindSocket(gm_cast<unsigned int>(id));
    if(s == NULL) return 0;
    s->ShutDown();
    return 1;
}

gmexport const char* socket_get_peer_address(double id) {
    ///socket_get_peer_address(id)
    //id: socket index
    //Returns the IP address of the computer this socket is connected to.
    //This function does not work if the socket is still connecting - wait until socket_get_state returns tcp_connected (2).
    
    Socket *s = gmdata.FindSocket(gm_cast<unsigned int>(id));
    if(s == NULL) return "";
    gmreturnstring = s->GetPeerAddress();
    return gmreturnstring.c_str();
}

gmexport double socket_read_data(double id, double buffer_id, double bytes) {
    ///socket_read_data(id,buffer,length)
    //id: socket index
    //buffer: buffer to use
    //length: length to retrieve
    //Reads a data block with a fixed size without any formatting.
    
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
    ///socket_write_data(id,buffer)
    //id: socket index
    //buffer: buffer to send
    //Sends a data block without any formatting.
    
    Socket *s = gmdata.FindSocket(gm_cast<unsigned int>(id));
    if(s == NULL) return 0;
    Buffer *b = gmdata.FindBuffer(gm_cast<unsigned int>(buffer_id));
    if(b == NULL) return 0;
    s->Write(b->GetData(), b->GetLength());
    return 1;
}

gmexport double socket_read_message(double id, double buffer_id) {
    ///socket_read_message(id,buffer)
    //id: socket index
    //buffer: buffer to use
    //returns: whether there was a message available.
    //Reads a new message, i.e. copies the contents of the message to the buffer.
    //You should use a while loop on this function to read all available messages.
    
    Socket *s = gmdata.FindSocket(gm_cast<unsigned int>(id));
    if(s == NULL) return 0;
    Buffer *b = gmdata.FindBuffer(gm_cast<unsigned int>(buffer_id));
    if(b == NULL) return 0;
    return (s->ReadMessage(b))? 1 : 0;
}

gmexport double socket_write_message(double id, double buffer_id) {
    ///socket_write_message(id,buffer)
    //buffer: buffer to send
    //id: socket index
    //Sends a message. This is handled automatically by the DLL, you don't need to do anything special if the receiver also uses Http Dll 2.
    
    Socket *s = gmdata.FindSocket(gm_cast<unsigned int>(id));
    if(s == NULL) return 0;
    Buffer *b = gmdata.FindBuffer(gm_cast<unsigned int>(buffer_id));
    if(b == NULL) return 0;
    s->WriteMessage(b);
    return 1;
}

gmexport double socket_read_message_delimiter(double id, double buffer_id, const char* delimiter) {
    ///socket_read_message_delimiter(id,buffer,delimiter)
    //id: socket index
    //buffer: buffer to use
    //delimiter: a string of one character
    //Reads a message that uses the delimiter format (i.e. a message sent by socket_write_message_delimiter). The delimiter should be a single character.
    
    Socket *s = gmdata.FindSocket(gm_cast<unsigned int>(id));
    if(s == NULL) return 0;
    Buffer *b = gmdata.FindBuffer(gm_cast<unsigned int>(buffer_id));
    if(b == NULL) return 0;
    return (s->ReadMessageDelimiter(b, delimiter[0]))? 1 : 0;
}

gmexport double socket_write_message_delimiter(double id, double buffer_id, const char* delimiter) {
    ///socket_write_message_delimiter(id,buffer,delimiter)
    //id: socket index
    //buffer: buffer to use
    //delimiter: a string of one character
    //Sends a message using the delimiter format. The delimiter should be a single character.
    
    Socket *s = gmdata.FindSocket(gm_cast<unsigned int>(id));
    if(s == NULL) return 0;
    Buffer *b = gmdata.FindBuffer(gm_cast<unsigned int>(buffer_id));
    if(b == NULL) return 0;
    s->WriteMessageDelimiter(b, delimiter[0]);
    return 1;
}

gmexport double socket_get_receiving_size(double id) {
    ///socket_get_receiving_size(id)
    //id: socket index
    //Returns the length of the data that has been received but not read yet.
    
    Socket *s = gmdata.FindSocket(gm_cast<unsigned int>(id));
    if(s == NULL) return 0;
    return s->GetReadDataLength();
}

gmexport double socket_get_sending_size(double id) {
    ///socket_get_sending_size(id)
    //id: socket index
    //Returns the length of the data that has been written but not sent yet.
    
    Socket *s = gmdata.FindSocket(gm_cast<unsigned int>(id));
    if(s == NULL) return 0;
    return s->GetWriteDataLength();
}
