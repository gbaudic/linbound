/* This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. 
 * If a copy of the MPL was not distributed with this file, 
 * You can obtain one at http://mozilla.org/MPL/2.0/.
 * 
 * This Source Code Form is “Incompatible With Secondary Licenses”, 
 * as defined by the Mozilla Public License, v. 2.0.
 */


#ifndef _H_CHANNEL_
#define _H_CHANNEL_

#include <vector>
#include <algorithm>
#include <SDL2/SDL_ttf.h>
#include "message.hpp"

class LB_MessageChannel
{
    public:
    static const Uint8 MAX_MSG_DISPLAYED = 7;

    LB_MessageChannel(TTF_Font *f, Sint16 x, Sint16 y);
    virtual ~LB_MessageChannel();
    void addMessage(LB_Message msg, bool inGame = true);
    void displayChannelInGame(SDL_Surface* dest);
    void displayFullChannel(SDL_Surface* dest);

    size_t cursorPos;

    private:
    std::vector<LB_Message> channel;
    size_t displayedMessages;

    Sint16 x, y; //Coordinates of the channel on world-space coordinates
    Uint16 width, height;

//    SDL_Surface* channelInGameSurface;
//    SDL_Surface* fullChannelSurface;
    TTF_Font *font;
    int lineStep;

    void flush();
    size_t getDisplayedMessages() const;
};

#endif
