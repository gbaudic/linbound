/* This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. 
 * If a copy of the MPL was not distributed with this file, 
 * You can obtain one at http://mozilla.org/MPL/2.0/.
 * 
 * This Source Code Form is “Incompatible With Secondary Licenses”, 
 * as defined by the Mozilla Public License, v. 2.0.
 */


#ifndef _H_MAP_
#define _H_MAP_

#include <string>
#include <vector> //Verify if best structure for this
#include "sprite.hpp"

class LB_MapBackground
{
public:
	LB_MapBackground();
	~LB_MapBackground();

	void refresh();
	SDL_Surface* getView();

private:
	SDL_Surface* staticPart;
	SDL_Surface* rendering;

	std::vector<sprite> animParts;
};

class LB_Map
{
    private:
    LB_MapBackground background;
    SDL_Surface* foregroundA;
    SDL_Surface* foregroundB;

    SDL_Texture* previewSmall; //in server view
    SDL_Texture* previewMedium; //in room view before loading
    SDL_Texture* previewA; //in room view while loading
    SDL_Texture* previewB;

    bool has2Sides;
    bool isASide;

    std::string name;

    int viewportX; //2D coordinates of the viewport
    int viewportY;

    //Methods
    public:
    LB_Map(std::string name, LB_MapBackground background, std::string foregroundA, std::string foregroundB = "");
    ~LB_Map();

    void setASide(bool isASide);
    bool getASide() const;

    void makeDamage(Sint16 x, Sint16 y, Sint16 radius); //For first versions we will express damages with circular areas
    void correctAfterDamage(Sint16 x, Sint16 y, Sint16 radius);
};

#endif //_H_MAP_
