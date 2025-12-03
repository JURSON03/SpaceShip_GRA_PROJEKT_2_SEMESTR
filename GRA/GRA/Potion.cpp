#include "Potion.h"


using namespace std;
using namespace sf;

Potion::Potion() : GraphicalObject("./TEKSTURY/POTION/Potion1.png", Vector2f(1500.f, 1500.f))
{
	this->state = State::Active;
	this->currentFrame = IntRect(0, 0, 32, 32);
	this->setTextureRect(currentFrame);
	this->setScale(3.f, 3.f);
	
	this->setPosition(rand() % 1900 + 500, rand() % 1900 + 500);
}


Potion::~Potion() = default;

void Potion::update() {
	this->updateAnimation();
	
}


void Potion::updateAnimation()
{
	if (animationTimer.getElapsedTime().asSeconds() >= 0.09f) {
		currentFrame.left += 32;
		if (currentFrame.left >= 128) {
			currentFrame.left = 0;
		}
		animationTimer.restart();
		setTextureRect(currentFrame);
	}

}
