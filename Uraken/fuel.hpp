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
	std::vector<sf::IntRect> frames;
	sf::Texture *texture;
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
	}
	void update(float fuel, sf::Vector2f vpos) {
		sprite.setPosition(vpos.x - 370, vpos.y - 240);
		if (fuel == 50) {
			param = 1;
			sprite.setTextureRect(frames[0]);
		} else {
			if (fuel <= 50 - 3.5 * param) {
				if(param < 13){
					param++;
					sprite.setTextureRect(frames[param]);
				}
			}

		}
	}

};

#endif /* FUEL_HPP_ */
