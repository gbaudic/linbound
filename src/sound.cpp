//Sound handling functions
//Part of LinBound game
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
#include <SDL/SDL.h>
#include <SDL/SDL_mixer.h>
using namespace std;

//As of 2009-08-17, all functions listed here need preallocated sound buffers
//This will be completed in an hypothetical future

//One basic function to load the music
//Returns 0 if OK, -1 if something went wrong
//TODO: test this function, even if it should really work
int LB_PlayMusic(Mix_Music *file1 = NULL, Mix_Music *file2)
{
	//We must first check if there's some music playin'
 	if (Mix_PlayingMusic() == 1) {
		//If it is the case, we stop it: we are here to change it!
		Mix_HaltMusic();
		//And we just free the memory used
		if (file1 != NULL) {
			Mix_FreeMusic(filename1);
		} else {
			//This should never happen but if it does, the app won't freeze
			SDL_SetError("No input pointer given !");
			return -1;
		}	
	}
	
	//Now it is time for some fun... enjoy the music ad infinitum
	return Mix_PlayMusic(file2, -1);
}

//Another function to play some SFX (rather useless currently...)
//Returns 0 if OK, -1 if something went wrong
//TODO: test this function, even if it should really work
int LB_PlaySFX(Mix_Chunk *filename, int channel, int loops)
{
 	return Mix_PlayChannel(channel, filename, loops);
}
