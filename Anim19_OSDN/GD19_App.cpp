/*
Copyright (c) Vima19 Inflanite Software W.T.Flanigan H.C.Flanigan

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

#include "StdAfx.h"
#include "resource.h"
#include "GD19_App.h"

GD19_App::GD19_App(void)
{
	Cl19_Ogre =			nullptr;
	Cl_Utilities =		nullptr;
	Cl_Grid =			nullptr;
	Cl_FileView =		nullptr;

	Cl_FileView_V2 =	nullptr;

	Cl_Panels =			nullptr;
	Cl_Load_Scene =		nullptr;
	Cl_Save_Scene =		nullptr;
	Cl_File_IO =		nullptr;
	Cl_Scene_Data =		nullptr;
	Cl_Bullet =			nullptr;
	Cl_Player =			nullptr;
	Cl_Collision =		nullptr;
	Cl_Ini =			nullptr;
	Cl_SoundMgr =		nullptr;
	Cl_Panels_Com =		nullptr;
	Cl_Resources =		nullptr;
	Cl_Visuals =		nullptr;
	Cl_Objects_New =	nullptr;
	Cl_Environment =	nullptr;
	Cl_Dialogs =		nullptr;
	Cl_Mesh_Viewer =	nullptr;
	Cl_Objects_Com =	nullptr;
	Cl_Dimensions =		nullptr;
	Cl_Properties =		nullptr;
	Cl_Object_Props =	nullptr;
	Cl_Stock =			nullptr;
	Cl_LookUps =		nullptr;
	Cl_ToolBar =		nullptr;
	Cl_Objects_FFile =	nullptr;
	Cl_spdlog =			nullptr;
	Cl_ImGui =			nullptr;
	Cl_Project =		nullptr;
	Cl_File_Data =		nullptr;
	Cl_Keyboard =		nullptr;


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
//	BannerBrush = 0;
	Brush_Blue = 0;
	Brush_White = 0;
	Brush_Green = 0;
	Brush_But_Normal = 0;
	Brush_But_Hover = 0;
	Brush_But_Pressed = 0;
	Brush_Red = 0;
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

	Font_CB12 = 0;
	Font_CB15 = 0;
	Font_Arial20 = 0;

	ViewGLhWnd = nullptr;
	ViewPLeaseWait = nullptr;
	GD_Properties_Hwnd = nullptr;
	Physics_Console_Hwnd = nullptr;

	OgreStarted = 0;
	Start_Scene_Loaded = 0;
	FullScreen = 0;
	FullScreen_App = 0;
	RenderBackGround = 0;

	FollowFunctions = 0;


	EquityDirecory_FullPath[0] = 0;
}

GD19_App::~GD19_App(void)
{
}

// *************************************************************************
// *						InitApp Inflanite							   *
// *************************************************************************
bool GD19_App::InitApp(void)
{
	Cl19_Ogre =			new GD19_Ogre();
	Cl_Utilities =		new GD19_Utilities();
	Cl_Grid =			new GD19_Grid();
	Cl_FileView =		new GD19_FileView();

	Cl_FileView_V2 =	new GD19_FileView_V2();

	Cl_Panels =			new GD19_Panels();
	Cl_Load_Scene =		new GD19_Load_Scene();
	Cl_Save_Scene =		new GD19_Save_Scene();
	Cl_File_IO =		new GD19_File_IO();
	Cl_Scene_Data =		new GD19_Scene_Data();
	Cl_Bullet =			new GD19_Bullet();		
	Cl_Player =			new GD19_Player();
	Cl_Collision =		new GD19_Collision();
	Cl_Ini =			new T_Ini();
	Cl_SoundMgr =		new GD19_SoundMgr();
	Cl_Panels_Com =		new GD19_Panel_Com();
	Cl_Resources =		new GD19_Resources();
	Cl_Visuals =		new GD19_Visuals();
	Cl_Objects_New =	new GD19_Objects_New();	
	Cl_Environment =	new GD19_Environment();
	Cl_Dialogs =		new GD19_Dialogs();
	Cl_Mesh_Viewer =	new GD19_Mesh_Viewer();
	Cl_Objects_Com =	new GD19_Objects_Com();
	Cl_Dimensions =		new GD19_Dimensions();
	Cl_Properties =		new GD19_Properties();
	Cl_Object_Props =	new GD19_Object_Properties();
	Cl_Stock =			new GD19_Stock();
	Cl_LookUps =		new GD19_LookUps();	
	Cl_ToolBar =		new GD19_ToolBar();
	Cl_Objects_FFile =	new GD19_Objects_FFile();
		
	Cl_spdlog =			new	GD_spdlog();
	Cl_ImGui =			new GD_ImGui();
	Cl_Project =		new GD19_Project();	
	Cl_File_Data =		new GD_File_Data();
	Cl_Keyboard =		new GD_Keyboard();
	
	SetBrushes_Fonts();

	LoadString(hInst, IDS_APP_TITLE, Version, 255);

	//char Udir[1024];
	//wchar_t* path = new wchar_t[128];
	//if (SUCCEEDED(SHGetKnownFolderPath(FOLDERID_LocalAppData, 0, NULL, &path)))//KF_FLAG_CREATE
	//{
	//	wsprintf(Udir, "%ls", path);
	//	CoTaskMemFree(path);
	//	strcpy(UserData_Folder, Udir);
	//}

	//char Udir2[1024];
	//wchar_t* path2 = new wchar_t[128];
	//if (SUCCEEDED(SHGetKnownFolderPath(FOLDERID_Desktop, 0, NULL, &path2)))//KF_FLAG_CREATE
	//{
	//	wsprintf(Udir2, "%ls", path2);
	//	CoTaskMemFree(path2);
	//	strcpy(DeskTop_Folder, Udir2);
	//}

	return 1;
}

// *************************************************************************
// *					SetMainWinCentre Inflanite						   *
// *************************************************************************
bool GD19_App::SetMainWinCentre(void)
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
// *						Resize_OgreWin Inflanite					   *
// *************************************************************************
bool GD19_App::Resize_OgreWin(void)
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
	SetWindowPos(ViewGLhWnd, NULL, 4, 43, NewWidth + 384, NewHeight + 100, SWP_NOZORDER);

	if (App->OgreStarted == 1)
	{
		RECT rect;
		GetClientRect(App->ViewGLhWnd, &rect);

		if ((rect.bottom - rect.top) != 0 && App->Cl19_Ogre->mCamera != 0)
		{
			App->Cl19_Ogre->mWindow->windowMovedOrResized();
			App->Cl19_Ogre->mCamera->setAspectRatio((Ogre::Real)App->Cl19_Ogre->mWindow->getWidth() / (Ogre::Real)App->Cl19_Ogre->mWindow->getHeight());
			App->Cl19_Ogre->mCamera->yaw(Radian(0));
			Root::getSingletonPtr()->renderOneFrame();
		}

		int Width = App->Cl19_Ogre->OgreListener->View_Width;
		int poo = (Width / 2) - 175;

		ImGui::SetWindowPos("Ogre Data", ImVec2(poo, 20));
	}

	App->Cl_Panels->MovePhysicsView();
	App->Cl_Panels->Move_FileView_Window();
	App->Cl_Panels->Place_GlobalGroups();

	return 1;
}

// *************************************************************************
// *						RedrawWindow_Dlg Terry Bernie				   *
// *************************************************************************
void GD19_App::RedrawWindow_Dlg(HWND hDlg)
{
	RedrawWindow(hDlg, NULL, NULL, RDW_INVALIDATE | RDW_UPDATENOW);
}

// *************************************************************************
// *					SetBrushes_Fonts Inflanite						   *
// *************************************************************************
void GD19_App::SetBrushes_Fonts(void)
{
	AppBackground = CreateSolidBrush(RGB(213, 222, 242));
	DialogBackGround = CreateSolidBrush(RGB(208, 230, 252));


	BlackBrush = CreateSolidBrush(RGB(0, 0, 0));

	//BannerBrush = CreateSolidBrush(RGB(200, 200, 0));

	Brush_White = CreateSolidBrush(RGB(255, 255, 255));

	///Brush_Grey = CreateSolidBrush(RGB(223, 223, 223));

	Brush_Red = CreateSolidBrush(RGB(252, 85, 63));
	Brush_Green = CreateSolidBrush(RGB(0, 255, 0));
	Brush_Blue = CreateSolidBrush(RGB(0, 180, 255));

	Brush_But_Normal = CreateSolidBrush(RGB(255, 255, 150));
	Brush_But_Hover = CreateSolidBrush(RGB(255, 255, 200));
	Brush_But_Pressed = CreateSolidBrush(RGB(240, 240, 190));

	Font_CB12 = CreateFont(-12, 0, 0, 0, 0, 0, 0, 0, 0, OUT_TT_ONLY_PRECIS, 0, 0, 0, "Courier Black");
	Font_CB15 = CreateFont(-15, 0, 0, 0, 0, 0, 0, 0, 0, OUT_TT_ONLY_PRECIS, 0, 0, 0, "Courier Black");
	Font_Arial20 = CreateFont(-20, 0, 0, 0, 0, 0, 0, 0, 0, OUT_TT_ONLY_PRECIS, 0, 0, 0, "Arial");
}

// *************************************************************************
// *				LoadProgramResource  ( Terry Bernie )			  	   *
// *************************************************************************
void GD19_App::LoadProgramResource(void)
{

//	Hnd_PinOff = LoadBitmap(hInst, (LPCTSTR)IDB_PINOFF);
//	Hnd_PinOn = LoadBitmap(hInst, (LPCTSTR)IDB_PINON);
	Hnd_FullScreen_Bmp = LoadBitmap(hInst, (LPCTSTR)IDB_FULLSCREEN);
//	Hnd_FlipWindingOrder = LoadBitmap(hInst, (LPCTSTR)IDB_FLIPWINDINGORDER);
	Hnd_ModelInfo_Bmp = LoadBitmap(hInst, (LPCTSTR)IDB_MODELDATA);
	Hnd_MouseSensitivity_Bmp = LoadBitmap(hInst, (LPCTSTR)IDB_MOUSESENSITIVITY);
//	Hnd_Projection_Bmp = LoadBitmap(hInst, (LPCTSTR)IDB_PROJECTION);

	//Hnd_LightsOn_Bmp = LoadBitmap(hInst, (LPCTSTR)IDB_LIGHTON);
	//Hnd_LightsOff_Bmp = LoadBitmap(hInst, (LPCTSTR)IDB_LIGHTOFF);

	//Hnd_BBOn_Bmp = LoadBitmap(hInst, (LPCTSTR)IDB_BONDINGBOXON);
	//Hnd_BBOff_Bmp = LoadBitmap(hInst, (LPCTSTR)IDB_BONDINGBOXOFF);

	//Hnd_NormalsOn_Bmp = LoadBitmap(hInst, (LPCTSTR)IDB_NORMALSON);
	//Hnd_NormalsOff_Bmp = LoadBitmap(hInst, (LPCTSTR)IDB_NORMALSOFF);

	//Hnd_BonesOn_Bmp = LoadBitmap(hInst, (LPCTSTR)IDB_BONESON);
	//Hnd_BonesOff_Bmp = LoadBitmap(hInst, (LPCTSTR)IDB_BONESOFF);

	//Hnd_MeshPointsOn_Bmp = LoadBitmap(hInst, (LPCTSTR)IDB_MESHPOINTSON);
	//Hnd_MeshPointsOff_Bmp = LoadBitmap(hInst, (LPCTSTR)IDB_MESHPOINTSOFF);

	//Hnd_MeshOn_Bmp = LoadBitmap(hInst, (LPCTSTR)IDB_MESHON);
	//Hnd_MeshOff_Bmp = LoadBitmap(hInst, (LPCTSTR)IDB_MESHOFF);

	//Hnd_TexturesOn_Bmp = LoadBitmap(hInst, (LPCTSTR)IDB_TEXTURESON);
	//Hnd_TexturesOff_Bmp = LoadBitmap(hInst, (LPCTSTR)IDB_TEXTURESOFF);
	//Hnd_Info_Bmp = LoadBitmap(hInst, (LPCTSTR)IDB_INFO);
	//Hnd_InfoSmall_Bmp = LoadBitmap(hInst, (LPCTSTR)IDB_INFOSMALL);

}

// *************************************************************************
// *	  				SetTitleBar Inflanite							   *
// *************************************************************************
void GD19_App::SetTitleBar(HWND hDlg)
{
	char TitleBar[260];
	strcpy(TitleBar, App->Version);
	SetWindowText(hDlg, TitleBar);
}

// *************************************************************************
// *						GetPriority_Class							   *
// *************************************************************************
void GD19_App::GetPriority_Class()
{
	/*DWORD dwError, dwPriClass;

	SetThreadPriorityBoost(GetCurrentThread(), true);

	dwPriClass = GetThreadPriority(GetCurrentThread());

	char buff[255];
	sprintf(buff, "Current thread priority is 0x%x", dwPriClass);

	App->Say(buff);*/
}

// *************************************************************************
// *									Say								   *
// *************************************************************************
void GD19_App::Say(const char* Message)
{
	char text[1024];
	strcpy(text, Message);
	App->Cl_Dialogs->Message(text);
}

// *************************************************************************
// *								Say_Int								   *
// *************************************************************************
void GD19_App::Say_Int(int Value)
{
	char buf[255];
	_itoa(Value, buf, 10);
	MessageBox(MainHwnd, buf, "Equity Notice", MB_OK);
}

// *************************************************************************
// *					Custom_Button_Normal Terry Bernie   		  	   *
// *************************************************************************
bool GD19_App::Custom_Button_Normal(LPNMCUSTOMDRAW item)
{
	{
		if (item->uItemState & CDIS_SELECTED) // Push Down
		{
			//Create pen for button border
			HPEN pen = CreatePen(PS_INSIDEFRAME, 0, RGB(0, 0, 0));

			//Select our brush into hDC
			HGDIOBJ old_pen = SelectObject(item->hdc, pen);
			HGDIOBJ old_brush = SelectObject(item->hdc, App->Brush_But_Pressed);

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
				HGDIOBJ old_brush = SelectObject(item->hdc, App->Brush_But_Hover);

				RoundRect(item->hdc, item->rc.left, item->rc.top, item->rc.right, item->rc.bottom, 5, 5);

				SelectObject(item->hdc, old_pen);
				SelectObject(item->hdc, old_brush);
				DeleteObject(pen);

				return CDRF_DODEFAULT;
			}

			HPEN pen = CreatePen(PS_INSIDEFRAME, 0, RGB(0, 0, 0)); // Idel 

			HGDIOBJ old_pen = SelectObject(item->hdc, pen);
			HGDIOBJ old_brush = SelectObject(item->hdc, App->Brush_But_Normal);

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
// *					Custom_Button Terry Bernie   			 	 	   *
// *************************************************************************
bool GD19_App::Custom_Button_Toggle(LPNMCUSTOMDRAW item, bool Toggle)
{
	static HBRUSH defaultbrush = NULL;
	static HBRUSH hotbrush = NULL;
	static HBRUSH selectbrush = NULL;

	{
		if (item->uItemState & CDIS_HOT) //Our mouse is over the button
		{
			//Select our color when the mouse hovers our button

			if (Toggle == 1)
			{
				hotbrush = CreateGradientBrush(RGB(0, 240, 0), RGB(0, 240, 0), item);
			}
			else
			{
				hotbrush = CreateGradientBrush(RGB(240, 240, 240), RGB(240, 240, 240), item);;
			}

			HPEN pen = CreatePen(PS_INSIDEFRAME, 0, RGB(0, 0, 0));

			HGDIOBJ old_pen = SelectObject(item->hdc, pen);
			HGDIOBJ old_brush = SelectObject(item->hdc, hotbrush);

			RoundRect(item->hdc, item->rc.left, item->rc.top, item->rc.right, item->rc.bottom, 7, 7);

			SelectObject(item->hdc, old_pen);
			SelectObject(item->hdc, old_brush);
			DeleteObject(pen);

			return CDRF_DODEFAULT;
		}

		//Select our color when our button is doing nothing

		if (Toggle == 1)
		{
			defaultbrush = App->Brush_Green;
		}
		else
		{
			defaultbrush = App->Brush_White;
		}

		HPEN pen = CreatePen(PS_INSIDEFRAME, 0, RGB(0, 0, 0));

		HGDIOBJ old_pen = SelectObject(item->hdc, pen);
		HGDIOBJ old_brush = SelectObject(item->hdc, defaultbrush);

		RoundRect(item->hdc, item->rc.left, item->rc.top, item->rc.right, item->rc.bottom, 7, 7);

		SelectObject(item->hdc, old_pen);
		SelectObject(item->hdc, old_brush);
		DeleteObject(pen);

		return CDRF_DODEFAULT;
	}

	return CDRF_DODEFAULT;
}

// *************************************************************************
// *						CreateGradientBrush					 	 	   *
// *************************************************************************
HBRUSH GD19_App::CreateGradientBrush(COLORREF top, COLORREF bottom, LPNMCUSTOMDRAW item)
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
// *					Custom_Button_Green Terry Bernie   			  	   *
// *************************************************************************
bool GD19_App::Custom_Button_Green(LPNMCUSTOMDRAW item)
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

			HPEN pen = CreatePen(PS_INSIDEFRAME, 0, RGB(0, 0, 0)); // Idel 

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
// *					Custom_Button_Blue Terry Bernie   			  	   *
// *************************************************************************
bool GD19_App::Custom_Button_Blue(LPNMCUSTOMDRAW item)
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

			HPEN pen = CreatePen(PS_INSIDEFRAME, 0, RGB(0, 0, 0)); // Idel 

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
// *					Custom_Button_Red Terry Bernie   			  	   *
// *************************************************************************
bool GD19_App::Custom_Button_Red(LPNMCUSTOMDRAW item)
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

			HPEN pen = CreatePen(PS_INSIDEFRAME, 0, RGB(0, 0, 0)); // Idel 

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

