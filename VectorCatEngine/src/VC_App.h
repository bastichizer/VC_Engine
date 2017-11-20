#ifndef VC_APP_H
#define VC_APP_H

#include <string>
#include "Quasar\QMaths.h"
#include "global.h"

class GameManager;

class VC_App
{
public:
	VC_App();
	virtual ~VC_App();

	virtual void Init();
	virtual void Update();
	virtual void Render();
	virtual void Shutdown();

	uint32 GetGameTime() { return m_currentTime; }
	uint32 GetTick() { return m_tick; }

protected:
	std::string m_appName;
	std::string m_windowTitle;

	QE::Vector2T<int> m_screenSize;

	bool m_bIsStartFrame;
	uint32 m_prevTime;
	uint32 m_currentTime;
	uint32 m_tick;

	GameManager* m_pGameManager;

private:
};

#endif // VC_APP_H
