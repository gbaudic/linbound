/**
 *  
 */
/* This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. 
 * If a copy of the MPL was not distributed with this file, 
 * You can obtain one at http://mozilla.org/MPL/2.0/.
 * 
 * This Source Code Form is “Incompatible With Secondary Licenses”, 
 * as defined by the Mozilla Public License, v. 2.0.
 */


#ifndef _H_MESSAGE_
#define _H_MESSAGE_

#include <string>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

enum MessageType { SERVER_MSG, BUGLE_MSG, REWARD_MSG, PENALTY_MSG, USER_MSG, POWER_USER_MSG, ADMIN_USER_MSG };

/**
 *  \struct Achievement
 *  Represents a particular event with some gold and xp to win or lose
 */
struct Achievement {
    std::string name;
    Sint16 gold; //! base value
    Sint8 xp; //! base value
    MessageType type; //! typically only REWARD or PENALTY
};

class LB_Message {
    public:

    static const Uint32 TIME_TO_LIVE = 5000; //! Maximum time to display in milliseconds

    SDL_Surface *inGameText; //Colored text
    SDL_Surface *inChannelText; //White text

    LB_Message(MessageType type, TTF_Font *f, std::string message, std::string author = "", std::string guild = "");
    ~LB_Message();

    void hideMessage();
    int updateMessageStatus();
    void exitGame();
    bool isDisplayed() const;
    int writeToChannel(SDL_Surface *channel, Sint16 x, Sint16 y, bool inGame = false);
    MessageType getMessageType() const;

    private:
    Uint32 creationTime;
    MessageType type;
    bool isDisplayedInChannel;

    std::string guild;
    std::string author;
    std::string message;
};

#endif
