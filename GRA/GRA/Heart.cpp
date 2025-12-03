
#include "Heart.h"

using namespace std;
using namespace sf;

Heart::Heart() :  GraphicalObject("./TEKSTURY/HEART/HeartsAnim.png", Vector2f(1500.f,1500.f))
{
	this->currentFrame = IntRect(0, 80, 16, 16);
	this->setTextureRect(currentFrame);
	this->setScale(4.f, 4.f);
	// this->setPosition(rand() % 1900 + 500, rand() % 1900 + 500);
	this->setPosition(rand() % 1900 + 500, rand() % 1900 + 500);
	this->State = Heart::Active;
}


Heart::~Heart() {

}

void Heart::update() {
	this->updateAnimation();
}


void Heart::updateAnimation()
{
	if(animationTimer.getElapsedTime().asSeconds() >= 0.09f){
	currentFrame.left += 16;
	if (currentFrame.left >= 96.f) {
		currentFrame.left = 0.f;
	}
	animationTimer.restart();
	setTextureRect(currentFrame);
}

}
