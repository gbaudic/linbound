/**
 * \file menu.cpp
 * \brief Class for the startup game menu
 * \version 0.1a
 * \author G. B.
 * \date 11/10/2016
 */
/* This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. 
 * If a copy of the MPL was not distributed with this file, 
 * You can obtain one at http://mozilla.org/MPL/2.0/.
 * 
 * This Source Code Form is “Incompatible With Secondary Licenses”, 
 * as defined by the Mozilla Public License, v. 2.0.
 */

#include <libintl.h>
#include <locale.h>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <guisan.hpp>
#include <guisan/sdl.hpp>
#include "sound.hpp" //may be useful
#include "utils.hpp"
#include "menu.hpp"

using namespace gcn;

void LB_Menu::action(const gcn::ActionEvent& actionEvent) {
	if (actionEvent.getId() == "newgame") {
		lbl_buttonHelp->setCaption(btn_play->getCaption());
		btn_localPlay->setVisible(true);
		btn_onlinePlay->setVisible(true);
		btn_back->setVisible(true);
		btn_settings->setVisible(false);
		btn_play->setVisible(false);
		btn_quit->setVisible(false);
		btn_credits->setVisible(false);
		mode = 1;
	} else if (actionEvent.getId() == "credits") {
		//Display an internal closable window with credits
		mode = 2;
	} else if (actionEvent.getId() == "quit") {
		//Generate a quit event for proper exiting
		SDL_Event quitevt;
		quitevt.type = SDL_QUIT;
		SDL_PushEvent(&quitevt);
	} else if (actionEvent.getId() == "back") {
		mode = 0;
		btn_localPlay->setVisible(false);
		btn_onlinePlay->setVisible(false);
		btn_back->setVisible(false);
		btn_settings->setVisible(true);
		btn_play->setVisible(true);
		btn_quit->setVisible(true);
		btn_credits->setVisible(true);
	}
}

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
	SDL_Surface* bck = IMG_Load("./res/menu/LB_menu.png");
	background = SDL_CreateTextureFromSurface(this->renderer, bck);
	SDL_FreeSurface(bck);
	
	mode = 0;
	Color transparent(0xff, 0, 0xff, 0xff);

	//Init GUI widgets
	lbl_buttonHelp = new Label("");
	lbl_buttonHelp->setPosition(70, 400);
	lbl_buttonHelp->setWidth(660);
	lbl_buttonHelp->setAlignment(gcn::Graphics::CENTER);

	lbl_version = new Label("Version "+getVersionString());
	lbl_version->setPosition(20, 570);

	btn_settings = new ImageButton("./res/menu/settings.png");
	btn_settings->setCaption(gettext("Settings"));
	btn_settings->setPosition(240, 220);
	btn_settings->setActionEventId("settings");
	btn_settings->addActionListener(this);
	btn_settings->setBorderSize(0);
	btn_settings->setBaseColor(transparent);
	btn_settings->adjustSize();

	btn_play = new ImageButton("./res/menu/newgame.png");
	btn_play->setCaption(gettext("New game"));
	btn_play->setPosition(70, 220);
	btn_play->setActionEventId("newgame");
	btn_play->addActionListener(this);
	btn_play->setBorderSize(0);
	btn_play->setBaseColor(transparent);
	btn_play->adjustSize();

	btn_localPlay = new ImageButton("./res/menu/localgame.png");
	btn_localPlay->setCaption(gettext("New local game"));
	btn_localPlay->setPosition(240, 220);
	btn_localPlay->setActionEventId("localgame");
	btn_localPlay->setVisible(false);
	btn_localPlay->addActionListener(this);
	btn_localPlay->setBorderSize(0);
	btn_localPlay->setBaseColor(transparent);
	btn_localPlay->adjustSize();

	btn_onlinePlay = new ImageButton("./res/menu/webgame.png");
	btn_onlinePlay->setCaption(gettext("New online/network game"));
	btn_onlinePlay->setPosition(410, 220);
	btn_onlinePlay->setActionEventId("onlinegame");
	btn_onlinePlay->setVisible(false);
	btn_onlinePlay->addActionListener(this);
	btn_onlinePlay->setBorderSize(0);
	btn_onlinePlay->setBaseColor(transparent);
	btn_onlinePlay->adjustSize();

	btn_back = new ImageButton("./res/menu/back.png");
	btn_back->setCaption(gettext("Back"));
	btn_back->setPosition(70, 220);
	btn_back->setActionEventId("back");
	btn_back->setVisible(false);
	btn_back->addActionListener(this);
	btn_back->setBorderSize(0);
	btn_back->setBaseColor(transparent);
	btn_back->adjustSize();

	btn_quit = new ImageButton("./res/menu/quit.png");
	btn_quit->setCaption(gettext("Quit Linbound"));
	btn_quit->setActionEventId("quit");
	btn_quit->setPosition(570, 220);
	btn_quit->addActionListener(this);
	btn_quit->setBorderSize(0);
	btn_quit->setBaseColor(transparent);
	btn_quit->adjustSize();

	btn_credits = new ImageButton("./res/menu/credits.png");
	btn_credits->setCaption(gettext("Credits"));
	btn_credits->setActionEventId("credits");
	btn_credits->setPosition(410, 220);
	btn_credits->addActionListener(this);
	btn_credits->setBorderSize(0);
	btn_credits->setBaseColor(transparent);
	btn_credits->adjustSize();

	//Add to container
	top->add(lbl_buttonHelp);
	top->add(lbl_version);
	top->add(btn_settings);
	top->add(btn_play);
	top->add(btn_localPlay);
	top->add(btn_onlinePlay);
	top->add(btn_back);
	top->add(btn_quit);
	top->add(btn_credits);
}

LB_Menu::~LB_Menu() {
	SDL_DestroyTexture(background);

	//Remove from container if not already done
	top->clear();

	//Delete widgets
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

