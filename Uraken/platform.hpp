/*
 * platform.hpp
 *
 *  Created on: 31 de ago. de 2023
 *      Author: hayde
 */

#ifndef PLATFORM_HPP_
#define PLATFORM_HPP_
#include <SFML/Graphics.hpp>
#include <Box2D/Box2D.h>
#include <cstdio>
class Platform{
public:
	b2Body* body;
	int num;
	Platform(int num){
		this->num = num;
		body = NULL;
	}
};



#endif /* PLATFORM_HPP_ */
