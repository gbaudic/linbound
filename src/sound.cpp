/**
 * \file sound.cpp
 * \brief Sound handling functions
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

#include <map>
#include <string>
#include <iostream>
#include <cstdlib>
#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>
#include "sound.hpp"
using namespace std;

//As of 2009-08-17, all functions listed here need preallocated sound buffers
//This will be completed in an hypothetical future
Mix_Music* music;
map<string, Mix_Chunk*> effects;

/**
  * One basic function to load the music
  * \param file the new music we want to play
  * \return 0 if OK, -1 if something gets wrong
*/
//TODO: test this function, even if it should really work
int LB_PlayMusic(char* file) {
	//We must first check if there's some music playin'
 	if (Mix_PlayingMusic() == 1) {
		//If it is the case, we stop it: we are here to change it!
		Mix_HaltMusic();
		//And we just free the memory used
		if (music != NULL) {
			Mix_FreeMusic(music);
		} else {
			//This should never happen but if it does, the app won't freeze
			SDL_SetError("LB_PlayMusic: No input pointer given! ");
			return -1;
		}
	}

    //Load the new music
    music = Mix_LoadMUS(file);
    if(music == NULL){
    	cout << gettext("Music not loaded: ") << Mix_GetError() << endl;
    	return -1;
    }

	//Now it is time for some fun... enjoy the music ad infinitum
	return Mix_PlayMusic(music, -1);
}

/**
 * Idea: load all possible FX in a Map and fetch them afterwards with their name
 */
int LB_LoadSFX(){
	string effectNames[] = {"wind", "turn", "win", "lose", "money"};
	
	return 0;
}

//Another function to play some SFX (rather useless currently...)
//Returns 0 if OK, -1 if something went wrong
/**
 * Plays a sound which is not the background music, e.g. SFX
 * @param filename the file to play
 * @param channel the channel on which you want to play the sound
 * @param loops the number of iterations of the sound
 * @return 0 if OK, -1 if something went wrong
 */
//TODO: test this function, even if it should really work
int LB_PlaySFX(Mix_Chunk *filename, int channel, int loops) {
 	return Mix_PlayChannel(channel, filename, loops);
}

/**
 * Free all allocated FXs
 */
int LB_FreeSFX() {
	return 0;
}

/**
 *  Determine how many times we have to repeat the sound
 */
int LB_CountGoldRepeat(Sint16 value) {
	int repeats = 1;
	int absolute = abs(value);
	if(absolute > 50)
		repeats++;
	if(absolute > 100)
		repeats++;
	if(absolute > 200)
		repeats++;
	if(absolute > 500)
		repeats++;
	
	return repeats;
}
