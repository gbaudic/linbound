/**
 * \file error.cpp
 * \brief Error system functions
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
//#include "main.h"
#include <SDL/SDL.h>
#include <SDL/SDL_ttf.h>
#include "error.hpp"
using namespace std;

extern int iscreenw, iscreenh;
extern TTF_Font *font;
char cError;
char *ErrorString = &cError;

/**
 * Displays an error corresponding to a given code
 * \param ErrorCode the code of the encountered error
 */
void LB_DisplayError (Uint16 ErrorCode)
{

}
