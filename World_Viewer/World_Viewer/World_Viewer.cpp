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
#include "World_Viewer.h"
//#include "scanner.h"
#include "Header.h"
#include "brush.h"


#define MAX_LOADSTRING 100

// Global Variables:
HINSTANCE hInst;                                // current instance
TCHAR szTitle[MAX_LOADSTRING];                  // The title bar text
TCHAR szWindowClass[MAX_LOADSTRING];            // the main window class name


ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);


void StartOgre();
void Close_App();

LRESULT CALLBACK ViewerMain_Proc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);
LRESULT CALLBACK Ogre3D_Proc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);

int Block_Call = 0;

WV_App* App = NULL;

#include "Shlwapi.h"
// *************************************************************************
// *				WinMain:- Terry and Hazel Flanigan 2023		  		   *
// *************************************************************************
int APIENTRY wWinMain(_In_ HINSTANCE hInstance,_In_opt_ HINSTANCE hPrevInstance, _In_ LPWSTR lpCmdLine, _In_ int  nCmdShow)
{
    InitCommonControls();

    App = new WV_App();
    _getcwd(App->EquityDirecory_FullPath, 1024);

    App->InitApp();

	char buff[255];
	strcpy(buff, PathGetArgsA(GetCommandLineA()));
	
	int Result = strcmp(buff,"WorldEditor");
	if (Result == 0)
	{
		//App->Say(buff);
		App->Is_WorldEditor = 1;
	}
	else
	{
		App->Is_WorldEditor = 0;
	}



    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

   
    LoadString(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadString(hInstance, IDC_WORLDVIEWER, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

	App->SetMainWinCentre();

	if (App->Debug_App == 1)
	{
		App->CL_TopTabs->Start_TopBar_Globals();
	}

	App->CL_Bullet->Init_Bullet();

	App->CL_Loader->Start_Groups_Dialog();

	if (App->Debug_App == 1)
	{
		App->CL_Properties->Start_Properties_Dialog();
	}

	//Fusion::BrushList_Create();

	

	SetTimer(App->MainHwnd, 1, 1, NULL);

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_WORLDVIEWER));

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
// *			MyRegisterClass:- Terry and Hazel Flanigan 2023	  	 	   *
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
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_WORLDVIEWER));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCE(IDC_WORLDVIEWER);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassEx(&wcex);
}

// *************************************************************************
// *			InitInstance:- Terry and Hazel Flanigan 2023			   *
// *************************************************************************
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
	App->hInst; // Store instance handle in our global variable

	App->MainHwnd = CreateWindow(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
		0, 0, 1200, 800, NULL, NULL, hInstance, NULL);

	App->Fdlg = CreateDialog(App->hInst, (LPCTSTR)IDD_FILEVIEW, App->MainHwnd, (DLGPROC)App->CL_SplitterViews->ViewerMain_Proc);

	int cx = GetSystemMetrics(SM_CXSCREEN);
	int cy = GetSystemMetrics(SM_CYSCREEN);

	RECT rect;
	GetClientRect(App->MainHwnd, &rect);
	MoveWindow(App->Fdlg, 0, 0, rect.right, rect.bottom, TRUE);

	App->CursorPosX = cx / 2;
	App->CursorPosY = cy / 2;

	App->CL_SplitterViews->Init_Views();

	App->CL_SplitterViews->Create_Left_Window();
	App->CL_SplitterViews->Create_Right_Window();
	App->CL_SplitterViews->Create_Bottom_Left_Window();

	App->ViewGLhWnd = CreateDialog(App->hInst, (LPCTSTR)IDD_VIEWER3D, App->Fdlg, (DLGPROC)Ogre3D_Proc);

	App->CL_SplitterViews->Resize_Windows(App->Fdlg, App->CL_SplitterViews->nleftWnd_width, App->CL_SplitterViews->nleftWnd_width);

	App->CL_Ogre->RenderHwnd = App->ViewGLhWnd;

	if (!App->MainHwnd)
	{
		return FALSE;
	}

	App->cmdHandle = FindWindow(szWindowClass, szTitle);

	ShowWindow(App->MainHwnd, nCmdShow);
	UpdateWindow(App->MainHwnd);

	return TRUE;
}

// *************************************************************************
// *				WndProc:- Terry and Hazel Flanigan 2023	  	 		   *
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

			// --------------------------- Camera
			case ID_CAMERA_NONE:
			{
				App->CL_Grid->Reset_View();
				App->CL_Grid->Grid_SetVisible(true);

				App->CL_Ogre->OgreListener->CameraMode = Enums::CamNone;
				return 1;
			}

			case ID_CAMERA_MODELMODE:
			{
				App->CL_Grid->Reset_View();
				App->CL_Grid->Grid_SetVisible(true);

				App->CL_Ogre->OgreListener->CameraMode = Enums::CamModel;
				return 1;
			}

			case ID_CAMERA_FREEMODE:
			{
				App->CL_Grid->Reset_View();
				App->CL_Grid->Grid_SetVisible(true);

				App->CL_Ogre->OgreListener->CameraMode = Enums::CamDetached;
				return 1;
			}
			
			// --------------------------- Windows
			case ID_WINDOWS_SHOWFPS:
			{
				if (App->CL_ImGui->Show_FPS_F == 1)
				{
					App->CL_ImGui->Show_FPS_F = 0;
				}
				else
				{
					App->CL_ImGui->Show_FPS_F = 1;
				}
				return 1;
			}
			
			//---------------------------------------------------
			case ID_VIEW_RESETVIEW:
			{
				App->CL_Grid->Reset_View();
				App->CL_Grid->Grid_SetVisible(true);

				return 1;
			}

			// --------------------------- Debug

			case ID_DEBUG_RESETPHYSICS:
			{
				App->CL_Physics->Reset_Physics();
				App->CL_Ogre->OgreListener->GD_Run_Physics = 1;

				return 1;
			}

			case ID_DEBUG_TEST:
			{
				App->CL_Export_Ogre->Export_AssimpToOgre();

				return 1;
			}
			case ID_DEBUG_MODELDATA:
			{
				if (App->CL_ImGui->Show_Model_Data_F == 1)
				{
					App->CL_ImGui->Close_Model_Data();
				}
				else
				{
					App->CL_ImGui->Start_Model_Data();
				}
				return 1;
			}

			case ID_DEBUG_CAMERA:
			{
				if (App->CL_ImGui->Show_Camera_Data_F == 1)
				{
					App->CL_ImGui->Close_Camera_Data();
				}
				else
				{
					App->CL_ImGui->Start_Camera_Data();
				}
				return 1;
			}
			
			case ID_OPEN_WORLDEDITORPROJECT:
			{
				int Result = App->CL_Loader->Open_File_Model("GDSB File   *.Wepf\0*.Wepf\0", "GDSB File", NULL);
				if (Result == 0)
				{
					return 1;
				}

				App->CL_Loader->Read_Project_File(App->CL_Loader->Path_FileName);
				App->CL_Loader->Load_File_Wepf();
				return 1;
			}
				
			case ID_DEBUG_SHOWIMGUIDEMO:
			{
				
				if (App->CL_Ogre->OgreListener->Show_DemoWindow == 1)
				{
					App->CL_Ogre->OgreListener->Show_DemoWindow = 0;
				}
				else
				{
					App->CL_Ogre->OgreListener->Show_DemoWindow = 1;
				}

				return 1;
			}

            case IDM_ABOUT:
                DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
                break;

            case IDM_EXIT:

				if (App->CL_Ogre->OgreListener->StopOgre == 0)
				{
					App->CL_Ogre->OgreListener->StopOgre = 1;
				}

				PostQuitMessage(0);
                break;


            default:
                return DefWindowProc(hWnd, message, wParam, lParam);
            }
        }
        break;
    //case WM_PAINT:
    //    {
    //        PAINTSTRUCT ps;
    //        HDC hdc = BeginPaint(hWnd, &ps);
    //        // TODO: Add any drawing code that uses hdc here...
    //        EndPaint(hWnd, &ps);
    //    }
    //    break;

	/*case WM_MOVING:
	{
		
		App->CL_SplitterViews->Resize_Fldg();
		App->Resize_OgreWin();
		Root::getSingletonPtr()->renderOneFrame();
		return 0;
	}*/
	
	case WM_SIZE:
	{
		App->CL_SplitterViews->Init_Views();
		App->CL_SplitterViews->Resize_Fldg();
		App->Resize_OgreWin();
		
		return 0;

	}

	case WM_WINDOWPOSCHANGED:
	{
		App->CL_SplitterViews->Init_Views();
		App->CL_SplitterViews->Resize_Fldg();
		App->Resize_OgreWin();
		return 0;

	}

	case WM_CLOSE:
	{
		
		if (App->CL_Ogre->OgreListener->StopOgre == 0)
		{
			App->CL_Ogre->OgreListener->StopOgre = 1;
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
// *				About:- Terry and Hazel Flanigan 2023	  	 		   *
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
// *			ViewerMain_Proc:- Terry and Hazel Flanigan 2023			   *
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
// *			Ogre3D_Proc:- Terry and Hazel Flanigan 2023				   *
// *************************************************************************
LRESULT CALLBACK Ogre3D_Proc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{

	case WM_INITDIALOG: // Bernie as the dialog is created
	{
		//App->ViewPLeaseWait = CreateDialog(App->hInst, (LPCTSTR)IDD_PLEASEWAIT, App->Fdlg, (DLGPROC)PleaseWait_Proc);
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
		//if (App->FullScreen == 1)
		{
			int zDelta = (short)HIWORD(wParam);    // wheel rotation

			if (zDelta > 0)
			{
				App->CL_Ogre->OgreListener->Wheel = -1;
			}
			else if (zDelta < 0)
			{
				App->CL_Ogre->OgreListener->Wheel = 1;
			}
			return 1;
		}
	}

	case WM_MOUSEMOVE: // ok up and running and we have a loop for mouse
	{
		POINT p;

		App->CL_Ogre->m_imgui.mouseMoved();


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
		App->CL_Ogre->m_imgui.mousePressed();


		if (ImGui::GetIO().WantCaptureMouse)
		{
			//App->Cl_FileView_V2->RightMouseDown = 1;
		}

		if (!ImGui::GetIO().WantCaptureMouse)
		{

			//if (App->SBC_Scene->GameMode_Running_Flag == 0)
			{
				if (App->OgreStarted == 1)
				{

					SetCapture(App->ViewGLhWnd);// Bernie
					SetCursorPos(App->CursorPosX, App->CursorPosY);
					App->CL_Ogre->OgreListener->Pl_RightMouseDown = 1;
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
		App->CL_Ogre->m_imgui.mouseReleased();

		//if (App->SBC_Scene->GameMode_Running_Flag == 0)
		{
			if (App->OgreStarted == 1)
			{
				ReleaseCapture();
				App->CL_Ogre->OgreListener->Pl_RightMouseDown = 0;
				SetCursor(App->CUR);
				return 1;
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

			{
				if (App->OgreStarted == 1)
				{
					if (App->Block_Mouse_Buttons == 0)
					{
						if (!ImGui::GetIO().WantCaptureMouse)
						{
							SetCapture(App->ViewGLhWnd);// Bernie
							SetCursorPos(App->CursorPosX, App->CursorPosY);
							App->CL_Ogre->OgreListener->Pl_LeftMouseDown = 1;
							App->CUR = SetCursor(NULL);
						}
						else
						{
							App->CL_Ogre->OgreListener->Pl_LeftMouseDown = 1;
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
		App->CL_Ogre->m_imgui.mouseReleased();

		//if (App->SBC_Scene->GameMode_Running_Flag == 0)
		{
			if (App->OgreStarted == 1)
			{
				ReleaseCapture();
				App->CL_Ogre->OgreListener->Pl_LeftMouseDown = 0;
				SetCursor(App->CUR);
				return 1;
			}
		}

		return 1;
	}

	}

	return FALSE;
}

// *************************************************************************
// *						StartOgre Terry Bernie			  	 		   *
// *************************************************************************
void StartOgre()
{
	App->CL_Ogre->InitOgre();

	Ogre::Root::getSingletonPtr()->renderOneFrame();
	//EndDialog(App->ViewPLeaseWait, LOWORD(0));

	App->OgreStarted = 1;

	KillTimer(App->MainHwnd, 1);

	if (App->Is_WorldEditor == 1)
	{
		char Path[MAX_PATH];
		strcpy(Path, App->EquityDirecory_FullPath);
		strcat(Path, "\\Data\\Temp.Wepf");

		strcpy(App->CL_Loader->Path_FileName, Path);
		strcpy(App->CL_Loader->FileName,"Temp.Wepf");

		//App->Say_Win(App->CL_Loader->Path_FileName);

		App->CL_Loader->Read_Project_File(App->CL_Loader->Path_FileName);
		App->CL_Loader->Load_File_Wepf();
	}


	//App->CL_Ogre->mRoot->startRendering();
	App->CL_Ogre->Ogre_Render_Loop();


	Close_App();
	SystemParametersInfo(SPI_SETSCREENSAVEACTIVE, TRUE, NULL, TRUE);
	PostQuitMessage(0);
}

// *************************************************************************
// *						Close_App Terry Bernie			  	 		   *
// *************************************************************************
void Close_App()
{
	if (App->CL_Ogre->mRoot)
	{
		delete App->CL_Ogre->mRoot;
		App->CL_Ogre->mRoot = NULL;
	}

	ImGui::DestroyContext();
}
