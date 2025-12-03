#pragma once
#include "GraphicalObject.h"
#include <SFML/Graphics.hpp>

using namespace std;
using namespace sf;


class Boss : public GraphicalObject
{
private:



	//
	int velocity;
	Clock clock;
	int hp;



public:

	Boss(float pos_x, float pos_y, FloatRect view, float stronger);
	~Boss();

	void update(FloatRect view, GraphicalObject& player);
	float getDistance(GraphicalObject& player);
	void update();
	void updateAngle(GraphicalObject &player);
	void updateMovement(GraphicalObject& player);

	int getHp() {
		return hp;
	}
	void decreaseHp() {
		hp = hp - 1;
	}

};

