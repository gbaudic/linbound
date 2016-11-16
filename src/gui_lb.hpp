/**
 * \file gui_lb.hpp
 * \brief GUI additions to guisan, specific to LinBound
 * \author G. B.
 * \version 0.1a
 * \date 24/10/2010
 */
/* This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. 
 * If a copy of the MPL was not distributed with this file, 
 * You can obtain one at http://mozilla.org/MPL/2.0/.
 * 
 * This Source Code Form is “Incompatible With Secondary Licenses”, 
 * as defined by the Mozilla Public License, v. 2.0.
 */

#ifndef _H_GUI_LB_
#define _H_GUI_LB_

#include <vector>
#include <SDL2/SDL.h>
#include <guisan.hpp>
#include <guisan/sdl.hpp>
#include "room.hpp"

const Uint16 BALLOON_RADIUS = 5; //! radius for rounded corners
const Uint32 BALLOON_TIMEOUT = 5000; //! time in milliseconds

class LB_RoomButton : public gcn::ImageButton {
public:
	LB_RoomButton(LB_Room* room);
	virtual ~LB_RoomButton();
	virtual void draw(gcn::Graphics* graphics);
	Uint16 getNumber();

private:
	LB_Room* mRoom;
	gcn::Image* mStatusImages;
};

class LB_MessageBalloon {
public:
	LB_MessageBalloon(std::string text);
	~LB_MessageBalloon();
	void draw(SDL_Renderer* target, Uint16 x, Uint16 y);
	
private:
	std::vector<SDL_Surface*> textLines;
	std::vector<SDL_Texture*> textTextures;
	Uint16 width, height;
	Uint8 lines;
	Uint32 creationTime;
};

/**
 * A subwindow to conduct a chat with one of your in-game friends
 */
class LB_ChatWindow {
public:
	LB_ChatWindow(std::string friendName);
	LB_ChatWindow(std::string friendName, std::string message);
	void setVisible(bool visible);
	void addMessage(std::string author, std::string message);
	std::string getRecipientName();

private:
	gcn::Window chatWindow;
	gcn::TextField tf_msg;
	gcn::ScrollArea sa_scroll;
	gcn::TextBox tb_chat;
	gcn::Button btn_close;
	gcn::Button btn_send;
};

#endif
