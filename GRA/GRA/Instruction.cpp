#include "Instruction.h"

using namespace std;
using namespace sf;




Instruction::Instruction() {
    initWindow();
    initText();
}

Instruction::~Instruction() = default;


void Instruction::initWindow() {
    window.create(sf::VideoMode(1280, 720), "Instrukcje do gry", sf::Style::Titlebar | sf::Style::Close);
}

void Instruction::initText() {
    if (!font.loadFromFile("./TEKSTURY/GUI/PixellettersFull.ttf")) {
        
    }

    string instruction = "Gra polega na jak najdluzszym przetrwaniu oraz zdobyciu jak najwiekszej ilosci punktow.";
    instruction +=  "\n\n STEROWANIE : \n W - poruszanie sie do gory \n S - poruszanie sie w dol \n A - poruszanie sie w lewo \n D - poruszanie sie w prawo \n Lewy przycisk myszy - oddawanie strzalow\n"; 
    instruction += "\n Ilosc punktow jest przyznawana za zniszczenie asteroidy lub przeciwny statek.\n";
    instruction += "Ilosc punktow dostaje sie w zaleznosci od wielkosci obiektu.Przeciwne statki zabieraja\n od 1 do 2 punktow zdrowia.";
    instruction += "\n Gracz zaczyna gre z 10 punktami zdrowia i jest to jego maksymalna ilosc. \n Gdy gracz straci wszystkie punkty zdrowia to przegrywa. \n";
    instruction += "Na mapie gracz moze podniesc serduszka. \n Kazde serduszko przywraca graczowi 1 serce. \n Gdy gracz posiada 10 serc nie jest wstanie podniesc kolejnego.";
    instruction += "\n Podniesienie przez gracza eliksiru powoduje kilkusekundowe zwiekszenie predkosci ataku.";
    instruction += "\n Co 90 sekund gry zwieksza sie poziom trudnosci. ";
    instruction += "\n Czarna dziura przyciaga gracza oraz inne obiekty z coraz wiekszym przyspieszeniem. ";
    instruction += "\n Kolizja przez gracza z czarna dziura powoduje jego natychmiastowa smierc.  ";
    instruction += "\n Na mapie po 60 sekundach pojawia sie boss, ktory jest silniejszy od przecietnych statkow";
    instruction += "\n Po zabiciu bossa mozna teraz miec maksymalnie o jeden punkt wiecej zycia";
    instruction += "\n Boss odradza sie co 60 sekund po zabiciu go i jest coraz silniejszy ze zdrowia";


    instructionsText.setFont(font);
    instructionsText.setString(instruction);
 
    instructionsText.setCharacterSize(24);
    instructionsText.setFillColor(sf::Color::White);
    instructionsText.setPosition(20, 20);
}

void Instruction::run() {
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }
        render();
    }
}

void Instruction::render() {
    window.clear(sf::Color::Black);
    window.draw(instructionsText);
    window.display();
}
