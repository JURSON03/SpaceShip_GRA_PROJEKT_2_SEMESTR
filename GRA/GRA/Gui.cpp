#include "Gui.h"

using namespace std;
using namespace sf;

Gui::Gui() {
    this->initGui();
    if (!this->texture.loadFromFile("./TEKSTURY/HEART/hearts.png")) {
        cout << "ERROR::GUI::HEART NIE UDALO SIE WCZYTAC ZDJECIA SERCA" << endl;
    }
    this->sprite.setTexture(this->texture);
    this->sprite.setPosition(1000.f, 1025.f);
    this->sprite.setTextureRect(IntRect(0, 0, 16, 16));
    this->sprite.setScale(1.5f, 1.5f);
    this->potionCollected = false;
}

Gui::~Gui() {
    

}


void Gui::initGui() {

 
    if (!this->font.loadFromFile("./TEKSTURY/GUI/PixellettersFull.ttf")) {
        cout << "ENGINE::ERROR_NIE_UDALO_SIE_ZALADOWAC_CZCIONKI" << endl;


    }
    // PUNKTY

    this->pointText.setFont(this->font);
    this->pointText.setCharacterSize(25);
    this->pointText.setFillColor(Color::White);
    this->pointText.setString("PUNKTY: " + to_string(0));
    this->pointText.setPosition(0.f, 0.f);

    //Zdrowie
    this->healText.setFont(this->font);
    this->healText.setCharacterSize(25);
    this->healText.setFillColor(Color::White);
    this->healText.setString("ZDROWIE: " + to_string(3));
    this->healText.setPosition(0.f, 0.f);

    //Game Over

    // Attack Time text
    this->attackTimeText.setFont(this->font);
    this->attackTimeText.setCharacterSize(25);
    this->attackTimeText.setFillColor(Color::White);
    this->attackTimeText.setString("ATTACK: " + to_string(0));
    this->attackTimeText.setPosition(0.f, 0.f);
    
}

void Gui::render(RenderWindow &window) {

    window.draw(this->pointText);
    window.draw(this->healText);
    window.draw(this->sprite);
    window.draw(this->gameOverText);
    
    if (attackTime < 7 && potionCollected == true) {
        window.draw(this->attackTimeText);
    }
   

}

void Gui::update(Player &player, FloatRect gameView) {

    // PUNKTY
    this->pointText.setPosition(gameView.left, gameView.top);
    this->pointText.setString("PUNKTY: " + to_string(player.getPlayerPoints()));

    // ZDROWIE
    this->sprite.setPosition(gameView.left+115, gameView.top + 22);
    this->healText.setPosition(gameView.left, gameView.top+15);
    this->healText.setString("ZDROWIE: " + to_string(player.getPlayerHp()));

    // ATTACK SPEED
    
    this->attackTimeText.setPosition(gameView.left, gameView.top + 30);
    this->attackTimeText.setString("ATTACK: " + to_string(abs(7 - attackTime)));
    if (attackTime >= 7) {
        this->potionCollected == false;
    }

    // BOSS



}


void Gui::gameOverUpdate(Player& player)
{
    if (player.getPlayerHp() <= 0) {
        this->gameOverText.setFont(this->font);
        this->gameOverText.setCharacterSize(90);
        this->gameOverText.setFillColor(Color::Red);
        this->gameOverText.setString("    GAME OVER \n ENTER - RESTART \n ESCAPE - LEAVE" );
        this->gameOverText.setPosition(player.getCenter().x-300, player.getCenter().y-500);
     
    }
}

void Gui::attackTimeUpdate(float time) {
    this-> attackTime = time;
}

bool Gui::updatePotionCollected() {
    return this->potionCollected = true;
}
