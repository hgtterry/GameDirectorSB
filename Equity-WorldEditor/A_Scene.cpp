// A_Scene.cpp: implementation of the A_Scene class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "A_Scene.h"

#include "FUSIONView.h"
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

A_Scene::A_Scene()
{

	Last_Saved_EBR_Path[0] = 0;
	Current_3DT_Path[0] = 0;
	Current_3DT_File[0] = 0;
	Current_3DT_Just_Path[0] = 0;
	Current_TXL_FilePath[0] = 0;
	Current_TXL_FileName[0] = 0;
}

A_Scene::~A_Scene()
{

}

// *************************************************************************
// *				Set_Paths:- Terry and Hazel Flanigan 2023			   *
// *************************************************************************
void A_Scene::Set_Paths(void)
{
	char mFileName[MAX_PATH];
	char mPath_FileName[MAX_PATH];

	strcpy(mFileName, Current_3DT_File);
	strcpy(mPath_FileName, Current_3DT_Path);

	int len1 = strlen(mFileName);
	int len2 = strlen(mPath_FileName);
	strcpy(Current_3DT_Just_Path, mPath_FileName);

	Current_3DT_Just_Path[len2 - len1] = 0;

	Get_Current_TxlPath();

}

// *************************************************************************
// *		Get_Current_TxlPath:- Terry and Hazel Flanigan 2023			   *
// *************************************************************************
void A_Scene::Get_Current_TxlPath(void)
{
	CFusionDoc* pDoc = (CFusionDoc*)App->m_pMainFrame->GetCurrentDoc();

	const char *WadFilePath;
	WadFilePath = Level_GetWadPath(pDoc->pLevel);

	strcpy(Current_TXL_FilePath,WadFilePath);

	Get_FileName_FromPath(Current_TXL_FilePath,Current_TXL_FilePath);

	strcpy(Current_TXL_FileName,JustFileName);

}

// *************************************************************************
// *		Get_FileName_FromPath:- Terry and Hazel Flanigan 2023	  	   *
// *************************************************************************
void A_Scene::Get_FileName_FromPath(char *pString, char *FileName)
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
