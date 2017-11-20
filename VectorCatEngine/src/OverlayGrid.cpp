//================================================================
// OverlayGrid.cpp
//================================================================

#include "OverlayGrid.h"
#include "global.h"

OverlayGrid::OverlayGrid(int width, int height, int posX, int posY, int offsetX, int offsetY, int gridSideLength, int gridCenterX, int gridCenterY, WCHAR* filename, UIManager* uiManager) : 
Sprite(width, height, posX, posY, uiManager),
m_displayGrid(true),
m_offsetX(offsetX),
m_offsetY(offsetY),
m_gridSideLength(gridSideLength),
m_gridCenter(XMINT2(gridCenterX, gridCenterY)),
m_currentScale(1.0f)
{
	Init(filename);
}

OverlayGrid::~OverlayGrid()
{

}

void OverlayGrid::Render(Camera* cam)
{
	if (m_displayGrid)
	{
		int scaledOffsetX = (int)((float)m_offsetX * m_currentScale);
		int scaledOffsetY = (int)((float)m_offsetY * m_currentScale);
		int halfOffsetX = scaledOffsetX / 2;
		int halfOffsetY = scaledOffsetY / 2;
		int gridHalves = m_gridSideLength * 2;
		
		for (int y = 0; y < m_gridSideLength; ++y)
		{
			for (int x = 0; x < m_gridSideLength; ++x)
			{
				m_pos.x = (int)((float)m_gridCenter.x * m_currentScale) - scaledOffsetX + (x - y) * halfOffsetX;
				m_pos.y = (int)((float)m_gridCenter.y * m_currentScale) + scaledOffsetY - m_gridSideLength * halfOffsetY + (x + y) * halfOffsetY;
				Sprite::Render(cam);
			}
		}
	}
}

void OverlayGrid::ZoomIn()
{
	if (m_currentScale < 2.0f)
	{
		m_currentScale += 0.5f;
	}
	SetScale(m_currentScale);
}

void OverlayGrid::ZoomOut()
{
	if (m_currentScale > 1.0f)
	{
		m_currentScale -= 0.5f;
	}
	SetScale(m_currentScale);
}

