#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include "GraphicalObject.h"

using namespace std;
using namespace sf;


class Bullet : public GraphicalObject
{
private:

	Vector2f direction;
	float movementSpeed;

public:
	
	Bullet(float pos_x, float pos_y, float dir_x, float dir_y, float movement_speed,string name);
	virtual ~Bullet();

	const FloatRect getBounds() const;
	void update();
	

};

