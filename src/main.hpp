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
/* This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. 
 * If a copy of the MPL was not distributed with this file, 
 * You can obtain one at http://mozilla.org/MPL/2.0/.
 * 
 * This Source Code Form is “Incompatible With Secondary Licenses”, 
 * as defined by the Mozilla Public License, v. 2.0.
 */


#ifndef _H_MAIN_
#define _H_MAIN_

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
/*#include <GL/gl.h>
#include <GL/glx.h>*/

#include "player.hpp"

SDL_Window *screen = NULL;
SDL_Renderer *renderer = NULL;
//SDL_Surface *old_screen;
SDL_Surface *image;
SDL_Surface *cursor = NULL;
//SDL_Surface *refresh_test = IMG_Load("./res/arrow.png");
SDL_Surface *icon = NULL;
SDL_Cursor *mousePointer = NULL;
SDL_Event event;
SDL_Event LastMouseEvent;
Uint8 iMode;
//Uint8 *piMode = &iMode;

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
