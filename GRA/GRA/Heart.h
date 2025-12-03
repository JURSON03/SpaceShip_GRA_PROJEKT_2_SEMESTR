#pragma once

#include "GraphicalObject.h"
#include "Collision.h"

#include <iostream>
#include <SFML/Graphics.hpp>

using namespace std;
using namespace sf;

class Heart : public GraphicalObject
{
private:

	IntRect currentFrame;
	Clock animationTimer;

public:

	enum healState { Active, Collected };

	healState State;

	Heart();
	~Heart();

	void update();
	void updateAnimation();


};

