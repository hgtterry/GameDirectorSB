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
#include "resource.h"
#include "A_TabsGroups_Dlg.h"

#pragma warning( disable : 4101)

struct tag_BrushList
{
	Brush* First;
	Brush* Last;
};

A_TabsGroups_Dlg::A_TabsGroups_Dlg(void)
{
	GroupsDlg_Hwnd = NULL;
	Groups_Dlg_Created = NULL;

	Selected_Index = -1;
	Selected_Brush = NULL;
}

A_TabsGroups_Dlg::~A_TabsGroups_Dlg(void)
{
}

// *************************************************************************
// *	  	Show_GroupsDialog:- Terry and Hazel Flanigan 2023			   *
// *************************************************************************
void A_TabsGroups_Dlg::Show_GroupsDialog(bool Show)
{
	ShowWindow(GroupsDlg_Hwnd, Show);
}

// *************************************************************************
// *	  	Start_GroupsDialog:- Terry and Hazel Flanigan 2023			   *
// *************************************************************************
void A_TabsGroups_Dlg::Start_GroupsDialog()
{
	GroupsDlg_Hwnd = CreateDialog(App->hInst, (LPCTSTR)IDD_SB_TABSBRUSHES, App->CL_TabsControl->Tabs_Control_Hwnd, (DLGPROC)Groups_Proc);

	Groups_Dlg_Created = 1;

	Fill_ListBox();
	Update_Dlg_Controls();
}

// *************************************************************************
// *			 Groups_Proc:- Terry and Hazel Flanigan 2023			   *
// *************************************************************************
LRESULT CALLBACK A_TabsGroups_Dlg::Groups_Proc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{

	switch (message)
	{
	case WM_INITDIALOG:
	{
		SendDlgItemMessage(hDlg, IDC_GD_BRUSHLIST, WM_SETFONT, (WPARAM)App->Font_CB15, MAKELPARAM(TRUE, 0));
		SendDlgItemMessage(hDlg, IDC_ST_GD_GROUPS, WM_SETFONT, (WPARAM)App->Font_CB18, MAKELPARAM(TRUE, 0));
		SendDlgItemMessage(hDlg, IDC_BRUSHCOUNT, WM_SETFONT, (WPARAM)App->Font_CB15, MAKELPARAM(TRUE, 0));
		SendDlgItemMessage(hDlg, IDC_ST_GD_BRUSHCOUNT, WM_SETFONT, (WPARAM)App->Font_CB15, MAKELPARAM(TRUE, 0));
		SendDlgItemMessage(hDlg, IDC_BT_GD_BRUSHPROPERTIES, WM_SETFONT, (WPARAM)App->Font_CB15, MAKELPARAM(TRUE, 0));

		SendDlgItemMessage(hDlg, IDC_ST_GD_SELECTED, WM_SETFONT, (WPARAM)App->Font_CB15, MAKELPARAM(TRUE, 0));
		SendDlgItemMessage(hDlg, IDC_ST_SELECTED, WM_SETFONT, (WPARAM)App->Font_CB15, MAKELPARAM(TRUE, 0));
		SendDlgItemMessage(hDlg, IDC_BT_DIMENSIONS, WM_SETFONT, (WPARAM)App->Font_CB15, MAKELPARAM(TRUE, 0));
		SendDlgItemMessage(hDlg, IDC_BT_DELETEBRUSH, WM_SETFONT, (WPARAM)App->Font_CB15, MAKELPARAM(TRUE, 0));
		
		return TRUE;
	}
	case WM_CTLCOLORSTATIC:
	{
		if (GetDlgItem(hDlg, IDC_ST_GD_GROUPS) == (HWND)lParam)
		{
			SetBkColor((HDC)wParam, RGB(0, 0, 0));
			SetTextColor((HDC)wParam, RGB(0, 0, 255));
			SetBkMode((HDC)wParam, TRANSPARENT);
			return (UINT)App->AppBackground;
		}

		if (GetDlgItem(hDlg, IDC_BRUSHCOUNT) == (HWND)lParam)
		{
			SetBkColor((HDC)wParam, RGB(0, 0, 0));
			SetTextColor((HDC)wParam, RGB(0, 0, 0));
			SetBkMode((HDC)wParam, TRANSPARENT);
			return (UINT)App->AppBackground;
		}

		if (GetDlgItem(hDlg, IDC_ST_GD_BRUSHCOUNT) == (HWND)lParam)
		{
			SetBkColor((HDC)wParam, RGB(0, 0, 0));
			SetTextColor((HDC)wParam, RGB(0, 0, 0));
			SetBkMode((HDC)wParam, TRANSPARENT);
			return (UINT)App->AppBackground;
		}

		if (GetDlgItem(hDlg, IDC_ST_GD_SELECTED) == (HWND)lParam)
		{
			SetBkColor((HDC)wParam, RGB(0, 0, 0));
			SetTextColor((HDC)wParam, RGB(0, 0, 0));
			SetBkMode((HDC)wParam, TRANSPARENT);
			return (UINT)App->AppBackground;
		}

		if (GetDlgItem(hDlg, IDC_ST_SELECTED) == (HWND)lParam)
		{
			SetBkColor((HDC)wParam, RGB(0, 0, 0));
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

		if (some_item->idFrom == IDC_BT_GD_BRUSHPROPERTIES && some_item->code == NM_CUSTOMDRAW)
		{
			LPNMCUSTOMDRAW item = (LPNMCUSTOMDRAW)some_item;

			bool test = IsWindowEnabled(GetDlgItem(hDlg, IDC_BT_GD_BRUSHPROPERTIES));
			if (test == 0)
			{
				App->Custom_Button_Greyed(item);
			}
			else
			{
				App->Custom_Button_Normal(item);
			}

			return CDRF_DODEFAULT;
		}

		if (some_item->idFrom == IDC_BT_DIMENSIONS && some_item->code == NM_CUSTOMDRAW)
		{
			LPNMCUSTOMDRAW item = (LPNMCUSTOMDRAW)some_item;
			bool test = IsWindowEnabled(GetDlgItem(hDlg, IDC_BT_DIMENSIONS));
			if (test == 0)
			{
				App->Custom_Button_Greyed(item);
			}
			else
			{
				App->Custom_Button_Normal(item);
			}
			return CDRF_DODEFAULT;
		}

		if (some_item->idFrom == IDC_BT_DELETEBRUSH && some_item->code == NM_CUSTOMDRAW)
		{
			LPNMCUSTOMDRAW item = (LPNMCUSTOMDRAW)some_item;
			bool test = IsWindowEnabled(GetDlgItem(hDlg, IDC_BT_DELETEBRUSH));
			if (test == 0)
			{
				App->Custom_Button_Greyed(item);
			}
			else
			{
				App->Custom_Button_Normal(item);
			}
			return CDRF_DODEFAULT;
		}

		return CDRF_DODEFAULT;
	}

	case WM_COMMAND:
	{
		if (LOWORD(wParam) == IDC_BT_DELETEBRUSH)
		{
			App->CLSB_Dialogs->YesNo("Are you sure", "Do you want to Delete the selected Brushes");

			bool Doit = App->CLSB_Dialogs->Canceled;
			if (Doit == 0)
			{
				App->m_pDoc = (CFusionDoc*)App->m_pMainFrame->GetCurrentDoc();
				App->CLSB_Doc->DeleteCurrentThing();
			}

			return TRUE;
		}

		if (LOWORD(wParam) == IDC_BT_DIMENSIONS)
		{
			App->CLSB_Brushes->Start_Dimensions_Dlg();
			return TRUE;
		}

		if (LOWORD(wParam) == IDC_GD_BRUSHLIST)
		{
			if (App->CL_TabsGroups_Dlg->Groups_Dlg_Created == 1)
			{
				App->CL_TabsGroups_Dlg->List_Selection_Changed(1);
			}
			return TRUE;
		}

		if (LOWORD(wParam) == IDC_BT_GD_BRUSHPROPERTIES)
		{
			App->CL_TabsGroups_Dlg->Start_Properties_Dlg();
			SendDlgItemMessage(hDlg, IDC_GD_BRUSHLIST, LB_SETCURSEL, (WPARAM)App->CL_TabsGroups_Dlg->Selected_Index, (LPARAM)0);
			return TRUE;
		}

		// -----------------------------------------------------------------
		if (LOWORD(wParam) == IDOK)
		{
			//App->CL_TextureDialog->f_TextureDlg_Active = 0;
			//EndDialog(hDlg, LOWORD(wParam));
			return TRUE;
		}

		if (LOWORD(wParam) == IDCANCEL)
		{
			//App->CL_TextureDialog->f_TextureDlg_Active = 0;
			//EndDialog(hDlg, LOWORD(wParam));
			return TRUE;
		}

		break;
	}
	}
	return FALSE;
}

// *************************************************************************
// *	  		Get_Index:- Terry and Hazel Flanigan 2023				   *
// *************************************************************************
void A_TabsGroups_Dlg::Get_Index(const Brush* b)
{
	App->Get_Current_Document();

	Level* pLevel = App->m_pDoc->pLevel;
	BrushList* pList = Level_GetBrushes(App->m_pDoc->pLevel);

	int Selected = 0;
	int Count = 0;

	b = pList->First;

	while (b != NULL)
	{
		Selected = App->m_pDoc->BrushIsSelected(b);

		if (Selected == 1)
		{
			SendDlgItemMessage(GroupsDlg_Hwnd, IDC_GD_BRUSHLIST, LB_SETCURSEL, (WPARAM)Count, (LPARAM)0);
			Selected_Index = Count;
			List_Selection_Changed(0);
		}

		Count++;
		b = b->Next;
	}

	Update_Dlg_SelectedBrushesCount();
}

// *************************************************************************
// *	  	List_Selection_Changed:- Terry and Hazel Flanigan 2023		   *
// *************************************************************************
void A_TabsGroups_Dlg::List_Selection_Changed(bool Clear)
{
	int Index = SendDlgItemMessage(GroupsDlg_Hwnd, IDC_GD_BRUSHLIST, LB_GETCURSEL, (WPARAM)0, (LPARAM)0);
	if	(Index == -1)
	{
		//App->Say("ListBox No Selection Available");
	}
	else
	{
		if (Groups_Dlg_Created == 1)
		{
			Selected_Index = Index;
			OnSelchangeBrushlist(Index,Clear);
		}
	}
}

// *************************************************************************
// *		OnSelchangeBrushlist:- Terry and Hazel Flanigan 2023		   *
// *************************************************************************
void A_TabsGroups_Dlg::OnSelchangeBrushlist(int Index, bool Clear)
{
	App->Get_Current_Document();

	int			c ;
	geBoolean	bChanged = FALSE ;

	c = App->CL_World->Get_Brush_Count();

	if( c > 0 )
	{
		if (Clear == 1)
		{
			App->m_pDoc->ResetAllSelections() ;
			App->m_pDoc->UpdateSelected();
		}
		
		Selected_Brush = App->CL_World->Get_Brush_ByIndex( Index );

		SelBrushList_Add(App->m_pDoc->pSelBrushes, Selected_Brush);

		if (Clear == 1)
		{
			Update_Dlg_Controls();
			App->CLSB_TopTabs->Update_Dlg_Controls();
		}
		//m_pDoc->DoBrushSelection( Selected_Brush, brushSelToggle) ;
		bChanged = GE_TRUE;
	}


	if( bChanged )
	{
		App->m_pDoc->UpdateSelected() ;
		App->m_pDoc->UpdateAllViews(UAV_ALL3DVIEWS, NULL);
	}
}

// *************************************************************************
// *			 Fill_ListBox:- Terry and Hazel Flanigan 2023			   *
// *************************************************************************
void A_TabsGroups_Dlg::Fill_ListBox()
{
	if (Groups_Dlg_Created == 1)
	{
		SendDlgItemMessage(GroupsDlg_Hwnd, IDC_GD_BRUSHLIST, LB_RESETCONTENT, (WPARAM)0, (LPARAM)0);

		App->m_pDoc = (CFusionDoc*)App->m_pMainFrame->GetCurrentDoc();

		Level *pLevel = App->m_pDoc->pLevel;
		BrushList *pList = Level_GetBrushes (App->m_pDoc->pLevel);

		int Count = 0;
		Brush * b;
		b = pList->First;
		while (b != NULL)
		{
			SendDlgItemMessage(GroupsDlg_Hwnd, IDC_GD_BRUSHLIST, LB_ADDSTRING, (WPARAM)0,(LPARAM)App->CL_Brush->Brush_GetName(b));
			Count++;
			b = b->Next;
		}


		char buff[100];
		SetDlgItemText(GroupsDlg_Hwnd, IDC_BRUSHCOUNT, itoa(Count, buff, 10));
	}
}

// *************************************************************************
// *	Update_Dlg_SelectedBrushesCount:- Terry and Hazel Flanigan 2023	   *
// *************************************************************************
void A_TabsGroups_Dlg::Update_Dlg_SelectedBrushesCount()
{
	char buff[100];
	int NumSelBrushes = SelBrushList_GetSize(App->m_pDoc->pSelBrushes);
	SetDlgItemText(GroupsDlg_Hwnd, IDC_ST_GD_SELECTED, itoa(NumSelBrushes, buff, 10));
}

// *************************************************************************
// *	  	Start_Properties_Dlg:- Terry and Hazel Flanigan 2023		   *
// *************************************************************************
void A_TabsGroups_Dlg::Start_Properties_Dlg()
{
	DialogBox(App->hInst, (LPCTSTR)IDD_SB_BRUSH_PROPERTIES, App->MainHwnd, (DLGPROC)Properties_Proc);
}

// *************************************************************************
// *			Properties_Proc:- Terry and Hazel Flanigan 2023			   *
// *************************************************************************
LRESULT CALLBACK A_TabsGroups_Dlg::Properties_Proc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{

	switch (message)
	{
	case WM_INITDIALOG:
	{
		SendDlgItemMessage(hDlg, IDC_BRUSH_PROPERTIESLIST, WM_SETFONT, (WPARAM)App->Font_CB18, MAKELPARAM(TRUE, 0));
		SendDlgItemMessage(hDlg, IDC_LIST_SELECTEDBRUSHES, WM_SETFONT, (WPARAM)App->Font_CB18, MAKELPARAM(TRUE, 0));

		SendDlgItemMessage(hDlg, IDC_ST_BP_SELECTEDBRUSHES, WM_SETFONT, (WPARAM)App->Font_CB18, MAKELPARAM(TRUE, 0));
		
		App->CL_TabsGroups_Dlg->List_SelectedBrushes(hDlg);
		App->CL_TabsGroups_Dlg->List_BrushData(hDlg);

		return TRUE;
	}
	
	case WM_CTLCOLORSTATIC:
	{
		if (GetDlgItem(hDlg, IDC_ST_BP_SELECTEDBRUSHES) == (HWND)lParam)
		{
			SetBkColor((HDC)wParam, RGB(0, 0, 0));
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
	{

		if (LOWORD(wParam) == IDC_LIST_SELECTEDBRUSHES)
		{
		
			int Index = SendDlgItemMessage(hDlg, IDC_LIST_SELECTEDBRUSHES, LB_GETCURSEL, (WPARAM)0, (LPARAM)0);
			if (Index == -1)
			{
			
			}
			else
			{
				App->CL_TabsGroups_Dlg->Selected_Index = Index;
				App->CL_TabsGroups_Dlg->Selected_Brush = SelBrushList_GetBrush(App->m_pDoc->pSelBrushes, Index);
				App->CL_TabsGroups_Dlg->List_BrushData(hDlg);
			}

			return TRUE;
		}

		// -----------------------------------------------------------------
		if (LOWORD(wParam) == IDOK)
		{
			//App->CL_TextureDialog->f_TextureDlg_Active = 0;
			EndDialog(hDlg, LOWORD(wParam));
			return TRUE;
		}

		if (LOWORD(wParam) == IDCANCEL)
		{
			//App->CL_TextureDialog->f_TextureDlg_Active = 0;
			EndDialog(hDlg, LOWORD(wParam));
			return TRUE;
		}

		break;
	}
	}
	return FALSE;
}

typedef struct TexInfoTag
{
	geVec3d VecNormal;
	geFloat xScale, yScale;
	int xShift, yShift;
	geFloat	Rotate;			// texture rotation angle in degrees
	TexInfo_Vectors TVecs;
	int Dib;				// index into the wad
	char Name[16];
	geBoolean DirtyFlag;
	geVec3d Pos;
	int txSize, tySize;		// texture size (not currently used)
	geXForm3d XfmFaceAngle;	// face rotation angle
} TexInfo;

typedef struct FaceTag
{
	int			NumPoints;
	int			Flags;
	Plane		Face_Plane;
	int			LightIntensity;
	geFloat		Reflectivity;
	geFloat		Translucency;
	geFloat		MipMapBias;
	geFloat		LightXScale, LightYScale;
	TexInfo		Tex;
	geVec3d		*Points;
} Face;

struct tag_FaceList
{
	int NumFaces;
	int Limit;
	Face **Faces;
	geBoolean Dirty;
	Box3d Bounds;
};

// *************************************************************************
// *	  List_SelectedBrushes:- Terry and Hazel Flanigan 2023			   *
// *************************************************************************
void A_TabsGroups_Dlg::List_SelectedBrushes(HWND hDlg)
{
	SendDlgItemMessage(hDlg, IDC_LIST_SELECTEDBRUSHES, LB_RESETCONTENT, (WPARAM)0, (LPARAM)0);

	int NumSelBrushes = SelBrushList_GetSize(App->m_pDoc->pSelBrushes);

	if (NumSelBrushes == 0)
	{
		Selected_Index = -1;
		return;
	}

	for (int i = 0; i < NumSelBrushes; ++i)
	{
		Brush* pBrush = SelBrushList_GetBrush(App->m_pDoc->pSelBrushes, i);
		SendDlgItemMessage(hDlg, IDC_LIST_SELECTEDBRUSHES, LB_ADDSTRING, (WPARAM)0, (LPARAM)pBrush->Name);
	}

	SendDlgItemMessage(hDlg, IDC_LIST_SELECTEDBRUSHES, LB_SETCURSEL, (WPARAM) 0, (LPARAM)0);

	Selected_Index = 0;
	Selected_Brush = SelBrushList_GetBrush(App->m_pDoc->pSelBrushes, 0);
}

// *************************************************************************
// *	  	   List_BrushData:- Terry and Hazel Flanigan 2023			   *
// *************************************************************************
void A_TabsGroups_Dlg::List_BrushData(HWND hDlg)
{
	SendDlgItemMessage(hDlg, IDC_BRUSH_PROPERTIESLIST, LB_RESETCONTENT, (WPARAM)0, (LPARAM)0);
	char buf[255];
	int c = App->CL_World->Get_Brush_Count();

	if( c > 0 )
	{
		if (Selected_Brush && Selected_Index > -1)
		{
			Show_Brush_Info(Selected_Brush, hDlg);
		}
		else
		{
			sprintf(buf, "%s", "No Brush Selected");
			SendDlgItemMessage(hDlg, IDC_BRUSH_PROPERTIESLIST, LB_ADDSTRING, (WPARAM)0, (LPARAM)buf);
		}
	}
	else
	{
		sprintf(buf, "%s", "The World has No Brushes");
		SendDlgItemMessage(hDlg, IDC_BRUSH_PROPERTIESLIST, LB_ADDSTRING, (WPARAM)0, (LPARAM)buf);
	}
}

// *************************************************************************
// *	  	Show_Brush_Info:- Terry and Hazel Flanigan 2023				   *
// *************************************************************************
bool A_TabsGroups_Dlg::Show_Brush_Info(const Brush *b, HWND hDlg)
{
	char buf[255];

	sprintf(buf, "%s%s", "Brush Name ",b->Name);
	SendDlgItemMessage(hDlg, IDC_BRUSH_PROPERTIESLIST, LB_ADDSTRING, (WPARAM)0, (LPARAM)buf);

	sprintf(buf, "%s%i", "Centre_Marker ", b->Centre_Marker);
	SendDlgItemMessage(hDlg, IDC_BRUSH_PROPERTIESLIST, LB_ADDSTRING, (WPARAM)0, (LPARAM)buf);

	if (b->Flags & 128)
	{
		sprintf(buf, "%s%d%s", "Type Flags ", b->Flags, "  - Cut Brush");
		SendDlgItemMessage(hDlg, IDC_BRUSH_PROPERTIESLIST, LB_ADDSTRING, (WPARAM)0, (LPARAM)buf);
	}
	else if (b->Flags & 1)
	{
		sprintf(buf, "%s%d%s", "Type Flags ", b->Flags, "  - Solid Brush");
		SendDlgItemMessage(hDlg, IDC_BRUSH_PROPERTIESLIST, LB_ADDSTRING, (WPARAM)0, (LPARAM)buf);
	}
	else if (b->Flags & 1024)
	{
		sprintf(buf, "%s%d%s", "Type Flags ", b->Flags, "  - Hollow Brush");
		SendDlgItemMessage(hDlg, IDC_BRUSH_PROPERTIESLIST, LB_ADDSTRING, (WPARAM)0, (LPARAM)buf);
	}
	else
	{
		sprintf(buf, "%s%d", "Type Flags ", b->Flags);
		SendDlgItemMessage(hDlg, IDC_BRUSH_PROPERTIESLIST, LB_ADDSTRING, (WPARAM)0, (LPARAM)buf);
	}
	
	sprintf(buf, "%s%d", "Model ID ",b->ModelId);
	SendDlgItemMessage(hDlg, IDC_BRUSH_PROPERTIESLIST, LB_ADDSTRING, (WPARAM)0, (LPARAM)buf);

	sprintf(buf, "%s%d", "Group ID ",b->GroupId);
	SendDlgItemMessage(hDlg, IDC_BRUSH_PROPERTIESLIST, LB_ADDSTRING, (WPARAM)0, (LPARAM)buf);

	sprintf(buf, "%s%f", "Hull Size ",b->HullSize);
	SendDlgItemMessage(hDlg, IDC_BRUSH_PROPERTIESLIST, LB_ADDSTRING, (WPARAM)0, (LPARAM)buf);

	if (b->Type == BRUSH_MULTI)
	{
		sprintf(buf, "%s%i%s", "Type ", b->Type, "  - BRUSH_MULTI");
		SendDlgItemMessage(hDlg, IDC_BRUSH_PROPERTIESLIST, LB_ADDSTRING, (WPARAM)0, (LPARAM)buf);
	}
	else if (b->Type == BRUSH_LEAF)
	{
		sprintf(buf, "%s%i%s", "Type ", b->Type, "  - BRUSH_LEAF");
		SendDlgItemMessage(hDlg, IDC_BRUSH_PROPERTIESLIST, LB_ADDSTRING, (WPARAM)0, (LPARAM)buf);
	}
	else if (b->Type == BRUSH_CSG)
	{
		sprintf(buf, "%s%i%s", "Type ", b->Type, "  - BRUSH_CSG");
		SendDlgItemMessage(hDlg, IDC_BRUSH_PROPERTIESLIST, LB_ADDSTRING, (WPARAM)0, (LPARAM)buf);
	}
	else
	{
		sprintf(buf, "%s%i%s", "Type ", b->Type,"Unknown");
		SendDlgItemMessage(hDlg, IDC_BRUSH_PROPERTIESLIST, LB_ADDSTRING, (WPARAM)0, (LPARAM)buf);
	}



	// Bounding Box
	sprintf(buf, "Max X = %f Y = %f Z = %f",b->BoundingBox.Max.X, b->BoundingBox.Max.Y, b->BoundingBox.Max.Z);
	SendDlgItemMessage(hDlg, IDC_BRUSH_PROPERTIESLIST, LB_ADDSTRING, (WPARAM)0, (LPARAM)buf);

	sprintf(buf, "Min X = %f Y = %f Z = %f", b->BoundingBox.Min.X, b->BoundingBox.Min.Y, b->BoundingBox.Min.Z);
	SendDlgItemMessage(hDlg, IDC_BRUSH_PROPERTIESLIST, LB_ADDSTRING, (WPARAM)0, (LPARAM)buf);

	if (b->Type == BRUSH_MULTI)
	{
		return Show_Brush_ListInfo(b->BList, hDlg);
	}
	if (b->Type == BRUSH_LEAF)
	{
		return Show_Brush_Faces_Info(b->Faces,  hDlg);
	}

	
	return 1;
}

// *************************************************************************
// *	  	Show_Brush_ListInfo:- Terry and Hazel Flanigan 2023			   *
// *************************************************************************
bool A_TabsGroups_Dlg::Show_Brush_ListInfo(BrushList *BList, HWND hDlg)
{
	char buf[MAX_PATH];
	Brush *pBrush;
	BrushIterator bi;
	int Count;

	Count = BrushList_Count (BList, (BRUSH_COUNT_MULTI | BRUSH_COUNT_LEAF | BRUSH_COUNT_NORECURSE));
	if (Count < 0)
	{
		sprintf(buf, "%s%d", "Sub Brushes ", Count);
		SendDlgItemMessage(hDlg, IDC_BRUSH_PROPERTIESLIST, LB_ADDSTRING, (WPARAM)0, (LPARAM)buf);
		return 0;
	}
	else
	{
		sprintf(buf, "%s%d", "Sub Brushes ",Count-1);
		SendDlgItemMessage(hDlg, IDC_BRUSH_PROPERTIESLIST, LB_ADDSTRING, (WPARAM)0, (LPARAM)buf);
	}
	
	pBrush = BrushList_GetFirst (BList, &bi);
	while (pBrush != NULL)
	{
		Show_Brush_Info(pBrush,hDlg);
		pBrush = BrushList_GetNext (&bi);
	}

	return 1;
}

// *************************************************************************
// *	  Show_Brush_Faces_Info:- Terry and Hazel Flanigan 2023			   *
// *************************************************************************
bool A_TabsGroups_Dlg::Show_Brush_Faces_Info(const FaceList *pList, HWND hDlg)
{
	int i;
	char buf[MAX_PATH];

	if (pList->NumFaces < 0)
	{
	}
	else
	{
		sprintf(buf, "%s%d", "BrushFaces ",pList->NumFaces);
		SendDlgItemMessage(hDlg, IDC_BRUSH_PROPERTIESLIST, LB_ADDSTRING, (WPARAM)0, (LPARAM)buf);

		for(i=0;i < pList->NumFaces; i++)
		{
			if (!Show_Face_Data(pList->Faces[i], hDlg)) return 0;
		}
	}

	return 1;
}

// *************************************************************************
// *		  Show_Face_Data:- Terry and Hazel Flanigan 2023			   *
// *************************************************************************
bool A_TabsGroups_Dlg::Show_Face_Data(const Face *f, HWND hDlg)
{
	
	char buf[MAX_PATH];
	int		i, xShift, yShift, Rotate;
	geFloat xScale, yScale, rot;

	sprintf(buf, "%s", " -------------------------------------------");
	SendDlgItemMessage(hDlg, IDC_BRUSH_PROPERTIESLIST, LB_ADDSTRING, (WPARAM)0, (LPARAM)buf);

	sprintf(buf, "%s%i", "Flags ",f->Flags);
	SendDlgItemMessage(hDlg, IDC_BRUSH_PROPERTIESLIST, LB_ADDSTRING, (WPARAM)0, (LPARAM)buf);

	sprintf(buf, "%s%d", "NumPoints",f->NumPoints);
	SendDlgItemMessage(hDlg, IDC_BRUSH_PROPERTIESLIST, LB_ADDSTRING, (WPARAM)0, (LPARAM)buf);

	for(i=0;i < f->NumPoints;i++)
	{
		sprintf(buf, "XYZ %f %f %f",f->Points[i].X,f->Points[i].Y,f->Points[i].Z);
		SendDlgItemMessage(hDlg, IDC_BRUSH_PROPERTIESLIST, LB_ADDSTRING, (WPARAM)0, (LPARAM)buf);
	}
	

	const TexInfo_Vectors* TVecs = Face_GetTextureVecs(f);
	geVec3d uVec, vVec;
	geFloat U, V;

	int txSize, tySize;

	Face_GetTextureSize(f, &txSize, &tySize);

	// make sure that the texture size is set correctly (division!)
	if (txSize == 0)
		txSize = 32;
	if (tySize == 0)
		tySize = 32;

	geVec3d_Scale(&TVecs->uVec, 1.f / (geFloat)txSize, &uVec);
	geVec3d_Scale(&TVecs->vVec, -1.f / (geFloat)tySize, &vVec);

	const geVec3d* verts = Face_GetPoints(f);
	//int curnum_verts = f->NumPoints;

	int j = 0;
	for (j = 0; j < f->NumPoints; j++)
	{
		U = geVec3d_DotProduct(&(verts[j]), &uVec);
		V = geVec3d_DotProduct(&(verts[j]), &vVec);
		U += (TVecs->uOffset / txSize);
		V -= (TVecs->vOffset / tySize);
		//write_float(f, U);
		//write_float(f, V);

		sprintf(buf, "UV %.3f %.3f",U,V);
		SendDlgItemMessage(hDlg, IDC_BRUSH_PROPERTIESLIST, LB_ADDSTRING, (WPARAM)0, (LPARAM)buf);
	}

	char buf2[MAX_PATH];
	strcpy(buf, Face_GetTextureName(f));
	sprintf(buf2, "%s%s", "Texture: = ", buf);
	SendDlgItemMessage(hDlg, IDC_BRUSH_PROPERTIESLIST, LB_ADDSTRING, (WPARAM)0, (LPARAM)buf2);

	return 1;
}

// *************************************************************************
// *		  Update_Dlg_Controls:- Terry and Hazel Flanigan 2023		   *
// *************************************************************************
void A_TabsGroups_Dlg::Update_Dlg_Controls()
{
	App->Get_Current_Document();

	int NumSelBrushes = SelBrushList_GetSize(App->m_pDoc->pSelBrushes);
	if (NumSelBrushes == 0)
	{
		EnableWindow(GetDlgItem(GroupsDlg_Hwnd, IDC_BT_GD_BRUSHPROPERTIES), 0);
		EnableWindow(GetDlgItem(GroupsDlg_Hwnd, IDC_BT_DIMENSIONS), 0);
		EnableWindow(GetDlgItem(GroupsDlg_Hwnd, IDC_BT_DELETEBRUSH), 0);

		SendDlgItemMessage(GroupsDlg_Hwnd, IDC_GD_BRUSHLIST, LB_SETCURSEL, (WPARAM)-1, (LPARAM)0);
	}
	else
	{
		EnableWindow(GetDlgItem(GroupsDlg_Hwnd, IDC_BT_GD_BRUSHPROPERTIES), 1);
		EnableWindow(GetDlgItem(GroupsDlg_Hwnd, IDC_BT_DIMENSIONS), 1);
		EnableWindow(GetDlgItem(GroupsDlg_Hwnd, IDC_BT_DELETEBRUSH), 1);
	}
}

