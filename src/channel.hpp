#ifndef _H_CHANNEL_
#define _H_CHANNEL_

#include "message.hpp"

class LB_MessageChannel
{
    public:
    static const int MAX_MSG_DISPLAYED = 7;

    void addMessage(LB_Message msg);
    void displayChannelInRoom();
    void displayFullChannel();


    private:
    LB_Message channel[];
    int displayedMessages;

    void flush();
    int getDisplayedMessages() const;
};

#endif
