/*
Copyright (c) 2022 Equity_ME Model Editor -- Inflanite Software W.T.Flanigan H.C.Flanigan

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

typedef struct Char_type2 { char Name[256]; }Char_type2;

class ME_Equity_SB
{
public:
	ME_Equity_SB();
	~ME_Equity_SB();

	bool Start_WE_import();
	bool Write_Project_File(char* Path_And_File);

	char Pref_Ogre_Path[MAX_PATH];

protected:
		
	static LRESULT CALLBACK WE_import_Proc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);

	
	bool Load_Project_File(char* Path_And_File);

	bool LoadTextures_TXL();
	int Check_for_Textures(geVFile *BaseFile);
	bool Check_in_Txl(char *FileName);
	bool AddTexture(geVFile *BaseFile, const char *Path, int GroupIndex);
	HBITMAP CreateHBitmapFromgeBitmap(geBitmap *Bitmap, HDC hdc);
	void Copy_Texture_Names();
	void Adjust();

	bool Txt_OpenFile(char* Extension, char* Title, char* StartDirectory);

	int NameCount;

	std::vector<Char_type2> BitMap_Names;

	char Txt_FileName[255];
	char Txt_Path_FileName[1024];

	char Pref_Txl_FileName[MAX_PATH];
	char Pref_Txl_Path_FileName[MAX_PATH];

	char Pref_WE_JustFileName[MAX_PATH];			
	char Pref_WE_Path_FileName[MAX_PATH];		

	char Pref_Ogre_JustFileName[MAX_PATH];		

	FILE* WriteScene;

	OPENFILENAME ofn;
};

