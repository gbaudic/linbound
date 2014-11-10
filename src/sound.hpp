/**
 * \file sound.hpp
 * \brief Header for the sound system
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

#ifndef _H_SOUND_
#define _H_SOUND_

#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>

int LB_PlayMusic(char* file);
int LB_PlaySFX(Mix_Chunk *filename, int channel, int loops);

#endif /* _H_SOUND_ */
