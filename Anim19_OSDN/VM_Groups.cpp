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

#include "stdafx.h"
#include "GD19_App.h"
#include "resource.h"
#include "VM_Groups.h"


VM_Groups::VM_Groups()
{
	RightGroups_Hwnd = nullptr;

	Sel_BaseBitmap = nullptr;

	SelectedGroup = 0;

	BasePicWidth = 0;
	BasePicHeight = 0;
}


VM_Groups::~VM_Groups()
{
}

// *************************************************************************
// *							Start_Groups				  		 	   *
// *************************************************************************
bool VM_Groups::Start_Groups()
{
	RightGroups_Hwnd = CreateDialog(App->hInst, (LPCTSTR)IDD_RIGHTGROUPS, App->SBC_Equity->MeshViewDialog_Hwnd, (DLGPROC)Groups_Proc);
	ShowWindow(RightGroups_Hwnd, 0);
	return 1;
}

// *************************************************************************
// *						Groups_Proc Terry Bernie		  			   *
// *************************************************************************
LRESULT CALLBACK VM_Groups::Groups_Proc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_INITDIALOG:
	{

		SendDlgItemMessage(hDlg, IDC_RGGROUPNAME, WM_SETFONT, (WPARAM)App->Font_Arial20, MAKELPARAM(TRUE, 0));
		SendDlgItemMessage(hDlg, IDC_RGTEXTURENAME, WM_SETFONT, (WPARAM)App->Font_Arial20, MAKELPARAM(TRUE, 0));

		SendDlgItemMessage(hDlg, IDC_INFO, WM_SETFONT, (WPARAM)App->Font_CB15, MAKELPARAM(TRUE, 0));
		SendDlgItemMessage(hDlg, IDC_CHANGETEXTURE, WM_SETFONT, (WPARAM)App->Font_CB15, MAKELPARAM(TRUE, 0));
		
		SetWindowLong(GetDlgItem(hDlg, IDC_BASETEXTURE2), GWL_WNDPROC, (LONG)ViewerBasePic);
	}

	case WM_CTLCOLORSTATIC:
	{
		if (GetDlgItem(hDlg, IDC_RGGROUPNAME) == (HWND)lParam)
		{
			SetBkColor((HDC)wParam, RGB(0, 255, 0));
			SetTextColor((HDC)wParam, RGB(0, 0, 0));
			SetBkMode((HDC)wParam, TRANSPARENT);
			return (UINT)App->AppBackground;
		}

		if (GetDlgItem(hDlg, IDC_RGTEXTURENAME) == (HWND)lParam)
		{
			SetBkColor((HDC)wParam, RGB(0, 255, 0));
			SetTextColor((HDC)wParam, RGB(0, 0, 0));
			SetBkMode((HDC)wParam, TRANSPARENT);
			return (UINT)App->AppBackground;
		}

		if (GetDlgItem(hDlg, IDC_GROUPID) == (HWND)lParam)
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

	case WM_CLOSE:
	{
		ShowWindow(App->CL_Vm_Groups->RightGroups_Hwnd, 0);

		break;
	}
	case WM_NOTIFY:
	{
		LPNMHDR some_item = (LPNMHDR)lParam;

		if (some_item->idFrom == IDC_CHANGETEXTURE && some_item->code == NM_CUSTOMDRAW)
		{
			LPNMCUSTOMDRAW item = (LPNMCUSTOMDRAW)some_item;
			App->Custom_Button_Normal(item);
			return CDRF_DODEFAULT;
		}

		if (some_item->idFrom == IDC_INFO && some_item->code == NM_CUSTOMDRAW)
		{
			LPNMCUSTOMDRAW item = (LPNMCUSTOMDRAW)some_item;
			App->Custom_Button_Normal(item);
			return CDRF_DODEFAULT;
		}

		return CDRF_DODEFAULT;
	}

	case WM_COMMAND:
	{
		if (LOWORD(wParam) == IDC_INFO)
		{
			if (App->CL_Vm_Model->Model_Loaded == 1)
			{
				if (App->CL_Vm_ImGui->Show_ImGui_TextureData == 1)
				{
					App->CL_Vm_ImGui->Show_ImGui_TextureData = 0;
				}
				else
				{
					App->CL_Vm_ImGui->Show_ImGui_TextureData = 1;
				}
			}
			return TRUE;
		}

		if (LOWORD(wParam) == IDC_CHANGETEXTURE)
		{
			if (App->CL_Vm_Model->Model_Loaded == 1)
			{
				App->CL_Vm_Groups->ChangeTexture_ModelLocation();
			}
			return TRUE;
		}
		//// ------------------------------------------------- Show All Groups
		//if (LOWORD(wParam) == IDC_SHOWALLGROUPS)
		//{
		//	HWND temp = GetDlgItem(hDlg, IDC_CKSHOWONLYGROUPS);
		//	HWND temp1 = GetDlgItem(hDlg, IDC_CKHIDEGROUP);

		//	App->CL_Right_Groups->CK_HideGroup = 0;
		//	App->Cl_Ogre->RenderListener->Show_HideGroup = 0;
		//	SendMessage(temp, BM_SETCHECK, 0, 0);

		//	App->CL_Right_Groups->CK_ShowGroupOnly = 0;
		//	App->Cl_Ogre->RenderListener->ShowOnlySubMesh = 0;
		//	SendMessage(temp1, BM_SETCHECK, 0, 0);

		//	return TRUE;
		//}
		//// ------------------------------------------------- Show Only Group
		//if (LOWORD(wParam) == IDC_CKSHOWONLYGROUPS)
		//{
		//	HWND temp = GetDlgItem(hDlg, IDC_CKSHOWONLYGROUPS);
		//	HWND temp1 = GetDlgItem(hDlg, IDC_CKHIDEGROUP);

		//	if (App->CL_Right_Groups->CK_ShowGroupOnly == 1)
		//	{
		//		App->CL_Right_Groups->CK_ShowGroupOnly = 0;
		//		App->Cl_Ogre->RenderListener->ShowOnlySubMesh = 0;
		//		SendMessage(temp, BM_SETCHECK, 0, 0);
		//	}
		//	else
		//	{
		//		App->CL_Right_Groups->CK_ShowGroupOnly = 1;
		//		App->Cl_Ogre->RenderListener->ShowOnlySubMesh = 1;
		//		SendMessage(temp, BM_SETCHECK, 1, 0);

		//		App->CL_Right_Groups->CK_HideGroup = 0;
		//		App->Cl_Ogre->RenderListener->Show_HideGroup = 0;
		//		SendMessage(temp1, BM_SETCHECK, 0, 0);
		//	}
		//	return TRUE;
		//}
		//// ------------------------------------------------- Hide Group
		//if (LOWORD(wParam) == IDC_CKHIDEGROUP)
		//{
		//	HWND temp = GetDlgItem(hDlg, IDC_CKHIDEGROUP);
		//	HWND temp1 = GetDlgItem(hDlg, IDC_CKSHOWONLYGROUPS);

		//	if (App->CL_Right_Groups->CK_HideGroup == 1)
		//	{
		//		App->CL_Right_Groups->CK_HideGroup = 0;
		//		App->Cl_Ogre->RenderListener->Show_HideGroup = 0;
		//		SendMessage(temp, BM_SETCHECK, 0, 0);
		//	}
		//	else
		//	{
		//		App->CL_Right_Groups->CK_HideGroup = 1;
		//		App->Cl_Ogre->RenderListener->Show_HideGroup = 1;
		//		SendMessage(temp, BM_SETCHECK, 1, 0);

		//		App->CL_Right_Groups->CK_ShowGroupOnly = 0;
		//		App->Cl_Ogre->RenderListener->ShowOnlySubMesh = 0;
		//		SendMessage(temp1, BM_SETCHECK, 0, 0);
		//	}
		//	return TRUE;
		//}
	}
	}
	return FALSE;
}

// *************************************************************************
// *						ViewerBasePic Terry Bernie	  				   *
// *************************************************************************
bool CALLBACK VM_Groups::ViewerBasePic(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	if (msg == WM_PAINT)
	{
		PAINTSTRUCT	ps;
		HDC			hDC;
		RECT		Rect;

		hDC = BeginPaint(hwnd, &ps);
		GetClientRect(hwnd, &Rect);
		Rect.left--;
		Rect.bottom--;
		FillRect(hDC, &Rect, (HBRUSH)(RGB(0, 255, 0)));

		if (App->CL_Vm_Groups->Sel_BaseBitmap != NULL)
		{
			RECT	Source;
			RECT	Dest;
			HDC		hDC;

			Source.left = 0;
			Source.top = 0;
			Source.bottom = App->CL_Vm_Groups->BasePicHeight;
			Source.right = App->CL_Vm_Groups->BasePicWidth;

			Dest = Rect;

			hDC = GetDC(hwnd);
			SetStretchBltMode(hDC, HALFTONE);

			App->CL_Vm_Groups->RenderTexture_Blit(hDC, App->CL_Vm_Groups->Sel_BaseBitmap, &Source, &Dest);
			ReleaseDC(hwnd, hDC);
		}
		EndPaint(hwnd, &ps);
		return 0;
	}
	return 0;// DefWindowProc(hwnd, msg, wParam, lParam);
}

// *************************************************************************
// *					RenderTexture_Blit Terry Bernie		  		   *
// *************************************************************************
bool VM_Groups::RenderTexture_Blit(HDC hDC, HBITMAP Bmp, const RECT *SourceRect, const RECT *DestRect)
{
	HDC		MemDC;
	int		SourceWidth;
	int		SourceHeight;
	int		DestWidth;
	int		DestHeight;

	MemDC = CreateCompatibleDC(hDC);
	if (MemDC == NULL)
		return FALSE;

	if (Bmp)
	{
		SelectObject(MemDC, Bmp);

		SourceWidth = SourceRect->right - SourceRect->left;
		SourceHeight = SourceRect->bottom - SourceRect->top;
		DestWidth = DestRect->right - DestRect->left;
		DestHeight = DestRect->bottom - DestRect->top;
		SetStretchBltMode(hDC, COLORONCOLOR);
		StretchBlt(hDC,
			DestRect->left,
			DestRect->top,
			DestHeight,
			DestHeight,
			MemDC,
			SourceRect->left,
			SourceRect->top,
			SourceWidth,
			SourceHeight,
			SRCCOPY);
	}

	DeleteDC(MemDC);

	return TRUE;
}

// *************************************************************************
// *					Update_Groups_Dialog Terry Bernie		  		   *
// *************************************************************************
void VM_Groups::Update_Groups_Dialog(int Index)
{
	SelectedGroup = Index;
	int TextureID = App->CL_Vm_Model->S_TextureInfo[Index]->ActorMaterialIndex;

	Sel_BaseBitmap = App->CL_Vm_Model->S_MeshGroup[Index]->Base_Bitmap;

	BITMAP bm;
	GetObject(Sel_BaseBitmap, sizeof(bm), &bm);

	BasePicWidth = bm.bmWidth;
	BasePicHeight = bm.bmHeight;

	ShowWindow(GetDlgItem(RightGroups_Hwnd, IDC_BASETEXTURE2), 0);
	ShowWindow(GetDlgItem(RightGroups_Hwnd, IDC_BASETEXTURE2), 1);

	
	SetDlgItemText(RightGroups_Hwnd, IDC_RGGROUPNAME, (LPCTSTR)App->CL_Vm_Model->S_MeshGroup[Index]->GroupName);
	SetDlgItemText(RightGroups_Hwnd, IDC_RGTEXTURENAME, (LPCTSTR)App->CL_Vm_Model->S_MeshGroup[Index]->Text_FileName);


	char buff[255];
	_itoa(TextureID, buff, 10);
	SetDlgItemText(RightGroups_Hwnd, IDC_GROUPID, (LPCTSTR)buff);
}

// *************************************************************************
// *				ChangeTexture_ModelLocation Terry Bernie			   *
// *************************************************************************
bool VM_Groups::ChangeTexture_ModelLocation(void)
{

	int test = 0;

	//------------------------------------------------------------ Assimp
	if (App->CL_Vm_Model->Model_Type == LoadedFile_Assimp)
	{

		test = App->CL_Vm_FileIO->OpenTextureFile("Equity10 Replace Texture", NULL, NULL);//App->S_ModelTexturePaths[0]->TextureFolder,1);
		if (test == 0) { return 0; }

		// Render Texture
		App->CL_Vm_Textures->Soil_Load_Texture(App->CL_Vm_Textures->g_Texture, App->CL_Vm_FileIO->Texture_Path_FileName, SelectedGroup);//App->S_MeshGroup[mIndex]->Soil_TextureIndex);
																												   // Preview Texture
		strcpy(App->CL_Vm_Model->S_MeshGroup[SelectedGroup]->Text_FileName, App->CL_Vm_FileIO->Texture_FileName);
		strcpy(App->CL_Vm_Model->S_MeshGroup[SelectedGroup]->Text_PathFileName, App->CL_Vm_FileIO->Texture_Path_FileName);

		App->CL_Vm_Textures->TexureToWinPreviewFullPath(SelectedGroup, App->CL_Vm_FileIO->Texture_Path_FileName);
		Update_Groups_Dialog(SelectedGroup);

		return 1;
	}
	
	//------------------------------------------------------------ Genesis 3D
	if (App->CL_Vm_Model->Model_Type == LoadedFile_Actor)
	{

		test = App->CL_Vm_FileIO->OpenTextureFile("Equity10 Replace Texture", NULL, NULL);//App->S_ModelTexturePaths[0]->TextureFolder,1);
		if (test == 0) { return 0; }

		char mFileName[1024];
		strcpy(mFileName, App->CL_Vm_FileIO->Texture_Path_FileName);

		App->CL_Vm_Textures->Soil_Load_Texture(App->CL_Vm_Textures->g_Texture, App->CL_Vm_FileIO->Texture_Path_FileName, App->CL_Vm_Model->S_TextureInfo[App->CL_Vm_Groups->SelectedGroup]->ActorMaterialIndex);//App->S_MeshGroup[mIndex]->Soil_TextureIndex);

		strcpy(App->CL_Vm_Model->S_MeshGroup[SelectedGroup]->Text_FileName, App->CL_Vm_FileIO->Texture_FileName);
		strcpy(App->CL_Vm_Model->S_MeshGroup[SelectedGroup]->Text_PathFileName, App->CL_Vm_FileIO->Texture_Path_FileName);

		App->CL_Vm_Textures->TexureToWinPreviewFullPath(SelectedGroup, App->CL_Vm_FileIO->Texture_Path_FileName);
		Update_Groups_Dialog(SelectedGroup);

		char buf[255];
		strcpy(buf, App->CL_Vm_Model->S_MeshGroup[SelectedGroup]->GroupName);
		strcat(buf, " -> ");
		strcat(buf, App->CL_Vm_Model->S_MeshGroup[SelectedGroup]->Text_FileName);

	//	App->CL_FileView->ChangeItem_Name(App->CL_FileView->HT_Textures_Mapped_Item[SelectedGroup], buf);

		if (_stricmp(mFileName + strlen(mFileName) - 4, ".BMP") == 0)
		{
			App->CL_Vm_Genesis3D->ChangeTexture(mFileName);
		}
	//	//---------------------------------------------------------- TGA
	//	if (stricmp(mFileName + strlen(mFileName) - 4, ".TGA") == 0)
	//	{
	//		
	//	}
	//	//---------------------------------------------------------- JPG
	//	if (stricmp(mFileName + strlen(mFileName) - 4, ".jpg") == 0)
	//	{
	//		App->CL_Textures->Texture_To_Bmp(mFileName);
	//		App->CL_Textures->Genesis_ChangeTexture("Etemp.bmp");
	//		remove("Etemp.bmp");
	//	}
	//	//---------------------------------------------------------- PNG
	//	if (stricmp(mFileName + strlen(mFileName) - 4, ".png") == 0)
	//	{
	//		App->CL_Textures->Texture_To_Bmp(mFileName);
	//		App->CL_Textures->Genesis_ChangeTexture("Etemp.bmp");
	//		remove("Etemp.bmp");
	//	}
	//	//---------------------------------------------------------- DDS
	//	if (stricmp(mFileName + strlen(mFileName) - 4, ".dds") == 0)
	//	{
	//		App->CL_Textures->Texture_To_Bmp(mFileName);
	//		App->CL_Textures->Genesis_ChangeTexture("Etemp.bmp");
	//		remove("Etemp.bmp");

	//	}
	
	}

	return TRUE;
}
