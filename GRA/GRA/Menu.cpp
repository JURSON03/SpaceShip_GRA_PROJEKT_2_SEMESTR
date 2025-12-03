
#include "Menu.h"

using namespace std;
using namespace sf;

Menu::Menu(float width, float height) {
    if (!font.loadFromFile("./TEKSTURY/GUI/PixellettersFull.ttf")) {
        // handle error
    }

    // Main window
    mainWindow = new RenderWindow(VideoMode(800, 600), "MAIN MENU");

    menu[0].setFont(font);
    menu[0].setFillColor(sf::Color::Red);
    menu[0].setString("START GAME");
    menu[0].setPosition(sf::Vector2f(width / 4, height / (3 + 1) * 1));

    menu[1].setFont(font);
    menu[1].setFillColor(sf::Color::White);
    menu[1].setString("INSTRUKCJA");
    menu[1].setPosition(sf::Vector2f(width / 4 , height / (3 + 1) * 2));

    menu[2].setFont(font);
    menu[2].setFillColor(sf::Color::White);
    menu[2].setString("EXIT");
    menu[2].setPosition(sf::Vector2f(width / 4, height / (3 + 1) * 3));

    selectedItemIndex = 0;

    if (!b.loadFromFile("./MUSIC/Click.ogg")) {
        cout << "ERROR" << endl;
    }
    s.setBuffer(b);
}

Menu::~Menu() {
    delete mainWindow;
   // delete instruction;
}

void Menu::draw() {
    for (int i = 0; i < 3; i++) {
        mainWindow->draw(menu[i]);
    }
}

void Menu::moveUp() {
    if (selectedItemIndex - 1 >= 0) {
        menu[selectedItemIndex].setFillColor(sf::Color::White);
        selectedItemIndex--;
        menu[selectedItemIndex].setFillColor(sf::Color::Red);      
    }
}

void Menu::moveDown() {
    if (selectedItemIndex + 1 < 3) {
        menu[selectedItemIndex].setFillColor(sf::Color::White);
        selectedItemIndex++;
        menu[selectedItemIndex].setFillColor(sf::Color::Red);
    }
}

void Menu::update() {

    
}


void Menu::render() {
    this->mainWindow->clear();

    this->draw();

    this->mainWindow->display();
    
}

void Menu::clickPlay() {
    s.play();
}

void Menu::updatePollEvent() {
          
        while (mainWindow->pollEvent(event)) {
            if (event.type == sf::Event::KeyReleased) {
                switch (event.key.code) {
                case Event::Closed:
                    mainWindow->close();
                    break;
                case sf::Keyboard::Up:
                    moveUp();
                    clickPlay();
                    break;
                case sf::Keyboard::Down:
                    moveDown();
                    clickPlay();
                    break;
                case sf::Keyboard::Escape:
                    this->mainWindow->close();
                    break;
                case sf::Keyboard::Return:
                    selectOption();
                    break;
                default:
                    break;
                }
                switch (event.type) {
                case Event::Closed:
                    mainWindow->close();
                default:
                    break;
                }
            }
        }
    
}


void Menu::run() {
    while (mainWindow->isOpen()){
        updatePollEvent();
        update();
        render();
    }
}

void Menu::selectOption() {
    
    if (selectedItemIndex == 0) {
        // Start Game
        delete mainWindow;
        game = new Engine();
        game->run();
        mainWindow->close();
        while (true) {
            if (game->playAgain()) {
                delete game;
                game = new Engine();
                game->run();
            }
            else if (game->exitGame()) {   
                break;              
            }
        }
    }
    else if (selectedItemIndex == 1) {
        // How To Play  
        instruction = new Instruction();
        
        instruction->run();
        mainWindow->close();
        delete mainWindow;
        mainWindow = new RenderWindow(VideoMode(800.f,600.f), "MAIN MENU");
        this->run();

    }
    else if (selectedItemIndex == 2) {
        // Exit
        mainWindow->close();
    }

    

}