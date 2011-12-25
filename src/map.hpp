
#ifndef _H_MAP_
#define _H_MAP_

class LB_Map
{
    protected:
    SDL_Surface* background;
    SDL_Surface* foregroundA;
    SDL_Surface* foregroundB;

    SDL_Surface* previewA;
    SDL_Surface* previewB;

    bool has2Sides;
    bool isASide;

    std::string name;

    //Methods
    public:
    LB_Map(std::string name, std::string background, std::string foregroundA, std::string foregroundB = "");
    ~LB_Map();

    void setASide(bool isASide);
    bool getASide() const;

    void makeDamage();
    void correctAfterDamage();
};

#endif
