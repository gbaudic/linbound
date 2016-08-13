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

/*#include <cstdio>
#include <cstdlib>*/
#include <iostream>
#include <SDL2/SDL.h>

#include "event.hpp"
using namespace std;


int LB_GetPressedButton(SDL_Event event)
{
	return 0;
}

void LB_CheckEvent(SDL_Event event)
{
	return;
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
		//used to blit cursor
	}

	return 0;
}
