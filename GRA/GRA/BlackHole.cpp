#include "BlackHole.h"

using namespace std;
using namespace sf;

BlackHole::~BlackHole() = default;

BlackHole::BlackHole() : GraphicalObject("./TEKSTURY/BLACKHOLE/Black_hole.png",Vector2f(500,500)) {

	this->setScale(Vector2f(4.f,4.f));

	this->vx_ = 50;
	this->vy_ = 50;
}


void BlackHole::update() {

}

void BlackHole::goToPlayer(GraphicalObject& player) {
    time = clock.restart();
    float getTime = time.asSeconds();
  
    float pos_x = ((player.getGlobalBounds().left + player.getGlobalBounds().width) / 2) - ((this->getGlobalBounds().left + this->getGlobalBounds().width) / 2);
    float pos_y = ((player.getGlobalBounds().top + player.getGlobalBounds().height) / 2) - ((this->getGlobalBounds().top + this->getGlobalBounds().height) / 2);

   
    float distance = sqrt(pos_x * pos_x + pos_y * pos_y);

    // Normalizacja wektora kierunku
    if (distance != 0) {
        pos_x /= distance;
        pos_y /= distance;
    }

    // Ruch w kierunku gracza ze sta³¹ prêdkoœci¹
    float moveX = pos_x * vx_ * getTime;
    float moveY = pos_y * vy_ * getTime;

    if (distance > 100) {
        this->move(moveX, moveY);
    }
}
