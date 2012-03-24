#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <SDL/SDL.h>
#include <SDL/SDL_ttf.h>

#include "message.hpp"
using namespace std;

extern TTF_Font *font;

LB_Message::LB_Message(LB_Message::MessageType type, std::string message, std::string author, std::string guild)
{
    this->type = type;
    this->message = message;
    this->author = author;
    this->guild = guild;
    this->isDisplayedInChannel = true;
    this->creationTime = SDL_GetTicks();

    //Do some rendering to fill the surfaces : one with colors, the other in white
    SDL_Color col;
    col.r = 0xff; col.g = 0xff; col.b = 0xff;
    inChannelText = TTF_RenderUTF8_Solid(font, toChar(author + "]" + message), col);

    switch(type){
    //TODO: to be filled up in the future with different colors
    case SERVER:

    	break;
    case BUGLE:

    	break;

    case USER:

    	break;
    case POWER_USER:

    	break;
    case ADMIN_USER:

    	break;
    case REWARD:

    	break;
    case PENALTY:

    	break;
    default:
    	inGameText = TTF_RenderUTF8_Solid(font, toChar(author + "]" + message), col); //Does not work
    	break;
    }
}

LB_Message::~LB_Message(){
	if(inGameText != NULL){
		SDL_FreeSurface(inGameText);
	}

	SDL_FreeSurface(inChannelText);
}

/**
* Hides a message, even if its time has not come yet
*/
void LB_Message::hideMessage()
{
    isDisplayedInChannel = false;
    return;
}

void LB_Message::updateMessageStatus()
{
    if(isDisplayedInChannel)
    {
        if(SDL_GetTicks() > LB_Message::TIME_TO_LIVE + creationTime)
        {
            isDisplayedInChannel = false;
        }
    }
    return;
}

void LB_Message::exitGame()
{
    SDL_FreeSurface(inGameText);
}

bool LB_Message::isDisplayed() const
{
    return isDisplayedInChannel;
}

/**
 * Converts a C++ string to a C-style 'string'
 * @param src the string to convert
 * @return a pointer to a char array
 * TODO: this function needs fixing...
 */
char* LB_Message::toChar(string src){
	char st[src.length() + 1];

	for(int i = 0 ; i < src.length() ; i++){
		st[i] = src[i];
	}
	st[src.length()] = '\0';

	return st;
}

void LB_Message::writeToChannel(SDL_Surface *channel, int x, int y){
	SDL_Rect r;
	r.x = x ; r.y = y;

	SDL_BlitSurface(inChannelText, NULL, channel, &r);
}
