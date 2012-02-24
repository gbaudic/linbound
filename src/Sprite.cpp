/**
 * Sprite.cpp
 *
 *  @date 23/02/2012
 *  @author G. B.
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

void AnimatedSprite::draw(SDL_Surface *dest)
{

}




