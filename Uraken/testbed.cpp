/*
 * testbed.cpp
 *
 *  Created on: 18 de ago. de 2023
 *      Author: Grupo 8
 */
#include "testbed.hpp"
#include "player.hpp"
#include <typeinfo>

void Testbed::displayWorld() {

	window.clear();
	world->Step(1.0 / 60, int32(8), int32(3)); //progress the physics simulation

	window.draw(fundo->background0);
	window.draw(fundo->background);
	window.draw(fundo->background2);
	window.draw(fundo->background3);
	window.draw(fundo->background4);
	window.draw(fundo->background5);
	window.draw(fundo->background6);
	window.draw(fundo->background7);
	window.draw(fundo->background8);
	window.draw(fundo->background9);
	window.draw(fundo->background10);
	window.draw(fundo->background11);
	window.draw(fundo->background12);
	//fundo->draw(window);

	view.setSize(900, 600); //setting the size of the view 900, 600
	view.zoom(0.85f);
	vpos.x = player->body->GetPosition().x * 32;
	vpos.y = player->body->GetPosition().y * 26;
	view.setCenter(vpos);
	window.setView(view);

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

	window.draw(fueldisplay->sprite);

	window.display();
}
b2Body* Testbed::createElement(int x, int y, int width, int height,
		b2BodyType type, sf::Color color = {233,150,122}) {
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
	shape->setFillColor(color);
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
	music.openFromFile("assets/naruto-blue-bird.wav");
	music.setLoop(true);
	music.setVolume(25);
	music.play();
	fundo = new Fundo;
	//Icone da janela.
	sf::Image image = sf::Image { };
	image.loadFromFile("assets/ninja.png");
	window.setIcon(image.getSize().x, image.getSize().y, image.getPixelsPtr());

	world = new b2World(gravity);
	player = new Player(elapsedtime);
	fueldisplay = new Fuel;
	player->body = createElement(130, 150, 52, 64, b2_dynamicBody, player->tex,
			player->frames[0]);

	//Paredes do jogo (para definir os limites de voo)
	//ground
	ground = createElement(200, 660, 16000, 170, b2_staticBody,
			sf::Color::Transparent); //creates the ground

	createElement(200, 692, 16000, 170, b2_staticBody,
				sf::Color{159,159,159});

	//left wall
	createElement(-320, 660, 16, 1800, b2_staticBody,
			sf::Color::Transparent);

	//right wall
	createElement(7600, 660, 16, 1800, b2_staticBody,
			sf::Color::Transparent);

	//up wall
	createElement(-985.8, -530, 20000, 1000, b2_staticBody,
			sf::Color{176,176,176});

	//creates platforms
	for (int i = 0; i < 20; i++) {
		Platform platform(i + 1);
		platforms.push_back(platform);
	}
	platforms[0].body = (createElement(130, 510, 112, 31, b2_staticBody)); //1
	platforms[1].body = (createElement(420, 440, 112, 31, b2_staticBody)); //2
	platforms[2].body = (createElement(770, 490, 112, 31, b2_staticBody)); //3
	platforms[3].body = (createElement(1150, 430, 112, 31, b2_staticBody)); //4
	platforms[4].body = (createElement(1500, 480, 112, 31, b2_staticBody)); //5
	platforms[5].body = (createElement(1850, 460, 112, 31, b2_staticBody)); //6
	platforms[6].body = (createElement(2180, 400, 112, 31, b2_staticBody)); //7
	platforms[7].body = (createElement(2550, 320, 112, 31, b2_staticBody)); //8
	platforms[8].body = (createElement(2850, 402, 112, 31, b2_staticBody)); //9
	platforms[9].body = (createElement(3260, 460, 112, 31, b2_staticBody)); //10
	platforms[10].body = (createElement(3660, 470, 112, 31, b2_staticBody)); //11
	platforms[11].body = (createElement(4000, 530, 112, 31, b2_staticBody)); //12
	platforms[12].body = (createElement(4400, 490, 112, 31, b2_staticBody)); //13
	platforms[13].body = (createElement(4800, 530, 112, 31, b2_staticBody)); //14
	platforms[14].body = (createElement(5195, 475, 112, 31, b2_staticBody)); //15
	platforms[15].body = (createElement(5600, 530, 112, 31, b2_staticBody)); //16
	platforms[16].body = (createElement(5920, 450, 112, 31, b2_staticBody)); //17
	platforms[17].body = (createElement(6300, 515, 112, 31, b2_staticBody)); //18
	platforms[18].body = (createElement(6700, 465, 112, 31, b2_staticBody)); //19
	platforms[19].body = (createElement(7200, 430, 112, 31, b2_staticBody)); //20

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
		//verifica se a "caixa" do player esta em contato com a plataforma do chão
		if (player->isPlayerOnPlatform(ground)) {
			window.close(); // Fecha o jogo se o jogador cair no chão
		}

		player->update();
		fueldisplay->update(player->fuel, vpos);
		displayWorld();
	}

}

