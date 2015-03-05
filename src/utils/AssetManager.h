#ifndef _ASSETMANAGER_H_
#define _ASSETMANAGER_H_

#include "TextureAtlas.h"
#include <vector>

using namespace std;

class AssetManager
{
public:
	static const char* ID;

private:
	class AtlasItem
	{
	public:
		const char* m_Name;
		TextureAtlas&		m_Atlas;

	public:
		explicit AtlasItem(const char* name, TextureAtlas& atlas) 
			: m_Name(name), m_Atlas(atlas) {}
	};

private:
	vector<AtlasItem*> m_Atlases;

public:
	AssetManager() {}
	~AssetManager();

	void			AddAtlas(const char* name, const char* imagePath, const char* dataPath);
	TextureAtlas*	GetTextureAtlas(const char* name);

};

#endif