#include "TileMap.h"


TileMap::TileMap(void)
{
	air = al_create_bitmap(50,50);

	grass = al_load_bitmap("res/grass.png");
	ground = al_load_bitmap("res/dirt.png");
	digged = al_load_bitmap("res/dig.png");

	ALLEGRO_BITMAP * tmp;

	tmp = al_load_bitmap("res/treasure.png");

	treasure = al_create_bitmap(50,50);
	al_set_target_bitmap(treasure);
	al_draw_bitmap(ground,0,0,0);
	al_draw_bitmap(tmp,5,5,0);

	rock = al_create_bitmap(50,50);
	al_set_target_bitmap(rock);
	al_draw_bitmap(ground,0,0,0);
	al_draw_bitmap(al_load_bitmap("res/rock_1.png"),6,3,0);

	al_destroy_bitmap(tmp);
}


TileMap::~TileMap(void)
{
	for(int i=0; i<7; ++i)
		for(int j=0; j<7; ++j)
			Images[i][j] = NULL;

	destroyObjectsOnMap();

	al_destroy_bitmap(ground);
	al_destroy_bitmap(treasure);
	al_destroy_bitmap(air);
	al_destroy_bitmap(rock);
}

VOID TileMap::destroyObjectsOnMap()
{
	if(objects.size() > 0)
	{
		list<Sprite*>::iterator it = objects.begin();
		while(it != objects.end())
		{
			delete (*it);
			objects.erase(it++);
		}
	}
}

ALLEGRO_BITMAP* TileMap::getTile(int x, int y)
{
		return Images[y][x];
}

bool TileMap::LoadMap(string mapName, Sprite* player, Sprite* follower)
{
	fstream mapFile(mapName, fstream::in);

	destroyObjectsOnMap();

	if(mapFile)
	{
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
		return true;
	}
	else
	{
		std::cout << "Brak mapy: " << mapName << std::endl;
		return false;
	}
}

void TileMap::BreakTile(int x, int y)
{
	if(Images[y][x] == ground || Images[y][x] == grass)
		Images[y][x] = digged;
}

list<Sprite*>::iterator TileMap::getFirstObject()
{
	return objects.begin();
}

list<Sprite*>::iterator TileMap::getLastObject()
{
	return objects.end();
}
