#include "Enemy.h"

using namespace std;
using namespace sf;

#define PI 3.14159

Enemy::Enemy(string name) : GraphicalObject(name, Vector2f(0.0,0.0)) {
	
	
	this->setScale(Vector2f(1.5f, 1.5f));
	this->currentFrame = IntRect(0, 0, 64, 64);
	this->setTextureRect(currentFrame);
	this->setPosition(rand() % 3000, 0);

	this->movementSpeed = rand() % 150 + 150;
	this->enemyHp = rand() % 2 + 1;
	this->enemyMaxHp = this->enemyHp;
	state = Enemy::Alive;
}

Enemy::~Enemy() {

}

void Enemy::update() {
	this->updateAnimation();
	
}

float Enemy::getDistance(GraphicalObject& player) {
	float distance = 0;
	float x = 0;
	float y = 0;
	x = abs(this->getPosition().x - player.getPosition().x);
	y = abs(this->getPosition().y - player.getPosition().y);
	

	return distance = sqrt(x * x + y * y);
}


void Enemy::updateMove(Player& player) {
	// Pozycja gracza
	getPlayerPos_x = player.getCenter().x;
	getPlayerPos_y = player.getCenter().y;

	float time = elapsed.asSeconds();

	// Pozycja enemy
	getEnemyPos_x = getEnemyPos().left;
	getEnemyPos_y = getEnemyPos().top;

	float dir_x = getPlayerPos_x - getEnemyPos_x;
	float dir_y = getPlayerPos_y - getEnemyPos_y;

	
	float distance = sqrt(dir_x * dir_x + dir_y * dir_y);

	// Wektor jednostkowy, normalizacja aby zachowac kierunek
	if (distance != 0) {
		dir_x /= distance;
		dir_y /= distance;
	}

	
	if (getDistance(player) > 20) {
		this->move(dir_x * time * movementSpeed, dir_y * time * movementSpeed);
	}

	// Kat miedzy graczem a enemy
	float angle = atan2(getPlayerPos_y - getEnemyPos_y, getPlayerPos_x - getEnemyPos_x);
	this->setRotation(angle * 180 / PI + 90);

	elapsed = clock.restart();
}





FloatRect Enemy::getEnemyPos() {
	return getGlobalBounds();
}

void Enemy::updateAnimation() {
	
	if(this->animationTimer.getElapsedTime().asSeconds() >= 0.8f)
	{
		this->currentFrame.left += 64;
		if (this->currentFrame.left >= 160.f)
			this->currentFrame.left = 0;

		this->animationTimer.restart();
		this->setTextureRect(this->currentFrame);
	}
	
}

int Enemy::getEnemyHp() const {
	return this->enemyHp;
}
int Enemy::setEnemyHp(int value) {
	this->enemyHp -= value;
	return this->enemyHp;
}

int Enemy::getEnemyMaxHp() const {
	return this->enemyMaxHp;
}
