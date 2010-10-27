/**
 * \file update.hpp
 * \brief Header for update functions
 * 		  Part of LinBound game
 * \author G. B.
 * \date 24/10/2010
 */
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
