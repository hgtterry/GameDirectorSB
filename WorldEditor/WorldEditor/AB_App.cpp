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
#include  <stdint.h>


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
	CLSB_Camera_WE =			NULL;
	CLSB_TopTabs =				NULL;
	CLSB_File_WE =				NULL;
	CL_Brush =					NULL;

	CLSB_Export_World =			NULL;

	CL_Main_View =				NULL;

	CL_F_View =					NULL;

	// Scene Builder 
	CLSB_Ogre =					nullptr;
	CLSB_Grid =					nullptr;
	CLSB_Equity =				nullptr;
	CLSB_Keyboard =				nullptr;
	CLSB_Camera_EQ =			nullptr;
	CLSB_Assimp =				nullptr;
	CLSB_Model =				nullptr;
	CLSB_Loader =				nullptr;
	CLSB_Ini =					nullptr;
	CLSB_Export_Ogre3D =		nullptr;
	CLSB_Export_Object =		nullptr;
	CLSB_Exporter =				nullptr;
	CLSB_Textures =				nullptr;
	CLSB_Dialogs =				nullptr;
	CLSB_ImGui =				nullptr;
	CLSB_Genesis3D =			nullptr;
	CLSB_Brushes =				nullptr;
	CLSB_RecentFiles =			nullptr;
	CLSB_TopTabs_Equity =		nullptr;
	CLSB_Dimensions =			nullptr;
	CLSB_Preferences =			nullptr;
	CLSB_Doc =					nullptr;
	CLSB_Panels =				nullptr;
	CLSB_Level =				nullptr;
	CLSB_Scene =				nullptr;
	CLSB_ViewMgrDlg =			nullptr;


	CLSB_Bullet =				nullptr;
	CLSB_Player =				nullptr;

	CLSB_FileView =				nullptr;
	CLSB_Properties =			nullptr;
	CLSB_Object =				nullptr;
	CLSB_Project =				nullptr;
	CLSB_Objects_Create =		nullptr;
	CLSB_Physics =				nullptr;
	CLSB_Environment =			nullptr;
	CLSB_SoundMgr =				nullptr;
	CLSB_Picking =				nullptr;

	AppBackground = NULL;
	BlackBrush =	NULL;
	Brush_White =	NULL;
	Brush_Green =	NULL;
	Brush_Tabs_UnSelected = NULL;
	Brush_Tabs = NULL;

	Font_CB15 = 0;
	Font_CB18 = 0;
	Font_Arial20 = 0;
	Font_Banner = 0;

	Hnd_HollowBox_Bmp = NULL;
	Hnd_SolidBox_Bmp = NULL;
	Hnd_HollowSpheroid_Bmp = NULL;
	Hnd_SolidSpheroid_Bmp = NULL;

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
	Hnd_FullScreen_Bmp = NULL;

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
	Just_Equity = 0;
	Centre_Debug = 1;

	hMenu_WE = NULL;

	MainHwnd = NULL;
	ViewGLhWnd = NULL;
	ListPanel = NULL;

	Equity_Dlg_hWnd = NULL;

	// MFC
	m_pMainFrame = NULL;
	pCFusionDoc = NULL;
	m_pDoc = NULL;

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
// *	  	Get_Current_Document:- Terry and Hazel Flanigan 2023		   *
// *************************************************************************
void SB_App::Get_Current_Document()
{
	m_pDoc = (CFusionDoc*)App->m_pMainFrame->GetCurrentDoc();
	if (m_pDoc == NULL)
	{
		Say("Bad m_pDoc Pointer");
	}
}

// *************************************************************************
// *								InitMFC								   *
// *************************************************************************
void SB_App::InitMFC(void)
{	
	m_pMainFrame = (CMainFrame *)AfxGetMainWnd();
}

#include <ShlObj.h>
//#include <shlobj_core.h>"

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
	CLSB_Camera_WE =				new SB_Camera_WE();
	CLSB_TopTabs =					new SB_TopTabs();
	CLSB_File_WE =					new	SB_File_WE();
	CL_Brush =						new A_Brush();

	CLSB_Export_World =				new SB_Export_World();
	
	CL_Main_View =					new A_MainView();

	CL_F_View =						new F_View();


	// Scene Builder 
	CLSB_Ogre =						new SB_Ogre();
	CLSB_Grid =						new SB_Grid();
	CLSB_Equity =					new SB_Equity();
	CLSB_Keyboard =					new SB_Keyboard();
	CLSB_Camera_EQ =				new SB_Camera_EQ();
	CLSB_Assimp =					new SB_Assimp();
	CLSB_Model =					new SB_Model();
	CLSB_Loader =					new SB_Loader();
	CLSB_Ini =						new SB_Ini();
	CLSB_Export_Ogre3D =			new SB_Export_Ogre3D();
	CLSB_Export_Object =			new SB_Export_Object();
	CLSB_Exporter =					new SB_Exporter();
	CLSB_Textures =					new SB_Textures();
	CLSB_Dialogs =					new SB_Dialogs();
	CLSB_ImGui =					new SB_ImGui();
	CLSB_Genesis3D =				new SB_Genesis3D();
	CLSB_Brushes =					new SB_Brushes();
	CLSB_RecentFiles =				new SB_RecentFiles();
	CLSB_TopTabs_Equity =			new SB_TopTabs_Equity();
	CLSB_Dimensions =				new SB_Dimensions();
	CLSB_Preferences =				new SB_Preferences();
	CLSB_Doc =						new SB_Doc();
	CLSB_Panels =					new	SB_Panels();
	CLSB_Level =					new SB_Level();
	CLSB_Scene =					new SB_Scene();
	CLSB_ViewMgrDlg =				new SB_ViewMgrDlg();
	
	CLSB_Bullet =					new SB_Bullet();
	CLSB_Player =					new SB_Player();

	CLSB_FileView =					new SB_FileView();
	CLSB_Properties =				new SB_Properties;
	CLSB_Object =					new SB_Object();
	CLSB_Project =					new SB_Project();
	CLSB_Objects_Create =			new SB_Objects_Create();
	CLSB_Physics =					new SB_Physics();
	CLSB_Environment =				new SB_Environment();
	CLSB_SoundMgr =					new SB_SoundMgr();
	
	
	InitCommonControls();

	hInst =NULL;
	MainHwnd = NULL;
	
	SetBrushes_Fonts();
	
	char path [MAX_PATH];

	if (SUCCEEDED(SHGetFolderPathA(NULL, CSIDL_APPDATA, NULL, 0, path)))//KF_FLAG_CREATE
	{
		//App->Say(path);
		strcpy(App->CLSB_RecentFiles->UserData_Folder, path);
	}
	else
	{
		App->Say("Can not access user folder");
	}

	
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

	Brush_Tabs = CreateSolidBrush(RGB(255, 255, 255));
	Brush_Tabs_UnSelected = CreateSolidBrush(RGB(240,240,240));

	Brush_But_Normal = CreateSolidBrush(RGB(255, 255, 150));
	Brush_But_Hover = CreateSolidBrush(RGB(255, 255, 230));
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

	Hnd_FullScreen_Bmp = LoadBitmap(hInst, (LPCTSTR)IDB_FULLSCREEN);

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
// *			Beep_Win:- Terry and Hazel Flanigan 2023				   *
// *************************************************************************
void SB_App::Beep_Win()
{
	Beep(440, 100);
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
// *			SB_App::Say_Vector3:- Terry and Hazel Flanigan 2023		   *
// *************************************************************************
void SB_App::Say_Vector3(Ogre::Vector3 Vector)
{
	char buf[255];
	sprintf(buf, "%f %f %f", Vector.x, Vector.y, Vector.z);
	MessageBox(MainHwnd, buf, "Equity Notice", MB_OK);
}

// *************************************************************************
// *			Message_ToFile:- Terry and Hazel Flanigan 2023			   *
// *************************************************************************
void SB_App::Message_ToFile(char* Message, char* Message2)
{
	if (App->Debug_App == 1)
	{
		char text[MAX_PATH];
		strcpy(text, Message);

		if (Message2 == NULL)
		{
			
		}
		else
		{
			strcat(text, " ");
			strcat(text, Message2);
		}

		Ogre::LogManager::getSingleton().setDefaultLog(Ogre::LogManager::getSingleton().getLog("App.log"));
		Ogre::LogManager::getSingleton().logMessage(text);
		Ogre::LogManager::getSingleton().setDefaultLog(Ogre::LogManager::getSingleton().getLog("WWSB.log"));

	}
}

// *************************************************************************
// *			Error_ToFile:- Terry and Hazel Flanigan 2023			   *
// *************************************************************************
void SB_App::Error_ToFile(char* Message, char* Message2)
{
	char text[MAX_PATH];
	char text2[MAX_PATH];
	char OutMessage[MAX_PATH];

	strcpy(text, Message);

	if (Message2 == NULL)
	{
		strcpy(text2," ");
		strcpy(OutMessage, Message);
		strcat(OutMessage, " ");
		strcat(OutMessage, text2);
	}
	else
	{
		strcpy(text2, Message2);
		strcpy(OutMessage, Message);
		strcat(OutMessage, " ");
		strcat(OutMessage, text2);
	}

	Ogre::LogManager::getSingleton().setDefaultLog(Ogre::LogManager::getSingleton().getLog("Error.log"));
	Ogre::LogManager::getSingleton().logMessage(OutMessage);
	Ogre::LogManager::getSingleton().setDefaultLog(Ogre::LogManager::getSingleton().getLog("WWSB.log"));

}

// *************************************************************************
// *			Clear_ErrorLog:- Terry and Hazel Flanigan 2023			   *
// *************************************************************************
void SB_App::Clear_ErrorLog()
{
	/*FILE* fp = NULL;

	char buffer[MAX_PATH];

	char Path[MAX_PATH];
	strcpy(Path, App->WorldEditor_Directory);
	strcat(Path, "Error.log");

	fp = fopen(Path, "w+");
	if (!fp)
	{
		App->Say("Cant Find File", Path);
		return;
	}

	fprintf(fp, "Error File");

	fclose(fp);

	unlink(Path);*/
}

// *************************************************************************
// *				FlashWindow:- Terry and Hazel Flanigan 2023			   *
// *************************************************************************
void SB_App::Flash_Window()
{
	FlashWindow(MainHwnd,true);
}

// *************************************************************************
// *					Custom_Button_Greyed Terry Bernie   		  	   *
// *************************************************************************
bool SB_App::Custom_Button_Greyed(LPNMCUSTOMDRAW item)
{
	HPEN pen = CreatePen(PS_INSIDEFRAME, 0, RGB(0, 0, 255)); // Idle 

	HGDIOBJ old_pen = SelectObject(item->hdc, pen);
	HGDIOBJ old_brush = SelectObject(item->hdc, Brush_Tabs_UnSelected);

	RoundRect(item->hdc, item->rc.left, item->rc.top, item->rc.right, item->rc.bottom, 5, 5);

	SelectObject(item->hdc, old_pen);
	SelectObject(item->hdc, old_brush);
	DeleteObject(pen);

	return CDRF_DODEFAULT;
}

// *************************************************************************
// *					Custom_Button_Normal Terry Bernie   		  	   *
// *************************************************************************
bool SB_App::Custom_Button_Normal(LPNMCUSTOMDRAW item)
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

				HPEN pen = CreatePen(PS_INSIDEFRAME, 0, RGB(0, 255, 0));

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

			RoundRect(item->hdc, item->rc.left, item->rc.top, item->rc.right, item->rc.bottom, 5, 5);

			SelectObject(item->hdc, old_pen);
			SelectObject(item->hdc, old_brush);
			DeleteObject(pen);
			
			return CDRF_DODEFAULT;
		}
	
		return CDRF_DODEFAULT;
}

// *************************************************************************
// *					Custom_Button Terry Bernie   			 	 	   *
// *************************************************************************
bool SB_App::Custom_Button_Toggle(LPNMCUSTOMDRAW item, bool Toggle)
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
bool SB_App::Custom_Button_Toggle_Tabs(LPNMCUSTOMDRAW item, bool Toggle)
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
				hotbrush = hotbrush = CreateSolidBrush(RGB(0, 255, 0));
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
			defaultbrush = CreateSolidBrush(RGB(154, 255, 154));
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
// *			Get_Stack:- Terry and Hazel Flanigan 2023				   *
// *************************************************************************
uint64_t SB_App::Get_Stack(void)
{
	volatile uint8_t var;

	MEMORY_BASIC_INFORMATION mbi;

	auto virtualQuerySuccess = VirtualQuery((LPCVOID)&var, &mbi, sizeof(mbi));

	if (!virtualQuerySuccess)
	{
		Say("Stack Query Failed");
		return 0;
	}

	return &var - mbi.AllocationBase;
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

// *************************************************************************
// *			Start_Dialogs:- Terry and Hazel Flanigan 2023			   *
// *************************************************************************
void SB_App::Start_Dialogs()
{
	CLSB_TopTabs->Start_Headers_Tabs();
	CL_TabsControl->Start_Tabs_Control_Dlg();
	CLSB_ViewMgrDlg->Start_View_MgrDlg();

}

