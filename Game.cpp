#include "Game.h"


Game::Game(void)
{
	if(InitializeAllegro())
	{
		TILE_SIZE = 50;
		YOFFSET = 150;

		display = al_create_display(350,500);
		evQueue = al_create_event_queue();
		timer = al_create_timer(1.0 / 50);

		al_register_event_source(evQueue, al_get_keyboard_event_source());
		al_register_event_source(evQueue, al_get_timer_event_source(timer));

		playerBMP = al_create_bitmap(50,50);
		al_set_target_bitmap(playerBMP);

		al_draw_filled_circle(25,25,25,al_map_rgb(255,255,255));

		player = new Sprite(playerBMP);
		map = new TileMap();

		map->LoadMap("map01.txt");
	}
}


bool Game::InitializeAllegro()
{
	if(al_init() && al_install_keyboard() && al_init_primitives_addon())
		return true;
	else
		return false;
}

Game::~Game(void)
{

	al_destroy_bitmap(playerBMP);

	delete map;
	delete player;

	DeinitializeAllegro();
}

void Game::DeinitializeAllegro()
{
	al_destroy_display(display);
	al_destroy_event_queue(evQueue);
	al_destroy_timer(timer);
}

void Game::GameLoop()
{
	ALLEGRO_EVENT ev;

	player->setX(3);
	player->setY(2);

	al_set_target_bitmap(al_get_backbuffer(display));
	Draw();

	al_start_timer(timer);

	while(true)
	{
		al_wait_for_event(evQueue, &ev);

		if(ev.type == ALLEGRO_EVENT_KEY_DOWN)
		{
			if(ev.keyboard.keycode == ALLEGRO_KEY_ESCAPE)
				break;
			else if(ev.keyboard.keycode == ALLEGRO_KEY_LEFT)
				player->setVelocityX(-1);
			else if(ev.keyboard.keycode == ALLEGRO_KEY_RIGHT)
				player->setVelocityX(1);
			else if(ev.keyboard.keycode == ALLEGRO_KEY_DOWN)
				player->setVelocityY(1);
		}
		else if(ev.type == ALLEGRO_EVENT_TIMER)
		{
			UpdateObject(player);
			Draw();
		}
	}
}

void Game::UpdateObject(Sprite* object)
{
	int oldX = object->getX();
	int dX = object->getVelocityX();
	int newX = oldX + dX;

	if(CheckForTileCollision(newX, object->getY()))
		object->setX(newX);

	int oldY = object->getY();
	int dY = object->getVelocityY();
	int newY = oldY + dY;

	if(CheckForTileCollision(object->getX(), newY))
		object->setY(newY);

	object->setVelocityX(0);
	object->setVelocityY(0);
}

bool Game::CheckForTileCollision(int newX, int newY)
{
	if (newX < 0 || newX > 6 || newY > 9)
		return false;
	else if(map->getTile(newX,newY) == map->air)
		return true;

	else if(map->getTile(newX,newY) == map->ground)
	{
		map->BreakTile(newX,newY);
		return true;
	}

	return false;
}

void Game::Draw()
{
	al_clear_to_color(al_map_rgb(0,0,0));

	for(int y=0; y<10; y++)
		for(int x=0; x<7; x++)
			al_draw_bitmap(map->getTile(x,y),x * TILE_SIZE, y * TILE_SIZE,0);

	list<Sprite*>::iterator it = map->getFirstObject();
	list<Sprite*>::iterator end = map->getLastObject();

	for(;it != end; ++it)
		al_draw_bitmap((*it)->getImage(),(*it)->getX() * TILE_SIZE, (*it)->getY() * TILE_SIZE,0);

	al_draw_bitmap(player->getImage(),player->getX() * TILE_SIZE,player->getY() * TILE_SIZE,0);

	al_flip_display();
}