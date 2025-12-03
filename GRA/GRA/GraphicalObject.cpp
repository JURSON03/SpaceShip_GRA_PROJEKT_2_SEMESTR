#include "GraphicalObject.h"
#include <algorithm>
using namespace std;
using namespace sf;

GraphicalObject::GraphicalObject(string texture_string, Vector2f pos)
{
	if (!texture.loadFromFile(texture_string)) {
		cout << "NIE UDALO SIE ZALADOWAC OBIEKTU" << endl;
	}
	this->setTexture(this->texture);
	this->setPosition(pos);
	// texture.setSmooth(true);
	
}



GraphicalObject::~GraphicalObject() = default;

void GraphicalObject::render(sf::RenderTarget& target)
{
	target.draw(*this);
}

bool GraphicalObject::collision(GraphicalObject* ob)
{
	if (Collision::pixelPerfectTest(*this, *ob)) {
		return true;
	}
	else {
		return false;
	}
}


/*
bool GraphicalObject::collision(GraphicalObject* ob)
{
	if (this->getGlobalBounds().intersects(ob->getGlobalBounds())) {
		return true;
	}
	else {
		return false;
	}
}
*/

