/**
 * \file init.hpp
 * \brief Header file for init functions
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

#ifndef _H_INIT_
#define _H_INIT_

#include <libintl.h>
#include <locale.h>

#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_net.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>

const int CHANNELS = 2;

//Prototypes
int LB_Init();
int LB_ParseOptions(int argc, char *argv[]);
int LB_InitNetwork(Uint8 *imode);
int LB_InitSound(int channels);
void LB_Quit();

#endif /* _H_INIT_ */
