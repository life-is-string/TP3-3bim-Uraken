/*
 * fundo.hpp
 *
 *  Created on: 27 de ago. de 2023
 *      Author: grupo 8
 */

#ifndef FUNDO_HPP_
#define FUNDO_HPP_
#include <string>
#include <cstdio>
#include <vector>
#include <iostream>
#include <SFML/Graphics.hpp>


class Fundo{
public:
	sf::Texture fundo1;
	sf::Texture fundo2;
	sf::Texture fundo3;
	sf::Texture fundo4;
	sf::Sprite background;
	sf::Sprite background2;
	sf::Sprite background3;
	sf::Sprite background4;

	Fundo(){
		fundo1.loadFromFile("assets/fundo1.png");
		fundo2.loadFromFile("assets/fundo2.png");
		fundo3.loadFromFile("assets/fundo3.png");
		fundo4.loadFromFile("assets/fundo4.png");

		background.setTexture(fundo1);
		background2.setTexture(fundo2);
		background3.setTexture(fundo3);
		background4.setTexture(fundo4);

		//definição os sprites
		background.setPosition(0, -40);
		background.setScale(1.8, 1.8);

		background2.setPosition(0, 40);
		background2.setScale(1.8, 1.8);

		background3.setPosition(0, -40);
		background3.setScale(1.8, 1.8);

		background4.setPosition(0, -40);
		background4.setScale(1.8, 1.8);

	}
};



#endif /* FUNDO_HPP_ */
