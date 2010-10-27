/**
 * \file sound.hpp
 * \brief Header for the sound system
 * \author G. B.
 * \version 0.1a
 * \date 24/10/2010
 */

#ifndef _H_SOUND_
#define _H_SOUND_

int LB_PlayMusic(Mix_Music *file1 = NULL, Mix_Music *file2 = NULL);
int LB_PlaySFX(Mix_Chunk *filename, int channel, int loops);

#endif /* _H_SOUND_ */
