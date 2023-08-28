/*
 * player.hpp
 *
 *  Created on: 20 de ago. de 2023
 *      Author: Grupo 8
 */
#ifndef PLAYER_HPP_
#define PLAYER_HPP_
#define inc_ang 30
#define normal_ang 0
#define max_angvel 2.7
#include <string>
#include <cstdio>
#include <vector>
#include <iostream>
#include "b2_sf_converter.hpp"
#include <SFML/Graphics.hpp>
#include <Box2D/Box2D.h>
class Player {
public:
	sf::Texture *tex;
	b2Body *body;
	float *elapsedtime;
	float ang_vel = 0;
	b2Vec2 linvel;
	std::vector<sf::IntRect> frames;

	Player(float &elapsedtime) {
		body = NULL;
		this->elapsedtime = &elapsedtime;
		frames.push_back(sf::IntRect(4, 0, 56, 64));
		frames.push_back(sf::IntRect(60, 0, 56, 64));
		frames.push_back(sf::IntRect(120, 0, 56, 64));
		frames.push_back(sf::IntRect(0, 68, 56, 64));
		frames.push_back(sf::IntRect(60, 68, 56, 68));
		frames.push_back(sf::IntRect(124, 68, 56, 64));
		tex = new sf::Texture();
		tex->loadFromFile("assets/nenja.png");

	}
	;
	void jet(std::string dir) {

		if (dir == "left") {
			body->ApplyLinearImpulse(b2Vec2(-2, -2), body->GetWorldCenter(),
					true);
			linvel = body->GetLinearVelocity();
			if (linvel.x < -7.5) {
				linvel.x = -7.5;
			}
			if (linvel.y < -6) {
				linvel.y = -6;
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
			if (linvel.x > 7.5) {
				linvel.x = 7.5;
			}
			if (linvel.y < -6) {
				linvel.y = -6;
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
			if (linvel.y < -7.5) {
				linvel.y = -7.5;
			}
			body->SetLinearVelocity(linvel);
		}

	}
	void animate() {
		linvel = body->GetLinearVelocity();
		sf::Sprite *sprite = static_cast<sf::Sprite*>(body->GetUserData());
		if (linvel.y > 6) {
			if (*elapsedtime >= 0.3 && *elapsedtime <= 0.6) {
				sprite->setTextureRect(frames[2]);
			}
			if (*elapsedtime >= 0.6 && *elapsedtime <= 0.9) {
				sprite->setTextureRect(frames[3]);
			}
			if (*elapsedtime >= 0.9) {
				sprite->setTextureRect(frames[4]);
			}
		}else{
			sprite->setTextureRect(frames[0]);
		}
	}

};

#endif /* PLAYER_HPP_ */
