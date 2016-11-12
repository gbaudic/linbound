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
 
#include <libintl.h>
#include <locale.h>

#include <iostream>
#include <fstream>
#include <string>

#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>

#include "settings.hpp"

using namespace std;

Settings* Settings::instance = NULL;

Uint8 Settings::getEffectsVolume() {
	return effectsVolume;
}

void Settings::setEffectsVolume( Uint8 effectsVolume) {
	this->effectsVolume = effectsVolume;
}

Uint16 Settings::getHeight() {
	return height;
}

void Settings::setHeight( Uint16 height) {
	this->height = height;
}

Settings* Settings::getInstance() {
	if(instance == NULL){
		instance = new Settings();
	}
	return instance;
}

Uint8 Settings::getMusicVolume() {
	return musicVolume;
}

void Settings::setMusicVolume( Uint8 musicVolume) {
	this->musicVolume = musicVolume;
}

Uint16 Settings::getWidth() {
	return width;
}

void Settings::setWidth( Uint16 width) {
	this->width = width;
}

Settings::Settings() {
	init();
}

Settings::~Settings() {
}

bool Settings::isAServer() {
	return isServer;
}

void Settings::setServer( bool isServer) {
	if(!isServerSet){
		this->isServer = isServer;
		this->isServerSet = true;
	}
}

/**
 * Initialize settings from external config file
 */
void Settings::init(){
	//Try to read the config file
	ifstream input("linbound.config", ios::in);
	string line;
	
	while(getline(input, line) && !input.eof()){
		if(!line.empty() && line.front() != '['){
			int eqpos = line.find('=');
			//Maybe a value here
			//determine if we know this key
			//if yes, check value consistency and inject; if no, ignore
		}
	}

	//If it fails...
	width = 800;
	height = 600;
	musicVolume = MIX_MAX_VOLUME / 2;
	effectsVolume = MIX_MAX_VOLUME / 2;

	input.close();
}

/**
 * Write setting changes to disk
 */
void Settings::save() {
	
	ofstream output("linbound.config", ios::out);
	output << "[Display]" << endl;
	output << "Height=" << height << endl
		   << "Width=" << width << endl << endl;
	output << "[Audio]" << endl;
	output << "MusicVolume=" << musicVolume << endl
		   << "EffectsVolume=" << effectsVolume << endl;
	output.close();
}

SettingsWindow::SettingsWindow() : settings(gettext("Settings")),
btn_ok(gettext("OK")), btn_cancel(gettext("Cancel")),
lbl_music(gettext("Music volume")), lbl_effects(gettext("Effects volume")),
sl_music(0, MIX_MAX_VOLUME), sl_effects(0, MIX_MAX_VOLUME)
{
	sl_music.setValue(Settings::getInstance()->getMusicVolume());
	sl_effects.setValue(Settings::getInstance()->getEffectsVolume());
	btn_cancel.adjustSize();
	btn_ok.setWidth(btn_cancel.getWidth());
	btn_ok.setHeight(btn_cancel.getHeight()); //just for aesthetics
	btn_ok.setActionEventId("ok");
	btn_ok.addActionListener(this);
	btn_cancel.setActionEventId("cancel");
	btn_cancel.addActionListener(this);
	
	gcn::Color color(0x1f, 0x75, 0xf5, 0);
	settings.setBaseColor(color);
	settings.add(&btn_ok, 100, 100);
	settings.add(&btn_cancel, 150, 100);
	settings.add(&lbl_music, 10, 30);
	settings.add(&lbl_effects, 10, 60);
	settings.add(&sl_music, 60, 30);
	settings.add(&sl_effects, 60, 60);

	settings.setVisible(true);
}

SettingsWindow::~SettingsWindow() {

}

void SettingsWindow::action(const gcn::ActionEvent& actionEvent) {

}

/**
 * Shows or hides the settings window
 */
void SettingsWindow::setVisible(bool visible) {
	settings.setVisible(visible);
}

