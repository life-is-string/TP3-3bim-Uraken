/*
 * player.hpp
 *
 *  Created on: 20 de ago. de 2023
 *      Author: hayde
 */
#ifndef PLAYER_HPP_
#define PLAYER_HPP_
#define inc_ang 30
#define normal_ang 0
#define max_angvel 2.7
#include <string>
#include <iostream>
#include "b2_sf_converter.hpp"
#include <SFML/Graphics.hpp>
#include <Box2D/Box2D.h>
class Player {
public:
	sf::Texture *tex;
	b2Body *body;
	float ang_vel = 0;
	b2Vec2 linvel;
	Player() {
		tex = new sf::Texture;
		tex->loadFromFile("assets/nenja.png", sf::IntRect(124, 68, 56, 64));
		body = NULL;
	}
	;
	void jet(std::string dir) {

		if (dir == "left") {
			body->ApplyLinearImpulse(b2Vec2(-2, -2), body->GetWorldCenter(),
					true);
			linvel = body->GetLinearVelocity();
			if (linvel.x < -4) {
				linvel.x = -4;
			}
			if (linvel.y < -4) {
				linvel.y = -4;
			}
			body->SetLinearVelocity(linvel);

			if (converter::radToDeg<double>(body->GetAngle()) > -15) {
				ang_vel = -0.3;
			} else {
				ang_vel = 0;
			}

			body->SetAngularVelocity(ang_vel);

		} else if (dir == "right") {
			body->ApplyLinearImpulse(b2Vec2(2, -2), body->GetWorldCenter(),
					true);
			linvel = body->GetLinearVelocity();
			if (linvel.x > 4) {
				linvel.x = 4;
			}
			if (linvel.y < -4) {
				linvel.y = -4.;
			}
			body->SetLinearVelocity(linvel);

			if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A)) {
				if (converter::radToDeg<double>(body->GetAngle()) < 15) {
					ang_vel = 0.3;
				} else {
					ang_vel = 0;
				}
			} else {
				if (converter::radToDeg<double>(body->GetAngle()) > 0) {
					ang_vel = -0.3;
				} else if (converter::radToDeg<double>(body->GetAngle()) < 0) {
					ang_vel = 0.3;
				} else {
					ang_vel = 0;
				}
			}
			body->SetAngularVelocity(ang_vel);
		}

	}
	void handleInputs() {
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A)) {
			jet("left");
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D)) {
			jet("right");
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D)
				&& sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A)) {
			linvel = body->GetLinearVelocity();
			if (linvel.y < -4) {
				linvel.y = -4;
			}
			body->SetLinearVelocity(linvel);
		}
	}

};

#endif /* PLAYER_HPP_ */
