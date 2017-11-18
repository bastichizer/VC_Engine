//===============================================================
// InputManager.h
//===============================================================

#ifndef INPUTMANAGER_H
#define INPUTMANAGER_H

#include "Delegate.h"
#include <Windows.h>
#include <vector>
using namespace std;

#ifndef HID_USAGE_PAGE_GENERIC
#define HID_USAGE_PAGE_GENERIC         ((USHORT) 0x01)
#endif
#ifndef HID_USAGE_GENERIC_MOUSE
#define HID_USAGE_GENERIC_MOUSE        ((USHORT) 0x02)
#endif

class InputManager
{
public:
	~InputManager();

	static InputManager* Get();

	void Init(HWND hwnd);

	void ProcessRawInput(HRAWINPUT rawInput);
	void ProcessMousePos();

	enum LeftMouseButtonStatus
	{
		LB_Up,
		LB_Clicked,
		LB_Down,
		LB_Released,
	};

	enum MiddleMouseButtonStatus
	{
		MB_Up,
		MB_Clicked,
		MB_Down,
		MB_Released,
	};

	enum RightMouseButtonStatus
	{
		RB_Up,
		RB_Clicked,
		RB_Down,
		RB_Released,
	};

	LeftMouseButtonStatus GetLeftMouseButton();
	MiddleMouseButtonStatus GetMiddleMouseButton();
	RightMouseButtonStatus GetRightMouseButton();
	void GetMouseMove(int &mouseX, int &mouseY);
	LPPOINT GetMousePosition();
	void PushLeftMouseButtonDelegate(Delegate<void, LeftMouseButtonStatus>* del);
	void PushMiddleMouseButtonDelegate(Delegate<void, MiddleMouseButtonStatus>* del);
	void PushRightMouseButtonDelegate(Delegate<void, RightMouseButtonStatus>* del);

private:
	InputManager();

	static InputManager* m_pInstance;

	RAWINPUTDEVICE Rid[1];
	HWND hWnd;

	int m_iMouseMoveX;
	int m_iMouseMoveY;
	POINT* m_pMousePos;

	bool m_bLeftButtonIsDown;
	bool m_bLeftButtonWasDown;
	bool m_bLeftButtonIsUp;

	bool m_bMiddleButtonIsDown;
	bool m_bMiddleButtonWasDown;
	bool m_bMiddleButtonIsUp;

	bool m_bRightButtonIsDown;
	bool m_bRightButtonWasDown;
	bool m_bRightButtonIsUp;

	LeftMouseButtonStatus m_eLeftButtonStatus;
	MiddleMouseButtonStatus m_eMiddleButtonStatus;
	RightMouseButtonStatus m_eRightButtonStatus;

	vector<Delegate<void, LeftMouseButtonStatus>*> m_leftMouseButtonDelegates;
	vector<Delegate<void, MiddleMouseButtonStatus>*> m_middleMouseButtonDelegates;
	vector<Delegate<void, RightMouseButtonStatus>*> m_rightMouseButtonDelegates;
};

#endif // INPUTMANAGER_H
