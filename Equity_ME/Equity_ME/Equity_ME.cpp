// Equity_ME.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "Equity_ME.h"

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

LRESULT CALLBACK ViewerMain_Proc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);
LRESULT CALLBACK Ogre3D_Proc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);

int Block_Call = 0; // If Ogre Started block restart [130122]
void Close_App();
void Start_Ogre();

ME_App *App = NULL;  // Main Global App [090122]

// *************************************************************************
// *							WinMain Terry Flanigan		  	 		   *
// *************************************************************************
int APIENTRY wWinMain(_In_ HINSTANCE hInstance,_In_opt_ HINSTANCE hPrevInstance,_In_ LPWSTR    lpCmdLine,_In_ int nCmdShow)
{
	InitCommonControls();

	App = new ME_App();
	
	_getcwd(App->EquityDirecory_FullPath, 1024);
	
	App->InitApp();

	
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: Place code here.

    // Initialize global strings
    LoadString(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadString(hInstance, IDC_EQUITY_ME, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // Perform application initialization:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

	App->LoadProgramResource();

	App->SetMainWin_Centre();

	App->mMenu = GetMenu(App->MainHwnd);

	App->CL_TopBar->Start_TopBar();
	App->CL_FileView->Start_FileView();		//Start Main File View Groups [210622]
	App->CL_Groups->Start_Groups_Dialog();
	App->CL_Motions->Start_Motions_Dialog();

	ShowWindow(App->MainHwnd, nCmdShow);
	UpdateWindow(App->MainHwnd);

	App->CL_Panels->Move_FileView_Window();
	App->CL_Panels->Place_GlobalGroups();

	App->CL_FileIO->Init_History();
	App->CL_Prefs->Read_Preferences(); // Read Preferences

	SetTimer(App->MainHwnd, 1, 1, NULL);

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_EQUITY_ME));

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

    return (int) msg.wParam;
}


// *************************************************************************
// *					MyRegisterClass Terry Flanigan		  	 		   *
// *************************************************************************
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEX wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = 0;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_EQUITY_ME));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCE(IDC_EQUITY_ME);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassEx(&wcex);
}

// *************************************************************************
// *					InitInstance Terry Flanigan			  	 		   *
// *************************************************************************
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
  
   App->hInst = hInstance; // Store instance handle in our global variable

   App->MainHwnd = CreateWindow(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
	   0, 0, 1200, 800, NULL, NULL, hInstance, NULL);

   App->Fdlg = CreateDialog(App->hInst, (LPCTSTR)IDD_FILEVIEW, App->MainHwnd, (DLGPROC)ViewerMain_Proc);

   int cx = GetSystemMetrics(SM_CXSCREEN);
   int cy = GetSystemMetrics(SM_CYSCREEN);
   MoveWindow(App->Fdlg, 0, 0, cx, cy, TRUE);

   App->ViewGLhWnd = CreateDialog(App->hInst, (LPCTSTR)IDD_VIEWER3D, App->Fdlg,(DLGPROC)Ogre3D_Proc);

   App->CL_Ogre->Render_Hwnd = App->ViewGLhWnd;

   if (!App->MainHwnd)
   {
      return FALSE;
   }

   UpdateWindow(App->MainHwnd);

   return TRUE;
}

// *************************************************************************
// *						WndProc Terry Flanigan			  	 		   *
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

			// ------------------------------------------------------- Views
			case ID_VIEW_OGRERESETVIEW:
			{

				App->CL_Grid->Reset_View();

				return 1;
			}

			// ------------------------------------------------------- Debug
			case ID_DEBUG_RENDER:
			{
				if (App->CL_Ogre->RenderListener->ShowTextured == 1)
				{
					App->CL_Ogre->RenderListener->ShowTextured = 0;
				}
				else
				{
					App->CL_Ogre->RenderListener->ShowTextured = 1;
				}

				return 1;	
			}

			case ID_DEBUG_GENERAL:
			{
				
				return 1;
			}

			case ID_DEBUG_APPDATA:
			{
				App->CL_Dialogs->What_List = Enums::Show_List_App;
				App->CL_Dialogs->Show_ListData();
				return 1;
			}

			case ID_DEBUG_SHOWIMGUIDEMO:
			{
				if (App->CL_ImGui->Show_ImGui_Test == 1)
				{
					App->CL_ImGui->Show_ImGui_Test = 0;
				}
				else
				{
					App->CL_ImGui->Show_ImGui_Test = 1;
				}

				return 1;
			}

			// ------------------------------------------------------- File
			case ID_FILE_CLEARMODEL:
			{
				App->CL_Model->Clear_Model_And_Reset();
				return 1;
			}

			// ------------------------------------------------------- Tools
			case ID_CENTRE_MIDDLE:
			{
				App->CL_Dimensions->Centre_Model_Mid();
				return 1;
			}

			case ID_CENTRE_BASE:
			{
				App->CL_Dimensions->Centre_Model_Base();
				return 1;
			}

			case ID_MODEL_ROTATEX:
			{
				App->CL_Dimensions->Rotate_X_Model(90);
				return 1;
			}

			case ID_MODEL_ROTATEY:
			{
				App->CL_Dimensions->Rotate_Y_Model(90);
				return 1;
			}

			case ID_MODEL_ROTATEZ:
			{
				App->CL_Dimensions->Rotate_Z_Model(90);
				return 1;
			}

			case ID_TOOLS_RFTEXTURELIBRARY:
			{
				App->CL_Texture_Lib->Start_Texl_Dialog();
				return 1;
			}
			
			
			// ------------------------------------------------------- Import
			case ID_IMPORT_EQ_WAVEFRONTOBJ:
			{
				App->CL_Assimp->SelectedPreset = 8 + 8388608 + 64 + aiProcess_PreTransformVertices;
				App->CL_Import->Assimp_Loader("Wavefront OBJ   *.obj\0*.obj\0", "Wavefront OBJ");
				return 1;
			}

			case ID_IMPORT_AUTODESK3DS:
			{
				App->CL_Assimp->SelectedPreset = 8 + 8388608 + 64 + aiProcess_PreTransformVertices;
				App->CL_Import->Assimp_Loader("Autodesk 3DS   *.3ds\0*.3ds\0", "Autodesk 3DS");
				return 1;
			}

			case ID_IMPORT_BLENDERBLEND:
			{
				App->CL_Assimp->SelectedPreset = 8 + 8388608 + 64 + aiProcess_PreTransformVertices;
				App->CL_Import->Assimp_Loader("Blender   *.blend\0*.blend\0", "Blender");
				return 1;
			}

			case ID_IMPORT_MILKSHAPEMS3D:
			{
				App->CL_Assimp->SelectedPreset = 8 + 8388608 + 64;
				App->CL_Import->Assimp_Loader("MilkShape Files   *.ms3d\0*.ms3d\0", "Load MilkShape File");
				return 1;
			}

			case ID_IMPORT_COLLADADAE:
			{
				App->CL_Assimp->SelectedPreset = 8 + 8388608 + 64 + aiProcess_PreTransformVertices;
				App->CL_Import->Assimp_Loader("Collada DAE   *.dae\0*.dae\0", "Collada DAE");
				return 1;
			}

			case ID_IMPORT_GENESIS3DACT:
			{
				App->CL_Import->RFActor_Loader();
				return 1;
			}

			case ID_OGRE3D_MESHMESH:
			{
				App->CL_Import->Ogre_Loader("Ogre3D   *.mesh\0*.mesh\0", "Ogre3D");
				return 1;
			}

			case ID_EQUITY_ROOM:
			{
				App->CL_Import->WorldEditor_Loader();
				return 1;
			}

			// ------------------------------------------------------- Export
			case ID_EXPORT_WAVEFRONTOBJ:
			{
				App->CL_Export->Object_Model();
				return 1;
			}

			case ID_MILKSHAPEMS3D_MESH:
			{
				App->CL_Export->Milkshape_Model();
				return 1;
			}

			case ID_OGRE3D_MESH:
			{
				App->CL_Export->Ogre3D_Model();
				return 1;
			}
			
			// ------------------------------------------------------- Windows
			case ID_WINDOWS_FILEVIEW:
			{
				ShowWindow(App->ListPanel, 1);

				if (App->CL_FileView->FileView_Active == 1)
				{
					App->CL_FileView->FileView_Active = 0;
					ShowWindow(App->ListPanel, 0);
					CheckMenuItem(App->mMenu, ID_WINDOWS_FILEVIEW, MF_BYCOMMAND | MF_UNCHECKED);
				}
				else
				{
					App->CL_FileView->FileView_Active = 1;
					ShowWindow(App->ListPanel, 1);
					CheckMenuItem(App->mMenu, ID_WINDOWS_FILEVIEW, MF_BYCOMMAND | MF_CHECKED);
				}
				return 1;
			}

			case ID_WINDOWS_GROUPS:
			{
				ShowWindow(App->CL_Groups->RightGroups_Hwnd, 1);

				if (App->CL_Groups->RightGroups_Visable == 1)
				{
					App->CL_Groups->RightGroups_Visable = 0;
					ShowWindow(App->CL_Groups->RightGroups_Hwnd, 0);
					CheckMenuItem(App->mMenu, ID_WINDOWS_GROUPS, MF_BYCOMMAND | MF_UNCHECKED);
				}
				else
				{
					App->CL_Groups->RightGroups_Visable = 1;
					ShowWindow(App->CL_Groups->RightGroups_Hwnd, 1);
					CheckMenuItem(App->mMenu, ID_WINDOWS_GROUPS, MF_BYCOMMAND | MF_CHECKED);
				}
				return 1;
			}

			// ------------------------------------- Recent Files
			case 5000 + 7: // Top Recent Files 1
			{
				char mFileName[1024];
				strcpy(mFileName, App->CL_FileIO->mPreviousFiles[7].c_str());
				App->CL_Import->Reload_FromResentFiles(mFileName);
				return 1;
			}
			case 5000 + 6: // 2
			{
				char mFileName[1024];
				strcpy(mFileName, App->CL_FileIO->mPreviousFiles[6].c_str());
				App->CL_Import->Reload_FromResentFiles(mFileName);
				return 1;
			}
			case 5000 + 5: // 3
			{
				char mFileName[1024];
				strcpy(mFileName, App->CL_FileIO->mPreviousFiles[5].c_str());
				App->CL_Import->Reload_FromResentFiles(mFileName);
				return 1;
			}
			case 5000 + 4: // 4
			{
				char mFileName[1024];
				strcpy(mFileName, App->CL_FileIO->mPreviousFiles[4].c_str());
				App->CL_Import->Reload_FromResentFiles(mFileName);
				return 1;
			}
			case 5000 + 3: // 5
			{
				char mFileName[1024];
				strcpy(mFileName, App->CL_FileIO->mPreviousFiles[3].c_str());
				App->CL_Import->Reload_FromResentFiles(mFileName);
				return 1;
			}
			case 5000 + 2: // 6
			{
				char mFileName[1024];
				strcpy(mFileName, App->CL_FileIO->mPreviousFiles[2].c_str());
				App->CL_Import->Reload_FromResentFiles(mFileName);
				return 1;
			}
			case 5000 + 1: // 7
			{
				char mFileName[1024];
				strcpy(mFileName, App->CL_FileIO->mPreviousFiles[1].c_str());
				App->CL_Import->Reload_FromResentFiles(mFileName);
				return 1;
			}
			case 5000 + 0: // 8
			{
				char mFileName[1024];
				strcpy(mFileName, App->CL_FileIO->mPreviousFiles[0].c_str());
				App->CL_Import->Reload_FromResentFiles(mFileName);
				return 1;
			}

			case ID_FILE_CLEARRESENTFILES:
			{
				App->CL_FileIO->ResentHistory_Clear();
				return 1;
			}
			
			//---------------------------------------------------------------------------- System
            case IDM_ABOUT:
                DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
                break;
            case IDM_EXIT:
				if (App->CL_Ogre->Ogre_Listener->Stop_Ogre == 0)
				{
					App->CL_Ogre->Ogre_Listener->Stop_Ogre = 1;
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
        }
        break;

	case WM_MOUSEWHEEL:
	{
		int zDelta = (short)HIWORD(wParam);    // wheel rotation

		if (zDelta > 0)
		{
			App->CL_Ogre->Ogre_Listener->Wheel = -1;
		}
		else if (zDelta < 0)
		{
			App->CL_Ogre->Ogre_Listener->Wheel = 1;
		}

		return 1;
	}

	case WM_MOVING:
	{
		App->CL_Panels->ResizeOgre_Window();
		Ogre::Root::getSingletonPtr()->renderOneFrame();
		return 0;
	}

	case WM_SIZE:
	{
		App->CL_Panels->ResizeOgre_Window();
	}break;

	case WM_CLOSE:
	{

		//App->Cl_Dialogs->YesNo("Close GameDirector", "Are you sure");
		/*if (App->Cl_Dialogs->Canceled == 1)
		{
			break;
		}*/

		if (App->CL_Ogre->Ogre_Listener->Stop_Ogre == 0)
		{
			App->CL_Ogre->Ogre_Listener->Stop_Ogre = 1;
		}

		PostQuitMessage(0);
		break;
	}

	case WM_TIMER:
		if (wParam == 1)
		{
			if (App->CL_Ogre->Ogre_Started == 0)
			{
				if (Block_Call == 0)
				{
					Block_Call = 1;
					Start_Ogre();
				}
			}

			////// Render behind windows
			//if (App->RenderBackGround == 1 && App->OgreStarted == 1)
			//{
			//	Ogre::Root::getSingletonPtr()->renderOneFrame();
			//}
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
// *						About Terry Flanigan			  	 		   *
// *************************************************************************
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{

	case WM_INITDIALOG:
	{
		SendDlgItemMessage(hDlg, IDC_STNAME, WM_SETFONT, (WPARAM)App->Font_Arial20, MAKELPARAM(TRUE, 0));
		SendDlgItemMessage(hDlg, IDC_STPROGRAMER, WM_SETFONT, (WPARAM)App->Font_Arial20, MAKELPARAM(TRUE, 0));

		SendDlgItemMessage(hDlg, IDC_LISTABOUT, WM_SETFONT, (WPARAM)App->Font_CB15, MAKELPARAM(TRUE, 0));

		SendDlgItemMessage(hDlg, IDC_STCOPYRIGHT, WM_SETFONT, (WPARAM)App->Font_CB15, MAKELPARAM(TRUE, 0));


		//--------------------------------

		char buff[255];

		sprintf(buff, "%s%s", " Build:- ", App->Version);
		SendDlgItemMessage(hDlg, IDC_LISTABOUT, LB_ADDSTRING, (WPARAM)0, (LPARAM)buff);
		
		SendDlgItemMessage(hDlg, IDC_LISTABOUT, LB_ADDSTRING, (WPARAM)0, (LPARAM)" ");

		App->CL_Ogre->GetVersion_OpenGL(buff);
		SendDlgItemMessage(hDlg, IDC_LISTABOUT, LB_ADDSTRING, (WPARAM)0, (LPARAM)buff);
		return (INT_PTR)TRUE;
	}

	case WM_CTLCOLORSTATIC:
	{
		
		if (GetDlgItem(hDlg, IDC_STNAME) == (HWND)lParam)
		{
			SetBkColor((HDC)wParam, RGB(0, 255, 0));
			SetTextColor((HDC)wParam, RGB(0, 0, 0));
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

		if (GetDlgItem(hDlg, IDC_STCOPYRIGHT) == (HWND)lParam)
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
// *						Ogre3D_Proc  (Terry Bernie)					   *
// *************************************************************************
LRESULT CALLBACK Ogre3D_Proc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{

	switch (message)
	{

	case WM_INITDIALOG:
	{
		return TRUE;
	}

	case WM_CTLCOLORDLG:
	{
		if (App->CL_Ogre->Ogre_Started == 0)
		{
			return (LONG)App->BlackBrush;
		}

		return false;
	}

	// Mouse Wheel
	case WM_MOUSEMOVE: // ok up and running and we have a loop for mouse
	{

		App->CL_Ogre->m_imgui.mouseMoved();

		SetFocus(App->ViewGLhWnd);
		break;
	}

	case WM_MOUSEWHEEL:
	{
		if (App->CL_Ogre->Ogre_Listener->Pl_LeftMouseDown == 0)
		{
			int zDelta = (short)HIWORD(wParam);    // wheel rotation

			if (zDelta > 0)
			{
				App->CL_Ogre->Ogre_Listener->Wheel = -1;
			}
			else if (zDelta < 0)
			{
				App->CL_Ogre->Ogre_Listener->Wheel = 1;
			}
		}

		return 1;

	}

	// Left Mouse Button
	case WM_LBUTTONDOWN: // BERNIE_HEAR_FIRE 
	{
		App->CL_Ogre->m_imgui.mousePressed();

		if (!ImGui::GetIO().WantCaptureMouse)
		{

			if (App->CL_Ogre->Ogre_Started == 1)
			{
				if (!ImGui::GetIO().WantCaptureMouse)
				{
					SetCapture(App->ViewGLhWnd);// Bernie
					SetCursorPos(500, 500);
					App->CL_Ogre->Ogre_Listener->Pl_LeftMouseDown = 1;
					App->CUR = SetCursor(NULL);
				}
				else
				{
					App->CL_Ogre->Ogre_Listener->Pl_LeftMouseDown = 1;
				}

				return 1;
			}

		}

		return 1;
	}
	case WM_LBUTTONUP:
	{
		App->CL_Ogre->m_imgui.mouseReleased();


		if (App->CL_Ogre->Ogre_Started == 1)
		{
			ReleaseCapture();
			App->CL_Ogre->Ogre_Listener->Pl_LeftMouseDown = 0;
			SetCursor(App->CUR);

			return 1;
		}

		return 1;
	}

	// Right Mouse Button
	case WM_RBUTTONDOWN: // BERNIE_HEAR_FIRE 
	{
		App->CL_Ogre->m_imgui.mousePressed();

		if (!ImGui::GetIO().WantCaptureMouse)
		{
			if (App->CL_Ogre->Ogre_Started == 1)
			{

				SetCapture(App->ViewGLhWnd);// Bernie
				SetCursorPos(500, 500);
				App->CL_Ogre->Ogre_Listener->Pl_RightMouseDown = 1;
				App->CUR = SetCursor(NULL);

				return 1;
			}
		}
		return 1;
	}
	case WM_RBUTTONUP:
	{
		App->CL_Ogre->m_imgui.mouseReleased();

		if (App->CL_Ogre->Ogre_Started == 1)
		{
			ReleaseCapture();
			App->CL_Ogre->Ogre_Listener->Pl_RightMouseDown = 0;
			SetCursor(App->CUR);

			return 1;
		}

		return 1;
	}

	case WM_COMMAND:
	{

	}

	break;
	}
	return FALSE;
}

// *************************************************************************
// *						StartOgre Terry Bernie			  	 		   *
// *************************************************************************
void Start_Ogre()
{
	App->CL_Ogre->Init_Ogre();

	Ogre::Root::getSingletonPtr()->renderOneFrame();
	//EndDialog(App->ViewPLeaseWait, LOWORD(0));

	App->CL_Ogre->Ogre_Started = 1;

	App->CL_Panels->ResizeOgre_Window();

	App->CL_Ogre->mRoot->startRendering();

	Close_App();

	SystemParametersInfo(SPI_SETSCREENSAVEACTIVE, TRUE, NULL, TRUE);
	PostQuitMessage(0);
}

// *************************************************************************
// *						Close_App Terry Bernie			  	 		   *
// *************************************************************************
void Close_App()
{
	//App->EBC_Model->Clear_ModelData();

	if (App->CL_Ogre->mRoot)
	{
		delete App->CL_Ogre->mRoot;
		App->CL_Ogre->mRoot = NULL;
	}

	//ImGui::DestroyContext();*/
}
