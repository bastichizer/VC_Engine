//================================================================
// OverlayGrid.h
//================================================================

#ifndef OVERLAYGRID_H
#define OVERLAYGRID_H

#include "Sprite.h"
using namespace std;

__declspec(align(16)) class OverlayGrid : public Sprite
{
public:
	OverlayGrid(int width, int height, int posX, int posY, int offsetX, int offsetY, int gridSideLength, int gridCenterX, int gridCenterY, WCHAR* filename, UIManager* uiManager);
	~OverlayGrid();

	// ensure 16 byte alignment for D3D XMMATRIX 
	void* operator new(size_t i) { return _aligned_malloc(i, 16); }
	void operator delete(void* p) { _aligned_free(p); }

	virtual void Render(Camera* cam);
	void ToggleOverlayGridActive() { m_displayGrid = !m_displayGrid; }
	void ZoomIn();
	void ZoomOut();

private:
	bool m_displayGrid;

	// Grid square placement variables
	int m_offsetX;
	int m_offsetY;
	int m_gridSideLength;
	XMINT2 m_gridCenter;

	float m_currentScale;
};

#endif //OVERLAYGRID_H

