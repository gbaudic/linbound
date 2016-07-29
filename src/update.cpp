/**
 * \file update.cpp
 * \brief Update functions
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

#include <libintl.h>
#include <locale.h>

#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <string>
#include <SDL2/SDL.h>
#include <SDL2/SDL_net.h>
//Here please put the cURL easy header
#include "update.hpp"
using namespace std;

extern char *ErrorString;
char* StringCat(char *string1, char *string2, char *string3);

/*char* StringCat(char *string1, char *string2, char *string3)
{
 	 int length = strlen(string1) + strlen(string2) + strlen(string3);
 	 char* tmpcat[length] = new char;
 	 strncpy(tmpcat, string1, strlen(string1));
 	 strncat(tmpcat, string2, strlen(string2));
 	 strncat(tmpcat, string3, strlen(string3));

 	 return tmpcat;
}*/

/**
 * Checks if the download is correct or not
 * \param filename the name of the file to check
 * \param MD5sum the md5 it is supposed to have
 * \return 0 if md5 check succeeds, -1 otherwise
 */
int LB_Update_FileIsSafe(char *filename, char *MD5sum)
{

	//If the algorithm failed, notify the user and terminate the function
/*	if (MD5File(filename) != NULL){
		char *MD5FileSum = MD5File(filename);
	} else {
		//StringCat("MD5 check for file ", filename, " failed.");
		//char *MD5FileSum = 0;
		SDL_SetError(ErrorString);
		return -1;
	}

	//Now it has succeeded, check the returned value
	if (strncmp(MD5File(filename), MD5sum, 32) == 0){
		//stricmp??
		//Return 0 and no error code if the files are the same
		return 0;
	}*/

	//Return -1 by default ; this shows that the file is different and has to be downloaded again
	return -1;
}

/**
 * The main update function
 * \return 0 if success, -1 otherwise
 */
int LB_Update()
{
	/*  **Main update function**
	Workflow :
	  -Check for available updates
	  -Determines which updates have to be grabbed
	  -Display total information
	  -Grab the files once by once, check their MD5 and replace the versions in the VERSION file */


	Uint16 iUpdateTotalSize;
	Uint8 iUpdateTotalFiles;

	return 0;
}
