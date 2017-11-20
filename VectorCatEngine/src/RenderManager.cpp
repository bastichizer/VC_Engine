//==============================================================
// RenderManager.cpp
//==============================================================

#include "RenderManager.h"

RenderManager* RenderManager::m_pInstance = NULL;

RenderManager::RenderManager() :
	m_pDevice(NULL),
	m_pSwapChain(NULL),
	m_pContext(NULL),
	m_pRenderTargetView(NULL),
	m_pPSSamplerState(NULL)
{
	SetClearColor(0.05f, 0.05f, 0.05f, 1.0f);
}

RenderManager::~RenderManager()
{
	if (m_pInstance)
	{
		delete m_pInstance;
	}
}

RenderManager* RenderManager::Get()
{
	if (!m_pInstance)
	{
		m_pInstance = new RenderManager();
	}
	return m_pInstance;
}

void RenderManager::Cleanup()
{
	if (m_pRenderTargetView)
	{
		m_pRenderTargetView->Release();
		m_pRenderTargetView = NULL;
	}

	if (m_pSwapChain)
	{
		m_pSwapChain->Release();
		m_pSwapChain = NULL;
	}

	if (m_pPSSamplerState)
	{
		m_pPSSamplerState->Release();
		m_pPSSamplerState = NULL;
	}

	if (m_pContext)
	{
		m_pContext->Release();
		m_pContext = NULL;
	}

	if (m_pDevice)
	{
		m_pDevice->Release();
		m_pDevice = NULL;
	}
}

HRESULT RenderManager::InitDevice(HWND hWnd)
{
	DXGI_SWAP_CHAIN_DESC swapChainDesc;
	ZeroMemory(&swapChainDesc, sizeof(swapChainDesc));
	swapChainDesc.BufferCount = 1;
	swapChainDesc.BufferDesc.Width = 1280;
	swapChainDesc.BufferDesc.Height = 720;
	swapChainDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	swapChainDesc.BufferDesc.RefreshRate.Numerator = 60;
	swapChainDesc.BufferDesc.RefreshRate.Denominator = 1;
	swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	swapChainDesc.OutputWindow = hWnd;
	swapChainDesc.SampleDesc.Count = 1;
	swapChainDesc.SampleDesc.Quality = 0;
	swapChainDesc.Windowed = TRUE;

	UINT flags = 0;
#ifdef _DEBUG
	flags |= D3D11_CREATE_DEVICE_DEBUG;
#endif

	HRESULT hr = D3D11CreateDeviceAndSwapChain(NULL, D3D_DRIVER_TYPE_HARDWARE, NULL, flags, m_featureLevels, 1, D3D11_SDK_VERSION, &swapChainDesc, &m_pSwapChain, &m_pDevice, NULL, &m_pContext);
	if (FAILED(hr))
	{
		return hr;
	}

	ID3D11Texture2D* pBackBuffer;
	hr = m_pSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&pBackBuffer);
	if (FAILED(hr))
	{
		return hr;
	}
	hr = m_pDevice->CreateRenderTargetView(pBackBuffer, NULL, &m_pRenderTargetView);
	pBackBuffer->Release();
	if (FAILED(hr))
	{
		return hr;
	}
	m_pContext->OMSetRenderTargets(1, &m_pRenderTargetView, NULL);

	D3D11_VIEWPORT viewport;
	viewport.Width = 1280.0f;
	viewport.Height = 720.0f;
	viewport.MinDepth = 0.0f;
	viewport.MaxDepth = 1.0f;
	viewport.TopLeftX = 0.0f;
	viewport.TopLeftY = 0.0f;
	m_pContext->RSSetViewports(1, &viewport);

	D3D11_SAMPLER_DESC desc;
	ZeroMemory(&desc, sizeof(D3D11_SAMPLER_DESC));
	desc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
	desc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
	desc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
	desc.Filter = D3D11_FILTER_MIN_MAG_MIP_POINT;
	desc.MaxLOD = 0;
	desc.MinLOD = 0;
	desc.MipLODBias = 0;
	hr = m_pDevice->CreateSamplerState(&desc, &m_pPSSamplerState);

	return hr;
}

void RenderManager::Begin()
{
	m_pContext->ClearRenderTargetView(m_pRenderTargetView, m_clearColor);

	m_pContext->PSSetSamplers(0, 1, &m_pPSSamplerState);
	SetBlendState();
}

void RenderManager::End()
{
	m_pSwapChain->Present(0, 0);
}

void RenderManager::Render()
{

}

void RenderManager::RenderBackground()
{

}

void RenderManager::RenderForeground()
{

}

void RenderManager::RenderPostFX()
{

}

void RenderManager::RenderUI()
{

}

void RenderManager::SetClearColor(float r, float g, float b, float a)
{
	m_clearColor[0] = r;
	m_clearColor[1] = g;
	m_clearColor[2] = b;
	m_clearColor[3] = a;
}

void RenderManager::SetBlendState()
{
	D3D11_RENDER_TARGET_BLEND_DESC rtbd;
	rtbd.BlendEnable = TRUE;
	rtbd.DestBlend = D3D11_BLEND_INV_SRC_ALPHA;
	rtbd.SrcBlend = D3D11_BLEND_SRC_ALPHA;
	rtbd.BlendOp = D3D11_BLEND_OP_ADD;
	rtbd.SrcBlendAlpha = D3D11_BLEND_ONE;
	rtbd.DestBlendAlpha = D3D11_BLEND_ZERO;
	rtbd.BlendOpAlpha = D3D11_BLEND_OP_ADD;
	rtbd.RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;

	//D3D11_RENDER_TARGET_BLEND_DESC descArray[8] = { rtbd, rtbd, rtbd, rtbd, rtbd, rtbd, rtbd, rtbd };

	D3D11_BLEND_DESC bd;
	bd.AlphaToCoverageEnable = FALSE;
	bd.IndependentBlendEnable = TRUE;
	for (int i = 0; i < 8; ++i)
	{
		bd.RenderTarget[i] = rtbd;
	}

	ID3D11BlendState* pBlendState = NULL;
	m_pDevice->CreateBlendState(&bd, &pBlendState);
	m_pContext->OMSetBlendState(pBlendState, NULL, 0xffffffff);
}

