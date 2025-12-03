#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include "Collision.h"

using namespace std;
using namespace sf;

class GraphicalObject : public Sprite
{
private:
	Texture texture;

public:


	GraphicalObject(string text, Vector2f pos);

	virtual ~GraphicalObject();
	virtual void update() = 0;
	void render(sf::RenderTarget& target);


	bool collision(GraphicalObject* ob);

};

