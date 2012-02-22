/*
 * Sprite.cpp
 *
 *  Created on: 23 févr. 2012
 *      Author: podgy
 */

#include "Sprite.hpp"

Sprite::Sprite() {
	// TODO Auto-generated constructor stub

}

Sprite::Sprite(const char *file, int x, int y, int dx, int dy) {
	//TODO: do some value-checking for consistency
	this->x = x;
	this->y = y;
	this->dx = dx;
	this->dy = dy;

}

Sprite::~Sprite() {
	// TODO Auto-generated destructor stub
	SDL_FreeSurface(surf);
}

/**
 * Draws the Sprite on a destination surface
 * @param dest a pointer to the destination surface
 */
void Sprite::draw(SDL_Surface *dest){

}

/**
 * Move the Sprite by one time unit (ie once its dx and dy)
 */
void Sprite::move() {
	x += dx;
	y += dy;
}

/**
 * A collision detector
 * @param obj the potential obstacle
 * @return true if there was a collision, false otherwise
 */
bool Sprite::collidesWith(SDL_Surface *obj) {
	return false;
}


