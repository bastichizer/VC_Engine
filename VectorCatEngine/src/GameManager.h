//==============================================================
// GameManager.h
//
// Game manager class, controls basic game logic and handles
// updates and rendering for ingame objects
//==============================================================

#ifndef GAMEMANAGER_H
#define GAMEMANAGER_H

#include "RenderManager.h"
#include "UICamera.h"
#include "UIManager.h"

class GameManager
{
public:
	GameManager();
	~GameManager();

	void Update();
	void Render();

	UIManager* GetUIManager() { return m_pUIManager; }
	UICamera* GetUICamera() { return m_pUICamera; }

private:
	UIManager* m_pUIManager;
	//Camera m_testCamera;
	UICamera* m_pUICamera;
};

#endif // GAMEMANAGER_H

