/**
 * \file image.hpp
 * \brief Header for image.cpp
 * 		  Part of LinBound game
 * \author G. B.
 * \date 24/10/2010
 */
/* This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. 
 * If a copy of the MPL was not distributed with this file, 
 * You can obtain one at http://mozilla.org/MPL/2.0/.
 * 
 * This Source Code Form is “Incompatible With Secondary Licenses”, 
 * as defined by the Mozilla Public License, v. 2.0.
 */


#ifndef _H_IMAGE_
#define _H_IMAGE_

int LB_ShowPicture(SDL_Surface *screen, const char* picture);
void LB_BlitCursor(SDL_Surface *screen, Uint8 CursorType, SDL_Event event);

#endif /* _H_IMAGE_ */
