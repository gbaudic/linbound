/**
 * \file image.hpp
 * \brief Header for image.cpp
 * 		  Part of LinBound game
 * \author G. B.
 * \date 24/10/2010
 */

#ifndef _H_IMAGE_
#define _H_IMAGE_

int LB_ShowPicture(SDL_Surface *screen, const char* picture);
void LB_BlitCursor(SDL_Surface *screen, Uint8 CursorType, SDL_Event event);

#endif /* _H_IMAGE_ */
