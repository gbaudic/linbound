/* This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. 
 * If a copy of the MPL was not distributed with this file, 
 * You can obtain one at http://mozilla.org/MPL/2.0/.
 * 
 * This Source Code Form is “Incompatible With Secondary Licenses”, 
 * as defined by the Mozilla Public License, v. 2.0.
 */


#include <cstdlib>
#include <string>
#include <SDL2/SDL.h>

#include "channel.hpp"

using namespace std;

LB_MessageChannel::LB_MessageChannel(TTF_Font *font, Sint16 x, Sint16 y){
	this->font = font;
	this->x = x;
	this->y = y;

	lineStep = TTF_FontHeight(font) + TTF_FontLineSkip(font);

	//Initialize the SDL_Surfaces - 8-bit depth should suffice for the colors we are using
	//channelInGameSurface = SDL_CreateRGBSurface(SDL_HWSURFACE, 300, MAX_MSG_DISPLAYED*lineStep, 8, 0xc0, 0x30, 0xc, 0x3);
	//fullChannelSurface = SDL_CreateRGBSurface(SDL_HWSURFACE, 300, lineStep, 8, 0xc0, 0x30, 0xc, 0x3);
	cursorPos = 0;
}

LB_MessageChannel::~LB_MessageChannel(){
	//SDL_FreeSurface(channelInGameSurface);
	//SDL_FreeSurface(fullChannelSurface);
}

/**
 * Appends a new message to the channel
 * @param msg the LB_Message to add
 * @param inGame ???
 */
void LB_MessageChannel::addMessage(LB_Message msg, bool inGame)
{
    //Add the message to the data structure
	channel.push_back(msg);

    displayedMessages++;

    //Make some room for it (to display it)
    flush();
}

/**
 * @param dest the SDL_Surface on which to print the channel
 */
void LB_MessageChannel::displayChannelInGame(SDL_Surface* dest)
{
	Sint16 current_y = 0;
	size_t zero(0);

    //Display only the messages that have to appear, with the appropriate logos and colors
	for(Uint8 i = max(zero, channel.size() - displayedMessages) ; i < channel.size() ; i++){
		if(channel[i].isDisplayed()){
			if(channel[i].getMessageType() <= LB_Message::PENALTY){
				//This message needs a logo, so we leave an offset in x
				channel[i].writeToChannel(dest, x + 15, y + current_y, true);

				//TODO: logo writing...
				//SDL_Rect r;
				//r.x = x; r.y = y + current_y;
				//SDL_BlitSurface(logoSurface, NULL, dest, &r);
			} else {
				//Simple message, no logo
				channel[i].writeToChannel(dest, x, y + current_y, true);
			}

			current_y += lineStep;
		}
	}
}

void LB_MessageChannel::displayFullChannel(SDL_Surface* dest)
{
    //Display all the messages, but in plain white
	Sint16 current_y = 0;

	for(size_t i = cursorPos ; i < min(channel.size(), cursorPos + MAX_MSG_DISPLAYED) ; i++){
		if(channel[i].getMessageType() > LB_Message::PENALTY){
			channel[i].writeToChannel(dest, x, y + current_y);
		}

		current_y += lineStep;
	}
}

void LB_MessageChannel::flush()
{
    //If there are too many messages to be displayed, hide the first one
	size_t zero(0);

    if(displayedMessages > MAX_MSG_DISPLAYED)
    {
    	channel[channel.size() - MAX_MSG_DISPLAYED - 1].hideMessage();
    	displayedMessages--;
    } else {
    	//If not, check if some are supposed to die and update the counter accordingly
    	for(Uint8 i= max(zero, channel.size() - MAX_MSG_DISPLAYED) ; i < channel.size() ; i++)
    	{
    		displayedMessages -= channel[i].updateMessageStatus();
    	}
    }
}

size_t LB_MessageChannel::getDisplayedMessages() const
{
    return this->displayedMessages;
}
