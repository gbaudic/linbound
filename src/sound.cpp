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
#include <stdexcept>
#include <cstdlib>
#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>
#include "sound.hpp"
using namespace std;

Mix_Music* music;
map<string, Mix_Chunk*> effects;

/**
 * One basic function to load the music
 * @param file the new music file we want to play
 * @return 0 if OK, -1 if something gets wrong
 */
//TODO: test this function, even if it should really work
int LB_PlayMusic(string file) {
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
    music = Mix_LoadMUS(file.c_str());
    if(music == NULL){
    	cout << gettext("Music not loaded: ") << Mix_GetError() << endl;
    	return -1;
    }

	//Now it is time for some fun... enjoy the music ad infinitum
	return Mix_PlayMusic(music, -1);
}

/**
 * Idea: load all possible FX in a Map and fetch them afterwards with their name
 * @return 0 on success, the number of errors encountered otherwise
 */
int LB_LoadSFX(){
	string effectNames[] = {"wind1", "turn", "victory", "lose", "money",
							"cow", "duck", "electron", "goat", "ice", "pig", "sheep", "tea", "unicorn"};
	int counter = 0;
	
	for(string item : effectNames){
		string path = "./res/sounds/" + item + ".ogg";
		Mix_Chunk* res = Mix_LoadWAV(path.c_str());
		if (res != NULL) {
			effects.insert(make_pair(item, res));
		} else {
			//Error while loading file
			counter++;
		}
	}

	return counter;
}

/**
 * Plays a sound which is not the background music, e.g. SFX
 * @param filename the file to play
 * @param loops the number of iterations of the sound
 * @return 0 if OK, -1 if something went wrong
 */
//TODO: test this function
int LB_PlaySFX(string SFXname, int loops) {
	int res;
	try {
		res = Mix_PlayChannel(-1, effects.at(SFXname), loops);
	} catch (const out_of_range& e) {
		SDL_SetError("Sound effect not found: "+ SFXname);
		return -1;
	}

 	return (res > 0 ? 0 : res);
}

/**
 * Free all allocated FXs
 * Used at program shutdown
 */
void LB_FreeSFX() {
	for(auto item : effects){ //C++11
		Mix_FreeChunk(item.second);
	}
}

/**
 *  Stop and free the music
 *  Used at program shutdown
 */
void LB_FreeMusic() {
	Mix_HaltMusic();
	Mix_FreeMusic(music);
}

/**
 *  Determine how many times we have to repeat the sound for money
 *  @return the number of times to play between 1 and 5
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
