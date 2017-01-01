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

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <string>
#include <cstdlib>

#include "player.hpp"
#include "sound.hpp"
#include "channel.hpp"
#include "map.hpp"
#include "room.hpp"
using namespace std;

/**
 *  Reset some attributes once a game is finished
 */
void LB_Room::reset(){
	turnsPlayed = 0;
	
	if(currentPlayers == maxPlayers){
		status = ROOM_FULL;
	} else {
		status = ROOM_WAITING;
	}
	
	//weather
}

RoomMode LB_Room::getMode() const {
	return mode;
}

RoomStatus LB_Room::getStatus() const {
	return status;
}

Uint16 LB_Room::getNumber() const {
	return roomNumber;
}

std::string LB_Room::getName() const {
	return name;
}

Uint8 LB_Room::getPlayers() const {
	return currentPlayers;
}

bool LB_Room::testPassword(std::string attempt) {
	if(isPasswordProtectedRoom) {
		return attempt == password;
	} else {
		return true; 
	} 
	//TODO: should ask the server instead
}

void LB_Room::changeRoomStatus(RoomStatus newStatus) {
	status = newStatus;
}

void LB_Room::changeRoomMode(RoomMode newMode) {
	mode = newMode;
}

void LB_Room::changeSuddenDeath(SuddenDeathType type, Uint8 turns) {
	sdType = type;
	suddenDeathTurns = turns;
}

void LB_Room::changeWind(LB_WindData newWind) {
	wind.power = newWind.power;
	wind.direction = newWind.direction;
	
	//TODO: play a sound effect to warn player
}

void LB_Room::addPlayer(LB_Player* player) {
	if(status == ROOM_WAITING && currentPlayers < maxPlayers) {
		players[currentPlayers] = player;
		currentPlayers++;
	} else {
		//message: cannot enter
	}
}

LB_RoomBasicInfo LB_Room::getInfo() {
	LB_RoomBasicInfo info;
	info.roomNumber = roomNumber;
	info.name = name;
	info.mode = mode;
	info.status = status;
	info.isPasswordProtectedRoom = isPasswordProtectedRoom;
	info.mapName = map->getName(); //simplify, use only the name?
	
	return info;
}

bool LB_Weather::hasExpired() const {
	return turnsLeft <= 0;
}

void LB_Weather::updateCounter() {
	turnsLeft--;
}

/**
 *  \param type the weather event type
 *  \param x left coordinate of this weather evenet, expressed in map foreground coordinates. Y is not necessary because these events take the whole height. 
 */
LB_Weather::LB_Weather(WeatherType type, Sint16 x) {
	turnsLeft = DURATION + 5; //we announce it 5 turns before appearance
	this->x = x;
	this->type = type;
	
	//TODO: support of sprite for tornado
	switch(type){
		case TORNADO:
			element = IMG_Load("./res/tornado.png");
			break;
		case MIRROR:
			element = IMG_Load("./res/mirror.png");
			break;
		case FORCE:
			element = IMG_Load("./res/force.png");
			break;
	}
}

LB_Weather::~LB_Weather() {
	SDL_FreeSurface(element);
}

/**
 *  \brief Draw this weather effect on a surface
 *  \param dest the destination SDL_Surface
 *  \param xOffset position of the x=0 of the destination surface (viewport) on the original map foreground surface
 */
void LB_Weather::draw(SDL_Surface* dest, Sint16 xOffset) {
	if(dest != NULL && element != NULL && x >= xOffset && !hasExpired()){
		if(turnsLeft <= DURATION){
			//draw the weather phenomenon
			SDL_Rect dstrect;
			dstrect.x = x - xOffset;
			for(int y = 0 ; y < dest->h ; y += element->h){
				dstrect.y = y;
				SDL_BlitSurface(element, NULL, dest, &dstrect);
			}
		} else {
			//draw a small marker to warn players
		}
	}
}

/**
 * Generate a new WindData struct
 * Should be called only on the server side
 */
LB_WindData generateWind() {
	LB_WindData result;
	
	result.power = rand() % 25;
	result.direction = rand() % 360; 
	
	return result;
}

/**
 * Generate a new weather effect 
 * \param mapWidth
 */
LB_Weather generateWeather(Sint16 mapWidth) {
    Sint16 position = rand() % mapWidth;
    int type = rand() % 3; //Magic number = nb of values in WeatherType
    
    return LB_Weather((WeatherType)type, position);
}

std::string LB_GameItem::getName() const {
	return name;
}

std::string LB_GameItem::getDescription() const {
	return description;
}

Uint8 LB_GameItem::getSize() const {
	return size;
}

Uint16 LB_GameItem::getDelay() const {
	return delay;
}

bool LB_GameItem::isEnabled() const {
	return enabled;
}
	
void LB_GameItem::enable(bool newState){
	enabled = newState;
}
