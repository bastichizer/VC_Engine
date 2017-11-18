//=======================================================================
// Sprite.cpp
//=======================================================================

#include "Sprite.h"
#include "AssetManager.h"
#include <d3dcompiler.h>
#include "Quasar\QMaths.h"

ID3D11PixelShader* Sprite::m_pPS = NULL;
ID3D11VertexShader* Sprite::m_pVS = NULL;
ID3D11InputLayout* Sprite::m_pVertexLayout = NULL;
ID3D11SamplerState* Sprite::m_pSamplerState = NULL;

Sprite::Sprite(int width, int height, int posX, int posY) :
m_pVertexBuffer(NULL),
m_pSpriteTexture(NULL),
m_pSpriteConstantBuffer(NULL),
m_width(width),
m_height(height),
m_scale(XMFLOAT2(1.0f, 1.0f))
{
	m_pos = XMINT2(posX, posY);
}

Sprite::~Sprite()
{
	if (m_pVertexBuffer)
	{
		m_pVertexBuffer->Release();
	}
	if (m_pSpriteTexture)
	{
		m_pSpriteTexture->Release();
	}
	if (m_pSpriteConstantBuffer)
	{
		m_pSpriteConstantBuffer->Release();
	}
}

// Cleans up the static variables
void Sprite::Cleanup()
{
	if (m_pVertexLayout)
	{
		m_pVertexLayout->Release();
		m_pVertexLayout = NULL;
	}
	if (m_pVS)
	{
		m_pVS->Release();
		m_pVS = NULL;
	}
	if (m_pPS)
	{
		m_pPS->Release();
		m_pPS = NULL;
	}
	if (m_pSamplerState)
	{
		m_pSamplerState->Release();
		m_pSamplerState = NULL;
	}
}

void Sprite::Init(WCHAR* texturePath)
{
	// Vertex buffer and shader setup
	D3D11_INPUT_ELEMENT_DESC vertLayout[] =
	{
		{"POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0},
		{"TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0},
	};
	UINT numElements = ARRAYSIZE(vertLayout);

	ID3DBlob* pVSBlob = NULL;
	if (!m_pVS)
	{
		if (FAILED(CompileShaderFromFile(L"Shaders\\SpriteShader.hlsl", "VS", "vs_5_0", &pVSBlob)))
		{
			// error message here
			return;
		}
		if (FAILED(RenderManager::Get()->GetDevice()->CreateVertexShader(pVSBlob->GetBufferPointer(), pVSBlob->GetBufferSize(), NULL, &m_pVS)))
		{
			// error message here
			return;
		}
	}
	ID3DBlob* pPSBlob = NULL;
	if (!m_pPS)
	{
		if (FAILED(CompileShaderFromFile(L"Shaders\\SpriteShader.hlsl", "PS", "ps_5_0", &pPSBlob)))
		{
			// error message here
			return;
		}
		if (FAILED(RenderManager::Get()->GetDevice()->CreatePixelShader(pPSBlob->GetBufferPointer(), pPSBlob->GetBufferSize(), NULL, &m_pPS)))
		{
			// error message here
			return;
		}
		pPSBlob->Release();
	}
	if (!m_pVertexLayout)
	{
		if (FAILED(RenderManager::Get()->GetDevice()->CreateInputLayout(vertLayout, numElements, pVSBlob->GetBufferPointer(), pVSBlob->GetBufferSize(), &m_pVertexLayout)))
		{
			// error message here
			return;
		}
		RenderManager::Get()->GetContext()->IASetInputLayout(m_pVertexLayout);
		pVSBlob->Release();
	}

	Vertex vertices[] = 
	{
		{
			XMFLOAT3((float)m_width, (float)m_height, 1.0f),
			XMFLOAT2(1.0f, 0.0f)
		},
		{
			XMFLOAT3((float)m_width, 0.0f, 1.0f),
			XMFLOAT2(1.0f, 1.0f)
		},
		{
			XMFLOAT3(0.0f, (float)m_height, 1.0f),
			XMFLOAT2(0.0f, 0.0f)
		},
		{
			XMFLOAT3(0.0f, 0.0f, 1.0f),
			XMFLOAT2(0.0f, 1.0f)
		},		
	};
	D3D11_BUFFER_DESC bd;
	ZeroMemory(&bd, sizeof(bd));
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.ByteWidth = sizeof(Vertex) * 4;
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bd.CPUAccessFlags = 0;
	bd.MiscFlags = 0;
	D3D11_SUBRESOURCE_DATA initData;
	ZeroMemory(&initData, sizeof(initData));
	initData.pSysMem = vertices;
	if (FAILED(RenderManager::Get()->GetDevice()->CreateBuffer(&bd, &initData, &m_pVertexBuffer)))
	{
		// error message here
		return;
	}

	// Texture setup
	if (FAILED(AssetManager::Get()->GetTextureFromFile(texturePath, &m_pSpriteShaderResourceView, &m_pSpriteTexture)))
	{
		// error message here
		return;
	}

	if (!m_pSamplerState)
	{
		D3D11_SAMPLER_DESC samplerDesc;
		ZeroMemory(&samplerDesc, sizeof(samplerDesc));
		samplerDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
		samplerDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
		samplerDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
		samplerDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
		samplerDesc.ComparisonFunc = D3D11_COMPARISON_ALWAYS;
		samplerDesc.MinLOD = 0;
		samplerDesc.MaxLOD = D3D11_FLOAT32_MAX;
		if (FAILED(RenderManager::Get()->GetDevice()->CreateSamplerState(&samplerDesc, &m_pSamplerState)))
		{
			// error message here
			return;
		}
	}

	// Constant buffer setup
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.ByteWidth = sizeof(CB);
	bd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	bd.CPUAccessFlags = 0;
	bd.MiscFlags = 0;
	if (FAILED(RenderManager::Get()->GetDevice()->CreateBuffer(&bd, NULL, &m_pSpriteConstantBuffer)))
	{
		// error message here
		return;
	}

	m_spriteConstants.brightness = 1.0f;
}

void Sprite::Render(Camera* cam)
{
	RenderManager::Get()->GetContext()->VSSetShader(m_pVS, NULL, 0);
	RenderManager::Get()->GetContext()->PSSetShader(m_pPS, NULL, 0);
	RenderManager::Get()->GetContext()->PSSetShaderResources(0, 1, &m_pSpriteShaderResourceView);
	RenderManager::Get()->GetContext()->PSGetSamplers(0, 1, &m_pSamplerState);

	/*XMMATRIX mat;
	mat.r[0].m128_f32[0] = m_scale.x;		mat.r[1].m128_f32[0] = 0.0f;			mat.r[2].m128_f32[0] = 0.0f;			mat.r[3].m128_f32[0] = (float)m_pos.x;
	mat.r[0].m128_f32[1] = 0.0f;			mat.r[1].m128_f32[1] = m_scale.y;		mat.r[2].m128_f32[1] = 0.0f;			mat.r[3].m128_f32[1] = (float)m_pos.y;
	mat.r[0].m128_f32[2] = 0.0f;			mat.r[1].m128_f32[2] = 0.0f;			mat.r[2].m128_f32[2] = 1.0f;			mat.r[3].m128_f32[2] = 0.0f;
	mat.r[0].m128_f32[3] = 0.0f;			mat.r[1].m128_f32[3] = 0.0f;			mat.r[2].m128_f32[3] = 0.0f;			mat.r[3].m128_f32[3] = 1.0f;*/	

	QE::Matrix4f mat;
	mat.m11 = m_scale.x;		mat.m12 = 0.0f;				mat.m13 = 0.0f;		mat.m14 = 0.0f;
	mat.m21 = 0.0f;				mat.m22 = m_scale.y;		mat.m23 = 0.0f;		mat.m24 = 0.0f;
	mat.m31 = 0.0f;				mat.m32 = 0.0f;				mat.m33 = 1.0f;		mat.m34 = 0.0f;
	mat.m41 = (float)m_pos.x;	mat.m42 = (float)m_pos.y;	mat.m43 = 0.0f;		mat.m44 = 1.0f;

	
	QE::Matrix4f viewProj = cam->GetViewProjMatrix();
	QE::Matrix4f worldViewProj = QE::Matrix4f::Multiply(mat, viewProj);
	m_spriteConstants.matWorldViewProj.r[0].m128_f32[0] = worldViewProj.m11;
	m_spriteConstants.matWorldViewProj.r[0].m128_f32[1] = worldViewProj.m12;
	m_spriteConstants.matWorldViewProj.r[0].m128_f32[2] = worldViewProj.m13;
	m_spriteConstants.matWorldViewProj.r[0].m128_f32[3] = worldViewProj.m14;

	m_spriteConstants.matWorldViewProj.r[1].m128_f32[0] = worldViewProj.m21;
	m_spriteConstants.matWorldViewProj.r[1].m128_f32[1] = worldViewProj.m22;
	m_spriteConstants.matWorldViewProj.r[1].m128_f32[2] = worldViewProj.m23;
	m_spriteConstants.matWorldViewProj.r[1].m128_f32[3] = worldViewProj.m24;

	m_spriteConstants.matWorldViewProj.r[2].m128_f32[0] = worldViewProj.m31;
	m_spriteConstants.matWorldViewProj.r[2].m128_f32[1] = worldViewProj.m32;
	m_spriteConstants.matWorldViewProj.r[2].m128_f32[2] = worldViewProj.m33;
	m_spriteConstants.matWorldViewProj.r[2].m128_f32[3] = worldViewProj.m34;

	m_spriteConstants.matWorldViewProj.r[3].m128_f32[0] = worldViewProj.m41;
	m_spriteConstants.matWorldViewProj.r[3].m128_f32[1] = worldViewProj.m42;
	m_spriteConstants.matWorldViewProj.r[3].m128_f32[2] = worldViewProj.m43;
	m_spriteConstants.matWorldViewProj.r[3].m128_f32[3] = worldViewProj.m44;

	RenderManager::Get()->GetContext()->UpdateSubresource(m_pSpriteConstantBuffer, 0, NULL, &m_spriteConstants, 0, 0);
	RenderManager::Get()->GetContext()->VSSetConstantBuffers(0, 1, &m_pSpriteConstantBuffer);
	RenderManager::Get()->GetContext()->PSSetConstantBuffers(0, 1, &m_pSpriteConstantBuffer);

	UINT stride = sizeof(Vertex);
	UINT offset = 0;
	RenderManager::Get()->GetContext()->IASetVertexBuffers(0, 1, &m_pVertexBuffer, &stride, &offset);
	RenderManager::Get()->GetContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);
	
	RenderManager::Get()->GetContext()->Draw(6, 0);
}

// shader compile function lifted from d3d samples
HRESULT Sprite::CompileShaderFromFile(WCHAR* fileName, LPCSTR entryPoint, LPCSTR shaderModel, ID3DBlob** ppBlobOut)
{
	HRESULT hr = S_OK;

	DWORD dwShaderFlags = D3DCOMPILE_ENABLE_STRICTNESS;
#ifdef _DEBUG
	// Set the D3DCOMPILE_DEBUG flag to embed debug information in the shaders.
	// Setting this flag improves the shader debugging experience, but still allows 
	// the shaders to be optimized and to run exactly the way they will run in 
	// the release configuration of this program.
	dwShaderFlags |= D3DCOMPILE_DEBUG;

	// Disable optimizations to further improve shader debugging
	dwShaderFlags |= D3DCOMPILE_SKIP_OPTIMIZATION;
#endif

	ID3DBlob* pErrorBlob = nullptr;
	hr = D3DCompileFromFile(fileName, nullptr, nullptr, entryPoint, shaderModel,
		dwShaderFlags, 0, ppBlobOut, &pErrorBlob);
	if (FAILED(hr))
	{
		if (pErrorBlob)
		{
			OutputDebugStringA(reinterpret_cast<const char*>(pErrorBlob->GetBufferPointer()));
			pErrorBlob->Release();
		}
		return hr;
	}
	if (pErrorBlob) pErrorBlob->Release();

	return S_OK;
}

