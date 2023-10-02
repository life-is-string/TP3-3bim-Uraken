/*
 * type.hpp
 *
 *  Created on: 9 de jun. de 2023
 *      Author: hayde
 */

#ifndef ENGINE_GAMEDATA_HPP_
#define ENGINE_GAMEDATA_HPP_
#include "statemachine.hpp"
#include "stdafx.hpp"

struct GameData{
	StateMachine machine;
	sf::RenderWindow window;
};
typedef std::shared_ptr<GameData> GameDataRef;



#endif /* ENGINE_GAMEDATA_HPP_ */
