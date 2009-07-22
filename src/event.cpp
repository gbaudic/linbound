//Event managing functions
//Part of Linbound game
//(C)  Copyright 2007-2009 G. B.

/*        This library is free software; you can redistribute it and/or
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

#include <libintl.h>
#include <locale.h>

#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <SDL/SDL.h>
#include "event.h"
using namespace std;

extern SDL_Surface *screen;
extern SDL_Surface *cursor;
extern SDL_Surface *refresh_test;
extern SDL_Surface *old_screen;
extern SDL_Surface *refresh_sample;
extern SDL_Event event;
extern SDL_Event LastMouseEvent;


void LB_BlitCursor(SDL_Surface *screen, Uint8 CursorType, SDL_Event event);

int GetPressedButton(SDL_Event event)
{

}

void LB_CheckEvent(SDL_Event event)
{

}

int LB_CheckCursorRedrawing()
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
	if(refresh_test->pixels!=refresh_sample->pixels){
		//Seems like the screen has been redrawn since last time
		return 1;
	} else {
		//Seems like nothing has changed
		return 0;
	}
	
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

int EventProcessor(SDL_Event event)
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
	if(event.type!=SDL_MOUSEMOTION && LB_CheckCursorRedrawing()==1){
		LB_BlitCursor(screen, LB_CURSOR_ARROW, LastMouseEvent);
	} 
	
	return 0;
}
