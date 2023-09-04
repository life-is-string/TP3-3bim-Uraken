/*
 * testbed.hpp
 *
 *  Created on: 18 de ago. de 2023
 *      Author: Grupo 8
 */

#ifndef TESTBED_HPP_
#define TESTBED_HPP_
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

class Testbed {
private:
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
	sf::RenderWindow *window;
	b2World *world;
	std::vector <b2Body*> platforms;
	std::vector<sf::Sprite*> bamboos;
	sf::View view; //creation of the view to follow the player
	bool freezeAll = false; //stops the simulation, game end
	void displayWorld();

public:
	b2Body* createElement(int x, int y, int width, int height,
			b2BodyType type, sf::Color color);
	b2Body* createElement(int x, int y, int width, int height,
				b2BodyType type, sf::Texture *tex, sf::IntRect frame);
	Testbed();
	void Run();
};



#endif /* TESTBED_HPP_ */
