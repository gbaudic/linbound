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
	int length = 2 + (login.length() +1) + (password.length() +1) + 2;
	
	UDPpacket* packet = SDLNet_AllocPacket(length);
	Uint8* data = packet->data;
	data[0] = LOGIN_MSG;
	data[1] = 0;
	strcpy(data[2], login.c_str());
	strcpy(data[2+login.length()+1], password.c_str());
	data[length-2] = LB_PROTOCOL_VERSION;
	data[length-1] = 0;
	packet->len = length;
	
	return packet;
}

/**
 * Prepares a packet containing logout information
 * \param login login name
 */
UDPpacket* LB_packLogoutInfo(std::string login) {
	int length = 2 + (login.length() +1);
	
	UDPpacket* packet = SDLNet_AllocPacket(length);
	Uint8* data = packet->data;
	data[0] = LOGOUT_MSG;
	data[1] = 0;
	strcpy(data[2], login.c_str());
	packet->len = length;
	
	return packet;
}

/**
 * Prepare a packet containing a chat message
 * \param receiver in-game name of receiver, or "sr", "te", "ro" for specific destinations
 * \param message message to send
 */
UDPpacket* LB_packChatMessage(std::string receiver, std::string message) {
	if(message.empty())
		return NULL;
	
	int length = 2 + (message.length() + 1);
	Uint8 code = CHAT_MSG;
	
	// Handle specific destinations 
	if(receiver == "sr") code = ALL_CHAT_MSG;
	if(receiver == "te") code = TEAM_CHAT_MSG;
	if(receiver == "ro") code = ROOM_CHAT_MSG;
	
	if(code == CHAT_MSG) {
		length += receiver.length() + 1;
	}
	
	UDPpacket* packet = SDLNet_AllocPacket(length);
	Uint8* data = packet->data;
	data[0] = code;
	data[1] = 0;
	if(code == CHAT_MSG) {
		strcpy(data[2], receiver.c_str());
		strcpy(data[2+receiver.length()+1],message.c_str());
	} else {
		strcpy(data[2], message.c_str()); //Receiver not needed
	}
	packet->len = length;
	
	return packet;
}
