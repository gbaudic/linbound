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

#include <libintl.h>
#include <locale.h>
 
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <guisan.hpp>
#include <guisan/sdl.hpp>

using namespace gcn;

//TODO: extern guisan objects (gui, container, imageloader...)

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
	Label* lbl_buttonHelp;
	Label* lbl_version;
	ImageButton* btn_settings;
	ImageButton* btn_play;
	ImageButton* btn_back;
	ImageButton* btn_localPlay;
	ImageButton* btn_onlinePlay;
	ImageButton* btn_quit;
	ImageButton* btn_credits;
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
	lbl_buttonHelp = new Label("");
	lbl_buttonHelp->setPosition(70, 400);

	lbl_version = new Label("Version ");
	lbl_version->setPosition(20, 570);

	btn_settings = new ImageButton("./res/menu/settings.png");
	btn_settings->setCaption(gettext("Settings"));
	btn_settings->setPosition(240, 220);

	btn_play = new ImageButton("./res/menu/newgame.png");
	btn_play->setCaption(gettext("New game"));
	btn_play->setPosition(70, 220);

	btn_localPlay = new ImageButton("./res/menu/localgame.png");
	btn_localPlay->setCaption(gettext("New local game"));
	btn_localPlay->setPosition(240, 220);
	btn_localPlay->setVisible(false);

	btn_onlinePlay = new ImageButton("./res/menu/webgame.png");
	btn_onlinePlay->setCaption(gettext("New online/network game"));
	btn_onlinePlay->setPosition(410, 220);
	btn_onlinePlay->setVisible(false);

	btn_back = new ImageButton("./res/menu/back.png");
	btn_back->setCaption(gettext("Back"));
	btn_back->setPosition(70, 220);
	btn_back->setVisible(false);

	btn_quit = new ImageButton("./res/menu/quit.png");
	btn_quit->setCaption(gettext("Quit Linbound"));
	btn_quit->setPosition(570, 220);

	btn_credits = new ImageButton("./res/menu/credits.png");
	btn_credits->setCaption(gettext("Credits"));
	btn_credits->setPosition(410, 220);
}

LB_Menu::~LB_Menu() {
	SDL_DestroyTexture(background);

	//TODO: delete widgets
	delete lbl_buttonHelp;
	delete lbl_version;
	delete btn_settings;
	delete btn_play;
	delete btn_localPlay;
	delete btn_onlinePlay;
	delete btn_back;
	delete btn_quit;
	delete btn_credits;
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
