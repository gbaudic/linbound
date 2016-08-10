/* This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0.
 * If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/.
 *
 * This Source Code Form is “Incompatible With Secondary Licenses”,
 * as defined by the Mozilla Public License, v. 2.0.
 */

#ifndef _H_ROOM_
#define _H_ROOM_

#include <SDL2/SDL.h>
#include "player.hpp"
#include "channel.hpp"
#include "map.hpp"

/**
 * \class LB_Room
 * Abstracts a room object with its properties
 */
class LB_Room
{
	public:
	enum RoomMode {SOLO, DUO, MULTI, POINTS};
	enum RoomStatus {WAITING, FULL, PLAYING};
	enum SuddenDeathType {BIGBOMB, DOUBLE, SS};

    RoomMode getMode() const;
    RoomStatus getStatus() const;
    bool testPassword(std::string attempt);
    LB_Room(std::string name, Uint16 roomNumber, Uint8 maxPlayers, RoomMode mode, std::string password = "");
    void changeRoomStatus(RoomStatus newStatus);
    void changeRoomMode(RoomMode newMode);

    private:
    Uint16 roomNumber;
    bool isPowerUserRoom, isPasswordProtectedRoom;
    std::string password;
    std::string name;
    RoomMode mode;
    RoomStatus status;

    Uint8 suddenDeathTurns; // 40, 56 or 72 in the original game
    SuddenDeathType sdType;

    LB_Map map;

    Uint8 maxPlayers, currentPlayers;

    LB_Player players[];

    LB_MessageChannel channel;
};

/**
 *  Summary of infos, returned by the server in the Channel view
 */
struct LB_RoomBasicInfo
{
    Uint16 iRoomNumber;
    std::string name;
    LB_Room::RoomMode mode;
    LB_Room::RoomStatus status;
    bool isPasswordProtectedRoom;

    LB_Map map;

};

/**
 *  Special weather effects appearing in-game
 *  Wind is somewhere else
 */
class LB_Weather {
	public:
	enum WeatherType {TORNADO, MIRROR, FORCE};
	
	const int DURATION = 10; //in turns
	
	LB_Weather(WeatherType type, Sint16 x);
	void draw(SDL_Surface* dest);
	bool hasExpired();
	void updateCounter(); 
	
	private:
	int TTL; //nb of turns before disappearance
	Sint16 x; //coordinate
	WeatherType type;
	SDL_Surface* element; //TODO: change to Sprite to support Tornado animation
};	

#endif
