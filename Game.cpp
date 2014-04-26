#include "Game.h"


Game::Game(void)
{
	if(al_init() && al_install_keyboard())
	{
		display = al_create_display(800,600);
		evQueue = al_create_event_queue();

		al_register_event_source(evQueue, al_get_keyboard_event_source());
	}
}


Game::~Game(void)
{
}

void Game::GameLoop()
{
	ALLEGRO_EVENT ev;

	while(true)
	{
		al_wait_for_event(evQueue, &ev);

		if(ev.type == ALLEGRO_EVENT_KEY_DOWN && ev.keyboard.keycode == ALLEGRO_KEY_ESCAPE)
			break;
	}
}