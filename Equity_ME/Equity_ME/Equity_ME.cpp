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
	App->CL_Groups->Start_Groups();

	ShowWindow(App->MainHwnd, nCmdShow);
	UpdateWindow(App->MainHwnd);

	App->CL_Panels->Move_FileView_Window();
	App->CL_Panels->Place_GlobalGroups();

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
  
   App->hInst; // Store instance handle in our global variable

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

   //ShowWindow(App->MainHwnd, nCmdShow);
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

				App->CL_Grid->GridNode->setPosition(0, 0, 0);
				App->CL_Grid->GridNode->resetOrientation();

				App->CL_Grid->HairNode->setPosition(0, 0, 0);
				App->CL_Grid->HairNode->resetOrientation();

				App->CL_Ogre->mCamera->setPosition(Ogre::Vector3(0, 90, 100));
				App->CL_Ogre->mCamera->lookAt(Ogre::Vector3(0, 30, 0));

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
				
			// ------------------------------------------------------- Import
			case ID_IMPORT_EQ_WAVEFRONTOBJ:
			{
				App->CL_Import->Assimp_Loader("Wavefront OBJ   *.obj\0*.obj\0", "Wavefront OBJ");
				return 1;
			}

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
		App->ResizeOgre_Window();
		Ogre::Root::getSingletonPtr()->renderOneFrame();
		return 0;
	}

	case WM_SIZE:
	{
		App->ResizeOgre_Window();
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
        return (INT_PTR)TRUE;

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

	App->ResizeOgre_Window();

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
