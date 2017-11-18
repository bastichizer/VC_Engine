//===========================================================================
// AssetManager.cpp
//===========================================================================

#include "AssetManager.h"

AssetManager* AssetManager::m_pInstance = NULL;

AssetManager::AssetManager()
{

}

AssetManager::~AssetManager()
{
	for (map<size_t, ID3D11Resource*>::iterator it = m_textureTable.begin(); it != m_textureTable.end(); ++it)
	{
		it->second->Release();
	}
	for (map<size_t, ID3D11ShaderResourceView*>::iterator it = m_rvTable.begin(); it != m_rvTable.end(); ++it)
	{
		it->second->Release();
	}

	if (m_pInstance)
	{
		delete m_pInstance;
	}
}

AssetManager* AssetManager::Get()
{
	if (!m_pInstance)
	{
		m_pInstance = new AssetManager();
	}
	return m_pInstance;
}

HRESULT AssetManager::GetTextureFromFile(const wchar_t* filename, ID3D11ShaderResourceView** pSRV, ID3D11Resource** pTexture)
{
	HRESULT hr = S_OK;
	wstring temp(filename);
	string path(temp.begin(), temp.end());
	hash<string> pathHash;
	size_t key = pathHash(path);
	if (m_textureTable.count(key) == 0)
	{
		hr = CreateDDSTextureFromFile(RenderManager::Get()->GetDevice(), filename, pTexture, pSRV);
		m_textureTable[key] = *pTexture;
		m_rvTable[key] = *pSRV;
	}
	else
	{
		*pTexture = m_textureTable[key];
		*pSRV = m_rvTable[key];
	}

	return hr;
}

