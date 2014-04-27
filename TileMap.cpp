#include "TileMap.h"


TileMap::TileMap(void)
{
	ground = al_create_bitmap(50,50);
	al_set_target_bitmap(ground);
	al_clear_to_color(al_map_rgb(173,102,9));

	treasure = al_create_bitmap(50,50);
	al_set_target_bitmap(treasure);
	al_clear_to_color(al_map_rgb(231,242,7));

	air = al_create_bitmap(50,50);
	al_set_target_bitmap(air);
	al_clear_to_color(al_map_rgb(82,223,255));
}


TileMap::~TileMap(void)
{
	std::cout << "Bla, bla";

	for(int i=0; i<7; ++i)
		for(int j=0; j<7; ++j)
			Images[i][j] = NULL;

	objects.clear();

	al_destroy_bitmap(ground);
	al_destroy_bitmap(treasure);
	al_destroy_bitmap(air);
}

ALLEGRO_BITMAP* TileMap::getTile(int x, int y)
{
	return Images[y][x];
}

void TileMap::LoadMap(string mapName)
{
	fstream mapFile(mapName, fstream::in);
	
	int y = 0;
	string mapLine;

	while(getline(mapFile, mapLine))
	{		
		int length = mapLine.length();
		for(int i=0; i < length; ++i)
		{
			if(mapLine[i] == '.') Images[y][i] = air;
			if (mapLine[i] == '0') Images[y][i] = ground;
			else if (mapLine[i] == '1'){
				Images[y][i] = ground;

			}
		}
		++y;
	}
	mapFile.close();
}

void TileMap::BreakTile(int x, int y)
{
	if(Images[y][x] == ground)
		Images[y][x] == air;
}