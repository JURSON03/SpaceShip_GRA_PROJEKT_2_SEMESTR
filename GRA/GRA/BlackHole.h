#pragma once

#include <SFML/Graphics.hpp>
#include "GraphicalObject.h"

using namespace std;
using namespace sf;

class BlackHole : public GraphicalObject
{
private:
	float vx_;
	float vy_;
	Clock clock;
	Time time;

public:
	BlackHole();
	~BlackHole();

	void update();
	void goToPlayer(GraphicalObject& player);


};

