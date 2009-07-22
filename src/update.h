//Header for update functions
//Part of LinBound game
// (C) Copyright 2007-2009 G. B.

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

#pragma once

#define LB_MAX_UPDATE_ATTEMPTS 2

class LB_UpdateObject
{
	public:
		char LocalPath;
		char RemotePath;
		
		Uint32 LocalVersion;
		Uint32 RemoteVersion;
		
		Uint16 TotalSize;
		Uint16 DLed_Size;
		Uint8 Progress;
		Uint8 DL_Attempts;
};
