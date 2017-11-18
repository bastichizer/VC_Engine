//==========================================================================
// GameMap.h
//==========================================================================

#ifndef GAMEMAP_H
#define GAMEMAP_H

#include "Sprite.h"

__declspec(align(16)) class GameMap : public Sprite
{
public:
	GameMap(int sizeX, int sizeY, int posX, int posY, WCHAR* texturePath);
	~GameMap();

	// ensure 16 byte alignment for D3D XMMATRIX 
	void* operator new(size_t i) { return _aligned_malloc(i, 16); }
	void operator delete(void* p) { _aligned_free(p); }

	virtual void Render(Camera* cam);
	void ZoomIn();
	void ZoomOut();

private:
	float m_currentScale;
};

#endif // GAMEMAP_H

