/*
 * myContactListener.cpp
 *
 *      Author: Grupo 8
 */

#include "myContactListener.hpp"

MyContactListener::MyContactListener(b2Body *playerBody, b2Body *ground, sf::RenderWindow *window){
	this->playerBody = playerBody;
	this->ground = ground;
	this->window = window;
}


void MyContactListener::BeginContact(b2Contact *contact) {
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
}


