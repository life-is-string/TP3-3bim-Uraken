/*
 * testbed.cpp
 *
 *  Created on: 18 de ago. de 2023
 *      Author: Grupo 8
 */
#include "testbed.hpp"
#include <typeinfo>

void Testbed::displayWorld() {

	window.clear();
	world->Step(1.0 / 60, int32(8), int32(3)); //progress the physics simulation

	//fundo = new Fundo;
	//window.draw(fundo);

	view.setSize(900, 600); //setting the size of the view 700, 400
	view.zoom(0.9f);
	window.setView(view);
	sf::Vector2f pos;
	pos.x = player->body->GetPosition().x * 32;
	pos.y = player->body->GetPosition().y * 22;
	view.setCenter(pos);

	for (b2Body *body = world->GetBodyList(); body != nullptr;
			body = body->GetNext()) { //this for sets as "i" a body from the world, and iterates to the next one until there isn't more bodies
		if (typeid(body->GetUserData()).name() == "class Sprite") {
			sf::Sprite *sprite = static_cast<sf::Sprite*>(body->GetUserData());
			sprite->setPosition(
					converter::metersToPixels(body->GetPosition().x),
					converter::metersToPixels(body->GetPosition().y));
			sprite->setRotation(converter::radToDeg<double>(body->GetAngle()));
			window.draw(*sprite);

		} else {
			sf::Shape *shape = static_cast<sf::Shape*>(body->GetUserData()); //grabs the graphical representation pointer
			//Converts the physics simulation data to graphics
			shape->setPosition(converter::metersToPixels(body->GetPosition().x),
					converter::metersToPixels(body->GetPosition().y));
			shape->setRotation(converter::radToDeg<double>(body->GetAngle()));
			window.draw(*shape);
		}
	}
	window.display();
}
b2Body* Testbed::createElement(int x, int y, int width, int height,
		b2BodyType type) {
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
	fixtureDef.restitution = 0.3;
	fixtureDef.shape = &b2shape;

	b2Body *element = world->CreateBody(&bodyDef);
	element->CreateFixture(&fixtureDef);

	//visible shape attributes
	sf::Shape *shape = new sf::RectangleShape(sf::Vector2f(width, height));
	shape->setOrigin(width / 2.0, height / 2.0);
	shape->setPosition(sf::Vector2f(x, y));
	shape->setFillColor(sf::Color::Blue);
	element->SetUserData(shape);

	//pointer for graphical representation
	return element;
}
b2Body* Testbed::createElement(int x, int y, int width, int height,
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

Testbed::Testbed() {
	window.create(sf::VideoMode(900, 600, 32), "Uraken");
	window.setFramerateLimit(60);
	b2Vec2 gravity(0.f, 9.f);

	//Icone da janela.
	sf::Image image = sf::Image { };
	image.loadFromFile("assets/ninja.png");
	window.setIcon(image.getSize().x, image.getSize().y, image.getPixelsPtr());

	world = new b2World(gravity);
	player = new Player(elapsedtime);
	player->body = createElement(130, 150, 52, 64, b2_dynamicBody, player->tex,
			player->frames[0]);

	//cria o chão
	ground = createElement(200, 620, 20000, 90, b2_staticBody); //creates the
	groundElement.push_back(ground); //vector for ground, separate to test collision differently

	//up wall
	createElement(890, -55, 20000, 65, b2_staticBody);

	//creates platforms
	platforms.push_back(createElement(130, 510, 112, 31, b2_staticBody)); //1
	platforms.push_back(createElement(420, 440, 112, 31, b2_staticBody)); //2
	platforms.push_back(createElement(770, 490, 112, 31, b2_staticBody)); //3
	platforms.push_back(createElement(1150, 430, 112, 31, b2_staticBody)); //4
	platforms.push_back(createElement(1500, 480, 112, 31, b2_staticBody)); //5
	platforms.push_back(createElement(1850, 460, 112, 31, b2_staticBody)); //6
	platforms.push_back(createElement(2180, 400, 112, 31, b2_staticBody)); //7
	platforms.push_back(createElement(2550, 320, 112, 31, b2_staticBody)); //8
	platforms.push_back(createElement(2850, 402, 112, 31, b2_staticBody)); //9
	platforms.push_back(createElement(3260, 460, 112, 31, b2_staticBody)); //10
	platforms.push_back(createElement(3660, 470, 112, 31, b2_staticBody)); //11
	platforms.push_back(createElement(4000, 530, 112, 31, b2_staticBody)); //12
	platforms.push_back(createElement(4400, 490, 112, 31, b2_staticBody)); //13
	platforms.push_back(createElement(4800, 530, 112, 31, b2_staticBody)); //14
	platforms.push_back(createElement(5195, 475, 112, 31, b2_staticBody)); //15
	platforms.push_back(createElement(5600, 530, 112, 31, b2_staticBody)); //16
	platforms.push_back(createElement(5920, 450, 112, 31, b2_staticBody)); //17
	platforms.push_back(createElement(6300, 515, 112, 31, b2_staticBody)); //18
	platforms.push_back(createElement(6700, 465, 112, 31, b2_staticBody)); //19
	platforms.push_back(createElement(7200, 430, 112, 31, b2_staticBody)); //20

}
void Testbed::Run() {
	while (window.isOpen()) {
		dt = clock.restart().asSeconds();
		elapsedtime += dt;
		if (elapsedtime >= 0.9)
			elapsedtime = 0.3;
		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed)
				window.close();
		}
		player->handleInputs();
		player->animate();
		displayWorld();
	}
}

