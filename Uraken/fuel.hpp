/*
 * fuel.hpp
 *
 *  Created on: 31 de ago. de 2023
 *      Author: hayde
 */

#ifndef FUEL_HPP_
#define FUEL_HPP_
#include <SFML/Graphics.hpp>
#include <Box2D/Box2D.h>
class Fuel {
private:
	sf::Clock cooldown;
	std::vector<sf::IntRect> frames;
	sf::Texture *texture;
	sf::SoundBuffer emptbuf;
	sf::Sound emptying;
	int param = 0;
public:
	sf::Sprite sprite;
	Fuel() {
		texture = new sf::Texture();
		texture->loadFromFile("assets/fuel.png");
		sprite.setTexture(*texture);
		sprite.setScale(4, 4);
		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 4; j++) {
				frames.push_back(sf::IntRect(0 + 24 * j, 0 + 28 * i, 24, 28));
				if (i == 4 && j == 3) {
					break;
				}
			}
		}
		emptbuf.loadFromFile("assets/bubble.wav");
		emptying.setBuffer(emptbuf);
		cooldown.restart();
	}
	void update(float fuel, sf::Vector2f vpos) {
		sprite.setPosition(vpos.x - 370, vpos.y - 240);
		if (fuel >= 25) {
			param = 0;
			sprite.setTextureRect(frames[0]);
		} else {
			if (fuel <= (25 - 1.78 * param)) {
				if (param < 13) {
					param++;
					sprite.setTextureRect(frames[param]);
					if (cooldown.getElapsedTime().asSeconds() >= 0.2) {
						emptying.play();
						cooldown.restart();
					}
				}
			}

		}
	}

};

#endif /* FUEL_HPP_ */
