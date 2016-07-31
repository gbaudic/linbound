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
#include <string>
#include <map>

using namespace tinyxml2;
using namespace std;

/**
 * Load a map from the XML description file
 */
void LB_LoadMap(const char *filename){
	XMLDocument doc;
	map<string, string> files;
	doc.LoadFile(filename);


	if(doc.ErrorID() == XML_NO_ERROR){
		// No error, proceed
		bool hasBside = false;
		XMLElement* elem = doc.FirstChildElement( "resources" )->FirstChildElement( "hasBside" );
		elem->QueryBoolText(&hasBside);
		
		elem = doc.FirstChildElement( "resources" )->FirstChildElement( "surface" );
		while(elem != NULL){
			const char* name = elem->Attribute( "name" ); 
			const char* file = elem->Attribute( "file" );
			
			//associate correct image with correct Map attribute
			files.insert(make_pair(string(name), string(file));
			//go to next one
			elem = doc.FirstChildElement( "resources" )->NextSiblingElement( "surface" );
		}
		
		elem = doc.FirstChildElement( "resources" )->FirstChildElement( "name" );
		string mapName;
		if(elem != NULL)
			const char* str = elem->GetText();
		mapName.assign(str);
	}

}


