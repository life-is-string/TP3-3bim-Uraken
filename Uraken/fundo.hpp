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
	//fazer um vector de backgrounds pra facilitar sua vida :)
	sf::Sprite background;
	sf::Sprite background2;
	sf::Sprite background3;
	sf::Sprite background4;
	sf::Sprite background5;
	sf::Sprite background6;
	sf::Sprite background7;
	sf::Sprite background8;
	sf::Sprite background9;
	sf::Sprite background10;
	sf::Sprite background11;
	sf::Sprite background12;

	Fundo(){
		fundo1.loadFromFile("assets/fundo1.png");
		fundo2.loadFromFile("assets/fundo2.png");
		fundo3.loadFromFile("assets/fundo3.png");
		fundo4.loadFromFile("assets/fundo4.png");

		background.setTexture(fundo1);
		background2.setTexture(fundo2);
		background3.setTexture(fundo3);
		background4.setTexture(fundo4);
		background5.setTexture(fundo1);
		background6.setTexture(fundo2);
		background7.setTexture(fundo3);
		background8.setTexture(fundo4);
		background9.setTexture(fundo1);
		background10.setTexture(fundo2);
		background11.setTexture(fundo3);
		background12.setTexture(fundo4);

		//definição os sprites
		background.setPosition(-300, -40);
		background.setScale(0.6, 0.6);
		background.setColor({250,250,250,180});

		background2.setPosition(387, -40);
		background2.setScale(0.6, 0.6);
		background2.setColor({250,250,250,180});

		background3.setPosition(1074, -40);
		background3.setScale(0.6, 0.6);
		background3.setColor({250,250,250,180});

		background4.setPosition(1766.4, -40);
		background4.setScale(0.6, 0.6);
		background4.setColor({250,250,250,180});

		background5.setPosition(2452.2, -40);
		background5.setScale(0.6, 0.6);
		background5.setColor( { 250, 250, 250, 180 });

		background6.setPosition(3139.2, -40);
		background6.setScale(0.6, 0.6);
		background6.setColor( { 250, 250, 250, 180 });

		background7.setPosition(3826.2, -40);
		background7.setScale(0.6, 0.6);
		background7.setColor( { 250, 250, 250, 180 });

		background8.setPosition(4518.6, -40);
		background8.setScale(0.6, 0.6);
		background8.setColor( { 250, 250, 250, 180 });

		background9.setPosition(5204.4, -40);
		background9.setScale(0.6, 0.6);
		background9.setColor( { 250, 250, 250, 180 });

		background10.setPosition(5891.4, -40);
		background10.setScale(0.6, 0.6);
		background10.setColor( { 250, 250, 250, 180 });

		background11.setPosition(6578.4, -40);
		background11.setScale(0.6, 0.6);
		background11.setColor( { 250, 250, 250, 180 });

		background12.setPosition(7270.8, -40);
		background12.setScale(0.6, 0.6);
		background12.setColor( { 250, 250, 250, 180 });

	}
	void draw(sf::RenderWindow &window){
		//https://i0.wp.com/blog.feabhas.com/wp-content/uploads/2015/07/image20.png
		//window.draw(backgrounds[i]);
	}
};



#endif /* FUNDO_HPP_ */
