/**
 * \file gui_lb.cpp
 * \brief GUI additions to guisan, specific to LinBound
 * \author G. B.
 * \version 0.1a
 * \date 24/10/2010
 */
/* This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. 
 * If a copy of the MPL was not distributed with this file, 
 * You can obtain one at http://mozilla.org/MPL/2.0/.
 * 
 * This Source Code Form is “Incompatible With Secondary Licenses”, 
 * as defined by the Mozilla Public License, v. 2.0.
 */


#include <libintl.h>
#include <locale.h>

#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_gfxPrimitives.h>
#include "gui_lb.hpp"
using namespace std;

extern int iscreenw, iscreenh;
SDL_Color black, white; /* Needs to be set somewhere */

/**
 * A GUI button representing a room in server view
 */
LB_RoomButton::LB_RoomButton(LB_Room* room) : gcn::ImageButton("./res/room_button.png") {
	mRoom = room;
}

LB_RoomButton::~LB_RoomButton() {

}

void LB_RoomButton::draw() {
	//TODO
	//Draw background
	//Draw texts
	//Draw room image
	//Draw status image
}

/**
 *  May be necessary for GUI interaction
 *  Returns the number for the room represented by this button on the GUI
 */
Uint16 LB_RoomButton::getRoomNumber() {
	LB_RoomBasicInfo roomInfo = mRoom->getInfo();
	return roomInfo.roomNumber; 
}

/**
 *  Draw a chat message as a balloon above a given player
 *  \param message the message to display
 *  \param x x coordinate of the player speaking, balloon will be located above him/her
 *  \param y y coordinate of the player
 *  \param target the renderer to draw to
 */
void drawMessageBalloon(SDL_Surface* message, Uint16 x, Uint16 y, SDL_Renderer *target) {
	//Measure text to get total width and length
	//Draw 4 circles for corners
	//Draw 4 rectangles for edges and central rectangle
	//Draw 4 lines to complete
	//Add text
	//Add tip at the bottom
	
}
