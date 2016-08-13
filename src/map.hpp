/* This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. 
 * If a copy of the MPL was not distributed with this file, 
 * You can obtain one at http://mozilla.org/MPL/2.0/.
 * 
 * This Source Code Form is “Incompatible With Secondary Licenses”, 
 * as defined by the Mozilla Public License, v. 2.0.
 */


#ifndef _H_MAP_
#define _H_MAP_

class LB_MapBackground
{
public:
	LB_MapBackground(std::string staticPartPath, std::vector<std::string> animPartsPaths);
	~LB_MapBackground();

	int getWidth() const;
	int getHeight() const;
	
	void refresh();
	SDL_Surface* getView();

private:
	SDL_Surface* staticPart;
	SDL_Surface* rendering;

	std::vector<Sprite> animParts;
};

class LB_Map
{
    private:
    LB_MapBackground* background;
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
	
	double parallaxX; //Factors for parallax between fore- and background
	double parallaxY;

    //Methods
    public:
    LB_Map(std::string name, LB_MapBackground* background, std::string foregroundA, std::string foregroundB = "");
    ~LB_Map();

    void setASide(bool isASide);
    bool getASide() const;
    std::string getName() const;
	
	void activate();
	void deactivate();

    void makeDamage(Sint16 x, Sint16 y, Sint16 radius); //For first versions we will express damages with circular areas
    void correctAfterDamage(Sint16 x, Sint16 y, Sint16 radius);
};

#endif //_H_MAP_
