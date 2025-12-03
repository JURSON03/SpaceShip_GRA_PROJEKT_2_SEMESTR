
#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include <iostream>
#include <vector>
#include <math.h>
#include "GraphicalObject.h"
#include "Asteroid.h"

using namespace std;
using namespace sf;

enum PLAYER_ANIMATION_STATES {IDLE =0, TOP};



class Player : public GraphicalObject
{
private:

	


	// Dodanie tekstur
	bool moving;

	// Animacje
	Clock animationTimer;
	IntRect currentFrame;
	short animState;

	//Accessor
	

	//Attack
	float attackCooldown;
	float attackCooldownMax;
	float angles;
	float attackSpeed;

	// Ruch
	Clock clock;
	Time elapsed;

	// BlackHole effects

	Clock clockBH;
	float acceleration;


	// Zmienne hp, punkty, predkosc poruszania
	float movementSpeed;
	int playerHp;
	int playerMaxHp;
	int points;
	
	// Private functions

	

	void initSprite();
	void initVariables();
	

public:

	enum PotionState { NonActive, Active };
	enum GunState {Gun_1, Gun_2, Gun_3};
	PotionState potionState;

	GunState gunState;

	Player();
	~Player();

	const Vector2f& getPos() const;

	const bool canAttack();

	void update();

	void movePlayer(float speedX, float speedY);
	
	void updateAnimation();
	void updateMovement();

	void updateAttack();

	void updateAngles(RenderWindow &window);

	FloatRect getRect();

	void setRotationPlayer(float angles);

	void BlackHoleEffect(GraphicalObject &player);

	Vector2f getCenter() const;

	int getPlayerHp() const;
	void setPlayerHp(int value);

	int getPlayerMaxHp() const;
	void setPlayerMaxHp(int value);

	float getAttackSpeed() const;
	float setAttackSpeed(float value);

	int getPlayerPoints() const;
	int setPlayerPoints(int value);

	// float setPlayerAttackSpeed(int value);
	void updateAttackCoolDown(float value);
	void updateAttackCoolUp(float value);
	void updatePlayerMaxHp() {
		playerMaxHp += 1;
	}

};

