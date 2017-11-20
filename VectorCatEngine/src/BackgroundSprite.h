#ifndef BACKGROUNDSPRITE_H
#define BACKGROUNDSPRITE_H

#include "Sprite.h"
#include "Quasar\QMaths.h"

class BackgroundSprite : public Sprite
{
public:
	BackgroundSprite(int width, int height, int posX, int posY, WCHAR* texturePath, UIManager* uiManager);
	virtual ~BackgroundSprite();

	void SetScrollX(bool v) { m_bScrollX = v; }
	void SetScrollY(bool v) { m_bScrollY = v; }
	void SetVel(QE::Vector2f v) { m_vel = v; }

	void Render(Camera* cam) override;

	// ensure 16 byte alignment for D3D XMMATRIX 
	void* operator new(size_t i) { return _aligned_malloc(i, 16); }
	void operator delete(void* p) { _aligned_free(p); }

private:
	bool m_bScrollX;
	bool m_bScrollY;

	QE::Vector2f m_vel;
};

#endif // BACKGROUNDSPRITE_H
