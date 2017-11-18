//=============================================================================
// AssetManager.h
//
// Asset manager class, will be used in this case for loading the textures
// used by the sprites and keeping them in a table so that if multiple sprites
// want the same texture it will be loaded into memory only once and the single
// reference will be shared between sprites using the texture
//=============================================================================

#ifndef ASSETMANAGER_H
#define ASSETMANAGER_H

#include "RenderManager.h"
#include "Microsoft_DirectXTex/DirectXTex-master/DDSTextureLoader/DDSTextureLoader.h" // for convenience using MS DirectXTex API for loading textures
using namespace DirectX;

#include <functional>
#include <map>
#include <string>
using namespace std;

class AssetManager
{
public:
	~AssetManager();

	static AssetManager* Get();

	HRESULT GetTextureFromFile(const wchar_t* filename, ID3D11ShaderResourceView** pSRV, ID3D11Resource** pTexture);

private:
	static AssetManager* m_pInstance;

	AssetManager();

	map<size_t, ID3D11Resource*> m_textureTable;
	map<size_t, ID3D11ShaderResourceView*> m_rvTable;
};

#endif // ASSETMANAGER_H
