/**
 * \file settings.cpp
 * \brief Settings-related classes
 * \version 0.1a
 * \author G. B.
 * \date 29/10/2016
 */

/* This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0.
 * If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/.
 *
 * This Source Code Form is "Incompatible With Secondary Licenses",
 * as defined by the Mozilla Public License, v. 2.0.
 */

#include "settings.hpp"

using namespace std;

static Uint8 Settings::getEffectsVolume() const {
	return effectsVolume;
}

void Settings::setEffectsVolume(static Uint8 effectsVolume) {
	this->effectsVolume = effectsVolume;
}

static Uint16 Settings::getHeight() const {
	return height;
}

void Settings::setHeight(static Uint16 height) {
	this->height = height;
}

const Settings& Settings::getInstance() const {
	return instance;
}

static Uint8 Settings::getMusicVolume() const {
	return musicVolume;
}

void Settings::setMusicVolume(static Uint8 musicVolume) {
	this->musicVolume = musicVolume;
}

static Uint16 Settings::getWidth() const {
	return width;
}

void Settings::setWidth(static Uint16 width) {
	this->width = width;
}

Settings::Settings() {

}

Settings::~Settings() {
}

static bool Settings::isServer() const {
	return isServer;
}

void Settings::setServer(static bool isServer) {
	this->isServer = isServer;
}

/**
 * Initialize settings from external config file
 */
void Settings::init(){

}

/**
 * Write setting changes to disk
 */
void Settings::save() {
}
