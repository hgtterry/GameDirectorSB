// A_Scene.cpp: implementation of the A_Scene class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "A_Scene.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

A_Scene::A_Scene()
{

	Last_Saved_EBR_Path[0] = 0;
	Current_3DT_Path[0] = 0;
	Current_3DT_File[0] = 0;
	Current_3DT_Just_Path[0] = 0;
}

A_Scene::~A_Scene()
{

}

// *************************************************************************
// *						Set_Paths Terry Bernie						   *
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

}
