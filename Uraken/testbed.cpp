/*
 * testbed.cpp
 *
 *  Created on: 18 de ago. de 2023
 *      Author: user
 */
#include "testbed.hpp"
#include <typeinfo>

void Testbed::displayWorld() {
	world->Step(1.0 / 60, int32(8), int32(3)); //progress the physics simulation
	window.clear(sf::Color::Green);
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
	shape->setFillColor(sf::Color::White);
	element->SetUserData(shape);

	//pointer for graphical representation
	return element;
}
b2Body* Testbed::createElement(int x, int y, int width, int height,
		b2BodyType type, sf::Texture *tex) {
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
	fixtureDef.density = 4;
	fixtureDef.friction = 0.4;
	fixtureDef.shape = &b2shape;

	b2Body *element = world->CreateBody(&bodyDef);
	element->CreateFixture(&fixtureDef);
	sf::Sprite *sprite = new sf::Sprite(*tex);
	sprite->setOrigin(width / 2.0, height / 2.0);
	sprite->setPosition(sf::Vector2f(x, y));
	element->SetUserData(sprite);
	return element;
}
Testbed::Testbed() {
	window.create(sf::VideoMode(800, 600, 32), "Uraken");
	window.setFramerateLimit(60);
	b2Vec2 gravity(0.f, 9.8f);
	world = new b2World(gravity);
	player.body = createElement(500, 100, 52, 64, b2_dynamicBody, player.tex);
	ground = createElement(400, 590, 800, 30, b2_staticBody); //creates the ground

	//walls
	createElement(-15, 300, 30, 600, b2_staticBody);
	createElement(815, 300, 30, 600, b2_staticBody);

	//creates platforms
	platforms.push_back(createElement(200, 450, 100, 30, b2_staticBody));
	platforms.push_back(createElement(500, 200, 100, 30, b2_staticBody));


}
void Testbed::Run() {
	while (window.isOpen()) {
		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed)
				window.close();
		}
		player.handleInputs();
		displayWorld();
	}
}

