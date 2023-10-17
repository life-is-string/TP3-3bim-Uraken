/*
 * player.cpp
 *
 *  Created on: 31 de ago. de 2023
 *      Author: hayde
 */
#include "player.hpp"

void Player::applyBlastImpulse(b2Body *body, b2Vec2 blastCenter,
		b2Vec2 applyPoint, float blastPower) {
	b2Vec2 blastDir = applyPoint - blastCenter;
	float distance = blastDir.Normalize();
	//ignore bodies exactly at the blast point - blast direction is undefined
	if (distance == 0)
		return;
	float invDistance = 1 / distance;
	float impulseMag = blastPower * invDistance * invDistance;
	body->ApplyLinearImpulse(impulseMag * blastDir, applyPoint, true);
}

Player::Player(float &elapsedtime, b2World *world) : world(world) {
	body = NULL;
	for (auto i : fleshparts) {
		i = NULL;
	}
	this->elapsedtime = &elapsedtime;
	frames.push_back(sf::IntRect(4, 0, 56, 64));
	frames.push_back(sf::IntRect(60, 0, 56, 64));
	frames.push_back(sf::IntRect(120, 0, 56, 64));
	frames.push_back(sf::IntRect(0, 68, 56, 64));
	frames.push_back(sf::IntRect(60, 68, 56, 68));
	frames.push_back(sf::IntRect(124, 68, 56, 64));
	failbuf.loadFromFile("assets/slam.wav");
	fail.setBuffer(failbuf);
	tex = new sf::Texture();
	tex->loadFromFile("assets/nenja.png");
	isjetting = false;
	nofuel = false;
	fuel = 25;
	checkpoint = NULL;
}

void Player::handleFuel() {
	if (isjetting && fuel > 0 && *elapsedtime >= 0.3 && *elapsedtime <= 0.6) {
		fuel -= 0.25;
	}
	if (fuel == 0) {
		nofuel = true;
	} else {
		nofuel = false;
	}
}
void Player::jet(std::string dir) {
	if (!isjetting) {
		isjetting = true;
	}
	if (dir == "left") {
		sf::Sprite *sprite = static_cast<sf::Sprite*>(body->GetUserData());
		sprite->setTextureRect(frames[1]);
		body->ApplyLinearImpulse(b2Vec2(-2, -2), body->GetWorldCenter(), true);
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
		sf::Sprite *sprite = static_cast<sf::Sprite*>(body->GetUserData());
		sprite->setTextureRect(frames[0]);
		body->ApplyLinearImpulse(b2Vec2(2, -2), body->GetWorldCenter(), true);
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
void Player::handleInputs() {
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A)) {
		jet("left");
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D)) {
		jet("right");
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D)
			&& sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A)) {
		linvel = body->GetLinearVelocity();
		sf::Sprite *sprite = static_cast<sf::Sprite*>(body->GetUserData());
		sprite->setTextureRect(frames[3]);
		if (linvel.y < -7.5) {
			linvel.y = -7.5;
		}

		body->SetLinearVelocity(linvel);
	}
	if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A)
			&& !sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D))
		isjetting = false;
}
void Player::animate() {
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
	} else {
		sprite->setTextureRect(frames[0]);
	}
}
void Player::respawn() {
	if (death) {
		for (auto i : fleshparts) {
			applyBlastImpulse(i, body->GetPosition(), i->GetWorldCenter(),
					15.f);
		}
		res = true;
		world->DestroyBody(body);
		fail.play();
		death = false;
	} else {
		return;
	}
}
void Player::update() {
	animate();
	handleFuel();
	if (!nofuel) {
		handleInputs();
	} else {
		isjetting = false;
	}
	respawn();
}

