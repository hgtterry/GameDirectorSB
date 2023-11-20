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
#include "SB_Mesh_Mgr.h"

#include "EntTypeName.h"
//#include "facelist.h"

enum BrushFlags
{
	BRUSH_SOLID = 0x0001,
	BRUSH_WINDOW = 0x0002,
	BRUSH_WAVY = 0x0004,
	BRUSH_DETAIL = 0x0008,	//not included in vis calculations
	BRUSH_HOLLOWCUT = 0x0010,
	BRUSH_TRANSLUCENT = 0x0020,
	BRUSH_EMPTY = 0x0040,
	BRUSH_SUBTRACT = 0x0080,
	BRUSH_CLIP = 0x0100,
	BRUSH_FLOCKING = 0x0200,
	BRUSH_HOLLOW = 0x0400,
	BRUSH_SHEET = 0x0800,
	BRUSH_HIDDEN = 0x1000,
	BRUSH_LOCKED = 0x2000,
	BRUSH_HINT = 0x4000,
	BRUSH_AREA = 0x8000
	// All flags larger than 0x8000 (i.e. 0x00010000 through 0x80000000)
	// are reserved for user contents.
};

struct tag_FaceList
{
	int NumFaces;
	int Limit;
	Face** Faces;
	geBoolean Dirty;
	Box3d Bounds;
};

#define NUM_VIEWS (4)

struct tag_Level3
{
	BrushList* Brushes;
	CEntityArray* Entities;
	char* WadPath;
	char* HeadersDir;
	// changed QD Actors
	char* ActorsDir;
	geBoolean ShowActors;
	char* PawnIniPath;
	// end change
	EntTypeNameList* EntTypeNames;
	GroupListType* Groups;
	SizeInfo* WadSizeInfos;
	CWadFile* WadFile;
	EntityTable* pEntityDefs;

	ModelInfo_Type	ModelInfo;

	SkyFaceTexture SkyFaces[6];
	geVec3d SkyRotationAxis;
	geFloat SkyRotationSpeed;
	geFloat	SkyTextureScale;

	// level edit settings
	CompileParamsType CompileParams;
	int GroupVisSetting;
	EntityViewList* pEntityView;

	GridInfo GridSettings;
	geBoolean BspRebuildFlag;
	ViewStateInfo ViewInfo[NUM_VIEWS];

	BrushTemplate_Arch ArchTemplate;
	BrushTemplate_Box	BoxTemplate;
	BrushTemplate_Cone	ConeTemplate;
	BrushTemplate_Cylinder CylinderTemplate;
	BrushTemplate_Spheroid	SpheroidTemplate;
	BrushTemplate_Staircase StaircaseTemplate;

	geVec3d TemplatePos;

	float DrawScale;		// default draw scale
	float LightmapScale;	// default lightmap scale
};

SB_Mesh_Mgr::SB_Mesh_Mgr(void)
{
	mBrush_Index = 0;
	mBrush_Name[0] = 0;
	memset(mAdjusedIndex_Store, 0, 500);

	mBrushCount = 0;
	mSubBrushCount = 0;
	mTextureCount = 0;

	Brush_Flag = 1;
	Group_Flag = 0;

	Mesh_Viewer_HWND = nullptr;
}

SB_Mesh_Mgr::~SB_Mesh_Mgr(void)
{
}

// *************************************************************************
// *	  		Start_Brush_Viewer:- Terry and Hazel Flanigan 2023		   *
// *************************************************************************
void SB_Mesh_Mgr::Start_Brush_Viewer()
{
	App->Get_Current_Document();

	Mesh_Viewer_HWND = CreateDialog(App->hInst, (LPCTSTR)IDD_SB_BRUSH_VIEWER, App->Equity_Dlg_hWnd, (DLGPROC)Brush_Viewer_Proc);
	
}

// *************************************************************************
// *			Brush_Viewer_Proc:- Terry and Hazel Flanigan 2023			   *
// *************************************************************************
LRESULT CALLBACK SB_Mesh_Mgr::Brush_Viewer_Proc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{

	switch (message)
	{
	case WM_INITDIALOG:
	{
		SendDlgItemMessage(hDlg, IDC_LISTBRUSHES, WM_SETFONT, (WPARAM)App->Font_CB15, MAKELPARAM(TRUE, 0));
		SendDlgItemMessage(hDlg, IDC_LISTDATA, WM_SETFONT, (WPARAM)App->Font_CB15, MAKELPARAM(TRUE, 0));

		SendDlgItemMessage(hDlg, IDC_BTJUSTBRUSH, WM_SETFONT, (WPARAM)App->Font_CB15, MAKELPARAM(TRUE, 0));
		SendDlgItemMessage(hDlg, IDC_BT_LOOKAT, WM_SETFONT, (WPARAM)App->Font_CB15, MAKELPARAM(TRUE, 0));
		
		SendDlgItemMessage(hDlg, IDOK, WM_SETFONT, (WPARAM)App->Font_CB15, MAKELPARAM(TRUE, 0));
		SendDlgItemMessage(hDlg, IDCANCEL, WM_SETFONT, (WPARAM)App->Font_CB15, MAKELPARAM(TRUE, 0));

		SendDlgItemMessage(hDlg, IDC_BT_BRUSH, WM_SETFONT, (WPARAM)App->Font_CB15, MAKELPARAM(TRUE, 0));
		SendDlgItemMessage(hDlg, IDC_BT_GROUP, WM_SETFONT, (WPARAM)App->Font_CB15, MAKELPARAM(TRUE, 0));

		SendDlgItemMessage(hDlg, IDC_ST_TEXTURE, WM_SETFONT, (WPARAM)App->Font_CB15, MAKELPARAM(TRUE, 0));
		SendDlgItemMessage(hDlg, IDC_BT_CONVERT, WM_SETFONT, (WPARAM)App->Font_CB15, MAKELPARAM(TRUE, 0));
		
		SendDlgItemMessage(hDlg, IDC_LISTBRUSHES, LB_RESETCONTENT, (WPARAM)0, (LPARAM)0);

		HWND Temp = GetDlgItem(hDlg, IDC_BT_MESH);
		if (App->CLSB_Ogre->RenderListener->ShowFaces == 1)
		{
			SendMessage(Temp, BM_SETIMAGE, (WPARAM)IMAGE_BITMAP, (LPARAM)(HANDLE)App->Hnd_MeshOn_Bmp);
		}
		else
		{
			SendMessage(Temp, BM_SETIMAGE, (WPARAM)IMAGE_BITMAP, (LPARAM)(HANDLE)App->Hnd_MeshOff_Bmp);
		}

		App->CLSB_Mesh_Mgr->Update_Brush_List(hDlg);
		App->CLSB_Mesh_Mgr->UpdateBrushData(hDlg, 0);

		App->CLSB_Ogre->RenderListener->Render_Just_Brush = 0;

		return TRUE;
	}

	case WM_CTLCOLORSTATIC:
	{
		if (GetDlgItem(hDlg, IDC_ST_TEXTURE) == (HWND)lParam)
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

		if (some_item->idFrom == IDC_BTJUSTBRUSH && some_item->code == NM_CUSTOMDRAW)
		{
			LPNMCUSTOMDRAW item = (LPNMCUSTOMDRAW)some_item;
			App->Custom_Button_Toggle(item, App->CLSB_Ogre->RenderListener->Render_Just_Brush);
			return CDRF_DODEFAULT;
		}

		if (some_item->idFrom == IDC_BT_LOOKAT && some_item->code == NM_CUSTOMDRAW)
		{
			LPNMCUSTOMDRAW item = (LPNMCUSTOMDRAW)some_item;
			App->Custom_Button_Normal(item);
			return CDRF_DODEFAULT;
		}
		
		if (some_item->idFrom == IDOK && some_item->code == NM_CUSTOMDRAW)
		{
			LPNMCUSTOMDRAW item = (LPNMCUSTOMDRAW)some_item;
			App->Custom_Button_Normal(item);
			return CDRF_DODEFAULT;
		}

		if (some_item->idFrom == IDCANCEL && some_item->code == NM_CUSTOMDRAW)
		{
			LPNMCUSTOMDRAW item = (LPNMCUSTOMDRAW)some_item;
			App->Custom_Button_Normal(item);
			return CDRF_DODEFAULT;
		}

		if (some_item->idFrom == IDC_BT_BRUSH && some_item->code == NM_CUSTOMDRAW)
		{
			LPNMCUSTOMDRAW item = (LPNMCUSTOMDRAW)some_item;
			App->Custom_Button_Toggle(item, App->CLSB_Mesh_Mgr->Brush_Flag);
			return CDRF_DODEFAULT;
		}

		if (some_item->idFrom == IDC_BT_GROUP && some_item->code == NM_CUSTOMDRAW)
		{
			LPNMCUSTOMDRAW item = (LPNMCUSTOMDRAW)some_item;
			App->Custom_Button_Toggle(item, App->CLSB_Mesh_Mgr->Group_Flag);
			return CDRF_DODEFAULT;
		}

		return CDRF_DODEFAULT;
	}

	case WM_COMMAND:

		if (LOWORD(wParam) == IDC_BT_CONVERT)
		{
			App->CLSB_Mesh_Mgr->WE_Convert_All_Texture_Groups();
			return TRUE;
		}
		
		if (LOWORD(wParam) == IDC_BT_TEXTUREIDPLUSE)
		{
			App->CLSB_Ogre->RenderListener->TextureID++;
			
			char buf[MAX_PATH];
			sprintf(buf, "%i %s", App->CLSB_Ogre->RenderListener->TextureID, App->CLSB_Mesh_Mgr->TextureName2[App->CLSB_Ogre->RenderListener->TextureID]);
			SetDlgItemText(hDlg, IDC_ST_TEXTURE, (LPCTSTR)buf);

			return TRUE;
		}

		if (LOWORD(wParam) == IDC_BT_TEXTUREIDMINUS)
		{
			App->CLSB_Ogre->RenderListener->TextureID--;

			char buf[MAX_PATH];
			sprintf(buf, "%i %s", App->CLSB_Ogre->RenderListener->TextureID, App->CLSB_Mesh_Mgr->TextureName2[App->CLSB_Ogre->RenderListener->TextureID]);
			SetDlgItemText(hDlg, IDC_ST_TEXTURE, (LPCTSTR)buf);

			return TRUE;
		}
		
		if (LOWORD(wParam) == IDC_BT_MESH)
		{
			HWND Temp = GetDlgItem(hDlg, IDC_BT_MESH);

			if (App->CLSB_Ogre->RenderListener->ShowFaces == 1)
			{
				App->CLSB_Ogre->RenderListener->ShowFaces = 0;
				SendMessage(Temp, BM_SETIMAGE, (WPARAM)IMAGE_BITMAP, (LPARAM)(HANDLE)App->Hnd_MeshOff_Bmp);
			}
			else
			{
				App->CLSB_Ogre->RenderListener->ShowFaces = 1;
				SendMessage(Temp, BM_SETIMAGE, (WPARAM)IMAGE_BITMAP, (LPARAM)(HANDLE)App->Hnd_MeshOn_Bmp);
			}

			return TRUE;
		}
		
		if (LOWORD(wParam) == IDC_BT_BRUSH)
		{
			if (App->CLSB_Ogre->RenderListener->Render_Brush_Group_Flag == 1)
			{
				App->CLSB_Ogre->RenderListener->Render_Brush_Group_Flag = 0;
				App->CLSB_Mesh_Mgr->Brush_Flag = 1;
				App->CLSB_Mesh_Mgr->Group_Flag = 0;
			}
			else
			{
				App->CLSB_Ogre->RenderListener->Render_Brush_Group_Flag = 1;
				App->CLSB_Mesh_Mgr->Group_Flag = 1;
				App->CLSB_Mesh_Mgr->Brush_Flag = 0;
			}

			App->CLSB_Model->Model_Type = Enums::LoadedFile_Brushes;
			App->CLSB_Mesh_Mgr->Update_Brush_List(hDlg);

			RedrawWindow(hDlg, NULL, NULL, RDW_INVALIDATE | RDW_UPDATENOW);

			return TRUE;
		}

		if (LOWORD(wParam) == IDC_BT_GROUP)
		{
			if (App->CLSB_Ogre->RenderListener->Render_Brush_Group_Flag == 1)
			{
				App->CLSB_Ogre->RenderListener->Render_Brush_Group_Flag = 0;
				App->CLSB_Mesh_Mgr->Brush_Flag = 1;
				App->CLSB_Mesh_Mgr->Group_Flag = 0;
			}
			else
			{
				App->CLSB_Ogre->RenderListener->Render_Brush_Group_Flag = 1;
				App->CLSB_Mesh_Mgr->Group_Flag = 1;
				App->CLSB_Mesh_Mgr->Brush_Flag = 0;
			}

			App->CLSB_Model->Model_Type = Enums::LoadedFile_Assimp;
			App->CLSB_Mesh_Mgr->Update_Brush_List(hDlg);

			RedrawWindow(hDlg, NULL, NULL, RDW_INVALIDATE | RDW_UPDATENOW);

			return TRUE;
		}
		
		if (LOWORD(wParam) == IDC_BT_LOOKAT)
		{
			App->CLSB_Mesh_Mgr->Set_BBox_Selected_Brush(App->CLSB_Ogre->RenderListener->Selected_Brush_Index);
			App->CLSB_Ogre->mCamera->lookAt(Ogre::Vector3(App->CLSB_Model->Sel_Brush_Centre.x, App->CLSB_Model->Sel_Brush_Centre.y, App->CLSB_Model->Sel_Brush_Centre.z));
			return TRUE;
		}

		if (LOWORD(wParam) == IDC_BTJUSTBRUSH)
		{
			if (App->CLSB_Model->Model_Type == Enums::LoadedFile_Brushes)
			{
				if (App->CLSB_Ogre->RenderListener->Render_Just_Brush == 1)
				{
					App->CLSB_Ogre->RenderListener->Render_Just_Brush = 0;
				}
				else
				{
					App->CLSB_Ogre->RenderListener->Render_Just_Brush = 1;
				}
			}

			if (App->CLSB_Model->Model_Type == Enums::LoadedFile_Assimp)
			{
				if (App->CLSB_Ogre->RenderListener->ShowOnlySubMesh == 1)
				{
					App->CLSB_Ogre->RenderListener->ShowOnlySubMesh = 0;
				}
				else
				{
					App->CLSB_Ogre->RenderListener->ShowOnlySubMesh = 1;
				}
			}

			App->CLSB_Ogre->RenderFrame();

			return TRUE;
		}

		if (LOWORD(wParam) == IDC_LISTBRUSHES)
		{
			char buff[256];
			int Index = 0;
			Index = SendDlgItemMessage(hDlg, IDC_LISTBRUSHES, LB_GETCURSEL, (WPARAM)0, (LPARAM)0);

			if (Index == -1)
			{
				return 1;
			}

			if (App->CLSB_Model->Model_Type == Enums::LoadedFile_Brushes)
			{
				App->CLSB_Ogre->RenderListener->Selected_Brush_Index = Index;
				App->CLSB_Ogre->RenderListener->Selected_Group_Index = App->CLSB_Model->B_Brush[Index]->Group_Index;
			}

			if (App->CLSB_Model->Model_Type == Enums::LoadedFile_Assimp)
			{
				App->CLSB_Ogre->RenderListener->Selected_Group = Index;
			}

			SetDlgItemText(hDlg, IDC_STBRUSHINDEX, (LPCTSTR)itoa(Index, buff, 10));

			App->CLSB_Mesh_Mgr->UpdateBrushData(hDlg, Index);

			return TRUE;
		}

		if (LOWORD(wParam) == IDOK)
		{
			//App->CLSB_Dialogs->F_ListData_Dlg_Active = 0;
			EndDialog(hDlg, LOWORD(wParam));
			return TRUE;
		}

		if (LOWORD(wParam) == IDCANCEL)
		{
			//App->CLSB_Dialogs->F_ListData_Dlg_Active = 0;
			EndDialog(hDlg, LOWORD(wParam));
			return TRUE;
		}

		break;
	}

	return FALSE;
}

// *************************************************************************
// *		Update_Brush_List:- Terry and Hazel Flanigan 2023		 	   *
// *************************************************************************
void SB_Mesh_Mgr::Update_Brush_List(HWND hDlg)
{
	SendDlgItemMessage(hDlg, IDC_LISTBRUSHES, LB_RESETCONTENT, (WPARAM)0, (LPARAM)0);

	char buf[MAX_PATH];
	int Count = 0;

	if (App->CLSB_Model->Model_Type == Enums::LoadedFile_Brushes)
	{
		while (Count < App->CLSB_Model->BrushCount)
		{
			sprintf(buf, "%i %s", Count, App->CLSB_Model->B_Brush[Count]->Brush_Name);
			SendDlgItemMessage(hDlg, IDC_LISTBRUSHES, LB_ADDSTRING, (WPARAM)0, (LPARAM)buf);
			Count++;
		}
	}

	if (App->CLSB_Model->Model_Type == Enums::LoadedFile_Assimp)
	{
		while (Count < App->CLSB_Model->GroupCount)
		{
			sprintf(buf, "%i %s", Count, App->CLSB_Model->Group[Count]->GroupName);
			SendDlgItemMessage(hDlg, IDC_LISTBRUSHES, LB_ADDSTRING, (WPARAM)0, (LPARAM)buf);
			Count++;
		}
	}
}

// *************************************************************************
// *			UpdateBrushData:- Terry and Hazel Flanigan 2023		 	   *
// *************************************************************************
void SB_Mesh_Mgr::UpdateBrushData(HWND hDlg, int Index)
{
	SendDlgItemMessage(hDlg, IDC_LISTDATA, LB_RESETCONTENT, (WPARAM)0, (LPARAM)0);

	char buf[MAX_PATH];

	if (App->CLSB_Model->Model_Type == Enums::LoadedFile_Brushes)
	{
		sprintf(buf, "Group Index %i %s", App->CLSB_Model->B_Brush[Index]->Group_Index, App->CLSB_Model->B_Brush[Index]->Brush_Name);
		SendDlgItemMessage(hDlg, IDC_LISTDATA, LB_ADDSTRING, (WPARAM)0, (LPARAM)buf);

		sprintf(buf, "Faces %i", App->CLSB_Model->B_Brush[Index]->Face_Count);
		SendDlgItemMessage(hDlg, IDC_LISTDATA, LB_ADDSTRING, (WPARAM)0, (LPARAM)buf);

		sprintf(buf, "Vertices %i", App->CLSB_Model->B_Brush[Index]->Vertice_Count);
		SendDlgItemMessage(hDlg, IDC_LISTDATA, LB_ADDSTRING, (WPARAM)0, (LPARAM)buf);

		int Count = 0;

		while (Count < App->CLSB_Model->B_Brush[Index]->Face_Count)
		{
			int TextureID = App->CLSB_Model->B_Brush[Index]->Face_Data[Count].TextID;

			sprintf(buf, "Text_ID %i %s", TextureID, TextureName2[TextureID]);
			SendDlgItemMessage(hDlg, IDC_LISTDATA, LB_ADDSTRING, (WPARAM)0, (LPARAM)buf);
			Count++;
		}

		App->CLSB_Mesh_Mgr->Set_BBox_Selected_Brush(Index);
	}

	if (App->CLSB_Model->Model_Type == Enums::LoadedFile_Assimp)
	{
		sprintf(buf, "Group Name %s", App->CLSB_Model->Group[Index]->GroupName);
		SendDlgItemMessage(hDlg, IDC_LISTDATA, LB_ADDSTRING, (WPARAM)0, (LPARAM)buf);

		sprintf(buf, "Faces %i", App->CLSB_Model->Group[Index]->GroupFaceCount);
		SendDlgItemMessage(hDlg, IDC_LISTDATA, LB_ADDSTRING, (WPARAM)0, (LPARAM)buf);

		sprintf(buf, "Vertices %i", App->CLSB_Model->Group[Index]->GroupVertCount);
		SendDlgItemMessage(hDlg, IDC_LISTDATA, LB_ADDSTRING, (WPARAM)0, (LPARAM)buf);
	}

	
}

//---------------------------------------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------------------------------------

// *************************************************************************
// * 		Brush_CSG_Callback:- Terry and Hazel Flanigan 2023			   *
// *************************************************************************
signed int SB_Mesh_Mgr::Brush_CSG_Callback(const Brush* pBrush, void* lParam)
{
	return (App->m_pDoc->BrushIsVisible(pBrush) && (!Brush_IsHint(pBrush)) && (!Brush_IsClip(pBrush)));
}

// *************************************************************************
// * 		Delete_Brush_List:- Terry and Hazel Flanigan 2023			   *
// *************************************************************************
void SB_Mesh_Mgr::Delete_Brush_List()
{
	SB_Model* pModel = App->CLSB_Model;

	int Count = 0;
	while (Count < 11999)
	{
		if (pModel->B_Brush[Count] != nullptr)
		{
			delete pModel->B_Brush[Count];
			//Debug
		}

		pModel->B_Brush[Count] = nullptr;

		Count++;
	}

	App->CLSB_Model->BrushCount = 0;

}

// *************************************************************************
// * 		WE_Build_Brush_List:- Terry and Hazel Flanigan 2023			   *
// *************************************************************************
void SB_Mesh_Mgr::WE_Build_Brush_List(int ExpSelected)
{
	App->Get_Current_Document();

	Delete_Brush_List();

	App->CLSB_Model->BrushCount = 0;

	mBrushCount = 0;
	mSubBrushCount = 0;

	char Path[MAX_PATH];
	strcpy(Path, App->WorldEditor_Directory);
	strcat(Path, "Data\\3DSTemp.txt");

	BrushList* BList;
	geBoolean fResult;

	BList = Level_GetBrushes(App->CLSB_Doc->pLevel);

	if (!ExpSelected)	// Build All
	{
		fResult = WE_Level_Build_Brushes(reinterpret_cast<tag_Level3*> (App->CLSB_Doc->pLevel), "FileName", BList, 0, 0, -1);
	}
	else				// Build Selected
	{
		int i, GroupID, GroupCount;
		char NewFileName[MAX_PATH];
		GroupID = -1;
		GroupCount = 1;

		for (i = 0; i < GroupCount; i++)
		{
			BrushList* SBList;
			Brush* pBrush;
			BrushIterator bi;

			SBList = BrushList_Create();
			pBrush = BrushList_GetFirst(BList, &bi);

			while (pBrush != NULL)
			{

				if (SelBrushList_Find(App->CLSB_Doc->pSelBrushes, pBrush))
				{
					Brush* pClone = Brush_Clone(pBrush);
					BrushList_Append(SBList, pClone);
				}

				pBrush = BrushList_GetNext(&bi);
			}
			// do CSG
			{
				ModelIterator	mi;
				int				i, CurId = 0;
				ModelInfo_Type* ModelInfo;
				Model* pMod;

				BrushList_ClearAllCSG(SBList);

				BrushList_DoCSG(SBList, CurId, Brush_CSG_Callback, this);

				//build individual model mini trees
				ModelInfo = Level_GetModelInfo(App->CLSB_Doc->pLevel);
				pMod = ModelList_GetFirst(ModelInfo->Models, &mi);

				for (i = 0; i < ModelList_GetCount(ModelInfo->Models); i++)
				{
					CurId = Model_GetId(pMod);

					BrushList_DoCSG(SBList, CurId, Brush_CSG_Callback, this);
				}
			}

			fResult = WE_Level_Build_Brushes(reinterpret_cast<tag_Level3*> (App->CLSB_Doc->pLevel), NewFileName, SBList, 0, 0, -1);
			if (!fResult)
			{
				App->Say("Error exporting group");
			}

			BrushList_Destroy(&SBList);
		}
	}

	//App->Say("Converted NEW");
}

// *************************************************************************
// *		WE_Level_Build_Brushes:- Terry and Hazel Flanigan 2023		   *
// *************************************************************************
bool SB_Mesh_Mgr::WE_Level_Build_Brushes(Level3* pLevel, const char* Filename, BrushList* BList, int ExpSelected, geBoolean ExpLights, int GroupID)
{
	int i;
	geBoolean* WrittenTex;

	WrittenTex = (geBoolean*)calloc(sizeof(geBoolean), pLevel->WadFile->mBitmapCount);

	// which textures are used?
	BrushList_GetUsedTextures(BList, WrittenTex, pLevel->WadFile);

	// Add Textures GL
	int AdjustedIndex = 0;
	for (i = 0; i < pLevel->WadFile->mBitmapCount; i++)
	{
		if (WrittenTex[i])
		{
			char matname[MAX_PATH];
			int j, k;
			strncpy(matname, pLevel->WadFile->mBitmaps[i].Name, MAX_PATH - 1);

			strcpy(TextureName2[AdjustedIndex], matname);

			mAdjusedIndex_Store[AdjustedIndex] = i;

			AddTexture_GL(NULL, matname, AdjustedIndex);

			AdjustedIndex++;
		}
	}

	mTextureCount = AdjustedIndex;
	

	WE_BrushList_Decode(BList, GE_FALSE);

	free(WrittenTex);

	return 1;
}

// *************************************************************************
// *			WE_BrushList_Decode:- Terry and Hazel Flanigan 2023		   *
// *************************************************************************
bool SB_Mesh_Mgr::WE_BrushList_Decode(BrushList* BList, geBoolean SubBrush)
{
	Brush* pBrush;
	BrushIterator bi;

	pBrush = BrushList_GetFirst(BList, &bi);

	while (pBrush != NULL)
	{
		if (mSubBrushCount == 0 && pBrush->Flags & 1 || pBrush->Flags & 1024)
		{
			if (SubBrush == 0)
			{
				strcpy(mBrush_Name, pBrush->Name);
				mBrush_Index = mBrushCount;
			}
		}

		if (!WE_Brush_Create(pBrush))
		{
			return GE_FALSE;
		}

		pBrush = BrushList_GetNext(&bi);

		if (SubBrush)
		{
			mSubBrushCount++;
		}
		else
		{
			mBrushCount++;
		}
	}

	mSubBrushCount = 0;

	if (!SubBrush)
	{
		mBrushCount = 0;
	}

	return GE_TRUE;
}

// *************************************************************************
// *			WE_Brush_Create:- Terry and Hazel Flanigan 2023			   *
// *************************************************************************
bool SB_Mesh_Mgr::WE_Brush_Create(const Brush* b)
{
	assert(ofile);
	assert(b);

	switch (b->Type)
	{
	case	BRUSH_MULTI:
		return WE_BrushList_Decode(b->BList, GE_TRUE);

	case	BRUSH_LEAF:
		if (b->BList)
		{
			return WE_BrushList_Decode(b->BList, GE_TRUE);
		}
		else
		{
			if (!(b->Flags & (BRUSH_HOLLOW | BRUSH_HOLLOWCUT | BRUSH_SUBTRACT)))
			{
				return WE_FaceList_Create(b, b->Faces, mBrushCount, mSubBrushCount);
			}
			else if ((b->Flags & BRUSH_SUBTRACT) && !(b->Flags & (BRUSH_HOLLOW | BRUSH_HOLLOWCUT)))
				mBrushCount--;
		}
		break;


	case	BRUSH_CSG:
		if (!(b->Flags & (BRUSH_HOLLOW | BRUSH_HOLLOWCUT | BRUSH_SUBTRACT)))
			return WE_FaceList_Create(b, b->Faces, mBrushCount, mSubBrushCount);
		break;
	default:
		assert(0);		// invalid brush type
		break;
	}

	return GE_TRUE;
}

// *************************************************************************
// *		WE_FaceList_Create:- Terry and Hazel Flanigan 2023			   *
// *************************************************************************
bool SB_Mesh_Mgr::WE_FaceList_Create(const Brush* b, const FaceList* pList, int BrushCount, int SubBrushCount)
{

	App->CLSB_Model->Create_Brush_XX(App->CLSB_Model->BrushCount);
	App->CLSB_Model->B_Brush[App->CLSB_Model->BrushCount]->Group_Index = mBrush_Index;
	strcpy(App->CLSB_Model->B_Brush[App->CLSB_Model->BrushCount]->Brush_Name, mBrush_Name);

	int i, j, k, num_faces, num_verts, num_mats, num_chars, curnum_verts;
	char matname[MAX_PATH];

	char* matf = (char*)calloc(sizeof(char), pList->NumFaces);

	assert(pList != NULL);
	assert(f != NULL);

	num_faces = num_verts = num_mats = num_chars = 0;
	// get the total number of verts, faces and materials of the object

	for (i = 0; i < pList->NumFaces; i++)
	{
		curnum_verts = Face_GetNumPoints(pList->Faces[i]);
		num_faces += (curnum_verts - 2);
		num_verts += curnum_verts;

		if (!matf[i])
		{
			matf[i] = 1;
			num_mats++;

			for (j = i + 1; j < pList->NumFaces; j++)
			{
				if (strcmp(Face_GetTextureName(pList->Faces[i]), Face_GetTextureName(pList->Faces[j])) == 0)
					matf[j] = 1;
			}

			strncpy(matname, Face_GetTextureName(pList->Faces[i]), MAX_PATH);
		}
	}

	for (i = 0; i < pList->NumFaces; i++)
		matf[i] = 0;

	// -----------------------------------  Vertices
	int VertIndex = 0;

	App->CLSB_Model->B_Brush[App->CLSB_Model->BrushCount]->Vertice_Count = num_verts;
	App->CLSB_Model->B_Brush[App->CLSB_Model->BrushCount]->vertex_Data.resize(num_verts);
	App->CLSB_Model->B_Brush[App->CLSB_Model->BrushCount]->Normal_Data.resize(num_verts);

	for (i = 0; i < pList->NumFaces; i++)
	{
		const geVec3d* verts;
		verts = Face_GetPoints(pList->Faces[i]);
		curnum_verts = Face_GetNumPoints(pList->Faces[i]);
		for (j = 0; j < curnum_verts; j++)
		{
			App->CLSB_Model->B_Brush[App->CLSB_Model->BrushCount]->vertex_Data[VertIndex].x = verts[j].X;
			App->CLSB_Model->B_Brush[App->CLSB_Model->BrushCount]->vertex_Data[VertIndex].y = verts[j].Y;
			App->CLSB_Model->B_Brush[App->CLSB_Model->BrushCount]->vertex_Data[VertIndex].z = verts[j].Z;

			App->CLSB_Model->B_Brush[App->CLSB_Model->BrushCount]->Normal_Data[VertIndex].x = 0.5;
			App->CLSB_Model->B_Brush[App->CLSB_Model->BrushCount]->Normal_Data[VertIndex].y = 0.5;
			App->CLSB_Model->B_Brush[App->CLSB_Model->BrushCount]->Normal_Data[VertIndex].z = 0.5;

			VertIndex++;
		}
	}

	int UVIndex = 0;
	// -----------------------------------  UVS
	App->CLSB_Model->B_Brush[App->CLSB_Model->BrushCount]->MapCord_Data.resize(num_verts);
	for (i = 0; i < pList->NumFaces; i++)
	{
		const TexInfo_Vectors* TVecs = Face_GetTextureVecs(pList->Faces[i]);
		const geVec3d* verts;
		geVec3d uVec, vVec;
		geFloat U, V;

		int txSize, tySize;

		Face_GetTextureSize(pList->Faces[i], &txSize, &tySize);

		// make sure that the texture size is set correctly (division!)
		if (txSize == 0)
			txSize = 32;
		if (tySize == 0)
			tySize = 32;

		geVec3d_Scale(&TVecs->uVec, 1.f / (geFloat)txSize, &uVec);
		geVec3d_Scale(&TVecs->vVec, -1.f / (geFloat)tySize, &vVec);

		verts = Face_GetPoints(pList->Faces[i]);
		curnum_verts = Face_GetNumPoints(pList->Faces[i]);

		for (j = 0; j < curnum_verts; j++)
		{
			U = geVec3d_DotProduct(&(verts[j]), &uVec);
			V = geVec3d_DotProduct(&(verts[j]), &vVec);
			U += (TVecs->uOffset / txSize);
			V -= (TVecs->vOffset / tySize);

			App->CLSB_Model->B_Brush[App->CLSB_Model->BrushCount]->MapCord_Data[UVIndex].u = U;
			App->CLSB_Model->B_Brush[App->CLSB_Model->BrushCount]->MapCord_Data[UVIndex].v = V;
			UVIndex++;
		}
	}

	int FaceIndex = 0;
	// -----------------------------------  Faces

	App->CLSB_Model->B_Brush[App->CLSB_Model->BrushCount]->Face_Count = num_faces;
	App->CLSB_Model->B_Brush[App->CLSB_Model->BrushCount]->Face_Data.resize(num_faces);
	num_verts = 0;
	for (i = 0; i < pList->NumFaces; i++)
	{
		curnum_verts = Face_GetNumPoints(pList->Faces[i]);
		for (j = 0; j < curnum_verts - 2; j++)
		{
			App->CLSB_Model->B_Brush[App->CLSB_Model->BrushCount]->Face_Data[FaceIndex].a = num_verts;
			App->CLSB_Model->B_Brush[App->CLSB_Model->BrushCount]->Face_Data[FaceIndex].b = num_verts + 2 + j;
			App->CLSB_Model->B_Brush[App->CLSB_Model->BrushCount]->Face_Data[FaceIndex].c = num_verts + 1 + j;

			FaceIndex++;
		}

		num_verts += curnum_verts;
	}

	// -----------------------------------  Texture IDs
	int TextureId = 0;

	for (i = 0; i < pList->NumFaces; i++)
	{
		if (!matf[i])
		{
			matf[i] = 1;

			int curnum_faces = (Face_GetNumPoints(pList->Faces[i]) - 2);

			for (j = i + 1; j < pList->NumFaces; j++)
			{
				if (strcmp(Face_GetTextureName(pList->Faces[i]), Face_GetTextureName(pList->Faces[j])) == 0)
				{
					curnum_faces += (Face_GetNumPoints(pList->Faces[j]) - 2);
				}
			}

			strncpy(matname, Face_GetTextureName(pList->Faces[i]), 11);

			// Material Name
			int DibId = Get_Adjusted_Index(Face_GetTextureDibId(pList->Faces[i]));


			// write number of faces that have this texture


			// write face numbers
			curnum_faces = 0;
			for (j = 0; j < i; j++)
			{
				curnum_faces += (Face_GetNumPoints(pList->Faces[j]) - 2);
			}

			curnum_verts = Face_GetNumPoints(pList->Faces[i]);
			for (j = 0; j < curnum_verts - 2; j++)
			{
				TextureId = Get_Adjusted_Index(Face_GetTextureDibId(pList->Faces[i]));
				App->CLSB_Model->B_Brush[App->CLSB_Model->BrushCount]->Face_Data[curnum_faces + j].TextID = TextureId;

			}

			curnum_faces += (curnum_verts - 2);

			for (j = i + 1; j < pList->NumFaces; j++)
			{
				curnum_verts = Face_GetNumPoints(pList->Faces[j]);
				if (strcmp(Face_GetTextureName(pList->Faces[i]), Face_GetTextureName(pList->Faces[j])) == 0)
				{
					matf[j] = 1;
					for (k = 0; k < curnum_verts - 2; k++)
					{
						TextureId = Get_Adjusted_Index(Face_GetTextureDibId(pList->Faces[i]));
						App->CLSB_Model->B_Brush[App->CLSB_Model->BrushCount]->Face_Data[curnum_faces + k].TextID = TextureId;
					}
				}

				curnum_faces += (curnum_verts - 2);
			}
		}
	}

	free(matf);

	App->CLSB_Model->BrushCount++;

	return GE_TRUE;
}

// *************************************************************************
// *			AddTexture_GL:- Terry and Hazel Flanigan 2023		  	   *
// *************************************************************************
bool SB_Mesh_Mgr::AddTexture_GL(geVFile* BaseFile, const char* TextureName, int GroupIndex)
{
	App->Get_Current_Document();

	//Debug
	HWND	PreviewWnd;
	HBITMAP	hbm;
	HDC		hDC;

	geBitmap* Bitmap = NULL;
	CWadFile* pWad;
	pWad = NULL;
	pWad = Level_GetWadFile(App->CLSB_Doc->pLevel);
	for (int index = 0; index < pWad->mBitmapCount; index++)
	{
		char mName[MAX_PATH];

		CString Name = pWad->mBitmaps[index].Name;
		strcpy(mName, Name);

		bool test = strcmp(mName, TextureName);
		if (test == 0)
		{
			Bitmap = pWad->mBitmaps[index].bmp;

			char TempTextureFile_BMP[MAX_PATH];
			strcpy(TempTextureFile_BMP, App->WorldEditor_Directory);
			strcat(TempTextureFile_BMP, "\\");
			strcat(TempTextureFile_BMP, "TextureLoad.bmp");

			App->CLSB_Textures->Genesis_WriteToBmp(Bitmap, TempTextureFile_BMP);

			App->CLSB_Textures->Soil_Load_Texture(App->CLSB_Ogre->RenderListener->g_BrushTexture, TempTextureFile_BMP, GroupIndex);

			DeleteFile((LPCTSTR)TempTextureFile_BMP);
		}
	}

	return TRUE;
}

// *************************************************************************
// *			Get_Adjusted_Index:- Terry and Hazel Flanigan 2023		   *
// *************************************************************************
int SB_Mesh_Mgr::Get_Adjusted_Index(int RealIndex)
{
	int Count = 0;
	while (Count < 500)
	{
		if (mAdjusedIndex_Store[Count] == RealIndex)
		{
			return Count;
		}

		Count++;
	}

	return -1;
}

// *************************************************************************
// *		 Set_BBox_Selected_Brush:- Terry and Hazel Flanigan 2023	   *
// *************************************************************************
void SB_Mesh_Mgr::Set_BBox_Selected_Brush(int Index)
{
	SB_Model* pModel = App->CLSB_Model;
	
	pModel->Sel_Brush_BB_Min.x = pModel->B_Brush[Index]->vertex_Data[0].x;
	pModel->Sel_Brush_BB_Min.y = pModel->B_Brush[Index]->vertex_Data[0].y;
	pModel->Sel_Brush_BB_Min.z = pModel->B_Brush[Index]->vertex_Data[0].z;

	pModel->Sel_Brush_BB_Max.x = pModel->B_Brush[Index]->vertex_Data[0].x;
	pModel->Sel_Brush_BB_Max.y = pModel->B_Brush[Index]->vertex_Data[0].y;
	pModel->Sel_Brush_BB_Max.z = pModel->B_Brush[Index]->vertex_Data[0].z;

	int VertCount = 0;

	while (VertCount < pModel->B_Brush[Index]->Vertice_Count)
	{
		if (pModel->B_Brush[Index]->vertex_Data[VertCount].x < pModel->Sel_Brush_BB_Min.x) pModel->Sel_Brush_BB_Min.x = pModel->B_Brush[Index]->vertex_Data[VertCount].x;
		if (pModel->B_Brush[Index]->vertex_Data[VertCount].y < pModel->Sel_Brush_BB_Min.y) pModel->Sel_Brush_BB_Min.y = pModel->B_Brush[Index]->vertex_Data[VertCount].y;
		if (pModel->B_Brush[Index]->vertex_Data[VertCount].z < pModel->Sel_Brush_BB_Min.z) pModel->Sel_Brush_BB_Min.z = pModel->B_Brush[Index]->vertex_Data[VertCount].z;

		if (pModel->B_Brush[Index]->vertex_Data[VertCount].x > pModel->Sel_Brush_BB_Max.x) pModel->Sel_Brush_BB_Max.x = pModel->B_Brush[Index]->vertex_Data[VertCount].x;
		if (pModel->B_Brush[Index]->vertex_Data[VertCount].y > pModel->Sel_Brush_BB_Max.y) pModel->Sel_Brush_BB_Max.y = pModel->B_Brush[Index]->vertex_Data[VertCount].y;
		if (pModel->B_Brush[Index]->vertex_Data[VertCount].z > pModel->Sel_Brush_BB_Max.z) pModel->Sel_Brush_BB_Max.z = pModel->B_Brush[Index]->vertex_Data[VertCount].z;

		VertCount++;
	}

	pModel->Sel_Brush_Size.x = (fabs(pModel->Sel_Brush_BB_Max.x - pModel->Sel_Brush_BB_Min.x));
	pModel->Sel_Brush_Size.y = (fabs(pModel->Sel_Brush_BB_Max.y - pModel->Sel_Brush_BB_Min.y));
	pModel->Sel_Brush_Size.z = (fabs(pModel->Sel_Brush_BB_Max.z - pModel->Sel_Brush_BB_Min.z));

	pModel->Sel_Brush_radius = (pModel->Sel_Brush_Size.x > pModel->Sel_Brush_Size.z) ? pModel->Sel_Brush_Size.z / 2.0f : pModel->Sel_Brush_Size.x / 2.0f;

	pModel->Sel_Brush_Centre.x = (pModel->Sel_Brush_BB_Min.x + pModel->Sel_Brush_BB_Max.x) / 2.0f;
	pModel->Sel_Brush_Centre.y = (pModel->Sel_Brush_BB_Min.y + pModel->Sel_Brush_BB_Max.y) / 2.0f;
	pModel->Sel_Brush_Centre.z = (pModel->Sel_Brush_BB_Min.z + pModel->Sel_Brush_BB_Max.z) / 2.0f;
}

// *************************************************************************
// *	Set_BBox_All_Selected_Brushes:- Terry and Hazel Flanigan 2023	   *
// *************************************************************************
void SB_Mesh_Mgr::Set_BBox_All_Selected_Brushes()
{
	SB_Model* pModel = App->CLSB_Model;

	pModel->BB_Min.x = pModel->B_Brush[0]->vertex_Data[0].x;
	pModel->BB_Min.y = pModel->B_Brush[0]->vertex_Data[0].y;
	pModel->BB_Min.z = pModel->B_Brush[0]->vertex_Data[0].z;

	pModel->BB_Max.x = pModel->B_Brush[0]->vertex_Data[0].x;
	pModel->BB_Max.y = pModel->B_Brush[0]->vertex_Data[0].y;
	pModel->BB_Max.z = pModel->B_Brush[0]->vertex_Data[0].z;

	int Count = 0;
	int VertCount = 0;

	while (Count < pModel->BrushCount)
	{

		VertCount = 0;
		while (VertCount < pModel->B_Brush[Count]->Vertice_Count)
		{
			if (pModel->B_Brush[Count]->vertex_Data[VertCount].x < pModel->BB_Min.x) pModel->BB_Min.x = pModel->B_Brush[Count]->vertex_Data[VertCount].x;
			if (pModel->B_Brush[Count]->vertex_Data[VertCount].y < pModel->BB_Min.y) pModel->BB_Min.y = pModel->B_Brush[Count]->vertex_Data[VertCount].y;
			if (pModel->B_Brush[Count]->vertex_Data[VertCount].z < pModel->BB_Min.z) pModel->BB_Min.z = pModel->B_Brush[Count]->vertex_Data[VertCount].z;

			if (pModel->B_Brush[Count]->vertex_Data[VertCount].x > pModel->BB_Max.x) pModel->BB_Max.x = pModel->B_Brush[Count]->vertex_Data[VertCount].x;
			if (pModel->B_Brush[Count]->vertex_Data[VertCount].y > pModel->BB_Max.y) pModel->BB_Max.y = pModel->B_Brush[Count]->vertex_Data[VertCount].y;
			if (pModel->B_Brush[Count]->vertex_Data[VertCount].z > pModel->BB_Max.z) pModel->BB_Max.z = pModel->B_Brush[Count]->vertex_Data[VertCount].z;

			VertCount++;
		}

		Count++;
	}

	pModel->Size.x = (fabs(pModel->BB_Max.x - pModel->BB_Min.x));
	pModel->Size.y = (fabs(pModel->BB_Max.y - pModel->BB_Min.y));
	pModel->Size.z = (fabs(pModel->BB_Max.z - pModel->BB_Min.z));

	pModel->radius = (pModel->Size.x > pModel->Size.z) ? pModel->Size.z / 2.0f : pModel->Size.x / 2.0f;

	pModel->Centre.x = (pModel->BB_Min.x + pModel->BB_Max.x) / 2.0f;
	pModel->Centre.y = (pModel->BB_Min.y + pModel->BB_Max.y) / 2.0f;
	pModel->Centre.z = (pModel->BB_Min.z + pModel->BB_Max.z) / 2.0f;
}

// *************************************************************************
// * 		Delete_Group_Brushes:- Terry and Hazel Flanigan 2023		   *
// *************************************************************************
void SB_Mesh_Mgr::Delete_Group_Brushes()
{
	SB_Model* pModel = App->CLSB_Model;

	int Count = 0;
	while (Count < 4999)
	{
		if (pModel->Group[Count] != nullptr)
		{
			delete pModel->Group[Count];
		}

		pModel->Group[Count] = nullptr;

		Count++;
	}

	App->CLSB_Model->GroupCount = 0;
	App->CLSB_Model->VerticeCount = 0;
}

// *************************************************************************
// *	WE_Convert_All_Texture_Groups:- Terry and Hazel Flanigan 2023	   *
// *************************************************************************
bool SB_Mesh_Mgr::WE_Convert_All_Texture_Groups()
{
	int mTotalVertices = 0;

	Delete_Group_Brushes();

	strcpy(App->CLSB_Model->JustName, "Test");

	App->CLSB_Model->Set_Groupt_Count(mTextureCount);

	int Count = 0;
	while (Count < mTextureCount)
	{
		App->CLSB_Model->Create_Mesh_Group(Count);
		int FaceCount = WE_Get_Vertice_Count(Count);

		strcpy(App->CLSB_Model->Group[Count]->GroupName, TextureName2[Count]);
		strcpy(App->CLSB_Model->Group[Count]->MaterialName, TextureName2[Count]);

		char buff[MAX_PATH];
		strcpy(buff, TextureName2[Count]);
		strcat(buff, ".bmp");
		strcpy(App->CLSB_Model->Group[Count]->Text_FileName, buff);

		App->CLSB_Model->Group[Count]->MaterialIndex = Count;
		App->CLSB_Model->Group[Count]->vertex_Data.resize(FaceCount * 3);
		App->CLSB_Model->Group[Count]->Normal_Data.resize(FaceCount * 3);
		App->CLSB_Model->Group[Count]->MapCord_Data.resize(FaceCount * 3);
		App->CLSB_Model->Group[Count]->Face_Data.resize(FaceCount);

		WE_Convert_To_Texture_Group(Count);

		mTotalVertices = mTotalVertices + FaceCount;

		Count++;
	}

	App->CLSB_Model->VerticeCount = mTotalVertices * 3;
	App->CLSB_Model->FaceCount = mTotalVertices;

	App->CLSB_Model->Model_Type = Enums::LoadedFile_Assimp;
	Update_Brush_List(Mesh_Viewer_HWND);

	return true;
}

// *************************************************************************
// *	WE_Convert_To_Texture_Group:- Terry and Hazel Flanigan 2023	 	   *
// *************************************************************************
bool SB_Mesh_Mgr::WE_Convert_To_Texture_Group(int TextureID)
{
	int Count = 0;
	int FaceCount = 0;
	int vertexIndex = 0;
	int FaceIndex = 0;
	int FacePos = 0;

	int A = 0;
	int B = 0;
	int C = 0;

	float X = 0;
	float Y = 0;
	float Z = 0;

	float U = 0;
	float V = 0;
	
	int BrushCount = App->CLSB_Model->BrushCount;
	Count = 0;

	while (Count < BrushCount)
	{
		FaceCount = 0;
		while (FaceCount < App->CLSB_Model->B_Brush[Count]->Face_Count)
		{
			if (App->CLSB_Model->B_Brush[Count]->Face_Data[FaceCount].TextID == TextureID)
			{

				A = App->CLSB_Model->B_Brush[Count]->Face_Data[FaceCount].a;
				B = App->CLSB_Model->B_Brush[Count]->Face_Data[FaceCount].b;
				C = App->CLSB_Model->B_Brush[Count]->Face_Data[FaceCount].c;

				X = App->CLSB_Model->B_Brush[Count]->vertex_Data[A].x;
				Y = App->CLSB_Model->B_Brush[Count]->vertex_Data[A].y;
				Z = App->CLSB_Model->B_Brush[Count]->vertex_Data[A].z;

				App->CLSB_Model->Group[TextureID]->vertex_Data[vertexIndex].x = X;
				App->CLSB_Model->Group[TextureID]->vertex_Data[vertexIndex].y = Y;
				App->CLSB_Model->Group[TextureID]->vertex_Data[vertexIndex].z = Z;

				U = App->CLSB_Model->B_Brush[Count]->MapCord_Data[A].u, 
				V = App->CLSB_Model->B_Brush[Count]->MapCord_Data[A].v;

				App->CLSB_Model->Group[TextureID]->MapCord_Data[vertexIndex].u = U;
				App->CLSB_Model->Group[TextureID]->MapCord_Data[vertexIndex].v = V;

				X = App->CLSB_Model->B_Brush[Count]->Normal_Data[A].x;
				Y = App->CLSB_Model->B_Brush[Count]->Normal_Data[A].y;
				Z = App->CLSB_Model->B_Brush[Count]->Normal_Data[A].z;

				App->CLSB_Model->Group[TextureID]->Normal_Data[vertexIndex].x = X;
				App->CLSB_Model->Group[TextureID]->Normal_Data[vertexIndex].y = Y;
				App->CLSB_Model->Group[TextureID]->Normal_Data[vertexIndex].z = Z;

				vertexIndex++;

				X = App->CLSB_Model->B_Brush[Count]->vertex_Data[B].x;
				Y = App->CLSB_Model->B_Brush[Count]->vertex_Data[B].y;
				Z = App->CLSB_Model->B_Brush[Count]->vertex_Data[B].z;

				App->CLSB_Model->Group[TextureID]->vertex_Data[vertexIndex].x = X;
				App->CLSB_Model->Group[TextureID]->vertex_Data[vertexIndex].y = Y;
				App->CLSB_Model->Group[TextureID]->vertex_Data[vertexIndex].z = Z;

				U = App->CLSB_Model->B_Brush[Count]->MapCord_Data[B].u,
				V = App->CLSB_Model->B_Brush[Count]->MapCord_Data[B].v;

				App->CLSB_Model->Group[TextureID]->MapCord_Data[vertexIndex].u = U;
				App->CLSB_Model->Group[TextureID]->MapCord_Data[vertexIndex].v = V;

				X = App->CLSB_Model->B_Brush[Count]->Normal_Data[B].x;
				Y = App->CLSB_Model->B_Brush[Count]->Normal_Data[B].y;
				Z = App->CLSB_Model->B_Brush[Count]->Normal_Data[B].z;

				App->CLSB_Model->Group[TextureID]->Normal_Data[vertexIndex].x = X;
				App->CLSB_Model->Group[TextureID]->Normal_Data[vertexIndex].y = Y;
				App->CLSB_Model->Group[TextureID]->Normal_Data[vertexIndex].z = Z;

				vertexIndex++;

				X = App->CLSB_Model->B_Brush[Count]->vertex_Data[C].x;
				Y = App->CLSB_Model->B_Brush[Count]->vertex_Data[C].y;
				Z = App->CLSB_Model->B_Brush[Count]->vertex_Data[C].z;

				App->CLSB_Model->Group[TextureID]->vertex_Data[vertexIndex].x = X;
				App->CLSB_Model->Group[TextureID]->vertex_Data[vertexIndex].y = Y;
				App->CLSB_Model->Group[TextureID]->vertex_Data[vertexIndex].z = Z;

				U = App->CLSB_Model->B_Brush[Count]->MapCord_Data[C].u,
				V = App->CLSB_Model->B_Brush[Count]->MapCord_Data[C].v;

				App->CLSB_Model->Group[TextureID]->MapCord_Data[vertexIndex].u = U;
				App->CLSB_Model->Group[TextureID]->MapCord_Data[vertexIndex].v = V;

				X = App->CLSB_Model->B_Brush[Count]->Normal_Data[C].x;
				Y = App->CLSB_Model->B_Brush[Count]->Normal_Data[C].y;
				Z = App->CLSB_Model->B_Brush[Count]->Normal_Data[C].z;

				App->CLSB_Model->Group[TextureID]->Normal_Data[vertexIndex].x = X;
				App->CLSB_Model->Group[TextureID]->Normal_Data[vertexIndex].y = Y;
				App->CLSB_Model->Group[TextureID]->Normal_Data[vertexIndex].z = Z;

				vertexIndex++;

				App->CLSB_Model->Group[TextureID]->Face_Data[FacePos].a = FaceIndex;
				FaceIndex++;
				App->CLSB_Model->Group[TextureID]->Face_Data[FacePos].b = FaceIndex;
				FaceIndex++;
				App->CLSB_Model->Group[TextureID]->Face_Data[FacePos].c = FaceIndex;
				FaceIndex++;
				FacePos++;
			}

			FaceCount++;
		}

		Count++;
	}

	App->CLSB_Model->Group[TextureID]->GroupVertCount = vertexIndex;
	App->CLSB_Model->Group[TextureID]->GroupFaceCount = vertexIndex/3;

	return 1;
}

// *************************************************************************
// *		WE_Get_Vertice_Count:- Terry and Hazel Flanigan 2023	 	   *
// *************************************************************************
int SB_Mesh_Mgr::WE_Get_Vertice_Count(int TextureID)
{
	int Count = 0;
	int FaceCount = 0;
	int TotalFaceCount = 0;
	
	int BrushCount = App->CLSB_Model->BrushCount;
	Count = 0;

	while (Count < BrushCount)
	{
		FaceCount = 0;
		while (FaceCount < App->CLSB_Model->B_Brush[Count]->Face_Count)
		{
			if (App->CLSB_Model->B_Brush[Count]->Face_Data[FaceCount].TextID == TextureID)
			{
				TotalFaceCount++;
			}

			FaceCount++;
		}

		Count++;
	}

	return TotalFaceCount;
}
