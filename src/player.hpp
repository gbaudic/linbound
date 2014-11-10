#ifndef _H_PLAYER_
#define _H_PLAYER_

#include <string>
#include <SDL2/SDL.h>

#include "Sprite.hpp"

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

		Uint16 iPlayerMobile1;
		Uint16 iPlayerMobile2;

		Sint16 playerDelay;
		Uint16 playerCnxDelay;
		Sint16 playerAward;
		Sint8 playerGp;

		bool isActivePlayer;

		Uint16 x,y;

		Sint8 iCurrentAngle;
		Sint8 iLastAngle;

		Sint16 iLife;


	protected:
		Uint32 iGP;
		Uint32 iPlayerGold;
		Uint32 iPlayerCash;

		Uint16 iPlayerRankLocal;
		Uint16 iPlayerRankGlobal;
		Level playerLevelLocal;
		Level playerLevelGlobal;

		Uint16 iPlayerTotalDamage;
		Uint16 iPlayerLastDamage;

		Uint32 iWinningRate;
		Uint16 iAverageHit;

		//LB_AvatarItem items[];

};

/**
 * \class LB_PlayerShortInfo
 * Represents the smallest set of information that can be visible for a connected player
*/
struct LB_PlayerShortInfo
{
    LB_Player::Level level;
    std::string allyName;
    std::string gameID;
};

/**
 * \class LB_PlayerBasicInfo
 * A partial set of information, visible e.g. when sharing the same game room before playing
 */
struct LB_PlayerBasicInfo
{
    LB_PlayerShortInfo shortInfos;

    char teamID;
    Uint8 iPlayerPlaceAlly;
    Uint8 iTotalInAlly;

    Uint16 iPlayerMobile1;
    Uint16 iPlayerMobile2;

    bool isRoomAdmin;
    Uint8 iNextAdmin; //To know who is going to be the admin if current admin goes away

    //LB_AvatarItem items[];

};

#endif
