#pragma once

#include <allegro5\allegro5.h>
#include <allegro5\allegro_primitives.h>
#include "Sprite.h"

class Game
{

private:
	ALLEGRO_DISPLAY* display;
	ALLEGRO_EVENT_QUEUE* evQueue;
	ALLEGRO_TIMER* timer;

	bool InitializeAllegro();
	void DeinitializeAllegro();

	Sprite* player;

	ALLEGRO_BITMAP * playerBMP;

	void Draw();

public:
	Game(void);
	~Game(void);

	void GameLoop();
};