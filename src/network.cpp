/**
 * \file network.cpp
 * \brief Network-related functions
 * \author G. B.
 * \version 0.1a
 * \date 19/08/2016
 */
/* This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. 
 * If a copy of the MPL was not distributed with this file, 
 * You can obtain one at http://mozilla.org/MPL/2.0/.
 * 
 * This Source Code Form is �Incompatible With Secondary Licenses�, 
 * as defined by the Mozilla Public License, v. 2.0.
 */

#include <libintl.h>
#include <locale.h>

#include <cstring>
#include <string>
#include <SDL2/SDL.h>
#include <SDL2/SDL_net.h>

#include "protocol.hpp"

UDPsocket serverSocket;
UDPsocket clientSocket;
extern bool isServer;

void LB_doNothing() {

}

/**
 *  Checks if the version of the server matches the version of this client (protocol.hpp/LB_PROTOCOL_VERSION)
 *  \param version the server version, as sent after discovery phase
 *  \return true if compatible, false otherwise
 */
bool LB_isServerCompatible(Uint8 version){
	return true;
}

void LB_discoverServers(){
	//Send a broadcast message, wait for replies
	
	//TODO: return a list
}

/**
 * Prepares a packet containing login information
 * \param login login name
 * \param password clear-text password
 */
UDPpacket* LB_packLoginInfo(std::string login, std::string password) {
	int length = 2 + (login.length() +1) + (password.length() +1);
	
	UDPpacket* packet = SDLNet_AllocPacket(length);
	Uint8* data = packet->data;
	data[0] = LOGIN_MSG;
	data[1] = 0;
	strcpy(data[2], login.c_str());
	strcpy(data[2+login.length()+1], password.c_str());
	
	return packet;
}
