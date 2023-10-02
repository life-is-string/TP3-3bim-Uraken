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
#include <SFML/Audio.hpp>
#include <Box2D/Box2D.h>

class Player {
private:
	sf::Clock clock;
	sf::SoundBuffer failbuf;
	sf::Sound fail;
	float ang_vel = 0;
	bool isjetting, nofuel;
	void handleFuel();
	void jet(std::string dir);
	void handleInputs();
	void animate();
	void respawn();

public:
	bool death = false;
	float fuel;
	sf::Texture *tex;
	b2Body *body, *checkpoint;
	float *elapsedtime;
	b2Vec2 pos;
	std::vector<sf::IntRect> frames;
	b2Vec2 linvel;

	Player(float &elapsedtime);
	void update();

};

#endif /* PLAYER_HPP_ */
