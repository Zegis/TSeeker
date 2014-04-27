#pragma once

#include<allegro5\allegro5.h>
#include<list>
#include "Sprite.h"
#include <string>
#include <fstream>
#include <iostream>

using std::string;
using std::fstream;
using std::getline;
using std::list;

class TileMap
{
private:

	ALLEGRO_BITMAP* ground;
	ALLEGRO_BITMAP* treasure;
	ALLEGRO_BITMAP* air;

	ALLEGRO_BITMAP *Images[10][7];

	list<Sprite> objects;

public:
	TileMap(void);
	~TileMap(void);

	ALLEGRO_BITMAP* getTile(int x, int y);

	void LoadMap(string);

	void BreakTile(int x, int y);

};