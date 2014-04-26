#pragma once

#include <allegro5\allegro5.h>

class Game
{

private:
	ALLEGRO_DISPLAY* display;
	ALLEGRO_EVENT_QUEUE* evQueue;

public:
	Game(void);
	~Game(void);

	void GameLoop();
};