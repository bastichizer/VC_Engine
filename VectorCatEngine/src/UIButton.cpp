//===============================================================
// UIButton.cpp
//===============================================================

#include "UIButton.h"
#include "UIManager.h"
#include "global.h"

UIButton::UIButton(int width, int height, int posX, int posY, float defaultBrightness, float hoverBrightness, float pressedBrightness, WCHAR* filename)
: Sprite(width, height, posX, posY),
m_defaultBrightness(defaultBrightness),
m_hoverBrightness(hoverBrightness),
m_pressedBrightness(pressedBrightness),
m_isPressed(false)
{
	Init(filename);
	m_spriteConstants.brightness = m_defaultBrightness;
}

UIButton::~UIButton()
{
	if (m_pLeftButtonDelegate)
	{
		delete m_pLeftButtonDelegate;
	}
}

void UIButton::OnPressed(InputManager::LeftMouseButtonStatus clickState)
{
	if (clickState == InputManager::LeftMouseButtonStatus::LB_Clicked)
	{
		if (CheckMouseOverButton())
		{
			for (int i = 0; i < (int)m_delegateVector.size(); ++i)
			{
				(*m_delegateVector[i])(0);
			}
		}
	}
}

void UIButton::PushDelegate(Delegate<void, int>* del)
{
	m_delegateVector.push_back(del);
}

bool UIButton::CheckMouseOverButton()
{
	POINT* mousePos = InputManager::Get()->GetMousePosition();
	LONG leftX = (LONG)m_pos.x;
	LONG rightX = (LONG)(m_pos.x + m_width);
	LONG bottomY = (LONG)m_pos.y;
	LONG topY = (LONG)(m_pos.y + m_height);

	LONG mouseX = mousePos->x;
	LONG mouseY = g_windowHeight - mousePos->y;
	
	if (mouseX <= leftX || mouseX >= rightX || mouseY <= bottomY || mouseY >= topY)
	{
		return false;
	}

	return true;
}

void UIButton::RegisterButtonWithInputManager()
{
	m_pLeftButtonDelegate = new Delegate<void, InputManager::LeftMouseButtonStatus>(this, &UIButton::OnPressed);
	InputManager::Get()->PushLeftMouseButtonDelegate(m_pLeftButtonDelegate);
}

