#pragma once
#include <SFML/Graphics.hpp>
#include <string>

using namespace std;
using namespace sf;

class Instruction {
public:

    void run();


    Instruction();

    ~Instruction();

private:
    sf::RenderWindow window;
    sf::Font font;
    sf::Text instructionsText;

    void initWindow();

    void initText(); 

    void render();


};




