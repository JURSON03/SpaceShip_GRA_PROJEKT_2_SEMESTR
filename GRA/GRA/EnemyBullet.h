#pragma once

#include <SFML/Graphics.hpp>
#include "GraphicalObject.h"
#include "Player.h"

using namespace std;
using namespace sf;

class EnemyBullet : public GraphicalObject
{
private:

	Vector2f direction;
	float movementSpeed;
	float angle;
	int damage;

public:
	
	enum State{Active = 0, Destroyed};
	State state;

	EnemyBullet(string name,float pos_x, float pos_y, float dir_x, float dir_y, float movement_speed);
	virtual ~EnemyBullet();

	const FloatRect getBounds() const;
	void update();
	void updateMovement();
	int bulletDamage() const;

};

