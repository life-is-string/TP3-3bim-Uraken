/*
 * fundo.hpp
 *
 *  Created on: 27 de ago. de 2023
 *      Author: grupo 8
 */

#ifndef BACKGROUND_HPP_
#define BACKGROUND_HPP_
#include <vector>
#include <SFML/Graphics.hpp>


class Background{
public:
	sf::Texture fundo1, fundo2, fundo3, fundo4;
	std::vector <sf::Sprite> backgrounds;
	Background(){
		fundo1.loadFromFile("assets/fundo1.png");
		fundo2.loadFromFile("assets/fundo2.png");
		fundo3.loadFromFile("assets/fundo3.png");
		fundo4.loadFromFile("assets/fundo4.png");

		for(int i = 0; i < 13; i++){
			sf::Sprite bg;
			bg.setScale(0.6, 0.6);
			bg.setColor( { 250, 250, 250, 180 });
			backgrounds.push_back(bg);
		}

		backgrounds[0].setTexture(fundo4);
		backgrounds[1].setTexture(fundo1);
		backgrounds[2].setTexture(fundo2);
		backgrounds[3].setTexture(fundo3);
		backgrounds[4].setTexture(fundo4);
		backgrounds[5].setTexture(fundo1);
		backgrounds[6].setTexture(fundo2);
		backgrounds[7].setTexture(fundo3);
		backgrounds[8].setTexture(fundo4);
		backgrounds[9].setTexture(fundo1);
		backgrounds[10].setTexture(fundo2);
		backgrounds[11].setTexture(fundo3);
		backgrounds[12].setTexture(fundo4);

		//definição os sprites
		backgrounds[0].setPosition(-985.8, -40);
		backgrounds[1].setPosition(-300, -40);
		backgrounds[2].setPosition(387, -40);
		backgrounds[3].setPosition(1074, -40);
		backgrounds[4].setPosition(1766.4, -40);
		backgrounds[5].setPosition(2452.2, -40);
		backgrounds[6].setPosition(3139.2, -40);
		backgrounds[7].setPosition(3826.2, -40);
		backgrounds[8].setPosition(4518.6, -40);
		backgrounds[9].setPosition(5204.4, -40);
		backgrounds[10].setPosition(5891.4, -40);
		backgrounds[11].setPosition(6578.4, -40);
		backgrounds[12].setPosition(7270.8, -40);

	}
};



#endif /* BACKGROUND_HPP_ */
