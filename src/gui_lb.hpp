/**
 * \file gui_lb.hpp
 * \brief Header for the GUI subsystem
 * \author G. B.
 * \version 0.1a
 * \date 24/10/2010
 */
/*    This library is free software; you can redistribute it and/or
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

#ifndef _H_GUI_LB_
#define _H_GUI_LB_

//Here we will define some constants for the error display function
//These strange values are directly inspired from Micro$oft Visual Basic(tm)
const int LB_MSG_CRITICAL = 16;
const int LB_MSG_QUESTION = 32;
const int LB_MSG_WARNING = 48;
const int LB_MSG_INFO = 64;
const int LB_MSG_TEXTRQ = 80;

const int LB_MSG_OKONLY = 17;
const int LB_MSG_OKCANCEL = 18;
const int LB_MSG_YESNO = 19;
const int LB_MSG_RETRYCANCEL = 20;
const int LB_MSG_CANCEL = 21;

#endif
