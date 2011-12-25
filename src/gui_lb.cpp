/**
 * \file gui_lb.cpp
 * \brief Functions related with GUI systems
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

#include <libintl.h>
#include <locale.h>

#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <guichan.hpp>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
//#include <SDL/SDL_ttf.h>
//#include <SDL/SDL_gfxPrimitives.h>
#include "gui_lb.hpp"
using namespace std;

extern SDL_Surface *screen;
extern int iscreenw, iscreenh;
//extern TTF_Font *font;
SDL_Color white; /* Needs to be set somewhere */


/* void LB_GUI_SetProgressBar(GUI_element *progressbar, Uint8 *percentage)
{
	return;
} */

/**
 * Displays a message box
 * \param type the type wanted, see gui_lb.hpp for available types
 * \param title title for the message box
 * \param message the message to display
 * \param buttons the number of buttons
 * \return 0 if success, -1 otherwise
 */
/*int LB_GUI_DisplayMsgBox(Uint8 type, const char* title, const char* message, Uint8 buttons)
{
	//Drawing the box : two filled rectangles
	boxColor(screen, iscreenw/4, iscreenh/4, iscreenw*3/4, iscreenh*3/4, 0x0066FF00);
	boxColor(screen, (iscreenw/4)+15, (iscreenh/4)+15, (iscreenw*3/4)-15, (iscreenh*3/4)+15, 0x00CCFF00);
	//and a line to put the title apart
	hlineColor(screen, (iscreenw/4)+15, (iscreenw*3/4)-15, (iscreenh/4)+50, 0x00000000);


	//SDL_Surface *title = TTF_RenderUTF8_Solid(font, title, white);
	//


	return 0;
}*/
