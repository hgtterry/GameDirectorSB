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

#include "stdafx.h"
#include "resource.h"
#include "ME_App.h"
#include "Shlobj.h"

ME_App::ME_App()
{
	CL_Ogre =		nullptr;
	CL_Utilities =	nullptr;
	CL_Grid =		nullptr;
	CL_ImGui =		nullptr;
	CL_Assimp =		nullptr;
	CL_Import =		nullptr;
	CL_FileIO =		nullptr;
	CL_Model =		nullptr;
	CL_TopBar =		nullptr;
	CL_FileView =	nullptr;
	CL_Groups =		nullptr;
	CL_Panels =		nullptr;
	CL_Textures =	nullptr;
	CL_Dialogs =	nullptr;
	CL_Dimensions = nullptr;

	CL_Export = nullptr;
	CL_Export_Object = nullptr;
	CL_Export_Milk = nullptr;

	CL_Genesis3D = nullptr;
	CL_Ogre3D = nullptr;
	CL_Motions = nullptr;
	CL_Equity_SB = nullptr;
	CL_Prefs = nullptr;
	CL_Ini = nullptr;
	CL_Export_Ogre3D = nullptr;
	CL_Texture_Lib = nullptr;

	SBC_Dimensions = nullptr;
	//----------------------------------------------
	hInst =			nullptr;

	MainHwnd =		nullptr;
	ViewGLhWnd =	nullptr;
	ListPanel =		nullptr;

	AppBackground = nullptr;
	BlackBrush =	nullptr;
	Brush_White =	nullptr;
	Brush_Green =	nullptr;

	Brush_But_Pressed = nullptr;;
	Brush_But_Normal =	nullptr;;
	Brush_But_Hover =	nullptr;;

	Brush_Tabs = nullptr;
	Brush_Tabs_UnSelected = nullptr;

	mMenu = 0;

	Font_CB15 = 0;
	Font_CB18 = 0;
	Font_Arial20 = 0;

	Hnd_ModelInfo_Bmp = NULL;
	Hnd_ModelInfoOn_Bmp = NULL;
	Hnd_GridOn_Bmp = NULL;
	Hnd_GridOff_Bmp = NULL;
	Hnd_BBOn_Bmp = NULL;
	Hnd_BBOff_Bmp = NULL;
	Hnd_MeshOn_Bmp = NULL;
	Hnd_MeshOff_Bmp = NULL;
	Hnd_HairOn_Bmp = NULL;
	Hnd_HairOff_Bmp = NULL;
	Hnd_TexturesOn_Bmp = NULL;
	Hnd_TexturesOff_Bmp = NULL;
	Hnd_MeshPointsOn_Bmp = NULL;
	Hnd_MeshPointsOff_Bmp = NULL;
	Hnd_BonesOn_Bmp = NULL;
	Hnd_BonesOff_Bmp = NULL;
	Hnd_NormalsOn_Bmp = NULL;
	Hnd_NormalsOff_Bmp = NULL;
	Hnd_LightsOn_Bmp = NULL;
	Hnd_LightsOff_Bmp = NULL;
	Hnd_PlayOff_Bmp = NULL;
	Hnd_PlayOn_Bmp = NULL;
	Hnd_PlayStop_Bmp = NULL;

	EquityDirecory_FullPath[0] = 0;
	Version[0] = 0;
}


ME_App::~ME_App()
{
}

// *************************************************************************
// *						InitApp Inflanite							   *
// *************************************************************************
bool ME_App::InitApp(void)
{
	CL_Ogre =		new ME_Ogre();
	CL_Utilities =	new ME_Utilities();
	CL_Grid =		new ME_Grid();
	CL_ImGui =		new ME_ImGui();
	CL_Assimp =		new ME_Assimp();
	CL_Import =		new ME_Import();
	CL_FileIO =		new ME_FileIO();
	CL_Model =		new ME_Model();
	CL_TopBar =		new ME_TopBar();
	CL_FileView =	new ME_FileView();
	CL_Groups =		new ME_Groups();
	CL_Panels =		new ME_Panels();
	CL_Textures =	new ME_Textures();
	CL_Dialogs =	new ME_Dialogs();
	CL_Dimensions = new ME_Dimensions();

	CL_Export = new ME_Export();
	CL_Export_Object = new ME_Export_Object();
	CL_Export_Milk = new ME_Export_Milkshape();
	CL_Motions = new ME_Motions();
	
	CL_Genesis3D = new ME_Genesis3D();
	CL_Ogre3D = new ME_Ogre3D();
	CL_Equity_SB = new ME_Equity_SB();
	CL_Prefs = new ME_Preferences();
	CL_Ini = new T_Ini();
	CL_Export_Ogre3D = new ME_Export_Ogre3D();
	CL_Texture_Lib = new ME_TextureLib();
	
	SBC_Dimensions = new SB_Dimensions();

	// ----------------------------------------------
	SetBrushes_Fonts();

	LoadString(hInst, IDS_APP_TITLE, Version, 255);

	char Udir[1024];
	wchar_t* path = new wchar_t[128];
	if (SUCCEEDED(SHGetKnownFolderPath(FOLDERID_LocalAppData, 0, NULL, &path)))//KF_FLAG_CREATE
	{
		wsprintf(Udir, "%ls", path);
		CoTaskMemFree(path);
		strcpy(App->CL_FileIO->UserData_Folder, Udir);
	}
	else
	{
		App->Say("Can not access user folder");
	}
	return 1;
}

// *************************************************************************
// *					SetMainWinCentre Inflanite						   *
// *************************************************************************
bool ME_App::SetMainWin_Centre(void)
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
// *				LoadProgramResource  ( Terry Bernie )			  	   *
// *************************************************************************
void ME_App::LoadProgramResource(void)
{

	////	Hnd_PinOff = LoadBitmap(hInst, (LPCTSTR)IDB_PINOFF);
	////	Hnd_PinOn = LoadBitmap(hInst, (LPCTSTR)IDB_PINON);
	//Hnd_FullScreen_Bmp = LoadBitmap(hInst, (LPCTSTR)IDB_FULLSCREEN);
	////	Hnd_FlipWindingOrder = LoadBitmap(hInst, (LPCTSTR)IDB_FLIPWINDINGORDER);

	//Hnd_MouseSensitivity_Bmp = LoadBitmap(hInst, (LPCTSTR)IDB_MOUSESENSITIVITY);
	////	Hnd_Projection_Bmp = LoadBitmap(hInst, (LPCTSTR)IDB_PROJECTION);

	////Hnd_Info_Bmp = LoadBitmap(hInst, (LPCTSTR)IDB_INFO);
	////Hnd_InfoSmall_Bmp = LoadBitmap(hInst, (LPCTSTR)IDB_INFOSMALL);

	Hnd_PlayOff_Bmp = LoadBitmap(App->hInst, (LPCTSTR)IDB_MOTPLAYOFF);
	//Hnd_PlayOn = LoadBitmap(App->hInst, (LPCTSTR)IDB_MOTPLAYON);
	Hnd_PlayStop_Bmp = LoadBitmap(App->hInst, (LPCTSTR)IDB_MOTSTOP);
	//Hnd_StepBack = LoadBitmap(App->hInst, (LPCTSTR)IDB_STEPBACK);
	//Hnd_StepForward = LoadBitmap(App->hInst, (LPCTSTR)IDB_STEPFORWARD);

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

	Hnd_ModelInfo_Bmp = LoadBitmap(hInst, (LPCTSTR)IDB_TB_MODELDATA);
	Hnd_ModelInfoOn_Bmp = LoadBitmap(hInst, (LPCTSTR)IDB_TB_MODELDATAON);
}

// *************************************************************************
// *					SetBrushes_Fonts Inflanite						   *
// *************************************************************************
void ME_App::SetBrushes_Fonts(void)
{
	AppBackground = CreateSolidBrush(RGB(213, 222, 242));

	BlackBrush = CreateSolidBrush(RGB(0, 0, 0));
	Brush_White = CreateSolidBrush(RGB(255, 255, 255));
	Brush_Green = CreateSolidBrush(RGB(0, 255, 0));

	Brush_But_Normal = CreateSolidBrush(RGB(255, 255, 150));
	Brush_But_Hover = CreateSolidBrush(RGB(255, 255, 200));
	Brush_But_Pressed = CreateSolidBrush(RGB(240, 240, 190));

	Brush_Tabs = CreateSolidBrush(RGB(255, 255, 255));
	Brush_Tabs_UnSelected = CreateSolidBrush(RGB(190, 190, 190));

	Font_CB15 = CreateFont(-15, 0, 0, 0, 0, 0, 0, 0, 0, OUT_TT_ONLY_PRECIS, 0, 0, 0, "Courier Black");
	Font_CB18 = CreateFont(-18, 0, 0, 0, 0, 0, 0, 0, 0, OUT_TT_ONLY_PRECIS, 0, 0, 0, "Courier Black");
	Font_Arial20 = CreateFont(-20, 0, 0, 0, 0, 0, 0, 0, 0, OUT_TT_ONLY_PRECIS, 0, 0, 0, "Arial");

}

// *************************************************************************
// *								Say_Win								   *
// *************************************************************************
void ME_App::Say_Win(const char* Message)
{
	char text[1024];
	strcpy(text, Message);
	MessageBox(MainHwnd, Message, "Message", MB_OK);
}

// *************************************************************************
// *								Say_Int								   *
// *************************************************************************
void ME_App::Say_Int(int Value)
{
	char buf[255];
	itoa(Value, buf, 10);
	MessageBox(MainHwnd, buf, "Equity Notice", MB_OK);
}

// *************************************************************************
// *							Say_Float								   *
// *************************************************************************
void ME_App::Say_Float(float Value)
{
	std::string ff;
	char buf[255];
	sprintf(buf, "%f", Value);
	MessageBox(MainHwnd, buf, "Equity Notice", MB_OK);
}

// *************************************************************************
// *									Say								   *
// *************************************************************************
void ME_App::Say(const char* Message)
{
	char text[1024];
	strcpy(text, Message);
	App->CL_Dialogs->Message(text);
}

// *************************************************************************
// *					Custom_Button_Normal Terry Bernie   		  	   *
// *************************************************************************
bool ME_App::Custom_Button_Normal(LPNMCUSTOMDRAW item)
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

			HPEN pen = CreatePen(PS_INSIDEFRAME, 0, RGB(0, 0, 0)); // Idle 

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
}

// *************************************************************************
// *					Custom_Button Terry Bernie   			 	 	   *
// *************************************************************************
bool ME_App::Custom_Button_Toggle(LPNMCUSTOMDRAW item, bool Toggle)
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
				hotbrush = CreateGradientBrush(RGB(0, 240, 0), RGB(0, 240, 0), item);
			}
			else
			{
				hotbrush = CreateGradientBrush(RGB(240, 240, 240), RGB(240, 240, 240), item);;
			}

			HPEN pen = CreatePen(PS_INSIDEFRAME, 0, RGB(0, 0, 0));

			HGDIOBJ old_pen = SelectObject(item->hdc, pen);
			HGDIOBJ old_brush = SelectObject(item->hdc, hotbrush);

			RoundRect(item->hdc, item->rc.left, item->rc.top, item->rc.right, item->rc.bottom, 0, 0);

			SelectObject(item->hdc, old_pen);
			SelectObject(item->hdc, old_brush);
			DeleteObject(pen);

			return CDRF_DODEFAULT;
		}

		//Select our colour when our button is doing nothing

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

		RoundRect(item->hdc, item->rc.left, item->rc.top, item->rc.right, item->rc.bottom, 0, 0);

		SelectObject(item->hdc, old_pen);
		SelectObject(item->hdc, old_brush);
		DeleteObject(pen);

		return CDRF_DODEFAULT;
	}

	return CDRF_DODEFAULT;
}

// *************************************************************************
// *		Custom_Button_Toggle_Tabs Terry Bernie   			 	 	   *
// *************************************************************************
bool ME_App::Custom_Button_Toggle_Tabs(LPNMCUSTOMDRAW item, bool Toggle)
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
				hotbrush = CreateGradientBrush(RGB(240, 240, 240), RGB(240, 240, 240), item);
			}
			else
			{
				//hotbrush = Brush_Tabs_UnSelected; // Unselected 
				hotbrush = CreateGradientBrush(RGB(240, 240, 240), RGB(240, 240, 240), item);;
			}

			HPEN pen = CreatePen(PS_INSIDEFRAME, 0, RGB(240, 240, 240));

			HGDIOBJ old_pen = SelectObject(item->hdc, pen);
			HGDIOBJ old_brush = SelectObject(item->hdc, hotbrush);

			RoundRect(item->hdc, item->rc.left, item->rc.top, item->rc.right, item->rc.bottom, 0, 0);

			SelectObject(item->hdc, old_pen);
			SelectObject(item->hdc, old_brush);
			DeleteObject(pen);

			return CDRF_DODEFAULT;
		}

		//Select our colour when our button is doing nothing

		if (Toggle == 1)
		{
			defaultbrush = App->Brush_Tabs; // Selected
		}
		else
		{
			defaultbrush = Brush_Tabs_UnSelected; // Unselected 
		}

		HPEN pen = CreatePen(PS_INSIDEFRAME, 0, RGB(255, 255, 255));

		HGDIOBJ old_pen = SelectObject(item->hdc, pen);
		HGDIOBJ old_brush = SelectObject(item->hdc, defaultbrush);

		RoundRect(item->hdc, item->rc.left, item->rc.top, item->rc.right, item->rc.bottom, 0, 0);

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
HBRUSH ME_App::CreateGradientBrush(COLORREF top, COLORREF bottom, LPNMCUSTOMDRAW item)
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


