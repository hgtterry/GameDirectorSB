/*
Copyright (c) 2023 Equity_ME World Editor -- HGT Software W.T.Flanigan H.C.Flanigan

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

#if !defined(AFX_A_SCENE_H__129C9FEB_647C_4B27_A8D9_5D36E52F7013__INCLUDED_)
#define AFX_A_SCENE_H__129C9FEB_647C_4B27_A8D9_5D36E52F7013__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class A_World  
{
public:
	A_World();
	virtual ~A_World();

	void Get_Current_Document();
	void Set_Paths(void);
	void Set_Current_3DT_Paths(void);
	void Get_FileName_FromPath(char *pString, char *FileName);
	void Set_Current_TxlPath(void);
	void Level_SetTxlPath(char* Path);

	// Brush Percific
	int Get_Brush_Count();
	Brush* Get_Brush_ByIndex(int Index);




	char Last_Saved_EBR_Path[MAX_PATH];
	char mCurrent_3DT_File[MAX_PATH];
	char mCurrent_3DT_Path[MAX_PATH];
	char mCurrent_3DT_PathAndFile[MAX_PATH];
	char mCurrent_TXL_FilePath[MAX_PATH];
	char mCurrent_TXL_FileName[MAX_PATH];

	char JustFileName[MAX_PATH];

protected:

	CFusionDoc			*m_pDoc;

};

#endif // !defined(AFX_A_SCENE_H__129C9FEB_647C_4B27_A8D9_5D36E52F7013__INCLUDED_)
