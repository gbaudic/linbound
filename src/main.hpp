/**
 * \file main.hpp
 * \brief Main.cpp header file
 *
 * It also defines several classes which should DEFINITELY be moved somewhere else (and also rewritten)
 *
 * \author G. B.
 * \version 0.1a
 * \date 24/10/2010
 */
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

#ifndef _H_MAIN_
#define _H_MAIN_

#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <GL/gl.h>
#include <GL/glx.h>

#include "player.hpp"

SDL_Surface *screen;
SDL_Surface *old_screen;
SDL_Surface *image;
SDL_Surface *cursor = IMG_Load("/home/podgy/workspace/Linbound/res/arrow.png");
SDL_Surface *refresh_test = IMG_Load("/home/podgy/workspace/Linbound/res/arrow.png");
SDL_Surface *refresh_sample = IMG_Load("/home/podgy/workspace/Linbound/res/arrow.png");
SDL_Event event;
SDL_Event LastMouseEvent;
Uint8 iMode;
//Uint8 *piMode = &iMode;



/**
 * \class LB_Room
 * Abstracts a room object with its properties
 */
class LB_Room
{
	public:
	enum RoomMode {SOLO, SCORE, TAG, JEWEL};
	enum RoomStatus {WAITING, FULL, PLAYING};

		Uint16 iRoomNumber;
		bool bRoomIsPowerUser;
		bool bIsPasswordProtected;
		std::string password;
		RoomMode mode;
		RoomStatus status;

		Uint8 iSuddenDeathTurns;
		Uint8 iSuddenDeathType;

		Uint8 iMapSide;
		char MapName[];

		Uint8 iMaxPlayers;
		Uint8 iCurrentPlayers;

		LB_Player players[];
};

/**
 * \class LB_Mobile
 * Abstracts a LinBound game mobile
 */
struct LB_Mobile
{
	char Image[];
	char ImageW1[];
	char ImageW2[];
	char ImageWSS[];

};

/**
 * \class LB_Jewel
 * Abstracts a jewel object used in Jewel game mode
 */
struct LB_Jewel
{
	Uint16 iPosx;
	Uint16 iPosy;

	Sint8 iValue;
	char Image[];
};

/**
 * \class LB_Avatar
 * Abstracts an avatar item
 */
class LB_AvatarItem
{
	char staticImage[];
	char gameImage[];
	std::string name;

    enum Type {HEAD, GLASSES, BODY, FLAG, EX};

	Sint8 iType;
	Sint8 iPopularity;
	Sint8 iDefence;
	Sint8 iAttack;
	Sint8 iBunge;
	Sint8 iHeart;
	Sint8 iBlueDelay;
	Sint8 iOrangeDelay;
	Sint8 iDelay;

	Uint32 iGoldPrices[3];
	Uint32 iCashPrices[3];

};

//Prototypes
int main(int argc, char* argv[]);
void MainLoop();

#endif
