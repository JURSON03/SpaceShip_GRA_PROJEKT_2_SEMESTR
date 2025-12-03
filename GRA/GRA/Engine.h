
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include <iostream>

#include <math.h>

#include "Player.h"
#include "Bullet.h"
#include "Background.h"
#include "Asteroid.h"
#include "Gui.h"
#include "Heart.h"
#include "Enemy.h"
#include "EnemyBullet.h"
#include "Potion.h"
#include "BlackHole.h"
#include "BOSS.h"

using namespace std;
using namespace sf;


class Engine
{

private:

    // BOSS
    Boss* boss;
    float bossAttackSpeed;
    float bossAttackSpeedMax;
    bool bossStronger;
    Clock spawnBoss;
    int bossCounter;

    // Sounds shots
    Sound soundShot;
    SoundBuffer bufferShot;
    bool isMouseButtonDown;

    // Sounds gameover
    Sound soundGameOver;
    SoundBuffer bufferGameOver;

    // BlackHole
    BlackHole* blackHole;
    float accelerationBH;

    // Window
    RenderWindow* window;
    Event event;
    View view;

    View defaultView;
    View currentView;

    // GUI
    Gui* GUI;

    //Strzaly



    Clock potionClock;
    float potionTime;


    // Granice widoku gracza oraz k¹t
    FloatRect viewBounds;
    float angles;

    // Asteroidy

    float asteroidSpawnTimer;
    float asteroidSpawnTimerMax;


    // Mapa
    Background* background;

    // Potion (dodaje attackSpeed) 
    float potionTimer;
    float potionTimerMax;
    int potionCounter;

    // Player
    Player* player;

    // Difficulty leavel
    Clock diffClock;

    // Enemy

    float enemySpawnTimer;
    float enemySpawnTimerMax;
    float enemyBulletSpawnTimer;
    float enemyBulletSpawnTimerMax;
    int maxEnemies;

    // Bonusy

    float heartSpawnTimer;
    float heartSpawnMaxTimer;
    int heartCounter;

    // GraphicalObjects
    vector <GraphicalObject*> objects;


    void initWindow();
    void initPlayer();
    // void initBullet();
    void initBackground();
    void initGUI();


public:

    Engine();
    ~Engine();
    void run();



    void updateEvents();
    void render();
    void update();

    FloatRect windowSize();
    void updateBullet();
    void updateInputPlayer();
    void updateCamera();
    void initCamera();
    void updateAnglesPlayer();
    void updateAsteroid();
    void updateAsteroidCollision();
    void updatePlayerHeart();
    bool playAgain();
    bool exitGame();
    void updateEnemyBullet();
    void updateEnemy();
    void updatePotion();
    void updateDifficultyLeavel();
    void updateBlackHole();
    void updateBoss();
};