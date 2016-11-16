/**
 * \file menu.hpp
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

#ifndef _H_MENU_
#define _H_MENU_

#include "context.hpp"
#include "settings.hpp"

class LB_Menu : public LB_Context, public gcn::ActionListener {
	/* Note: abusing multiple inheritance of C++ to make this class an ActionListener
	 * is the simplest idea I have had to overcome issues with a nested separate ActionListener class.
	 */
	public:
	LB_Menu(SDL_Renderer* renderer);
	~LB_Menu();
	void drawBackground();
	void drawMiddleground();
	void processEvent(SDL_Event event);
	void action(const gcn::ActionEvent& actionEvent);

	private:
	Uint8 mode; //0 for start menu, 1 for game buttons, 2 for credits
	SDL_Texture* background;
	gcn::Label* lbl_buttonHelp;
	gcn::Label* lbl_version;
	gcn::ImageButton* btn_settings;
	gcn::ImageButton* btn_play;
	gcn::ImageButton* btn_back;
	gcn::ImageButton* btn_localPlay;
	gcn::ImageButton* btn_onlinePlay;
	gcn::ImageButton* btn_quit;
	gcn::ImageButton* btn_credits;
	
	SettingsWindow win_settings;

};

#endif
