#ifndef _H_PLAYER_
#define _H_PLAYER_

#include <SDL/SDL.h>

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


		char AllyID[13];
		char TeamID[1];
		Uint8 iPlayerPlaceAlly;
		Uint8 iTotalInAlly;

		Uint16 iPlayerMobile1;
		Uint16 iPlayerMobile2;

		Sint16 iPlayerDelay;
		Uint16 iPlayerCnxDelay;
		Sint16 iPlayerAward;
		Sint8 iPlayerGp;

		bool bIsActivePlayer;

		Uint16 iPosx;
		Uint16 iPosy;

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

#endif
