#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <SDL/SDL.h>
#include <SDL/SDL_ttf.h>

#include "channel.hpp"

void LB_MessageChannel::addMessage(LB_Message msg)
{
    //Add the message to the data structure

    this->displayedMessages++;

    //Make some room for it (to display it)
    this->flush();
}

void LB_MessageChannel::displayChannelInRoom()
{
    //Display only the messages that have to appear, with the appropriate logos
    flush();
}

void LB_MessageChannel::displayFullChannel()
{
    //Display all the messages, but in plain white
}

void LB_MessageChannel::flush()
{
    //If there are too many messages to be displayed, hide the first ones
    if(this->displayedMessages > MAX_MSG_DISPLAYED)
    {

    }
    //If not, check if some are supposed to die
    for(int i=0 ; i < 100;i++) //Correct it once the channel has an appropriate data structure
    {
        channel[i].updateMessageStatus();
    }

}

int LB_MessageChannel::getDisplayedMessages() const
{
    return this->displayedMessages;
}
