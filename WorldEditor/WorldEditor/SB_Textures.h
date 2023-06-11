/*
Copyright (c) 2023 World Editor -- HGT Software W.T.Flanigan H.C.Flanigan

This software is provided 'as-is', without any express or implied
warranty. In no event will the authors be held liable for any damages
arising from the use of this software.

Permission is granted to anyone to use this software for any purpose,
including commercial applications, and to alter it and redistribute it
freely, subject to the following restrictions:

1. The origin of this software must not be misrepresented; you must not
claim that you wrote the original software. If you use this software
in a product, an acknowledgment in the product documentation would be
appreciated but is not required.

2. Altered source versions must be plainly marked as such, and must not be
misrepresented as being the original software.

3. This notice may not be removed or altered from any source
distribution.
*/

#pragma once
class SB_Textures
{
public:
	SB_Textures();
	~SB_Textures();

	void Load_Textures_Assimp();
	void Load_Textures_Ogre3D(void);

	bool Windows_Preview_FullPath(int Index, char* FullPath);
	bool Load_OpenGL_Textures(int TextureID);

	int WriteTGA(const char* pszFile, geBitmap* pBitmap);
	int Genesis_WriteToBmp(geBitmap* bmp, char* filename);
	bool Soil_Load_Texture(UINT textureArray[], LPSTR strFileName, int textureID);
	bool HBITMAP_TO_BmpFile(HBITMAP Bitmap, char* Filename, char* SaveFolder);

	bool Jpg_To_png24(char* File);
	bool Bmp_To_Jpg(char* File);

	char TextureFileName[MAX_PATH];

protected:

	bool Texture_To_Bmp(char* File);
	bool LoadDummyTexture(int Index);
};

