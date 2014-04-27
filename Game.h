#pragma once

#include <allegro5\allegro5.h>
#include <allegro5\allegro_primitives.h>
#include <allegro5\allegro_font.h>
#include <allegro5\allegro_ttf.h>
#include "Sprite.h"
#include "TileMap.h"

class Game
{

private:
	ALLEGRO_DISPLAY* display;
	ALLEGRO_EVENT_QUEUE* evQueue;
	ALLEGRO_TIMER* timer;

	bool InitializeAllegro();
	void DeinitializeAllegro();

	Sprite* player;
	TileMap* map;

	ALLEGRO_BITMAP * playerBMP;

	ALLEGRO_FONT* font;

	int TILE_SIZE;
	int YOFFSET;

	void Draw();
	void DrawEnd();

	bool inGame;

public:
	Game(void);
	~Game(void);

	void UpdateObject(Sprite* object);

	bool CheckForTileCollision(int nexX, int newY);

	void CheckObjectCollisions(Sprite* object);
	Sprite* Game::GetSpriteCollision(Sprite* object);

	void GameLoop();
};