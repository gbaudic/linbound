/**
 *  \file utils.cpp
 *  \brief Utility functions
 *  \author G. B.
 */
/* This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. 
 * If a copy of the MPL was not distributed with this file, 
 * You can obtain one at http://mozilla.org/MPL/2.0/.
 * 
 * This Source Code Form is “Incompatible With Secondary Licenses”, 
 * as defined by the Mozilla Public License, v. 2.0.
 */

#include <SDL2/SDL.h>
#include "utils.hpp"

/**
 * Makes an angle between 0 and 360 degrees
 * \param angle the angle to normalize, in degrees
 * \return a value between 0 and 359 degrees
 */
Sint16 normalizeAngle(Sint16 angle){
    while(angle < 0)
        angle += 360;
        
    return angle % 360;
}

/**
 *  Implementation of Pythagorean theorem
 *  Required for damage computation
 */
double getDistance(Sint16 x1, Sint16 y1, Sint16 x2, Sint16 y2) {
	return sqrt((x1-x2)*(x1-x2) + (y1-y2)*(y1-y2));
}

/**
 * Implements a conversion to get same angle notation as in GunBound
 * Required to make transition easier for players
 * \param angle the angle in degree
 * \returns a normalized value with 0 <= abs(angle) <= 90, 0 is horizontal, pointing downwards is negative
 */
Sint16 getShotAngle(Sint16 angle) {
	angle = normalizeAngle(angle); //[0; 360)
	angle -= 180; //[-180; 180)

	if(angle > 90){
		return 90 - (angle - 90);
	} else {
		if(angle < -90) {
			return -90 - (90 + angle);
		} else {
			return angle;
		}
	}

}