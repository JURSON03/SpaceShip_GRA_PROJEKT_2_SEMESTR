#include "Asteroid.h"
#include "Collision.h"

using namespace std;
using namespace sf;

Asteroid::Asteroid(float pos_x, float pos_y) : GraphicalObject("TEKSTURY/KOMETA/ASTEROID.png", Vector2f(0, 0))
{
	this->speed = rand() % 6 + 2;
	this->asteroidSize = rand() % 6 + 2;
	currentFrame = IntRect(0, 0, 80, 80);
	this->setTextureRect(IntRect(0, 0, 96, 96));
	this->setScale(asteroidSize, asteroidSize);
	this->setOrigin(96 / 2, 96 / 2);
	this->setPosition(pos_x, pos_y);

	// Variables 
	this->hp = rand() % 3 + 1;
	// cout << hp << endl;
	state = Active;

}

Asteroid::~Asteroid() = default;



void Asteroid::update()
{
	this->move(0.1f, speed*0.5f);
	this->rotate(0.25f);
	
}

bool Asteroid::collision(GraphicalObject* ob)
{
	if (Collision::pixelPerfectTest(*this, *ob)) {
		state = Exploding;
		return true;
	}
	else {
		return false;
	}
}

void Asteroid::updateAnimation()
{
	if (state == Exploding && animationTimer.getElapsedTime().asSeconds() >= 0.065f) {
		currentFrame.left += 96;
		if (currentFrame.left >= 768.f) { 
			state = Destroyed; 
		}
		animationTimer.restart();
		setTextureRect(currentFrame);
	}
}

bool Asteroid::isDestroyed() const
{
	if (state == Destroyed) {
		return true;
	}
	else return false;
}

int Asteroid::getAsteroidSize()
{
	return asteroidSize;
}

void Asteroid::decreaseHeal() {
	if (state == Asteroid::Active && hp > 0 && animationTimer.getElapsedTime().asSeconds() >= 0.075f) {
		currentFrame.left += 96;
		setTextureRect(currentFrame);
	}
	hp = hp - 1;

}

int Asteroid::getHp() const{
	return hp;
}

int Asteroid::setHp() {
	return hp - 1;
}