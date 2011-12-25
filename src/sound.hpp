/**
 * \file sound.hpp
 * \brief Header for the sound system
 * \author G. B.
 * \version 0.1a
 * \date 24/10/2010
 */

#ifndef _H_SOUND_
#define _H_SOUND_

Mix_Music* music;

int LB_PlayMusic(const char* file);
int LB_PlaySFX(Mix_Chunk *filename, int channel, int loops);

#endif /* _H_SOUND_ */
