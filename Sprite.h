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

	bool follower;

public:
	Sprite(ALLEGRO_BITMAP *, bool);
	Sprite(ALLEGRO_BITMAP * nBmp, int nX, int nY);
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

	bool isFollower();

	void stop();
};

