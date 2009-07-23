//Initialization functions
//Part of LinBound game
//(C) Copyright 2007-2009 G. B.

/*        This library is free software; you can redistribute it and/or
    modify it under the terms of the GNU Lesser General Public
    License as published by the Free Software Foundation; either
    version 2.1 of the License, or (at your option) any later version.

    This library is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
    Lesser General Public License for more details.

    You should have received a copy of the GNU Lesser General Public
    License along with this library; if not, write to the Free Software
    Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA */

#include <libintl.h>
#include <locale.h>

#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_net.h>
#include <SDL/SDL_ttf.h>
#include <SDL/SDL_mixer.h>
//#include <ssl.h> -- using cURL will make this include unnecessary
#include "init.hpp"
using namespace std;

TTF_Font *font;
int fontsize = 12;

int LB_Init()
{
	//Initializing SDL
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) != 0) {
		cout << "FATAL : Cannot init SDL : " << SDL_GetError() << endl;
		return 1;
	}

	//Initializing SDL_ttf, needed for text display
	if (TTF_Init() != 0){
		cout << "FATAL : Cannot init SDL_ttf " << SDL_GetError() << endl;
		IsTTFEnabled = false;
		return 1;
	}
	
	//TTF is initialized correctly, so let's load the font
	font = TTF_OpenFont("./resources/LiberationSans-Regular.ttf", fontsize);
	
	//Set the keyboard repeating delay : after 700 ms, every 200 ms
	SDL_EnableKeyRepeat(700, 200);
	//Hide the black cursor to replace it with a colored one
	SDL_ShowCursor(0);
	
	//Give an icon to the window
	SDL_WM_SetIcon(IMG_Load("linbound.gif"), NULL);
	
	return 0;
}

int LB_ParseOptions(int argc, char *argv[])
{

}

int LB_InitNetwork(Uint8 *imode)
{
	
	//if (SDLNet_Init() != 0){
	//	IsNETEnabled = false;
	//	return 1;
	//}
}

/*int LB_InitSound()
{
 	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 1024) == -1) {
    cout << "Mix_OpenAudio: " << Mix_GetError() << endl;
    return -1;
}

}*/

void LB_Quit()
{
	
	SDL_ShowCursor(1);
	
	if (IsTTFEnabled == true){
		TTF_CloseFont(font);
		TTF_Quit();
	}

	//if (IsNETEnabled == true){
	//	SDLNet_Quit();
	//}
	
	//Mix_CloseAudio;
	
	SDL_Quit();
	
}
