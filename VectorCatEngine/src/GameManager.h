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
//#include "UIManager.h"

class UIManager;
class VC_App;

class GameManager
{
public:
	GameManager(VC_App* app);
	virtual ~GameManager();

	virtual void Update();
	virtual void Render();

	virtual UIManager* GetUIManager() { return m_pUIManager; }
	virtual UICamera* GetUICamera() { return m_pUICamera; }
	virtual VC_App* GetApp() { return m_pApp; }

private:
	VC_App* m_pApp;
	UIManager* m_pUIManager;
	//Camera m_testCamera;
	UICamera* m_pUICamera;
};

#endif // GAMEMANAGER_H

