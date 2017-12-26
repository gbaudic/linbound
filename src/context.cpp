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
#include "context.hpp"

using namespace gcn;


LB_Context::LB_Context(SDL_Renderer* renderer,
		LB_Context::Context context){
	_renderer = renderer;
	_context = context;
}

LB_Context::~LB_Context() {
}


LB_Context::Context LB_Context::getContext() const {
	return _context;
}
