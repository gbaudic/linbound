/**
 * \file update.hpp
 * \brief Header for update functions
 * 		  Part of LinBound game
 * \author G. B.
 * \date 24/10/2010
 */
/* This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. 
 * If a copy of the MPL was not distributed with this file, 
 * You can obtain one at http://mozilla.org/MPL/2.0/.
 * 
 * This Source Code Form is “Incompatible With Secondary Licenses”, 
 * as defined by the Mozilla Public License, v. 2.0.
 */


#ifndef _H_UPDATE_
#define _H_UPDATE_

const int LB_MAX_UPDATE_ATTEMPTS  = 2;

/**
 * \class LB_UpdateObject
 * Abstracts an update object
 */
class LB_UpdateObject
{
	public:
		char LocalPath[];
		char RemotePath[];
		
		Uint32 LocalVersion;
		Uint32 RemoteVersion;
		
		Uint16 TotalSize;
		Uint16 DLed_Size;
		Uint8 Progress;
		Uint8 DL_Attempts;
};

int LB_Update_FileIsSafe(char *filename, char *MD5sum);
int LB_Update();

#endif
