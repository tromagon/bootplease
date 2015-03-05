#include "AssetManager.h"
#include "s3eFile.h"
#include <Iw2D.h>

const char* AssetManager::ID = "AssetManager_ID";

AssetManager::~AssetManager()
{
	const int l = m_Atlases.size();
	for (int i = l - 1 ; i >= 0 ; i--)
	{
		AtlasItem* item = m_Atlases[i];
		TextureAtlas* atlas = &(item->m_Atlas);
		Texture* texture = &(atlas->GetAtlasTexture());
		CIw2DImage* image = &(texture->GetImage());

		m_Atlases.erase(m_Atlases.begin() + i);

		delete item;
		delete atlas;
		delete texture;
		delete image;
	}
}

void AssetManager::AddAtlas(const char* name, const char* imagePath, const char* dataPath)
{
	CIw2DImage* image = Iw2DCreateImage(imagePath);
	Texture* texture = new Texture(*image);

	s3eFile* file = s3eFileOpen(dataPath, "rb");
	int len = s3eFileGetSize(file);
	char* buffer = new char[len];

	s3eFileRead(buffer, len, 1, file);
	s3eFileClose(file);

	TextureAtlas* atlas = new TextureAtlas(*texture, buffer);
	AtlasItem* item = new AtlasItem(name, *atlas);
	m_Atlases.push_back(item);

	delete buffer;
}

TextureAtlas* AssetManager::GetTextureAtlas(const char* name)
{
	const int l = m_Atlases.size();
	for (int i = 0 ; i < l ; i++)
	{
		AtlasItem* item = m_Atlases[i];
		if (item->m_Name == name)
		{
			return &(item->m_Atlas);
		}
	}

	return nullptr;
}