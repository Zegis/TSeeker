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

class TileMap
{
private:

	ALLEGRO_BITMAP* ground;
	ALLEGRO_BITMAP* treasure;

	ALLEGRO_BITMAP *Images[7][7];

public:
	TileMap(void);
	~TileMap(void);

	ALLEGRO_BITMAP* getTile(int, int);

	void LoadMap(string);

};