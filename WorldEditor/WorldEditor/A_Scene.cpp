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

#include "stdafx.h"
#include "AB_App.h"
#include "A_Scene.h"

#include "FUSIONView.h"
#include "FUSIONDoc.h"

A_World::A_World()
{

	Last_Saved_EBR_Path[0] = 0;
	
	mCurrent_TXL_FilePath[0] = 0;
	mCurrent_TXL_FileName[0] = 0;

	mCurrent_3DT_File[0] = 0;
	mCurrent_3DT_PathAndFile[0] = 0;
}

A_World::~A_World()
{

}

// *************************************************************************
// *	  	Get_Current_Document:- Terry and Hazel Flanigan 2023		   *
// *************************************************************************
void A_World::Get_Current_Document()
{
	m_pDoc = (CFusionDoc*)App->m_pMainFrame->GetCurrentDoc();
}

// *************************************************************************
// *				Set_Paths:- Terry and Hazel Flanigan 2023			   *
// *************************************************************************
void A_World::Set_Paths(void)
{
	//Get_Current_Document();

	Set_Current_3DT_Paths();
	Set_Current_TxlPath();
}


// *************************************************************************
// *			Reset_Editor:- Terry and Hazel Flanigan 2023			   *
// *************************************************************************
void A_World::Reset_Editor(void)
{
	App->CLSB_TopTabs->Reset_Tabs_Buttons();
	App->CLSB_TopTabs->Header_BrushModify_Flag = 1;
	ShowWindow(App->CLSB_TopTabs->Brush_Modify_Panel_Hwnd, SW_SHOW);

	App->CLSB_TopTabs->Reset_Render_Buttons();
	App->CLSB_TopTabs->Textured_Flag = 1;

	App->CLSB_TopTabs->Reset_Brush_Buttons();
	App->CLSB_TopTabs->Brush_Select_Flag = 1;

	App->CLSB_TopTabs->Select_Mode();

	App->CL_TabsControl->Hide_Dialogs();
	App->CL_TabsControl->Tab_Templates_Flag = 1;
	App->CL_TabsTemplates_Dlg->Show_TemplatesDialog(true);

	App->CL_Render_App->Render3D_Mode(ID_VIEW_TEXTUREVIEW); // Use Textures not wire frame

	App->CL_TabsTemplates_Dlg->Enable_Insert_Button(false);

	RedrawWindow(App->CL_TabsControl->Tabs_Control_Hwnd, NULL, NULL, RDW_INVALIDATE | RDW_UPDATENOW);
	RedrawWindow(App->CLSB_TopTabs->Top_Tabs_Hwnd, NULL, NULL, RDW_INVALIDATE | RDW_UPDATENOW);

}

// *************************************************************************
// *		Set_Current_3DT_Paths:- Terry and Hazel Flanigan 2023		   *
// *************************************************************************
void A_World::Set_Current_3DT_Paths(void)
{
	CFusionDoc* pDoc = (CFusionDoc*)App->m_pMainFrame->GetCurrentDoc();

	char mFileName[MAX_PATH];
	char mPath_FileName[MAX_PATH];
	
	strcpy(mCurrent_3DT_PathAndFile,pDoc->GetPathName()); // MFC

	Get_FileName_FromPath(mCurrent_3DT_PathAndFile,mCurrent_3DT_PathAndFile);

	strcpy(mCurrent_3DT_File,JustFileName);

	strcpy(mFileName, mCurrent_3DT_File);
	strcpy(mPath_FileName, mCurrent_3DT_Path);
	int len1 = strlen(mFileName);
	int len2 = strlen(mCurrent_3DT_PathAndFile);
	strcpy(mCurrent_3DT_Path, mCurrent_3DT_PathAndFile);

	mCurrent_3DT_Path[len2 - len1] = 0;

}

// *************************************************************************
// *		Set_Current_TxlPath:- Terry and Hazel Flanigan 2023			   *
// *************************************************************************
void A_World::Set_Current_TxlPath(void)
{
	CFusionDoc* pDoc = (CFusionDoc*)App->m_pMainFrame->GetCurrentDoc();

	const char *WadFilePath;
	WadFilePath = Level_GetWadPath(pDoc->pLevel);

	strcpy(mCurrent_TXL_FilePath,WadFilePath);

	Get_FileName_FromPath(mCurrent_TXL_FilePath,mCurrent_TXL_FilePath);

	strcpy(mCurrent_TXL_FileName,JustFileName);

}

// *************************************************************************
// *		Get_FileName_FromPath:- Terry and Hazel Flanigan 2023	  	   *
// *************************************************************************
void A_World::Get_FileName_FromPath(char *pString, char *FileName)
{
	JustFileName[0] = 0;

	int Count = 0;
	int Mark = 0;
	bool Test = 0;

	while (*pString != 0)
	{
		if (*pString == '\\' || *pString == '/')
		{
			Test = 1;
			Mark = Count;
		}

		Count++;
		pString++;
	}

	if (Mark == 0 && Test == 0)
	{
		strcpy(JustFileName, FileName);
	}
	else
	{
		if (Mark == 0 && Test == 1)
		{
			Mark = 1;
			strcpy(JustFileName, (FileName + Mark));
		}
		else
		{
			strcpy(JustFileName, (FileName + Mark) + 1);
		}
	}
}

struct tag_BrushList
{
	Brush *First;
	Brush *Last;
};

// *************************************************************************
// *			Get_Brush_Count:- Terry and Hazel Flanigan 2023			   *
// *************************************************************************
int A_World::Get_Brush_Count()
{
	m_pDoc = (CFusionDoc*)App->m_pMainFrame->GetCurrentDoc();

	Level *pLevel = m_pDoc->pLevel;
	BrushList *pList = Level_GetBrushes (m_pDoc->pLevel);


	int Count = 0;
	Brush * b;
	b = pList->First;
	while (b != NULL)
	{
		Count++;
		b = b->Next;
	}

	return Count;
}

// *************************************************************************
// *			Get_Brush_ByIndex:- Terry and Hazel Flanigan 2023		   *
// *************************************************************************
Brush* A_World::Get_Brush_ByIndex(int Index)
{
	m_pDoc = (CFusionDoc*)App->m_pMainFrame->GetCurrentDoc();

	Level *pLevel = m_pDoc->pLevel;
	BrushList *pList = Level_GetBrushes (m_pDoc->pLevel);

	int Count = 0;
	Brush * b;
	b = pList->First;
	while (b != NULL)
	{
		if (Count == Index)
		{
			return b;
		}

		Count++;
		b = b->Next;
	}

	return NULL;
}

// *************************************************************************
// *			Level_SetTxlPath:- Terry and Hazel Flanigan 2023		   *
// *************************************************************************
void A_World::Level_SetTxlPath(char* Path)
{
	m_pDoc = (CFusionDoc*)App->m_pMainFrame->GetCurrentDoc();

	Level_SetWadPath(m_pDoc->pLevel,Path);
	App->CL_World->Set_Current_TxlPath();
	m_pDoc->UpdateAfterWadChange();
}

