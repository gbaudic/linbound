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
#include "strings.h"
#include <SDL/SDL_image.h>

#include "main.hpp"
#include "init.hpp"
#include "event.hpp"
#include "image.hpp"
#include "sound.hpp"

#include "message.hpp"

using namespace std;


Uint16 iscreenw = 800;
Uint16 iscreenh = 600;
extern SDL_Rect old_cursor, cur_dest;

bool IsFirstRun = true;

/**
 * The holy Main Function
 * @param argc the number of arguments given
 * @param argv the arguments
 * @return 1 on error, 0 otherwise
 */
int main(int argc, char *argv[])
{
	cout << "Initializing LinBound v0.1a..." << endl;

	LB_Init();

	//Set up the screen
	screen = SDL_SetVideoMode(iscreenw, iscreenh, 16, SDL_SWSURFACE);
	if (screen == NULL) {
		cout << "FATAL : Cannot set video mode : " << SDL_GetError() << endl;
		return 1;
	}

	//The next commented function puts the cursor at the center of our screen
	SDL_WarpMouse(iscreenw/2, iscreenh/2);

	//The colorkey needs the image to be loaded before doing anything, otherwise it crashes (function moved to image.cpp)

	//Call a function which displays an image
	//If it crashed, don't let the user see a black window: he might be scared.
		switch (LB_ShowPicture(screen, "/home/podgy/workspace/Linbound/res/menuLB.jpg")) {
			case -1 :
			SDL_FreeSurface(image);
			SDL_Quit();
			return 1;
			case 0 :
			SDL_UpdateRect(screen, 0, 0, 0, 0);
			break;
		}
	//cout << "pic shown" << endl;
	old_screen = IMG_Load("/home/podgy/workspace/Linbound/res/arrow.png");
	//old_cursor.x = old_cursor.y = 0;

	//cur_dest.x = cur_dest.y = 0;

    if(LB_PlayMusic("/home/podgy/workspace/Linbound/res/sound/test.ogg") != 0){
        cout << "error with the music ! : " << SDL_GetError() << endl;
    }


	//cout << "Entering main loop" << endl;
	MainLoop();

	//Let the user see how marvellous it is for 3 seconds
	//SDL_Delay(3000);

	//Free the memory allocated to the images
	//TODO : it would be more clever to use an array to put the images and free them at once by making a function iterate through the whole table
	SDL_FreeSurface(refresh_test);
	SDL_FreeSurface(old_screen);
	SDL_FreeSurface(refresh_sample);
	SDL_FreeSurface(image);
	SDL_FreeSurface(cursor);
	SDL_FreeSurface(screen);
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
				return;
			}
		}

        //Network events (send and receive)

        //Update the model

        //Update the graphics

        //Change audio if needed


	} //and finishes there
}
