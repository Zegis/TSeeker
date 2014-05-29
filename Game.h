#pragma once

#include <allegro5\allegro5.h>
#include <allegro5\allegro_primitives.h>
#include <allegro5\allegro_font.h>
#include <allegro5\allegro_ttf.h>
#include <allegro5\allegro_image.h>
#include "Sprite.h"
#include "TileMap.h"
#include <sstream>

using std::stringstream;

class Game
{

private:
	ALLEGRO_DISPLAY* display;
	ALLEGRO_EVENT_QUEUE* evQueue;
	ALLEGRO_TIMER* timer;

	bool InitializeAllegro();
	void DeinitializeAllegro();

	Sprite* player;
	Sprite* follower;
	TileMap* map;

	ALLEGRO_BITMAP * playerBMP;
	ALLEGRO_BITMAP* followerBMP;

	ALLEGRO_FONT* font;
	ALLEGRO_FONT* msgFont;

	int TILE_SIZE;
	int YOFFSET;

	int MAXLVL;

	int currentLvl;

	void Draw();
	void DrawEnd();

	bool inGame;
	bool inLevel;

	void UpdateObject(Sprite* object);

	bool CheckForTileCollision(int nexX, int newY, bool isFollower);

	void CheckObjectCollisions(Sprite* object);
	Sprite* GetSpriteCollision(Sprite* object);

	void GameLoop();

	void GameTutorial();

	bool GameMenu();

	string assembleMapName();

public:
	Game(void);
	~Game(void);

	void Run();
};