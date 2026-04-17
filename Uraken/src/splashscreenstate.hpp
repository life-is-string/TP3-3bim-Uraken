/*
 * splashscreenstate.hpp
 *
 *  Created on: 15 de out. de 2023
 *      Author: hayde
 */

#ifndef SPLASHSCREENSTATE_HPP_
#define SPLASHSCREENSTATE_HPP_
#include "gamedata.hpp"
#include "gameState.hpp"
#include "statemachine.hpp"
#include "stdafx.hpp"
#include "menustate.hpp"

class SplashScreen : public State{
public:
	SplashScreen(GameDataRef data);
	void init();
	void draw();
	void handleInput();
	void update();
private:
	GameDataRef data;
	sf::Clock clock;
	sf::SoundBuffer barkbuf;
	sf::Sound bark;
	sf::Texture tex;
	sf::Sprite logo;
	float a = 0;
	bool fade = false;
};



#endif /* SPLASHSCREENSTATE_HPP_ */
