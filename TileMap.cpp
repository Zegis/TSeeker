#include "TileMap.h"


TileMap::TileMap(void)
{
	ground = al_create_bitmap(50,50);
	al_set_target_bitmap(ground);
	al_clear_to_color(al_map_rgb(173,102,9));

	treasure = al_load_bitmap("treasure.png");

	air = al_create_bitmap(50,50);
	al_set_target_bitmap(air);
	al_clear_to_color(al_map_rgb(82,223,255));

	rock = al_load_bitmap("rock.png");
	grass = al_load_bitmap("grass.png");
}


TileMap::~TileMap(void)
{
	for(int i=0; i<7; ++i)
		for(int j=0; j<7; ++j)
			Images[i][j] = NULL;

	objects.clear();

	al_destroy_bitmap(ground);
	al_destroy_bitmap(treasure);
	al_destroy_bitmap(air);
	al_destroy_bitmap(rock);
}

ALLEGRO_BITMAP* TileMap::getTile(int x, int y)
{
		return Images[y][x];
}

void TileMap::LoadMap(string mapName, Sprite* player, Sprite* follower)
{
	fstream mapFile(mapName, fstream::in);

	objects.clear();
	
	int y = 0;
	string mapLine;

	while(getline(mapFile, mapLine))
	{		
		int length = mapLine.length();
		for(int i=0; i < length; ++i)
		{
			if(mapLine[i] == '.') Images[y][i] = air;
			else if (mapLine[i] == '@'){
				Images[y][i] = air;
				player->setX(i);
				player->setY(y);
			}
			else if (mapLine[i] == 'F')
			{
				Images[y][i] = air;
				follower->setX(i);
				follower->setY(y);
			}
			else if (mapLine[i] == '0') Images[y][i] = ground;
			else if (mapLine[i] == 'R') Images[y][i] = rock;
			else if (mapLine[i] == 'G') Images[y][i] = grass;
			else if (mapLine[i] == '1'){
				Images[y][i] = air;
				objects.push_back(new Sprite(treasure,i,y));
			}
		}
		++y;
	}
	mapFile.close();
}

void TileMap::BreakTile(int x, int y)
{
	if(Images[y][x] == ground || Images[y][x] == grass)
		Images[y][x] = air;
}

list<Sprite*>::iterator TileMap::getFirstObject()
{
	return objects.begin();
}

list<Sprite*>::iterator TileMap::getLastObject()
{
	return objects.end();
}
