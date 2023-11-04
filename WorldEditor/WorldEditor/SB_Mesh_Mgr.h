#pragma once

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

class SB_Mesh_Mgr
{
public:
	SB_Mesh_Mgr(void);
	~SB_Mesh_Mgr(void);

	void Start_Brush_Viewer();
	void Build_Brush_List(int ExpSelected);

private:

	static LRESULT CALLBACK Brush_Viewer_Proc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);

	void UpdateBrushData(HWND hDlg, int Index);

	bool Level_Build_Brushes(Level3* pLevel, const char* Filename, BrushList* BList, int ExpSelected, geBoolean ExpLights, int GroupID);
	bool BrushList_Decode(BrushList* BList, geBoolean SubBrush);
	bool Brush_Create_X(const Brush* b);
	bool FaceList_Create(const Brush* b, const FaceList* pList, int BrushCount, int SubBrushCount);
	bool AddTexture_GL(geVFile* BaseFile, const char* TextureName, int GroupIndex);
	int Get_Adjusted_Index(int RealIndex);

	int AdjusedIndex_Store[500];
	int Brush_Index;
	char Brush_Name[200];
};

