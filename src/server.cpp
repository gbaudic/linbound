#include <cstdio>
#include <cstdlib>
#include <iostream>

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
