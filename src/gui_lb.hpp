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

const Uint16 BALLOON_RADIUS = 5; //! radius for rounded corners, in pixels
const Uint32 BALLOON_TIMEOUT = 5000; //! time in milliseconds

/**
 * @brief An improved button to represent a room
 */
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

/**
 * @brief A balloon to hold text for a user message
 */
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
	Uint32 creationTime; //! needed
};

/**
 * A subwindow to conduct a chat with one of your in-game friends
 */
class LB_ChatWindow : public gcn::ActionListener {
public:
	LB_ChatWindow(std::string friendName);
	LB_ChatWindow(std::string friendName, std::string message);
	~LB_ChatWindow();
	void setVisible(bool visible);
	void addMessage(std::string author, std::string message);
	void action(const gcn::ActionEvent &actionEvent);
	std::string getRecipientName();

private:
	gcn::Window chatWindow;
	gcn::TextField tf_msg;
	gcn::ScrollArea sa_scroll;
	gcn::TextBox tb_chat;
	gcn::Button btn_close;
	gcn::Button btn_send;
	std::string recipient; //! necessary if caption displays other infos
};

/**
 * A subwindow to display the credits directly from the menu
 * Data will be fetched from the existing AUTHORS file
 */
class CreditsWindow {
public:
	CreditsWindow();
	~CreditsWindow();
	void setVisible(bool visible);

private:
	gcn::Window creditsWindow;
	gcn::TextBox tb_text;
	gcn::ScrollArea sa_scroll;
	gcn::Button btn_close;
};

/**
 * The subwindow which opens in the server list to let you login to a server
 */
class LoginWindow {
public:
	LoginWindow();
	~LoginWindow();
	void setVisible(bool visible);
	std::string getLogin();
	std::string getPassword();
	void setStatus(std::string status);

private:
	gcn::Window loginWindow;
	gcn::Label lbl_status;
	gcn::TextField tf_login;
	gcn::PasswordField tf_password;
	gcn::Button btn_login, btn_cancel;
};

/**
 *  A subwindow to create a new room
 */
class CreateRoomWindow {
public:
	CreateRoomWindow();
	~CreateRoomWindow();
	void setVisible(bool visible);
	
private:
	gcn::Window createRoomWindow;
	gcn::Label lbl_name, lbl_password, lbl_sdType, lbl_sdTurns;
	gcn::TextField tf_name, tf_password;
	gcn::RadioButton rb_bigbomb, rb_double, rb_doubleplus, rb_ss; //SuddenDeathType
	gcn::RadioButton rb_40, rb_56, rb_72; //nb of turns
	gcn::Button btn_ok, btn_cancel;
	
};

#endif
