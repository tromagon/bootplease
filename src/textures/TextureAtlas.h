#ifndef _TEXTUREATLAS_H_
#define _TEXTUREATLAS_H_

#include "Texture.h"
#include "SubTexture.h"
#include <vector>
#include <string>

using namespace std;

class TextureAtlas
{
	class SubTextureItem
	{
	public:
		const string	m_Name;
		SubTexture&		m_SubTexture;

	public:
		explicit SubTextureItem(const string name, SubTexture& texture) 
			: m_Name(name), m_SubTexture(texture) {}
	};

private:
	Texture&				m_AtlasTexture;
	vector<SubTextureItem*> m_SubTextures;

public:
	Texture&				GetAtlasTexture() { return m_AtlasTexture; }

public:
	explicit TextureAtlas(Texture& atlasTexture, const char* atlasData);
	~TextureAtlas();

	Texture* GetTexture(const string name);

private:
	void ParseAtlas(const char* atlasData);
	void AddRegion(const string name, Rectangle region);
};

#endif