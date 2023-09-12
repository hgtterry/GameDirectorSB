#include "stdafx.h"
#include "AB_App.h"
#include "resource.h"
#include "A_FaceDialog.h"

#include "FUSIONView.h"
#include "FUSIONDoc.h"

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
	geVec3d* Points;
} Face;

static CString TEXT_NUM_FACES = "Number of Faces Selected: ";

A_FaceDialog::A_FaceDialog(void)
{
	m_TextureAngle = 0;

	m_TextureXScale = 0;
	m_TextureYScale = 0;

	m_TextureYOffset = 0;
	m_TextureXOffset = 0;

	f_FaceDlg_Active = 0;

	ScaleX_Delta = 0.01;
	ScaleY_Delta = 0.01;

	FaceDlg_Hwnd = NULL;
}

A_FaceDialog::~A_FaceDialog(void)
{
}

// *************************************************************************
// *	  	Start_FaceDialog:- Terry and Hazel Flanigan 2023			   *
// *************************************************************************
void A_FaceDialog::Start_FaceDialog()
{
	if (f_FaceDlg_Active == 0)
	{
		/*if (App->CLSB_Equity->EquitySB_Dialog_Visible == 1)
		{
			FaceDlg_Hwnd = CreateDialog(App->hInst, (LPCTSTR)IDD_SB_FACE_PROPERTIES, App->CLSB_Equity->Equity_Main_hWnd, (DLGPROC)FaceDialog_Proc);
			f_FaceDlg_Active = 1;
		}
		else*/
		{
			FaceDlg_Hwnd = CreateDialog(App->hInst, (LPCTSTR)IDD_SB_FACE_PROPERTIES, App->MainHwnd, (DLGPROC)FaceDialog_Proc);
			f_FaceDlg_Active = 1;
		}
	}
}

// *************************************************************************
// *		  FaceDialog_Proc:- Terry and Hazel Flanigan 2023			   *
// *************************************************************************
LRESULT CALLBACK A_FaceDialog::FaceDialog_Proc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{

	switch (message)
	{
	case WM_INITDIALOG:
	{
		SendDlgItemMessage(hDlg, IDC_LABEL_NUM_FACES, WM_SETFONT, (WPARAM)App->Font_CB15, MAKELPARAM(TRUE, 0));
		SendDlgItemMessage(hDlg, IDC_STTEXT2, WM_SETFONT, (WPARAM)App->Font_CB15, MAKELPARAM(TRUE, 0));
		SendDlgItemMessage(hDlg, IDC_STTEXT, WM_SETFONT, (WPARAM)App->Font_CB15, MAKELPARAM(TRUE, 0));
		SendDlgItemMessage(hDlg, IDOK, WM_SETFONT, (WPARAM)App->Font_CB15, MAKELPARAM(TRUE, 0));

		SendDlgItemMessage(hDlg, IDC_LISTFACEPROPERTIES, WM_SETFONT, (WPARAM)App->Font_CB15, MAKELPARAM(TRUE, 0));
		
		App->CL_FaceDialog->UpdatePolygonFocus();

		App->CL_FaceDialog->UpdateDialog(hDlg);

		App->CL_FaceDialog->Update_FaceProperties_Dlg(hDlg);

		HWND CB_hWnd = GetDlgItem(hDlg, IDC_CBXOFFSET);
		App->CL_FaceDialog->Fill_ComboBox_OffSetValues(CB_hWnd);

		CB_hWnd = GetDlgItem(hDlg, IDC_CBYOFFSET);
		App->CL_FaceDialog->Fill_ComboBox_OffSetValues(CB_hWnd);

		CB_hWnd = GetDlgItem(hDlg, IDC_CBXSCALE);
		App->CL_FaceDialog->Fill_ComboBox_ScaleValues(CB_hWnd);

		CB_hWnd = GetDlgItem(hDlg, IDC_CBYSCALE);
		App->CL_FaceDialog->Fill_ComboBox_ScaleValues(CB_hWnd);

		CB_hWnd = GetDlgItem(hDlg, IDC_CBANGLE);
		App->CL_FaceDialog->Fill_ComboBox_AngleValues(CB_hWnd);

		return TRUE;
	}
	case WM_CTLCOLORSTATIC:
	{
		if (GetDlgItem(hDlg, IDC_STTEXT2) == (HWND)lParam)
		{
			SetBkColor((HDC)wParam, RGB(0, 0, 0));
			SetTextColor((HDC)wParam, RGB(0, 0, 0));
			SetBkMode((HDC)wParam, TRANSPARENT);
			return (UINT)App->AppBackground;
		}

		if (GetDlgItem(hDlg, IDC_STTEXT) == (HWND)lParam)
		{
			SetBkColor((HDC)wParam, RGB(0, 0, 0));
			SetTextColor((HDC)wParam, RGB(0, 0, 0));
			SetBkMode((HDC)wParam, TRANSPARENT);
			return (UINT)App->AppBackground;
		}

		if (GetDlgItem(hDlg, IDC_LABEL_NUM_FACES) == (HWND)lParam)
		{
			SetBkColor((HDC)wParam, RGB(0, 0, 0));
			SetTextColor((HDC)wParam, RGB(0, 0, 0));
			SetBkMode((HDC)wParam, TRANSPARENT);
			return (UINT)App->AppBackground;
		}

		if (GetDlgItem(hDlg, IDC_LABEL_TEXTURE_OFFSET_SCALEX) == (HWND)lParam)
		{
			SetBkColor((HDC)wParam, RGB(0, 0, 0));
			SetTextColor((HDC)wParam, RGB(0, 0, 0));
			SetBkMode((HDC)wParam, TRANSPARENT);
			return (UINT)App->AppBackground;
		}

		if (GetDlgItem(hDlg, IDC_LABEL_TEXTURE_OFFSET_SCALEY) == (HWND)lParam)
		{
			SetBkColor((HDC)wParam, RGB(0, 0, 0));
			SetTextColor((HDC)wParam, RGB(0, 0, 0));
			SetBkMode((HDC)wParam, TRANSPARENT);
			return (UINT)App->AppBackground;
		}

		if (GetDlgItem(hDlg, IDC_LABEL_TEXTURE_OFFSET_SCALEANGLE) == (HWND)lParam)
		{
			SetBkColor((HDC)wParam, RGB(0, 0, 0));
			SetTextColor((HDC)wParam, RGB(0, 0, 0));
			SetBkMode((HDC)wParam, TRANSPARENT);
			return (UINT)App->AppBackground;
		}

		if (GetDlgItem(hDlg, IDC_TEXTURELOCK) == (HWND)lParam)
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

		if (some_item->idFrom == IDC_FLIPHORIZONTAL && some_item->code == NM_CUSTOMDRAW)
		{
			LPNMCUSTOMDRAW item = (LPNMCUSTOMDRAW)some_item;
			App->Custom_Button_Normal(item);
			return CDRF_DODEFAULT;
		}

		if (some_item->idFrom == IDC_FLIPVERTICAL && some_item->code == NM_CUSTOMDRAW)
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

		return CDRF_DODEFAULT;
	}

	case WM_VSCROLL:
		{
			// -------- Angle
			if(HWND(lParam) == GetDlgItem(hDlg, IDC_SBANGLE_UNIT))
			{
				switch ((int)LOWORD(wParam))
				{
				case SB_LINEUP:

					App->CL_FaceDialog->m_TextureAngle++;
					App->CL_FaceDialog->UpdateDialog(hDlg);
					App->CL_FaceDialog->OnKillfocusAngle();

					break;

				case SB_LINEDOWN:
					App->CL_FaceDialog->m_TextureAngle--;
					App->CL_FaceDialog->UpdateDialog(hDlg);
					App->CL_FaceDialog->OnKillfocusAngle();

					break;
				}
				
				return 0;
			}

			// -------- Offset X
			if(HWND(lParam) == GetDlgItem(hDlg, IDC_SBXOFFSET_UNIT))
			{
				switch ((int)LOWORD(wParam))
				{
				case SB_LINEUP:

					App->CL_FaceDialog->m_TextureXOffset++;
					App->CL_FaceDialog->UpdateDialog(hDlg);
					App->CL_FaceDialog->OnKillfocusXOffset() ;

					break;

				case SB_LINEDOWN:
					App->CL_FaceDialog->m_TextureXOffset--;
					App->CL_FaceDialog->UpdateDialog(hDlg);
					App->CL_FaceDialog->OnKillfocusXOffset() ;

					break;
				}
				
				return 0;
			}

			// -------- Offset Y
			if(HWND(lParam) == GetDlgItem(hDlg, IDC_SBYOFFSET_UNIT))
			{
				switch ((int)LOWORD(wParam))
				{
				case SB_LINEUP:

					App->CL_FaceDialog->m_TextureYOffset++;
					App->CL_FaceDialog->UpdateDialog(hDlg);
					App->CL_FaceDialog->OnKillfocusYOffset() ;

					break;

				case SB_LINEDOWN:
					App->CL_FaceDialog->m_TextureYOffset--;
					App->CL_FaceDialog->UpdateDialog(hDlg);
					App->CL_FaceDialog->OnKillfocusYOffset() ;

					break;
				}
				
				return 0;
			}

			// -------- Scale Y
			if(HWND(lParam) == GetDlgItem(hDlg, IDC_SBYSCALE_UNIT))
			{
				switch ((int)LOWORD(wParam))
				{
				case SB_LINEUP:

					App->CL_FaceDialog->m_TextureYScale = App->CL_FaceDialog->m_TextureYScale + App->CL_FaceDialog->ScaleY_Delta;
					App->CL_FaceDialog->UpdateDialog(hDlg);
					App->CL_FaceDialog->OnKillfocusYScale() ;

					break;

				case SB_LINEDOWN:
					App->CL_FaceDialog->m_TextureYScale = App->CL_FaceDialog->m_TextureYScale - App->CL_FaceDialog->ScaleY_Delta;
					App->CL_FaceDialog->UpdateDialog(hDlg);
					App->CL_FaceDialog->OnKillfocusYScale() ;

					break;
				}
				
				return 0;
			}

			// -------- Scale X
			if(HWND(lParam) == GetDlgItem(hDlg, IDC_SBXSCALE_UNIT))
			{
				switch ((int)LOWORD(wParam))
				{
				case SB_LINEUP:

					App->CL_FaceDialog->m_TextureXScale = App->CL_FaceDialog->m_TextureXScale + App->CL_FaceDialog->ScaleX_Delta;
					App->CL_FaceDialog->UpdateDialog(hDlg);
					App->CL_FaceDialog->OnKillfocusXScale() ;

					break;

				case SB_LINEDOWN:
					App->CL_FaceDialog->m_TextureXScale = App->CL_FaceDialog->m_TextureXScale - App->CL_FaceDialog->ScaleX_Delta;
					App->CL_FaceDialog->UpdateDialog(hDlg);
					App->CL_FaceDialog->OnKillfocusXScale() ;

					break;
				}
				
				return 0;
			}

			return 0;
		}

	case WM_COMMAND:
		{

		if (LOWORD(wParam) == IDC_TEXTURELOCK)
		{
			HWND temp = GetDlgItem(hDlg, IDC_TEXTURELOCK);

			App->Get_Current_Document();

			Face* pFace;
			int NumberOfFaces;

			int test = SendMessage(temp, BM_GETCHECK, 0, 0);
			if (test == BST_CHECKED)
			{
				NumberOfFaces = SelFaceList_GetSize(App->m_pDoc->pSelFaces);

				for (int i = 0; i < NumberOfFaces; ++i)
				{
					pFace = SelFaceList_GetFace(App->m_pDoc->pSelFaces,i);
					Face_SetTextureLock(pFace,true);
				}

				App->CLSB_Doc->UpdateAllViews(UAV_RENDER_ONLY, NULL);
				
				return 1;
			}
			else
			{
				NumberOfFaces = SelFaceList_GetSize(App->m_pDoc->pSelFaces);

				for (int i = 0; i < NumberOfFaces; ++i)
				{
					pFace = SelFaceList_GetFace(App->m_pDoc->pSelFaces, i);
					Face_SetTextureLock(pFace, false);
				}

				App->CLSB_Doc->UpdateAllViews(UAV_RENDER_ONLY, NULL);
				return 1;
			}
			return TRUE;
		}

		if (LOWORD(wParam) == IDC_CBXSCALE)
		{
			switch (HIWORD(wParam)) // Find out what message it was
			{
			case CBN_DROPDOWN:
				break;
			case CBN_CLOSEUP:
			{
				char buff[MAX_PATH]{ 0 };

				HWND temp = GetDlgItem(hDlg, IDC_CBXSCALE);
				int Index = SendMessage(temp, CB_GETCURSEL, 0, 0);
				SendMessage(temp, CB_GETLBTEXT, Index, (LPARAM)buff);
				
				App->CL_FaceDialog->ScaleX_Delta = atof(buff);
			}
			}

			return TRUE;
		}

		if (LOWORD(wParam) == IDC_CBYSCALE)
		{
			switch (HIWORD(wParam)) // Find out what message it was
			{
			case CBN_DROPDOWN:
				break;
			case CBN_CLOSEUP:
			{
				char buff[MAX_PATH]{ 0 };

				HWND temp = GetDlgItem(hDlg, IDC_CBYSCALE);
				int Index = SendMessage(temp, CB_GETCURSEL, 0, 0);
				SendMessage(temp, CB_GETLBTEXT, Index, (LPARAM)buff);

				App->CL_FaceDialog->ScaleY_Delta = atof(buff);
			}
			}

			return TRUE;
		}

		if (LOWORD(wParam) == IDC_FLIPHORIZONTAL)
		{
			App->CL_FaceDialog->On_FlipHorizontal();
			App->CL_FaceDialog->Update_FaceProperties_Dlg(hDlg);
			return TRUE;
		}

		if (LOWORD(wParam) == IDC_FLIPVERTICAL)
		{
			App->CL_FaceDialog->OnFlipvertical();
			App->CL_FaceDialog->Update_FaceProperties_Dlg(hDlg);
			return TRUE;
		}

		// -----------------------------------------------------------------
		if (LOWORD(wParam) == IDOK)
		{
			App->CL_FaceDialog->f_FaceDlg_Active = 0;
			EndDialog(hDlg, LOWORD(wParam));
			return TRUE;
		}

		if (LOWORD(wParam) == IDCANCEL)
		{
			App->CL_FaceDialog->f_FaceDlg_Active = 0;
			EndDialog(hDlg, LOWORD(wParam));
			return TRUE;
		}

		break;
	}
	}
	return FALSE;
}

// *************************************************************************
// *				Fill_ComboBox_OffSetValues Terry Flanigan	  		   *
// *************************************************************************
void A_FaceDialog::Fill_ComboBox_OffSetValues(HWND hDlg)
{
	SendMessage(hDlg, CB_ADDSTRING, 0, (LPARAM)(LPCTSTR)"4");
	SendMessage(hDlg, CB_ADDSTRING, 0, (LPARAM)(LPCTSTR)"8");
	SendMessage(hDlg, CB_ADDSTRING, 0, (LPARAM)(LPCTSTR)"16");
	SendMessage(hDlg, CB_ADDSTRING, 0, (LPARAM)(LPCTSTR)"32");
	SendMessage(hDlg, CB_ADDSTRING, 0, (LPARAM)(LPCTSTR)"64");
	SendMessage(hDlg, CB_ADDSTRING, 0, (LPARAM)(LPCTSTR)"128");

	SendMessage(hDlg, CB_SETCURSEL, 2, 0);
}

// *************************************************************************
// *				Fill_ComboBox_ScaleValues Terry Flanigan	  		   *
// *************************************************************************
void A_FaceDialog::Fill_ComboBox_ScaleValues(HWND hDlg)
{
	SendMessage(hDlg, CB_ADDSTRING, 0, (LPARAM)(LPCTSTR)"0.001");
	SendMessage(hDlg, CB_ADDSTRING, 0, (LPARAM)(LPCTSTR)"0.01");
	SendMessage(hDlg, CB_ADDSTRING, 0, (LPARAM)(LPCTSTR)"0.02");
	SendMessage(hDlg, CB_ADDSTRING, 0, (LPARAM)(LPCTSTR)"0.05");
	SendMessage(hDlg, CB_ADDSTRING, 0, (LPARAM)(LPCTSTR)"0.10");
	SendMessage(hDlg, CB_ADDSTRING, 0, (LPARAM)(LPCTSTR)"0.50");
	SendMessage(hDlg, CB_ADDSTRING, 0, (LPARAM)(LPCTSTR)"1.0");
	SendMessage(hDlg, CB_ADDSTRING, 0, (LPARAM)(LPCTSTR)"2.0");
	
	SendMessage(hDlg, CB_SETCURSEL, 1, 0);
}

// *************************************************************************
// *				Fill_ComboBox_AngleValues Terry Flanigan	  		   *
// *************************************************************************
void A_FaceDialog::Fill_ComboBox_AngleValues(HWND hDlg)
{
	SendMessage(hDlg, CB_ADDSTRING, 0, (LPARAM)(LPCTSTR)"5");
	SendMessage(hDlg, CB_ADDSTRING, 0, (LPARAM)(LPCTSTR)"10");
	SendMessage(hDlg, CB_ADDSTRING, 0, (LPARAM)(LPCTSTR)"15");
	SendMessage(hDlg, CB_ADDSTRING, 0, (LPARAM)(LPCTSTR)"30");
	SendMessage(hDlg, CB_ADDSTRING, 0, (LPARAM)(LPCTSTR)"45");
	SendMessage(hDlg, CB_ADDSTRING, 0, (LPARAM)(LPCTSTR)"90");
	
	SendMessage(hDlg, CB_SETCURSEL, 2, 0);
}

// *************************************************************************
// *		  UpdatePolygonFocus:- Terry and Hazel Flanigan 2023		   *
// *************************************************************************
void A_FaceDialog::UpdatePolygonFocus()
{
	App->Get_Current_Document();

	int NumberOfFaces = 0;
	Face *pFace;

	if (App->m_pDoc)
	{
		NumberOfFaces = SelFaceList_GetSize (App->m_pDoc->pSelFaces);
//		pFace = SelFaceList_GetFace (pDoc->pSelFaces, 0);
		if (NumberOfFaces)
		{
			pFace = SelFaceList_GetFace(App->m_pDoc->pSelFaces, (NumberOfFaces - 1));
		}
		else
		{
			pFace = NULL;
		}
	}
	else
	{
		pFace = NULL;
	}

	if (pFace == NULL)
	{
		NumberOfFaces = 0;
	}

	CString StringNumberOfFaces;

	StringNumberOfFaces.Format("%d",NumberOfFaces);
	m_NumFaces = TEXT_NUM_FACES + StringNumberOfFaces;
	
	if (App->m_pDoc && NumberOfFaces && pFace)
	{
		m_TextureAngle	= Face_GetTextureRotate (pFace);
		Face_GetTextureShift (pFace, &m_TextureXOffset, &m_TextureYOffset);
		Face_GetTextureScale (pFace, &m_TextureXScale, &m_TextureYScale);

//		m_TextureLock	=Face_IsTextureLocked (pFace);
//		GetDlgItem( IDC_FACELIGHTINTENSITY )->EnableWindow( m_Light && !m_Sky) ;
//		DisplayingNULL = FALSE;
//		EnabledChange(TRUE);
	}
	else
	{
//		DisplayingNULL = TRUE;
//		EnabledChange(FALSE);
	}

//	UpdateData(FALSE);
}

// *************************************************************************
// *	Update_FaceProperties_Dlg:- Terry and Hazel Flanigan 2023		   *
// *************************************************************************
void A_FaceDialog::Update_FaceProperties_Dlg(HWND hDlg)
{
	App->Get_Current_Document();
	
	SendDlgItemMessage(hDlg, IDC_LISTFACEPROPERTIES, LB_RESETCONTENT, (WPARAM)0, (LPARAM)0);

	char buf[MAX_PATH];
	int NumberOfFaces = 0;
	Face* pFace;


	NumberOfFaces = SelFaceList_GetSize(App->m_pDoc->pSelFaces);
	//		pFace = SelFaceList_GetFace (pDoc->pSelFaces, 0);
	if (NumberOfFaces)
	{
		pFace = SelFaceList_GetFace(App->m_pDoc->pSelFaces, (NumberOfFaces - 1));
	}
	else
	{
		pFace = NULL;
	}

	if (pFace == NULL)
	{
		NumberOfFaces = 0;
		return;
	}
	
	const TexInfo_Vectors* TVecs = Face_GetTextureVecs(pFace);
	geVec3d uVec, vVec;
	geFloat U, V;

	int txSize, tySize;

	Face_GetTextureSize(pFace, &txSize, &tySize);

	// make sure that the texture size is set correctly (division!)
	if (txSize == 0)
		txSize = 32;
	if (tySize == 0)
		tySize = 32;

	geVec3d_Scale(&TVecs->uVec, 1.f / (geFloat)txSize, &uVec);
	geVec3d_Scale(&TVecs->vVec, -1.f / (geFloat)tySize, &vVec);

	const geVec3d* verts = Face_GetPoints(pFace);
	
	int j = 0;
	for (j = 0; j < pFace->NumPoints; j++)
	{
		U = geVec3d_DotProduct(&(verts[j]), &uVec);
		V = geVec3d_DotProduct(&(verts[j]), &vVec);
		U += (TVecs->uOffset / txSize);
		V -= (TVecs->vOffset / tySize);
		
		sprintf(buf, "UV %.3f %.3f", U, V);
		SendDlgItemMessage(hDlg, IDC_LISTFACEPROPERTIES, LB_ADDSTRING, (WPARAM)0, (LPARAM)buf);
	}

}

// *************************************************************************
// *		  UpdateDialog:- Terry and Hazel Flanigan 2023				   *
// *************************************************************************
void A_FaceDialog::UpdateDialog(HWND hDlg)
{
	char buf[255];

	SetDlgItemText(hDlg, IDC_LABEL_NUM_FACES, (LPCTSTR)App->CL_FaceDialog->m_NumFaces);

	sprintf(buf, "%i", m_TextureXOffset);
	SetDlgItemText(hDlg, IDC_EDITXOFFSET, (LPCTSTR)buf);

	sprintf(buf, "%i", m_TextureYOffset);
	SetDlgItemText(hDlg, IDC_EDITYOFFSET, (LPCTSTR)buf);

	sprintf(buf, "%.3f", m_TextureXScale);
	SetDlgItemText(hDlg, IDC_EDITXSCALE, (LPCTSTR)buf);

	sprintf(buf, "%.3f", m_TextureYScale);
	SetDlgItemText(hDlg, IDC_EDITYSCALE, (LPCTSTR)buf);

	sprintf(buf, "%.0f", m_TextureAngle);
	SetDlgItemText(hDlg, IDC_EDITANGLE, (LPCTSTR)buf);

	Update_FaceProperties_Dlg(hDlg);
}

// *************************************************************************
// *		  FlipVertical:- Terry and Hazel Flanigan 2023				   *
// *************************************************************************
geBoolean A_FaceDialog::FlipVertical(Face *pFace, void *)
{
	float xScale, yScale;

	Face_GetTextureScale (pFace, &xScale, &yScale);
	Face_SetTextureScale (pFace, xScale, -yScale);
	return GE_TRUE;
}

// *************************************************************************
// *		  OnFlipvertical:- Terry and Hazel Flanigan 2023			   *
// *************************************************************************
void A_FaceDialog::OnFlipvertical() 
{
	App->m_pDoc = (CFusionDoc*)App->m_pMainFrame->GetCurrentDoc();

	if (App->m_pDoc)
	{
		App->m_pDoc->SetModifiedFlag();
		m_TextureYScale = -m_TextureYScale;
		SelFaceList_Enum (App->m_pDoc->pSelFaces, FlipVertical, NULL);
		AssignCurrentToViews();
	}
}

// *************************************************************************
// *		  FlipHorizontal3:- Terry and Hazel Flanigan 2023			   *
// *************************************************************************
geBoolean A_FaceDialog::FlipHorizontal(Face *pFace, void *)
{
	float xScale, yScale;

	Face_GetTextureScale (pFace, &xScale, &yScale);
	Face_SetTextureScale (pFace, -xScale, yScale);

	return GE_TRUE;
}

// *************************************************************************
// *		  On_FlipHorizontal:- Terry and Hazel Flanigan 2023			   *
// *************************************************************************
bool A_FaceDialog::On_FlipHorizontal()
{
	if (App->m_pDoc)
	{
		App->m_pDoc->SetModifiedFlag();
		m_TextureXScale = -m_TextureXScale;
		SelFaceList_Enum (App->m_pDoc->pSelFaces, FlipHorizontal, NULL);
		AssignCurrentToViews();
	}

	return GE_TRUE;
}

// *************************************************************************
// *		  AssignCurrentToViews:- Terry and Hazel Flanigan 2023		   *
// *************************************************************************
geBoolean A_FaceDialog::ChangeTextureAngle (Face *pFace, void *lParam)
{
	float *pAngle = (float *)lParam;

	Face_SetTextureRotate (pFace, *pAngle);
	return GE_TRUE;
}

// *************************************************************************
// *		  AssignCurrentToViews:- Terry and Hazel Flanigan 2023		   *
// *************************************************************************
void A_FaceDialog::OnKillfocusAngle() 
{	
	App->Get_Current_Document();

	if (App->m_pDoc)
	{
		App->m_pDoc->SetModifiedFlag();
		SelFaceList_Enum (App->m_pDoc->pSelFaces, ChangeTextureAngle, &m_TextureAngle);

		AssignCurrentToViews ();
	}
}

// *************************************************************************
// *		  ChangeYOffset:- Terry and Hazel Flanigan 2023				   *
// *************************************************************************
geBoolean A_FaceDialog::ChangeYOffset (Face *pFace, void *lParam)
{
	int *pYOffset = (int *)(lParam);
	int xOff, yOff;

	Face_GetTextureShift (pFace, &xOff, &yOff);
	Face_SetTextureShift (pFace, xOff, *pYOffset);
	return GE_TRUE;	
}

// *************************************************************************
// *		  OnKillfocusYOffset:- Terry and Hazel Flanigan 2023		   *
// *************************************************************************
void A_FaceDialog::OnKillfocusYOffset() 
{	
	App->Get_Current_Document();

	if (App->m_pDoc)
	{
		App->m_pDoc->SetModifiedFlag();
		SelFaceList_Enum (App->m_pDoc->pSelFaces, ChangeYOffset, &m_TextureYOffset);
		AssignCurrentToViews ();
	}
}

// *************************************************************************
// *		  ChangeXOffset:- Terry and Hazel Flanigan 2023				   *
// *************************************************************************
geBoolean A_FaceDialog::ChangeXOffset (Face *pFace, void *lParam)
{
	int *pXOffset = (int *)(lParam);
	int xOff, yOff;
	
	Face_GetTextureShift (pFace, &xOff, &yOff);
	Face_SetTextureShift (pFace, *pXOffset, yOff);
	return GE_TRUE;	
}

// *************************************************************************
// *		  OnKillfocusYOffset:- Terry and Hazel Flanigan 2023		   *
// *************************************************************************
void A_FaceDialog::OnKillfocusXOffset() 
{
	App->Get_Current_Document();

	if (App->m_pDoc)
	{
		App->m_pDoc->SetModifiedFlag();
		SelFaceList_Enum (App->m_pDoc->pSelFaces, ChangeXOffset, &m_TextureXOffset);
		AssignCurrentToViews ();
	}
}

// *************************************************************************
// *		  ChangeTextureYScale:- Terry and Hazel Flanigan 2023		   *
// *************************************************************************
geBoolean A_FaceDialog::ChangeTextureYScale (Face *pFace, void *lParam)
{
	float *pYScale = (float *)lParam;
	float xScale, yScale;

	Face_GetTextureScale (pFace, &xScale, &yScale);
	Face_SetTextureScale (pFace, xScale, *pYScale);
	return GE_TRUE;
}

// *************************************************************************
// *		  OnKillfocusYScale:- Terry and Hazel Flanigan 2023			   *
// *************************************************************************
void A_FaceDialog::OnKillfocusYScale() 
{
	App->Get_Current_Document();

	if (App->m_pDoc)
	{
		App->m_pDoc->SetModifiedFlag();
		SelFaceList_Enum (App->m_pDoc->pSelFaces, ChangeTextureYScale, &m_TextureYScale);
		AssignCurrentToViews ();
	}
}

// *************************************************************************
// *		  ChangeTextureXScale:- Terry and Hazel Flanigan 2023		   *
// *************************************************************************
geBoolean A_FaceDialog::ChangeTextureXScale (Face *pFace, void *lParam)
{
	float *pXScale = (float *)lParam;
	float xScale, yScale;

	Face_GetTextureScale (pFace, &xScale, &yScale);
	Face_SetTextureScale (pFace, *pXScale, yScale);
	return GE_TRUE;
}

// *************************************************************************
// *		  OnKillfocusXScale:- Terry and Hazel Flanigan 2023			   *
// *************************************************************************
void A_FaceDialog::OnKillfocusXScale() 
{
	App->Get_Current_Document();

	if (App->m_pDoc)
	{
		App->m_pDoc->SetModifiedFlag();
		SelFaceList_Enum (App->m_pDoc->pSelFaces, ChangeTextureXScale, &m_TextureXScale);
		AssignCurrentToViews ();
	}
}

// *************************************************************************
// *		  AssignCurrentToViews:- Terry and Hazel Flanigan 2023		   *
// *************************************************************************
void A_FaceDialog::AssignCurrentToViews()
{
	App->Get_Current_Document();

	if (App->m_pDoc)
	{
		App->m_pDoc->SetModifiedFlag();

		// update child faces on all selected brushes
		int NumSelBrushes;

		NumSelBrushes = SelBrushList_GetSize (App->m_pDoc->pSelBrushes);
		for (int i = 0; i < NumSelBrushes; ++i)
		{
			Brush *pBrush = SelBrushList_GetBrush (App->m_pDoc->pSelBrushes, i);
			Brush_UpdateChildFaces (pBrush);
		}

		App->CLSB_Doc->UpdateAllViews(UAV_RENDER_ONLY, NULL);
	}
}
