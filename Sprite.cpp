#include "Sprite.h"


Sprite::Sprite(ALLEGRO_BITMAP* nBmp)
{
	bmp = nBmp;
	dx = 0;
	dy = 0;
}

Sprite::Sprite()
{
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

void Sprite::update(long elapsedTime)
{
	y += dy * elapsedTime;
	x += dx * elapsedTime;
}

ALLEGRO_BITMAP * Sprite::getImage()
{
	return bmp;
}

Sprite::~Sprite(void)
{
}
