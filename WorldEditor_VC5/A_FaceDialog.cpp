#include "stdafx.h"
#include "AB_App.h"
#include "resource.h"
#include "A_FaceDialog.h"

#include "FUSIONView.h"
#include "FUSIONDoc.h"

static CString TEXT_NUM_FACES = "Number of Faces Selected: ";

A_FaceDialog::A_FaceDialog(void)
{
	m_TextureAngle = 0;

	m_TextureXScale = 0;
	m_TextureYScale = 0;

	m_TextureYOffset = 0;
	m_TextureXOffset = 0;

	f_FaceDlg_Active = 0;
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
	FaceDlg_Hwnd = CreateDialog(App->hInst, (LPCTSTR)IDD_FACEDIALOG, App->MainHwnd, (DLGPROC)FaceDialog_Proc);

	f_FaceDlg_Active = 1;
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
		//SendDlgItemMessage(hDlg, IDC_LABEL_NUM_FACES, WM_SETFONT, (WPARAM)App->Font_CB18, MAKELPARAM(TRUE, 0));
		//SendDlgItemMessage(hDlg, IDC_LISTTDTEXTURES, WM_SETFONT, (WPARAM)App->Font_CB15, MAKELPARAM(TRUE, 0));

		App->CL_FaceDialog->UpdatePolygonFocus();

		App->CL_FaceDialog->UpdateDialog(hDlg);

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
		if (GetDlgItem(hDlg, IDC_GROUP_TEXTURE_OFFSET_SCALE) == (HWND)lParam)
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

					App->CL_FaceDialog->m_TextureYScale = App->CL_FaceDialog->m_TextureYScale + (float)0.05;
					App->CL_FaceDialog->UpdateDialog(hDlg);
					App->CL_FaceDialog->OnKillfocusYScale() ;

					break;

				case SB_LINEDOWN:
					App->CL_FaceDialog->m_TextureYScale = App->CL_FaceDialog->m_TextureYScale - (float)0.05;
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

					App->CL_FaceDialog->m_TextureXScale = App->CL_FaceDialog->m_TextureXScale + (float)0.05;
					App->CL_FaceDialog->UpdateDialog(hDlg);
					App->CL_FaceDialog->OnKillfocusXScale() ;

					break;

				case SB_LINEDOWN:
					App->CL_FaceDialog->m_TextureXScale = App->CL_FaceDialog->m_TextureXScale - (float)0.05;
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
			if (LOWORD(wParam) == IDC_FLIPHORIZONTAL)
			{
				App->CL_FaceDialog->On_FlipHorizontal();
				return TRUE;
			}

			if (LOWORD(wParam) == IDC_FLIPVERTICAL)
			{
				App->CL_FaceDialog->OnFlipvertical();
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
	SendMessage(hDlg, CB_ADDSTRING, 0, (LPARAM)(LPCTSTR)"0.1");
	SendMessage(hDlg, CB_ADDSTRING, 0, (LPARAM)(LPCTSTR)"0.2");
	SendMessage(hDlg, CB_ADDSTRING, 0, (LPARAM)(LPCTSTR)"0.5");
	SendMessage(hDlg, CB_ADDSTRING, 0, (LPARAM)(LPCTSTR)"0.75");
	SendMessage(hDlg, CB_ADDSTRING, 0, (LPARAM)(LPCTSTR)"1.0");
	SendMessage(hDlg, CB_ADDSTRING, 0, (LPARAM)(LPCTSTR)"2.0");
	
	SendMessage(hDlg, CB_SETCURSEL, 2, 0);
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
	int NumberOfFaces = 0;
	Face *pFace;

	m_pDoc = (CFusionDoc*)App->m_pMainFrame->GetCurrentDoc();
	
	if (m_pDoc)
	{
		NumberOfFaces = SelFaceList_GetSize (m_pDoc->pSelFaces);
//		pFace = SelFaceList_GetFace (pDoc->pSelFaces, 0);
		if (NumberOfFaces)
			pFace = SelFaceList_GetFace (m_pDoc->pSelFaces, (NumberOfFaces-1));
		else
			pFace = NULL;
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
	
	if (m_pDoc && NumberOfFaces && pFace)
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

	sprintf(buf, "%.2f", m_TextureXScale);
	SetDlgItemText(hDlg, IDC_EDITXSCALE, (LPCTSTR)buf);

	sprintf(buf, "%.2f", m_TextureYScale);
	SetDlgItemText(hDlg, IDC_EDITYSCALE, (LPCTSTR)buf);

	sprintf(buf, "%.0f", m_TextureAngle);
	SetDlgItemText(hDlg, IDC_EDITANGLE, (LPCTSTR)buf);
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
	m_pDoc = (CFusionDoc*)App->m_pMainFrame->GetCurrentDoc();

	if (m_pDoc)
	{
		m_pDoc->SetModifiedFlag();
		m_TextureYScale = -m_TextureYScale;
		SelFaceList_Enum (m_pDoc->pSelFaces, FlipVertical, NULL);
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
	m_pDoc = (CFusionDoc*)App->m_pMainFrame->GetCurrentDoc();

	if (m_pDoc)
	{
		m_pDoc->SetModifiedFlag();
		m_TextureXScale = -m_TextureXScale;
		SelFaceList_Enum (m_pDoc->pSelFaces, FlipHorizontal, NULL);
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
	m_pDoc = (CFusionDoc*)App->m_pMainFrame->GetCurrentDoc();

	if (m_pDoc)
	{
		m_pDoc->SetModifiedFlag();
		//UpdateData (TRUE);
		//OnFloatKillFocus (m_EditAngle, &m_TextureAngle, 0, "0");
		SelFaceList_Enum (m_pDoc->pSelFaces, ChangeTextureAngle, &m_TextureAngle);

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
	m_pDoc = (CFusionDoc*)App->m_pMainFrame->GetCurrentDoc();

	if (m_pDoc)
	{
		m_pDoc->SetModifiedFlag();
		//UpdateData (TRUE);
		//OnIntKillFocus (m_EditYOffset, &m_TextureYOffset, 0, "0");
		SelFaceList_Enum (m_pDoc->pSelFaces, ChangeYOffset, &m_TextureYOffset);
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
	m_pDoc = (CFusionDoc*)App->m_pMainFrame->GetCurrentDoc();

	if (m_pDoc)
	{
		m_pDoc->SetModifiedFlag();
		//UpdateData (TRUE);
		//OnIntKillFocus (m_EditXOffset, &m_TextureXOffset, 0, "0");
		SelFaceList_Enum (m_pDoc->pSelFaces, ChangeXOffset, &m_TextureXOffset);
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
	m_pDoc = (CFusionDoc*)App->m_pMainFrame->GetCurrentDoc();

	if (m_pDoc)
	{
		m_pDoc->SetModifiedFlag();
		//UpdateData (TRUE);
		//OnFloatKillFocus (m_EditYScale, &m_TextureYScale, 1.0f, "1.0");
		SelFaceList_Enum (m_pDoc->pSelFaces, ChangeTextureYScale, &m_TextureYScale);
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
	m_pDoc = (CFusionDoc*)App->m_pMainFrame->GetCurrentDoc();

	if (m_pDoc)
	{
		m_pDoc->SetModifiedFlag();
		//UpdateData (TRUE);
		//OnFloatKillFocus (m_EditXScale, &m_TextureXScale, 1.0f, "1.0");
		SelFaceList_Enum (m_pDoc->pSelFaces, ChangeTextureXScale, &m_TextureXScale);
		AssignCurrentToViews ();
	}
}

// *************************************************************************
// *		  AssignCurrentToViews:- Terry and Hazel Flanigan 2023		   *
// *************************************************************************
void A_FaceDialog::AssignCurrentToViews()
{
	m_pDoc = (CFusionDoc*)App->m_pMainFrame->GetCurrentDoc();

	if (m_pDoc)
	{
		m_pDoc->SetModifiedFlag();

		// update child faces on all selected brushes
		int NumSelBrushes;

		NumSelBrushes = SelBrushList_GetSize (m_pDoc->pSelBrushes);
		for (int i = 0; i < NumSelBrushes; ++i)
		{
			Brush *pBrush = SelBrushList_GetBrush (m_pDoc->pSelBrushes, i);
			Brush_UpdateChildFaces (pBrush);
		}

		m_pDoc->UpdateAllViews(UAV_RENDER_ONLY, NULL);
	}
}
