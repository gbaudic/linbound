/**
 *  \file protocol.hpp
 *
 *  \brief Protocol defines for the LinBound game
 *  \version 0.1a
 *  \date 30/04/2012
 *
 */

/* This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0.
 * If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/.
 *
 * This Source Code Form is “Incompatible With Secondary Licenses”,
 * as defined by the Mozilla Public License, v. 2.0.
 */

#ifndef _H_PROTOCOL_
#define _H_PROTOCOL_

/******* Message types *******/
const Uint8 ERROR = 255; //Used for special popups or real errors
const Uint8 INTERNAL = 250; //Used for login, ping measures...

const Uint8 SERVER_INFO = 200; //Basic server info
const Uint8 ROOM0_INFO = 210; //Basic room info in channel : number, title, type, map used, status
const Uint8 ROOM5_INFO = 215; //Full room info: size, settings...
const Uint8 USER0_INFO = 220; //Name, guild, level; location for buddies
const Uint8 USER5_INFO = 225; //Full statistics
const Uint8 ITEM0_INFO = 230; //The 4 or 5 items worn while playing
const Uint8 ITEM5_INFO = 235; //Full list of items used while in the "avatar shop"
const Uint8 MOBILE_INFO = 240; //Choice of mobile(s) for the battle

const Uint8 CHAT_MSG = 100; //Chat message (add the message type to this value to get the final packet type)

const Uint8 WEATHER_MSG = 110; //Wind change, hurricane, thunder, mirror, force
const Uint8 SHOT_MSG = 120; //Shot coordinates: angle, strength, weapon or item used
const Uint8 DMG_MSG = 125; //Result of a shot: impact on players, on the map...
const Uint8 ITEMS_MSG = 135; //Item choice when playing (for server consistency checks)
const Uint8 COORDS_MSG = 130; //Coordinates (for players landing, at the beginning or when respawning)
const Uint8 RESULTS_MSG = 150; //Results of the battle : wins/loses, rewards

const Uint8 LB_PROTOCOL_VERSION = 1; //Used to denote incompatibilities between versions

/******* Special senders/recipients *******/
const char* CHANNEL = "ch";
const char* SERVER = "sr";
const char* CLIENT = "cl";
const char* TEAM = "te";
const char* ROOM = "ro";

struct LB_Packet {
	const char* sender;
	const char* recipient;
	Uint8 type;
	const char* content;
};


#endif /* _H_PROTOCOL_ */
