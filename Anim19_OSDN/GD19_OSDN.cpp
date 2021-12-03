/*
Copyright (c) GameDirector 2019 Inflanite Software W.T.Flanigan H.C.Flanigan B.Parkin

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
#include "GD19_OSDN.h"

#define MAX_LOADSTRING 100

// Global Variables:
HINSTANCE hInst;                                // current instance
TCHAR szTitle[MAX_LOADSTRING];                  // The title bar text
TCHAR szWindowClass[MAX_LOADSTRING];            // the main window class name

// Forward declarations of functions included in this code module:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

LRESULT CALLBACK Ogre3D_Proc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);
LRESULT CALLBACK ViewerMain_Proc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);
LRESULT CALLBACK PleaseWait_Proc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);

int Block_Call = 0;
void Close_App();
void StartOgre();

GD19_App *App = NULL;

// *************************************************************************
// *							WinMain HGT Software		  	 		   *
// *************************************************************************
int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPWSTR    lpCmdLine,
	_In_ int       nCmdShow)
{

	InitCommonControls();

	App = new GD19_App();
	_getcwd(App->EquityDirecory_FullPath, 1024);

	App->InitApp();

	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

	// TODO: Place code here.

	// Initialize global strings
	LoadString(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadString(hInstance, IDC_GD19_OSDN, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	// Perform application initialization:
	if (!InitInstance(hInstance, nCmdShow))
	{
		return FALSE;
	}

	App->LoadProgramResource();

	App->mMenu = GetMenu(App->MainHwnd);

//	HBITMAP hBitMap = LoadBitmap(App->hInst, MAKEINTRESOURCE(IDB_FILEINACTIVE));
//	SetMenuItemBitmaps(App->mMenu, ID_WINDOWS_FILEVIEW, MF_BYCOMMAND, 0, hBitMap);

	App->SBC_FileView->Start_FileView();

	App->Cl_Panels->Resize_FileView();

	App->SetMainWinCentre();

	App->SBC_FileView->Init_FileView();

	ShowWindow(App->ListPanel, 1);

	ShowWindow(App->MainHwnd, nCmdShow);
	//ShowWindow(App->MainHwnd, SW_MAXIMIZE);
	UpdateWindow(App->MainHwnd);

	App->Cl_Panels->Move_FileView_Window();
	App->Cl_Panels->Place_GlobalGroups();
	

	App->Cl_Properties->Start_GD_Properties();
	App->CL_Vm_Groups->Start_Groups();
	App->SBC_Physics->Start_Physics_Pannel();

	//App->Cl_Bullet->Start_Physics_Console(); // Atention
	//App->Cl_Panels->MovePhysicsView();

	App->CL_Vm_TopBar->Start_TopBar_Globals();

	App->SBC_Camera->Start_Camera_PropsPanel();
	App->SBC_Player->Start_Player_PropsPanel();
	App->SBC_Aera->Start_Area_PropsPanel();

	//CheckMenuItem(App->mMenu, ID_WINDOW_SHOWFPSSHORT, MF_BYCOMMAND | MF_CHECKED);
	//CheckMenuItem(App->mMenu, ID_GRID_DIVISIONS, MF_BYCOMMAND | MF_CHECKED);

	App->Cl_Bullet->Init_Bullet();
	App->Cl_Scene_Data->Init_Scene();

	App->CL_Vm_FileIO->Init_History();

	App->Cl_Vm_Preferences->Read_Preferences(); // Read Preferences

	App->Set_Main_TitleBar(" ");

	SetTimer(App->MainHwnd, 1, 1, NULL);

	HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_GD19_OSDN));

	MSG msg;

	// Main message loop:
	while (GetMessage(&msg, nullptr, 0, 0))
	{
		if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}

	return (int)msg.wParam;
}

// *************************************************************************
// *						MyRegisterClass HGT Software	  	 		   *
// *************************************************************************
ATOM MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEX wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style = 0;
	wcex.lpfnWndProc = WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance;
	wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_GD19_OSDN));
	wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wcex.lpszMenuName = MAKEINTRESOURCE(IDC_GD19_OSDN);
	wcex.lpszClassName = szWindowClass;
	wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

	return RegisterClassEx(&wcex);
}

// *************************************************************************
// *						InitInstance HGT Software		  	 		   *
// *************************************************************************
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
	App->hInst = hInstance;

	App->MainHwnd = CreateWindow(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
		0, 0, 1200, 800, NULL, NULL, hInstance, NULL);

	App->Fdlg = CreateDialog(App->hInst, (LPCTSTR)IDD_FILEVIEW, App->MainHwnd, (DLGPROC)ViewerMain_Proc);

	int cx = GetSystemMetrics(SM_CXSCREEN);
	int cy = GetSystemMetrics(SM_CYSCREEN);
	MoveWindow(App->Fdlg, 0, 0, cx, cy, TRUE);

	App->ViewGLhWnd = CreateDialog(App->hInst, (LPCTSTR)IDD_VIEWER3D, App->Fdlg, (DLGPROC)Ogre3D_Proc);

	App->Cl19_Ogre->RenderHwnd = App->ViewGLhWnd;

	if (!App->MainHwnd)
	{
		return FALSE;
	}

	//ShowWindow(App->MainHwnd, nCmdShow);
	UpdateWindow(App->MainHwnd);

	return TRUE;
}

// *************************************************************************
// *						WndProc HGT Software			  	 		   *
// *************************************************************************
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_COMMAND:
	{
		int wmId = LOWORD(wParam);
		// Parse the menu selections:
		switch (wmId)
		{

		// Vima 20/3/20

		case ID_TEST_GENERAL:
		{
			App->CL_Vm_ImGui->Reset_Groups = 1;
			/*App->Say(App->ETemp_Folder);
			App->CL_Vm_Textures->CreateDummyTexture();
			App->Say("ok");

			remove(App->ETemp_Folder);*/

			return 1;
		}

		case ID_TEST_PROGRESSBAR:
		{
			if (App->CL_Vm_ImGui->Show_Progress_Bar == 0)
			{
				App->CL_Vm_ImGui->Set_ProgressCount(10501);
				App->CL_Vm_ImGui->Start_ProgressBar();
			}
			else
			{
				App->CL_Vm_ImGui->Stop_ProgressBar();
			}
			return 1;
		}

		case ID_TEST_WRITEPREFERENCES:
		{
			App->Cl_Vm_Preferences->Write_Preferences();
			return 1;
		}

		case ID_OPEN_PROJECT:
		{
			App->Debug_Text();
			return 1;
		}

		case ID_OPEN_SCENE:
		{
			App->Debug_Text();
			return 1;
		}
		
		case ID_NEW_PROJECT:
		{
			App->SBC_Project->Start_Create_Project();
			return 1;
		}

		case ID_NEW_SCENE:
		{
			App->Debug_Text();
			return 1;
		}

		case ID_FILE_QUICKLOAD:
		{
			App->SBC_Project->Load_Scene_Auto();
			return 1;
		}

		case ID_FILE_CLEARLEVEL32869:
		{
			App->SBC_Project->Clear_Level();
			return 1;
		}
		
		// Exporters
	
		//case ID_OGRE3D_TEST:
		//{
		//	//App->CL_Vm_Exporter->Actor_Model();
		//	App->Say("Here");

		//	char Path[1024];
		//	strcpy(Path, App->EquityDirecory_FullPath);;
		//	strcat(Path, "\\");
		//	strcat(Path, "Data");
		//	strcat(Path, "\\");
		//	strcat(Path, "Test.mesh");
		//	App->Say(Path);
		//	App->CL_Vm_Model->CreateMeshFile("Test.mesh");
		//	return 1;
		//}

	
		case ID_FILE_CLEAR:
		{
			App->CL_Vm_Model->Clear_ModelData();
			return 1;
		}

		// Camera Mode
		case ID_MODE_WORLD:
		{
			App->Cl19_Ogre->OgreListener->CameraMode = 0;
			return 1;
		}

		case ID_MODE_MODEL:
		{

			App->Cl19_Ogre->OgreListener->CameraMode = 1;
			return 1;
		}

		case ID_CAMERA_RESET:
		{
			App->SBC_Camera->Reset_View();
			return 1;
		}

		case ID_TOOLS_TEXTURELIB:
		{
			App->CL_Vm_TextLib->Start_TexturePack();
			return 1;
		}

		// ------------------------------------- Debug Physics Draw
		case ID_PHYSICS_DRAWDEBUG:
		{
			if (App->Cl19_Ogre->OgreListener->Dubug_Physics_Draw == 1)
			{
				App->Cl19_Ogre->OgreListener->Dubug_Physics_Draw = 0;
			}
			else
			{
				App->Cl19_Ogre->OgreListener->Dubug_Physics_Draw = 1;
			}

			return 1;
		}

		case ID_PHYSICS_RENDER:
		{
			
				if (App->Cl19_Ogre->BulletListener->Render_Debug_Flag == 1)
				{
					App->Cl19_Ogre->BulletListener->Render_Debug_Flag = 0;
				}
				else
				{
					App->Cl19_Ogre->BulletListener->Render_Debug_Flag = 1;
				}

			return 1;
		}

		// ------------------------------------- Recent Files
		case 5000 + 7: // Top Recent Files 1
		{
			char mFileName[1024];
			strcpy(mFileName, App->CL_Vm_FileIO->mPreviousFiles[7].c_str());
			App->SBC_Import->Reload_FromResentFiles(mFileName);
			return 1;
		}
		case 5000 + 6: // 2
		{
			char mFileName[1024];
			strcpy(mFileName, App->CL_Vm_FileIO->mPreviousFiles[6].c_str());
			App->SBC_Import->Reload_FromResentFiles(mFileName);
			return 1;
		}
		case 5000 + 5: // 3
		{
			char mFileName[1024];
			strcpy(mFileName, App->CL_Vm_FileIO->mPreviousFiles[5].c_str());
			App->SBC_Import->Reload_FromResentFiles(mFileName);
			return 1;
		}
		case 5000 + 4: // 4
		{
			char mFileName[1024];
			strcpy(mFileName, App->CL_Vm_FileIO->mPreviousFiles[4].c_str());
			App->SBC_Import->Reload_FromResentFiles(mFileName);
			return 1;
		}
		case 5000 + 3: // 5
		{
			char mFileName[1024];
			strcpy(mFileName, App->CL_Vm_FileIO->mPreviousFiles[3].c_str());
			App->SBC_Import->Reload_FromResentFiles(mFileName);
			return 1;
		}
		case 5000 + 2: // 6
		{
			char mFileName[1024];
			strcpy(mFileName, App->CL_Vm_FileIO->mPreviousFiles[2].c_str());
			App->SBC_Import->Reload_FromResentFiles(mFileName);
			return 1;
		}
		case 5000 + 1: // 7
		{
			char mFileName[1024];
			strcpy(mFileName, App->CL_Vm_FileIO->mPreviousFiles[1].c_str());
			App->SBC_Import->Reload_FromResentFiles(mFileName);
			return 1;
		}
		case 5000 + 0: // 8
		{
			char mFileName[1024];
			strcpy(mFileName, App->CL_Vm_FileIO->mPreviousFiles[0].c_str());
			App->SBC_Import->Reload_FromResentFiles(mFileName);
			return 1;
		}

		// -----------------------------------------------------
		//------------------------- Menu Camera
		case ID_CAMERA_FOLLOWOBJECT:
		{
			if (App->Cl19_Ogre->OgreListener->FollowPlayer == 1)
			{
				App->Cl19_Ogre->OgreListener->FollowPlayer = 0;
			}
			else
			{
				App->Cl19_Ogre->OgreListener->FollowPlayer = 1;
			}
			return 1;
		}

		case ID_CAMERA_OBJECTPROPERTIES:
		{
			/*if (App->Cl_ImGui->Show_Camera_Object == 1)
			{
				App->Cl_ImGui->Show_Camera_Object = 0;
			}
			else
			{
				App->Cl_ImGui->Show_Camera_Object = 1;
			}*/
			return 1;
		}
		
		//------------------------- Menu Test
		case ID_SETTINGS_TEST:
		{
			/*if (App->Cl_ImGui->Show_ImGui_Preferences == 1)
			{
				App->Cl_ImGui->Show_ImGui_Preferences = 0;
			}
			else
			{
				App->Cl_ImGui->Show_ImGui_Preferences = 1;
			}*/
			return 1;
		}

		case ID_TEST_VIEWLOG:
		{
			if (App->FollowFunctions == 1)
			{
				App->FollowFunctions = 0;
				CheckMenuItem(App->mMenu, ID_TEST_VIEWLOG, MF_BYCOMMAND | MF_UNCHECKED);
			}
			else
			{
				App->FollowFunctions = 1;
				CheckMenuItem(App->mMenu, ID_TEST_VIEWLOG, MF_BYCOMMAND | MF_CHECKED);
			}
			return 1;
		}

		//------------------------- Menu Settings
		case ID_SETTINGS_STARTUP:
		{
			App->Cl_Scene_Data->Dialog_GetUserFile(App->MainHwnd);
			return 1;
		}

		case ID_SETTINGS_PREFERENCES:
		{
			App->Cl_Vm_Preferences->Start_Preferences();
			return 1;
		}

		//------------------------- Add Item
		case ID_ADDITEM_OBJECT:
		{
			App->Cl_Dialogs->YesNo("Add Object", "Do you want to add a new Object now");
			bool Doit = App->Cl_Dialogs->Canceled;
			if (Doit == 0)
			{
				App->Cl_Mesh_Viewer->Mesh_Viewer_Mode = Enums::Mesh_Viewer_Objects; // Objects
				App->Cl_Mesh_Viewer->StartMeshViewer();
				App->Cl_Object_Props->Is_Player = 0; // Mark as Object selected
			}

			return 1;
		}

		/*case ID_ADDITEM_SOUNDS:
		{
			App->CL_Dialogs->YesNo("Add Entity", "Do you want to add a new Sound Entity now");
			bool Doit = App->GDCL_Dialogs->Canceled;
			if (Doit == 0)
			{
				App->CL10_Objects_New->Add_New_SoundEntity();
			}

			return 1;
		}*/

		/*case ID_ADDITEM_MESSAGE:
		{
			App->CL_Dialogs->YesNo("Add Entity", "Do you want to add a new Message Entity now");
			bool Doit = App->GDCL_Dialogs->Canceled;
			if (Doit == 0)
			{
				App->CL10_Objects_New->Add_New_MessageEntity();
			}

			return 1;
		}*/

		/*case ID_ADDITEM_MOVER:
		{
			App->CL_Dialogs->YesNo("Add Entity", "Do you want to add a new Move Entity now");
			bool Doit = App->GDCL_Dialogs->Canceled;
			if (Doit == 0)
			{
				App->CL10_Objects_New->Add_New_MessageEntity();
			}

			return 1;
		}*/

		//case ID_ADDITEM_COLLECTABLES:
		//{
		//	App->CL_Dialogs->YesNo("Add Entity", "Do you want to add a new Collectable Entity now");
		//	bool Doit = App->GDCL_Dialogs->Canceled;
		//	if (Doit == 0)
		//	{
		//		App->GDCL_Mesh_Viewer->Mesh_Viewer_Mode = Enums::Mesh_Viewer_Collectables;
		//		App->GDCL_Mesh_Viewer->StartMeshViewer();
		//		App->GDCL_Object_Props->Is_Player = 0; // Mark as Object selected
		//											   //App->GDCL_Add_NewObject->Add_Collectable_Entity();
		//	}

		//	return 1;
		//}

		/*case ID_ADDITEM_TELEPORTER:
		{
			App->CL_Dialogs->YesNo("Add Entity", "Do you want to add a new Telport Entity now");
			bool Doit = App->GDCL_Dialogs->Canceled;
			if (Doit == 0)
			{
				App->CL10_Objects_New->Add_New_TeleportEntity();
			}

			return 1;
		}*/

		//------------------------- Tools
		case ID_TOOLS_SOUNDPLAYER:
		{
			App->Cl_SoundMgr->Dialog_SoundFile();
			return 1;
		}

		case ID_TOOLS_RESOURCEVIEWER:
		{
			App->SBC_Resources->Start_Resources();
			return 1;
		}

		/*case ID_TOOLS_MESHVIEWER:
		{
			App->Cl_Mesh_Viewer->StartMeshViewer();
			return 1;
		}*/

		//------------------------- Mode
		case ID_MODE_FREECAM:
		{
			if (App->SBC_Player->PlayerAdded == 1)
			{
				App->Cl19_Ogre->OgreListener->GD_CameraMode = Enums::CamDetached;
			}
			return 1;
		}

		case ID_MODE_FIRSTPERSON:
		{
			if (App->SBC_Player->PlayerAdded == 1)
			{
				App->Cl19_Ogre->OgreListener->GD_CameraMode = Enums::CamFirst;
			}
			else
			{
				App->Say("No Player in Scene");
			}
			return 1;
		}

		//------------------------- Data
		case ID_DATA_SCENEDATA:
		{
			App->Cl_Dialogs->Start_DataView();
			return 1;
		}
		//------------------------- Menu Windows
		
		
		case ID_WINDOWS_PROPERTIES:
		{

			/*if (App->Cl_ImGui->Show_Propertities == 1)
			{
				App->Cl_ImGui->Show_Propertities = 0;
				CheckMenuItem(App->mMenu, ID_WINDOWS_PROPERTIES, MF_BYCOMMAND | MF_UNCHECKED);
			}
			else
			{
				App->Cl_ImGui->Show_Propertities = 1;
				CheckMenuItem(App->mMenu, ID_WINDOWS_PROPERTIES, MF_BYCOMMAND | MF_CHECKED);
			}*/

			return 1;
		}

		case ID_WINDOWS_SHOWIMGUIPANELS:
		{

			if (App->Cl19_Ogre->OgreListener->Show_ImGui_Panels == 1)
			{
				App->Cl19_Ogre->OgreListener->Show_ImGui_Panels = 0;
				CheckMenuItem(App->mMenu, ID_WINDOWS_SHOWIMGUIPANELS, MF_BYCOMMAND | MF_UNCHECKED);
			}
			else
			{
				App->Cl19_Ogre->OgreListener->Show_ImGui_Panels = 1;
				CheckMenuItem(App->mMenu, ID_WINDOWS_SHOWIMGUIPANELS, MF_BYCOMMAND | MF_CHECKED);
			}

			return 1;
		}
		case ID_WINDOWS_SHOWPHYSICSPANEL:
		{

			/*if (App->Cl_ImGui->Show_PhysicsConsole == 1)
			{
				App->Cl_ImGui->Show_PhysicsConsole = 0;
				CheckMenuItem(App->mMenu, ID_WINDOWS_SHOWPHYSICSPANEL, MF_BYCOMMAND | MF_UNCHECKED);
			}
			else
			{
				App->Cl_ImGui->Show_PhysicsConsole = 1;
				CheckMenuItem(App->mMenu, ID_WINDOWS_SHOWPHYSICSPANEL, MF_BYCOMMAND | MF_CHECKED);
			}*/

		/*	if (App->Cl_Bullet->Physics_Dlg_Active == 1) // Atention
			{
				App->Cl_Bullet->Physics_Dlg_Active = 0;
				ShowWindow(App->Physics_Console_Hwnd, 0);
				CheckMenuItem(App->mMenu, ID_WINDOWS_SHOWPHYSICSPANEL, MF_BYCOMMAND | MF_UNCHECKED);
			}
			else
			{
				App->Cl_Bullet->Physics_Dlg_Active = 1;
				ShowWindow(App->Physics_Console_Hwnd, 1);
				CheckMenuItem(App->mMenu, ID_WINDOWS_SHOWPHYSICSPANEL, MF_BYCOMMAND | MF_CHECKED);
			}*/
			return 1;
		}

		case ID_WINDOWS_LOG:
		{
			/*if (App->Cl_ImGui->Show_ImGui_Log == 1)
			{
				App->Cl_ImGui->Show_ImGui_Log = 0;
			}
			else
			{
				App->Cl_ImGui->Show_ImGui_Log = 1;
			}*/
			return 1;
		}

		case ID_WINDOWS_NEWFILEVIEW:
		{
			/*if (App->Cl_ImGui->Show_ImGui_FileView == 1)
			{
				App->Cl_ImGui->Show_ImGui_FileView = 0;
			}
			else
			{
				App->Cl_ImGui->Show_ImGui_FileView = 1;
			}*/
			return 1;
		}

		case ID_WINDOWS_DEBUGPROPERTIES:
		{
			/*if (App->Cl_ImGui->Show_Object_Data == 1)
			{
				App->Cl_ImGui->Show_Object_Data = 0;
			}
			else
			{
				App->Cl_ImGui->Show_Object_Data = 1;
			}*/
			return 1;
		}

		case ID_WINDOWS_TESTIMGUI:
		{
			if (App->CL_Vm_ImGui->Show_ImGui_Test == 1)
			{
				App->CL_Vm_ImGui->Show_ImGui_Test = 0;
			}
			else
			{
				App->CL_Vm_ImGui->Show_ImGui_Test = 1;
			}
			return 1;
		}

		case ID_WINDOWS_FPS:
		{

			/*if (App->Cl_ImGui->Show_OgreData == 1)
			{
				App->Cl_ImGui->Show_OgreData = 0;
				CheckMenuItem(App->mMenu, ID_WINDOWS_FPS, MF_BYCOMMAND | MF_UNCHECKED);
			}
			else
			{
				App->Cl_ImGui->Show_OgreData = 1;
				CheckMenuItem(App->mMenu, ID_WINDOWS_FPS, MF_BYCOMMAND | MF_CHECKED);
			}*/
			return 1;
		}

		// File View
		case ID_WINDOWS_FILEVIEW:
		{
			ShowWindow(App->ListPanel, 1);

			if (App->Cl_FileView->FileView_Active == 1)
			{
				App->Cl_FileView->FileView_Active = 0;
				ShowWindow(App->ListPanel, 0);
				CheckMenuItem(App->mMenu, ID_WINDOWS_FILEVIEW, MF_BYCOMMAND | MF_UNCHECKED);
			}
			else
			{
				App->Cl_FileView->FileView_Active = 1;
				ShowWindow(App->ListPanel, 1);
				CheckMenuItem(App->mMenu, ID_WINDOWS_FILEVIEW, MF_BYCOMMAND | MF_CHECKED);
			}
			return 1;
		}

		//------------------------- Menu File
		
		case ID_FILE_SAVELEVELAS:
		{
			App->Cl_Save_Scene->SaveGDScene_40(true);
			return 1;
		}

		case ID_FILE_LOADLEVEL:
		{
			//App->Cl_Load_Scene->OpenScene(true);

			//App->SBC_Import->Bullet_Load_Room("Ogre3D   *.mesh\0*.mesh\0", "Ogre3D");
			App->SBC_Import->Load_Scene("Level   *.SBLevel\0*.SBLevel\0", "Level");
			//strcpy(App->Cl_Vm_Preferences->Pref_Ogre_JustFileName, App->CL_Vm_Model->FileName);
			//strcpy(App->Cl_Vm_Preferences->Pref_Ogre_Path, App->CL_Vm_Model->Model_FolderPath);

			//App->Cl_Vm_Preferences->Write_Preferences();
			//// -----------------------------------------------------

			//App->SBC_Physics->Enable_Physics(1);
			//
			//ShowWindow(App->SBC_Physics->PhysicsPannel_Hwnd, SW_SHOW);

			return 1;
		}

		case IDM_ABOUT:
			DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
			break;
		case IDM_EXIT:
			/*App->CL64_Dialogs->YesNo("Close GameDirector", "Are you sure");
			if (App->GDCL_Dialogs->Canceled == 1)
			{
			break;
			}*/
			if (App->Cl19_Ogre->OgreListener->StopOgre == 0)
			{
				App->Cl19_Ogre->OgreListener->StopOgre = 1;
			}
			PostQuitMessage(0);
			break;
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
		}
	}
	break;
	case WM_PAINT:
	{
		PAINTSTRUCT ps;
		HDC hdc = BeginPaint(hWnd, &ps);
		// TODO: Add any drawing code that uses hdc here...
		EndPaint(hWnd, &ps);
		break;
	}
	
	case WM_MOUSEWHEEL:
	{
		int zDelta = (short)HIWORD(wParam);    // wheel rotation

		if (zDelta > 0)
		{
			App->Cl19_Ogre->OgreListener->Wheel = -1;
		}
		else if (zDelta < 0)
		{
			App->Cl19_Ogre->OgreListener->Wheel = 1;
		}

		return 1;
	}

	case WM_MOVING:
	{
		App->Resize_OgreWin();
		Root::getSingletonPtr()->renderOneFrame();
		return 0;
	}
	
	case WM_SIZE:
	{
		App->Resize_OgreWin();

	}break;

	case WM_CLOSE:
	{

		App->Cl_Dialogs->YesNo("Close GameDirector", "Are you sure");
		if (App->Cl_Dialogs->Canceled == 1)
		{
			break;
		}

		if (App->Cl19_Ogre->OgreListener->StopOgre == 0)
		{
			App->Cl19_Ogre->OgreListener->StopOgre = 1;
		}

		PostQuitMessage(0);
		break;
	}

	case WM_TIMER:
		if (wParam == 1)
		{
			if (App->OgreStarted == 0)
			{
				if (Block_Call == 0)
				{
					Block_Call = 1;
					StartOgre();
				}
			}

			if (App->OgreStarted == 1 && App->Start_Scene_Loaded == 0)
			{
				App->Start_Scene_Loaded = 1;
				//App->Cl_Scene_Data->Start_Scene();

				// Check
				//App->Cl_Scene_Data->Cl_Object[1]->bt_body->setLinearVelocity(btVector3(35,0,35));
				//App->Cl19_Ogre->OgreListener->_desiredVelocity = App->Cl_Scene_Data->Cl_Object[1]->bt_body->getLinearVelocity().length();
			}

			//// Render behind windows
			if (App->RenderBackGround == 1 && App->OgreStarted == 1)
			{
				Ogre::Root::getSingletonPtr()->renderOneFrame();
			}
			break;
		}
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}

// *************************************************************************
// *					Ogre3D_Proc Terry Bernie 						   *
// *************************************************************************
LRESULT CALLBACK Ogre3D_Proc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{

	case WM_INITDIALOG: // Bernie as the dialog is created
	{
		App->ViewPLeaseWait = CreateDialog(App->hInst, (LPCTSTR)IDD_PLEASEWAIT, App->Fdlg, (DLGPROC)PleaseWait_Proc);
		return TRUE;
	}

	case WM_CTLCOLORDLG:
	{
		if (App->OgreStarted == 0)
		{
			return (LONG)App->BlackBrush;
		}
	}
	case WM_MOUSEWHEEL:
	{
		if (App->FullScreen == 1)
		{
			int zDelta = (short)HIWORD(wParam);    // wheel rotation

			if (zDelta > 0)
			{
				App->Cl19_Ogre->OgreListener->Wheel = -1;
			}
			else if (zDelta < 0)
			{
				App->Cl19_Ogre->OgreListener->Wheel = 1;
			}
			return 1;
		}
	}

	case WM_MOUSEMOVE: // ok up and running and we have a loop for mouse
	{
		POINT p;

		App->Cl19_Ogre->m_imgui.mouseMoved();
		
		
		if (GetCursorPos(&p) && App->OgreStarted == 1)// && App->CL10_Dimensions->Mouse_Move_Mode == Enums::Edit_Mouse_None)
		{
			if (ScreenToClient(App->ViewGLhWnd, &p))
			{
				RECT rc;
				GetClientRect(App->ViewGLhWnd, &rc);
				int width = rc.right - rc.left;
				int height = rc.bottom - rc.top;

				float tx = (width / 2) - (float)p.x;
			}
		}

		SetFocus(App->ViewGLhWnd);
		break;
	}
	// Right Mouse Button
	case WM_RBUTTONDOWN: // BERNIE_HEAR_FIRE 
	{
		App->Cl19_Ogre->m_imgui.mousePressed();

		if (ImGui::GetIO().WantCaptureMouse)
		{
			//App->Cl_FileView_V2->RightMouseDown = 1;
		}

		if (!ImGui::GetIO().WantCaptureMouse)
		{
			if (App->OgreStarted == 1)
			{
				
				SetCapture(App->ViewGLhWnd);// Bernie
				SetCursorPos(500, 500);
				App->Cl19_Ogre->OgreListener->Pl_RightMouseDown = 1;
				App->CUR = SetCursor(NULL);
				return 1;
			}
		}
		return 1;
	}
	case WM_RBUTTONUP:
	{
		App->Cl19_Ogre->m_imgui.mouseReleased();
		
		if (App->OgreStarted == 1)
		{
			ReleaseCapture();
			App->Cl19_Ogre->OgreListener->Pl_RightMouseDown = 0;
			SetCursor(App->CUR);
			return 1;
		}

		return 1;
	}
	// Left Mouse Button
	case WM_LBUTTONDOWN: // BERNIE_HEAR_FIRE 
	{
		App->Cl19_Ogre->m_imgui.mousePressed();

		if (!ImGui::GetIO().WantCaptureMouse)
		{

			{
				
				if (App->OgreStarted == 1)
				{
					if (!ImGui::GetIO().WantCaptureMouse)
					{
						SetCapture(App->ViewGLhWnd);// Bernie
						SetCursorPos(500, 500);
						App->Cl19_Ogre->OgreListener->Pl_LeftMouseDown = 1;
						App->CUR = SetCursor(NULL);
					}
					else
					{
						App->Cl19_Ogre->OgreListener->Pl_LeftMouseDown = 1;
					}

					return 1;
				}
			}
		}

		return 1;
	}

	case WM_LBUTTONUP:
	{
		App->Cl19_Ogre->m_imgui.mouseReleased();

		if (App->Cl_Scene_Data->S_Flags[0]->GameMode == 0)
		{
			if (App->OgreStarted == 1)
			{
				ReleaseCapture();
				App->Cl19_Ogre->OgreListener->Pl_LeftMouseDown = 0;
				SetCursor(App->CUR);
				return 1;
			}
		}

		return 1;
	}
	case WM_KEYDOWN:
		switch (wParam)
		{
			case 'C':
				if (GetAsyncKeyState(VK_CONTROL))
				{
			//		App->CL10_Objects_Com->Copy_Object();
			//		return 1;
				}
			case 'V':
				if (GetAsyncKeyState(VK_CONTROL))
				{
			//		App->CL10_Objects_Com->Paste_Object();
			//		return 1;
				}
				return 1;
			//	// more keys here
		}break;
	}

	return FALSE;
}

// *************************************************************************
// *					ViewerMain_Proc  (Terry Bernie)					   *
// *************************************************************************
LRESULT CALLBACK ViewerMain_Proc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{

	switch (message)
	{

	case WM_INITDIALOG:
	{
		return TRUE;
	}

	case WM_CTLCOLORDLG:
	{
		return (LONG)App->AppBackground;
	}
	case WM_COMMAND:
	{

	}
	break;
	}
	return FALSE;
}

// *************************************************************************
// *					PleaseWait_Proc Terry Bernie 					   *
// *************************************************************************
LRESULT CALLBACK PleaseWait_Proc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{

	case WM_INITDIALOG: // Bernie as the dialog is created
	{
		HFONT Font;
		Font = CreateFont(-15, 0, 0, 0, FW_BOLD, 0, 0, 0, 0, OUT_TT_ONLY_PRECIS, 0, 0, 0, "Aerial Black");
		SendDlgItemMessage(hDlg, IDC_STWAIT, WM_SETFONT, (WPARAM)Font, MAKELPARAM(TRUE, 0));

		return TRUE;
	}

	case WM_CTLCOLORDLG:
	{
		return (LONG)App->BlackBrush;
	}

	break;
	case WM_CTLCOLORSTATIC:
	{
		if (GetDlgItem(hDlg, IDC_STWAIT) == (HWND)lParam)
		{
			SetBkColor((HDC)wParam, RGB(0, 255, 0));
			SetTextColor((HDC)wParam, RGB(0, 255, 0));
			SetBkMode((HDC)wParam, TRANSPARENT);
			return (UINT)App->BlackBrush;
		}
		return FALSE;
	}
	}
	return FALSE;
}

// *************************************************************************
// *							About Terry Bernie			  	 		   *
// *************************************************************************
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
	{
		HFONT Font;
		HFONT Font1;
		HFONT Font2;
		Font = CreateFont(-17, 0, 0, 0, FW_BOLD, 0, 0, 0, 0, OUT_TT_ONLY_PRECIS, 0, 0, 0, "Aerial Black");
		Font1 = CreateFont(-30, 0, 0, 0, FW_BOLD, 0, 0, 0, 0, OUT_TT_ONLY_PRECIS, 0, 0, 0, "Aerial Black");
		Font2 = CreateFont(-20, 0, 0, 0, FW_BOLD, 0, 0, 0, 0, OUT_TT_ONLY_PRECIS, 0, 0, 0, "Aerial Black");

		SendDlgItemMessage(hDlg, IDC_STNAME, WM_SETFONT, (WPARAM)Font1, MAKELPARAM(TRUE, 0));
		SendDlgItemMessage(hDlg, IDC_STCOPYRIGHT, WM_SETFONT, (WPARAM)Font, MAKELPARAM(TRUE, 0));
		SendDlgItemMessage(hDlg, IDC_LISTABOUT, WM_SETFONT, (WPARAM)Font, MAKELPARAM(TRUE, 0));

		SendDlgItemMessage(hDlg, IDC_STPROGRAMER, WM_SETFONT, (WPARAM)Font2, MAKELPARAM(TRUE, 0));
		SendDlgItemMessage(hDlg, IDC_STGRAPHICS, WM_SETFONT, (WPARAM)Font2, MAKELPARAM(TRUE, 0));

		SendDlgItemMessage(hDlg, IDC_STTHANKS, WM_SETFONT, (WPARAM)Font, MAKELPARAM(TRUE, 0));
		SendDlgItemMessage(hDlg, IDC_ST10, WM_SETFONT, (WPARAM)Font, MAKELPARAM(TRUE, 0));

		SetDlgItemText(hDlg, IDC_STNAME, App->Version);

		char buff[255];

		SendDlgItemMessage(hDlg, IDC_LISTABOUT, LB_ADDSTRING, (WPARAM)0, (LPARAM)" ");
		
		sprintf(buff, "%s  %s", " Ogre Version ", "1.9");
		SendDlgItemMessage(hDlg, IDC_LISTABOUT, LB_ADDSTRING, (WPARAM)0, (LPARAM)buff);

		sprintf(buff, "%s  %s", " Bullet Version ", "2.86");
		SendDlgItemMessage(hDlg, IDC_LISTABOUT, LB_ADDSTRING, (WPARAM)0, (LPARAM)buff);
		
		sprintf(buff, "%s  %s", " ImGui ", ImGui::GetVersion());
		SendDlgItemMessage(hDlg, IDC_LISTABOUT, LB_ADDSTRING, (WPARAM)0, (LPARAM)buff);
		
		SendDlgItemMessage(hDlg, IDC_LISTABOUT, LB_ADDSTRING, (WPARAM)0, (LPARAM)" "); // Space
		App->Cl19_Ogre->GetVersion(buff);
		SendDlgItemMessage(hDlg, IDC_LISTABOUT, LB_ADDSTRING, (WPARAM)0, (LPARAM)buff);

		return (INT_PTR)TRUE;
	}

	case WM_CTLCOLORSTATIC:
	{
		if (GetDlgItem(hDlg, IDC_STNAME) == (HWND)lParam)
		{
			SetBkColor((HDC)wParam, RGB(0, 255, 0));
			SetTextColor((HDC)wParam, RGB(0, 0, 255));
			SetBkMode((HDC)wParam, TRANSPARENT);
			return (UINT)App->AppBackground;
		}
		if (GetDlgItem(hDlg, IDC_STCOPYRIGHT) == (HWND)lParam)
		{
			SetBkColor((HDC)wParam, RGB(0, 255, 0));
			SetTextColor((HDC)wParam, RGB(0, 0, 255));
			SetBkMode((HDC)wParam, TRANSPARENT);
			return (UINT)App->AppBackground;
		}

		if (GetDlgItem(hDlg, IDC_STPROGRAMER) == (HWND)lParam)
		{
			SetBkColor((HDC)wParam, RGB(0, 255, 0));
			SetTextColor((HDC)wParam, RGB(0, 0, 0));
			SetBkMode((HDC)wParam, TRANSPARENT);
			return (UINT)App->AppBackground;
		}

		if (GetDlgItem(hDlg, IDC_STGRAPHICS) == (HWND)lParam)
		{
			SetBkColor((HDC)wParam, RGB(0, 255, 0));
			SetTextColor((HDC)wParam, RGB(0, 0, 0));
			SetBkMode((HDC)wParam, TRANSPARENT);
			return (UINT)App->AppBackground;
		}

		if (GetDlgItem(hDlg, IDC_STTHANKS) == (HWND)lParam)
		{
			SetBkColor((HDC)wParam, RGB(0, 255, 0));
			SetTextColor((HDC)wParam, RGB(0, 0, 0));
			SetBkMode((HDC)wParam, TRANSPARENT);
			return (UINT)App->AppBackground;
		}

		if (GetDlgItem(hDlg, IDC_ST10) == (HWND)lParam)
		{
			SetBkColor((HDC)wParam, RGB(0, 255, 0));
			SetTextColor((HDC)wParam, RGB(0, 0, 0));
			SetBkMode((HDC)wParam, TRANSPARENT);
			return (UINT)App->AppBackground;
		}
		return FALSE;
	}
	case WM_CTLCOLORDLG:
	{
		return (LONG)App->AppBackground;
	}

	case WM_NOTIFY:
	{
		LPNMHDR some_item = (LPNMHDR)lParam;

		if (some_item->idFrom == IDOK && some_item->code == NM_CUSTOMDRAW)
		{
			LPNMCUSTOMDRAW item = (LPNMCUSTOMDRAW)some_item;
			App->Custom_Button_Normal(item);
			return CDRF_DODEFAULT;
		}

		return CDRF_DODEFAULT;
	}

	case WM_COMMAND:
		if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
		{
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		break;
	}
	return (INT_PTR)FALSE;
}

// *************************************************************************
// *						StartOgre Terry Bernie			  	 		   *
// *************************************************************************
void StartOgre()
{
	App->Cl19_Ogre->InitOgre();

	Ogre::Root::getSingletonPtr()->renderOneFrame();
	EndDialog(App->ViewPLeaseWait, LOWORD(0));

	App->OgreStarted = 1;

	//App->Resize_OgreWin();

	App->Cl19_Ogre->mRoot->startRendering();

	Close_App();

	SystemParametersInfo(SPI_SETSCREENSAVEACTIVE, TRUE, NULL, TRUE);
	PostQuitMessage(0);
}

// *************************************************************************
// *						Close_App Terry Bernie			  	 		   *
// *************************************************************************
void Close_App()
{
	App->CL_Vm_Model->Clear_ModelData();

	//App->Say("Exit");

	if (App->Cl19_Ogre->mRoot)
	{
		delete App->Cl19_Ogre->mRoot;
		App->Cl19_Ogre->mRoot = NULL;
	}

	ImGui::DestroyContext();
}