/**
 *  \file player.hpp
 *  \brief Class definitions for players
 *  \author G. B.
 */
/* This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. 
 * If a copy of the MPL was not distributed with this file, 
 * You can obtain one at http://mozilla.org/MPL/2.0/.
 * 
 * This Source Code Form is �Incompatible With Secondary Licenses�, 
 * as defined by the Mozilla Public License, v. 2.0.
 */
 
#include "player.hpp"

/**
 *  \brief Get the achievement with the correct gold and xp settings for this player
 *  \param base the Achievement with the base values
 *  \param popularity additive factor for increase or decrease
 *  \param itemsOn if true, allows player items to be taken into account
 *  \return an Achievement holding the correct values
 */
Achievement LB_Player::getPersonalizedValue(Achievement base, Sint8 popularity, bool itemsOn) {
	if(!itemsOn) {
		return base;
	} else {
		Achievement result;
		result.name = base.name;
		result.type = base.type;
		result.gold = base.gold * (100+popularity) / 100;
		result.xp = base.xp * (100+popularity) / 100;
		return result;
	}
}

/**
 *  Reinitialize some attributes after a game
 */
void LB_Player::reset() {
	currentAngle = 0; lastAngle = 0;
	playerDelay = 0;
	xp += playerXp;
	playerGold += playerAward;
	playerXp = 0; playerAward = 0;
}

/**
 *  Populate avatar item stats for the player
 */
void LB_Player::computeStats() {
	//reset
	popularity = 0; defence = 0; attack = 0; bunge = 0;
	heart = 0; blueDelay = 0; orangeDelay = 0; delay = 0;
	//refill
	for(int i = 0 ; i < 5 ; i++){
		popularity += items[i].popularity;
		defence += items[i].defence;
		attack += items[i].attack;
		bunge += items[i].bunge;
		heart += items[i].heart;
		blueDelay += items[i].blueDelay;
		orangeDelay += items[i].orangeDelay;
		delay += items[i].delay;
	}
}
 
 
Uint16 getBaseDamage(Weapon weapon) {
	switch(weapon){
		case WEAPON_SHOT1: return 200;
		case WEAPON_SHOT2: return 300;
		case WEAPON_SUPER_SHOT: return 500;
		default: return 0;
	}
}
