/*
 * testbed.hpp
 *
 *  Created on: 18 de ago. de 2023
 *      Author: Grupo 8
 */

#ifndef TESTBED_HPP_
#define TESTBED_HPP_
#include "player.hpp"
#include "fundo.hpp"
#include <SFML/Graphics.hpp>
#include <Box2D/Box2D.h>
#include "b2_sf_converter.hpp"
#include <vector>

class Testbed {
private:
	float dt, elapsedtime = 0.3;
	sf::Clock clock;
	Player *player;
	/////Fundo *fundo;
	sf::RenderWindow window;
	b2World *world;
	b2Body *ground;
	std::vector <b2Body*> platforms;
	std::vector<b2Body*> groundElement;
	sf::View view; //creation of the view to follow the player

public:
	void displayWorld();
	b2Body* createElement(int x, int y, int width, int height,
			b2BodyType type);
	b2Body* createElement(int x, int y, int width, int height,
				b2BodyType type, sf::Texture *tex, sf::IntRect frame);
	Testbed();
	void Run();
};

#endif /* TESTBED_HPP_ */
