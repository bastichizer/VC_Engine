//=========================================================================
// Sprite.h
//
// Sprite class, base class for rendering all game elements. This class 
// will contain all the items needed to render a sprite on screen including
// vertex buffer, resource view and shader references. In a full engine I 
// would put these things into separate classes for better flexibility but
// for the purposes of this test it's easier to have them all together here
//=========================================================================

#ifndef SPRITE_H
#define SPRITE_H

#include "RenderManager.h"
#include "Camera.h"
#include <DirectXMath.h>
using namespace DirectX;

class UIManager;

struct Vertex
{
	XMFLOAT3 pos;
	XMFLOAT2 uv;
};

__declspec(align(16)) class Sprite
{
public:
	Sprite(int width, int height, int posX, int posY, UIManager* uiManager);
	virtual ~Sprite();

	// ensure 16 byte alignment for D3D XMMATRIX 
	void* operator new(size_t i) { return _aligned_malloc(i, 16); }
	void operator delete(void* p) { _aligned_free(p); }

	void Init(WCHAR* texturePath);

	virtual void Render(Camera* cam);

	// making the shader, vertex layout and sampler state references static, since we are using a common shader for all sprites so only want them created once
	static ID3D11VertexShader* m_pVS;
	static ID3D11PixelShader* m_pPS;
	static ID3D11InputLayout* m_pVertexLayout;
	static ID3D11SamplerState* m_pSamplerState;

	static void Cleanup();

	HRESULT CompileShaderFromFile(WCHAR* fileName, LPCSTR entryPoint, LPCSTR shaderModel, ID3DBlob** ppBlobOut);

	void SetBrightness(float val) { m_spriteConstants.brightness = val; }
	void SetScale(float val) { m_scale.x = m_scale.y = val; }
	void SetScale(float valX, float valY) { m_scale.x = valX; m_scale.y = valY; }

protected:
	ID3D11Buffer* m_pVertexBuffer;
	ID3D11Resource* m_pSpriteTexture;
	ID3D11ShaderResourceView* m_pSpriteShaderResourceView;
	ID3D11Buffer* m_pSpriteConstantBuffer;

	UIManager* m_pUIManager;

	struct CB
	{
		XMMATRIX matWorldViewProj;
		float brightness;
	};
	CB m_spriteConstants;

	int m_width;
	int m_height;
	XMINT2 m_pos;
	XMFLOAT2 m_scale;
};

#endif // SPRITE_H

