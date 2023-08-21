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
	bool max_right_ang = false, max_left_ang = false;
	Player() {
		tex = new sf::Texture;
		tex->loadFromFile("assets/nenja.png", sf::IntRect(124, 68, 56, 64));
		body = NULL;
	}
	;
	void jet(std::string dir) {
		if (dir == "left") {
			body->ApplyLinearImpulse(b2Vec2(-1.5, -2.5), body->GetWorldCenter(),
					true);
			if (!max_left_ang) {
				ang_vel -= 0.03;
			}
			if (converter::radToDeg<double>(body->GetAngle()) < -15) {
				max_left_ang = true;
				ang_vel = 0;
			}
			body->SetAngularVelocity(ang_vel);

		}
		if (dir == "right") {
			body->ApplyLinearImpulse(b2Vec2(1.5, -2.5), body->GetWorldCenter(),
					true);
			if (!max_right_ang) {
				ang_vel += 0.03;
			}
			if (converter::radToDeg<double>(body->GetAngle()) > 15) {
				max_right_ang = true;
				ang_vel = 0;
			}
			body->SetAngularVelocity(ang_vel);
		}

		b2Vec2 vel = body->GetLinearVelocity();
		if (vel.x > 3) {
			vel.x = 3;
		}
		if (vel.y < -5) {
			vel.y = -5;
		}

		body->SetLinearVelocity(vel);
	}
	void handleInputs() {
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A)) {
			jet("left");
		} else {
			max_left_ang = true;
			if (converter::radToDeg<double>(body->GetAngle()) < 0) {
				ang_vel += 0.03;
				body->SetAngularVelocity(ang_vel);
			}
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D)) {
			jet("right");
		} else {
			max_right_ang = true;
			if (converter::radToDeg<double>(body->GetAngle()) > 0) {
				ang_vel -= 0.03;
				body->SetAngularVelocity(ang_vel);
			}
		}

	}

};

#endif /* PLAYER_HPP_ */
