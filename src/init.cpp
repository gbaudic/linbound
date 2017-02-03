/**
 * \file init.cpp
 * \brief Initialization functions
 * 		  Part of LinBound game
 * \author G. B.
 * \version 0.1a
 * \date 24/10/2010
 */

/* This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. 
 * If a copy of the MPL was not distributed with this file, 
 * You can obtain one at http://mozilla.org/MPL/2.0/.
 * 
 * This Source Code Form is "Incompatible With Secondary Licenses",
 * as defined by the Mozilla Public License, v. 2.0.
 */

#include <libintl.h>
#include <locale.h>

#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_net.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>
#include <guisan.hpp>
#include <guisan/sdl.hpp>

#include "init.hpp"
#include "sound.hpp"
#include "db.hpp"
#include "settings.hpp"
using namespace std;

TTF_Font *font = NULL;
int fontsize = 12;
bool isTTFEnabled = true;
bool isNETEnabled = true;
extern UDPsocket serverSocket;
extern UDPsocket clientSocket;
extern gcn::SDLInput* input;
extern gcn::SDLGraphics* graphics;
extern gcn::SDLImageLoader* imageLoader;
extern gcn::SDLTrueTypeFont* gcnfont;
bool isServer = false;

/**
 * Initializes the libraries and surfaces which will always be used, regardless of the game mode
 * @return 0 if OK, -1 if an error occurs
 */
int LB_Init() {
	//Initializing SDL
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) != 0) {
		cout << gettext("FATAL : Cannot init SDL : ") << SDL_GetError() << endl;
		return -1;
	}

	//Initializing SDL_ttf, needed for text display
	if (TTF_Init() != 0){
		cout << gettext("FATAL : Cannot init SDL_ttf ") << SDL_GetError() << endl;
		isTTFEnabled = false;
		return -1;
	}

	//TTF is initialized correctly, so let's load the font
	font = TTF_OpenFont("./res/fonts/LiberationSans-Regular.ttf", fontsize);
	if (font == NULL){
		cout << gettext("Font opening failed! " ) << TTF_GetError() << endl;
	}

	//Initialize the sound system
	if (!isServer && LB_InitSound(CHANNELS) == -1){
		return -1;
	}
	

	//Create GUI base objects
	input = new gcn::SDLInput();
	imageLoader = new gcn::SDLImageLoader();
	gcn::Image::setImageLoader(imageLoader);
	graphics = new gcn::SDLGraphics();
	gcnfont = new gcn::SDLTrueTypeFont("./res/fonts/LiberationSans-Regular.ttf", 12);
	gcn::Widget::setGlobalFont(gcnfont);

	SDL_DisableScreenSaver();

	return 0;
}

/**
 * Parses the options given to the main function and acts accordingly
 * @param argc the number of arguments passed
 * @param argv the array containing those arguments
 * @return 0 if execution must continue, -1 if program should stop
 */
int LB_ParseOptions(int argc, char *argv[]) {

	if(argc >= 2){
		if(strncmp(argv[1], "-v\0", 2) == 0 || strncmp(argv[1], "--version\0", 9) == 0){
			cout << "LinBound v0.1a\n"
					<< "(C) 2008-2016 G. B. aka podgy_piglet and contributors\n"
					<< "This software is free software released under the Mozilla Public License 2.0\n";
			return -1;
		}
		
		//Detect if we are launched as a server
		if(strncmp(argv[1], "--server\0", 8) == 0){
			isServer = true;
			cout << "Running in server mode" << endl;
		}
		
		//Manage help flag
		if(strncmp(argv[1], "-h\0", 2) || strncmp(argv[1], "--help\0", 6)){
			cout << "LinBound v0.1a\n" << endl
				 << "Supported commands: " << endl
				 << "-h, --help    : display this help and exit" << endl
				 << "-v, --version : display version number and exit" << endl
				 << "--server      : start a server" << endl;
			return -1;
		}
	}

	return 0;
}

/**
 * Initializes the network
 * @param imode the game mode
 * @return 0 if OK, -1 otherwise
 */
int LB_InitNetwork(Uint8 *imode) {

	if (SDLNet_Init() != 0){
		cout << gettext("SDL_net init error: ") << SDLNet_GetError() << endl;
		isNETEnabled = false;
		return -1;
	}

	//TODO: create UDP sockets
	serverSocket = SDLNet_UDP_Open(SERVER_PORT);
	if(serverSocket == NULL){
		cout << gettext("Server socket creation error: ") << SDLNet_GetError() << endl;
		return -1;
	}
	//client socket
	
	if(isServer){
		LB_initDB();
	}

	return 0;

}

/**
 * The function in charge of initializing the true audio subsystem for playing music and SFX
 * @param channels the number of channels you want to open (eg 2 for SFX and music)
 * @return 0 if no error, -1 otherwise
 */
int LB_InitSound(int channels) {
	if (!isServer) {
		if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 4096) == -1) {
			cout << "Mix_OpenAudio: " << Mix_GetError() << endl;
			return -1;
		}

		int flags = MIX_INIT_OGG; //MP3 is unlikely to work everywhere...
		int res = Mix_Init(flags);

		if(res != flags){
			cout << gettext("Error loading audio decoding libraries : ") << Mix_GetError() << endl;
		}

		if (Mix_AllocateChannels(channels) != channels){
			cout << gettext("All channels haven't been allocated, exiting") << endl;
			return -1;
		}

		if (LB_LoadSFX() != 0){
			cout << gettext("Error loading SFX files: ") << Mix_GetError() << endl;
			//Missing audio files is unpleasant but not critical, no return here
		}

		//Set the volume to 50% to begin
		Mix_VolumeMusic(MIX_MAX_VOLUME/2);
		Mix_Volume(-1, MIX_MAX_VOLUME/2);
	}

	return 0;

}

/**
 * The function in charge of exiting everything and calling quit functions for the called libraries
 * Should be called only once when shutting down the program
 */
void LB_Quit() {

	if (isTTFEnabled){
		TTF_CloseFont(font);
		TTF_Quit();
	}
	
	if(isServer){
		LB_closeDB();
	}

	if (isNETEnabled){
		//close sockets if needed
		SDLNet_UDP_Close(serverSocket);
		SDLNet_Quit();
	}

	delete input;
	delete graphics;
	delete imageLoader;
	
	if(!isServer){
		LB_FreeSFX();
		LB_FreeMusic();
		Mix_Quit();
		Mix_CloseAudio();
	}

	SDL_Quit();
	return;
}
