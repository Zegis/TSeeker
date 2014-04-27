#include "Game.h"


Game::Game(void)
{
	if(InitializeAllegro())
	{
		TILE_SIZE = 50;
		YOFFSET = 150;

		display = al_create_display(350,500);
		evQueue = al_create_event_queue();
		timer = al_create_timer(1.0 / 05);

		al_register_event_source(evQueue, al_get_keyboard_event_source());
		al_register_event_source(evQueue, al_get_timer_event_source(timer));

		playerBMP = al_create_bitmap(50,50);
		al_set_target_bitmap(playerBMP);
		al_draw_filled_circle(25,25,25,al_map_rgb(255,255,255));

		followerBMP = al_create_bitmap(50,50);
		al_set_target_bitmap(followerBMP);
		al_draw_filled_ellipse(25,25,25,15,al_map_rgb(187,52 ,224));

		font = al_load_ttf_font("pirulen.ttf",40,0);
		msgFont = al_load_ttf_font("pirulen.ttf", 18,0);

		player = new Sprite(playerBMP, false);
		follower = new Sprite(followerBMP, true);
		map = new TileMap();

		map->LoadMap("map01.txt", player, follower);

		inGame = true;
		al_set_target_bitmap(al_get_backbuffer(display));
	}
}


bool Game::InitializeAllegro()
{
	if(al_init() && al_install_keyboard() && al_init_primitives_addon())
	{
		al_init_font_addon();		
		al_init_ttf_addon();
		
		return true;
	}
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
	al_destroy_font(font);
	al_destroy_display(display);
	al_destroy_event_queue(evQueue);
	al_destroy_timer(timer);
}

void Game::Run()
{
	
	if(GameMenu())
		GameLoop();
	else
		al_rest(0.5);
}

bool Game::GameMenu()
{

	al_clear_to_color(al_map_rgb(0,0,0));

	int lineY = 140;
	
	al_draw_text(font,al_map_rgb(255,255,255),20, lineY,0,"Treasure");

	int lineOffset = al_get_font_line_height(font);
	lineY += lineOffset; 

	al_draw_text(font,al_map_rgb(255,255,255),65, lineY,0,"Seeker");

	lineY = 440;

	al_draw_text(msgFont, al_map_rgb(255,255,255), 15, lineY, 0, "Press ENTER to start");
	lineOffset = al_get_font_line_height(msgFont);
	lineY += lineOffset;

	al_draw_text(msgFont, al_map_rgb(255,255,255), 65, lineY, 0, "ESCAPE to quit");

	al_flip_display();

	ALLEGRO_EVENT ev;

	while(true)
	{
		al_wait_for_event(evQueue, &ev);

		if(ev.type==ALLEGRO_EVENT_KEY_DOWN) 
			if (ev.keyboard.keycode == ALLEGRO_KEY_ENTER)
				return true;
			else if (ev.keyboard.keycode == ALLEGRO_KEY_ESCAPE)
				return false;
	}
}

void Game::GameLoop()
{
	ALLEGRO_EVENT ev;

	
	Draw();

	al_start_timer(timer);

	while(inGame)
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
			else if(ev.keyboard.keycode == ALLEGRO_KEY_PAD_4)
				follower->setVelocityX(-1);
			else if(ev.keyboard.keycode == ALLEGRO_KEY_PAD_5)
				follower->setVelocityX(0);
			else if(ev.keyboard.keycode == ALLEGRO_KEY_PAD_6)
				follower->setVelocityX(1);
		}
		else if(ev.type == ALLEGRO_EVENT_TIMER)
		{
			UpdateObject(player);
			UpdateObject(follower);
			Draw();
		}
	}

	DrawEnd();
	al_rest(1);
}

void Game::UpdateObject(Sprite* object)
{
	if(object->isFollower())
	{
		object->setVelocityY(1);
	}

	int oldX = object->getX();
	int dX = object->getVelocityX();
	int newX = oldX + dX;

	if(CheckForTileCollision(newX, object->getY(), object->isFollower()))
		object->setX(newX);
	else
		object->setVelocityX(0);

	int oldY = object->getY();
	int dY = object->getVelocityY();
	int newY = oldY + dY;

	if(CheckForTileCollision(object->getX(), newY, object->isFollower()))
		object->setY(newY);
	else
		object->setVelocityY(0);

	if(!object->isFollower())
	{
		object->setVelocityX(0);
		object->setVelocityY(0);
	}	

	CheckObjectCollisions(object);
}

bool Game::CheckForTileCollision(int newX, int newY, bool isFollower)
{
	if (newX < 0 || newX > 6 || newY > 9)
		return false;
	else if(map->getTile(newX,newY) == map->air)
		return true;

	else if(map->getTile(newX,newY) == map->ground && !isFollower)
	{
		map->BreakTile(newX,newY);
		return true;
	}

	return false;
}

void Game::CheckObjectCollisions(Sprite* object)
{
	Sprite* collisionSprite = GetSpriteCollision(object);

	if( collisionSprite != NULL && object->isFollower())
		inGame = false;
}

Sprite* Game::GetSpriteCollision(Sprite* object)
{
	list<Sprite*>::iterator it = map->getFirstObject();
	list<Sprite*>::iterator end = map->getLastObject();

	for(;it != end; ++it)
	{
		if( (*it)->getX() == object->getX() && (*it)->getY() == object->getY())
			return (*it);
	}

	return NULL;
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

	al_draw_bitmap(follower->getImage(), follower->getX() * TILE_SIZE, follower->getY() * TILE_SIZE,0);

	al_flip_display();
}

void Game::DrawEnd()
{
	if(!inGame)
	{
		al_clear_to_color(al_map_rgb(0,0,0));

		al_draw_text(font,al_map_rgb(255,255,255), 45, 180, 0, "Victory!");

		al_draw_text(msgFont,al_map_rgb(255,255,255), 30, 280, 0, "Thanks for playing!");
	}
	
	al_flip_display();
}