#pragma once

#include <SFML/Graphics.hpp>
#include "GraphicalObject.h"

using namespace std;
using namespace sf;

class Asteroid : public GraphicalObject
{
private:


	int hp;
	int damage;
	int points;
	int speed;

	// Pozycja
	Vector2f position;

	// Wielkosc asteroidy

	int asteroidSize;

	

	//Animacje
	IntRect currentFrame;
	Clock animationTimer;
	

public:

	enum State{Active, Exploding, Destroyed};
	State state;

	Asteroid(float pos_x, float pos_y);
	virtual ~Asteroid();
	void update();
	bool collision(GraphicalObject *ob);
	void updateAnimation();
	bool isDestroyed() const;
	int getAsteroidSize();
	void decreaseHeal();

	int getHp() const;
	int setHp();
};


