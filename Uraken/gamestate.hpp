/*
 * menu.hpp
 *
 *  Created on: 9 de jun. de 2023
 *      Author: hayde
 */
#pragma once
#ifndef STATES_MENUSTATE_HPP_
#define STATES_MENUSTATE_HPP_
#include "gamedata.hpp"
#include "State.hpp"
#include "stdafx.hpp"
#include "player.hpp"
#include "fuel.hpp"
#include "myContactListener.hpp"
#include <SFML/Graphics.hpp>
#include <SFML/Audio/Music.hpp>
#include <typeinfo>
#include <Box2D/Box2D.h>
#include "b2_sf_converter.hpp"
#include <vector>
#include <iostream>
#include "background.hpp"

class GameState: public State {
public:
	GameState(GameDataRef data);
	void init();
	void update();
	void draw();

private:
	GameDataRef data;
	MyContactListener *contactListener;
	sf::Music music;
	sf::Vector2f vpos;
	float dt = 0, elapsedtime = 0.3, winposy = 0;
	sf::Clock clock;
	sf::Sprite winscreen;
	Fuel *fueldisplay;
	Player *player;
	Background *bg;
	b2Body *ground;
	b2World *world;
	std::vector<b2Body*> platforms;
	std::vector<sf::Sprite*> bamboos;
	b2Body* createElement(int x, int y, int width, int height, b2BodyType type,
			sf::Color color);
	b2Body* createElement(int x, int y, int width, int height, b2BodyType type,
			sf::Texture *tex, sf::IntRect frame);
	sf::View view; //creation of the view to follow the player
	sf::View minimap; //creation of the view for the minimap
	bool freezeAll = false; //stops the simulation, game end

};

#endif /* STATES_MENUSTATE_HPP_ */
