/**
 * sprite.cpp
 *
 *  @date 23/02/2012
 *  @author G. B.
 */


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
    http://robloach.net */

#include <cmath>

#include "Sprite.hpp"

/* returns maximum or minimum of number */
#define SDL_COLLIDE_MAX(a,b)	((a > b) ? a : b)
#define SDL_COLLIDE_MIN(a,b)	((a < b) ? a : b)

#define PI 3.14159265

Sprite::Sprite() {
	// TODO Auto-generated constructor stub

}

Sprite::Sprite(const char *file, int x, int y, int dx, int dy) {
	//TODO: do some value-checking for consistency
	this->x = x;
	this->y = y;
	this->dx = dx;
	this->dy = dy;

	surf = IMG_Load(file);

	text = NULL;
	rotated = NULL;
	this->rend = NULL;
	isVisible = true;

	creationTime = SDL_GetTicks();
	timeToLive = 0;
	
	rArea.x = 0; rArea.y = 0;
	rArea.w = surf->w; rArea.h = surf->h;

}

Sprite::~Sprite() {
	SDL_FreeSurface(surf);
	SDL_FreeSurface(rotated);
	SDL_DestroyTexture(text);
}

/**
 * Draws the Sprite on a destination surface
 * @param dest a pointer to the destination surface
 */
void Sprite::draw(SDL_Surface *dest){
	SDL_Rect destRec;

	destRec.x = x;
	destRec.y = y;
	destRec.w = rArea.w;
	destRec.h = rArea.h;

	SDL_BlitSurface(surf, &rArea, dest, &destRec);
}

void Sprite::draw(SDL_Renderer* rend, Sint16 xOffset, Sint16 yOffset){
	if(surf != NULL){
		text = SDL_CreateTextureFromSurface(rend, surf);
	}
	this->rend = rend;

	SDL_Rect destRec;

	destRec.x = x - xOffset;
	destRec.y = y - yOffset;
	destRec.w = rArea.w;
	destRec.h = rArea.h;
	
	SDL_RenderCopy(rend, text, &rArea, &destRec);
}

/**
 * Move the Sprite by one time unit (ie once its dx and dy)
 */
void Sprite::move() {
	x += dx;
	y += dy;
}

SDL_Rect* Sprite::getRect(){
	return &rArea;
}

Sint16 Sprite::getCenterX() {
	return x + rArea.w;
}

Sint16 Sprite::getCenterY() {
	return y + rArea.h;
}

/**
 * Returns the angle needed to align with the speed vector, in degrees
 * Reference is the horizontal line, this function ignores any previous rotations
 */
Sint16 Sprite::getSpeedAngle() {
	if(dx == 0){
		if(dy == 0){
			return 0;
		} else {
			return (dy < 0 ? 90 : -90);
		}
	} else {
		double angleRad = atan2(-dy,dx);
		return angleRad * 180 / PI;
	}
}

/**
 *  @param dest the SDL_Surface to blit to
 */
void AnimatedSprite::draw(SDL_Surface *dest) {
		SDL_Rect destRec;
		Uint32 currentTime = SDL_GetTicks();

		rArea.x = src_x + src_w*(((currentTime - creationTime) / refreshRate) % nbAFrames);

		destRec.x = x;
		destRec.y = y;
		destRec.w = rArea.w;
		destRec.h = rArea.h;

		SDL_BlitSurface(surf, &rArea, dest, &destRec);
}

/**
	SDL surface test if offset (u,v) is a transparent pixel
*/
bool SDL_CollideTransparentPixel(SDL_Surface *surface , int u , int v)
{
	if(SDL_MUSTLOCK(surface))
		SDL_LockSurface(surface);
	/*assert that (u,v) offsets lie within surface*/
	SDL_assert_release((u < surface->w) && (v < surface->h));

	int bpp = surface->format->BytesPerPixel;
	/*here p is the address to the pixel we want to retrieve*/
	Uint8 *p = (Uint8 *)surface->pixels + v * surface->pitch + u * bpp;

	Uint32 pixelcolor;

	switch(bpp)
	{
		case(1):
			pixelcolor = *p;
		break;

		case(2):
			pixelcolor = *(Uint16 *)p;
		break;

		case(3):
			if(SDL_BYTEORDER == SDL_BIG_ENDIAN)
				pixelcolor = p[0] << 16 | p[1] << 8 | p[2];
			else
				pixelcolor = p[0] | p[1] << 8 | p[2] << 16;
		break;

		case(4):
			pixelcolor = *(Uint32 *)p;
		break;
	}

	if(SDL_MUSTLOCK(surface))
		SDL_UnlockSurface(surface);
	Uint32 colkey = 0;
	SDL_GetColorKey(surface,&colkey);
	/* test whether pixels color == color of transparent pixels for that surface */
	return (pixelcolor == colkey);
}

/**
	SDL pixel perfect collision test
*/
bool SDL_CollidePixel(SDL_Surface *as , int ax , int ay ,
                       SDL_Surface *bs , int bx , int by, int skip)
{
	/*a - bottom right co-ordinates in world space*/
	int ax1 = ax + as->w - 1;
	int ay1 = ay + as->h - 1;

	/*b - bottom right co-ordinates in world space*/
	int bx1 = bx + bs->w - 1;
	int by1 = by + bs->h - 1;

	/*check if bounding boxes intersect*/
	if((bx1 < ax) || (ax1 < bx))
		return false;
	if((by1 < ay) || (ay1 < by))
		return false;

/*Now lets make the bounding box for which we check for a pixel collision*/

	/*To get the bounding box we do
            Ax1,Ay1______________
                |                |
                |                |
                |                |
                |    Bx1,By1____________
                |        |       |      |
                |        |       |      |
                |________|_______|      |
                         |    Ax2,Ay2   |
                         |              |
                         |              |
                         |___________Bx2,By2

	To find that overlap we find the biggest left hand coordinate
	AND the smallest right hand coordinate

	To find it for y we do the biggest top y value
	AND the smallest bottom y value

	Therefore the overlap here is Bx1,By1 --> Ax2,Ay2

	Remember	Ax2 = Ax1 + SA->w
			Bx2 = Bx1 + SB->w

			Ay2 = Ay1 + SA->h
			By2 = By1 + SB->h
	*/

	/*now we loop round every pixel in area of
	intersection
		if 2 pixels alpha values on 2 surfaces at the
		same place != 0 then we have a collision*/
	int xstart = SDL_COLLIDE_MAX(ax,bx);
	int xend = SDL_COLLIDE_MIN(ax1,bx1);

	int ystart = SDL_COLLIDE_MAX(ay,by);
	int yend = SDL_COLLIDE_MIN(ay1,by1);

	for(int y = ystart ; y <= yend ; y += skip)
	{
		for(int x = xstart ; x <= xend ; x += skip)
		{
			/*compute offsets for surface
			before pass to TransparentPixel test*/
			if(!SDL_CollideTransparentPixel(as , x-ax , y-ay)
			&& !SDL_CollideTransparentPixel(bs , x-bx , y-by))
				return true;
		}
	}

	return false;
}

/*
	SDL bounding box collision test
*/
bool SDL_CollideBoundingBox(SDL_Surface *sa , int ax , int ay ,
                             SDL_Surface *sb , int bx , int by)
{
	if(bx + sb->w < ax)	return false;	//just checking if their
	if(bx > ax + sa->w)	return false;	//bounding boxes even touch

	if(by + sb->h < ay)	return false;
	if(by > ay + sa->h)	return false;

	return true;	//bounding boxes intersect
}

/*
	SDL bounding box collision tests (works on SDL_Rect's)
*/
bool SDL_CollideBoundingBox(SDL_Rect a , SDL_Rect b)
{
	if(b.x + b.w < a.x)	return false;	//just checking if their
	if(b.x > a.x + a.w)	return false;	//bounding boxes even touch

	if(b.y + b.h < a.y)	return false;
	if(b.y > a.y + a.h)	return false;

	return true;				//bounding boxes intersect
}

/*
	tests whether 2 circles intersect

	circle1 : centre (x1,y1) with radius r1
	circle2 : centre (x2,y2) with radius r2

	(allow distance between circles of offset)
*/
bool SDL_CollideBoundingCircle(int x1 , int y1 , int r1 ,
                                 int x2 , int y2 , int r2 , int offset)
{
	int xdiff = x2 - x1;	// x plane difference
	int ydiff = y2 - y1;	// y plane difference

	/* distance between the circles centres squared */
	int dcentre_sq = (ydiff*ydiff) + (xdiff*xdiff);

	/* calculate sum of radiuses squared */
	int r_sum_sq = r1 + r2;	// square on seperate line, so
	r_sum_sq *= r_sum_sq;	// dont recompute r1 + r2

	return (dcentre_sq - r_sum_sq <= (offset*offset));
}

/*
	a circle intersection detection algorithm that will use
	the position of the centre of the surface as the centre of
	the circle and approximate the radius using the width and height
	of the surface (for example a rect of 4x6 would have r = 2.5).
*/
bool SDL_CollideBoundingCircle(SDL_Surface *a , int x1 , int y1 ,
                                 SDL_Surface *b , int x2 , int y2 ,
                                   int offset)
{
	/* if radius is not specified
	we approximate them using SDL_Surface's
	width and height average and divide by 2*/
	int r1 = (a->w + a->h) / 4;	// same as / 2) / 2;
	int r2 = (b->w + b->h) / 4;

	x1 += a->w / 2;		// offset x and y
	y1 += a->h / 2;		// co-ordinates into
				// centre of image
	x2 += b->w / 2;
	y2 += b->h / 2;

	return SDL_CollideBoundingCircle(x1,y1,r1,x2,y2,r2,offset);
}


