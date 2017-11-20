//==============================================================
// UIButton.h
//==============================================================

#ifndef UIBUTTON_H
#define UIBUTTON_H

#include "Sprite.h"
#include "Delegate.h"
#include "InputManager.h"
#include <vector>
using namespace std;

class UIButton : public Sprite
{
public:
	UIButton(int width, int height, int posX, int posY, float defaultBrightness, float hoverBrightness, float pressedBrightness, WCHAR* filename, UIManager* uiManager);
	~UIButton();

	void OnPressed(InputManager::LeftMouseButtonStatus clickState);

	void PushDelegate(Delegate<void, int>* del);
	void RegisterButtonWithInputManager();

private:
	bool CheckMouseOverButton();

	float m_defaultBrightness;
	float m_hoverBrightness;
	float m_pressedBrightness;

	bool m_isPressed;

	vector<Delegate<void, int>*> m_delegateVector;

	Delegate<void, InputManager::LeftMouseButtonStatus>* m_pLeftButtonDelegate;
};

#endif // UIBUTTON_H

