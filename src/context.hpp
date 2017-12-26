/**
 * \file context.hpp
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
 
#ifndef _H_CONTEXT_
#define _H_CONTEXT_

extern gcn::Gui* gui;
extern gcn::Container* top;

class LB_Context {
public:
	enum Context {
		MAIN_MENU,
		SERVER_LIST,
		ROOM_LIST,
		ROOM_LOBBY,
		ROOM,
		SHOP
	};

	LB_Context(SDL_Renderer* renderer, Context context);
	virtual ~LB_Context() = 0;
	virtual void drawBackground() = 0;
	virtual void drawMiddleground() = 0;
	virtual void processEvent(SDL_Event event) = 0;
	Context getContext() const;
	
protected:
	SDL_Renderer* _renderer; //reference, this object is created and managed outside the class
	Context _context;
	
};

#endif
 
