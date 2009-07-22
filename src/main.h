//Main.cpp header file
//Part of LinBound game
//Copyright (C) 2007-2009 G. B.
/*    This library is free software; you can redistribute it and/or
    modify it under the terms of the GNU Lesser General Public
    License as published by the Free Software Foundation; either
    version 2.1 of the License, or (at your option) any later version.

    This library is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
    Lesser General Public License for more details.

    You should have received a copy of the GNU Lesser General Public
    License along with this library; if not, write to the Free Software
    Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA */

#pragma once

#include <SDL/SDL.h>

SDL_Surface *screen;
SDL_Surface *old_screen;
SDL_Surface *image;
SDL_Surface *cursor = IMG_Load("./arrow.png");
SDL_Surface *refresh_test = IMG_Load("./arrow.png");
SDL_Surface *refresh_sample = IMG_Load("./arrow.png");
SDL_Event event;
SDL_Event LastMouseEvent;
Uint8 iMode;
Uint8 *piMode = &iMode;

class LB_Player
{
	public:
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
		Uint32 iPlayerLevelLocal;
		Uint32 iPlayerLevelGlobal;
		
		Uint16 iPlayerTotalDamage;
		Uint16 iPlayerLastDamage;
		
		Uint32 iWinningRate;
		Uint16 iAverageHit;
		
		Uint32 iHeadAvatar;
		Uint32 iBodyAvatar;
		Uint32 iGlassesAvatar;
		Uint32 iFlagAvatar;
		Uint32 iExAvatar[3];

};

class LB_Room
{
	public:
		Uint16 iRoomNumber;
		bool bRoomIsPowerUser;
		unsigned int iRoomMode;
		
		Uint8 iSuddenDeathTurns;
		Uint8 iSuddenDeathType;
		
		Uint8 iMapSide;
		char MapName[];
		
		Uint8 iMaxPlayers;
		Uint8 iCurrentPlayers;
};

struct LB_Mobile
{
	char Image[];
	char ImageW1[];
	char ImageW2[];
	char ImageWSS[];
	
};

struct LB_Jewel
{
	Uint16 iPosx;
	Uint16 iPosy;
	
	Sint8 iValue;
	char Image[];
};

struct Avatar
{
	char StaticImage[];
	char GameImage[];
	
	Sint8 iType;
	Sint8 iPopularity;
	Sint8 iDefence;
	Sint8 iAttack;
	Sint8 iBunge;
	Sint8 iHeart;
	Sint8 iBlueDelay;
	Sint8 iOrangeDelay;
	Sint8 iDelay;
	
	Uint32 iWeekPrice;
	Uint32 iMonthPrice;
	Uint32 iLimitlessPrice;
	
};
