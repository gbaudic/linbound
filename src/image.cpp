/**
 * \file image.cpp
 * \brief Functions dealing with images
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


#include <libintl.h>
#include <locale.h>

#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL2_gfxPrimitives.h>
#include "image.hpp"
using namespace std;

extern SDL_Surface *refresh_sample;
extern SDL_Surface *image;
extern SDL_Event LastMouseEvent;
extern bool IsFirstRun;

//Set SDL_Rects used for blitting cursors
SDL_Event *p_LastMouseEvent = &LastMouseEvent;

/**
 * Blits a whole picture on a given surface
 * @param screen the screen surface
 * @param picture the picture to show
 * @return 0 if success, -1 otherwise
 */
int LB_ShowPicture(SDL_Surface *screen, const char* picture)
{
	SDL_Rect src, dest;

	//Load the image we want to display
	image = IMG_Load(picture);
	if (image == NULL) {
		//If it didn't work, tell the user
		cout << gettext("ERROR : Cannot load the img: ") << picture << endl;
		return -1;
	}

	//Setting coordinates
	src.x = src.y = dest.x = dest.y = 0;
	src.w = dest.w = image->w;
	src.h = dest.h = image->h;

	//Blit the black screen and our image together...
	SDL_BlitSurface(image, &src, screen, &dest);
	//and update the screen to make it appear in our window

	//cout << "picture shown" << endl;
	return 0;
}

