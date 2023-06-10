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

#include "stdafx.h"
#include "AB_App.h"


SB_App::SB_App()
{
	ABC_Export_RFW =			NULL;
	CLSB_FileIO =				NULL;
	CL_Dialogs =				NULL;
	CL_World =					NULL;
	CL_Render_App =				NULL;
	CL_TxlEditor =				NULL;
	CL_TextureDialog =			NULL;
	CL_FaceDialog =				NULL;
	CL_TabsControl =			NULL;
	CL_TabsGroups_Dlg =			NULL;
	CL_TabsTemplates_Dlg =		NULL;

	CL_CreateArchDialog =		NULL;
	CL_CreateBoxDialog =		NULL;
	CL_CreateConeDialog =		NULL;
	CL_CreateCylDialog =		NULL;
	CL_CreateSpheroidDialog =	NULL;
	CL_CreateStaircaseDialog  = NULL;
	CL_Camera =					NULL;
	CL_TopTabs =				NULL;
	CL_File =					NULL;
	CL_Brush =					NULL;

	CL_Export_World =			NULL;

	CL_Main_View =				NULL;

	CL_F_View =					NULL;

	// Scene Builder 
	CLSB_Ogre =					nullptr;
	CLSB_Grid =					nullptr;
	CLSB_Ogre_Dialog =			nullptr;
	CLSB_Keyboard =				nullptr;
	CLSB_Camera =				nullptr;
	CLSB_Assimp =				nullptr;
	CLSB_Model =				nullptr;
	CLSB_Loader =				nullptr;
	CLSB_Ini =					nullptr;
	CLSB_Load_Textures =		nullptr;
	CLSB_Export_Ogre3D =		nullptr;
	CLSB_Exporter =				nullptr;

	AppBackground = NULL;
	BlackBrush =	NULL;
	Brush_White =	NULL;
	Brush_Green =	NULL;
	Brush_Tabs_UnSelected = NULL;

	Font_CB15 = 0;
	Font_CB18 = 0;
	Font_Arial20 = 0;
	Font_Banner = 0;

	Hnd_HollowBox_Bmp = NULL;
	Hnd_SolidBox_Bmp = NULL;
	Hnd_HollowSpheroid_Bmp = NULL;
	Hnd_SolidSpheroid_Bmp = NULL;

	Hnd_Arch_Icon =		NULL;
	Hnd_Cone_Icon =		NULL;
	Hnd_Cyl_Icon =		NULL;
	Hnd_Spheriod_Icon = NULL;
	Hnd_Box_Icon =		NULL;
	Hnd_Stairs_Icon =	NULL;

	WorldEditor_Directory[0] = 0;

	CursorPosX = 500;
	CursorPosY = 500;

	Debug_App = 1;
	Debug_File = 1;

	hMenu = NULL;

	// MFC
	m_pMainFrame = NULL;
	pCFusionDoc = NULL;

	Write_DebugFile = NULL;

}

SB_App::~SB_App()
{

}

#include <tlhelp32.h>
#include <tchar.h>

bool SB_App::IsProcessRunning(char* executableName)
{
	PROCESSENTRY32 entry;
	entry.dwSize = sizeof(PROCESSENTRY32);

	HANDLE  snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, NULL);

	if (!Process32First(snapshot, &entry)) {
		CloseHandle(snapshot);
		return false;
	}

	do {
		if (!_tcsicmp(entry.szExeFile, executableName)) {
			CloseHandle(snapshot);
			return true;
		}
	} while (Process32Next(snapshot, &entry));

	CloseHandle(snapshot);
	return false;
}

// *************************************************************************
// *								InitMFC								   *
// *************************************************************************
void SB_App::InitMFC(void)
{	
	m_pMainFrame = (CMainFrame *)AfxGetMainWnd();
}

// *************************************************************************
// *						InitApp Inflanite							   *
// *************************************************************************
bool SB_App::InitApp(void)
{	
	ABC_Export_RFW  =				new AB_Export_RFW();
	CLSB_FileIO =					new	SB_FileIO();
	CL_Dialogs =					new	A_Dialogs();
	CL_World =						new	A_World();
	CL_Render_App =					new	A_Render_App();
	CL_TxlEditor =					new	A_TxlEditor();
	CL_TextureDialog =				new	A_TextureDialog();
	CL_FaceDialog =					new A_FaceDialog();
	CL_TabsControl =				new A_TabsControl();
	CL_TabsGroups_Dlg =				new A_TabsGroups_Dlg();
	CL_TabsTemplates_Dlg =			new A_TabsTemplates_Dlg();

	CL_CreateArchDialog =			new A_CreateArchDialog();
	CL_CreateBoxDialog =			new A_CreateBoxDialog();
	CL_CreateConeDialog =			new A_CreateConeDialog();
	CL_CreateCylDialog =			new A_CreateCylDialog();
	CL_CreateSpheroidDialog =		new A_CreateSpheroidDialog();
	CL_CreateStaircaseDialog  =		new A_CreateStaircaseDialog();
	CL_Camera =						new A_Camera();
	CL_TopTabs =					new A_TopTabs();
	CL_File =						new	A_File();
	CL_Brush =						new A_Brush();

	CL_Export_World =				new A_Export_World();
	
	CL_Main_View =					new A_MainView();

	CL_F_View =						new F_View();


	// Scene Builder 
	CLSB_Ogre =						new SB_Ogre();
	CLSB_Grid =						new SB_Grid();
	CLSB_Ogre_Dialog =				new SB_Ogre_Dialog();
	CLSB_Keyboard =					new SB_Keyboard();
	CLSB_Camera =					new SB_Camera();
	CLSB_Assimp =					new SB_Assimp();
	CLSB_Model =					new SB_Model();
	CLSB_Loader =					new SB_Loader();
	CLSB_Ini =						new SB_Ini();
	CLSB_Load_Textures =			new SB_Load_Textures();
	CLSB_Export_Ogre3D =			new SB_Export_Ogre3D();
	CLSB_Exporter =					new SB_Exporter();

	InitCommonControls();

	hInst =NULL;
	MainHwnd = NULL;
	
	SetBrushes_Fonts();

	return 1;
}

// *************************************************************************
// *					SetBrushes_Fonts Inflanite						   *
// *************************************************************************
void SB_App::SetBrushes_Fonts(void)
{
	AppBackground = CreateSolidBrush(RGB(213, 222, 242));

	BlackBrush = CreateSolidBrush(RGB(0, 0, 0));
	Brush_White = CreateSolidBrush(RGB(255, 255, 255));
	Brush_Green = CreateSolidBrush(RGB(0, 255, 0));

	//Brush_Tabs = CreateSolidBrush(RGB(255, 255, 255));
	Brush_Tabs_UnSelected = CreateSolidBrush(RGB(190, 190, 190));

	Brush_But_Normal = CreateSolidBrush(RGB(255, 255, 150));
	Brush_But_Hover = CreateSolidBrush(RGB(255, 255, 200));
	Brush_But_Pressed = CreateSolidBrush(RGB(240, 240, 190));

	Font_CB15 = CreateFont(-15, 0, 0, 0, 0, 0, 0, 0, 0, OUT_TT_ONLY_PRECIS, 0, 0, 0, "Courier Black");
	Font_CB18 = CreateFont(-18, 0, 0, 0, 0, 0, 0, 0, 0, OUT_TT_ONLY_PRECIS, 0, 0, 0, "Courier Black");
	Font_Arial20 = CreateFont(-20, 0, 0, 0, 0, 0, 0, 0, 0, OUT_TT_ONLY_PRECIS, 0, 0, 0, "Arial");
	Font_Banner = CreateFont(-30, 0, 0, 0, FW_BOLD, 0, 0, 0, 0, OUT_TT_ONLY_PRECIS, 0, 0, 0, "Aerial Black");
}

// *************************************************************************
// *		LoadProgramResource:- Terry and Hazel Flanigan 2023		  	   *
// *************************************************************************
void SB_App::LoadProgramResource(void)
{
	Hnd_HollowBox_Bmp = LoadBitmap(hInst, (LPCTSTR)IDB_HOLLOWBOX);
	Hnd_SolidBox_Bmp = LoadBitmap(hInst, (LPCTSTR)IDB_SOLIDBOX);

	Hnd_HollowSpheroid_Bmp = LoadBitmap(hInst, (LPCTSTR)IDB_HOLLOWSPHERE);
	Hnd_SolidSpheroid_Bmp = LoadBitmap(hInst, (LPCTSTR)IDB_SOLIDSPHERE);

	Hnd_Arch_Icon = LoadIcon(hInst, (LPCTSTR)IDI_ARCH_PRIMITIVE);
	Hnd_Cone_Icon = LoadIcon(hInst, (LPCTSTR)IDI_CONE_PRIMITIVE);
	Hnd_Cyl_Icon = LoadIcon(hInst, (LPCTSTR)IDI_CYLINDER_PRIMITIVE);
	Hnd_Spheriod_Icon = LoadIcon(hInst, (LPCTSTR)IDI_SPHEROID_PRIMITIVE);
	Hnd_Box_Icon = LoadIcon(hInst, (LPCTSTR)IDI_CUBE_PRIMITIVE);
	Hnd_Stairs_Icon = LoadIcon(hInst, (LPCTSTR)IDI_STAIRCASE_PRIMITIVE);

}

// *************************************************************************
// *				Say:- Terry and Hazel Flanigan 2023					   *
// *************************************************************************
void SB_App::Say(const char* Message, char* Message2)
{
	char text[MAX_PATH];
	char text2[MAX_PATH];

	strcpy(text, Message);

	if (Message2 == NULL)
	{
		strcpy(text2, " ");
	}
	else
	{
		strcpy(text2, Message2);
	}

	App->CL_Dialogs->Message(text, text2);
}

// *************************************************************************
// *				Say_Int:- Terry and Hazel Flanigan 2023				   *
// *************************************************************************
void SB_App::Say_Int(int Value)
{
	char buf[255];
	itoa(Value, buf, 10);
	MessageBox(MainHwnd, buf, "Equity Notice", MB_OK);
}

// *************************************************************************
// *			Say_Float:- Terry and Hazel Flanigan 2023				   *
// *************************************************************************
void SB_App::Say_Float(float Value)
{
	char buf[255];
	sprintf(buf, "%f", Value);
	MessageBox(MainHwnd, buf, "Equity Notice", MB_OK);
}

// *************************************************************************
// *				FlashWindow:- Terry and Hazel Flanigan 2023			   *
// *************************************************************************
void SB_App::Flash_Window()
{
	FlashWindow(MainHwnd,true);
}

// *************************************************************************
// *	Custom_Button_Toggle_Tabs_MFC:- Terry and Hazel Flanigan 2023      *
// *************************************************************************
bool SB_App::Custom_Button_Toggle_Tabs_MFC(LPDRAWITEMSTRUCT lpDIS,HWND hDlg, bool Toggle)
{
	if (Toggle == 0)
	{
		HPEN pen = CreatePen(PS_INSIDEFRAME, 0, RGB(190, 190, 190));

		HGDIOBJ old_pen = SelectObject(lpDIS->hDC, pen);
		HGDIOBJ old_brush = SelectObject(lpDIS->hDC, App->Brush_Tabs_UnSelected);

		RoundRect(lpDIS->hDC, lpDIS->rcItem.left, lpDIS->rcItem.top,
			lpDIS->rcItem.right, lpDIS->rcItem.bottom, 0, 0);

		char szBtnText[32] = { 0 };

		HWND temp = GetDlgItem(hDlg, lpDIS->CtlID);
		GetDlgItemText(hDlg,lpDIS->CtlID, szBtnText, sizeof(szBtnText)); 

		SetTextColor(lpDIS->hDC, RGB(0, 0, 0));
		SetBkMode(lpDIS->hDC, TRANSPARENT);
		DrawText(lpDIS->hDC,szBtnText,strlen(szBtnText), &lpDIS->rcItem,DT_CENTER | DT_SINGLELINE | DT_VCENTER);

	}
	else
	{
		HPEN pen = CreatePen(PS_INSIDEFRAME, 0, RGB(255, 255, 255));

		HGDIOBJ old_pen = SelectObject(lpDIS->hDC, pen);
		HGDIOBJ old_brush = SelectObject(lpDIS->hDC, App->Brush_White);

		RoundRect(lpDIS->hDC, lpDIS->rcItem.left, lpDIS->rcItem.top,
			lpDIS->rcItem.right, lpDIS->rcItem.bottom, 0, 0);

		char szBtnText[32] = { 0 };

		HWND temp = GetDlgItem(hDlg, lpDIS->CtlID);
		GetDlgItemText(hDlg,lpDIS->CtlID, szBtnText, sizeof(szBtnText)); 

		SetTextColor(lpDIS->hDC, RGB(0, 0, 0));
		SetBkMode(lpDIS->hDC, TRANSPARENT);
		DrawText(lpDIS->hDC,szBtnText,strlen(szBtnText), &lpDIS->rcItem,DT_CENTER | DT_SINGLELINE | DT_VCENTER);

	}

	return 1;
}

// *************************************************************************
// *	Custom_Button_Toggle_MFC:- Terry and Hazel Flanigan 2023   	 	   *
// *************************************************************************
bool SB_App::Custom_Button_Toggle_MFC(LPDRAWITEMSTRUCT lpDIS,HWND hDlg, bool Toggle)
{
	if (Toggle == 0)
	{
		HPEN pen = CreatePen(PS_INSIDEFRAME, 0, RGB(0, 0, 0));

		HGDIOBJ old_pen = SelectObject(lpDIS->hDC, pen);
		HGDIOBJ old_brush = SelectObject(lpDIS->hDC, App->Brush_But_Normal);

		RoundRect(lpDIS->hDC, lpDIS->rcItem.left, lpDIS->rcItem.top,
			lpDIS->rcItem.right, lpDIS->rcItem.bottom, 2, 2);

		char szBtnText[32] = { 0 };

		HWND temp = GetDlgItem(hDlg, lpDIS->CtlID);
		GetDlgItemText(hDlg,lpDIS->CtlID, szBtnText, sizeof(szBtnText)); 

		SetTextColor(lpDIS->hDC, RGB(0, 0, 0));
		SetBkMode(lpDIS->hDC, TRANSPARENT);
		DrawText(lpDIS->hDC,szBtnText,strlen(szBtnText), &lpDIS->rcItem,DT_CENTER | DT_SINGLELINE | DT_VCENTER);

	}
	else
	{
		HPEN pen = CreatePen(PS_INSIDEFRAME, 0, RGB(0, 0, 0));

		HGDIOBJ old_pen = SelectObject(lpDIS->hDC, pen);
		HGDIOBJ old_brush = SelectObject(lpDIS->hDC, App->Brush_Green);

		RoundRect(lpDIS->hDC, lpDIS->rcItem.left, lpDIS->rcItem.top,
			lpDIS->rcItem.right, lpDIS->rcItem.bottom, 2, 2);

		char szBtnText[32] = { 0 };

		HWND temp = GetDlgItem(hDlg, lpDIS->CtlID);
		GetDlgItemText(hDlg,lpDIS->CtlID, szBtnText, sizeof(szBtnText)); 

		SetTextColor(lpDIS->hDC, RGB(0, 0, 0));
		SetBkMode(lpDIS->hDC, TRANSPARENT);
		DrawText(lpDIS->hDC,szBtnText,strlen(szBtnText), &lpDIS->rcItem,DT_CENTER | DT_SINGLELINE | DT_VCENTER);

	}

	return 1;
}

// *************************************************************************
// *		Custom_Button_Normal_MFC:- Terry and Hazel Flanigan 2023  	   *
// *************************************************************************
bool SB_App::Custom_Button_Normal_MFC(LPDRAWITEMSTRUCT lpDIS,HWND hDlg)
{
	HPEN pen = CreatePen(PS_INSIDEFRAME, 0, RGB(0, 0, 0));

	HGDIOBJ old_pen = SelectObject(lpDIS->hDC, pen);
	HGDIOBJ old_brush = SelectObject(lpDIS->hDC, App->Brush_But_Normal);

	RoundRect(lpDIS->hDC, lpDIS->rcItem.left, lpDIS->rcItem.top,
		lpDIS->rcItem.right, lpDIS->rcItem.bottom, 2, 2);

	char szBtnText[32] = { 0 };

	HWND temp = GetDlgItem(hDlg, lpDIS->CtlID);
	GetDlgItemText(hDlg,lpDIS->CtlID, szBtnText, sizeof(szBtnText)); 

	SetTextColor(lpDIS->hDC, RGB(0, 0, 0));
	SetBkMode(lpDIS->hDC, TRANSPARENT);
	DrawText(lpDIS->hDC,szBtnText,strlen(szBtnText), &lpDIS->rcItem,DT_CENTER | DT_SINGLELINE | DT_VCENTER);
	return 1;

	return 1;
}

// *************************************************************************
// *	Custom_Button_Toggle_Disable:- Terry and Hazel Flanigan 2023	   *
// *************************************************************************
bool SB_App::Custom_Button_Toggle_Disable(LPDRAWITEMSTRUCT lpDIS,HWND hDlg, bool Toggle)
{
	if (Toggle == 0)
	{
		HPEN pen = CreatePen(PS_INSIDEFRAME, 0, RGB(0, 0, 0));

		HGDIOBJ old_pen = SelectObject(lpDIS->hDC, pen);
		HGDIOBJ old_brush = SelectObject(lpDIS->hDC, App->Brush_Tabs_UnSelected);

		RoundRect(lpDIS->hDC, lpDIS->rcItem.left, lpDIS->rcItem.top,
			lpDIS->rcItem.right, lpDIS->rcItem.bottom, 2, 2);

		char szBtnText[32] = { 0 };

		HWND temp = GetDlgItem(hDlg, lpDIS->CtlID);
		GetDlgItemText(hDlg,lpDIS->CtlID, szBtnText, sizeof(szBtnText)); 

		SetTextColor(lpDIS->hDC, RGB(0, 0, 0));
		SetBkMode(lpDIS->hDC, TRANSPARENT);
		DrawText(lpDIS->hDC,szBtnText,strlen(szBtnText), &lpDIS->rcItem,DT_CENTER | DT_SINGLELINE | DT_VCENTER);
	}
	else
	{
		HPEN pen = CreatePen(PS_INSIDEFRAME, 0, RGB(0, 0, 0));

		HGDIOBJ old_pen = SelectObject(lpDIS->hDC, pen);
		HGDIOBJ old_brush = SelectObject(lpDIS->hDC, App->Brush_Green);

		RoundRect(lpDIS->hDC, lpDIS->rcItem.left, lpDIS->rcItem.top,
			lpDIS->rcItem.right, lpDIS->rcItem.bottom, 2, 2);

		char szBtnText[32] = { 0 };

		HWND temp = GetDlgItem(hDlg, lpDIS->CtlID);
		GetDlgItemText(hDlg,lpDIS->CtlID, szBtnText, sizeof(szBtnText)); 

		SetTextColor(lpDIS->hDC, RGB(0, 0, 0));
		SetBkMode(lpDIS->hDC, TRANSPARENT);
		DrawText(lpDIS->hDC,szBtnText,strlen(szBtnText), &lpDIS->rcItem,DT_CENTER | DT_SINGLELINE | DT_VCENTER);
	}

	return 1;
}

// *************************************************************************
// *						CreateGradientBrush					 	 	   *
// *************************************************************************
HBRUSH SB_App::CreateGradientBrush(COLORREF top, COLORREF bottom, LPNMCUSTOMDRAW item)
{
	HBRUSH Brush = NULL;
	HDC hdcmem = CreateCompatibleDC(item->hdc);
	HBITMAP hbitmap = CreateCompatibleBitmap(item->hdc, item->rc.right - item->rc.left, item->rc.bottom - item->rc.top);
	SelectObject(hdcmem, hbitmap);

	int r1 = GetRValue(top), r2 = GetRValue(bottom), g1 = GetGValue(top), g2 = GetGValue(bottom), b1 = GetBValue(top), b2 = GetBValue(bottom);
	for (int i = 0; i < item->rc.bottom - item->rc.top; i++)
	{
		RECT temp;
		int r, g, b;
		r = int(r1 + double(i * (r2 - r1) / item->rc.bottom - item->rc.top));
		g = int(g1 + double(i * (g2 - g1) / item->rc.bottom - item->rc.top));
		b = int(b1 + double(i * (b2 - b1) / item->rc.bottom - item->rc.top));
		Brush = CreateSolidBrush(RGB(r, g, b));
		temp.left = 0;
		temp.top = i;
		temp.right = item->rc.right - item->rc.left;
		temp.bottom = i + 1;
		FillRect(hdcmem, &temp, Brush);
		DeleteObject(Brush);
	}
	HBRUSH pattern = CreatePatternBrush(hbitmap);

	DeleteDC(hdcmem);
	DeleteObject(Brush);
	DeleteObject(hbitmap);

	return pattern;
}

// *************************************************************************
// *			Debug_Set:- Terry and Hazel Flanigan 2023				   *
// *************************************************************************
void SB_App::Debug_Set(void)
{
	if (Debug_File == 1)
	{
		Write_DebugFile = NULL;

		char Path[1024];
		strcpy(Path,App->WorldEditor_Directory);
		strcat(Path,"Debug.txt");

		Write_DebugFile = fopen(Path, "wt");


		if (!Write_DebugFile)
		{
			return;
		}

		fprintf(Write_DebugFile, "Debug File\n");
	}
}

// *************************************************************************
// *			Debug_Close:- Terry and Hazel Flanigan 2023				   *
// *************************************************************************
void SB_App::Debug_Close(void)
{
	if (Debug_File == 1)
	{
		if (Write_DebugFile)
		{
			fclose(Write_DebugFile);
			Write_DebugFile = NULL;
		}
	}
}

// *************************************************************************
// *			Debug_Message:- Terry and Hazel Flanigan 2023				   *
// *************************************************************************
void SB_App::Debug_Message(char* Message, bool NewLine)
{
	if (Debug_File == 1)
	{
		fprintf(Write_DebugFile, "%s ",Message);

		if (NewLine == 1)
		{
			fprintf(Write_DebugFile, "%s","\n");
		}
	}
}

// *************************************************************************
// *			Debug_Int:- Terry and Hazel Flanigan 2023				   *
// *************************************************************************
void SB_App::Debug_Int(int Value, bool NewLine)
{
	if (Debug_File == 1)
	{
		fprintf(Write_DebugFile, "%i ",Value);

		if (NewLine == 1)
		{
			fprintf(Write_DebugFile, "%s","\n");
		}	
	}
}

// *************************************************************************
// *			Debug_Float:- Terry and Hazel Flanigan 2023				   *
// *************************************************************************
void SB_App::Debug_Float(float Value, bool NewLine)
{
	if (Debug_File == 1)
	{
		fprintf(Write_DebugFile, "%f ",Value);

		if (NewLine == 1)
		{
			fprintf(Write_DebugFile, "%s","\n");
		}	
	}
}

// *************************************************************************
// *			Wait_For_Key:- Terry and Hazel Flanigan 2023			   *
// *************************************************************************
void SB_App::Wait_For_Key(int Delay)
{
	int Count = 0;

	while (Count < Delay)
	{
		App->Flash_Window();
		Count++;
	}
}

