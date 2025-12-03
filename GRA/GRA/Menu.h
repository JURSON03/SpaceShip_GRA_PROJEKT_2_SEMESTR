#pragma once

#include <SFML/Graphics.hpp>
#include "Engine.h"
#include "Instruction.h"
#include <SFML/Audio.hpp>

using namespace std;
using namespace sf;

class Menu {
public:
    Menu(float width, float height);
    ~Menu();

    void draw();
    void moveUp();
    void moveDown();
    int getPressedItem() { return selectedItemIndex; }

    void update();
    void render();
    void updatePollEvent();
    void run();

    void selectOption();
    void clickPlay();

private:
    int selectedItemIndex;
    sf::Font font;
    sf::Text menu[3]; 

    // Engine game
    Engine* game;

    // Events
    Event event;

    // Window
    RenderWindow *mainWindow;

    // Instruction
    Instruction* instruction;

    Sound s;
    SoundBuffer b;



};
