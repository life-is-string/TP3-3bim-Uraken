/*
 * menustate.cpp
 *
 *  Created on: 15 de out. de 2023
 *      Author: hayde
 */
/*
 * menustate.cpp
 *
 *  Created on: 15 de out. de 2023
 *      Author: hayde
 */
#include "menustate.hpp"

MenuState::MenuState(GameDataRef data) {
	this->data = data;
	selected_index = 0;
	enter = false;
}
void MenuState::init() {

	bg_tex.loadFromFile("assets/menu_bgd.png");
	background.setTexture(bg_tex);
	tut_tex.loadFromFile("assets/tutorial.png");
	tutorial.setTexture(tut_tex);
	arcadefont.loadFromFile("assets/daydream.ttf");
	menuMusic.openFromFile("assets/audio.wav");
	menuMusic.setLoop(true);
	menuMusic.setVolume(40);
	menuMusic.play();
	enterBuf.loadFromFile("assets/enter_menu.wav");
	enterOption.setBuffer(enterBuf);
	selectBuf.loadFromFile("assets/switch.ogg");
	select.setBuffer(selectBuf);

	menu[0].setString("Play");
	menu[1].setString("Options");
	menu[2].setString("Exit");
	title.setString("URAKEN");

	sf::FloatRect textbounds;
	titlefont.loadFromFile("assets/menu_font.ttf");
	title.setFont(titlefont);
	title.setCharacterSize(160);
	title.setCharacterSize(120);
	textbounds = title.getLocalBounds();
	title.setOrigin(textbounds.width / 2, textbounds.height / 2);
	title.setFillColor(sf::Color { 186, 35, 38 });
	title.setPosition(ww / 2, 160);

	float distance = -12.5;

	for (int i = 0; i < 3; i++) {
		menu[i].setFont(arcadefont);
		menu[i].setFillColor(unselected);
		menu[i].setCharacterSize(60);
		textbounds = menu[i].getLocalBounds();
		menu[i].setOrigin(textbounds.width / 2, textbounds.height / 2);
		menu[i].setPosition(ww / 2, wh / 2 + distance);
		distance += 100;
	}

	selected_index = 0;
	menu[selected_index].setFillColor(selected);

}
void MenuState::draw() {
	data->window.clear(sf::Color::White);
	data->window.draw(background);
	if (inOptions) {
		data->window.draw(tutorial);
	} else {
		data->window.draw(title);
		for (int i = 0; i < 3; i++) {
			data->window.draw(menu[i]);
		}
	}
	data->window.display();
}

void MenuState::update() {
	if (selected_index > 0 && moveUp) { //it will only move up when current selected option is not the first one
		select.play();
		menu[selected_index].setFillColor(unselected);
		selected_index--;
		menu[selected_index].setFillColor(selected);
		moveUp = false;
	}
	if (selected_index < 2 && moveDown) { //it will only move up when current selected option is not the last one
		select.play();
		menu[selected_index].setFillColor(unselected);
		selected_index++;
		menu[selected_index].setFillColor(selected);
		moveDown = false;
	}
	if (enter) {
		options();
	}
}

void MenuState::handleInput() {
	sf::Event event;
	while (data->window.pollEvent(event)) {

		if (event.type == sf::Event::Closed) {
			data->window.close();
		}
		if (event.type == sf::Event::KeyPressed) {
			if (event.key.code == sf::Keyboard::Up && !inOptions) {
				moveUp = true;
				break;
			}
			if (event.key.code == sf::Keyboard::Down && !inOptions) {
				moveDown = true;
				break;
			}
			if (event.key.code == sf::Keyboard::Enter && !inOptions) {
				enter = true;
				enterOption.play();
				break;
			}
			if (event.key.code == sf::Keyboard::Escape && inOptions) {
				inOptions = false;
				break;
			}
		}

	}
}

void MenuState::options() { //happens when entering an option
	switch (selected_index) { //current index entered
	case 0:
		menuMusic.setLoop(false);
		menuMusic.stop();
		data->machine.addState(StateRef(new GameState(data)), true);
		enter = false;
		break;
	case 1:
		inOptions = true;
		enter = false;
		break;
	case 2:
		data->window.close();
		break;
	}
}



