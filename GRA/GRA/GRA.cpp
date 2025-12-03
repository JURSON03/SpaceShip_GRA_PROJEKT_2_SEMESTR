/*
#include "Engine.h"
#include "Player.h"

#include <SFML/Graphics.hpp>
#include <time.h>


int main(void) {

   
Engine* game = new Engine();
game->run();

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

    return 0;
}

*/


#include <SFML/Graphics.hpp>
#include "Menu.h"
#include <time.h>

int main() {

    srand(time(NULL));

    Menu* menu = new Menu(800,600);
    menu->run();
    delete menu;

    return 0;
}

