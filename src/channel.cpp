#include <cstdlib>
#include <string>
#include <SDL/SDL.h>
#include <SDL/SDL_ttf.h>

#include "channel.hpp"

using namespace std;

LB_MessageChannel::LB_MessageChannel(TTF_Font *font, Sint16 x, Sint16 y){
	this->font = font;
	this->x = x;
	this->y = y;

	lineStep = TTF_FontHeight(font) + TTF_FontLineSkip(font);

	//Initialize the SDL_Surfaces - 8-bit depth should suffice for the colors we are using
	channelInGameSurface = SDL_CreateRGBSurface(SDL_HWSURFACE, 300, MAX_MSG_DISPLAYED*lineStep, 8, 0xc0, 0x30, 0xc, 0x3);
	fullChannelSurface = SDL_CreateRGBSurface(SDL_HWSURFACE, 300, lineStep, 8, 0xc0, 0x30, 0xc, 0x3);
}

LB_MessageChannel::~LB_MessageChannel(){
	SDL_FreeSurface(channelInGameSurface);
	SDL_FreeSurface(fullChannelSurface);
}

void LB_MessageChannel::addMessage(LB_Message msg, bool inGame)
{
    //Add the message to the data structure
	channel.push_back(msg);

    displayedMessages++;

    //Make some room for it (to display it)
    flush();

    if(!inGame){
    	//Regenerate the fullChannel to draw the last line we've just added
    }
}

void LB_MessageChannel::prepareChannelInGame()
{
	Sint16 current_y = 0;
	size_t zero(0);

    //Display only the messages that have to appear, with the appropriate logos and colors
	for(Uint8 i = max(zero, channel.size() - displayedMessages) ; i < channel.size() ; i++){
		if(channel[i].isDisplayed()){
			if(channel[i].getMessageType() <= LB_Message::PENALTY){
				//This message needs a logo, so we leave an offset in x
				channel[i].writeToChannel(channelInGameSurface, 15, current_y, true);

				//TODO: logo writing...
				//SDL_Rect r;
				//r.x = 0; r.y = current_y;
				//SDL_BlitSurface(logoSurface, NULL, channelInGameSurface, &r);
			} else {
				//Simple message, no logo
				channel[i].writeToChannel(channelInGameSurface, 0, current_y, true);
			}

			current_y += lineStep;
		}
	}
}

void LB_MessageChannel::prepareFullChannel()
{
    //Display all the messages, but in plain white
	Sint16 current_y = 0;

	for(Uint8 i = 0 ; i < channel.size() ; i++){
		if(channel[i].getMessageType() > LB_Message::PENALTY){
			channel[i].writeToChannel(fullChannelSurface, 0, current_y);
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
