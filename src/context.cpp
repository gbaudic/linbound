/**
 * \file context.cpp
 * \brief Context definition, used to represent various views in game
 * \version 0.1a
 * \author G. B.
 * \date 25/08/2016
 */

/* This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. 
 * If a copy of the MPL was not distributed with this file, 
 * You can obtain one at http://mozilla.org/MPL/2.0/.
 * 
 * This Source Code Form is "Incompatible With Secondary Licenses", 
 * as defined by the Mozilla Public License, v. 2.0.
 */
 
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <guisan.hpp>
#include <guisan/sdl.hpp>

using namespace gcn;

class LB_Context {
	public:
	LB_Context(SDL_Renderer* renderer);
	virtual ~LB_Context() = 0;
	virtual void drawBackground() = 0;
	virtual void drawMiddleground() = 0;
	virtual void drawGUI() = 0;
	virtual void processEvent(SDL_Event event) = 0;
	
	protected:
	SDL_Renderer* renderer; //reference, this object is created and managed outside the class
	
};

//Start menu
class LB_Menu : public LB_Context {
	public:
	LB_Menu(SDL_Renderer* renderer);
	~LB_Menu();
	void drawBackground();
	void drawMiddleground();
	void drawGUI();
	void processEvent(SDL_Event event);
	
	private:
	SDL_Texture* background;
	Label lbl_buttonHelp;
	Label lbl_version;
	Button btn_settings;
	Button btn_play;
	Button btn_localPlay;
	Button btn_onlinePlay;
	Button btn_quit;
	Button btn_credits;
};

//Settings view

//Server list

//Room list

//Room lobby view

//Room game view

//Avatar item shop


LB_Context::LB_Context(SDL_Renderer* renderer){
	this->renderer = renderer;
}

LB_Context::~LB_Context() {};

void LB_Menu::processEvent(SDL_Event event) {
	//Mouse clicks = buttons, pass to guisan
	//Key presses: either game control (handle) or text typing (pass to guisan)
	switch(event.type){
		case SDL_MOUSEBUTTONDOWN:
		case SDL_MOUSEBUTTONUP: 
			break; //check if there is a click on a button
		default: break;
	}
}

LB_Menu::LB_Menu(SDL_Renderer* renderer) : LB_Context(renderer){
	SDL_Surface* bck = IMG_Load("./res/menu/menuLB.jpg");
	background = SDL_CreateTextureFromSurface(this->renderer, bck);
	SDL_FreeSurface(bck);
	//TODO: init GUI widgets
}

LB_Menu::~LB_Menu() {
	SDL_DestroyTexture(background);
}

void LB_Menu::drawBackground() {
	SDL_RenderCopy(renderer, background, NULL, NULL);
}

void LB_Menu::drawMiddleground() {
	return; //Nothing to draw
}

void LB_Menu::drawGUI() {
	return; //TBD
}
