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

#include <guisan.hpp>
#include <guisan/sdl.hpp>
#include "room.hpp"

const Uint16 BALLOON_RADIUS = 5; //for rounded corners

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

void drawMessageBalloon(SDL_Surface* message, Uint16 x, Uint16 y, SDL_Renderer *target);

#endif
