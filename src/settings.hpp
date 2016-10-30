/**
 * \file settings.hpp
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

#ifndef _H_SETTINGS_
#define _H_SETTINGS_

#include <SDL2/SDL.h>
#include <guisan.hpp>
#include <guisan/sdl.hpp>

/**
 *  Singleton to encapsulate game settings
 */
class Settings {
public:
	static Uint8 getEffectsVolume() const;
	void setEffectsVolume(static Uint8 effectsVolume);
	static Uint16 getHeight() const;
	void setHeight(static Uint16 height);
	const Settings& getInstance() const;
	static Uint8 getMusicVolume() const;
	void setMusicVolume(static Uint8 musicVolume);
	static Uint16 getWidth() const;
	void setWidth(static Uint16 width);
	static bool isServer() const;
	void setServer(static bool isServer);

private:
	static Uint8 musicVolume;
	static Uint8 effectsVolume;
	static Uint16 height, width; //window size
	static bool isServer;
	static Settings instance;
	Settings();
	~Settings();
	void init();
	void save();
	Settings& operator= (const Settings&) = delete; //ensure singleton
	Settings (const Settings&) = delete;
};

/**
 *  Subwindow to control settings from main menu
 */
class SettingsWindow {
	public:
	SettingsWindow();
	~SettingsWindow();
	
	private:
	gcn::Window settings;
	gcn::Button btn_ok, btn_cancel;
	gcn::Label lbl_music, lbl_effects;
	gcn::Slider sl_music, sl_effects;
	
};


#endif /* _H_SETTINGS_ */
