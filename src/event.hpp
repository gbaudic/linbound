/**
 * \file event.hpp
 * \brief Header for the event system
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


#ifndef _H_EVENT_
#define _H_EVENT_

//Constants for cursor types
const int LB_CURSOR_ARROW = 0;
const int LB_CURSOR_WAIT = 1;

//Prototypes
int LB_GetPressedButton(SDL_Event event);
void LB_CheckEvent(SDL_Event event);
bool LB_CheckCursorRedrawing();
int LB_EventProcessor(SDL_Event event);

#endif
