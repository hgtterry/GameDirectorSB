#pragma once
class ME_Textures
{
public:
	ME_Textures();
	~ME_Textures();

	bool TexureToWinPreviewFullPath(int Index, char* FullPath);
	void Strip_JustFileName(char *pString, char *FileName);

	bool LoadDummyTexture(int Index);

	char JustFileName[MAX_PATH];

private:

};

