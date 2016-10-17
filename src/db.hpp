/**
 * \file db.hpp
 * \brief Database handling methods, used when acting as a server
 * \version 0.1a
 * \author G. B.
 * \date 14/09/2016
 */

/* This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0.
 * If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/.
 *
 * This Source Code Form is "Incompatible With Secondary Licenses",
 * as defined by the Mozilla Public License, v. 2.0.
 */
 
#ifndef _H_DB_
#define _H_DB_
 
int LB_initDB();
bool isDBOpen();
void LB_closeDB();

int LB_createPlayer(string name, string password);
int LB_editPlayer(LB_Player &player);
LB_Player* LB_getPlayer(string name);
bool LB_authenticatePlayer(string name, string password);

int LB_createRoom(LB_Room &targetRoom);
LB_Room* LB_getRoom(int number);
int LB_editRoom(LB_Room &newRoom);
int LB_deleteRoom(int number);

#endif
