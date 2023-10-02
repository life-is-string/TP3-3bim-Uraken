/*
 * statemachine.hpp
 *
 *  Created on: 3 de jun. de 2023
 *      Author: hayde
 */
#pragma once
#ifndef STATE_HPP_
#define STATE_HPP_
#include "stdafx.hpp"

class State{
public:
	virtual ~State(){};
	virtual void init(){};
	virtual void update(){};
	virtual void draw(){};
};


#endif /* STATE_HPP_ */
