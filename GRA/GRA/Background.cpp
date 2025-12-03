#include "Background.h"


using namespace std;
using namespace sf;

Background::Background() : GraphicalObject("./TEKSTURY/BACKGROUND/SPACE2.png", Vector2f(0.f, 0.f))
{
	if (!music.openFromFile("./MUSIC/BackGround.ogg")) {
		cout << "ERROR::BACKGROUND::NIE UDALO SIE WCZYTAC MUZYKI" << endl;
	}
	music.setVolume(20);
	music.play();
	music.setLoop(true);

	
}

Background::~Background() = default;

void Background::update()
{
	
}



