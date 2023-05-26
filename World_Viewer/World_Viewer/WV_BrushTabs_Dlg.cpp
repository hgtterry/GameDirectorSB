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
#include "WV_App.h"
#include "resource.h"
#include "WV_BrushTabs_Dlg.h"

struct tag_BrushList
{
	Brush* First;
	Brush* Last;
};

WV_BrushTabs_Dlg::WV_BrushTabs_Dlg()
{
	BrushTabs_Dlg_Hwnd = nullptr;
	BrushTab_Created = 0;

	Selected_Index = -1;
	Selected_Brush = NULL;
}

WV_BrushTabs_Dlg::~WV_BrushTabs_Dlg()
{
}

// *************************************************************************
// *			Start_BrushTab_Dlg:- Terry and Hazel Flanigan 2023	  	   *
// *************************************************************************
bool WV_BrushTabs_Dlg::Start_BrushTab_Dlg()
{
	if (BrushTab_Created == 1)
	{
		return 1;
	}

	BrushTabs_Dlg_Hwnd = CreateDialog(App->hInst, (LPCTSTR)IDD_BRUSHPROPERTIES, App->MainHwnd, (DLGPROC)BrushTab_Dlg_Proc);

	BrushTab_Created = 1;

	Fill_ListBox();

	return 1;
}

// *************************************************************************
// *			BrushTab_Dlg_Proc:- Terry and Hazel Flanigan 2023	 	   *
// *************************************************************************
LRESULT CALLBACK WV_BrushTabs_Dlg::BrushTab_Dlg_Proc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_INITDIALOG:
	{
		SendDlgItemMessage(hDlg, IDC_GD_BRUSHLIST, WM_SETFONT, (WPARAM)App->Font_CB15, MAKELPARAM(TRUE, 0));
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

	case WM_CLOSE:
	{
		break;
	}


	case WM_NOTIFY:
	{


		return CDRF_DODEFAULT;
	}

	case WM_COMMAND:
	{
		
		if (LOWORD(wParam) == IDC_BTTEST)
		{

			App->CL_Export_World->Export_World_GD3D(1);

			return TRUE;
		}

		if (LOWORD(wParam) == IDC_GD_BRUSHLIST)
		{

			if (App->CL_BrushTabs_Dlg->BrushTab_Created == 1)
			{
				App->CL_BrushTabs_Dlg->List_Selection_Changed();
			}

			return TRUE;
		}

		if (LOWORD(wParam) == IDC_BT_GD_BRUSHPROPERTIES)
		{
			App->CL_BrushTabs_Dlg->Start_Properties_Dlg();
		 
			SendDlgItemMessage(hDlg, IDC_GD_BRUSHLIST, LB_SETCURSEL, (WPARAM)App->CL_BrushTabs_Dlg->Selected_Index, (LPARAM)0);
			return TRUE;
		}

		if (LOWORD(wParam) == IDCANCEL)
		{
			App->CL_BrushTabs_Dlg->BrushTab_Created = 0;
			EndDialog(hDlg, LOWORD(wParam));
			return TRUE;
		}

		if (LOWORD(wParam) == IDOK)
		{
			App->CL_BrushTabs_Dlg->BrushTab_Created = 0;
			EndDialog(hDlg, LOWORD(wParam));
			return TRUE;
		}
	}

	}
	return FALSE;
}

// *************************************************************************
// *	  	List_Selection_Changed:- Terry and Hazel Flanigan 2023		   *
// *************************************************************************
void WV_BrushTabs_Dlg::List_Selection_Changed()
{
	int Index = SendDlgItemMessage(BrushTabs_Dlg_Hwnd, IDC_GD_BRUSHLIST, LB_GETCURSEL, (WPARAM)0, (LPARAM)0);
	if (Index == -1)
	{
		//App->Say("ListBox No Selection Available");
	}
	else
	{
		if (BrushTab_Created == 1)
		{
			Selected_Index = Index;
			OnSelchangeBrushlist(Index);
		}
	}
}

// *************************************************************************
// *		OnSelchangeBrushlist:- Terry and Hazel Flanigan 2023		   *
// *************************************************************************
void WV_BrushTabs_Dlg::OnSelchangeBrushlist(int Index)
{
	
	int	c = 0;

	c = App->CL_Brushes->Get_Brush_Count();

	if (c > 0)
	{
		Selected_Brush = App->CL_Brushes->Get_Brush_ByIndex(Index);
	}

}

// *************************************************************************
// *	  	Start_Properties_Dlg:- Terry and Hazel Flanigan 2023		   *
// *************************************************************************
void WV_BrushTabs_Dlg::Start_Properties_Dlg()
{
	DialogBox(App->hInst, (LPCTSTR)IDD_SB_BRUSH_PROPERTIES, App->MainHwnd, (DLGPROC)Properties_Proc);
}

// *************************************************************************
// *			Properties_Proc:- Terry and Hazel Flanigan 2023			   *
// *************************************************************************
LRESULT CALLBACK WV_BrushTabs_Dlg::Properties_Proc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{

	switch (message)
	{
	case WM_INITDIALOG:
	{
		SendDlgItemMessage(hDlg, IDC_BRUSH_PROPERTIESLIST, WM_SETFONT, (WPARAM)App->Font_CB18, MAKELPARAM(TRUE, 0));

		App->CL_BrushTabs_Dlg->List_BrushData(hDlg);

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
			EndDialog(hDlg, LOWORD(wParam));
			return TRUE;
		}

		if (LOWORD(wParam) == IDCANCEL)
		{
			EndDialog(hDlg, LOWORD(wParam));
			return TRUE;
		}

		break;
	}
	}
	return FALSE;
}

// *************************************************************************
// *			 Fill_ListBox:- Terry and Hazel Flanigan 2023			   *
// *************************************************************************
void WV_BrushTabs_Dlg::Fill_ListBox()
{
	if (BrushTab_Created == 1)
	{
		SendDlgItemMessage(BrushTabs_Dlg_Hwnd, IDC_GD_BRUSHLIST, LB_RESETCONTENT, (WPARAM)0, (LPARAM)0);

		BrushList* pList = App->CL_CFusionDoc->pLevel->Brushes;

		int Count = 0;
		Brush* b;
		b = pList->First;

		while (b != NULL)
		{
			SendDlgItemMessage(BrushTabs_Dlg_Hwnd, IDC_GD_BRUSHLIST, LB_ADDSTRING, (WPARAM)0, (LPARAM)b->Name);
			Count++;
			b = b->Next;
		}

		//char buff[100];
		//SetDlgItemText(BrushTabs_Dlg_Hwnd, IDC_BRUSHCOUNT, itoa(Count, buff, 10));
	}
}


// *************************************************************************
// *	  				List_BrushData Terry Flanigan					   *
// *************************************************************************
void WV_BrushTabs_Dlg::List_BrushData(HWND hDlg)
{

	char buf[255];
	int c = App->CL_Brushes->Get_Brush_Count();

	if (c > 0)
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
bool WV_BrushTabs_Dlg::Show_Brush_Info(const Brush* b, HWND hDlg)
{
	char buf[255];

	sprintf(buf, "%s%s", "Brush Name ", b->Name);
	SendDlgItemMessage(hDlg, IDC_BRUSH_PROPERTIESLIST, LB_ADDSTRING, (WPARAM)0, (LPARAM)buf);

	sprintf(buf, "%s%d", "Flags ", b->Flags);
	SendDlgItemMessage(hDlg, IDC_BRUSH_PROPERTIESLIST, LB_ADDSTRING, (WPARAM)0, (LPARAM)buf);

	sprintf(buf, "%s%d", "Model ID ", b->ModelId);
	SendDlgItemMessage(hDlg, IDC_BRUSH_PROPERTIESLIST, LB_ADDSTRING, (WPARAM)0, (LPARAM)buf);

	sprintf(buf, "%s%d", "Group ID ", b->GroupId);
	SendDlgItemMessage(hDlg, IDC_BRUSH_PROPERTIESLIST, LB_ADDSTRING, (WPARAM)0, (LPARAM)buf);

	sprintf(buf, "%s%f", "Hull Size ", b->HullSize);
	SendDlgItemMessage(hDlg, IDC_BRUSH_PROPERTIESLIST, LB_ADDSTRING, (WPARAM)0, (LPARAM)buf);

	sprintf(buf, "%s%d", "Type ", b->Type);
	SendDlgItemMessage(hDlg, IDC_BRUSH_PROPERTIESLIST, LB_ADDSTRING, (WPARAM)0, (LPARAM)buf);

	if (b->Type == BRUSH_MULTI)
	{
		return Show_Brush_ListInfo(b->BList, hDlg);
	}
	if (b->Type == BRUSH_LEAF)
	{
		return Show_Brush_Faces_Info(b->Faces, hDlg);
	}

	return 1;
}

// *************************************************************************
// *	  	Show_Brush_ListInfo:- Terry and Hazel Flanigan 2023			   *
// *************************************************************************
bool WV_BrushTabs_Dlg::Show_Brush_ListInfo(BrushList* BList, HWND hDlg)
{
	char buf[MAX_PATH];
	Brush* pBrush;
	BrushIterator bi;
	int Count;

	Count = BrushList_Count(BList, (BRUSH_COUNT_MULTI | BRUSH_COUNT_LEAF | BRUSH_COUNT_NORECURSE));
	if (Count < 0)
	{
		return 0;
	}
	else
	{
		sprintf(buf, "%s%d", "Type ", Count);
		SendDlgItemMessage(hDlg, IDC_BRUSH_PROPERTIESLIST, LB_ADDSTRING, (WPARAM)0, (LPARAM)buf);
	}

	pBrush = BrushList_GetFirst(BList, &bi);
	while (pBrush != NULL)
	{
		Show_Brush_Info(pBrush, hDlg);
		pBrush = BrushList_GetNext(&bi);
	}

	return 1;
}

// *************************************************************************
// *	  Show_Brush_Faces_Info:- Terry and Hazel Flanigan 2023			   *
// *************************************************************************
bool WV_BrushTabs_Dlg::Show_Brush_Faces_Info(const FaceList* pList, HWND hDlg)
{
	int i;
	char buf[MAX_PATH];

	if (pList->NumFaces < 0)
	{
	}
	else
	{
		sprintf(buf, "%s%d", "BrushFaces ", pList->NumFaces);
		SendDlgItemMessage(hDlg, IDC_BRUSH_PROPERTIESLIST, LB_ADDSTRING, (WPARAM)0, (LPARAM)buf);
		for (i = 0; i < pList->NumFaces; i++)
		{
			if (!Show_Face_Data(pList->Faces[i], hDlg)) return 0;
		}
	}

	return 1;
}

// *************************************************************************
// *		  Show_Face_Data:- Terry and Hazel Flanigan 2023			   *
// *************************************************************************
bool WV_BrushTabs_Dlg::Show_Face_Data(const Face* f, HWND hDlg)
{
	char buf[MAX_PATH];
	int		i;// xShift, yShift, Rotate;
	//geFloat xScale, yScale, rot;

	sprintf(buf, "%s%d", "NumPoints", f->NumPoints);
	SendDlgItemMessage(hDlg, IDC_BRUSH_PROPERTIESLIST, LB_ADDSTRING, (WPARAM)0, (LPARAM)buf);

	/*if (fprintf(wf, "\t\tNumPoints %d\n", f->NumPoints) < 0) return GE_FALSE;
	if (fprintf(wf, "\t\tFlags %d\n", f->Flags) < 0) return GE_FALSE;
	if (fprintf(wf, "\t\tLight %d\n", f->LightIntensity) < 0) return GE_FALSE;
	if (fprintf(wf, "\t\tMipMapBias %f\n", f->MipMapBias) < 0) return GE_FALSE;
	if (fprintf(wf, "\t\tTranslucency %f\n", f->Translucency) < 0) return GE_FALSE;
	if (fprintf(wf, "\t\tReflectivity %f\n", f->Reflectivity) < 0) return GE_FALSE;*/

	for (i = 0; i < f->NumPoints; i++)
	{
		//if (fprintf(wf, "\t\t\tVec3d %f %f %f\n", f->Points[i].X, f->Points[i].Y, f->Points[i].Z) < 0) return GE_FALSE;

		sprintf(buf, "Vec3d %f %f %f", f->Points[i].X, f->Points[i].Y, f->Points[i].Z);
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
