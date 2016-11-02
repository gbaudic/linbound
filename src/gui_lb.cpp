/**
 * \file gui_lb.cpp
 * \brief GUI additions to guisan, specific to LinBound
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
//#include <SDL2/SDL_ttf.h>
//#include <SDL2/SDL_gfxPrimitives.h>
#include "gui_lb.hpp"
using namespace std;

extern int iscreenw, iscreenh;
SDL_Color white; /* Needs to be set somewhere */

/**
 * A GUI button representing a room in server view
 */
LB_RoomButton::LB_RoomButton() : gcn::ImageButton() {
	
}


