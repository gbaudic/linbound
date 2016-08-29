/**
 * \file init.hpp
 * \brief Header file for init functions
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

#ifndef _H_INIT_
#define _H_INIT_

const int CHANNELS = 2; //stereo audio
const Uint16 SERVER_PORT = 6545;

enum GameMode {MENU_MODE, SETTINGS_MODE, SERVER_VIEW_MODE, SERVER_LIST_MODE, ITEM_SHOP_MODE, LOBBY_MODE, ROOM_MODE};

//Prototypes
int LB_Init();
int LB_ParseOptions(int argc, char *argv[]);
int LB_InitNetwork(Uint8 *imode);
int LB_InitSound(int channels);
void LB_Quit();

#endif /* _H_INIT_ */
