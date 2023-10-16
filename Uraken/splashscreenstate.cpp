/*
 * splashscreenstate.cpp
 *
 *  Created on: 15 de out. de 2023
 *      Author: hayde
 */
#include "splashscreenstate.hpp"
#include <iostream>
SplashScreen::SplashScreen(GameDataRef data) :
		data(data) {
}
;
void SplashScreen::init() {
	tex.loadFromFile("assets/devdogs_logo.png");
	logo.setTexture(tex);
	logo.setOrigin(logo.getGlobalBounds().width/2, logo.getLocalBounds().height/2);
	logo.setPosition(ww / 2, wh / 2);
	logo.setScale(0.9,0.9);
	logo.setColor(sf::Color{255,255,255,a});
}
void SplashScreen::update() {
	if(!fade){
		if(a < 255){
			a+=5;
		}
		if(a > 255){
			a = 255;
		}
		logo.setColor(sf::Color{255,255,255,a});
	}
	if (clock.getElapsedTime().asSeconds() > 4.4) {
		fade = true;
		a-=5;
		if(a < 0){
			a = 0;
			data->machine.addState(StateRef(new MenuState(data)), true);
		}
		logo.setColor(sf::Color{255,255,255,a});
	}
}
void SplashScreen::handleInput() {
	sf::Event event;
	while (data->window.pollEvent(event)) {

		if (event.type == sf::Event::Closed) {
			data->window.close();
		}
	}
}
void SplashScreen::draw() {
	data->window.clear(sf::Color::White);
	data->window.draw(logo);
	data->window.display();
}

