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
#include "platform.hpp"
#include "fundo.hpp"
#include "myContactListener.hpp"
#include <SFML/Graphics.hpp>
#include <SFML/Audio/Music.hpp>

#include <Box2D/Box2D.h>
#include "b2_sf_converter.hpp"
#include <vector>

class Testbed {
private:
	sf::Music music;
	sf::Vector2f vpos;
	float dt, elapsedtime = 0.3;
	sf::Clock clock;
	Fuel *fueldisplay;
	Player *player;
	Fundo *fundo;
	b2Body *ground;
	sf::RenderWindow window;
	b2World *world;
	std::vector <Platform> platforms;
	sf::View view; //creation of the view to follow the player


public:
	void displayWorld();
	b2Body* createElement(int x, int y, int width, int height,
			b2BodyType type, sf::Color color);
	b2Body* createElement(int x, int y, int width, int height,
				b2BodyType type, sf::Texture *tex, sf::IntRect frame);
	Testbed();
	void Run();
};



#endif /* TESTBED_HPP_ */
