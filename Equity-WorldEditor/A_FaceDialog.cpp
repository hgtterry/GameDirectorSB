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

		return FALSE;
	}

	case WM_CTLCOLORDLG:
		{
			return (LONG)App->AppBackground;
		}

	case WM_NOTIFY:
	{
		/*LPNMHDR some_item = (LPNMHDR)lParam;

		if (some_item->idFrom == IDC_BTTDAPPLY && some_item->code == NM_CUSTOMDRAW)
		{
			LPNMCUSTOMDRAW item = (LPNMCUSTOMDRAW)some_item;
			App->Custom_Button_Normal(item);
			return CDRF_DODEFAULT;
		}*/

		return CDRF_DODEFAULT;
	}

	case WM_VSCROLL:
		{
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

			/*if(HWND(lParam) == GetDlgItem(hDlg, IDC_SBYOFFSET_UNIT))
			{
				App->Say("offset");
			}*/

			/*switch ((int)LOWORD(wParam))
			{

			case SB_LINEUP:

				SetScrollPos((HWND)lParam, SB_CTL, 0, TRUE);
				break;

			case SB_LINEDOWN:

				SetScrollPos((HWND)lParam, SB_CTL, 100, TRUE);
				break;

			}*/

			return 0;
		}

	case WM_COMMAND:
		{
			if (LOWORD(wParam) == IDC_FLIPHORIZONTAL)
			{
				App->CL_FaceDialog->On_FlipHorizontal();
				return TRUE;
			}

			/*if (LOWORD(wParam) == IDC_BTTDAPPLY)
			{
				App->CL_TextureDialog->Apply_Texture();
				return TRUE;
			}*/

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
//		Face_GetLightScale (pFace, &m_LightXScale, &m_LightYScale);
//		m_LightIntensity = Face_GetLightIntensity (pFace);
//		m_MipMapBias = Face_GetMipMapBias (pFace);
//		m_Translucency = Face_GetTranslucency (pFace);
//		m_Reflectivity = Face_GetReflectivity (pFace);
//
//		m_Light			=Face_IsLight (pFace);
//		m_FullBright	=Face_IsFullBright (pFace);
//		m_Gouraud		=Face_IsGouraud (pFace);
//		m_Flat			=Face_IsFlat (pFace);
//		m_TextureLock	=Face_IsTextureLocked (pFace);
//		m_Transparent	=Face_IsTransparent (pFace);
//		m_Sky			=Face_IsSky (pFace);
//		m_Mirror		=Face_IsMirror (pFace);
//
////		GetDlgItem( IDC_FACELIGHTINTENSITY )->EnableWindow( m_Light && !m_Sky) ;
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

	sprintf(buf, "%.0f", m_TextureAngle);
	SetDlgItemText(hDlg, IDC_EDITANGLE, (LPCTSTR)buf);
}


// *************************************************************************
// *		  FlipHorizontal3:- Terry and Hazel Flanigan 2023			   *
// *************************************************************************
geBoolean A_FaceDialog::FlipHorizontal3 (Face *pFace, void *)
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

		SelFaceList_Enum (m_pDoc->pSelFaces, FlipHorizontal3, NULL);

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

		/*UpdateData (TRUE);
		OnFloatKillFocus (m_EditAngle, &m_TextureAngle, 0, "0");*/

		SelFaceList_Enum (m_pDoc->pSelFaces, ChangeTextureAngle, &m_TextureAngle);

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
