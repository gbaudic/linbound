/**
 *  
 */
/* This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. 
 * If a copy of the MPL was not distributed with this file, 
 * You can obtain one at http://mozilla.org/MPL/2.0/.
 * 
 * This Source Code Form is “Incompatible With Secondary Licenses”, 
 * as defined by the Mozilla Public License, v. 2.0.
 */

#include <SDL2/SDL.h>
#include <SDL2/SDL2_gfxPrimitives.h>

#include <string>
#include <vector> //Verify if best structure for this
#include "Sprite.hpp"

#include "map.hpp"
using namespace std;


LB_MapBackground::LB_MapBackground(std::string staticPartPath, std::vector<std::string> animPartsPaths){
	//TODO: to be written, add place for bck description and sprite coordinates
	this->staticPart = IMG_Load(staticPartPath.c_str());

	for (std::vector<std::string>::iterator it = animPartsPaths.begin() ; it != animPartsPaths.end(); ++it){
		animParts.push_back(Sprite(it->c_str(), 0, 0, 0, 0));
	}
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

int LB_MapBackground::getWidth() const {
	return this->rendering->w;
}

int LB_MapBackground::getHeight() const {
	return this->rendering->h;
}

SDL_Surface* LB_MapBackground::getView() {
	return rendering;
}

LB_Map::LB_Map(std::string name, LB_MapBackground* background, std::string foregroundA, std::string foregroundB) {
    //Fill the SDL_Surfaces with the images associated with the paths given as arguments
    this->name = name;
	
	this->foregroundA = IMG_Load(foregroundA.c_str());
	this->foregroundB = IMG_Load(foregroundB.c_str());
	
	this->background = background;

	//Compute parallax ratios
	parallaxX = (double)background->getWidth()/(this->foregroundA->w);
	parallaxY = (double)background->getHeight()/(this->foregroundA->h);
	
	//Use RLE acceleration and set magenta colorkey on foregrounds
	SDL_SetColorKey(this->foregroundA, SDL_TRUE, SDL_MapRGB(this->foregroundA->format, 0xFF, 0, 0xFF));
	SDL_SetSurfaceRLE(this->foregroundA, 1);
	if(this->foregroundB != NULL) {
		SDL_SetColorKey(this->foregroundB, SDL_TRUE, SDL_MapRGB(this->foregroundB->format, 0xFF, 0, 0xFF));	
		SDL_SetSurfaceRLE(this->foregroundB, 1);
	}
}

LB_Map::~LB_Map() {
    //Free the SDL_Surfaces properly
	SDL_DestroyTexture(previewSmall);
	SDL_DestroyTexture(previewMedium);
    SDL_FreeSurface(foregroundA);
    SDL_DestroyTexture(preview);

    if(has2Sides){
        SDL_FreeSurface(foregroundB);
    }
	
	SDL_DestroyTexture(foreground);
}

/**
 * Change map side
 * @param newSide true to choose A, false to choose B
 */
void LB_Map::setASide(bool newSide) {
	if(has2Sides)
		isASide = newSide;
}

bool LB_Map::getASide() const {
    return isASide;
}

std::string LB_Map::getName() const {
	return name;
}

void LB_Map::setViewport(int x, int y) {
	viewport.x = x;
	viewport.y = y;
}

void LB_Map::setViewportSize(int w, int h) {
	viewport.w = w;
	viewport.h = h;
	//TODO: recompute parallax ratios
}

void drawBackground(SDL_Renderer* rend) {
	
}

/**
 *  Draws the (possibly destroyed) foreground to a renderer
 *  \param rend a SDL_Renderer pointer
 */
void LB_Map::drawForeground(SDL_Renderer* rend) {
	if(refreshForeground){
		//This trick lets us refresh the texture only when needed
		SDL_DestroyTexture(foreground); //avoid memory leaks
		foreground = SDL_CreateTextureFromSurface(rend, isASide ? foregroundA : foregroundB);
		refreshForeground = false;
	}
	SDL_RenderCopy(rend, foreground, NULL, &viewport);
}

/**
 * Draws a magenta circle at the desired coordinates to create a hole
 */
void LB_Map::makeDamage(Sint16 x, Sint16 y, Sint16 radius) {
	//TODO: sdl_gfx now writes to a Renderer instead of a Surface
	SDL_Surface* srf = NULL;
	if(isASide){
		srf = foregroundA;
	} else {
		srf = foregroundB;
	}
	
	if(srf == NULL)
		return;
	
	if(SDL_MUSTLOCK(srf))
		SDL_LockSurface(srf);
	for(int xi = x - radius; xi < x + radius ; x++){
		for(int yi = y - radius ; yi < y + radius ; y++){
			if(xi*xi + yi*yi <= radius*radius && xi >= 0 && xi < srf->w && yi >= 0 && yi < srf->h){
				Uint32 *p = (Uint32 *)srf->pixels + yi * srf->w + xi;
				*p = SDL_MapRGBA(srf->format, 0xff, 0, 0xff, 0);
				//this assumes a 32-bit surface...
			}
		}
	}	
	if(SDL_MUSTLOCK(srf))
		SDL_UnlockSurface(srf);
	
	/*if(isASide){
		filledCircleRGBA(foregroundA, x, y, radius, 0xff, 0, 0xff, 0);
	} else {
		filledCircleRGBA(foregroundB, x, y, radius, 0xff, 0, 0xff, 0);
	}*/
	refreshForeground = true;

}

/**
 * Effectively load the biggest surfaces in memory when requested
 * The aim of this is to save memory with maps when they are not being played
 */
void LB_Map::activate() {
	//Reload background and fresh foreground
	
	refreshForeground = true;
}

void LB_Map::deactivate() {
	//Free background and used foreground
}

