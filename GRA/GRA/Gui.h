#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include "Player.h"

using namespace std;
using namespace sf;

class Gui
{ 
private:
	Font font;
	Text pointText;
	Text healText;
	Text gameOverText;
	Text attackTimeText;
	float attackTime;
	bool potionCollected;

	Texture texture;
	Sprite sprite;


	void initGui();

public:

	Gui();
	~Gui();

	void update(Player &player, FloatRect gameView);
	void render(RenderWindow& window);
	void gameOverUpdate(Player &player);
	void attackTimeUpdate(float time);
	bool updatePotionCollected();
};

