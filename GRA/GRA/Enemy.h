#pragma once

#include <SFML/Graphics.hpp>
#include "GraphicalObject.h"
#include "Collision.h"
#include "Player.h"
#include <cmath>
#include <math.h>

using namespace std;
using namespace sf;

class Enemy : public GraphicalObject
{
private:
	int enemyHp;
	int getPoints;
	int enemyMaxHp;

	// Attack
	float movementSpeed;
	float attackSpeed;

	//Predkosc
	Time elapsed;
	Clock clock;

	// Animacje
	Clock animationTimer;
	IntRect currentFrame;

	// Pozycja gracza
	float getPlayerPos_x;
	float getPlayerPos_y;

	// Pozycja enemy
	float getEnemyPos_x;
	float getEnemyPos_y;

public:

	enum State {Alive = 0, Dead};
	State state;
	Enemy(string name);
	~Enemy();

	void update();
	void updateMove(Player& player);
	void updateAnimation();
	FloatRect getEnemyPos();
	int getEnemyHp() const;
	int setEnemyHp(int value);
	int getEnemyMaxHp() const;

	float getDistance(GraphicalObject& player);
};

