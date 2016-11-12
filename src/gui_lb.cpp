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
#include <string>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL2_gfxPrimitives.h>
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

void LB_RoomButton::draw(gcn::Graphics* graphics) {
	//TODO

	gcn::Color faceColor = getBaseColor();
	gcn::Color highlightColor, shadowColor;
	int alpha = getBaseColor().a;

	if (isPressed())
	{
		faceColor = faceColor - 0x303030;
		faceColor.a = alpha;
		highlightColor = faceColor - 0x303030;
		highlightColor.a = alpha;
		shadowColor = faceColor + 0x303030;
		shadowColor.a = alpha;
	}
	else
	{
		highlightColor = faceColor + 0x303030;
		highlightColor.a = alpha;
		shadowColor = faceColor - 0x303030;
		shadowColor.a = alpha;
	}

	graphics->setColor(faceColor);
	graphics->fillRectangle(gcn::Rectangle(1, 1, getDimension().width-1, getHeight() - 1));

	graphics->setColor(highlightColor);
	graphics->drawLine(0, 0, getWidth() - 1, 0);
	graphics->drawLine(0, 1, 0, getHeight() - 1);

	graphics->setColor(shadowColor);
	graphics->drawLine(getWidth() - 1, 1, getWidth() - 1, getHeight() - 1);
	graphics->drawLine(1, getHeight() - 1, getWidth() - 1, getHeight() - 1);

	graphics->setColor(getForegroundColor());

	if(isPressed()) {
		graphics->drawImage(mImage, 0 + 1, 0 + 1);
		graphics->drawText(to_string(mRoom->getNumber()), 2 + 1, 2 + 1, gcn::Graphics::LEFT);
		graphics->drawText(mRoom->getName(), 20 + 1, 2 + 1, gcn::Graphics::LEFT);
		//Draw room image
		//Draw status image
	} else {
		graphics->drawImage(mImage, 0, 0);
		graphics->drawText(to_string(mRoom->getNumber()), 2, 2, gcn::Graphics::LEFT);
		graphics->drawText(mRoom->getName(), 20, 2, gcn::Graphics::LEFT);

		if (isFocused()) {
			graphics->drawRectangle(gcn::Rectangle(2, 2, getWidth() - 4, getHeight() - 4));
		}
	}

}

/**
 *  May be necessary for GUI interaction
 *  Returns the number for the room represented by this button on the GUI
 */
Uint16 LB_RoomButton::getNumber() {
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
