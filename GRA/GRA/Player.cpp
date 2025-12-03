
#include "Player.h"
#include "Collision.h"

using namespace std;
using namespace sf;


const Vector2f& Player::getPos() const
{
	return this->getPosition();
}




void Player::initSprite()
{
	// Ustawienie tekstury do sprite
	this->setScale(Vector2f(1.5f, 1.5f));
	this->currentFrame = IntRect(128, 0, 64, 64);
	this->setTextureRect(currentFrame);
	this->setPosition(1500.f, 1500.f);

}



Player::Player() : GraphicalObject("./TEKSTURY/PLAYER/Spaceship_Red64-Sheet.png",Vector2f(0.f,0.f))
{
	this->movementSpeed = 400.f;  // Basic 400.f
	this->initSprite();
	this->initVariables();
	this->playerHp = 10.f;		// Basic 10			//////////////////////////////////////////////////////////////////////////////////
	this->playerMaxHp = 10.f;
	this->attackSpeed = 6.f;
	this->points = 0;

	this->animState = IDLE;
	this->attackCooldownMax = 60.f;		// Basic 60.f
	this->attackCooldown = this->attackCooldownMax;

	this->acceleration = 1;
}

Player::~Player() = default;



void Player::update()
{
	updateMovement();
	updateAnimation();
	updateAttack();
	this->setOrigin(this->getLocalBounds().width / 2, this->getLocalBounds().height / 2);

}

void Player::initVariables()
{
	this->potionState = NonActive;
	this->gunState = Gun_1;
}

void Player::updateAnimation()
{
	if (animState == IDLE)
	{
		if (this->animationTimer.getElapsedTime().asSeconds() >= 0.18f)
		{
			this->currentFrame.left += 64;
			if (this->currentFrame.left >= 160.f)
				this->currentFrame.left = 0;

			this->animationTimer.restart();
			this->setTextureRect(this->currentFrame);
		}
	}


}

void Player::updateMovement()
{
	elapsed = clock.restart();
	float time = elapsed.asSeconds();



	if (Keyboard::isKeyPressed(Keyboard::A) && this->getPosition().x >=500) {
		this->move(-abs(movementSpeed * time), 0);

	}

	if (Keyboard::isKeyPressed(Keyboard::D) && this->getPosition().x <= 2500) {
		this->move(abs(movementSpeed * time), 0);

	}

	if (Keyboard::isKeyPressed(Keyboard::W) && this->getPosition().y >= 500) {
		this->move(0, -abs(movementSpeed * time));


	}

	if (Keyboard::isKeyPressed(Keyboard::S) && this->getPosition().y <= 2500) {
		this->move(0, abs(movementSpeed * time));
		this->animState = IDLE;
	}
}

void Player::BlackHoleEffect(GraphicalObject &blackhole) {

	float speed = clockBH.getElapsedTime().asSeconds();

	float distance = 0;
	float x = 0;
	float y = 0;
	x = abs(blackhole.getPosition().x - this->getPosition().x);
	y = abs(blackhole.getPosition().y - this->getPosition().y);
	distance = sqrt(x * x + y * y);

	float dir_x = (blackhole.getPosition().x - this->getPosition().x) / abs((blackhole.getPosition().x - this->getPosition().x));
	float dir_y = (blackhole.getPosition().y - this->getPosition().y) / (abs(blackhole.getPosition().y - this->getPosition().y));

	const float vx_ = 100;
	const float vy_ = 100;

	if (distance < 600) {		
		this->move(vx_ *speed * dir_x * acceleration, vy_ *speed * dir_y * acceleration);
		acceleration += 0.001;
	}
	else {
		acceleration = 1;
	}

	clockBH.restart();

}


// ATTACK FUNCTION

void Player::updateAttack()
{
	if(this->attackCooldown < this->attackCooldownMax){
		this->attackCooldown += 0.5f;
	}
}

void Player::updateAngles(RenderWindow& window)
{
}

FloatRect Player::getRect()
{
	return this->getGlobalBounds();
}

void Player::setRotationPlayer(float angles)
{
	 this->setRotation(angles + 180);
}

const bool Player::canAttack()
{
	if (this->attackCooldown >= this->attackCooldownMax)
	{
		this->attackCooldown = 0.f;
		return true;
	}
	else return false;
}


void Player::movePlayer(float speedX, float speedY)
{
	 this->move(this-> movementSpeed*speedX , this->movementSpeed*speedY);
}

Vector2f Player::getCenter() const {
	FloatRect bounds = this->getGlobalBounds();
	return Vector2f(bounds.left + bounds.width / 2.0f, bounds.top + bounds.height / 2.0f);
}

int Player::getPlayerHp() const
{
	return this->playerHp;
}

void Player::setPlayerHp(int value) {
	this->playerHp += value;
}

float Player::getAttackSpeed() const {
	return this->attackSpeed;
}

float Player::setAttackSpeed(float value) {
	return this->attackSpeed *= value;
}

int Player::getPlayerMaxHp() const
{
	return this->playerMaxHp;
}

void Player::setPlayerMaxHp(int value) {
	this->playerMaxHp += value;
}

int Player::getPlayerPoints() const {
	return points;
}

int Player::setPlayerPoints(int value) {
	return points += value;
}



void Player::updateAttackCoolDown(float value) {
	this->attackCooldownMax /= value;
}

void Player::updateAttackCoolUp(float value) {
	this->attackCooldownMax = value;
}

