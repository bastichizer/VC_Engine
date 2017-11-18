//======================================================================
// RenderManager.h
// 
// Render manager, singleton class, holds the D3D device, context and 
// swap chain as well as keeping track of render state settings
//======================================================================

#ifndef RENDERMANAGER_H
#define RENDERMANAGER_H

#include <d3d11.h>

class RenderManager
{
public:
	~RenderManager();

	static RenderManager* Get();

	HRESULT InitDevice(HWND hWnd);

	void Cleanup();

	void Begin();
	void End();
	void Render();
	void RenderForeground();
	void RenderBackground();
	void RenderPostFX();
	void RenderUI();

	void SetClearColor(float r, float g, float b, float a);

	ID3D11Device* GetDevice() { return m_pDevice; }
	ID3D11DeviceContext* GetContext() { return m_pContext; }

	void SetBlendState();

private:
	RenderManager();
	static RenderManager* m_pInstance;

	// d3d device
	ID3D11Device* m_pDevice;
	// swapchain
	IDXGISwapChain* m_pSwapChain;
	// context
	ID3D11DeviceContext* m_pContext;
	// render target view
	ID3D11RenderTargetView* m_pRenderTargetView;

	const D3D_FEATURE_LEVEL m_featureLevels[1] = { D3D_FEATURE_LEVEL_11_0 };

	float m_clearColor[4];
};

#endif // RENDERMANAGER_H
