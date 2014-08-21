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

	ALLEGRO_BITMAP *Images[10][7];

	list<Sprite*> objects;

public:
	TileMap(void);
	~TileMap(void);

	ALLEGRO_BITMAP* getTile(int x, int y);

	ALLEGRO_BITMAP* ground;
	ALLEGRO_BITMAP* grass;
	ALLEGRO_BITMAP* treasure;
	ALLEGRO_BITMAP* air;
	ALLEGRO_BITMAP* rock;
	ALLEGRO_BITMAP* digged;

	ALLEGRO_BITMAP* playerBMP;

	bool LoadMap(string, Sprite*, Sprite*);

	list<Sprite*>::iterator getFirstObject();
	list<Sprite*>::iterator getLastObject();

	void BreakTile(int x, int y);

};