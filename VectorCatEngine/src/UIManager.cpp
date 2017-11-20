//==============================================================
// UIManager.cpp
//==============================================================

#include "UIManager.h"
#include "global.h"
#include "OverlayGrid.h"

UIManager::UIManager(GameManager* gameManager) :
m_currentViewScale(1.0f),
m_pGameManager(gameManager)
{
	
}

UIManager::~UIManager()
{
	for (int i = 0; i < (int)m_backgroundVector.size(); ++i)
	{
		delete m_backgroundVector[i];
		m_backgroundVector[i] = NULL;
	}
	for (int i = 0; i < (int)m_midgroundVector.size(); ++i)
	{
		if (m_midgroundVector[i])
		{
			delete m_midgroundVector[i];
			m_midgroundVector[i] = NULL;
		}
	}
	for (int i = 0; i < (int)m_foregroundVector.size(); ++i)
	{
		delete m_foregroundVector[i];
		m_foregroundVector[i] = NULL;
	}
	for (int i = 0; i < (int)m_buttonDelegates.size(); ++i)
	{
		delete m_buttonDelegates[i];
		m_buttonDelegates[i] = NULL;
	}
}

void UIManager::Update()
{

}

void UIManager::Render(Camera* cam)
{
	// Render function setup to render from back to front to avoid alpha blending issues

	for (int i = 0; i < (int)m_backgroundVector.size(); ++i)
	{
		m_backgroundVector[i]->Render(cam);
	}
	for (int i = 0; i < (int)m_midgroundVector.size(); ++i)
	{
		m_midgroundVector[i]->Render(cam);
	}
	for (int i = 0; i < (int)m_foregroundVector.size(); ++i)
	{
		m_foregroundVector[i]->Render(cam);
	}
}



