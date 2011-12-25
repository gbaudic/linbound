#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <SDL/SDL.h>
#include "map.hpp"
using namespace std;

LB_Map::LB_Map(std::string name, std::string background, std::string foregroundA, std::string foregroundB)
{
    //Fill the SDL_Surfaces with the images associated with the paths given as arguments
    this->name = name;
}

LB_Map::~LB_Map()
{
    //Free the SDL_Surfaces properly
    SDL_FreeSurface(background);
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
