/*
 * myContactListener.hpp
 *
 *  Created on: 1 de set. de 2023
 *      Author: Grupo 8
 */

#ifndef MYCONTACTLISTENER_HPP_
#define MYCONTACTLISTENER_HPP_

#include "player.hpp"
#include "testbed.hpp"
#include <SFML/Graphics.hpp>

#include <Box2D/Box2D.h>
#include "b2_sf_converter.hpp"

class MyContactListener: public b2ContactListener {
private:
	//corpo player, ground, window
	b2Body *playerBody, *ground;
	sf::RenderWindow *window;

public:

	MyContactListener(b2Body *playerBody, b2Body *ground, sf::RenderWindow *window);

	void BeginContact(b2Contact *contact);

};

#endif /* MYCONTACTLISTENER_HPP_ */
