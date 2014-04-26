#pragma once

#include <allegro5\allegro5.h>

class Sprite
{

private:
	ALLEGRO_BITMAP *bmp;

	int x;
	int y;

	int dx;
	int dy;

public:
	Sprite(ALLEGRO_BITMAP *);
	Sprite();
	~Sprite(void);

	ALLEGRO_BITMAP* getImage();

	int getWidth();
	int getHeight();

	int getX();
	int getY();

	void setX(int);
	void setY(int);

	int getVelocityX();
	int getVelocityY();

	void setVelocityX(int);
	void setVelocityY(int);

	void update(long elapsedTime);
};

