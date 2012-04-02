/**
 * \file error.cpp
 * \brief Error system functions
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
