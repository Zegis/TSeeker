#include "Game.h"


Game::Game(void)
{
	if(InitializeAllegro())
	{
		display = al_create_display(800,600);
		evQueue = al_create_event_queue();
		timer = al_create_timer(1.0 / 50);


		al_register_event_source(evQueue, al_get_keyboard_event_source());
		al_register_event_source(evQueue, al_get_timer_event_source(timer));

		playerBMP = al_create_bitmap(50,50);
		al_set_target_bitmap(playerBMP);

		al_draw_filled_circle(25,25,20,al_map_rgb(255,255,255));

		player = new Sprite(playerBMP);

		
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
	DeinitializeAllegro();
	al_destroy_bitmap(playerBMP);

	delete player;
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

	player->setX(400);
	player->setY(350);

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
				player->setVelocityX(-4);
			else if(ev.keyboard.keycode == ALLEGRO_KEY_RIGHT)
				player->setVelocityX(4);
		}
		else if(ev.type == ALLEGRO_EVENT_KEY_UP)
		{
			if(ev.keyboard.keycode == ALLEGRO_KEY_LEFT || ev.keyboard.keycode == ALLEGRO_KEY_RIGHT)
				player->setVelocityX(0);
		}
		else if(ev.type == ALLEGRO_EVENT_TIMER)
		{
			player->update(1);
			Draw();
		}
	}
}

void Game::Draw()
{
	al_clear_to_color(al_map_rgb(0,0,0));

	al_draw_bitmap(player->getImage(),player->getX(),player->getY(),0);

	al_flip_display();
}