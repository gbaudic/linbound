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
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_gfxPrimitives.h>
#include "image.hpp"
using namespace std;


extern SDL_Surface *screen;
extern SDL_Surface *old_screen;
extern SDL_Surface *refresh_sample;
extern SDL_Surface *image;
extern SDL_Surface *cursor;
extern SDL_Event LastMouseEvent;
extern bool IsFirstRun;

//Set SDL_Rects used for blitting cursors
SDL_Rect old_cursor;
SDL_Rect *p_old_cursor = &old_cursor;
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

/**
 * Blits the cursor on the screen
 *
 * \param screen the screen surface
 * \param CursorType the cursor wanted : 0 for normal, 1 for waiting
 * \param event the mouse event to process
 */
void LB_BlitCursor(SDL_Surface *screen, Uint8 CursorType, SDL_Event event)
{
	//Choose the right cursor to display (0 for pointer, 1 for waiting)
	//cout << "Loading cursors" << endl;
	/* The IMG_Load block uses more and more memory at each iteration
	if (CursorType != 0) {
		cursor = IMG_Load("./wait.png");
	 } else {
		 if (CursorType == 0 && cursor == IMG_Load("./wait.png")) {
			 cursor = IMG_Load("./arrow.png");
		 }
	}  */


	//Set the colorkey for transparency
	//Could be moved to a better place to avoid repeating at each iteration
	SDL_SetColorKey(cursor, SDL_SRCCOLORKEY | SDL_RLEACCEL, SDL_MapRGB(cursor->format, 255, 0, 255));

	SDL_Rect cur_src, cur_dest;

	//Setting the coordinates, one more time
	cur_src.x = cur_src.y = 0;


	//Erasing the old cursor
	if(IsFirstRun == false) {
		if(SDL_BlitSurface(old_screen, NULL, screen, p_old_cursor) != 0) {
			//using NULL at 2 : entire surf
			//Null at 4 : blit on x=0 and y=0
			cout << "DEBUG : old cursor theft failed" << endl
			<< "Must appear only on first run of loop" << endl;
			} else {
			//and updating the display
			SDL_UpdateRect(screen, p_old_cursor->x, p_old_cursor->y, p_old_cursor->w, p_old_cursor->h);
			//cout << "Cursor erased at last" << endl;
		}
	} else {
		IsFirstRun = false;
	}


	//Saving and setting the x and y coords
	cur_src.w = cur_dest.w = p_old_cursor->w = cursor->w;
	cur_src.h = cur_dest.h = p_old_cursor->h = cursor->h;
	cur_dest.x = p_old_cursor->x = event.motion.x;
	cur_dest.y = p_old_cursor->y = event.motion.y;

	//Saving the place which will now host the cursor before it is drawn
	SDL_BlitSurface(screen, &cur_dest, old_screen, &cur_src);
	//cout << "Cursor saved" << endl;
	//Updating the display
	//SDL_UpdateRect(old_screen, 0, 0, old_cursor.w, old_cursor.h);

	//Blit the surfaces and display the result -- the user is now happy
	SDL_BlitSurface(cursor, &cur_src, screen, &cur_dest);
	//cout << "Cursor drawn" << endl;
	SDL_UpdateRect(screen, cur_dest.x, cur_dest.y, cur_dest.w, cur_dest.h);

	//Here we save the chunk of surface with the cursor to determine if it has been redrawn next time
	SDL_BlitSurface(screen, &cur_dest, refresh_sample, &cur_src);

	//Here we save the mouse event for redrawing if there was no event && the cursor place was updated
	p_LastMouseEvent->motion = event.motion;

	return;
}

/*void LB_FreeImages(SDL_Surface* surfs[])
{
	for(int i = 0 ; i < size(surfs) ; i++)
	{
		SDL_FreeSurface(surfs[i]);
	}
}*/

