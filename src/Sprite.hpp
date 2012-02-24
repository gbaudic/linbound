/**
 * Sprite.h
 *
 *  	@date 23/02/2012
 *      @author G. B.
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

#ifndef SPRITE_H_
#define SPRITE_H_

#include <SDL/SDL.h>

//TODO: take some inspiration for this Sprite class from SDLSprite class (no copy&paste because it's GPLed)
//TODO: for collisions use SDL_collide directly, MIT license is OK with LGPL

/**
 * A generic sprite, as used classically in 2D animation
 */
class Sprite {
public:

	Uint16 x; //Position coordinates
	Uint16 y;
	Uint16 dx; //Motion vector coordinates
	Uint16 dy;

	//Uint8 orderZ; //may be useful to sort blitting operations in a suitable order
	bool isVisible;

	Uint32 creationTime; //time origin for time-related tasks (limited lifespan, animation...)
	Uint32 timeToLive;

	Sprite();
	Sprite(const char* file, int x, int y, int dx, int dy);
	virtual ~Sprite();
	virtual void draw(SDL_Surface* dest);
	void move();
	bool collidesWith(SDL_Surface* obj);

private:
	SDL_Surface* surf;
	SDL_Rect rArea;
};

/**
 * A Sprite with an animated view
 */
class AnimatedSprite : public Sprite {
public :
	void draw(SDL_Surface* dest);
private :
	Uint16 src_x; //Coordinates of top left hand corner of first frame in the image file
	Uint16 src_y;
	Uint16 src_w; //Width and height -- must be the same for all frames
	Uint16 src_h;

	Uint8 nbAFrames; //Total number of frames for the animation
	Uint16 refreshRate; //Display time for each frame (constant, but could be made variable as in *.gif files)
};

/**
 * A Sprite with a mass to use some physics (ie gravity) with it
 */
class MassiveSprite : public Sprite {

public:
	Uint16 mass;
};
#endif /* SPRITE_H_ */
