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
 *   popularity acts as an additive factor for increase or decrease
 *  \param itemsOn if true, allows player items to be taken into account
 *  \return an Achievement holding the correct values
 */
Achievement LB_Player::getPersonalizedValue(Achievement base, bool itemsOn) {
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

/**
 *  \brief Compute the damage experienced by receiver
 *  \param shot a pointer to a LB_Shot. The damage field will be modified by this method.
 *  \param sender the player firing the shot
 *  \param receiver the player who will sustain the damage
 */
void computeDamage(LB_Shot* shot, LB_Player* sender, LB_Player* receiver) {
	double distance = getDistance(sender->x, sender->y, receiver->x, receiver->y);
	if(distance >= MAX_DISTANCE) {
		//Too far, no damage
		shot->damage = 0;
	} else {
		//Linear decrease of damage
		Uint16 maxDamage = getBaseDamage(shot->weapon) * (MAX_DISTANCE - distance) / MAX_DISTANCE;
		Sint8 factor = 100 + sender->getPlayerStat(ATTACK_STAT) - receiver->getPlayerStat(DEFENCE_STAT);
		shot->damage = maxDamage * factor / 100;
	}
}

Uint16 LB_Player::getCurrentMobile() {
	return usesMobile1 ? playerMobile1 : playerMobile2;
}

Sint8 LB_Player::getPlayerStat(Statistic stat) {
	return playerStats[stat];
}

/**
 *  Implementation of Pythagore theorem
 *  Required for damage computation
 */
double getDistance(Sint16 x1, Sint16 y1, Sint16 x2, Sint16 y2) {
	return sqrt((x1-x2)*(x1-x2) + (y1-y2)*(y1-y2));
}
 
/**
 *  Returns the base value for actual damage computation
 *  TODO: add more changes by making a different method for each mobile
 */
Uint16 getBaseDamage(Weapon weapon) {
	switch(weapon){
		case WEAPON_SHOT1: return 200;
		case WEAPON_SHOT2: return 300;
		case WEAPON_SUPER_SHOT: return 500;
		default: return 0;
	}
}
