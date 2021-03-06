//==============================================================
// UIManager.h
//==============================================================

#ifndef UIMANAGER_H
#define UIMANAGER_H

#include "GameMap.h"
#include "BackgroundSprite.h"
#include "Delegate.h"
#include "UIButton.h"
#include "tinyxml2-master\tinyxml2.h" // TinyXML2 lib used for xml parsing
#include "GameManager.h"
#include <vector>
using namespace std;

class UIManager
{
public:
	UIManager(GameManager* gameManager);
	virtual ~UIManager();

	virtual void Update();
	virtual void Render(Camera* cam);

	GameManager* GetGameManager() { return m_pGameManager; }

protected:
	vector<Sprite*> m_backgroundVector; // background sprite elements - generally background scenery type stuff
	vector<Sprite*> m_midgroundVector; // midground sprite elements - typically this is where the active gameplay elements go
	vector<Sprite*> m_foregroundVector; // UI elements go here

	float m_currentViewScale; // the scale of the background and midground elements for zooming

	vector<Delegate<void, int>*> m_buttonDelegates;

	GameManager* m_pGameManager;
};

#endif // UIMANAGER_H

