/**
 * \file event.hpp
 * \brief Header for the event system
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

#ifndef _H_EVENT_
#define _H_EVENT_

//Constants for cursor types
const int LB_CURSOR_ARROW = 0;
const int LB_CURSOR_WAIT = 1;

//Prototypes
int LB_GetPressedButton(SDL_Event event);
void LB_CheckEvent(SDL_Event event);
int LB_CheckCursorRedrawing();
int LB_EventProcessor(SDL_Event event);

#endif
