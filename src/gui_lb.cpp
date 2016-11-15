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
extern TTF_Font* font;
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
 *  Create a balloon to display a chat message in a more pleasant way
 *  \param text a string to represent the text to display, only the first 100 characters are used
 */
LB_MessageBalloon::LB_MessageBalloon(std::string text, Uint16 x, Uint16 y) {
	this->x = x;
	this->y = y;
	
	//Compute line size
	int w, h;
	TTF_SizeText(font, "m", &w, &h); 
	
	//Compute actual width and height
	if(text.length() > 20) {
		width = 20*w + 2*BALLOON_RADIUS;
	} else {
		width = text.length()*w + 2*BALLOON_RADIUS;
	}
	Uint8 lines = text.length() / 20 + 1;
	height = lines > 5 ? 5 : lines;
	height *= h;
	height += 2*BALLOON_RADIUS;
	
	//Slice and render text
	for(int i = 1 ; i <= lines ; i++) {
		textLines.push_back(TTF_RenderText_Solid(font, text.substr(20*(lines -1), 20).c_str(), black));
	}
}

LB_MessageBalloon::~LB_MessageBalloon() {
	for(SDL_Surface* s : textLines) {
		SDL_FreeSurface(s);
	}
	for(SDL_Texture* t : textTextures) {
		SDL_DestroyTexture(t);
	}
}

/**
 *  Draw a chat message as a balloon above a given player
 *  \param target the renderer to draw to
 *  \param x position of the player talking, balloon will be drawn above
 *  \param y position of the player talking, balloon will be drawn above
 */
void LB_MessageBalloon::draw(SDL_Renderer *target, Uint16 x, Uint16 y) {	
	// 30 and 20 are respectively the height and width of the balloon tip
	//Draw balloon
	roundedBoxRGBA(target, x - width / 2, y - height - 30 + 1, x + width / 2, y - 30, BALLOON_RADIUS, 0xff, 0xff, 0xff, 0);
	roundedRectangleRGBA(target, x - width / 2, y - height - 30 + 1, x + width / 2, y - 30, BALLOON_RADIUS, 0, 0, 0, 0);
	//Add text
	SDL_Rect dstRect;
	dstRect.x = x - width / 2 + BALLOON_RADIUS;
	dstRect.y = y - height - 30 + BALLOON_RADIUS;
	for(int i = 1 ; i <= lines ; i++) {
		if(textTextures.size() < lines) {
			//Create textures from surfaces if necessary
			textTextures.push_back(SDL_CreateTextureFromSurface(target, textLines[i-1]));
		}
		dstRect.h = textTextures[i-1]->h;
		dstRect.w = textTextures[i-1]->w; 
		SDL_RenderCopy(target, textTextures[i-1], NULL, &dstRect);
		dstRect.y += textTextures[i-1]->h;
	}
	//Add tip at the bottom
	filledTrigonRGBA(target, x, y, x, y - 30, x + 20, y - 30, 0xff, 0xff, 0xff, 0);
	
}
