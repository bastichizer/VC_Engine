//===============================================================
// InputManager.cpp
//===============================================================

#include "InputManager.h"

InputManager* InputManager::m_pInstance = NULL;

InputManager::InputManager()
{

}

InputManager::~InputManager()
{
	if (m_pInstance)
	{
		delete m_pInstance;
	}
}

InputManager* InputManager::Get()
{
	if (!m_pInstance)
	{
		m_pInstance = new InputManager();
	}
	return m_pInstance;
}

void InputManager::Init(HWND hwnd)
{
	m_pMousePos = new POINT;

	hWnd = hwnd;

	Rid[0].usUsagePage = HID_USAGE_PAGE_GENERIC;
	Rid[0].usUsage = HID_USAGE_GENERIC_MOUSE;
	Rid[0].dwFlags = RIDEV_INPUTSINK;
	Rid[0].hwndTarget = hWnd;
	RegisterRawInputDevices(Rid, 1, sizeof(Rid[0]));

	m_bLeftButtonIsDown = false;
	m_bLeftButtonWasDown = false;
	m_bLeftButtonIsUp = true;

	m_bMiddleButtonIsDown = false;
	m_bMiddleButtonWasDown = false;
	m_bMiddleButtonIsUp = true;

	m_bRightButtonIsDown = false;
	m_bRightButtonWasDown = false;
	m_bRightButtonIsUp = true;

	m_eLeftButtonStatus = LeftMouseButtonStatus::LB_Up;
	m_eMiddleButtonStatus = MiddleMouseButtonStatus::MB_Up;
	m_eRightButtonStatus = RightMouseButtonStatus::RB_Up;
}

void InputManager::ProcessRawInput(HRAWINPUT rawInput)
{
	UINT dwSize = sizeof(RAWINPUT);
	static BYTE lpb[sizeof(RAWINPUT)];

	GetRawInputData(rawInput, RID_INPUT, lpb, &dwSize, sizeof(RAWINPUTHEADER));

	RAWINPUT* raw = (RAWINPUT*)lpb;

	if (raw->header.dwType == RIM_TYPEMOUSE)
	{
		m_iMouseMoveX = raw->data.mouse.lLastX;
		m_iMouseMoveY = raw->data.mouse.lLastY;

		switch (m_eLeftButtonStatus)
		{
		case LeftMouseButtonStatus::LB_Up:
			if (raw->data.mouse.usButtonFlags == RI_MOUSE_LEFT_BUTTON_DOWN)
			{
				m_bLeftButtonIsDown = true;
				m_bLeftButtonIsUp = false;
				m_eLeftButtonStatus = LeftMouseButtonStatus::LB_Clicked;
				// send click event
				for (int i = 0; i < (int)m_leftMouseButtonDelegates.size(); ++i)
				{
					(*m_leftMouseButtonDelegates[i])(m_eLeftButtonStatus);
				}
			}
			break;

		case LeftMouseButtonStatus::LB_Clicked:
			if (raw->data.mouse.usButtonFlags != RI_MOUSE_LEFT_BUTTON_UP)
			{
				m_bLeftButtonWasDown = true;
				m_eLeftButtonStatus = LeftMouseButtonStatus::LB_Down;
			}
			else
			{
				m_bLeftButtonIsDown = false;
				m_bLeftButtonWasDown = true;
				m_bLeftButtonIsUp = true;
				m_eLeftButtonStatus = LeftMouseButtonStatus::LB_Released;
				// send release event
				for (int i = 0; i < (int)m_leftMouseButtonDelegates.size(); ++i)
				{
					(*m_leftMouseButtonDelegates[i])(m_eLeftButtonStatus);
				}
			}
			break;

		case LeftMouseButtonStatus::LB_Down:
			if (raw->data.mouse.usButtonFlags == RI_MOUSE_LEFT_BUTTON_UP)
			{
				m_bLeftButtonIsDown = false;
				m_bLeftButtonIsUp = true;
				m_eLeftButtonStatus = LeftMouseButtonStatus::LB_Released;
				// send release event
				for (int i = 0; i < (int)m_leftMouseButtonDelegates.size(); ++i)
				{
					(*m_leftMouseButtonDelegates[i])(m_eLeftButtonStatus);
				}
			}
			break;

		case LeftMouseButtonStatus::LB_Released:
			if (raw->data.mouse.usButtonFlags != RI_MOUSE_LEFT_BUTTON_DOWN)
			{
				m_bLeftButtonWasDown = false;
				m_eLeftButtonStatus = LeftMouseButtonStatus::LB_Up;
			}
			else
			{
				m_bLeftButtonIsDown = true;
				m_bLeftButtonWasDown = false;
				m_bLeftButtonIsUp = false;
				m_eLeftButtonStatus = LeftMouseButtonStatus::LB_Clicked;
				// send click event
				for (int i = 0; i < (int)m_leftMouseButtonDelegates.size(); ++i)
				{
					(*m_leftMouseButtonDelegates[i])(m_eLeftButtonStatus);
				}
			}
			break;
		}

		switch (m_eMiddleButtonStatus)
		{
		case MiddleMouseButtonStatus::MB_Up:
			if (raw->data.mouse.usButtonFlags == RI_MOUSE_MIDDLE_BUTTON_DOWN)
			{
				m_bMiddleButtonIsDown = true;
				m_bMiddleButtonIsUp = false;
				m_eMiddleButtonStatus = MiddleMouseButtonStatus::MB_Clicked;
				// send click event
				for (int i = 0; i < (int)m_middleMouseButtonDelegates.size(); ++i)
				{
					(*m_middleMouseButtonDelegates[i])(m_eMiddleButtonStatus);
				}
			}
			break;

		case MiddleMouseButtonStatus::MB_Clicked:
			if (raw->data.mouse.usButtonFlags != RI_MOUSE_MIDDLE_BUTTON_UP)
			{
				m_bMiddleButtonWasDown = true;
				m_eMiddleButtonStatus = MiddleMouseButtonStatus::MB_Down;
			}
			else
			{
				m_bMiddleButtonIsDown = false;
				m_bMiddleButtonWasDown = true;
				m_bMiddleButtonIsUp = true;
				m_eMiddleButtonStatus = MiddleMouseButtonStatus::MB_Released;
				// send release event
				for (int i = 0; i < (int)m_middleMouseButtonDelegates.size(); ++i)
				{
					(*m_middleMouseButtonDelegates[i])(m_eMiddleButtonStatus);
				}
			}
			break;

		case MiddleMouseButtonStatus::MB_Down:
			if (raw->data.mouse.usButtonFlags == RI_MOUSE_MIDDLE_BUTTON_UP)
			{
				m_bMiddleButtonIsDown = false;
				m_bMiddleButtonIsUp = true;
				m_eMiddleButtonStatus = MiddleMouseButtonStatus::MB_Released;
				// send release event
				for (int i = 0; i < (int)m_middleMouseButtonDelegates.size(); ++i)
				{
					(*m_middleMouseButtonDelegates[i])(m_eMiddleButtonStatus);
				}
			}
			break;

		case MiddleMouseButtonStatus::MB_Released:
			if (raw->data.mouse.usButtonFlags != RI_MOUSE_MIDDLE_BUTTON_DOWN)
			{
				m_bMiddleButtonWasDown = false;
				m_eMiddleButtonStatus = MiddleMouseButtonStatus::MB_Up;
			}
			else
			{
				m_bMiddleButtonIsDown = true;
				m_bMiddleButtonWasDown = false;
				m_bMiddleButtonIsUp = false;
				m_eMiddleButtonStatus = MiddleMouseButtonStatus::MB_Clicked;
				// send click event
				for (int i = 0; i < (int)m_middleMouseButtonDelegates.size(); ++i)
				{
					(*m_middleMouseButtonDelegates[i])(m_eMiddleButtonStatus);
				}
			}
			break;
		}

		switch (m_eRightButtonStatus)
		{
		case RightMouseButtonStatus::RB_Up:
			if (raw->data.mouse.usButtonFlags == RI_MOUSE_RIGHT_BUTTON_DOWN)
			{
				m_bRightButtonIsDown = true;
				m_bRightButtonIsUp = false;
				m_eRightButtonStatus = RightMouseButtonStatus::RB_Clicked;
				// send click event
				for (int i = 0; i < (int)m_rightMouseButtonDelegates.size(); ++i)
				{
					(*m_rightMouseButtonDelegates[i])(m_eRightButtonStatus);
				}
			}
			break;

		case RightMouseButtonStatus::RB_Clicked:
			if (raw->data.mouse.usButtonFlags != RI_MOUSE_RIGHT_BUTTON_UP)
			{
				m_bRightButtonWasDown = true;
				m_eRightButtonStatus = RightMouseButtonStatus::RB_Down;
			}
			else
			{
				m_bRightButtonIsDown = false;
				m_bRightButtonWasDown = true;
				m_bRightButtonIsUp = true;
				m_eRightButtonStatus = RightMouseButtonStatus::RB_Released;
				// send release event
				for (int i = 0; i < (int)m_rightMouseButtonDelegates.size(); ++i)
				{
					(*m_rightMouseButtonDelegates[i])(m_eRightButtonStatus);
				}
			}
			break;

		case RightMouseButtonStatus::RB_Down:
			if (raw->data.mouse.usButtonFlags == RI_MOUSE_RIGHT_BUTTON_UP)
			{
				m_bRightButtonIsDown = false;
				m_bRightButtonIsUp = true;
				m_eRightButtonStatus = RightMouseButtonStatus::RB_Released;
				// send release event
				for (int i = 0; i < (int)m_rightMouseButtonDelegates.size(); ++i)
				{
					(*m_rightMouseButtonDelegates[i])(m_eRightButtonStatus);
				}
			}
			break;

		case RightMouseButtonStatus::RB_Released:
			if (raw->data.mouse.usButtonFlags != RI_MOUSE_RIGHT_BUTTON_DOWN)
			{
				m_bRightButtonWasDown = false;
				m_eRightButtonStatus = RightMouseButtonStatus::RB_Up;
			}
			else
			{
				m_bRightButtonIsDown = true;
				m_bRightButtonWasDown = false;
				m_bRightButtonIsUp = false;
				m_eRightButtonStatus = RightMouseButtonStatus::RB_Clicked;
				// send click event
				for (int i = 0; i < (int)m_rightMouseButtonDelegates.size(); ++i)
				{
					(*m_rightMouseButtonDelegates[i])(m_eRightButtonStatus);
				}
			}
			break;
		}
	}
}

void InputManager::ProcessMousePos()
{
	if (GetCursorPos(m_pMousePos))
	{
		if (!ScreenToClient(hWnd, m_pMousePos))
		{
			//QE::ErrorExit(L"QInput::ProcessMousePos()");
		}
	}
	else
	{
		//QE::ErrorExit(L"QInput::ProcessMousePos()");
	}
}

InputManager::LeftMouseButtonStatus InputManager::GetLeftMouseButton()
{
	return m_eLeftButtonStatus;
}

InputManager::MiddleMouseButtonStatus InputManager::GetMiddleMouseButton()
{
	return m_eMiddleButtonStatus;
}

InputManager::RightMouseButtonStatus InputManager::GetRightMouseButton()
{
	return m_eRightButtonStatus;
}

void InputManager::GetMouseMove(int &mouseX, int &mouseY)
{
	mouseX = m_iMouseMoveX;
	mouseY = m_iMouseMoveY;
}

LPPOINT InputManager::GetMousePosition()
{
	ProcessMousePos();
	return m_pMousePos;
}

void InputManager::PushLeftMouseButtonDelegate(Delegate<void, LeftMouseButtonStatus>* del)
{
	m_leftMouseButtonDelegates.push_back(del);
}

void InputManager::PushMiddleMouseButtonDelegate(Delegate<void, MiddleMouseButtonStatus>* del)
{
	m_middleMouseButtonDelegates.push_back(del);
}

void InputManager::PushRightMouseButtonDelegate(Delegate<void, RightMouseButtonStatus>* del)
{
	m_rightMouseButtonDelegates.push_back(del);
}

