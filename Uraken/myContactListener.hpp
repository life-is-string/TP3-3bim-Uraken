/*
 * myContactListener.hpp
 *
 *  Created on: 1 de set. de 2023
 *      Author: Grupo 8
 */

#ifndef MYCONTACTLISTENER_HPP_
#define MYCONTACTLISTENER_HPP_

#include <Box2D/Box2D.h>
#include <SFML/Graphics.hpp>

class MyContactListener: public b2ContactListener {
private:
	b2Body *playerBody, *ground;
	sf::RenderWindow *window;
public:
	MyContactListener(b2Body *playerBody, b2Body *ground, sf::RenderWindow *window) : playerBody(playerBody), ground(ground), window(window){}
	void BeginContact(b2Contact *contact) override{
		b2Fixture *fixtureA = contact->GetFixtureA();
		b2Fixture *fixtureB = contact->GetFixtureB();

		if (fixtureA->IsSensor() || fixtureB->IsSensor()) {
			//nao vai fazer nada se o corpo A ou B for um sensor
			return;
		}

		b2Body *bodyA = fixtureA->GetBody();
		b2Body *bodyB = fixtureB->GetBody();

		if (bodyA == nullptr || bodyB == nullptr) {
			return;
		}

		if ((bodyA == playerBody && bodyB == ground) || (bodyA == ground && bodyB == playerBody)) {
			window->close();
		}
	};
};

#endif /* MYCONTACTLISTENER_HPP_ */
