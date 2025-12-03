
#include "Engine.h"

#define PI 3.14159

using namespace std;
using namespace sf;

// KONSTRUKTOR // DESTRUKTOR //

Engine::Engine() 
{
    // Init
    window = new RenderWindow(VideoMode(1000, 700), "GAME PROJECT");
    this->window->setFramerateLimit(240);
    this->defaultView = window->getDefaultView();
    this->window->setVerticalSyncEnabled(false);

    initGUI();
    initPlayer();
    initBackground();


    blackHole = new BlackHole();
   
   // initSpawnTimers
    this->asteroidSpawnTimer = 0.f;
    this->asteroidSpawnTimerMax = 8.f;
    this->heartSpawnTimer = 0.f;
    this->heartSpawnMaxTimer = 200.f;
    this->enemySpawnTimer = 0.f;
    this->enemySpawnTimerMax = 60.f;
    this->enemyBulletSpawnTimer = 0.f;
    this->enemyBulletSpawnTimerMax = 20.f;
    this->potionTimer = 0.f;
    this->potionTimerMax = 100.f;

    // BOSS
    this->bossAttackSpeed = 0.f;
    this->bossAttackSpeedMax = 20.f;
    this->bossStronger = false;
    this->bossCounter = 0;

    this->potionClock.restart();
    this->potionTime = potionClock.getElapsedTime().asSeconds();

    this->potionCounter = 0;
    this->heartCounter = 0;


    // Sounds shots
    this->bufferShot.loadFromFile("./MUSIC/shoot.ogg");
    this->soundShot.setBuffer(bufferShot);
    this->soundShot.setVolume(30);

    // Sounds game over
    if(!this->bufferGameOver.loadFromFile("./MUSIC/gameOver.ogg"));
    this->soundGameOver.setBuffer(bufferGameOver);
    this->soundGameOver.setVolume(30);

    this->accelerationBH = 1;
    this->maxEnemies = 6;
    

   // this->boss = new Boss(1500, 1500, windowSize());
    boss = nullptr;
    
}

Engine::~Engine() {
    delete this->window;
    delete this->player;
    delete this->background;
    delete this->GUI;
    delete this->boss;

   // USUWANIE OBIEKTÓW HEART, POTION
    for (const auto& ob : objects) {
        delete ob;
    }

    // Usuwanie blackHole
    delete blackHole;
}


// INICJACJA FUNKCJE //



void Engine::initWindow() {
   
}


void Engine::initPlayer()
{
    player = new Player();
   
}

void Engine::initBackground()
{
    background = new Background();
}


void Engine::initCamera()
{
    view = window->getDefaultView();

}

void Engine::initGUI()
{
    GUI = new Gui();
}


// FUNKCJE  UPDATE EVENTS//

void Engine::updateEvents() {
    while (this->window->pollEvent(event))
    {
        if (event.Event::type == Event::Closed) {
            this->window->close();
            this->exitGame();
        }
        if (Keyboard::isKeyPressed(Keyboard::Escape)) {
            this->window->close();
            this->exitGame();
        }

    }
}

FloatRect Engine::windowSize() {
    FloatRect viewBounds;

    viewBounds.left = window->getView().getCenter().x - window->getView().getSize().x / 2;
    viewBounds.top = window->getView().getCenter().y - window->getView().getSize().y / 2;
    viewBounds.width = window->getView().getSize().x;
    viewBounds.height = window->getView().getSize().y;

    return viewBounds;
}

// FUNCKJE UPDATE //

void Engine::update()
{
  
 
    this->updateCamera();
    player->update();
    this->updateAnglesPlayer();
    this->updateInputPlayer();
    this->player->update();
    this->updateAsteroidCollision();

    this->updateDifficultyLeavel();

    //HEART
    this->updatePlayerHeart();
    // Potion
    this->updatePotion();
    //STRZALY
    this->updateBullet();
    // ASTEROIDY
    this->updateAsteroid();
    // ENEMY
    this->updateEnemyBullet();
    this->updateEnemy();

    

    this->updateBlackHole();


    this->background->update();

    if (player->getPlayerHp() <= 0) {
        soundGameOver.play();
    }

  
    this->updateBoss();
    

    this->GUI->update(*player, windowSize());
    
}



// FUNKCJE UPDATE I RENDER //

void Engine::render() {

    this->window->clear();  

    

    //Render map 
    this->background->render(*this->window);

    //Render Player
    this->player->render(*this->window);


    // Render BlackHole
    this->blackHole->render(*window);


    // OBJECTS
    for (const auto& ob : objects) {
        ob->render(*this->window);
    }

    if (boss != nullptr) {
        this->boss->render(*window);
    }

    this->GUI->render(*this->window);

    this->GUI->gameOverUpdate(*player);

    this->window->display();
}



void Engine::updateDifficultyLeavel() {
    if (diffClock.getElapsedTime().asSeconds() >= 90) {

        this->asteroidSpawnTimerMax -= 0.1f;
        this->enemySpawnTimerMax -= 1.f;
        this->enemyBulletSpawnTimerMax -=0.5f;
        this->maxEnemies += 0.5;
        diffClock.restart();
    }
}


void Engine::updateInputPlayer()
{
    if (Mouse::isButtonPressed(Mouse::Left) && this->player->canAttack())
    {
        //   float dir_x = cos(angles);  
        //   float dir_y = sin(angles);  
           // Strzal leci pod katem myszki

        string gun_1 = "./TEKSTURY/BULLET/bullet0.png";
        string gun_2 = "./TEKSTURY/BULLET/bullet1.png";
        string gun_3 = "./TEKSTURY/BULLET/bullet2.png";

        if (player->gunState == Player::Gun_1) {
            objects.emplace_back(new Bullet(
                this->player->getPos().x,
                this->player->getPos().y,
                cos(angles), sin(angles), player->getAttackSpeed(), "./TEKSTURY/BULLET/bullet0.png"));
        }
        else if (player->gunState == Player::Gun_2) {
            objects.emplace_back(new Bullet(
                this->player->getPos().x,
                this->player->getPos().y,
                cos(angles), sin(angles), player->getAttackSpeed(), "./TEKSTURY/BULLET/bullet1.png"));
        }
        else if (player->gunState == Player::Gun_3) {
            objects.emplace_back(new Bullet(
                this->player->getPos().x,
                this->player->getPos().y,
                cos(angles), sin(angles), player->getAttackSpeed(), "./TEKSTURY/BULLET/bullet2.png"));
        }       
    }

    if (Keyboard::isKeyPressed(Keyboard::Num1)) {
        this->player->gunState = Player::Gun_1;
    }
    else if(Keyboard::isKeyPressed(Keyboard::Num2)) {
        this->player->gunState = Player::Gun_2;
    }
    else if (Keyboard::isKeyPressed(Keyboard::Num3)) {
        this->player->gunState = Player::Gun_3;
    }

}




void Engine::updateCamera()
{
    // Centrowanie na gracza
    view.setCenter(player->getPos());
    window->setView(view);
}

void Engine::updateAnglesPlayer()
{
    Vector2i mousePixelPos = Mouse::getPosition(*window); // Pozycja myszy w pikselach na ekranie
    Vector2f mouseWorldPos = window->mapPixelToCoords(mousePixelPos); // Przeliczenie na wspó³rzêdne œwiata

    Vector2f playerPos = player->getPos(); // Pozycja gracza w œwiecie

    // Obliczanie k¹ta miêdzy graczem a mysz¹
    angles = atan2(mouseWorldPos.y - playerPos.y, mouseWorldPos.x - playerPos.x);

    // Ustawienie obrotu gracza
    float angleDegrees = angles * 180 / PI;
    player->setRotationPlayer(angleDegrees - 90); 
}


void Engine::updateBullet() {

    
    // Aktualny widok okna
    viewBounds.left = window->getView().getCenter().x - window->getView().getSize().x / 2;
    viewBounds.top = window->getView().getCenter().y - window->getView().getSize().y / 2;
    viewBounds.width = window->getView().getSize().x;
    viewBounds.height = window->getView().getSize().y;

   

    for (int i = 0; i < objects.size(); i++) {
        if (Bullet* bullets = dynamic_cast<Bullet*>(objects[i])) {
            bullets->update();
            if (bullets->getBounds().top + bullets->getBounds().height < viewBounds.top
                || bullets->getBounds().left + bullets->getBounds().width < viewBounds.left
                || bullets->getBounds().left > viewBounds.left + viewBounds.width
                || bullets->getBounds().top > viewBounds.top + viewBounds.height)
            {
                // Delete bullets
                delete objects.at(i);
                objects.erase(objects.begin() + i);
            }
        }
    }
}




void Engine::updateAsteroid() {
    this->asteroidSpawnTimer += 0.1f;
    if (this->asteroidSpawnTimer >= this->asteroidSpawnTimerMax) {
        this->objects.push_back(new Asteroid(rand() % 3000 + 300, -100));
        this->asteroidSpawnTimer = 0.f;
    }

    for (int k = 0; k < objects.size();k++) {
        if (Asteroid* asteroid = dynamic_cast<Asteroid*>(objects[k])) {
            asteroid->update();
            asteroid->updateAnimation();

            bool asteroidDestroyed = false;

            // Usuwanie asteroidy oraz strzaly po trafieniu
            for (int i = 0; i < objects.size(); i++) {
                if (Bullet* bullet = dynamic_cast<Bullet*>(objects[i])) {
                    if (bullet->collision(asteroid) && (asteroid)->getHp() <= 1) {
                        (asteroid)->state = Asteroid::Exploding;
                        (asteroid)->updateAnimation();
                        player->setPlayerPoints((asteroid)->getAsteroidSize());
                        delete objects.at(i);
                        objects.erase(objects.begin() + i);
                        asteroidDestroyed = true;
                        break;
                    }
                    else if ((asteroid)->isDestroyed()) {
                        delete objects.at(k);
                        objects.erase(objects.begin() + k);
                        asteroidDestroyed = true;
                        break;
                    }
                    else if (bullet->collision(asteroid) && (asteroid)->getHp() > 0) {
                        (asteroid)->decreaseHeal();
                        delete objects.at(i);
                        objects.erase(objects.begin() + i);
                    }

                }
            }

            if (!asteroidDestroyed) {
                if ((asteroid)->getPosition().y >= 3000.f) {
                    delete objects.at(k);
                    objects.erase(objects.begin() + k);
                }
            }
        }
    }
}


void Engine::updateAsteroidCollision()
{
        for (int i = 0; i < objects.size(); i++){
            if (Asteroid* asteroid = dynamic_cast<Asteroid*>(objects[i])) {
                if (player->collision(asteroid) && asteroid->state == Asteroid::Active) {
                    cout << "UDERZYLA CIE ASTEROIDA!!! TRACISZ JEDEN PUNKT ZDROWIA" << endl;
                    asteroid->state = Asteroid::Exploding;
                    this->player->setPlayerHp(-1);

                }
                else if (asteroid->isDestroyed()) {
                    delete this->objects.at(i);
                    this->objects.erase(this->objects.begin() + i);
                    if (i > 0) {
                        i--;
                    }
                    continue;
                }
            }
        }
   
}

void Engine::updatePlayerHeart() {

    if (this->heartCounter < 5) {
        this->heartSpawnTimer += 0.1f;
        if (this->heartSpawnTimer >= this->heartSpawnMaxTimer) {
            this->objects.push_back(new Heart());
            this->heartSpawnTimer = 0.f;
            this->heartCounter++;
        }
    }
    //  cout << objects.size() << endl;

    for (int i = 0; i < objects.size(); i++) {
        if (Heart* heart_ = dynamic_cast<Heart*>(objects[i])) {
            if (player->collision(heart_) && player->getPlayerHp() < player->getPlayerMaxHp() && heart_->State == Heart::Active) {
                player->setPlayerHp(1);
                heart_->State = Heart::Collected;
                cout << "Dodano jeden punkt zdrowia! " << endl;
            }
        }
    }

    for (int i = 0; i < objects.size(); i++) {
        if (Heart* heart_ = dynamic_cast<Heart*>(objects[i])) {
            if (heart_->State == Heart::Collected) {
                delete objects.at(i);
                objects.erase(objects.begin() + i);
                this->heartCounter--;
                if (i > 0) {
                    i--;
                }
            }
        }
    }

    for (int i = 0; i < objects.size(); i++) {
        if (Heart* heart_ = dynamic_cast<Heart*>(objects[i])) {
            heart_->updateAnimation();
        }
    }
    


}



void Engine::updateEnemy() {

    int enemyCount = 0;

    for (int i = 0; i < objects.size();i++) {
        if (Enemy* ob = dynamic_cast<Enemy*>(objects[i])) {
            enemyCount++;
        }
    }

    // Dodawanie nowego przeciwnika
    if (enemyCount < 5) {

        this->enemySpawnTimer += 0.09f;   // 0.1f
        if (this->enemySpawnTimer >= this->enemySpawnTimerMax) {
            int randomValue = rand() % 2;
            if (randomValue == 0) {
                this->objects.push_back(new Enemy("./TEKSTURY/ENEMY/Spaceship64-Sheet.png"));
            }
            else {
                this->objects.push_back(new Enemy("./TEKSTURY/ENEMY/Spaceship_Green64-Sheet.png"));
            }
            this->enemySpawnTimer = 0.f;
        }
    }

    // Dodawanie strzalow do przeciwnikow
    this->enemyBulletSpawnTimer += 0.1f;
    if (this->enemyBulletSpawnTimer >= this->enemyBulletSpawnTimerMax) {
        if (objects.size() > 0) {
            for (int i = 0; i < objects.size(); i++) {
                if (Enemy* ob = dynamic_cast<Enemy*>(objects[i])) {
                    this->objects.push_back(
                        new EnemyBullet("./TEKSTURY/BULLET/bullet1.png",ob->getEnemyPos().left, ob->getEnemyPos().top, player->getCenter().x, player->getCenter().y, 3.f));
                }
            }
            this->enemyBulletSpawnTimer = 0.f;
        }
    }
    
    for (int i = 0; i < objects.size();i++) {
        if (EnemyBullet* enemyBullets = dynamic_cast<EnemyBullet*>(objects[i])) {
            enemyBullets->updateMovement();
        }
    }
    
        
    for (int i = 0; i < objects.size(); i++) {
        if (Enemy* ob = dynamic_cast<Enemy*>(objects[i])) {
            ob->updateMove(*player);
            ob->update();
        }
    }
    
    for (int i = 0; i < objects.size(); i++) {
        if (Enemy* ob = dynamic_cast<Enemy*>(objects[i])) {
        // ZMIANA STANU PRZECIWNIKA NA DEAD
            for (int k = 0; k < objects.size(); k++) {
                if (Bullet* bullets = dynamic_cast<Bullet*>(objects[k])) {
                    if ((bullets->collision(ob)) && (ob->state == Enemy::Alive)) {
                        if (ob->getEnemyHp() == 0) {
                            ob->state = Enemy::Dead;
                        }
                        delete objects.at(k);
                        objects.erase(objects.begin() + k);
                        ob->setEnemyHp(1);
                        break;
                    }
                }
            }
        }
    }
    
        // USUWANIE PRZECIWNIKOW ZE STANEM DEAD
        for (int k = 0; k < objects.size(); k++) {
            if (Enemy* ob = dynamic_cast<Enemy*>(objects[k])) {
                if (ob->state == Enemy::Dead) {
                    player->setPlayerPoints(ob->getEnemyMaxHp());
                    delete objects.at(k);
                    this->objects.erase(objects.begin() + k);
                    if (k != 0) {
                        k--;
                    }
                }
            }
        }

        // EnemyBullets zadaja obrazenia Player'owi
        for (int i = 0; i < objects.size(); i++) {
            if (EnemyBullet* enemyBullet = dynamic_cast<EnemyBullet*>(objects[i])) {
                if (player->collision(enemyBullet)) {
                    player->setPlayerHp(-enemyBullet->bulletDamage());
                    delete this->objects.at(i);
                    this->objects.erase(objects.begin() + i);
                    if (i != 0) {
                        i--;
                    }
                }
            }
        }

        // USUWANIE TRAFIENIA STRZALU PLAYERA ZE STRZALEM ENEMYBULLET

        for (int i = 0; i < objects.size(); i++) {
            for(int k=0; k < objects.size(); k++){
                if (EnemyBullet* enemyBullet = dynamic_cast<EnemyBullet*>(objects[i])) {
                    if (Bullet* bullet = dynamic_cast<Bullet*>(objects[k])) {
                        if (enemyBullet->collision(bullet) && enemyBullet->state == EnemyBullet::Active) {
                            delete this->objects.at(k);
                            objects.erase(objects.begin() + k);
                            enemyBullet->state = EnemyBullet::Destroyed;
                            if (i != 0) {
                                i--;
                            }
                            if (k != 0) {
                                k--;
                            }
                        }
                    }
                }
            }
        }
        
        // USUWANIE ENEMYBULLET ZE STANEM DESTROYED
        for (int i = 0; i < objects.size(); i++) {
            if (EnemyBullet* enemyBullet = dynamic_cast<EnemyBullet*>(objects[i])) {
                if (enemyBullet->state == EnemyBullet::Destroyed) {
                    delete this->objects.at(i);
                    this->objects.erase(objects.begin() + i);
                    if (i >= 1) {
                        i--;
                    }
                }
            }
        }

}

void Engine::updateEnemyBullet() {
     
  //   cout << enemyBullet.size() << endl;

    viewBounds.left = window->getView().getCenter().x - window->getView().getSize().x / 2;
    viewBounds.top = window->getView().getCenter().y - window->getView().getSize().y / 2;
    viewBounds.width = window->getView().getSize().x;
    viewBounds.height = window->getView().getSize().y;


    for (int i = 0; i < objects.size(); i++) {
        if (EnemyBullet* enemyBull = dynamic_cast<EnemyBullet*>(objects[i])) {
            if (enemyBull->getBounds().top + enemyBull->getBounds().height < viewBounds.top
                || enemyBull->getBounds().left + enemyBull->getBounds().width < viewBounds.left
                || enemyBull->getBounds().left > viewBounds.left + viewBounds.width
                || enemyBull->getBounds().top > viewBounds.top + viewBounds.height)
            {
                // Delete bullets
                delete objects.at(i);       // Potrzebne do zwolnienia pamieci  
                objects.erase(objects.begin() + i);
               
            }
        }
    }
   
  
    
}

void Engine::updatePotion() {
    // Sprawdzanie czy jest potrzeba spawnowania nowego potion
    if (potionCounter < 4) {
        this->potionTimer += 0.1f;
        if (this->potionTimer >= this->potionTimerMax) {
            this->objects.push_back(new Potion());
            this->potionTimer = 0.f;
            potionCounter++;
        }
    }

    // Kolizja z potion
    for (int i = 0; i < objects.size(); i++) {
        if (Potion* potion_ = dynamic_cast<Potion*>(objects[i])) {
            if (this->player->collision(potion_) && potion_->state == Potion::Active && this->player->potionState == Player::NonActive) {
                this->player->updateAttackCoolDown(2.2f);
                potion_->state = Potion::Collected;
                potionClock.restart();
                this->potionTime = potionClock.getElapsedTime().asSeconds();
                this->GUI->attackTimeUpdate(potionTime);
                this->player->potionState = Player::Active;
                this->GUI->updatePotionCollected();
            }
        }
    }
    // Usuwanie zebranych potion
    for (int i = 0; i < objects.size(); i++) {
        if (Potion* potion_ = dynamic_cast<Potion*>(objects[i])) {
            if (potion_->state == Potion::Collected) {
                delete this->objects.at(i);
                this->objects.erase(objects.begin() + i);
                potionCounter--;
                if (i > 0) {
                    i--;
                }
            }
        }
    }

    // SPRAWDZANIE CZASU POTION
    if (this->potionTime < 7.1f) {
        this->potionTime = this->potionClock.getElapsedTime().asSeconds();
        this->GUI->attackTimeUpdate(potionTime);
    }

    // Przywracanie normalnej szybkoœci ataku po 7 sekundach
    if (potionTime > 7.f && player->potionState == Player::Active) {
        this->player->updateAttackCoolUp(60.f);
        this->player->potionState = Player::NonActive;
    }

    for (int i = 0; i < objects.size(); i++) {
        if (Potion* potion_ = dynamic_cast<Potion*>(objects[i])) {
            potion_->updateAnimation();
        }
    }
   //cout << objects.size() << endl;
}


void Engine::updateBlackHole() {

    // Followuj gracza
    this->blackHole->goToPlayer(*player);

    // Gracz odrazu ginie po kolizji z czarna dziura
    if (this->player->collision(blackHole)) {
        this->player->setPlayerHp(-10);
        cout << "WCIAGNELA CIE CZARNA DZIURA. PRZEGRYWASZ z " << player->getPlayerPoints() << " PUNKTAMI!" << endl;
    }

    // Efekt przyciagania czarnej dziury dla gracza
    player->BlackHoleEffect(*blackHole);


    // Dla innych obiektow przyciaganie
    for (int i = 0; i < objects.size(); i++) {

        float distance = 0;
        float x = 0;
        float y = 0;
        x = abs(blackHole->getPosition().x - objects[i]->getPosition().x);
        y = abs(blackHole->getPosition().y - objects[i]->getPosition().y);
        distance = sqrt(x * x + y * y);

        if (distance < 300) {
            if (blackHole->collision(objects[i])) {
                delete objects.at(i);
                objects.erase(objects.begin() + i);
                continue;
            }
          

            float dir_x = (blackHole->getPosition().x - objects[i]->getPosition().x) / abs((blackHole->getPosition().x - objects[i]->getPosition().x));
            float dir_y = (blackHole->getPosition().y - objects[i]->getPosition().y) / (abs(blackHole->getPosition().y - objects[i]->getPosition().y));

            const float vx_ = 50;
            const float vy_ = 50;
            float speed = 0.01;

            objects[i]->move(vx_ * speed * dir_x * accelerationBH, vy_ * speed * dir_y * accelerationBH);
            accelerationBH += 0.001;

        }
        else {
            accelerationBH = 1;
        }
    }
}


void Engine::updateBoss() {

   
    if (boss == nullptr && spawnBoss.getElapsedTime().asSeconds() > 1) {
        bool create = true;

        while (create) {
            float distance = 0;
            int x = rand() % 3000;
            int y = rand() % 3000;
            x = abs(x - player->getPosition().x);
            y = abs(y - player->getPosition().y);

            distance = sqrt(x * x + y * y);
            if (distance > 600) {
                bossCounter += 1;
                this->boss = new Boss(x, y, windowSize(), bossCounter * 10);
                x = 0;
                y = 0;
                create = false;
                cout << "NA MAPIE POJAWIL SIE BOSS" << endl;                
            }
        }
        spawnBoss.restart();
    }


    if (boss != nullptr) {

        this->bossAttackSpeed += 0.1f;
        if (this->bossAttackSpeed >= this->bossAttackSpeedMax) {
            // Dodawanie strzalow do Bossa

            float bossCenterX = boss->getGlobalBounds().left + boss->getGlobalBounds().width / 2;
            float bossCenterY = boss->getGlobalBounds().top + boss->getGlobalBounds().height / 2;

            if (!this->bossStronger) {
                this->objects.push_back(
                    new EnemyBullet("./TEKSTURY/BULLET/bullet1.png",
                        bossCenterX,
                        bossCenterY,
                        player->getCenter().x, player->getCenter().y, 4.5f));
            }
            else if (bossStronger) {
                // SRODEK
                this->objects.push_back(
                    new EnemyBullet("./TEKSTURY/BULLET/bullet1.png",
                        bossCenterX,
                        bossCenterY,
                        player->getCenter().x, player->getCenter().y, 6.f));

                // LEWA STRONA
                this->objects.push_back(
                    new EnemyBullet("./TEKSTURY/BULLET/bullet1.png",
                        boss->getGlobalBounds().left,
                        boss->getGlobalBounds().top,
                        player->getCenter().x, player->getCenter().y, 8.f));

                // PRAWA STRONA
                this->objects.push_back(
                    new EnemyBullet("./TEKSTURY/BULLET/bullet1.png",
                        boss->getGlobalBounds().left + boss->getGlobalBounds().width,
                        boss->getGlobalBounds().top + boss->getGlobalBounds().height,
                        player->getCenter().x, player->getCenter().y, 8.f));
            }

            bossAttackSpeed = 0.f;
        }

        for (int i = 0; i < objects.size(); i++) {
            if (Bullet* bullet = dynamic_cast<Bullet*>(objects[i])) {
                if (boss->collision(bullet)) {
                    delete objects.at(i);
                    objects.erase(objects.begin() + i);
                    boss->decreaseHp();
                    if (boss->getHp() % 10 == 0) {
                        cout << "BOSSOWI POZOSTALO " << boss->getHp() << endl;
                        this->bossAttackSpeedMax -= 1.f;
                    }
                    if (boss->getHp() == 50) {
                        this->bossStronger = true;
                    }
                    if (i > 0) {
                        i--;
                    }
                }
            }
        }
        this->boss->update(windowSize(), *player);
        if (boss->getHp() <= 0) {
            cout << "POKONANO BOSSA" << endl;
            player->setPlayerPoints(50);
            this->bossAttackSpeedMax = 20.f;
            this->player->updatePlayerMaxHp();        
            delete boss;
            boss = nullptr;
            spawnBoss.restart();
        }

       
    }
    
    
}


bool Engine::playAgain() {

    if (player->getPlayerHp() <= 0) {
        soundGameOver.play();
        if(Keyboard::isKeyPressed(Keyboard::Enter)) {
        return true;
        }
    }
    else {       
        return false;
    }

}

bool Engine::exitGame() {   
    return true;
}

// FUNCKJA RUN SILNIKA //

void Engine::run() {
    while (this->window->isOpen() && playAgain() == false ) {

        this->updateEvents();
        if (this->player->getPlayerHp() > 0) {
            this->update();
        }

        this->playAgain();
        this->render();
    }
}
