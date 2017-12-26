/* This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. 
 * If a copy of the MPL was not distributed with this file, 
 * You can obtain one at http://mozilla.org/MPL/2.0/.
 * 
 * This Source Code Form is “Incompatible With Secondary Licenses”, 
 * as defined by the Mozilla Public License, v. 2.0.
 */


#include "message.hpp"
using namespace std;

/**
 * @brief Constructor
 */
LB_Message::LB_Message(MessageType type, TTF_Font *font, string message, string author, string guild)
{
    _type = type;
    _message = message;
    _author = author;
    _guild = guild;
    _isDisplayedInChannel = true;
    _creationTime = SDL_GetTicks();

    //Do some rendering to fill the surfaces : one with colors, the other in white
    SDL_Color col;
    col.r = 0xff; col.g = 0xff; col.b = 0xff;
    string fullMsg = _author + "]" + _message;
    if(type >= USER_MSG){
    	inChannelText = TTF_RenderUTF8_Solid(font, fullMsg.c_str(), col);
    }

    switch(_type){
    //TODO: - check color availability on channel 8-bit surface
    case SERVER_MSG:
    	col.b = 0; //yellow
    	inGameText = TTF_RenderUTF8_Solid(font, message.c_str(), col);
    	break;
    case BUGLE_MSG:
    	col.r = 0; col.g = 0x80; col.b = 0; //green
    	fullMsg = guild + " " + author + "]" + message;
    	inGameText = TTF_RenderUTF8_Solid(font, fullMsg.c_str(), col);
    	break;
    case USER_MSG:
    	fullMsg = guild + " " + author + "]" + message;
    	inGameText = TTF_RenderUTF8_Solid(font, fullMsg.c_str(), col); //white
    	break;
    case POWER_USER_MSG:
    	col.r = 0xff; col.g = 0xc0; col.b = 0xff;//light magenta
    	fullMsg = guild + " " + author + "]" + message;
    	inGameText = TTF_RenderUTF8_Solid(font, fullMsg.c_str(), col);
    	break;
    case ADMIN_USER_MSG:
    	col.r = 0xff; col.g = 0x80; col.b = 0; //orange
    	inGameText = TTF_RenderUTF8_Solid(font, fullMsg.c_str(), col);
    	break;
    case REWARD_MSG:
    	col.r = 0; col.g = 0xff; col.b = 0xff; //light blue
    	inGameText = TTF_RenderUTF8_Solid(font, fullMsg.c_str(), col);
    	break;
    case PENALTY_MSG:
    	col.r = 0xff; col.g = 0; col.b = 0; //red
    	inGameText = TTF_RenderUTF8_Solid(font, fullMsg.c_str(), col);
    	break;
    default:
    	inGameText = TTF_RenderUTF8_Solid(font, fullMsg.c_str(), col);
    	break;
    }
}

LB_Message::~LB_Message() {
	if(inGameText != NULL){
		SDL_FreeSurface(inGameText);
	}

	if(_type >= USER_MSG){
		SDL_FreeSurface(inChannelText);
	}
}

/**
* Hides a message, even if its time has not come yet
*/
void LB_Message::hideMessage() {
    _isDisplayedInChannel = false;
}

/**
 * Hides a message, but checks if its time has come first
 */
void LB_Message::updateMessageStatus() {
    if(_isDisplayedInChannel && SDL_GetTicks() > LB_Message::TIME_TO_LIVE + _creationTime) {
        _isDisplayedInChannel = false;
    }
}

void LB_Message::exitGame() {
    SDL_FreeSurface(inGameText);
}

bool LB_Message::isDisplayed() const {
    return _isDisplayedInChannel;
}

MessageType LB_Message::getMessageType() const {
	return _type;
}

/**
 * Blits a message text into the channel
 * \param channel the destination SDL_Surface pointer
 * \param x x coordinate on the destination surface
 * \param y y coordinate on the destination surface
 * \param inGame if true, use the colored in-game version. The plain white one is used if false. 
 */
int LB_Message::writeToChannel(SDL_Surface *channel, Sint16 x, Sint16 y, bool inGame){
	SDL_Rect r;
	r.x = x ; r.y = y;

	if(_type >= USER_MSG && !inGame){
		SDL_BlitSurface(inChannelText, NULL, channel, &r);
		return 1;
	}

	if(inGame){
		SDL_BlitSurface(inGameText, NULL, channel, &r);
		return 1;
	}

	return 0;
}
