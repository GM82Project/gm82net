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
    ///udpsocket_create()
    //Creates a new UDP socket and returns the id.
    
    UDPSocket *s = NULL;
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
    ///udpsocket_destroy(id)
    //id: UDP socket index
    //Destroys a UDP socket.
    
    std::map<unsigned int, UDPSocket*>::iterator it = gmdata.udpsockets.find(gm_cast<unsigned int>(id));
    if(it == gmdata.udpsockets.end()) {
        return 0;
    }
    delete it->second;
    gmdata.udpsockets.erase(it);
    return 1;
}

gmexport double udpsocket_exists(double id) {
    ///udpsocket_exists(id)
    //id: UDP socket index
    //Returns whether a UDP socket with the given id exists.
    
    UDPSocket *s = gmdata.FindUDPSocket(gm_cast<unsigned int>(id));
    return (s == NULL)? 0 : 1;
}

gmexport double udpsocket_get_state(double id) {
    ///udpsocket_get_state(id)
    //id: UDP socket index
    //Returns the current state of the UDP socket.
    //Return value:
    //0 = udp_notstarted (the UDP socket has not been started)
    //1 = udp_started (the UDP socket has been started)
    //2 = udp_error (an error has occurred)
    
    UDPSocket *s = gmdata.FindUDPSocket(gm_cast<unsigned int>(id));
    if(s == NULL) return 0;
    return s->GetState();
}

gmexport double udpsocket_reset(double id) {
    ///udpsocket_reset(id)
    //id: UDP socket index
    //Resets the UDP socket to its initial state.
    
    UDPSocket *s = gmdata.FindUDPSocket(gm_cast<unsigned int>(id));
    if(s == NULL) return 0;
    s->Reset();
    return 1;
}

gmexport double udpsocket_start(double id, double ipv6, double port) {
    ///udpsocket_start(id,ipv6,port)
    //id: UDP socket index
    //ipv6: whether to use ipv6, or default to ipv4
    //port: port number to listen in
    //Starts the UDP socket. You have to call this function once before sending or receiving messages.
    //For using a random port, set the port to 0, and the system will randomize a port when sending the first message, which is also required to receive messages.
    
    UDPSocket *s = gmdata.FindUDPSocket(gm_cast<unsigned int>(id));
    if(s == NULL) return 0;
    s->Start(gm_cast<bool>(ipv6), gm_cast<unsigned int>(port));
    return 1;
}

gmexport double udpsocket_set_destination(double id, const char* address, double port) {
    ///udpsocket_set_destination(id,address,port)
    //id: UDP socket index
    //address: address to send to
    //port: port number to send to
    //Sets the destination. It is possible to change the destination as many times as you want.
    
    UDPSocket *s = gmdata.FindUDPSocket(gm_cast<unsigned int>(id));
    if(s == NULL) return 0;
    s->SetDestination(address, gm_cast<unsigned int>(port));
    return 1;
}

gmexport double udpsocket_receive(double id, double buffer_id) {
    ///udpsocket_receive(id,buffer)
    //id: UDP socket index
    //buffer: buffer to store the message
    //returns: whether there was a message available
    //Receives a new message, and copies the contents of the message to the buffer.
    //You should use a while loop on this function to read all available messages at once.
    
    UDPSocket *s = gmdata.FindUDPSocket(gm_cast<unsigned int>(id));
    if(s == NULL) return 0;
    Buffer *b = gmdata.FindBuffer(gm_cast<unsigned int>(buffer_id));
    if(b == NULL) return 0;
    return (s->Receive(b))? 1 : 0;
}

gmexport double udpsocket_send(double id, double buffer_id) {
    ///udpsocket_send(id,buffer)
    //id: UDP socket index
    //buffer: buffer to send
    //Sends a message to the currently set destination.
    //UDP packets are more strictly limited in size, and large packets have a tendency to get dropped, so try to keep your messages within 512 bytes.
    
    UDPSocket *s = gmdata.FindUDPSocket(gm_cast<unsigned int>(id));
    if(s == NULL) return 0;
    Buffer *b = gmdata.FindBuffer(gm_cast<unsigned int>(buffer_id));
    if(b == NULL) return 0;
    s->Send(b);
    return 1;
}

gmexport const char* udpsocket_get_last_address(double id) {
    ///udpsocket_get_last_address(id)
    //id: UDP socket index
    //Returns the IP address the last message came from. Since UDP sockets are connectionless, this can be any IP, not just your destination address.
    //Note that the IP can be spoofed; a hacker can send a UDP message pretending to be from a different IP. You should never rely on the IP address alone in situations where security is important.
    UDPSocket *s = gmdata.FindUDPSocket(gm_cast<unsigned int>(id));
    if(s == NULL) return "";
    gmreturnstring= s->GetLastAddress();
    return gmreturnstring.c_str();
}

gmexport double udpsocket_get_last_port(double id) {
    ///udpsocket_get_last_port(id)
    //id: UDP socket index
    //Returns the port the last message came from. You should usually send the response to this port (this should work even with local area networks).
    UDPSocket *s = gmdata.FindUDPSocket(gm_cast<unsigned int>(id));
    if(s == NULL) return 0;
    return s->GetLastPort();
}

gmexport double udpsocket_get_ttl(double id) {
    ///udpsocket_get_ttl(id)
    //id: UDP socket index
    //Returns the currently set Time To Live for packets sent by this socket. This value is used to make messages expire if the travel hops are too numerous.
    
    UDPSocket *s = gmdata.FindUDPSocket(gm_cast<unsigned int>(id));
    if(s == NULL) return 0;
    return s->GetTTL();
}

gmexport double udpsocket_set_ttl(double id, double ttl) {
    ///udpsocket_set_ttl(id,ttl)
    //id: UDP socket index
    //ttl: time to live, in hops (0-255)
    //Sets the Time To Live for packets sent by this socket. This value is used to make messages expire if the travel hops are too numerous.
    //The default value is usually 32.
    
    UDPSocket *s = gmdata.FindUDPSocket(gm_cast<unsigned int>(id));
    if(s == NULL) return 0;
    s->SetTTL(gm_cast<unsigned int>(ttl));
    return 1;
}

/*
gmexport double udpsocket_get_max_message_size(double id) {
    UDPSocket *s = gmdata.FindUDPSocket(gm_cast<unsigned int>(id));
    if(s == NULL) return 0;
    return s->GetMaxMessageSize();
}
*/
