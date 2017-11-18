//================================================================
// GameMap.cpp
//================================================================

#include "GameMap.h"

GameMap::GameMap(int sizeX, int sizeY, int posX, int posY, WCHAR* texturePath) : Sprite::Sprite(sizeX, sizeY, posX, posY),
m_currentScale(1.0f)
{
	Init(texturePath);
}

GameMap::~GameMap()
{

}

void GameMap::Render(Camera* cam)
{
	Sprite::Render(cam);
}

void GameMap::ZoomIn()
{
	if (m_currentScale < 2.0f)
	{
		m_currentScale += 0.5f;
	}
	SetScale(m_currentScale);
}

void GameMap::ZoomOut()
{
	if (m_currentScale > 1.0f)
	{
		m_currentScale -= 0.5f;
	}
	SetScale(m_currentScale);
}

