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

/*		Collision-related methods come from the SDL_collide library
  	SDL_Collide:  A 2D collision detection library for use with SDL

    MIT License
    Copyright 2005-2006 SDL_collide Team, http://sdl-collide.sourceforge.net
    All rights reserved.

    Permission is hereby granted, free of charge, to any person obtaining a copy
    of this software and associated documentation files (the "Software"), to deal
    in the Software without restriction, including without limitation the rights
    to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
    copies of the Software, and to permit persons to whom the Software is
    furnished to do so, subject to the following conditions:

    The above copyright notice and this permission notice shall be included in all
    copies or substantial portions of the Software.

    THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
    IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
    FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
    AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
    LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
    OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
    SOFTWARE.

    Amir Taaki
    genjix@gmail.com

    Rob Loach
    http://robloach.net*/

#ifndef SPRITE_H_
#define SPRITE_H_

#include <SDL/SDL.h>

//TODO: take some inspiration for this Sprite class from SDLSprite class (no copy&paste because it's GPLed)

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

	/**
	 * SDL surface test if offset (u,v) is a transparent pixel
	 */
	bool SDL_CollideTransparentPixel(SDL_Surface *surface, int u, int v);

	/**
	 * Pixel-perfect collision between two surfaces.
	 *
	 * @param SA the first surface to check
	 * @param Ax1 the top-left X-coordinate of surface @a SA
	 * @param Ay1 the top-left Y-coordinate of surface @a SA
	 * @param SB the second surface to check
	 * @param Bx1 the top-left X-coordinate of surface @a SB
	 * @param By1 the top-left Y-coordinate of surface @a SB
	 * @param skip how many pixels the looping test should skip.
	 *             1 is a truly perfect pixel test, but a value
	 *             of 4 should be fine.
	 *             this parameter is here to speed up the test at
	 *             the expense of accuracy.
	 *
	 * @return non-zero on collision, 0 otherwise
	 */
	bool SDL_CollidePixel(SDL_Surface *as, int ax, int ay, SDL_Surface *bs, int bx, int by, int skip = 4);

	/**
	 * Bounding-box collision between two surfaces.
	 *
	 * @param SA the first surface to check
	 * @param Ax1 the top-left X-coordinate of surface @a SA
	 * @param Ay1 the top-left Y-coordinate of surface @a SA
	 * @param SB the second surface to check
	 * @param Bx1 the top-left X-coordinate of surface @a SB
	 * @param By1 the top-left Y-coordinate of surface @a SB
	 *
	 * @return non-zero on collision, 0 otherwise
	 */
	bool SDL_CollideBoundingBox(SDL_Surface *sa, int ax, int ay, SDL_Surface *sb, int bx, int by);

	/**
	 * Bounding-box collision between two rectangles.
	 *
	 * @param A the first rectangle to check
	 * @param B the second rectangle to check
	 *
	 * @return non-zero on collision, 0 otherwise
	 */
	bool SDL_CollideBoundingBox(SDL_Rect a, SDL_Rect b);

	/**
	 * tests whether 2 circles intersect
	 *
	 * circle1 : centre (x1,y1) with radius r1
	 * circle2 : centre (x2,y2) with radius r2
	 *
	 * (allow distance between circles of offset)
	 */
	bool SDL_CollideBoundingCircle(int x1, int y1, int r1, int x2, int y2, int r2, int offset);

	/**
	 * a circle intersection detection algorithm that will use
	 * the position of the center of the surface as the center of
	 * the circle and approximate the radius using the width and height
	 * of the surface (for example a rect of 4x6 would have r = 2.5).
	 */
	bool SDL_CollideBoundingCircle(SDL_Surface *a, int x1, int y1, SDL_Surface *b, int x2, int y2, int offset);

#endif /* SPRITE_H_ */
