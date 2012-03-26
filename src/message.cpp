#include <cstdlib>
#include <string>

#include "message.hpp"
using namespace std;

LB_Message::LB_Message(LB_Message::MessageType type, TTF_Font *font, std::string message, std::string author, std::string guild)
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
    string fullMsg = author + "]" + message;
    if(type >= USER){
    	inChannelText = TTF_RenderUTF8_Solid(font, fullMsg.c_str(), col);
    }

    switch(type){
    //TODO: - complete POWER_USER
    case SERVER:
    	col.b = 0; //yellow
    	inGameText = TTF_RenderUTF8_Solid(font, message.c_str(), col);
    	break;
    case BUGLE:
    	col.r = 0; col.g = 0x80; col.b = 0; //green
    	fullMsg = guild + " " + author + "]" + message;
    	inGameText = TTF_RenderUTF8_Solid(font, fullMsg.c_str(), col);
    	break;
    case USER:
    	fullMsg = guild + " " + author + "]" + message;
    	inGameText = TTF_RenderUTF8_Solid(font, fullMsg.c_str(), col); //white
    	break;
    case POWER_USER:
    	//not decided yet
    	break;
    case ADMIN_USER:
    	col.r = 0xff; col.g = 0x80; col.b = 0; //orange
    	inGameText = TTF_RenderUTF8_Solid(font, fullMsg.c_str(), col);
    	break;
    case REWARD:
    	col.r = 0; col.g = 0x66; col.b = 0xff; //light blue
    	inGameText = TTF_RenderUTF8_Solid(font, fullMsg.c_str(), col);
    	break;
    case PENALTY:
    	col.r = 0xff; col.g = 0; col.b = 0; //red
    	inGameText = TTF_RenderUTF8_Solid(font, fullMsg.c_str(), col);
    	break;
    default:
    	inGameText = TTF_RenderUTF8_Solid(font, fullMsg.c_str(), col);
    	break;
    }
}

LB_Message::~LB_Message(){
	if(inGameText != NULL){
		SDL_FreeSurface(inGameText);
	}

	if(type >= USER){
		SDL_FreeSurface(inChannelText);
	}
}

/**
* Hides a message, even if its time has not come yet
*/
void LB_Message::hideMessage()
{
    isDisplayedInChannel = false;
    return;
}

int LB_Message::updateMessageStatus()
{
    if(isDisplayedInChannel)
    {
        if(SDL_GetTicks() > LB_Message::TIME_TO_LIVE + creationTime)
        {
            isDisplayedInChannel = false;
            return 1;
        }
    }
    return 0;
}

void LB_Message::exitGame()
{
    SDL_FreeSurface(inGameText);
}

bool LB_Message::isDisplayed() const
{
    return isDisplayedInChannel;
}

LB_Message::MessageType LB_Message::getMessageType() const
{
	return type;
}

int LB_Message::writeToChannel(SDL_Surface *channel, Sint16 x, Sint16 y, bool inGame){
	SDL_Rect r;
	r.x = x ; r.y = y;

	if(type >= USER && !inGame){
		SDL_BlitSurface(inChannelText, NULL, channel, &r);
		return 1;
	}

	if(inGame){
		SDL_BlitSurface(inGameText, NULL, channel, &r);
		return 1;
	}

	return 0;
}
