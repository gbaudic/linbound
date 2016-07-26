/**
 * \file xml.cpp
 * \brief XML-related functions
 * 		  Part of LinBound game
 * \author G. B.
 * \version 0.1a
 * \date 26/07/2016
 */
/* This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0.
 * If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/.
 *
 * This Source Code Form is “Incompatible With Secondary Licenses”,
 * as defined by the Mozilla Public License, v. 2.0.
 */

#include "tinyxml2.h"

using namespace tinyxml2;
using namespace std;

/**
 * Load a map from the XML description file
 */
void LB_LoadMap(const char *filename){
	XMLDocument doc;
	doc.LoadFile(filename);

	if(doc.ErrorID() == XML_NO_ERROR){
		// No error, proceed
		XMLElement* elem = doc.FirstChildElement( "resources" )->FirstChildElement( "surface" );
		
		//associate correct image with correct Map attribute
	}

}


