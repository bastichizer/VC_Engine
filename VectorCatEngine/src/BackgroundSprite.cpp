#include "BackgroundSprite.h"
#include "UIManager.h"
#include "VC_App.h"

BackgroundSprite::BackgroundSprite(int width, int height, int posX, int posY, WCHAR* texturePath, UIManager* uiManager) : Sprite(width, height, posX, posY, uiManager),
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
	float delta = (float)m_pUIManager->GetGameManager()->GetApp()->GetTick() * 0.001f;
	if (m_bScrollX)
	{
		m_pos.x += m_vel.x * delta;
		m_pos.x = floorf(m_pos.x);
	}
	if (m_bScrollY)
	{
		m_pos.y += m_vel.y * delta;
		m_pos.y = floorf(m_pos.y);
		if (m_pos.y < -m_height)
		{
			m_pos.y = g_windowHeight - (m_pos.y + m_height);
		}
		else if (m_pos.y > g_windowHeight)
		{
			m_pos.y = m_pos.y - g_windowHeight;
		}
	}

	QE::Vector2f basePos = QE::Vector2f(m_pos.x, m_pos.y);
	if (m_pos.y > 0.0f)
	{
		while (m_pos.y > 0.0f)
		{
			m_pos.y -= (float)m_height;
		}
	}

	while (m_pos.y <= g_windowHeight)
	{
		Sprite::Render(cam);
		m_pos.y += m_height;
	}

	m_pos.x = basePos.x;
	m_pos.y = basePos.y;
}

