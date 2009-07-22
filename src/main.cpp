//The main file of LinBound game, an attempt to create GunBound for unsupported platforms.
//(C) Copyright 2007-2009 G. B.

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
#include "strings.h"
#include <SDL/SDL_image.h>
#include "main.h"
using namespace std;


Uint16 iscreenw = 800;
Uint16 iscreenh = 600;
extern SDL_Rect old_cursor, cur_dest;

int ShowPicture(SDL_Surface *screen, const char* picture);
int LB_Init();
void MainLoop();
int EventProcessor(SDL_Event event);
bool IsFirstRun = true;

int main(int argc, char *argv[])
{
	cout << "Initializing LinBound v0.1a..." << endl;
	
	/* if (argc >= 3){
		//Recognize and use resolution requested by the user
		//If arguments are bad, use default to let the soft run and avoid hacking by buffer overflow.
		if (strncmp(argv[1], "640\0",3) == 0 && strncmp(argv[2], "480\0", 3) == 0){
			iscreenw = 640;
			iscreenh = 480;
			cout << "Using 640*480, user-defined" << endl;
		}
			
		if (strncmp(argv[1], "800\0",3) == 0 && strncmp(argv[2], "600\0", 3) == 0){
			iscreenw = 800;
			iscreenh = 600;
			cout << "Using 800*600, user-defined" << endl;
		}
			
		if (strncmp(argv[1], "1024\0",4) == 0 && strncmp(argv[2], "768\0", 3) == 0){
			iscreenw = 1024;
			iscreenh = 768;
			cout << "Using 1024*768, user-defined" << endl;
		}
		
		if (iscreenw == 0){
			iscreenw = 800;
			iscreenh = 600;
			cout << "Bad arguments, using default 800*600" << endl;
		}
	}  else {
		//Use default and tell the user if he put nothing
		cout << "No resolution defined, using default 800*600." << endl;
		iscreenw = 800;
		iscreenh = 600;
	} */
	
	
	
	LB_Init();
	
	//Set up the screen
	screen = SDL_SetVideoMode(iscreenw, iscreenh, 16, SDL_SWSURFACE);
	if (screen == NULL) {
		cout << "FATAL : Cannot set video mode : " << SDL_GetError() << endl;
		return 1;
	}
	
	//Give a title to our window
	SDL_WM_SetCaption("LinBound", "LinBound");
	//The next commented function puts the cursor at the center of our screen
	SDL_WarpMouse(iscreenw/2, iscreenh/2);
	
	//The colorkey needs the image to be loaded before doing anything, otherwise it crashes ( function moved to image.cpp)
	
	//Call a function which displays an image
	//If it crashed, don't let the user see a black window: he might be scared.
		switch (ShowPicture(screen, "menuLB.jpg")) {
			case 1 : 
			SDL_FreeSurface(image);
			SDL_Quit();
			return 1;
			case 0 : 
			SDL_UpdateRect(screen, 0, 0, 0, 0);
			break;
		}
	//cout << "pic shown" << endl;
	old_screen = IMG_Load("./arrow.png");
	//old_cursor.x = old_cursor.y = 0;
	
	//cur_dest.x = cur_dest.y = 0;
	
	//cout << "Entering main loop" << endl;
	MainLoop();
	
	//Let the user see how marvellous it is for 3 seconds
	//SDL_Delay(3000);
	
	//Free the memory allocated to the images
	//TODO : it would be cleverer to use an array to put the images and free them at once by making a function iterate through the whole table
	SDL_FreeSurface(refresh_test);
	SDL_FreeSurface(old_screen);
	SDL_FreeSurface(refresh_sample);
	SDL_FreeSurface(image);
	SDL_FreeSurface(cursor);
	SDL_FreeSurface(screen);
	//and quit SDL nicely
	SDL_Quit();
	
	return 0;
}

void MainLoop()
{
	for(;;){
		//The true loop begins here...
		//cout << "loop" << endl;
				
		//Here we poll the user events
		if (SDL_PollEvent(&event) == 1) {
			if (EventProcessor(event) == -1) {
				return;
			}
		} 
	
	
	
	
	} //and finishes there
}
