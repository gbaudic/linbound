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
#include "context.hpp"
#include "menu.hpp"

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
gcn::SDLTrueTypeFont* gcnfont; //font is needed for widgets

LB_Context* currentContext;
SDL_Surface* guiSurface; //Required to use simultaneously guisan and SDL Rendering API
SDL_Texture* guiTexture;

/**
 * The holy Main Function
 * @param argc the number of arguments given
 * @param argv the arguments
 * @return 1 on error, 0 otherwise
 */
int main(int argc, char *argv[]) {
	cout << gettext("Initializing LinBound...") << endl;
    
    //Handle any startup options
	int result = LB_ParseOptions(argc, argv);
	if(result == -1){
		return 0;
	}
	
	//gettext support
	setlocale(LC_ALL, "");
	bindtextdomain("linbound", "./po");
	textdomain("linbound");
	
    //Initialize required libraries
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
	SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
	
	//Set up GUI rendering surfaces
	guiSurface = SDL_CreateRGBSurface(0, iscreenw, iscreenh, 32, 0x00FF0000,
                                      0x0000FF00, 0x000000FF, 0xFF000000);
	//guiTexture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STREAMING, iscreenw, iscreenh);
	SDL_SetColorKey(guiSurface, SDL_TRUE, SDL_MapRGB(guiSurface->format, 0xff, 0, 0xff));
	SDL_SetSurfaceRLE(guiSurface, 1);
	guiTexture = SDL_CreateTextureFromSurface(renderer, guiSurface);
	if (guiSurface == NULL || guiTexture == NULL){
	    cout << gettext("FATAL : Cannot create GUI surface: ") << SDL_GetError() << endl;
		return 1;
	}
	SDL_SetTextureBlendMode(guiTexture, SDL_BLENDMODE_BLEND);
	
	//Give an icon to the window
	icon = IMG_Load("./res/linbound.gif");
	SDL_SetWindowIcon(screen, icon);

	cursor = IMG_Load("./res/cursor.png");

	//The next function puts the cursor at the center of our screen
	SDL_WarpMouseInWindow(screen, iscreenw/2, iscreenh/2);

	graphics->setTarget(guiSurface);
	top = new gcn::Container();
	top->setDimension(gcn::Rectangle(0, 0, iscreenw, iscreenh));
	top->setOpaque(false);
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

    currentContext = new LB_Menu(renderer);

    if(LB_PlayMusic("./res/sound/test.ogg") != 0){
        cout << gettext("error with the music! : ") << SDL_GetError() << endl;
    }
	
	//Initialize random generator (will be used for wind generation and weather effect placement)
	srand(1854973);
    
    //Initialize framerate limiter (default is 30, we keep it)
    SDL_initFramerate(&mgr);

	//cout << "Entering main loop" << endl;
    try {
    	MainLoop();
    } catch (gcn::Exception &e) {
		cerr << e.getMessage() << endl;
		return 1;
	} catch (std::exception &e) {
		cerr << gettext("Std exception: ") << e.what() << endl;
		return 1;
	} catch (...) {
		cerr << gettext("Unknown exception") << endl;
		return 1;
	}

	//Free the memory allocated to the images
	delete currentContext;
	delete gcnfont;
	delete top;
	delete gui;
	//TODO : it would be more clever to use a list to put the images and free them at once by making a function iterate through it
	SDL_FreeCursor(mousePointer); 
	//SDL_FreeSurface(refresh_test);
	SDL_DestroyTexture(guiTexture);
	SDL_FreeSurface(guiSurface);
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
void MainLoop() {
	for(;;){
		//The true loop begins here...
		//cout << "loop" << endl;

		//Here we poll the user events
		while (SDL_PollEvent(&event) == 1) {
			if (LB_EventProcessor(event) == -1) {
				//cout << "break" << endl;
				return;
			}
			input->pushInput(event);
		}

        //Network events (send and receive)

        //Update the model
		gui->logic();

        //Update the graphics
		SDL_RenderClear(renderer);
		SDL_FillRect(guiSurface, NULL, SDL_MapRGB(guiSurface->format, 0xff, 0, 0xff));
		//**Background
		currentContext->drawBackground();
        
		//**Foreground
		currentContext->drawMiddleground();

		//**GUI
		gui->draw();
		//Move guisurface to guitexture
		SDL_UpdateTexture(guiTexture, NULL, guiSurface->pixels, guiSurface->pitch);
		//Copy texture to screen
		SDL_RenderCopy(renderer, guiTexture, NULL, NULL);

		SDL_RenderPresent(renderer);
		//SDL_UpdateWindowSurface(screen);

        //Change audio if needed

        SDL_framerateDelay(&mgr);
	} //and finishes there
}

