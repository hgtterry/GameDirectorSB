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

#include "stdafx.h"
#include "resource.h"
#include "WV_App.h"
#include "Shlobj.h"


WV_App::WV_App(void)
{
	CL_Ogre =			nullptr;
	CL_Grid =			nullptr;
	CL_ImGui =			nullptr;
	CL_Loader =			nullptr;
	CL_Ini =			nullptr;
	CL_Assimp =			nullptr;
	CL_Model =			nullptr;
	CL_Export_Ogre =	nullptr;
	CL_PB =				nullptr;
	CL_Load_Ogre =		nullptr;
	CL_Keyboard =		nullptr;

	Fdlg = nullptr;
	hInst = nullptr;
	MainHwnd = nullptr;
	ListPanel = nullptr;
	mMenu = nullptr;

	AppBackground = NULL;
	DialogBackGround = NULL;
	BlackBrush = NULL;

	CUR = 0;
	AppBackground = 0;
	BlackBrush = 0;
	AppTest = 0;
//	BannerBrush = 0;
	Brush_Blue = 0;
	Brush_White = 0;
	Brush_Green = 0;
	Brush_But_Normal = 0;
	Brush_But_Hover = 0;
	Brush_But_Pressed = 0;
	Brush_Red = 0;
	Brush_Tabs = 0;
	Brush_Tabs_UnSelected = 0;
	Brush_Panel = 0;
	Brush_Button = 0;
	Brush_Button_Hover = 0;

	DialogBackGround = 0;

	Hnd_PinOff = NULL;
	Hnd_PinOn = NULL;
	Hnd_FlipWindingOrder = NULL;
	Hnd_FullScreen_Bmp = NULL;
	Hnd_ModelInfo_Bmp = NULL;
	Hnd_MouseSensitivity_Bmp = NULL;
	Hnd_Projection_Bmp = NULL;
	Hnd_LightsOn_Bmp = NULL;
	Hnd_LightsOff_Bmp = NULL;
	Hnd_BBOn_Bmp = NULL;
	Hnd_BBOff_Bmp = NULL;
	Hnd_NormalsOn_Bmp = NULL;
	Hnd_NormalsOff_Bmp = NULL;
	Hnd_BonesOn_Bmp = NULL;
	Hnd_BonesOff_Bmp = NULL;
	Hnd_MeshPointsOn_Bmp = NULL;
	Hnd_MeshPointsOff_Bmp = NULL;
	Hnd_MeshOn_Bmp = NULL;
	Hnd_MeshOff_Bmp = NULL;
	Hnd_TexturesOn_Bmp = NULL;
	Hnd_TexturesOff_Bmp = NULL;
	Hnd_Info_Bmp = NULL;
	Hnd_InfoSmall_Bmp = NULL;

	Hnd_PhysicsOff_Bmp = NULL;
	Hnd_PhysicsOn_Bmp = NULL;

	Hnd_Playoff = NULL;
	Hnd_PlayOn = NULL;
	Hnd_PlayStop = NULL;
	Hnd_StepBack = NULL;
	Hnd_StepForward = NULL;

	Hnd_GridOn_Bmp = NULL;
	Hnd_GridOff_Bmp = NULL;

	Hnd_HairOn_Bmp = NULL;
	Hnd_HairOff_Bmp = NULL;

	Font_CB12 = 0;
	Font_CB15 = 0;
	Font_CB15_Bold = 0;
	Font_Arial20 = 0;
	Font_Banner = 0;

	ViewGLhWnd =			nullptr;

	ViewPLeaseWait =		nullptr;
	GD_Properties_Hwnd =	nullptr;
	Physics_Console_Hwnd =	nullptr;

	OgreStarted = 0;
	Start_Scene_Loaded = 0;
	FullScreen = 0;
	FullScreen_App = 0;
	RenderBackGround = 0;

	Block_Mouse_Buttons = 0;

	Panels_Disabled_Flag = 0;
	Panels_Hidden_Flag = 0;

	FollowFunctions = 0;

	CursorPosX = 500;
	CursorPosY = 500;

	Debug_App = 1;
	V_New_Objects = 1;

	EquityDirecory_FullPath[0] = 0;
	ETemp_Folder[0] = 0;
}

WV_App::~WV_App(void)
{
}

// *************************************************************************
// *				InitApp:- Terry and Hazel Flanigan 2023				   *
// *************************************************************************
bool WV_App::InitApp(void)
{

	CL_Ogre =			new WV_Ogre();
	CL_Grid =			new WV_Grid();
	CL_ImGui =			new WV_ImGui();
	CL_Loader =			new WV_Loader();
	CL_Ini =			new WV_Ini();
	CL_Assimp =			new WV_Assimp();
	CL_Model =			new WV_Model();
	CL_Export_Ogre =	new WV_Export_Ogre();
	CL_PB =				new WV_PB();
	CL_Load_Ogre =		new WV_Load_Ogre();
	CL_Keyboard =		new WV_Keyboard();

	SetBrushes_Fonts();

	LoadString(hInst, IDS_APP_TITLE, Version, 255);

	char Udir[MAX_PATH];
	wchar_t* path = new wchar_t[128];
	if (SUCCEEDED(SHGetKnownFolderPath(FOLDERID_LocalAppData, 0, NULL, &path)))//KF_FLAG_CREATE
	{
		wsprintf(Udir, "%ls", path);
		CoTaskMemFree(path);
		//strcpy(App->SBC_FileIO->UserData_Folder, Udir);
	}
	else
	{
		App->Say("Can not access user folder");
	}

	char Deskdir[MAX_PATH];
	wchar_t* d_path = new wchar_t[128];
	if (SUCCEEDED(SHGetKnownFolderPath(FOLDERID_Desktop, 0, NULL, &d_path)))//KF_FLAG_CREATE
	{
		wsprintf(Deskdir, "%ls", d_path);
		CoTaskMemFree(d_path);
		//strcpy(App->SBC_FileIO->DeskTop_Folder, Deskdir);
	}
	else
	{
		App->Say("Can not access user folder");
	}

	strcpy_s(ETemp_Folder, EquityDirecory_FullPath);
	strcat_s(ETemp_Folder, "\\Data\\ETemp.bmp");

	strcpy_s(Default_Project, EquityDirecory_FullPath);
	strcat_s(Default_Project, "\\Projects\\RF_Project_Prj\\Project.SBProj");
	
	char StartFile[1024];
	strcpy_s(StartFile, App->EquityDirecory_FullPath);
	strcat_s(StartFile, "\\");
	strcat_s(StartFile, "Data\\StartUp.gcf");

	//App->Cl_Ini->SetPathName(StartFile);
	//App->Cl_Ini->WriteString("Startup", "Scene_Path_FileName", Default_Project);

	return 1;
}

// *************************************************************************
// *			SetMainWinCentre:- Terry and Hazel Flanigan 2023		   *
// *************************************************************************
bool WV_App::SetMainWinCentre(void)
{
	int ClientWidth_X = GetSystemMetrics(SM_CXSCREEN);
	int ClientHeight_Y = GetSystemMetrics(SM_CYSCREEN);

	RECT Control;
	GetClientRect(MainHwnd, &Control);

	int AllX = (ClientWidth_X / 2) - (Control.right / 2) - 10;
	int AllY = (ClientHeight_Y / 2) - (Control.bottom / 2) - 30;

	SetWindowPos(MainHwnd, NULL, AllX, AllY, 0, 0, SWP_NOSIZE);

	return 1;
}

// *************************************************************************
// *			Resize_OgreWin:- Terry and Hazel Flanigan 2023			   *
// *************************************************************************
bool WV_App::Resize_OgreWin(void)
{
	RECT rcl;

	int WidthClient = 0;
	int HeightClient;
	int NewWidth = 0;
	int NewHeight = 0;

	GetClientRect(MainHwnd, &rcl);

	WidthClient = rcl.right - rcl.left - 1010;
	NewWidth = 417 + WidthClient + 200;

	HeightClient = rcl.bottom - rcl.top;
	NewHeight = HeightClient - 150;

	//-----------------Ogre Window
	SetWindowPos(ViewGLhWnd, NULL, 4, 80, NewWidth + 384, NewHeight + 68, SWP_NOZORDER);

	if (App->OgreStarted == 1)
	{
		RECT rect;
		GetClientRect(App->ViewGLhWnd, &rect);

		if ((rect.bottom - rect.top) != 0 && App->CL_Ogre->mCamera != 0)
		{
			App->CL_Ogre->mWindow->windowMovedOrResized();
			App->CL_Ogre->mCamera->setAspectRatio((Ogre::Real)App->CL_Ogre->mWindow->getWidth() / (Ogre::Real)App->CL_Ogre->mWindow->getHeight());
			App->CL_Ogre->mCamera->yaw(Radian(0));

			Root::getSingletonPtr()->renderOneFrame();
		}

	}

	return 1;
}

// *************************************************************************
// *			RedrawWindow_Dlg:- Terry and Hazel Flanigan 2023		   *
// *************************************************************************
void WV_App::RedrawWindow_Dlg(HWND hDlg)
{
	RedrawWindow(hDlg, NULL, NULL, RDW_INVALIDATE | RDW_UPDATENOW);
}

// *************************************************************************
// *			SetBrushes_Fonts:- Terry and Hazel Flanigan 2023		   *
// *************************************************************************
void WV_App::SetBrushes_Fonts(void)
{
	AppBackground = CreateSolidBrush(RGB(213, 222, 242));
	DialogBackGround = CreateSolidBrush(RGB(208, 230, 252));
	AppTest = CreateSolidBrush(RGB(218, 240, 255));

	BlackBrush = CreateSolidBrush(RGB(0, 0, 0));

	//BannerBrush = CreateSolidBrush(RGB(200, 200, 0));

	Brush_White = CreateSolidBrush(RGB(255, 255, 255));

	Brush_Panel = CreateSolidBrush(RGB(218, 240, 255));

	Brush_Red = CreateSolidBrush(RGB(252, 85, 63));
	Brush_Green = CreateSolidBrush(RGB(0, 255, 0));
	Brush_Blue = CreateSolidBrush(RGB(0, 180, 255));

	Brush_But_Normal = CreateSolidBrush(RGB(255, 255, 150));
	Brush_But_Hover = CreateSolidBrush(RGB(255, 255, 200));
	Brush_But_Pressed = CreateSolidBrush(RGB(240, 240, 190));
	Brush_Tabs = CreateSolidBrush(RGB(255, 255, 255));
	Brush_Tabs_UnSelected = CreateSolidBrush(RGB(190, 190, 190));

	Brush_Button = CreateSolidBrush(RGB(65, 147, 245));
	Brush_Button_Hover = CreateSolidBrush(RGB(153, 204, 255));

	Font_CB12 = CreateFont(-12, 0, 0, 0, 0, 0, 0, 0, 0, OUT_TT_ONLY_PRECIS, 0, 0, 0, "Courier Black");
	Font_CB15 = CreateFont(-15, 0, 0, 0, 0, 0, 0, 0, 0, OUT_TT_ONLY_PRECIS, 0, 0, 0, "Courier Black");
	Font_Arial20 = CreateFont(-20, 0, 0, 0, 0, 0, 0, 0, 0, OUT_TT_ONLY_PRECIS, 0, 0, 0, "Arial");
	Font_CB15_Bold = CreateFont(-15, 0, 0, 0, FW_BOLD, 0, 0, 0, 0, OUT_TT_ONLY_PRECIS, 0, 0, 0, "Courier Black");

	Font_Banner = CreateFont(-30, 0, 0, 0, FW_BOLD, 0, 0, 0, 0, OUT_TT_ONLY_PRECIS, 0, 0, 0, "Aerial Black");
}

// *************************************************************************
// *				LoadProgramResource  ( Terry Bernie )			  	   *
// *************************************************************************
void WV_App::LoadProgramResource(void)
{


	/*Hnd_FullScreen_Bmp = LoadBitmap(hInst, (LPCTSTR)IDB_FULLSCREEN);

	
	Hnd_MouseSensitivity_Bmp = LoadBitmap(hInst, (LPCTSTR)IDB_MOUSESENSITIVITY);


	Hnd_Playoff = LoadBitmap(App->hInst, (LPCTSTR)IDB_MOTPLAYOFF);
	Hnd_PlayOn = LoadBitmap(App->hInst, (LPCTSTR)IDB_MOTPLAYON);
	Hnd_PlayStop = LoadBitmap(App->hInst, (LPCTSTR)IDB_MOTSTOP);
	Hnd_StepBack = LoadBitmap(App->hInst, (LPCTSTR)IDB_STEPBACK);
	Hnd_StepForward = LoadBitmap(App->hInst, (LPCTSTR)IDB_STEPFORWARD);

	Hnd_MeshOn_Bmp = LoadBitmap(hInst, (LPCTSTR)IDB_MESHON);
	Hnd_MeshOff_Bmp = LoadBitmap(hInst, (LPCTSTR)IDB_MESHOFF);

	Hnd_MeshPointsOn_Bmp = LoadBitmap(hInst, (LPCTSTR)IDB_MESHPOINTSON);
	Hnd_MeshPointsOff_Bmp = LoadBitmap(hInst, (LPCTSTR)IDB_MESHPOINTSOFF);

	Hnd_BBOn_Bmp = LoadBitmap(hInst, (LPCTSTR)IDB_BONDINGBOXON);
	Hnd_BBOff_Bmp = LoadBitmap(hInst, (LPCTSTR)IDB_BONDINGBOXOFF);

	Hnd_BonesOn_Bmp = LoadBitmap(hInst, (LPCTSTR)IDB_BONESON);
	Hnd_BonesOff_Bmp = LoadBitmap(hInst, (LPCTSTR)IDB_BONESOFF);

	Hnd_GridOn_Bmp = LoadBitmap(hInst, (LPCTSTR)IDB_GRIDON);
	Hnd_GridOff_Bmp = LoadBitmap(hInst, (LPCTSTR)IDB_GRIDOFF);

	Hnd_HairOn_Bmp = LoadBitmap(hInst, (LPCTSTR)IDB_HAIRON);
	Hnd_HairOff_Bmp = LoadBitmap(hInst, (LPCTSTR)IDB_HAIROFF);

	Hnd_TexturesOn_Bmp = LoadBitmap(hInst, (LPCTSTR)IDB_TEXTURESON);
	Hnd_TexturesOff_Bmp = LoadBitmap(hInst, (LPCTSTR)IDB_TEXTURESOFF);

	Hnd_NormalsOn_Bmp = LoadBitmap(hInst, (LPCTSTR)IDB_NORMALSON);
	Hnd_NormalsOff_Bmp = LoadBitmap(hInst, (LPCTSTR)IDB_NORMALSOFF);

	Hnd_LightsOn_Bmp = LoadBitmap(hInst, (LPCTSTR)IDB_LIGHTON);
	Hnd_LightsOff_Bmp = LoadBitmap(hInst, (LPCTSTR)IDB_LIGHTOFF);

	Hnd_ModelInfo_Bmp = LoadBitmap(hInst, (LPCTSTR)IDB_MODELDATA);

	Hnd_InfoBig_Bmp = LoadBitmap(hInst, (LPCTSTR)IDB_INFOBIG);
	Hnd_InfoSmall_Bmp = LoadBitmap(hInst, (LPCTSTR)IDB_INFOSMALL);

	Hnd_PhysicsOff_Bmp = LoadBitmap(hInst, (LPCTSTR)IDB_PHYSICSOFF);
	Hnd_PhysicsOn_Bmp = LoadBitmap(hInst, (LPCTSTR)IDB_PHYSICSON);*/

}

// *************************************************************************
// *		SetTitleBar Inflanite:- Terry and Hazel Flanigan 2023		   *
// *************************************************************************
void WV_App::SetTitleBar(HWND hDlg)
{
	char TitleBar[260];
	strcpy_s(TitleBar, App->Version);
	SetWindowText(hDlg, TitleBar);
}

// *************************************************************************
// *	  	Set_Main_TitleBar:- Terry and Hazel Flanigan 2023			   *
// *************************************************************************
void WV_App::Set_Main_TitleBar(char * PathFile)
{
	char TitleBar[260];
	strcpy_s(TitleBar, App->Version);
	strcat_s(TitleBar, "    ");
	strcat_s(TitleBar, PathFile);
	SetWindowText(MainHwnd, TitleBar);
}

// *************************************************************************
// *				Say:- Terry and Hazel Flanigan 2023					   *
// *************************************************************************
void WV_App::Say(const char* Message)
{
	char text[1024];
	strcpy_s(text, Message);
	//App->Cl_Dialogs->Message(text);
}

// *************************************************************************
// *						Debug_Text Terry Flanigan					   *
// *************************************************************************
void WV_App::Debug_Text()
{
	//App->Cl_Dialogs->Message("Here");
	MessageBox(App->MainHwnd, "Here", "Debug", MB_OK);
}

// *************************************************************************
// *				Say_Win:- Terry and Hazel Flanigan 2023				   *
// *************************************************************************
void WV_App::Say_Win(const char* Message)
{
	char text[1024];
	strcpy_s(text, Message);
	MessageBox(MainHwnd, Message, "Message", MB_OK);
}

// *************************************************************************
// *				Say_Int:- Terry and Hazel Flanigan 2023				   *
// *************************************************************************
void WV_App::Say_Int(int Value)
{
	char buf[255];
	_itoa_s(Value, buf, 10);
	MessageBox(MainHwnd, buf, "Equity Notice", MB_OK);
}

// *************************************************************************
// *		Custom_Button_Normal:- Terry and Hazel Flanigan 2023   	  	   *
// *************************************************************************
bool WV_App::Custom_Button_Normal(LPNMCUSTOMDRAW item)
{
	{
		if (item->uItemState & CDIS_SELECTED) // Push Down
		{
			//Create pen for button border
			HPEN pen = CreatePen(PS_INSIDEFRAME, 0, RGB(0, 0, 0));

			//Select our brush into hDC
			HGDIOBJ old_pen = SelectObject(item->hdc, pen);
			HGDIOBJ old_brush = SelectObject(item->hdc, App->Brush_But_Pressed);

			RoundRect(item->hdc, item->rc.left, item->rc.top, item->rc.right, item->rc.bottom, 1, 1);

			//Clean up
			SelectObject(item->hdc, old_pen);
			SelectObject(item->hdc, old_brush);
			DeleteObject(pen);

			return CDRF_DODEFAULT;
		}
		else
		{
			if (item->uItemState & CDIS_HOT) //Our mouse is over the button
			{

				HPEN pen = CreatePen(PS_INSIDEFRAME, 0, RGB(0, 255, 0));

				HGDIOBJ old_pen = SelectObject(item->hdc, pen);
				HGDIOBJ old_brush = SelectObject(item->hdc, App->Brush_But_Hover);

				RoundRect(item->hdc, item->rc.left, item->rc.top, item->rc.right, item->rc.bottom, 1, 1);

				SelectObject(item->hdc, old_pen);
				SelectObject(item->hdc, old_brush);
				DeleteObject(pen);

				return CDRF_DODEFAULT;
			}

			HPEN pen = CreatePen(PS_INSIDEFRAME, 0, RGB(0, 0, 0)); // Idle 

			HGDIOBJ old_pen = SelectObject(item->hdc, pen);
			HGDIOBJ old_brush = SelectObject(item->hdc, App->Brush_But_Normal);

			RoundRect(item->hdc, item->rc.left, item->rc.top, item->rc.right, item->rc.bottom, 1, 1);

			SelectObject(item->hdc, old_pen);
			SelectObject(item->hdc, old_brush);
			DeleteObject(pen);

			return CDRF_DODEFAULT;
		}

		return CDRF_DODEFAULT;
	}

	return CDRF_DODEFAULT;
}
// *************************************************************************
// *	Custom_Button_Toggle_Tabs:- Terry and Hazel Flanigan 2023 		   *
// *************************************************************************
bool WV_App::Custom_Button_Toggle_Tabs(LPNMCUSTOMDRAW item, bool Toggle)
{
	static HBRUSH defaultbrush = NULL;
	static HBRUSH hotbrush = NULL;
	static HBRUSH selectbrush = NULL;

	{
		if (item->uItemState & CDIS_HOT) //Our mouse is over the button
		{
			//Select our colour when the mouse hovers our button

			if (Toggle == 1)
			{
				hotbrush = CreateSolidBrush(RGB(0, 255, 0));
			}
			else
			{
				//hotbrush = Brush_Tabs_UnSelected; // Unselected 
				hotbrush = CreateSolidBrush(RGB(240, 240, 240));
			}

			HPEN pen = CreatePen(PS_INSIDEFRAME, 0, RGB(0, 0, 0));

			HGDIOBJ old_pen = SelectObject(item->hdc, pen);
			HGDIOBJ old_brush = SelectObject(item->hdc, hotbrush);

			RoundRect(item->hdc, item->rc.left, item->rc.top, item->rc.right, item->rc.bottom, 5, 5);

			SelectObject(item->hdc, old_pen);
			SelectObject(item->hdc, old_brush);
			DeleteObject(pen);

			return CDRF_DODEFAULT;
		}

		//Select our colour when our button is doing nothing

		if (Toggle == 1)
		{
			defaultbrush = defaultbrush = CreateSolidBrush(RGB(154, 255, 154));
		}
		else
		{
			defaultbrush = CreateSolidBrush(RGB(255, 255, 255)); // Unselected 
		}

		HPEN pen = CreatePen(PS_INSIDEFRAME, 0, RGB(0, 0, 0));

		HGDIOBJ old_pen = SelectObject(item->hdc, pen);
		HGDIOBJ old_brush = SelectObject(item->hdc, defaultbrush);

		RoundRect(item->hdc, item->rc.left, item->rc.top, item->rc.right, item->rc.bottom, 5, 5);

		SelectObject(item->hdc, old_pen);
		SelectObject(item->hdc, old_brush);
		DeleteObject(pen);

		return CDRF_DODEFAULT;
	}

	return CDRF_DODEFAULT;
}
// *************************************************************************
// *		Custom_Button_Toggle:- Terry and Hazel Flanigan 2023  	  	   *
// *************************************************************************
bool WV_App::Custom_Button_Toggle(LPNMCUSTOMDRAW item, bool Toggle)
{
	static HBRUSH defaultbrush = NULL;
	static HBRUSH hotbrush = NULL;
	static HBRUSH selectbrush = NULL;

	{
		if (item->uItemState & CDIS_HOT) //Our mouse is over the button
		{
			//Select our colour when the mouse hovers our button

			if (Toggle == 1)
			{
				hotbrush = CreateSolidBrush(RGB(0, 255, 0));
			}
			else // Unselected
			{
				hotbrush = CreateSolidBrush(RGB(240, 240, 240));//App->Brush_Button_Hover;
			}

			HPEN pen = CreatePen(PS_INSIDEFRAME, 0, RGB(0, 0, 0));

			HGDIOBJ old_pen = SelectObject(item->hdc, pen);
			HGDIOBJ old_brush = SelectObject(item->hdc, hotbrush);

			RoundRect(item->hdc, item->rc.left, item->rc.top, item->rc.right, item->rc.bottom, 5, 5);

			SelectObject(item->hdc, old_pen);
			SelectObject(item->hdc, old_brush);
			DeleteObject(pen);

			return CDRF_DODEFAULT;
		}

		//Select our colour when our button is doing nothing 

		if (Toggle == 1)
		{
			defaultbrush = CreateSolidBrush(RGB(154, 255, 154));
		}
		else // Unselected
		{
			defaultbrush = CreateSolidBrush(RGB(255, 255, 255));
		}

		HPEN pen = CreatePen(PS_INSIDEFRAME, 0, RGB(0, 0, 0));

		HGDIOBJ old_pen = SelectObject(item->hdc, pen);
		HGDIOBJ old_brush = SelectObject(item->hdc, defaultbrush);

		RoundRect(item->hdc, item->rc.left, item->rc.top, item->rc.right, item->rc.bottom, 5, 5);

		SelectObject(item->hdc, old_pen);
		SelectObject(item->hdc, old_brush);
		DeleteObject(pen);

		return CDRF_DODEFAULT;
	}

	return CDRF_DODEFAULT;
}

// *************************************************************************
// *		Custom_Button_Green:- Terry and Hazel Flanigan 2023   	  	   *
// *************************************************************************
bool WV_App::Custom_Button_Green(LPNMCUSTOMDRAW item)
{
	{
		if (item->uItemState & CDIS_SELECTED) // Push Down
		{
			//Create pen for button border
			HPEN pen = CreatePen(PS_INSIDEFRAME, 0, RGB(0, 0, 0));

			//Select our brush into hDC
			HGDIOBJ old_pen = SelectObject(item->hdc, pen);
			HGDIOBJ old_brush = SelectObject(item->hdc, App->Brush_Green);

			RoundRect(item->hdc, item->rc.left, item->rc.top, item->rc.right, item->rc.bottom, 5, 5);

			//Clean up
			SelectObject(item->hdc, old_pen);
			SelectObject(item->hdc, old_brush);
			DeleteObject(pen);

			return CDRF_DODEFAULT;
		}
		else
		{
			if (item->uItemState & CDIS_HOT) //Our mouse is over the button
			{
				HPEN pen = CreatePen(PS_INSIDEFRAME, 0, RGB(0, 0, 0));

				HGDIOBJ old_pen = SelectObject(item->hdc, pen);
				HGDIOBJ old_brush = SelectObject(item->hdc, App->Brush_Green);

				RoundRect(item->hdc, item->rc.left, item->rc.top, item->rc.right, item->rc.bottom, 5, 5);

				SelectObject(item->hdc, old_pen);
				SelectObject(item->hdc, old_brush);
				DeleteObject(pen);

				return CDRF_DODEFAULT;
			}

			HPEN pen = CreatePen(PS_INSIDEFRAME, 0, RGB(0, 0, 0)); // Idle 

			HGDIOBJ old_pen = SelectObject(item->hdc, pen);
			HGDIOBJ old_brush = SelectObject(item->hdc, App->Brush_Green);

			RoundRect(item->hdc, item->rc.left, item->rc.top, item->rc.right, item->rc.bottom, 7, 7);

			SelectObject(item->hdc, old_pen);
			SelectObject(item->hdc, old_brush);
			DeleteObject(pen);
			return CDRF_DODEFAULT;
		}

		return CDRF_DODEFAULT;
	}

	return CDRF_DODEFAULT;
}

// *************************************************************************
// *		Custom_Button_Blue:- Terry and Hazel Flanigan 2023   	  	   *
// *************************************************************************
bool WV_App::Custom_Button_Blue(LPNMCUSTOMDRAW item)
{
	{
		if (item->uItemState & CDIS_SELECTED) // Push Down
		{
			//Create pen for button border
			HPEN pen = CreatePen(PS_INSIDEFRAME, 0, RGB(0, 0, 0));

			//Select our brush into hDC
			HGDIOBJ old_pen = SelectObject(item->hdc, pen);
			HGDIOBJ old_brush = SelectObject(item->hdc, App->Brush_Blue);

			RoundRect(item->hdc, item->rc.left, item->rc.top, item->rc.right, item->rc.bottom, 5, 5);

			//Clean up
			SelectObject(item->hdc, old_pen);
			SelectObject(item->hdc, old_brush);
			DeleteObject(pen);

			return CDRF_DODEFAULT;
		}
		else
		{
			if (item->uItemState & CDIS_HOT) //Our mouse is over the button
			{
				HPEN pen = CreatePen(PS_INSIDEFRAME, 0, RGB(0, 0, 0));

				HGDIOBJ old_pen = SelectObject(item->hdc, pen);
				HGDIOBJ old_brush = SelectObject(item->hdc, App->Brush_Blue);

				RoundRect(item->hdc, item->rc.left, item->rc.top, item->rc.right, item->rc.bottom, 5, 5);

				SelectObject(item->hdc, old_pen);
				SelectObject(item->hdc, old_brush);
				DeleteObject(pen);

				return CDRF_DODEFAULT;
			}

			HPEN pen = CreatePen(PS_INSIDEFRAME, 0, RGB(0, 0, 0)); // Idle 

			HGDIOBJ old_pen = SelectObject(item->hdc, pen);
			HGDIOBJ old_brush = SelectObject(item->hdc, App->Brush_Blue);

			RoundRect(item->hdc, item->rc.left, item->rc.top, item->rc.right, item->rc.bottom, 7, 7);

			SelectObject(item->hdc, old_pen);
			SelectObject(item->hdc, old_brush);
			DeleteObject(pen);

			return CDRF_DODEFAULT;
		}

		return CDRF_DODEFAULT;
	}

	return CDRF_DODEFAULT;
}

// *************************************************************************
// *		Custom_Button_Red:- Terry and Hazel Flanigan 2023   	  	   *
// *************************************************************************
bool WV_App::Custom_Button_Red(LPNMCUSTOMDRAW item)
{
	{
		if (item->uItemState & CDIS_SELECTED) // Push Down
		{
			//Create pen for button border
			HPEN pen = CreatePen(PS_INSIDEFRAME, 0, RGB(0, 0, 0));

			//Select our brush into hDC
			HGDIOBJ old_pen = SelectObject(item->hdc, pen);
			HGDIOBJ old_brush = SelectObject(item->hdc, App->Brush_Red);

			RoundRect(item->hdc, item->rc.left, item->rc.top, item->rc.right, item->rc.bottom, 5, 5);

			//Clean up
			SelectObject(item->hdc, old_pen);
			SelectObject(item->hdc, old_brush);
			DeleteObject(pen);

			return CDRF_DODEFAULT;
		}
		else
		{
			if (item->uItemState & CDIS_HOT) //Our mouse is over the button
			{
				HPEN pen = CreatePen(PS_INSIDEFRAME, 0, RGB(0, 0, 0));

				HGDIOBJ old_pen = SelectObject(item->hdc, pen);
				HGDIOBJ old_brush = SelectObject(item->hdc, App->Brush_Red);

				RoundRect(item->hdc, item->rc.left, item->rc.top, item->rc.right, item->rc.bottom, 5, 5);

				SelectObject(item->hdc, old_pen);
				SelectObject(item->hdc, old_brush);
				DeleteObject(pen);

				return CDRF_DODEFAULT;
			}

			HPEN pen = CreatePen(PS_INSIDEFRAME, 0, RGB(0, 0, 0)); // Idle 

			HGDIOBJ old_pen = SelectObject(item->hdc, pen);
			HGDIOBJ old_brush = SelectObject(item->hdc, App->Brush_Red);

			RoundRect(item->hdc, item->rc.left, item->rc.top, item->rc.right, item->rc.bottom, 7, 7);

			SelectObject(item->hdc, old_pen);
			SelectObject(item->hdc, old_brush);
			DeleteObject(pen);

			return CDRF_DODEFAULT;
		}

		return CDRF_DODEFAULT;
	}

	return CDRF_DODEFAULT;
}

// *************************************************************************
// *			Flash_Window:- Terry and Hazel Flanigan 2022			   *
// *************************************************************************
void WV_App::Flash_Window()
{
	FlashWindow(App->MainHwnd, true);
}


