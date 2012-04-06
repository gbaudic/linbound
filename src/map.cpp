/* This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. 
 * If a copy of the MPL was not distributed with this file, 
 * You can obtain one at http://mozilla.org/MPL/2.0/.
 * 
 * This Source Code Form is “Incompatible With Secondary Licenses”, 
 * as defined by the Mozilla Public License, v. 2.0.
 */

#include <SDL/SDL.h>
#include <SDL/SDL_gfxPrimitives.h>

#include "map.hpp"
using namespace std;

LB_MapBackground::LB_MapBackground(){
	//TODO: to be written
}

LB_MapBackground::~LB_MapBackground(){
	SDL_FreeSurface(rendering);
	SDL_FreeSurface(staticPart);
}

void LB_MapBackground::refresh(){
	for(unsigned int i = 0 ; i < animParts.size() ; i++){
		//Blit the static part on sprites rects
		SDL_Rect* r = animParts[i].getRect();
		SDL_BlitSurface(staticPart, r, rendering, r);

		//Draw the sprites in their current state
		animParts[i].draw(rendering);
	}
}

SDL_Surface* LB_MapBackground::getView(){
	return rendering;
}

LB_Map::LB_Map(std::string name, LB_MapBackground background, std::string foregroundA, std::string foregroundB)
{
    //Fill the SDL_Surfaces with the images associated with the paths given as arguments
    this->name = name;
}

LB_Map::~LB_Map()
{
    //Free the SDL_Surfaces properly
	SDL_FreeSurface(previewSmall);
	SDL_FreeSurface(previewMedium);
    SDL_FreeSurface(foregroundA);
    SDL_FreeSurface(previewA);

    if(has2Sides)
    {
        SDL_FreeSurface(foregroundB);
        SDL_FreeSurface(previewB);
    }
}

void LB_Map::setASide(bool newSide)
{
    isASide = newSide;
}

bool LB_Map::getASide() const
{
    return isASide;
}

/**
 * Draws a magenta circle at the desired coordinates to create a hole
 */
void LB_Map::makeDamage(Sint16 x, Sint16 y, Sint16 radius){
	if(isASide){
		filledCircleRGBA(foregroundA, x, y, radius, 0xff, 0, 0xff, 0);
	} else {
		filledCircleRGBA(foregroundB, x, y, radius, 0xff, 0, 0xff, 0);
	}

}

/**
 * Completes the black border which has been eaten by makeDamage
 */
void LB_Map::correctAfterDamage(Sint16 x, Sint16 y, Sint16 radius){
	if(isASide){

	} else {

	}
}
