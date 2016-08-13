/**
 * \file gui_lb.cpp
 * \brief Functions related with GUI systems
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
//#include <guichan.hpp>
//#include <guichan/sdl.hpp>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
//#include <SDL2/SDL_ttf.h>
//#include <SDL2/SDL_gfxPrimitives.h>
#include "gui_lb.hpp"
using namespace std;

extern int iscreenw, iscreenh;
//extern TTF_Font *font;
SDL_Color white; /* Needs to be set somewhere */

LB_GUI::LB_GUI(){
	/*imageLoader = new SDLImageLoader();
	Image::setImageLoader(imageLoader);
	graphics = new SDLGraphics();
	graphics->setTarget(screen);
	input = new SDLInput();

	//font init...

	gui = new Gui();
	gui->setGraphics(graphics);
	gui->setInput(input);

	top = new Container();
	top->setDimension(Rectangle(0,0,iscreenw,iscreenh));
	gui->setTop(top);*/
}

LB_GUI::~LB_GUI(){
	/*delete top;

	delete gui;
	delete input;
	delete graphics;
	delete imageLoader;*/
}
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
