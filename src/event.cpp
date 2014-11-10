/**
 * \file event.cpp
 * \brief Event handling functions
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

#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <SDL2/SDL.h>
#include "event.hpp"
using namespace std;

extern SDL_Window *screen;
extern SDL_Surface *cursor;
extern SDL_Surface *refresh_test;
extern SDL_Surface *old_screen;
extern SDL_Surface *refresh_sample;
extern SDL_Event event;
extern SDL_Event LastMouseEvent;


void LB_BlitCursor(SDL_Window *screen, Uint8 CursorType, SDL_Event event);

int LB_GetPressedButton(SDL_Event event)
{
	return 0;
}

void LB_CheckEvent(SDL_Event event)
{
	return;
}

/**
 * Checks if the cursor has been overwritten or not
 * \return 1 if the screen has changed, 0 otherwise
 */
//TODO: this function typically gives a boolean answer, so use a boolean!
bool LB_CheckCursorRedrawing()
{
	//Creating the temporary rects for blitting
	SDL_Rect src, dest;

	//Setting coordinates
	src.x = LastMouseEvent.motion.x;
	src.y = LastMouseEvent.motion.y;
	dest.x = 0;
	dest.y = 0;
	src.w = dest.w = cursor->w;
	src.h = dest.h = cursor->h;

	//Blit the screen to the test surface...
	SDL_BlitSurface(screen, &src, refresh_test, &dest);

	//and perform the desired check
	return (refresh_test->pixels!=refresh_sample->pixels);

}

/* int LB_ClickDetector(SDL_MouseButtonEvent *event)
{
	if (event->type == SDL_MOUSEBUTTONDOWN && event->button == SDL_BUTTON_LEFT){
		GetPressedButton(event.x, event.y);
	}

	if (event->type == SDL_MOUSEBUTTONDOWN && event->button == SDL_BUTTON_RIGHT){
		GetMenu(event.x, event.y);
	}
} */

/**
 * A processor to pass the events to the corresponding processing subsystem
 * @param event the event to process
 * @return -1 if it is a quit event, 0 otherwise
 */
int LB_EventProcessor(SDL_Event event)
{
	if(event.type==SDL_QUIT){
		return -1;
	}

	if(event.type==SDL_KEYDOWN){
		if (event.key.keysym.sym==SDLK_ESCAPE){
			return -1;
		}
	}

	if(event.type==SDL_MOUSEMOTION) {
		//LB_CheckEvent(event);
		LB_BlitCursor(screen, LB_CURSOR_ARROW, event);
	}

	//This IF statement checks if display has been redrawn with no cursor move to redraw the cursor
	if(event.type!=SDL_MOUSEMOTION && LB_CheckCursorRedrawing() ){
		LB_BlitCursor(screen, LB_CURSOR_ARROW, LastMouseEvent);
	}

	return 0;
}
