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
#include <SFML/Audio.hpp>
#include "Player.hpp"
#include <iostream>

class MyContactListener: public b2ContactListener {
private:
	sf::Sound sucess;
	sf::Music *music;
	b2Body *ground;
	sf::RenderWindow *window;
	Player *player;
	bool* freezeAll;
	sf::SoundBuffer sucessbuf;
	std::vector<b2Body*> platforms;
public:
	MyContactListener(Player* player, std::vector<b2Body*> platforms, b2Body* ground,
			sf::RenderWindow *window, bool* freezeAll, sf::Music *music) :
			player(player), platforms(platforms), window(window), ground(ground), freezeAll(freezeAll), music(music) {
		sucessbuf.loadFromFile("assets/sucess.wav");
		sucess.setBuffer(sucessbuf);

	}
	void BeginContact(b2Contact *contact) override {
		b2Fixture *fixtureA = contact->GetFixtureA();
		b2Fixture *fixtureB = contact->GetFixtureB();

		if (fixtureA->IsSensor() || fixtureB->IsSensor()) {
			//nao vai fazer nada se o corpo A ou B for um sensor
			return;
		}

		b2Body *bodyA = fixtureA->GetBody();
		b2Body *bodyB = fixtureB->GetBody();
		b2Vec2 normal = contact->GetManifold()->localNormal;

		if (bodyA == nullptr || bodyB == nullptr) {
			return;
		}

		if ((bodyA == player->body && bodyB == ground)
							|| (bodyA == ground && bodyB == player->body)) {

			player->death = true;
		}

		for (auto i : platforms) {
			if ((bodyA == player->body && bodyB == i)
					|| (bodyA == i && bodyB == player->body)) {
				if (normal == b2Vec2(0, 1) || normal == b2Vec2(0, -1)) { //detects top collision
					player->linvel = player->body->GetLinearVelocity();
					if (player->linvel.y > 6) { //dies
						player->death = true;
					}else if(player->checkpoint != i){ //new checkpoint
						sucess.play();
						player->checkpoint = i;
						player->fuel = 25;
						if(i == platforms[19]){ //last platforms, win the game
							//send broadcast to the testbed to freeze all and to show win screen
							*freezeAll = true;
							music->stop();
							music->openFromFile("assets/naruto-wind.wav");
							music->play();
						}
					}
				}
			}
		}
	}
	;
};

#endif /* MYCONTACTLISTENER_HPP_ */
