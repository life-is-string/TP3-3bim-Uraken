/*
 * player.hpp
 *
 *  Created on: 20 de ago. de 2023
 *      Author: hayde
 */
#ifndef PLAYER_HPP_
#define PLAYER_HPP_
#include <string>
#include <iostream>
#include <SFML/Graphics.hpp>
#include <Box2D/Box2D.h>
class Player {
public:
	sf::Texture *tex;
	b2Body *body;
	Player() {
		tex = new sf::Texture;
		tex->loadFromFile("assets/nenja.png", sf::IntRect(124, 68, 56, 64));
		body = NULL;
	}
	;
	void jet(std::string dir) {
		if (dir == "left") {
			body->ApplyLinearImpulse(b2Vec2(-1, -3), body->GetWorldCenter(),
					true);
		}
		if (dir == "right") {
			body->ApplyLinearImpulse(b2Vec2(1, -3), body->GetWorldCenter(),
					true);
		}
		b2Vec2 vel = body->GetLinearVelocity();
		if (vel.x > 2) {
			vel.x = 2;
		}
		if (vel.y < -6) {
			vel.y = -6;
		}
		body->SetLinearVelocity(vel);
		std::cout << vel.x << " " << vel.y << "\n";
	}
	void handleInputs() {
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A)) {
			jet("left");
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D)) {
			jet("right");
		}
	}

};

#endif /* PLAYER_HPP_ */
