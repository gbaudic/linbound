#ifndef _H_CHANNEL_
#define _H_CHANNEL_

#include <vector>
#include <algorithm>
#include <SDL/SDL_ttf.h>
#include "message.hpp"

class LB_MessageChannel
{
    public:
    static const Uint8 MAX_MSG_DISPLAYED = 7;

    LB_MessageChannel(TTF_Font *f, Sint16 x, Sint16 y);
    virtual ~LB_MessageChannel();
    void addMessage(LB_Message msg, bool inGame = true);
    void prepareChannelInGame();
    void prepareFullChannel();


    private:
    std::vector<LB_Message> channel;
    size_t displayedMessages;

    Sint16 x; //Coordinates of the channel on world-space coordinates
    Sint16 y;
    Uint16 width;
    Uint16 height;

    SDL_Surface* channelInGameSurface;
    SDL_Surface* fullChannelSurface;
    TTF_Font *font;
    int lineStep;

    void flush();
    size_t getDisplayedMessages() const;
};

#endif
