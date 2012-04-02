/* This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. 
 * If a copy of the MPL was not distributed with this file, 
 * You can obtain one at http://mozilla.org/MPL/2.0/.
 * 
 * This Source Code Form is “Incompatible With Secondary Licenses”, 
 * as defined by the Mozilla Public License, v. 2.0.
 */


#include "server.hpp"

LB_BasicServerInfo::LB_BasicServerInfo(LB_Player::Level min, LB_Player::Level max, bool areAvatarEnabled, int bonus, int users, int maxUsers)
{
    if(min < max)
    {
        this->minLevel = min;
        this->maxLevel = max;
        this->areAvatarEnabled = areAvatarEnabled;

        if(bonus == 0 || bonus == 10 || bonus == 20 || bonus == 50)
        {
            this->bonusPercentage = bonus;
        } else {
            this->bonusPercentage = 0;
        }

        this->currentUsers = users;
        this->maxUsers = maxUsers;
    }
}
