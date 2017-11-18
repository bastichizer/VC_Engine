#include "BackgroundSprite.h"

BackgroundSprite::BackgroundSprite(int width, int height, int posX, int posY, WCHAR* texturePath) : Sprite(width, height, posX, posY),
m_bScrollX(false),
m_bScrollY(false)
{
	Init(texturePath);
	m_vel = QE::Vector2f(0.0f, 0.0f);
}

BackgroundSprite::~BackgroundSprite()
{

}

void BackgroundSprite::Render(Camera* cam)
{
	Sprite::Render(cam);
}

