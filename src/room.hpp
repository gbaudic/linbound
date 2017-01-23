/**
 * \file room.cpp
 * \brief Description for Room objects and associated structs
 * \author G. B.
 * \version 0.1a
 * \date 2016
 */
/* This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0.
 * If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/.
 *
 * This Source Code Form is “Incompatible With Secondary Licenses”,
 * as defined by the Mozilla Public License, v. 2.0.
 */

#ifndef _H_ROOM_
#define _H_ROOM_

#include "channel.hpp"
#include "map.hpp"
#include "player.hpp"

enum class RoomMode {SOLO, DUO, MULTI, POINTS};
enum class RoomStatus {ROOM_WAITING, ROOM_FULL, ROOM_PLAYING};
enum class SuddenDeathType {BIGBOMB, DOUBLE, DOUBLEPLUS, SS};
enum class PlayerStatus {IDLE, READY, LOADING, OK}; //used when waiting/pre-game
enum class MobileStatus {WAITING, FALLING, FLYING, SHOOTING, DEAD, DYING}; //used in-game
enum WeatherType {TORNADO, MIRROR, FORCE}; //no enum class since I need int correspondence

const int MAX_PLAYERS = 8;

std::string to_string(SuddenDeathType s);

/**
 *  Summary of infos, returned by the server in the Channel view
 */
struct LB_RoomBasicInfo
{
    Uint16 roomNumber;
    std::string name;
    RoomMode mode;
    RoomStatus status;
    bool isPasswordProtectedRoom;

    std::string mapName;

};

struct LB_WindData {
	Uint8 power; /*!< between 0 and 24*/
	int direction; /*!< angle in degrees, trigonometric: 0=east/right, 90=north/up...*/
};

LB_WindData generateWind();

/**
 *  Special weather effects appearing in-game
 *  Wind is somewhere else
 */
class LB_Weather {
	public:

	static const int DURATION = 10; //in turns

	LB_Weather(WeatherType type, Sint16 x);
	~LB_Weather();
	void draw(SDL_Surface* dest, Sint16 xOffset);
	bool hasExpired() const;
	void updateCounter();

	private:
	int turnsLeft; //nb of turns before disappearance
	Sint16 x; //coordinate, using map foreground as reference
	WeatherType type;
	SDL_Surface* element; //TODO: change to Sprite to support Tornado animation
};

LB_Weather generateWeather(Sint16 mapWidth);

/**
 * \class LB_Room
 * Abstracts a room object with its properties
 */
class LB_Room
{
	public:

    RoomMode getMode() const;
    RoomStatus getStatus() const;
    Uint16 getNumber() const;
    std::string getName() const;
	Uint8 getPlayers() const;
    bool testPassword(std::string attempt);
    LB_Room(std::string name, Uint16 roomNumber, Uint8 maxPlayers, RoomMode mode, std::string password = "");
    void changeRoomStatus(RoomStatus newStatus);
    void changeRoomMode(RoomMode newMode);
	void changeMap(LB_Map* newMap);
	void changeSuddenDeath(SuddenDeathType type, Uint8 turns);
	void changeWind(LB_WindData newWind);
	void changeName(std::string newName);
	void addPlayer(LB_Player* player); //parameter to be decided
	void removePlayer(LB_Player* player); //same as above
	//LB_Player[] getPlayersFromTeam(char team);
	void triggerSuddenDeath();
	LB_RoomBasicInfo getInfo();
	void reset(); //reset after a finished game

    private:
    Uint16 roomNumber;
    bool isPowerUserRoom, isPasswordProtectedRoom;
    std::string password;
    std::string name;
    RoomMode mode;
    RoomStatus status;

    Uint8 suddenDeathTurns; // 40, 56 or 72 in the original game
    SuddenDeathType sdType;
	bool isSDActive; //flag: some actions may be possible in SD mode only
	Uint16 turnsPlayed; 
	LB_WindData wind;

    LB_Map* map;

    Uint8 maxPlayers, currentPlayers;

    LB_Player* players[MAX_PLAYERS]; //TODO: use a list instead, append so that 0 is always admin
	LB_Weather weather[10];

    LB_MessageChannel* channel;
};

class LB_GameItem {
	public:	
	virtual void use();
	std::string getName() const;
	std::string getDescription() const;
	Uint8 getSize() const;
	Uint16 getDelay() const;
	bool isEnabled() const;
	void enable(bool newState);
	
	private:
	Uint8 size; //1 or 2 slots out of 6
	SDL_Surface* surf; //for GUI button
	std::string name;
	std::string description;
	Uint16 delay;
	bool enabled; //admin can disable items
};

#endif
