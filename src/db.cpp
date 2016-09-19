/**
 * \file db.cpp
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

#include <iostream>
#include <string>
#include <sqlite3.h>
using namespace std;

sqlite3 *serverDB;

/**
 * Open the database file
 * \return 0 on success, non-zero on error
 */
int LB_initDB(){
	int result = sqlite3_open("linbound.db", &serverDB);
	if (result != SQLITE_OK){
		cout << "SQLite error: " << sqlite3_errmsg(serverDB) << endl;
		sqlite3_close(serverDB);
		return 1;
	}
	return 0;
}

/**
 * Wrapper for db closing
 */
void LB_closeDB(){
	sqlite3_close(serverDB);
}

/**
 * Add a new player in this server's database
 */
int LB_createPlayer(string name, string password){
    //TODO
    return 0;
}

/**
 * Try to enter a room
 */
int LB_getRoom(int number){
    //TODO
    return 0;
}

