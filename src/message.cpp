#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <SDL/SDL.h>
#include <SDL/SDL_ttf.h>

#include "message.hpp"
using namespace std;

LB_Message::LB_Message(LB_Message::MessageType type, std::string message, std::string author, std::string guild)
{
    this->type = type;
    this->message = message;
    this->author = author;
    this->guild = guild;
    this->isDisplayedInChannel = true;
    this->creationTime = SDL_GetTicks();

    //Do some rendering to fill the surfaces : one with colors, the other in white
}

/**
* Hides a message, even if its time has not come yet
*/
void LB_Message::hideMessage()
{
    this->isDisplayedInChannel = false;
    return;
}

void LB_Message::updateMessageStatus()
{
    if(this->isDisplayedInChannel)
    {
        if(SDL_GetTicks() > LB_Message::TIME_TO_LIVE + this->creationTime)
        {
            this->isDisplayedInChannel = false;
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
    return this->isDisplayedInChannel;
}
