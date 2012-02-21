/**
 * \file sound.hpp
 * \brief Header for the sound system
 * \author G. B.
 * \version 0.1a
 * \date 24/10/2010
 */



#ifndef _H_SOUND_
#define _H_SOUND_

#include <SDL/SDL.h>
#include <SDL/SDL_mixer.h>

int LB_PlayMusic(char* file);
int LB_PlaySFX(Mix_Chunk *filename, int channel, int loops);

#endif /* _H_SOUND_ */
