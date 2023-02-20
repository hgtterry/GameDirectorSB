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
	App->SBC_Scene->Zero_Pointers();

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

	CheckMenuItem(App->mMenu, ID_WINDOWS_SHOWPHYSICSPANEL, MF_BYCOMMAND | MF_CHECKED);


	App->SBC_FileView->Start_FileView();
	ShowWindow(App->ListPanel, 0);
	App->SBC_FileView->Init_FileView();
	App->SBC_Panels->Move_FileView_Window();
	App->SBC_Panels->Resize_FileView();


	App->SetMainWinCentre();

	App->SBC_Panels->Place_GlobalGroups();
	

	App->SBC_Properties->Start_GD_Properties();

	App->SBC_TopTabs->Start_TopBar_Globals();

	App->SBC_Com_Camera->Start_Camera_PropsPanel();
	App->SBC_Player->Start_Player_PropsPanel();
	
	App->SBC_Props_Dialog->Start_Props_Dialogs();

	App->SBC_Bullet->Init_Bullet();

	App->SBC_FileIO->Init_History();

	App->SBC_Prefs->Read_Preferences(); // Read Preferences

	App->Set_Main_TitleBar(" ");
	App->SBC_FileView->SelectItem(App->SBC_FileView->FV_LevelFolder);

	CheckMenuItem(App->mMenu, ID_WINDOWS_FPS, MF_BYCOMMAND | MF_CHECKED);
	EnableMenuItem(App->mMenu, ID_FILE_SAVEPROJECTALL, MF_GRAYED);


	if (App->SBC_Prefs->Prefs_FullScreen_Flag == 1)
	{
		ShowWindow(App->MainHwnd, SW_MAXIMIZE);
	}
	else
	{
		ShowWindow(App->MainHwnd, SW_SHOWNORMAL);
	}

	ShowWindow(App->ListPanel, 1);
	ShowWindow(App->SBC_Properties->Properties_Dlg_hWnd, 1);

	UpdateWindow(App->MainHwnd);

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

	App->CursorPosX = cx/2;
	App->CursorPosY = cy/2;


	App->ViewGLhWnd = CreateDialog(App->hInst, (LPCTSTR)IDD_VIEWER3D, App->Fdlg, (DLGPROC)Ogre3D_Proc);

	App->SBC_Ogre->RenderHwnd = App->ViewGLhWnd;

	if (!App->MainHwnd)
	{
		return FALSE;
	}

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

		// ---------------------------------------------------------------------- Debug

		case ID_DEBUG_PLAYER:
		{
			if (App->SBC_Gui_Dialogs->Show_Debug_Player == 1)
			{
				App->SBC_Gui_Dialogs->Show_Debug_Player = 0;
			}
			else
			{
				App->SBC_Gui_Dialogs->Show_Debug_Player = 1;
			}
			return 1;
		}

		case ID_TEST_DISABLEDIALOGS:
		{
			App->SBC_Gui_Dialogs->Close_All_Dialogs();

			if (App->Panels_Disabled_Flag == 1)
			{
				App->Panels_Disabled_Flag = 0;
				App->Disable_Panels(false);
			}
			else
			{
				App->Panels_Disabled_Flag = 1;
				App->Disable_Panels(true);
			}
			
			Debug;
			return 1;
		}

		case ID_TEST_HIDEPANELS:
		{
			if (App->Panels_Hidden_Flag == 1)
			{
				App->Panels_Hidden_Flag = 0;
				App->Show_Panels(true);
			}
			else
			{
				App->Panels_Hidden_Flag = 1;
				App->Show_Panels(false);
			}

			return 1;
		}
		
		case ID_DEBUG_SHOWSTARTUP:
		{
			App->SBC_Dialogs->Front_Screen();
			return 1;
		}
		
		case ID_DEBUG_CAMERA:
		{
			if (App->SBC_Debug->Show_Debug_Camera == 1)
			{
				App->SBC_Debug->Show_Debug_Camera = 0;
			}
			else
			{
				App->SBC_Debug->Show_Debug_Camera = 1;
			}
			return 1;
		}

		case ID_DEBUG_RESOURCEFOLDER:
		{
			App->Cl_Dialogs->Start_Gen_ListBox(Enums::ListBox_Resource_Folder);
			return 1;
		}
	
		case ID_DEBUG_COPYRESOURCES:
		{
			char Test[MAX_PATH];
			strcpy(Test,"C:\\Users\\Gen2\\Desktop\\Test\\");

			App->SBC_Project->Copy_Assets(App->SBC_Project->m_Main_Assets_Path, Test);
			return 1;
		}

		case ID_DEBUG_APPRELEASE:
		{
			App->SBC_Dialogs->YesNo("Release GameDirector", "Are you sure", 1);
			if (App->Cl_Dialogs->Canceled == 0)
			{
				char buf[1024];
				strcpy(buf, App->SBC_FileIO->UserData_Folder);
				strcat(buf, "\\Equity\\Equity_SB.ini");

				remove(buf);

				char DirCheck[1024];
				strcpy(DirCheck, App->SBC_FileIO->UserData_Folder);
				strcat(DirCheck, "\\");
				strcat(DirCheck, "Equity");

				RemoveDirectory(DirCheck);

				App->SBC_Prefs->Set_Defaults();

				App->Say("Done");
			}

			return 1;
		}
		
		case ID_DEBUG_MESHVIEWER:
		{
			App->SBC_MeshViewer->Mesh_Viewer_Mode = Enums::Mesh_Viewer_Objects; // 0; // Objects; // Objects
			App->SBC_MeshViewer->StartMeshViewer();
			return 1;
		}
		
		case ID_DEBUG_PROJECT:
		{
			if (App->SBC_Debug->Show_Debug_Project == 1)
			{
				App->SBC_Debug->Show_Debug_Project = 0;
			}
			else
			{
				App->SBC_Debug->Show_Debug_Project = 1;
			}
			return 1;
		}

		case ID_DEBUG_APP32891:
		{
			if (App->CL_Vm_ImGui->Show_App_Data == 1)
			{
				App->CL_Vm_ImGui->Show_App_Data = 0;
			}
			else
			{
				App->CL_Vm_ImGui->Show_App_Data = 1;
			}
			return 1;
		}

		case ID_TEST_PROGRESSBAR:
		{
			if (App->CL_Vm_ImGui->Show_Progress_Bar == 0)
			{
				App->CL_Vm_ImGui->Set_ProgressCount(10501);
				//App->CL_Vm_ImGui->Start_ProgressBar();
			}
			else
			{
				//App->CL_Vm_ImGui->Stop_ProgressBar();
			}
			return 1;
		}

		case ID_TEST_WRITEPREFERENCES:
		{
			App->SBC_Prefs->Write_Preferences();
			return 1;
		}

		case ID_DEBUG_SHOWIMGUIDEMO:
		{
			if (App->SBC_Ogre->OgreListener->Show_DemoWindow == 1)
			{
				App->SBC_Ogre->OgreListener->Show_DemoWindow = 0;
			}
			else
			{
				App->SBC_Ogre->OgreListener->Show_DemoWindow = 1;
			}
			return 1;
		}

		case ID_DEBUG_TESTIMGUIDIALOG:
		{
			Ogre::Entity* GroundEnt = App->SBC_Ogre->mSceneMgr->createEntity("Ground12", "DoorEntity_GD.mesh", App->SBC_Scene->Project_Resource_Group);
			Ogre::SceneNode* groundNode = App->SBC_Ogre->mSceneMgr->getRootSceneNode()->createChildSceneNode();
			groundNode->attachObject(GroundEnt);

			groundNode->setVisible(true);
			groundNode->setPosition(0,0,0);
	

			/*if (App->SBC_Prefs->Show_Preferences_GUI == 0)
			{
				App->SBC_Prefs->Start_Preferences_GUI();
			}
			else
			{
				App->SBC_Prefs->Close_Preferences_GUI();
			}*/

			/*if (App->SBC_Front_Dlg->Show_Front_Dlg_Flag == 0)
			{
				App->SBC_Front_Dlg->Show_Front_Dlg_Flag = 1;
			}
			else
			{
				App->SBC_Front_Dlg->Show_Front_Dlg_Flag = 0;
			}*/

			/*if (App->SBC_Gui_Dialogs->Show_Progress_Bar2 == 0)
			{
				App->SBC_Gui_Dialogs->Start_ProgressBar();
			}
			else
			{
				App->SBC_Gui_Dialogs->Stop_ProgressBar();
			}*/
			
			return 1;
		}

		// ------------------------------------------------------------
		case ID_OPEN_PROJECT:
		{
			App->SBC_Import->Load_Project("Project   *.SBProj\0*.SBProj\0", "Project");
			return 1;
		}

		case ID_EXAMPLES_RF:
		{
			char Test_Project[MAX_PATH];
			strcpy(Test_Project, App->EquityDirecory_FullPath);
			strcat(Test_Project, "\\Projects\\RF_Project_Prj\\Project.SBProj");

			App->SBC_Import->Reload_FromResentFiles(Test_Project);

			return 1;
		}

		case ID_EXAMPLES_TESTPROJECT:
		{
			char Test_Project[MAX_PATH];
			strcpy(Test_Project, App->EquityDirecory_FullPath);
			strcat(Test_Project, "\\Projects\\First_Project_Prj\\Project.SBProj");

			App->SBC_Import->Reload_FromResentFiles(Test_Project);

			return 1;
		}
		
		case ID_IMPORT_ROOM:
		{
			App->SBC_Import_Room->Room_Loader("Ogre3D   *.mesh\0*.mesh\0", "Ogre3D");
			return 1;
		}
		
		// ------------------------------------------------------------
		case ID_NEW_PROJECT:
		{
			App->SBC_Project_Create->Start_New_Project();

			return 1;
		}

		case ID_FILE_CLEARLEVEL32869:
		{
			App->SBC_Scene->Clear_Level();
			return 1;
		}

		case ID_FILE_SAVEPROJECTALL:
		{
			if (App->SBC_Scene->Scene_Loaded == 1)
			{
				App->SBC_Project->Save_All();
			}

			return 1;
		}
		
		case ID_FILE_SAVEPROJECT:
		{
			if (App->SBC_Scene->Scene_Loaded == 1)
			{
				App->SBC_Project->Start_Save_Project_Dialog();
			}

			return 1;
		}
		
		case ID_TOOLS_TEXTURELIB:
		{
			//App->CL_Vm_TextLib->Start_TexturePack();
			return 1;
		}

		// ------------------------------------- Debug Physics Draw
		case ID_PHYSICS_DRAWDEBUG:
		{
			if (App->SBC_Ogre->OgreListener->Dubug_Physics_Draw == 1)
			{
				App->SBC_Ogre->OgreListener->Dubug_Physics_Draw = 0;
			}
			else
			{
				App->SBC_Ogre->OgreListener->Dubug_Physics_Draw = 1;
			}

			return 1;
		}

		case ID_PHYSICS_RENDER:
		{
			
				if (App->SBC_Ogre->BulletListener->Render_Debug_Flag == 1)
				{
					App->SBC_Ogre->BulletListener->Render_Debug_Flag = 0;
				}
				else
				{
					App->SBC_Ogre->BulletListener->Render_Debug_Flag = 1;
				}

			return 1;
		}

		// ------------------------------------- Recent Projects

		case ID_RECENTPROJECTS2_PROJECTS:
		{
			App->SBC_FileIO->Start_RecentProjects_Dlg(0);
			return 1;
		}

		case ID_FILE_CLEARRESENTPROJECTS:
		{
			App->SBC_FileIO->ResentHistory_Clear(0);
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

		case ID_SETTINGS_PREFERENCES:
		{
			if (App->SBC_Prefs->Show_Preferences_GUI == 0)
			{
				App->SBC_Prefs->Start_Preferences_GUI();
			}

			return 1;
		}

		//------------------------- Add Item
		case ID_ADDITEM_OBJECT:
		{
			App->SBC_Dialogs->YesNo("Add Object", "Do you want to add a new Object now",1);
			bool Doit = App->Cl_Dialogs->Canceled;
			if (Doit == 0)
			{
				App->SBC_MeshViewer->Mesh_Viewer_Mode = Enums::Mesh_Viewer_Objects; // Objects
				App->SBC_MeshViewer->StartMeshViewer();
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
		
		case ID_ADDITEM_MESSAGE:
		{
			/*App->SBC_Dialogs->YesNo("Add Entity", "Do you want to add a new Message Entity now");
			bool Doit = App->GDCL_Dialogs->Canceled;
			if (Doit == 0)
			{*/
				App->SBC_Com_Entity->Add_New_Message();
			//}
			
			return 1;
		}

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
			App->SBC_SoundMgr->Dialog_SoundFile();
			return 1;
		}

		case ID_TOOLS_RESOURCEVIEWER:
		{
			App->SBC_Resources->Start_Resources(App->Fdlg);
			return 1;
		}

		case ID_TOOLS_COLOURVIEWER:
		{
			if (App->SBC_Gui_Dialogs->Show_ColourPicker == 1)
			{
				App->SBC_Gui_Dialogs->Show_ColourPicker = 0;
			}
			else
			{
				App->SBC_Gui_Dialogs->Show_ColourPicker = 1;
			}

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
			if (App->SBC_Scene->Player_Added == 1)
			{
				App->SBC_Ogre->OgreListener->GD_CameraMode = Enums::CamDetached;
				App->SBC_TopTabs->Toggle_FirstCam_Flag = 0;
				App->SBC_TopTabs->Toggle_FreeCam_Flag = 1;

				int f = App->SBC_Scene->B_Player[0]->Phys_Body->getCollisionFlags();
				App->SBC_Scene->B_Player[0]->Phys_Body->setCollisionFlags(f & (~(1 << 5)));

				App->SBC_Ogre->BulletListener->Render_Debug_Flag = 0;
				App->SBC_Ogre->RenderFrame();
				App->SBC_Ogre->BulletListener->Render_Debug_Flag = 1;

				RedrawWindow(App->SBC_TopTabs->Camera_TB_hWnd, NULL, NULL, RDW_INVALIDATE | RDW_UPDATENOW);
			}
			return 1;
		}

		case ID_MODE_FIRSTPERSON:
		{
			if (App->SBC_Scene->Player_Added == 1)
			{
				App->SBC_Ogre->OgreListener->GD_CameraMode = Enums::CamFirst;
				App->SBC_TopTabs->Toggle_FirstCam_Flag = 1;
				App->SBC_TopTabs->Toggle_FreeCam_Flag = 0;

				App->SBC_Scene->B_Player[0]->Player_Node->setVisible(false);

				int f = App->SBC_Scene->B_Player[0]->Phys_Body->getCollisionFlags();
				App->SBC_Scene->B_Player[0]->Phys_Body->setCollisionFlags(f | (1 << 5));

				App->SBC_Ogre->BulletListener->Render_Debug_Flag = 0;
				App->SBC_Ogre->RenderFrame();
				App->SBC_Ogre->BulletListener->Render_Debug_Flag = 1;

				App->SBC_Ogre->OgreListener->GD_Run_Physics = 1;

				RedrawWindow(App->SBC_TopTabs->Camera_TB_hWnd, NULL, NULL, RDW_INVALIDATE | RDW_UPDATENOW);
			}
			return 1;
		}

		case ID_MODE_SELECTION:
		{
			if (App->SBC_Scene->Scene_Loaded == 1)
			{
				if (App->SBC_TopTabs->Toggle_Select_Flag == 1)
				{
					App->CL_Vm_ImGui->Show_Object_Selection = 0;

					App->SBC_TopTabs->Toggle_Select_Flag = 0;
					App->SBC_Markers->mPickSight->hide();
					App->SBC_Ogre->OgreListener->GD_Selection_Mode = 0;
				}
				else
				{
					App->SBC_TopTabs->Toggle_Select_Flag = 1;
					App->SBC_Markers->mPickSight->show();
					App->SBC_Ogre->OgreListener->GD_Selection_Mode = 1;
				}

				RedrawWindow(App->SBC_TopTabs->Camera_TB_hWnd, NULL, NULL, RDW_INVALIDATE | RDW_UPDATENOW);
			}

			return 1;
		}

		//------------------------- Menu Windows
		
		
		case ID_WINDOWS_PROPERTIES:
		{

			if (App->SBC_Properties->Properties_Dlg_Active == 1)
			{
				App->SBC_Properties->Properties_Dlg_Active = 0;
				CheckMenuItem(App->mMenu, ID_WINDOWS_PROPERTIES, MF_BYCOMMAND | MF_UNCHECKED);

				ShowWindow(App->SBC_Properties->Properties_Dlg_hWnd, 0);
			}
			else
			{
				App->SBC_Properties->Properties_Dlg_Active = 1;
				CheckMenuItem(App->mMenu, ID_WINDOWS_PROPERTIES, MF_BYCOMMAND | MF_CHECKED);

				ShowWindow(App->SBC_Properties->Properties_Dlg_hWnd, 1);
			}

			return 1;
		}


		case ID_WINDOWS_SHOWPHYSICSPANEL:
		{

			if (App->SBC_Gui_Dialogs->Show_Physics_Console == 1) // Atention
			{
				App->SBC_Gui_Dialogs->Physics_Console_StartPos = 0;
				App->SBC_Gui_Dialogs->Show_Physics_Console = 0;
				CheckMenuItem(App->mMenu, ID_WINDOWS_SHOWPHYSICSPANEL, MF_BYCOMMAND | MF_UNCHECKED);
			}
			else
			{
				App->SBC_Gui_Dialogs->Physics_Console_StartPos = 0;
				App->SBC_Gui_Dialogs->Show_Physics_Console = 1;
				CheckMenuItem(App->mMenu, ID_WINDOWS_SHOWPHYSICSPANEL, MF_BYCOMMAND | MF_CHECKED);
			}
			return 1;
		}

		case ID_WINDOWS_FPS:
		{

			if (App->CL_Vm_ImGui->Show_FPS == 1)
			{
				App->CL_Vm_ImGui->Show_FPS = 0;
				CheckMenuItem(App->mMenu, ID_WINDOWS_FPS, MF_BYCOMMAND | MF_UNCHECKED);
			}
			else
			{
				App->CL_Vm_ImGui->Show_FPS = 1;
				CheckMenuItem(App->mMenu, ID_WINDOWS_FPS, MF_BYCOMMAND | MF_CHECKED);
			}

			return 1;
		}

		// File View
		case ID_WINDOWS_FILEVIEW:
		{
			ShowWindow(App->ListPanel, 1);

			if (App->SBC_FileView->FileView_Active == 1)
			{
				App->SBC_FileView->FileView_Active = 0;
				ShowWindow(App->ListPanel, 0);
				CheckMenuItem(App->mMenu, ID_WINDOWS_FILEVIEW, MF_BYCOMMAND | MF_UNCHECKED);
			}
			else
			{
				App->SBC_FileView->FileView_Active = 1;
				ShowWindow(App->ListPanel, 1);
				CheckMenuItem(App->mMenu, ID_WINDOWS_FILEVIEW, MF_BYCOMMAND | MF_CHECKED);
			}
			return 1;
		}

		case ID_MOUSEANDKEYS:
		{
			App->Cl_Utilities->OpenHTML("Help\\MouseAndKeys.html");
			return 1;
		}

		//------------------------- Menu Help
		
		case ID_HELP_CHANGELOG:
		{
			App->Cl_Utilities->OpenHTML("Help\\ChangeLog.html");
			return 1;
		}

		case ID_HELP_TOADD:
		{
			App->Cl_Utilities->OpenHTML("Help\\todo.html");
			return 1;
		}
		
		case IDM_ABOUT:
			DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
			break;
		case IDM_EXIT:
			if (App->SBC_Scene->Scene_Modified == 1)
			{

				App->SBC_Dialogs->YesNo("Save Scene", "Scene has been Modified Do you wish to save changes", 1);

				bool Doit = App->SBC_Dialogs->Canceled;
				if (Doit == 0)
				{
					App->SBC_Project->Start_Save_Project_Dialog();
				}

			}
			else
			{
				App->SBC_Dialogs->YesNo("Close GameDirector", "Are you sure", 1);

				if (App->SBC_Dialogs->Canceled == 1)
				{
					return 1;
				}
			}

			App->SBC_Gui_Dialogs->Close_All_Dialogs();

			if (App->SBC_Ogre->OgreListener->StopOgre == 0)
			{
				App->SBC_Ogre->OgreListener->StopOgre = 1;
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
			App->SBC_Ogre->OgreListener->Wheel = -1;
		}
		else if (zDelta < 0)
		{
			App->SBC_Ogre->OgreListener->Wheel = 1;
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
		if (App->SBC_Scene->Scene_Modified == 1)
		{
		
			App->SBC_Dialogs->YesNo("Save Scene", "Scene has been Modified Do you wish to save changes",1);

			bool Doit = App->SBC_Dialogs->Canceled;
			if (Doit == 0)
			{
				App->SBC_Project->Start_Save_Project_Dialog();
			}

		}
		else
		{
			App->SBC_Dialogs->YesNo("Close GameDirector", "Are you sure", 1);

			if (App->SBC_Dialogs->Canceled == 1)
			{
				return 1;
			}
		}

		App->SBC_Gui_Dialogs->Close_All_Dialogs();
		
		if (App->SBC_Ogre->OgreListener->StopOgre == 0)
		{
			App->SBC_Ogre->OgreListener->StopOgre = 1;
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
				App->SBC_Ogre->OgreListener->Wheel = -1;
			}
			else if (zDelta < 0)
			{
				App->SBC_Ogre->OgreListener->Wheel = 1;
			}
			return 1;
		}
	}

	case WM_MOUSEMOVE: // ok up and running and we have a loop for mouse
	{
		POINT p;

		App->SBC_Ogre->m_imgui.mouseMoved();
		
		
		if (GetCursorPos(&p) && App->OgreStarted == 1)// && App->CL10_Dimensions->Mouse_Move_Mode == Enums::Edit_Mouse_None)
		{
			if (ScreenToClient(App->ViewGLhWnd, &p))
			{
				RECT rc;
				GetClientRect(App->ViewGLhWnd, &rc);
				int width = rc.right - rc.left;
				int height = rc.bottom - rc.top;

				float tx = ((float)width / 2) - (float)p.x;
			}
		}

		SetFocus(App->ViewGLhWnd);
		break;
	}
	// Right Mouse Button
	case WM_RBUTTONDOWN: // BERNIE_HEAR_FIRE 
	{
		App->SBC_Ogre->m_imgui.mousePressed();
		

		if (ImGui::GetIO().WantCaptureMouse)
		{
			//App->Cl_FileView_V2->RightMouseDown = 1;
		}

		if (!ImGui::GetIO().WantCaptureMouse)
		{

			if (App->SBC_Scene->GameMode_Running_Flag == 0)
			{
				if (App->OgreStarted == 1)
				{

					SetCapture(App->ViewGLhWnd);// Bernie
					SetCursorPos(App->CursorPosX, App->CursorPosY);
					App->SBC_Ogre->OgreListener->Pl_RightMouseDown = 1;
					App->CUR = SetCursor(NULL);
					return 1;
				}
			}
		}
		return 1;
	}

	case WM_KEYUP:
	{
		ImGuiIO& io = ImGui::GetIO();

		io.KeysDown[VK_BACK] = false;
		io.KeysDown[VK_LEFT] = false;
		io.KeysDown[VK_RIGHT] = false;
		return 1;
	}

	case WM_CHAR:
	{
		if (ImGui::GetIO().WantCaptureKeyboard)
		{
			ImGuiIO& io = ImGui::GetIO();
			io.AddInputCharacter((unsigned short)wParam);
		}
		return 1;
	}

	case WM_KEYDOWN:
	{
		ImGuiIO& io = ImGui::GetIO();
		bool Done = 0;

		if (wParam == VK_BACK)
		{
			io.KeysDown[VK_BACK] = true;
		}

		if (wParam == VK_RIGHT)
		{
			io.KeysDown[VK_RIGHT] = true;
		}

		if (wParam == VK_LEFT)
		{
			io.KeysDown[VK_LEFT] = true;
		}
		
		return 1;
	}

	case WM_RBUTTONUP:
	{
		App->SBC_Ogre->m_imgui.mouseReleased();

		if (App->SBC_Scene->GameMode_Running_Flag == 0)
		{
			if (App->OgreStarted == 1)
			{
				ReleaseCapture();
				App->SBC_Ogre->OgreListener->Pl_RightMouseDown = 0;
				SetCursor(App->CUR);
				return 1;
			}
		}

		return 1;
	}
	// Left Mouse Button
	case WM_LBUTTONDOWN: // BERNIE_HEAR_FIRE 
	{
		App->SBC_Ogre->m_imgui.mousePressed();

		if (!ImGui::GetIO().WantCaptureMouse)
		{

			{
				
				if (App->OgreStarted == 1)
				{
					if (App->Block_Mouse_Buttons == 0)
					{
						if (!ImGui::GetIO().WantCaptureMouse)
						{
							SetCapture(App->ViewGLhWnd);// Bernie
							SetCursorPos(App->CursorPosX, App->CursorPosY);
							App->SBC_Ogre->OgreListener->Pl_LeftMouseDown = 1;
							App->CUR = SetCursor(NULL);
						}
						else
						{
							App->SBC_Ogre->OgreListener->Pl_LeftMouseDown = 1;
						}
					}

					return 1;
				}
			}
		}

		return 1;
	}

	case WM_LBUTTONUP:
	{
		App->SBC_Ogre->m_imgui.mouseReleased();

		if (App->SBC_Scene->GameMode_Running_Flag == 0)
		{
			if (App->OgreStarted == 1)
			{
				ReleaseCapture();
				App->SBC_Ogre->OgreListener->Pl_LeftMouseDown = 0;
				SetCursor(App->CUR);
				return 1;
			}
		}

		return 1;
	}
	//case WM_KEYDOWN:
	//	switch (wParam)
	//	{
	//		case 'C':
	//			if (GetAsyncKeyState(VK_CONTROL))
	//			{
	//		//		App->CL10_Objects_Com->Copy_Object();
	//		//		return 1;
	//			}
	//		case 'V':
	//			if (GetAsyncKeyState(VK_CONTROL))
	//			{
	//		//		App->CL10_Objects_Com->Paste_Object();
	//		//		return 1;
	//			}
	//			return 1;
	//		//	// more keys here
	//	}break;

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
		HFONT Font2;
		Font = CreateFont(-17, 0, 0, 0, FW_BOLD, 0, 0, 0, 0, OUT_TT_ONLY_PRECIS, 0, 0, 0, "Aerial Black");
		Font2 = CreateFont(-20, 0, 0, 0, FW_BOLD, 0, 0, 0, 0, OUT_TT_ONLY_PRECIS, 0, 0, 0, "Aerial Black");

		SendDlgItemMessage(hDlg, IDC_STNAME, WM_SETFONT, (WPARAM)App->Font_Banner, MAKELPARAM(TRUE, 0));
		SendDlgItemMessage(hDlg, IDC_STCOPYRIGHT, WM_SETFONT, (WPARAM)Font, MAKELPARAM(TRUE, 0));
		SendDlgItemMessage(hDlg, IDC_LISTABOUT, WM_SETFONT, (WPARAM)Font, MAKELPARAM(TRUE, 0));

		SendDlgItemMessage(hDlg, IDC_STPROGRAMER, WM_SETFONT, (WPARAM)Font2, MAKELPARAM(TRUE, 0));
		SendDlgItemMessage(hDlg, IDC_STGRAPHICS, WM_SETFONT, (WPARAM)Font2, MAKELPARAM(TRUE, 0));

		SendDlgItemMessage(hDlg, IDC_STTHANKS, WM_SETFONT, (WPARAM)Font, MAKELPARAM(TRUE, 0));
		SendDlgItemMessage(hDlg, IDC_ST10, WM_SETFONT, (WPARAM)Font, MAKELPARAM(TRUE, 0));

		SetDlgItemText(hDlg, IDC_STNAME, App->Version);

		char buff[255];

		SendDlgItemMessage(hDlg, IDC_LISTABOUT, LB_ADDSTRING, (WPARAM)0, (LPARAM)" ");
		
		/*sprintf(buff, "%s", " EquitySB Alpha Build 22/12/22");
		SendDlgItemMessage(hDlg, IDC_LISTABOUT, LB_ADDSTRING, (WPARAM)0, (LPARAM)buff);*/

		/*sprintf(buff, "%s  %s", " Ogre Version ", "1.9");
		SendDlgItemMessage(hDlg, IDC_LISTABOUT, LB_ADDSTRING, (WPARAM)0, (LPARAM)buff);

		sprintf(buff, "%s  %s", " Bullet Version ", "2.86");
		SendDlgItemMessage(hDlg, IDC_LISTABOUT, LB_ADDSTRING, (WPARAM)0, (LPARAM)buff);
		
		sprintf(buff, "%s  %s", " ImGui ", ImGui::GetVersion());
		SendDlgItemMessage(hDlg, IDC_LISTABOUT, LB_ADDSTRING, (WPARAM)0, (LPARAM)buff);*/
		
		SendDlgItemMessage(hDlg, IDC_LISTABOUT, LB_ADDSTRING, (WPARAM)0, (LPARAM)" "); // Space
		App->SBC_Ogre->GetVersion_OpenGL(buff);
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
	App->SBC_Ogre->InitOgre();

	Ogre::Root::getSingletonPtr()->renderOneFrame();
	EndDialog(App->ViewPLeaseWait, LOWORD(0));

	App->OgreStarted = 1;

	App->SBC_Dialogs->Front_Screen();

	KillTimer(App->MainHwnd, 1);

	App->SBC_SoundMgr->Play_StartUp_Sound();

	char Default_Project[MAX_PATH];
	strcpy(Default_Project, App->EquityDirecory_FullPath);
	strcat(Default_Project, "\\Projects\\RF_Project_Prj\\Project.SBProj");

	if (App->SBC_Prefs->Prefs_Load_LastScene_Flag == 1)
	{
		App->SBC_TopTabs->Do_Quick_Load();
	}
	
	App->SBC_Panels->MovePhysicsView();
	App->SBC_Panels->MovePropertiesPanel_Gui();
	//App->SBC_Gui_Dialogs->Show_Physics_Console = 0;
	//App->SBC_Gui_Dialogs->Show_Physics_Console = 1;

	//App->SBC_Ogre->mRoot->startRendering();
	App->SBC_Ogre->Ogre_Render_Loop();

	
	Close_App();
	SystemParametersInfo(SPI_SETSCREENSAVEACTIVE, TRUE, NULL, TRUE);
	PostQuitMessage(0);
}

// *************************************************************************
// *						Close_App Terry Bernie			  	 		   *
// *************************************************************************
void Close_App()
{
	if (App->SBC_Ogre->mRoot)
	{
		delete App->SBC_Ogre->mRoot;
		App->SBC_Ogre->mRoot = NULL;
	}

	ImGui::DestroyContext();
}