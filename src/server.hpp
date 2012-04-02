/* This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. 
 * If a copy of the MPL was not distributed with this file, 
 * You can obtain one at http://mozilla.org/MPL/2.0/.
 * 
 * This Source Code Form is “Incompatible With Secondary Licenses”, 
 * as defined by the Mozilla Public License, v. 2.0.
 */

#ifndef _H_SERVER_
#define _H_SERVER_

#include <list>
#include "player.hpp"
#include "room.hpp"
#include "channel.hpp"

/**
*
*/
struct LB_BasicServerInfo
{
    LB_Player::Level minLevel;
    LB_Player::Level maxLevel;
    bool areAvatarEnabled;
    int bonusPercentage;
    int currentUsers;
    int maxUsers;

    LB_BasicServerInfo(LB_Player::Level min, LB_Player::Level max, bool areAvatarEnabled, int bonus, int users, int maxUsers);
};

/**
 * \class LB_Server
 * Represents an abstract server object from the client point of view
 */
class LB_Server
{
    public:
    static const int SERVER_PORT = 6545;
    //IP address ?

    LB_BasicServerInfo getBasicServerInfo();


    private:
    LB_Player::Level minLevel;
    LB_Player::Level maxLevel;
    bool areAvatarEnabled;
    int bonusPercentage; //0, 10, 20 or even 50 %

    int currentUsers;
    int maxUsers;

    LB_MessageChannel channels[8];
    std::list<LB_Room> rooms();

};



#endif
