/*
 * splashscreenstate.hpp
 *
 *  Created on: 15 de out. de 2023
 *      Author: hayde
 */
#ifndef MENUSTATE_HPP_
#define MENUSTATE_HPP_

#include "gamedata.hpp"
#include "gameState.hpp"
#include "statemachine.hpp"
#include "stdafx.hpp"

class MenuState: public State {
public:
	MenuState(GameDataRef data);
	void init();
	void draw();
	void handleInput();
	void options();
	//void update();
	void update();
	//void handleInput();

private:
	GameDataRef data;
	sf::Music menuMusic;
	sf::SoundBuffer selectBuf, enterBuf;
	sf::Sound select, enterOption;
	sf::Font arcadefont, titlefont;
	sf::Text menu[3], title;
	sf::Sprite background, tutorial;
	sf::Texture bg_tex, tut_tex;
	int selected_index;
	sf::Color unselected{0,0,0};
	sf::Color selected{128, 24, 10};
	bool moveUp = false, moveDown = false, enter = false, inOptions = false;
};

#endif /* MENUSTATE_HPP_ */
