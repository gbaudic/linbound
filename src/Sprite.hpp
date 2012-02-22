/*
 * Sprite.h
 *
 *  Created on: 23 févr. 2012
 *      Author: podgy
 */

#ifndef SPRITE_H_
#define SPRITE_H_

#include <SDL/SDL.h>

/**
 * A generic sprite as used classically in 2D animation
 */
class Sprite {
public:

	Uint16 x;
	Uint16 y;
	Uint16 dx;
	Uint16 dy;

	Sprite();
	Sprite(const char* file, int x, int y, int dx, int dy);
	virtual ~Sprite();
	void draw(SDL_Surface* dest);
	void move();
	bool collidesWith(SDL_Surface *obj);

private:
	SDL_Surface* surf;
};

/**
 * A Sprite with a mass to use some physics (ie gravity) with it
 */
class MassiveSprite : public Sprite {

public:
	Uint16 mass;
};
#endif /* SPRITE_H_ */
