#include "VC_App.h"
#include "RenderManager.h"
#include "GameManager.h"

VC_App::VC_App()
{
	m_pGameManager = NULL;
}

VC_App::~VC_App()
{
	if (m_pGameManager)
	{
		delete m_pGameManager;
	}
}

void VC_App::Init()
{
	m_bIsStartFrame = true;

	m_prevTime = GetTickCount();
	m_currentTime = GetTickCount();
	m_tick = 0;
}

void VC_App::Update()
{
	if (m_bIsStartFrame)
	{
		m_bIsStartFrame = false;
		return;
	}

	m_currentTime = GetTickCount();
	m_tick = m_currentTime - m_prevTime;
	m_prevTime = m_currentTime;
}

void VC_App::Render()
{

}

void VC_App::Shutdown()
{

}
