
#include "Bullet.h"
#include <math.h>
#include "Collision.h"

using namespace std;
using namespace sf;




Bullet::Bullet(float pos_x, float pos_y, float dir_x, float dir_y, float movement_speed, string name) : GraphicalObject(name,Vector2f(pos_x,pos_y))
{

	setPosition(pos_x, pos_y);
	this->direction.x = dir_x;
	this->direction.y = dir_y;
	this->movementSpeed = movement_speed;
	
}

Bullet::~Bullet()
{
}

const FloatRect Bullet::getBounds() const
{	
	return this->getGlobalBounds();
}

void Bullet::update()
{
	// Movement
	this->move(this->movementSpeed * this->direction.x, this->movementSpeed * this->direction.y);
}

