#include "Sprite.h"


Sprite::Sprite(ALLEGRO_BITMAP* nBmp, bool nfollower)
{
	bmp = nBmp;
	dx = 0;
	dy = 0;
	x = 0;
	y = 0;
	follower = nfollower;
}

Sprite::Sprite(ALLEGRO_BITMAP* nBmp, int nX, int nY)
{
	bmp = nBmp;
	dx = 0;
	dy = 0;
	x = nX;
	y = nY;	
}

Sprite::Sprite()
{
	dx = 0;
	dy = 0;
	x = y = 0;
}

int Sprite::getHeight()
{
	return al_get_bitmap_height(bmp);
}

int Sprite::getWidth()
{
	return al_get_bitmap_width(bmp);
}

int Sprite::getX()
{
	return x;
}

void Sprite::setX(int newX)
{
	x = newX;
}

int Sprite::getY()
{
	return y;
}

void Sprite::setY(int newY)
{
	y = newY;
}

int Sprite::getVelocityX()
{
	return dx;
}

int Sprite::getVelocityY()
{
	return dy;
}

void Sprite::setVelocityY(int newdY)
{
	dy = newdY;
}
void Sprite::setVelocityX(int newdX)
{
	dx = newdX;
}

bool Sprite::isFollower()
{
	return follower;
}

ALLEGRO_BITMAP * Sprite::getImage()
{
	return bmp;
}

Sprite::~Sprite(void)
{
}
