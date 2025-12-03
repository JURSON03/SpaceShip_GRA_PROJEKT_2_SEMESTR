#pragma once


#include "GraphicalObject.h"
#include <SFML/Graphics.hpp>
#include "Collision.h"

class Potion : public GraphicalObject
{
private:

	IntRect currentFrame;
	Clock animationTimer;

public:

	enum State {Active, Collected };

	State state;

	Potion();
	~Potion();

	void update();
	void updateAnimation();


};

