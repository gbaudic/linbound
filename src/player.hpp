/**
 *  \file player.hpp
 *  \brief Class definitions for players
 *  \author G. B.
 */
/* This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. 
 * If a copy of the MPL was not distributed with this file, 
 * You can obtain one at http://mozilla.org/MPL/2.0/.
 * 
 * This Source Code Form is “Incompatible With Secondary Licenses”, 
 * as defined by the Mozilla Public License, v. 2.0.
 */

#ifndef _H_PLAYER_
#define _H_PLAYER_

#include <string>
#include <SDL2/SDL.h>

#include "Sprite.hpp"
#include "message.hpp" //for Achievement

enum Weapon {WEAPON_SHOT1 = 1, WEAPON_SHOT2 = 2, WEAPON_SUPER_SHOT = 55};
enum Mobile {TEAPOT, COFFEE_CUP, TREE, ORANGE, ROSE, CABBAGE, RASPBERRY,
				DIAMOND, ROCK, TANK, ICEBERG, PLANE, TRASH_CAN, RESISTOR, 
				SHEEP, GOAT, PIG, COW, UNICORN, DOLPHIN, DUCK};

/**
 * \class LB_Player
 * Abstracts a LB player
 */
class LB_Player
{
	public:

        enum Level {Chick, WoodHammer, DoubleWoodHammer, StoneAxe, DoubleStoneAxe,
        MetalAxe, DoubleMetalAxe, SilverAxe, DoubleSilverAxe, GoldAxe, DoubleGoldAxe,
        MetalDoubleSidedAxe, MetalDoubleSidedAxePlus, SilverDoubleSidedAxe, SilverDoubleSidedAxePlus,
        GoldDoubleSidedAxe, GoldDoubleSidedAxePlus, BronzeStar, SilverStar, GoldStar, DoubleStars,
        TripleStars, VioletHole, SapphireHole, RedRubyHole, DiamondHole, BlueDragon, RedDragon, SilverDragon,
        BlueKnight, RedKnight, SilverKnight, BluePhoenix, RedPhoenix, SilverPhoenix,
        BronzeMedal, SilverMedal, GoldMedal, BronzeCrown, SilverCrown, GoldCrown, VIP,
        BronzeTrophy, SilverTrophy, GoldTrophy, Administrator};


		std::string allianceName;
		char teamID;
		Uint8 rankInAlliance, sizeOfAlliance;

		Uint16 playerMobile1;
		Uint16 playerMobile2;

		Sint16 playerDelay;
		Uint16 playerCnxDelay;
		Sint16 playerAward;
		Sint8 playerGp;

		bool isActivePlayer;

		Uint16 x,y;

		Sint16 currentAngle;
		Sint16 lastAngle;

		Sint16 life; //any value between 0 and 1500 is OK, >1500 is cheating, <0 is dead
		
		Achievement getPersonalizedValue(Achievement base, bool avatarOn); //compute values considering items worn

	protected:
		Uint32 xp;
		Uint32 playerGold;
		Uint32 playerCash;

		Uint16 playerRankLocal;
		Uint16 playerRankGlobal;
		Level playerLevelLocal;
		Level playerLevelGlobal;

		Uint16 playerTotalDamage;
		Uint16 playerLastDamage;

		Uint32 winningRate;
		Uint16 averageHit;

		//LB_AvatarItem items[];

};

/**
 * \class LB_PlayerShortInfo
 * Represents the smallest set of information that can be visible for a connected player
*/
struct LB_PlayerShortInfo {
    LB_Player::Level level;
    std::string allyName;
    std::string gameID;
};

/**
 * \class LB_PlayerBasicInfo
 * A partial set of information, visible e.g. when sharing the same game room before playing
 */
struct LB_PlayerBasicInfo {
    LB_PlayerShortInfo shortInfos;

    char teamID;
    Uint8 playerPlaceAlly;
    Uint8 totalInAlly;

    Uint16 playerMobile1;
    Uint16 playerMobile2;

    bool isRoomAdmin;
    Uint8 nextAdmin; //To know who is going to be the admin if current admin goes away

    //LB_AvatarItem items[];

};

#endif
