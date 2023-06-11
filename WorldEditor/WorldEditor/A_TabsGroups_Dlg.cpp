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
	GroupsDlg_Hwnd = CreateDialog(App->hInst, (LPCTSTR)IDD_SB_TABSGROUPS, App->CL_TabsControl->Tabs_Control_Hwnd, (DLGPROC)Groups_Proc);

	Groups_Dlg_Created = 1;

	Fill_ListBox();
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

		return FALSE;
	}

	case WM_CTLCOLORDLG:
	{
		return (LONG)App->AppBackground;
	}

	case WM_DRAWITEM:
		{
			LPDRAWITEMSTRUCT lpDIS = (LPDRAWITEMSTRUCT)lParam;

			if (lpDIS->CtlID == IDC_BT_GD_BRUSHPROPERTIES)
			{
				App->Custom_Button_Normal_MFC(lpDIS,hDlg);
				return TRUE;
			}

			return TRUE;
		}

	case WM_COMMAND:
		{
			if (LOWORD(wParam) == IDC_GD_BRUSHLIST)
			{
				if (App->CL_TabsGroups_Dlg->Groups_Dlg_Created == 1)
				{
					App->CL_TabsGroups_Dlg->List_Selection_Changed();
				}
				return TRUE;
			}

			if (LOWORD(wParam) == IDC_BT_GD_BRUSHPROPERTIES)
			{
				App->CL_TabsGroups_Dlg->Start_Properties_Dlg();
				SendDlgItemMessage(hDlg, IDC_GD_BRUSHLIST,LB_SETCURSEL, (WPARAM)App->CL_TabsGroups_Dlg->Selected_Index, (LPARAM)0);
				return TRUE;
			}

			if (LOWORD(wParam) == IDC_BTTEST)
			{
				//Brush_Scale(App->CL_TabsGroups_Dlg->Selected_Brush,10);
				//Debug
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



struct tag_BrushList
{
	Brush *First;
	Brush *Last;
};

// *************************************************************************
// *	  	List_Selection_Changed:- Terry and Hazel Flanigan 2023		   *
// *************************************************************************
void A_TabsGroups_Dlg::List_Selection_Changed()
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
			OnSelchangeBrushlist(Index);
		}
	}
}

// *************************************************************************
// *	  		Get_Index:- Terry and Hazel Flanigan 2023				   *
// *************************************************************************
void A_TabsGroups_Dlg::Get_Index(const Brush *b)
{
	m_pDoc = (CFusionDoc*)App->m_pMainFrame->GetCurrentDoc();

	Level *pLevel = m_pDoc->pLevel;
	BrushList *pList = Level_GetBrushes (m_pDoc->pLevel);

	char buff[100];
	int Selected = 0;
	int Count = 0;
	b = pList->First;
	while (b != NULL)
	{
		Selected = m_pDoc->BrushIsSelected(b);

		if (Selected == 1)
		{
			SendDlgItemMessage(GroupsDlg_Hwnd, IDC_GD_BRUSHLIST,LB_SETCURSEL, (WPARAM)Count, (LPARAM)0);
			Selected_Index = Count;
			List_Selection_Changed();
		}

		Count++;
		b = b->Next;
	}


}

// *************************************************************************
// *		OnSelchangeBrushlist:- Terry and Hazel Flanigan 2023		   *
// *************************************************************************
void A_TabsGroups_Dlg::OnSelchangeBrushlist(int Index) 
{
	m_pDoc = (CFusionDoc*)App->m_pMainFrame->GetCurrentDoc();

	int			c ;
	geBoolean	bChanged = FALSE ;

	c = App->CL_World->Get_Brush_Count();

	if( c > 0 )
	{
		m_pDoc->ResetAllSelections() ;
		m_pDoc->UpdateSelected();
		
		Selected_Brush = App->CL_World->Get_Brush_ByIndex( Index );
		m_pDoc->DoBrushSelection( Selected_Brush, brushSelToggle) ;
		bChanged = GE_TRUE;
	}


	if( bChanged )
	{
		m_pDoc->UpdateSelected() ;
		m_pDoc->UpdateAllViews(UAV_ALL3DVIEWS, NULL);
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

		m_pDoc = (CFusionDoc*)App->m_pMainFrame->GetCurrentDoc();

		Level *pLevel = m_pDoc->pLevel;
		BrushList *pList = Level_GetBrushes (m_pDoc->pLevel);

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

		App->CL_TabsGroups_Dlg->List_BrushData(hDlg);
		return TRUE;
	}
	case WM_CTLCOLORSTATIC:
	{
		return FALSE;
	}

	case WM_CTLCOLORDLG:
	{
		return (LONG)App->AppBackground;
	}

	case WM_COMMAND:
		{
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
// *	  				List_BrushData Terry Flanigan					   *
// *************************************************************************
void A_TabsGroups_Dlg::List_BrushData(HWND hDlg)
{
	
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

	sprintf(buf, "%s%d", "Flags ",b->Flags);
	SendDlgItemMessage(hDlg, IDC_BRUSH_PROPERTIESLIST, LB_ADDSTRING, (WPARAM)0, (LPARAM)buf);

	sprintf(buf, "%s%d", "Model ID ",b->ModelId);
	SendDlgItemMessage(hDlg, IDC_BRUSH_PROPERTIESLIST, LB_ADDSTRING, (WPARAM)0, (LPARAM)buf);

	sprintf(buf, "%s%d", "Group ID ",b->GroupId);
	SendDlgItemMessage(hDlg, IDC_BRUSH_PROPERTIESLIST, LB_ADDSTRING, (WPARAM)0, (LPARAM)buf);

	sprintf(buf, "%s%f", "Hull Size ",b->HullSize);
	SendDlgItemMessage(hDlg, IDC_BRUSH_PROPERTIESLIST, LB_ADDSTRING, (WPARAM)0, (LPARAM)buf);

	sprintf(buf, "%s%d", "Type ",b->Type);
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
// *	  	Show_BrushList:- Terry and Hazel Flanigan 2023				   *
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
		return 0;
	}
	else
	{
		sprintf(buf, "%s%d", "Type ",Count);
		SendDlgItemMessage(hDlg, IDC_BRUSH_PROPERTIESLIST, LB_ADDSTRING, (WPARAM)0, (LPARAM)buf);
	}
	
	pBrush = BrushList_GetFirst (BList, &bi);
	while (pBrush != NULL)
	{
		//if (!Brush_ExportTo3dtv1_32(pBrush, ofile)) return GE_FALSE;

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

	sprintf(buf, "%s%d", "NumPoints",f->NumPoints);
	SendDlgItemMessage(hDlg, IDC_BRUSH_PROPERTIESLIST, LB_ADDSTRING, (WPARAM)0, (LPARAM)buf);

	/*if (fprintf(wf, "\t\tNumPoints %d\n", f->NumPoints) < 0) return GE_FALSE;
	if (fprintf(wf, "\t\tFlags %d\n", f->Flags) < 0) return GE_FALSE;
	if (fprintf(wf, "\t\tLight %d\n", f->LightIntensity) < 0) return GE_FALSE;
	if (fprintf(wf, "\t\tMipMapBias %f\n", f->MipMapBias) < 0) return GE_FALSE;
	if (fprintf(wf, "\t\tTranslucency %f\n", f->Translucency) < 0) return GE_FALSE;
	if (fprintf(wf, "\t\tReflectivity %f\n", f->Reflectivity) < 0) return GE_FALSE;*/

	for(i=0;i < f->NumPoints;i++)
	{
		//if (fprintf(wf, "\t\t\tVec3d %f %f %f\n", f->Points[i].X, f->Points[i].Y, f->Points[i].Z) < 0) return GE_FALSE;

		sprintf(buf, "Vec3d %f %f %f",f->Points[i].X,f->Points[i].Y,f->Points[i].Z);
		SendDlgItemMessage(hDlg, IDC_BRUSH_PROPERTIESLIST, LB_ADDSTRING, (WPARAM)0, (LPARAM)buf);
	}

	//Face_GetTextureShift (f, &xShift, &yShift);
	//Face_GetTextureScale (f, &xScale, &yScale);
	//rot		=Face_GetTextureRotate (f);
	//Rotate	=Units_Round(rot);

	//{
	//	char QuotedValue[SCANNER_MAXDATA];

	//	// Quote the texture name
	//	Util_QuoteString (Face_GetTextureName (f), QuotedValue);
	//	if (fprintf(wf, "\t\t\tTexInfo Rotate %d Shift %d %d Scale %f %f Name %s\n",
	//		Rotate, xShift, yShift, xScale, yScale, QuotedValue) < 0) return GE_FALSE;
	//}

	//if (fprintf(wf, "\t\tLightScale %f %f\n", f->LightXScale, f->LightYScale) < 0) return GE_FALSE;

	//if (fprintf (wf, "%s", "\tTransform\t") < 0) return GE_FALSE;
	//if (!TypeIO_WriteXForm3dText (wf, &(f->Tex.XfmFaceAngle))) return GE_FALSE;

	//if (fprintf (wf, "%s", "\tPos\t") < 0) return GE_FALSE;
	//if( !TypeIO_WriteVec3dText(wf, &f->Tex.Pos )) return GE_FALSE;

	return 1;
}