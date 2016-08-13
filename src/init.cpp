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
 * This Source Code Form is “Incompatible With Secondary Licenses”, 
 * as defined by the Mozilla Public License, v. 2.0.
 */

//#include <ssl.h> -- using cURL will make this include unnecessary
#include "init.hpp"
using namespace std;

TTF_Font *font = NULL;
int fontsize = 12;
bool isTTFEnabled = true;
bool isNETEnabled = true;

/**
 * Initializes the libraries and surfaces which will always be used, regardless of the game mode
 * @return 0 if OK, -1 if an error occurs
 */
int LB_Init()
{
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
		cout << gettext("Font opening failed!" ) << TTF_GetError() << endl;
	}

	//Initialize the sound system
	if (LB_InitSound(CHANNELS) == -1){
		return -1;
	}


	SDL_DisableScreenSaver();

	return 0;
}

/**
 * Parses the options given to the main function and acts accordingly
 * @param argc the number of arguments passed
 * @param argv the array containing those arguments
 * @return 0 if OK, -1 if there's an error
 */
int LB_ParseOptions(int argc, char *argv[])
{
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

	if(argc >= 2){
		if(strncmp(argv[1], "-v\0", 2) == 0 || strncmp(argv[1], "--version\0", 9) == 0){
			cout << "LinBound v0.1a\n"
					<< "(C) 2008-2016 G. B. aka podgy_piglet and contributors\n"
					<< "This software is free software released under the Mozilla Public License 2.0\n";
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
int LB_InitNetwork(Uint8 *imode)
{

	if (SDLNet_Init() != 0){
		isNETEnabled = false;
		return -1;
	}

	return 0;

}

/**
 * The function in charge of initializing the true audio subsystem for playing music and SFX
 * @param channels the number of channels you want to open (eg 2 for SFX and music)
 * @return 0 if no error, -1 otherwise
 */
int LB_InitSound(int channels)
{
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

	Mix_VolumeMusic(MIX_MAX_VOLUME/2); //Set the volume to 50% to begin

	return 0;

}

/**
 * The function in charge of exiting everything and calling quit functions for the called libraries
 */
void LB_Quit()
{

	if (isTTFEnabled){
		TTF_CloseFont(font);
		TTF_Quit();
	}

	if (isNETEnabled){
		SDLNet_Quit();
	}

	Mix_CloseAudio();

	SDL_Quit();
	return;
}
