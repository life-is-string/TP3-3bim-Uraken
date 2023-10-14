/*
 * testbed.cpp
 *
 *  Created on: 18 de ago. de 2023
 *      Author: Grupo 8
 */
#include "gamestate.hpp"

void GameState::draw() {

	data->window.clear();
	//progress the physics simulation
	if (!freezeAll) {
		world->Step(1.0 / 60, int32(8), int32(3));
	}
	for (auto i : bg->backgrounds) {
		data->window.draw(i);
	}


	//View update
	view.setSize(900, 600);
	view.zoom(0.85f);
	vpos.x = player->body->GetPosition().x * 32;
	vpos.y = player->body->GetPosition().y * 26;
	view.setCenter(vpos);
	data->window.setView(view);


	sf::Texture fundoBranco;
	fundoBranco.loadFromFile("assets/fundoMinimapa2.png");
	sf::Sprite fundoBrancoo;
	fundoBrancoo.setTexture(fundoBranco);
	//fundoBrancoo.setColor( { 255, 255, 255, 190 });
	fundoBrancoo.setPosition(vpos.x - -138, vpos.y - 262);
	fundoBrancoo.setScale(0.5, 0.5);
	data->window.draw(fundoBrancoo);

	for (auto i : bg->backgrounds) {
		data->window.draw(i);
	}

	if (!freezeAll) {
		winscreen.setPosition(vpos.x,
				vpos.y + winscreen.getGlobalBounds().height);
		winposy = winscreen.getPosition().y;
	}
	//Converts the simulation to the graphical elements
	for (b2Body *body = world->GetBodyList(); body != nullptr;
			body = body->GetNext()) { //this for sets as "i" a body from the world, and iterates to the next one until there isn't more bodies
		if (typeid(body->GetUserData()).name() == "class Sprite") {
			sf::Sprite *sprite = static_cast<sf::Sprite*>(body->GetUserData());
			sprite->setPosition(
					converter::metersToPixels(body->GetPosition().x),
					converter::metersToPixels(body->GetPosition().y));
			sprite->setRotation(converter::radToDeg<double>(body->GetAngle()));
			data->window.draw(*sprite);

		} else {
			sf::Shape *shape = static_cast<sf::Shape*>(body->GetUserData()); //grabs the graphical representation pointer
			//Converts the physics simulation data to graphics
			shape->setPosition(converter::metersToPixels(body->GetPosition().x),
					converter::metersToPixels(body->GetPosition().y));
			shape->setRotation(converter::radToDeg<double>(body->GetAngle()));
			data->window.draw(*shape);
		}
	}

	data->window.draw(fueldisplay->sprite);

	for (auto i : bamboos) {
		data->window.draw(*i);
	}

	if (freezeAll) {
		data->window.draw(winscreen);
		std::cout << winposy - winscreen.getGlobalBounds().height << "\n"
				<< winscreen.getPosition().y;
		if (winscreen.getPosition().y
				> winposy - winscreen.getGlobalBounds().height)
			winscreen.move(0, -1.8);
	}
	//view do minimapa
	minimap.setSize(500, 390);
	minimap.zoom(1.6f);
	minimap.setViewport(sf::FloatRect(0.68, 0, 0.32, 0.36));
	minimap.setCenter(vpos);
	data->window.setView(minimap);

	for (auto i : bg->backgrounds) {
		data->window.draw(i);
	}

	if (!freezeAll) {
		winscreen.setPosition(vpos.x,
				vpos.y + winscreen.getGlobalBounds().height);
		winposy = winscreen.getPosition().y;
	}
	//Converts the simulation to the graphical elements
	for (b2Body *body = world->GetBodyList(); body != nullptr;
			body = body->GetNext()) { //this for sets as "i" a body from the world, and iterates to the next one until there isn't more bodies
		if (typeid(body->GetUserData()).name() == "class Sprite") {
			sf::Sprite *sprite = static_cast<sf::Sprite*>(body->GetUserData());
			sprite->setPosition(
					converter::metersToPixels(body->GetPosition().x),
					converter::metersToPixels(body->GetPosition().y));
			sprite->setRotation(converter::radToDeg<double>(body->GetAngle()));
			data->window.draw(*sprite);

		} else {
			sf::Shape *shape = static_cast<sf::Shape*>(body->GetUserData()); //grabs the graphical representation pointer
			//Converts the physics simulation data to graphics
			shape->setPosition(converter::metersToPixels(body->GetPosition().x),
					converter::metersToPixels(body->GetPosition().y));
			shape->setRotation(converter::radToDeg<double>(body->GetAngle()));
			data->window.draw(*shape);
		}
	}

	data->window.draw(fueldisplay->sprite);

	for (auto i : bamboos) {
		data->window.draw(*i);
	}

	if (freezeAll) {
		data->window.draw(winscreen);
		std::cout << winposy - winscreen.getGlobalBounds().height << "\n"
				<< winscreen.getPosition().y;
		if (winscreen.getPosition().y
				> winposy - winscreen.getGlobalBounds().height)
			winscreen.move(0, -1.8);
	}
	data->window.display();
}
b2Body* GameState::createElement(int x, int y, int width, int height,
		b2BodyType type, sf::Color color = sf::Color::Transparent) {
	//Box2d: creates a polygon object using pixel_to_meters dimensions
	b2BodyDef bodyDef;

	//defines body initial position:
	bodyDef.position.Set(converter::pixelsToMeters<double>(x),
			converter::pixelsToMeters<double>(y));

	//defines the physics:
	bodyDef.type = type; //defines if its dynamic or fixed
	b2PolygonShape b2shape; //square-like shape (useful for collisions)
	b2shape.SetAsBox(converter::pixelsToMeters<double>(width / 2),
			converter::pixelsToMeters<double>(height / 2));

	//physics attributes def
	b2FixtureDef fixtureDef;
	fixtureDef.density = 1.0;
	fixtureDef.friction = 0.4;
	fixtureDef.restitution = 0.1;
	fixtureDef.shape = &b2shape;

	b2Body *element = world->CreateBody(&bodyDef);
	element->CreateFixture(&fixtureDef);

	//visible shape attributes
	sf::Shape *shape = new sf::RectangleShape(sf::Vector2f(width, height));
	shape->setOrigin(width / 2.0, height / 2.0);
	shape->setPosition(sf::Vector2f(x, y));
	shape->setFillColor(color);
	element->SetUserData(shape);

	//pointer for graphical representation
	return element;
}
b2Body* GameState::createElement(int x, int y, int width, int height,
		b2BodyType type, sf::Texture *tex, sf::IntRect frame) {
	//Box2d: creates a polygon object using pixel_to_meters dimensions
	b2BodyDef bodyDef;

	//defines body initial position:
	bodyDef.position.Set(converter::pixelsToMeters<double>(x),
			converter::pixelsToMeters<double>(y));

	//defines the physics:
	bodyDef.type = type; //defines if its dynamic or fixed
	b2PolygonShape b2shape; //square-like shape (useful for collisions)
	b2shape.SetAsBox(converter::pixelsToMeters<double>(width / 2),
			converter::pixelsToMeters<double>(height / 2));

	//physics attributes def
	b2FixtureDef fixtureDef;
	fixtureDef.density = 5;
	fixtureDef.friction = 0.4;
	fixtureDef.shape = &b2shape;

	b2Body *element = world->CreateBody(&bodyDef);
	element->CreateFixture(&fixtureDef);
	sf::Sprite *sprite = new sf::Sprite(*tex, frame);
	sprite->setOrigin(width / 2.0, height / 2.0);
	sprite->setPosition(sf::Vector2f(x, y));
	element->SetUserData(sprite);
	return element;
}

void GameState::init() {

	//b2World setup
	b2Vec2 gravity(0.f, 9.f);
	world = new b2World(gravity);

	//Background music setup
	music.openFromFile("assets/naruto-blue-bird.wav");
	music.setLoop(true);
	music.setVolume(25);
	music.play();

	//Game assets setup
	sf::Texture *winTex = new sf::Texture;
	winTex->loadFromFile("assets/win.png");
	winscreen.setTexture(*winTex);
	winscreen.setOrigin(winscreen.getGlobalBounds().width / 2,
			winscreen.getGlobalBounds().height / 2);
	winscreen.setScale(0.8, 0.8);
	bg = new Background;
	player = new Player(elapsedtime);
	fueldisplay = new Fuel;
	player->body = createElement(130, 452, 52, 64, b2_dynamicBody, player->tex,
			player->frames[0]);

	//Walls (flight limits)

	//ground
	ground = createElement(200, 660, 16000, 170, b2_staticBody,
			sf::Color::Transparent);

	//lake
	createElement(200, 692, 16000, 170, b2_staticBody,
			sf::Color { 159, 159, 159 });

	//left wall
	createElement(-320, 660, 16, 1800, b2_staticBody, sf::Color::Transparent);

	//sky
	createElement(-985.8, -530, 20000, 1000, b2_staticBody, sf::Color { 176,
			176, 176 });

	//Platforms setup

	platforms.push_back(createElement(130, 510, 112, 31, b2_staticBody)); //1
	platforms.push_back(createElement(420, 250, 112, 31, b2_staticBody)); //2
	platforms.push_back(createElement(850, 499, 112, 31, b2_staticBody)); //3
	platforms.push_back(createElement(1290, 110, 112, 31, b2_staticBody)); //4
	platforms.push_back(createElement(1690, 350, 112, 31, b2_staticBody)); //5
	platforms.push_back(createElement(2280, 150, 112, 31, b2_staticBody)); //6
	platforms.push_back(createElement(2559, 350, 112, 31, b2_staticBody)); //7
	platforms.push_back(createElement(3090, 100, 112, 31, b2_staticBody)); //8
	platforms.push_back(createElement(3560, 402, 112, 31, b2_staticBody)); //9
	platforms.push_back(createElement(3860, 205, 112, 31, b2_staticBody)); //10
	platforms.push_back(createElement(4200, 510, 112, 31, b2_staticBody)); //11
	platforms.push_back(createElement(4650, 210, 112, 31, b2_staticBody)); //12
	platforms.push_back(createElement(4950, 420, 112, 31, b2_staticBody)); //13
	platforms.push_back(createElement(5365, 104, 112, 31, b2_staticBody)); //14
	platforms.push_back(createElement(5520, 375, 112, 31, b2_staticBody)); //15
	platforms.push_back(createElement(5920, 230, 112, 31, b2_staticBody)); //16
	platforms.push_back(createElement(6250, 470, 112, 31, b2_staticBody)); //17
	platforms.push_back(createElement(6530, 105, 112, 31, b2_staticBody)); //18
	platforms.push_back(createElement(6850, 465, 112, 31, b2_staticBody)); //19
	platforms.push_back(createElement(7300, 120, 112, 31, b2_staticBody)); //20

	//Bamboo platforms sprites setup
	sf::Texture *bambootex = new sf::Texture;
	bambootex->loadFromFile("assets/bamboo.png");
	for (int i = 0; i < 20; i++) {
		sf::Sprite *bamboo;
		bamboo = new sf::Sprite;
		bamboo->setTexture(*bambootex);
		bamboo->setOrigin(112 / 2, 32 / 2);
		bamboos.push_back(bamboo);
	}
	for (int i = 0; i < 20; i++) {
		bamboos[i]->setPosition(
				converter::metersToPixels(platforms[i]->GetPosition().x),
				converter::metersToPixels(platforms[i]->GetPosition().y));
	}

	//Checkpoint and collision setup
	player->checkpoint = platforms[0];
	contactListener = new MyContactListener(player, platforms, ground,
			&data->window, &freezeAll, &music);
	world->SetContactListener(contactListener);
}

GameState::GameState(GameDataRef data) {
	this->data = data;
}

void GameState::update() {
	dt = clock.restart().asSeconds();
	elapsedtime += dt;
	if (elapsedtime >= 0.9)
		elapsedtime = 0.3;
	sf::Event event;
	while (data->window.pollEvent(event)) {
		if (event.type == sf::Event::Closed)
			data->window.close();
	}
	if (!freezeAll) {
		player->update();
		fueldisplay->update(player->fuel, vpos);
	}
}

