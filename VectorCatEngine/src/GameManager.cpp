//==============================================================
// GameManager.cpp
//==============================================================

#include "GameManager.h"
#include "global.h"
#include "InputManager.h"
#include "UIManager.h"
#include "VC_App.h"

GameManager::GameManager(VC_App* app) :
m_pApp(app)
{
	m_pUIManager = new UIManager(this);
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