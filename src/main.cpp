/**
 * \file main.cpp
 * \brief The main file
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
#include <string>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL2_framerate.h>
#include <guisan.hpp>
#include <guisan/sdl.hpp>

#include "main.hpp"
#include "init.hpp"
#include "event.hpp"
#include "image.hpp"
#include "sound.hpp"

#include "message.hpp"

using namespace std;


Uint16 iscreenw = 800;
Uint16 iscreenh = 600;

bool isFirstRun = true;

FPSmanager mgr;

gcn::SDLInput* input;             // Input driver
gcn::SDLGraphics* graphics;       // Graphics driver
gcn::SDLImageLoader* imageLoader; // For loading images
gcn::Gui* gui;            // A Gui object - binds it all together
gcn::Container* top;      // A top container
//gcn::SDLTrueTypeFont* font; //font is needed for widgets

/**
 * The holy Main Function
 * @param argc the number of arguments given
 * @param argv the arguments
 * @return 1 on error, 0 otherwise
 */
int main(int argc, char *argv[])
{
	cout << gettext("Initializing LinBound v0.1a...") << endl;

	int result = LB_ParseOptions(argc, argv);
	if(result == -1){
		return 0;
	}
	
	//gettext support
	setlocale(LC_ALL, "");
	bindtextdomain("linbound", "./po");
	textdomain("linbound");
	

	LB_Init();

	//Set up the screen
	screen = SDL_CreateWindow("LinBound", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, iscreenw, iscreenh, SDL_WINDOW_SHOWN);
	renderer = SDL_CreateRenderer(screen, -1, 0);
	if (screen == NULL) {
		cout << gettext("FATAL : Cannot create window: ") << SDL_GetError() << endl;
		return 1;
	}
	if (renderer == NULL) {
		cout << gettext("FATAL : Cannot create renderer: ") << SDL_GetError() << endl;
		return 1;
	}
	
	//Give an icon to the window
	icon = IMG_Load("./res/linbound.gif");
	SDL_SetWindowIcon(screen, icon);

	cursor = IMG_Load("./res/cursor.png");

	//The next function puts the cursor at the center of our screen
	SDL_WarpMouseInWindow(screen, iscreenw/2, iscreenh/2);

	graphics->setTarget(SDL_GetWindowSurface(screen));
	top = new gcn::Container();
	gui = new gcn::Gui();
	gui->setGraphics(graphics);
	gui->setInput(input);
	gui->setTop(top);

	//The colorkey needs the image to be loaded before doing anything, otherwise it crashes (function moved to image.cpp)
	int ckresult = SDL_SetColorKey(cursor, SDL_TRUE, SDL_MapRGB(cursor->format, 0xff, 0, 0xff));
	if(ckresult != 0){
		cout << SDL_GetError() << endl;
	}
	SDL_SetSurfaceRLE(cursor, 1);

	mousePointer = SDL_CreateColorCursor(cursor, 0, 0);
	if (mousePointer == NULL){
		cout << gettext("FATAL : Cannot create cursor: ") << SDL_GetError() << endl;
		return 1;
	}
	SDL_SetCursor(mousePointer);

	//Call a function which displays an image
	//If it crashed, don't let the user see a black window: he might be scared.
	switch (LB_ShowPicture(renderer, "./res/menu/menuLB.jpg")) {
		case -1 :
			SDL_FreeSurface(image);
			SDL_Quit();
			return 1;
		case 0 :
			SDL_RenderPresent(renderer);
			break;
		}
	//cout << "pic shown" << endl;


    if(LB_PlayMusic("./res/sound/test.ogg") != 0){
        cout << gettext("error with the music! : ") << SDL_GetError() << endl;
    }
	
	//Initialize random generator (will be used for wind generation and weather effect placement)
	srand(1854973);
    
    //Initialize framerate limiter (default is 30, we keep it)
    SDL_initFramerate(&mgr);

	//cout << "Entering main loop" << endl;
	MainLoop();

	//Let the user see how marvellous it is for 3 seconds
	//SDL_Delay(3000);

	//Free the memory allocated to the images
	delete top;
	delete gui;
	//TODO : it would be more clever to use an array to put the images and free them at once by making a function iterate through the whole table
	SDL_FreeCursor(mousePointer); 
	//SDL_FreeSurface(refresh_test);
	SDL_FreeSurface(image);
	SDL_FreeSurface(cursor);
	SDL_FreeSurface(icon);
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(screen);
	//and quit SDL nicely
	LB_Quit();

	return 0;
}

/**
 * The function acting as the base loop powering the game
 */
void MainLoop()
{
	for(;;){
		//The true loop begins here...
		//cout << "loop" << endl;

		//Here we poll the user events
		if (SDL_PollEvent(&event) == 1) {
			if (LB_EventProcessor(event) == -1) {
				//cout << "break" << endl;
				return;
			}
			input->pushInput(event);
		}

        //Network events (send and receive)

        //Update the model

        //Update the graphics
		SDL_RenderClear(renderer);
		//**Background

		//**Foreground

		//**GUI

		SDL_RenderPresent(renderer);

        //Change audio if needed

        SDL_framerateDelay(&mgr);
	} //and finishes there
}

