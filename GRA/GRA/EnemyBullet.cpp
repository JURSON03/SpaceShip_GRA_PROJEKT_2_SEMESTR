#include "EnemyBullet.h"

#include <math.h>
#include "Collision.h"

#define PI 3.14159

using namespace std;
using namespace sf;




EnemyBullet::EnemyBullet(string name,float pos_x, float pos_y, float target_x, float target_y, float movement_speed)
    : GraphicalObject(name, Vector2f(pos_x, pos_y)), movementSpeed(movement_speed)
{

    this->damage = rand() % 2 + 1;

    // wektor przemieszczenia
    direction.x = (target_x - pos_x);
    direction.y = (target_y - pos_y);

    // Wektor jednostkowy w kierunku gracza
   
    float length = sqrt(direction.x * direction.x + direction.y * direction.y);
    if (length != 0) {
        direction.x /= length;
        direction.y /= length;
    }
   
   
        // Obliczenie kata dla obrotu strzaly   
        angle = atan2(direction.y, direction.x) * 180 / PI;
        rotate(angle + 90);
    
    
 
    this->state = Active;

}


EnemyBullet::~EnemyBullet()
{
}

const FloatRect EnemyBullet::getBounds() const
{
	return this->getGlobalBounds();
}

void EnemyBullet::update() {
	move(this->direction.x * movementSpeed, this->direction.y * movementSpeed);
}


void EnemyBullet::updateMovement() {

	move(this->direction.x * movementSpeed, this->direction.y * movementSpeed);

}

int EnemyBullet::bulletDamage() const {
    return damage;
}

