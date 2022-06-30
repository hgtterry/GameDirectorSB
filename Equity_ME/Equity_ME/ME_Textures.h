#pragma once
class ME_Textures
{
public:
	ME_Textures();
	~ME_Textures();

	bool Soil_DecodeTextures(int TextureID);
	bool Soil_Load_Texture(UINT textureArray[], LPSTR strFileName, int textureID);
	bool TexureToWinPreviewFullPath(int Index, char* FullPath);
	void Strip_JustFileName(char *pString, char *FileName);

	bool DecompileTextures(char* Path);

	bool LoadDummyTexture(int Index);
	bool ChangeTexture_Model(void);

	char JustFileName[MAX_PATH];
	char TextureFileName[MAX_PATH];
	UINT  g_Texture[300];

private:

};

