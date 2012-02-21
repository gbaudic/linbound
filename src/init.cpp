/**
 * \file init.cpp
 * \brief Initialization functions
 * 		  Part of LinBound game
 * \author G. B.
 * \version 0.1a
 * \date 24/10/2010
 */

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
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_net.h>
#include <SDL/SDL_ttf.h>
#include <SDL/SDL_mixer.h>
//#include <ssl.h> -- using cURL will make this include unnecessary
#include "init.hpp"
using namespace std;

TTF_Font *font;
int fontsize = 12;
bool bIsTTFEnabled = true;
bool bIsNETEnabled = true;

/**
 * Initializes the libraries and surfaces which will always be used, regardless of the game mode
 * @return 0 if OK, -1 if an error occurs
 */
int LB_Init()
{
	//Initializing SDL
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) != 0) {
		cout << "FATAL : Cannot init SDL : " << SDL_GetError() << endl;
		return -1;
	}

	//Initializing SDL_ttf, needed for text display
	if (TTF_Init() != 0){
		cout << "FATAL : Cannot init SDL_ttf " << SDL_GetError() << endl;
		bIsTTFEnabled = false;
		return -1;
	}

	//TTF is initialized correctly, so let's load the font
	font = TTF_OpenFont("/home/podgy/workspace/Linbound/res/LiberationSans-Regular.ttf", fontsize);
	if (font == NULL){
		cout << "Font opening failed!" << endl;
	}

	//Initialize the sound system
	if (LB_InitSound(CHANNELS) == -1){
		return -1;
	}

	//Set the keyboard repeating delay : after 700 ms, every 200 ms
	SDL_EnableKeyRepeat(700, 200);
	//Hide the black cursor to replace it with a colored one (an image, actually)
	SDL_ShowCursor(0);

	//Give an icon to the window
	SDL_WM_SetIcon(IMG_Load("/home/podgy/workspace/Linbound/res/linbound.gif"), NULL);

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
		bIsNETEnabled = false;
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
 		cout << "Error loading audio decoding libraries : " << Mix_GetError() << endl;
 	}

	if (Mix_AllocateChannels(channels) != channels){
		cout << "All channels haven't been allocated, exiting" << endl;
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

	SDL_ShowCursor(1);

	if (bIsTTFEnabled == true){
		TTF_CloseFont(font);
		TTF_Quit();
	}

	if (bIsNETEnabled == true){
		SDLNet_Quit();
	}

	Mix_CloseAudio();

	SDL_Quit();
	return;
}
