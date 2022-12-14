// A_Scene.h: interface for the A_Scene class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_A_SCENE_H__129C9FEB_647C_4B27_A8D9_5D36E52F7013__INCLUDED_)
#define AFX_A_SCENE_H__129C9FEB_647C_4B27_A8D9_5D36E52F7013__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class A_Scene  
{
public:
	A_Scene();
	virtual ~A_Scene();

	void Set_Paths(void);

	char Last_Saved_EBR_Path[MAX_PATH];
	char Current_3DT_Path[MAX_PATH];
	char Current_3DT_File[MAX_PATH];
	char Current_3DT_Just_Path[MAX_PATH];

};

#endif // !defined(AFX_A_SCENE_H__129C9FEB_647C_4B27_A8D9_5D36E52F7013__INCLUDED_)
