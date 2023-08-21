/*
 * testbed.hpp
 *
 *  Created on: 18 de ago. de 2023
 *      Author: user
 */

#ifndef TESTBED_HPP_
#define TESTBED_HPP_
#include "player.hpp"
#include <SFML/Graphics.hpp>
#include <Box2D/Box2D.h>
#include "b2_sf_converter.hpp"
#include <vector>

class Testbed {
private:
	Player player;
	sf::RenderWindow window;
	b2World *world;
	b2Body *ground;
	std::vector <b2Body*> platforms;

public:
	void displayWorld();
	b2Body* createElement(int x, int y, int width, int height,
			b2BodyType type);
	b2Body* createElement(int x, int y, int width, int height,
				b2BodyType type, sf::Texture *tex);
	Testbed();
	void Run();
};

#endif /* TESTBED_HPP_ */
