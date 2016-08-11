/* This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0.
 * If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/.
 *
 * This Source Code Form is “Incompatible With Secondary Licenses”,
 * as defined by the Mozilla Public License, v. 2.0.
 */

#include "room.hpp"

void LB_Room::reset(){
	turns = 0;
	
	if(currentPlayers == maxPlayers){
		status = FULL;
	} else {
		status = WAITING;
	}
}

LB_Room::RoomMode LB_Room::getMode() const {
	return mode;
}

LB_Room::RoomStatus LB_Room::getStatus() const {
	return status;
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
	turnsLeft = DURATION;
	this->x = x;
	this->type = type;
	
	//TODO: switch to load the correct image depending on type
}

LB_Weather::~LB_Weather() {
	SDL_FreeSurface(element);
}

/**
 *  \brief Draw this weather effect on a surface
 *  \param dest the destination SDL_Surface
 *  \param xOffset position of the x=0 of the destination surface (viewport) on the original map foreground surface
 */
void LB_Weather::draw(SDL_Surface* dest, Sint16 xOffset){
	if(dest != NULL && x >= xOffset){
		SDL_Rect dstrect;
		dstrect.x = x - xOffset;
		for(int y = 0 ; y < dest->h ; y += surf->h){
			dstrect.y = y;
			SDL_BlitSurface(surf, NULL, dest, dstrect);
		}
	}
}
