#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>

#include "GraphicalObject.h"

using namespace std;
using namespace sf;


class Background : public GraphicalObject
{
private:

	Music music;

public:
	Background();
	~Background();


	void update();

};

