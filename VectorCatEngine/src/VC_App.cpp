#include "VC_App.h"
#include "RenderManager.h"

VC_App::VC_App()
{

}

VC_App::~VC_App()
{

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
