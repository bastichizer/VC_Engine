//==============================================================
// GameManager.cpp
//==============================================================

#include "GameManager.h"
#include "global.h"
#include "InputManager.h"

GameManager::GameManager()
{
	m_pUIManager = new UIManager();
	//m_pUIManager->SetCurrentExperience(0.5f);
	//m_pUIManager->SetCurrentHappiness(0.8f);
}

GameManager::~GameManager()
{
	Sprite::Cleanup();
	delete m_pUIManager;
}

void GameManager::Update()
{
	m_pUICamera->UpdateViewMatrix();
	m_pUIManager->Update();
}

void GameManager::Render()
{
	m_pUIManager->Render(m_pUICamera);
}