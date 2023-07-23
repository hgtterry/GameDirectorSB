#pragma once

/*
Copyright (c) World_Viewer 2023 Inflanite Software W.T.Flanigan H.C.Flanigan

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

typedef struct Char_type2 { char Name[256]; }Char_type2;

class SB_Loader
{
public:
	SB_Loader(void);
	~SB_Loader(void);

	bool Start_Groups_Dialog();
	bool Open_File_Model(const char* Extension, const char* Title, const char* StartDirectory);
	bool Read_Project_File(char* Path_And_File);

	void Assimp_Loader(char* Extension, char* Extension2);
	void Load_File_Wepf();

	bool RFActor_Loader(void);
	bool Load_ActorWorld();

	char FileName[MAX_PATH];
	char Path_FileName[MAX_PATH];

	char Txl_FileName[MAX_PATH];
	char Txl_Path_FileName[MAX_PATH];
	char WE_JustFileName[MAX_PATH];
	char Ogre_JustFileName[MAX_PATH];
	char Ogre_Path[MAX_PATH];
	char WE_Path_FileName[MAX_PATH];

	bool LoadError;

	TCHAR szSelectedDir[MAX_PATH];

protected:

	static LRESULT CALLBACK Groups_Proc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);

	bool LoadTextures_TXL();
	void Copy_Texture_Names();
	int Check_for_Textures(geVFile* BaseFile);
	bool Check_in_Txl(char* FileName);
	bool AddTexture(geVFile* BaseFile, const char* Path, int GroupIndex);
	HBITMAP CreateHBitmapFromgeBitmap(geBitmap* Bitmap, HDC hdc);

	void Adjust();

	void Rotate_Z_Model(float Z);
	void Rotate_X_Model(float X);
	void Centre_Model_Mid(void);
	void Translate_Model(float X, float Y, float Z);

	int NameCount;
	HWND RightGroups_Hwnd;

	std::vector<Char_type2> BitMap_Names;

	CFusionDoc* m_pDoc;

	OPENFILENAME ofn;
};

