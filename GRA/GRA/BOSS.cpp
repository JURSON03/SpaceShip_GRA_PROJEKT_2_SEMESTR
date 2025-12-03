#include "BOSS.h"

using namespace std;
using namespace sf;


Boss::Boss(float pos_x, float pos_y, FloatRect view, float stronger) : GraphicalObject("./TEKSTURY/BOSS/copper_space_fighter.png", Vector2f(pos_x,pos_y))
{
	this->setScale(4.f, 4.f);

	 velocity = rand()% 150 + 50 + stronger;
	 hp = 100+stronger;
}

void Boss::update() {
}

float Boss::getDistance(GraphicalObject& player) {
	float distance = 0;
	float x = 0;
	float y = 0;
	x = abs(this->getGlobalBounds().left - player.getGlobalBounds().left);
	y = abs(this->getGlobalBounds().top - player.getGlobalBounds().top);

	return distance = sqrt(x * x + y * y);
}


Boss::~Boss() {
	cout << "POKONANO BOSSA!" << endl;
}


void Boss::update(FloatRect view, GraphicalObject &player) {

	this->updateAngle(player);
	this->updateMovement(player);
}


void Boss::updateAngle(GraphicalObject& player)
{
	float angle = atan2(player.getPosition().y - this->getPosition().y, player.getPosition().x - this->getPosition().x);
	this->setRotation(angle * 180 / 3.14159 + 90);
}


void Boss::updateMovement(GraphicalObject& player) {

    // Srodek gracza
    float playerCenter_x = player.getGlobalBounds().left + player.getGlobalBounds().width / 2;
    float playerCenter_y = player.getGlobalBounds().top + player.getGlobalBounds().height / 2;

    //Srodek bosa
    float bossCenter_x = this->getGlobalBounds().left + this->getGlobalBounds().width / 2;
    float bossCenter_y = this->getGlobalBounds().top + this->getGlobalBounds().height / 2;

    // wektor przem.
    float getDirection_x = playerCenter_x - bossCenter_x;
    float getDirection_y = playerCenter_y - bossCenter_y;

    // distance
    float distance = sqrt(getDirection_x * getDirection_x + getDirection_y * getDirection_y);

    // normalizacja wektora
    if (distance != 0) {
        getDirection_x /= distance;
        getDirection_y /= distance;
    }


    float time = clock.getElapsedTime().asSeconds();

    this->move(getDirection_x * velocity * time, getDirection_y * velocity * time);

    clock.restart();
}
