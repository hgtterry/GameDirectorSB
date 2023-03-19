/*
Copyright (c) 2023 Equity_ME World Editor -- HGT Software W.T.Flanigan H.C.Flanigan

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
#include "A_TextureDialog.h"

#include "WadFile.h"
#include "Ram.h"

#include "FUSIONView.h"
#include "FUSIONDoc.h"

A_TextureDialog::A_TextureDialog(void)
{
	f_TextureDlg_Active = 0;
	TextureDlg_Hwnd = NULL;
	m_pDoc = NULL;

	strcpy(m_CurrentTexture,"aztec66");

	Sel_BaseBitmap = NULL;
	BasePicWidth = NULL;
	BasePicHeight = NULL;
}

A_TextureDialog::~A_TextureDialog(void)
{
}

// *************************************************************************
// *	  		Show_Dialog:- Terry and Hazel Flanigan 2023				   *
// *************************************************************************
void A_TextureDialog::Show_Dialog(bool Show)
{
	if (App->CL_TextureDialog->f_TextureDlg_Active == 1)
	{
		ShowWindow(TextureDlg_Hwnd, Show);
	}
}

// *************************************************************************
// *	  	Start_TextureDialog:- Terry and Hazel Flanigan 2023			   *
// *************************************************************************
void A_TextureDialog::Start_TextureDialog()
{
	TextureDlg_Hwnd = CreateDialog(App->hInst, (LPCTSTR)IDD_DLGRIGHTPANE, App->MainHwnd, (DLGPROC)TextureDialog_Proc);

	Set_Txl_FileName();
	Fill_ListBox();
	Get_BitMap();
}

// *************************************************************************
// *        TextureDialog_Proc:- Terry and Hazel Flanigan 2023			   *
// *************************************************************************
LRESULT CALLBACK A_TextureDialog::TextureDialog_Proc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{

	switch (message)
	{
	case WM_INITDIALOG:
	{
		SendDlgItemMessage(hDlg, IDC_STTDTXLNAME, WM_SETFONT, (WPARAM)App->Font_CB18, MAKELPARAM(TRUE, 0));
		SendDlgItemMessage(hDlg, IDC_LISTTDTEXTURES, WM_SETFONT, (WPARAM)App->Font_CB15, MAKELPARAM(TRUE, 0));
		SendDlgItemMessage(hDlg, IDC_BTTDAPPLY, WM_SETFONT, (WPARAM)App->Font_CB15, MAKELPARAM(TRUE, 0));
		
		App->CL_TextureDialog->f_TextureDlg_Active = 1;

		SetWindowLong(GetDlgItem(hDlg, IDC_BASETEXTURE2), GWL_WNDPROC, (LONG)ViewerBasePic);

		return TRUE;
	}
	case WM_CTLCOLORSTATIC:
	{
		if (GetDlgItem(hDlg, IDC_STTDTXLNAME) == (HWND)lParam)
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

		if (some_item->idFrom == IDC_BTTDAPPLY && some_item->code == NM_CUSTOMDRAW)
		{
			LPNMCUSTOMDRAW item = (LPNMCUSTOMDRAW)some_item;
			App->Custom_Button_Normal(item);
			return CDRF_DODEFAULT;
		}

		return CDRF_DODEFAULT;
	}

	case WM_COMMAND:
		{
			if (LOWORD(wParam) == IDC_LISTTDTEXTURES)
			{
				App->CL_TextureDialog->List_Selection_Changed();
				return TRUE;
			}

			if (LOWORD(wParam) == IDC_BTTDAPPLY)
			{
				App->CL_TextureDialog->Apply_Texture();
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
// *						ViewerBasePic Terry Flanigan	  			   *
// *************************************************************************
bool CALLBACK A_TextureDialog::ViewerBasePic(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
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

		if (App->CL_TextureDialog->Sel_BaseBitmap != NULL)
		{
			RECT	Source;
			RECT	Dest;
			HDC		hDC;

			Source.left = 0;
			Source.top = 0;
			Source.bottom = App->CL_TextureDialog->BasePicHeight;
			Source.right = App->CL_TextureDialog->BasePicWidth;

			Dest = Rect;

			hDC = GetDC(hwnd);
			SetStretchBltMode(hDC, HALFTONE);

			App->CL_TextureDialog->RenderTexture_Blit(hDC, App->CL_TextureDialog->Sel_BaseBitmap, &Source, &Dest);
			ReleaseDC(hwnd, hDC);

		}

		EndPaint(hwnd, &ps);
		return 0;
	}

	DefWindowProc(hwnd, msg, wParam, lParam);
}

// *************************************************************************
// *					RenderTexture_Blit Terry Bernie		  		   *
// *************************************************************************
bool A_TextureDialog::RenderTexture_Blit(HDC hDC, HBITMAP Bmp, const RECT *SourceRect, const RECT *DestRect)
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

static void TextureFace
	(
	  Face *pFace,
	  int SelId,
	  char const *Name,
	  WadFileEntry* pbmp // changed QD 12/03
	)
{
	Face_SetTextureDibId (pFace, SelId);
	Face_SetTextureName (pFace, Name);
// changed QD 12/03
	Face_SetTextureSize (pFace, pbmp->Width, pbmp->Height);
// end change
}

// changed QD 12/03
static void TextureBrushList(BrushList *pList, int SelId, char const *Name, WadFileEntry* pbmp);

static void TextureBrush(Brush *pBrush,int SelId,char const *Name,WadFileEntry* pbmp) // changed QD 12/03)
{
	int j;

	assert(pBrush);
	
	if(Brush_IsMulti(pBrush))
	{
		// changed QD 12/03
		TextureBrushList((BrushList *)Brush_GetBrushList(pBrush), SelId, Name, pbmp);
	}
	else
	{
		for (j = 0; j < Brush_GetNumFaces (pBrush); ++j)
		{
			Face *pFace;

			pFace = Brush_GetFace (pBrush, j);
			TextureFace (pFace, SelId, Name, pbmp); // changed QD 12/03
		}
	}
}

static void TextureBrushList
	(
	  BrushList *pList,
	  int SelId,
	  char const *Name,
	  WadFileEntry* pbmp // changed QD 12/03
	)
{
	Brush *b;
	BrushIterator bi;

	assert(pList);
	assert(Name);

#pragma message ("Change this and the function above to use BrushList_EnumAll")
	for(b=BrushList_GetFirst(pList, &bi);b;b=BrushList_GetNext(&bi))
	{
		TextureBrush(b, SelId, Name, pbmp); // changed QD 12/03
	}	
}




// *************************************************************************
// *			Apply_Texture:- Terry and Hazel Flanigan 2023			   *
// *************************************************************************
void A_TextureDialog::Apply_Texture() 
{
	m_pDoc = (CFusionDoc*)App->m_pMainFrame->GetCurrentDoc();

	int SelectedItem;
	int SelId;
	int		i;
	
	SelectedItem = SendDlgItemMessage(TextureDlg_Hwnd, IDC_LISTTDTEXTURES, LB_GETCURSEL, (WPARAM)0, (LPARAM)0);

	//SetCurSel( SelectedItem );
	
	SelId = SelectedItem;// = LBIndex;SelectedItem;//0;//m_TextureList.GetItemData (SelectedItem);

	if(m_pDoc->mModeTool==ID_TOOLS_TEMPLATE)
		return;
	
	m_pDoc->SetModifiedFlag();	

	switch (m_pDoc->mAdjustMode)
	{
		case ADJUST_MODE_FACE :
		{
			int Size;

			Size = SelFaceList_GetSize (m_pDoc->pSelFaces);
			for (i = 0; i < Size; ++i)
			{
				Face *pFace;
				pFace = SelFaceList_GetFace (m_pDoc->pSelFaces, i);

				// changed QD 12/03
				WadFileEntry* BitmapPtr = m_pDoc->GetDibBitmap( m_CurrentTexture );
				::TextureFace (pFace, SelId, (LPCSTR)m_CurrentTexture, BitmapPtr);
				// end change
			}
			// have to go through the selected brushes and update their child faces
			int NumSelBrushes = SelBrushList_GetSize (m_pDoc->pSelBrushes);
			for (i = 0; i < NumSelBrushes; ++i)
			{
				Brush *pBrush;

				pBrush = SelBrushList_GetBrush (m_pDoc->pSelBrushes, i);
				Brush_UpdateChildFaces (pBrush);
			}
			break;
		}

		case ADJUST_MODE_BRUSH :
		{
			if(m_pDoc->GetSelState() & MULTIBRUSH)
			{
				int NumSelBrushes = SelBrushList_GetSize (m_pDoc->pSelBrushes);
				for (i = 0; i < NumSelBrushes; ++i)
				{
					Brush *pBrush = SelBrushList_GetBrush (m_pDoc->pSelBrushes, i);
					// changed QD 12/03
					WadFileEntry* BitmapPtr = m_pDoc->GetDibBitmap( m_CurrentTexture );
					::TextureBrush (pBrush, SelId, (LPCSTR)m_CurrentTexture, BitmapPtr);
					// end change
					Brush_UpdateChildFaces (pBrush);
				}
			}
			else
			{
				// changed QD 12/03
				WadFileEntry* BitmapPtr = m_pDoc->GetDibBitmap( m_CurrentTexture );
				::TextureBrush (m_pDoc->CurBrush, SelId, (LPCSTR)m_CurrentTexture, BitmapPtr);
				// end change
				Brush_UpdateChildFaces (m_pDoc->CurBrush);
			}
			break;
		}

		default :
			return;
	}

	//if(m_pParentCtrl->LastView)
		//m_pParentCtrl->LastView->SetFocus();

	m_pDoc->UpdateAllViews(UAV_ALL3DVIEWS, NULL);
	
}

// *************************************************************************
// *			Select_Texture:- Terry and Hazel Flanigan 2023			   *
// *************************************************************************
void A_TextureDialog::Select_Texture(int SelNum)
{

	SendDlgItemMessage(TextureDlg_Hwnd, IDC_LISTTDTEXTURES,LB_SETCURSEL, (WPARAM)SelNum, (LPARAM)0);
	List_Selection_Changed();

	/*for (int i = 0; i < m_TextureList.GetCount(); ++i)
	{
		int SelId = m_TextureList.GetItemData (i);
		if (SelNum == SelId)
		{
			SetCurSel(i);
			OnSelchangetexturelist();
			return;
		}
	}*/
}

// *************************************************************************
// *	  	List_Selection_Changed:- Terry and Hazel Flanigan 2023		   *
// *************************************************************************
void A_TextureDialog::List_Selection_Changed()
{
	int Index = SendDlgItemMessage(TextureDlg_Hwnd, IDC_LISTTDTEXTURES, LB_GETCURSEL, (WPARAM)0, (LPARAM)0);
	if	(Index == LB_ERR)
	{
		App->Say("?");
	}
	else
	{
		char TextureName[MAX_PATH];
		SendDlgItemMessage(TextureDlg_Hwnd, IDC_LISTTDTEXTURES, LB_GETTEXT, (WPARAM)Index, (LPARAM)TextureName);
		strcpy(m_CurrentTexture,TextureName);
		Get_BitMap();
	}

	//	Also set the current selection value in the document...
	//m_pDoc->mCurTextureSelection = SelNum;
}

// *************************************************************************
// *	  	Set_Txl_FileName:- Terry and Hazel Flanigan 2023			   *
// *************************************************************************
void A_TextureDialog::Set_Txl_FileName()
{
	SetDlgItemText(TextureDlg_Hwnd, IDC_STTDTXLNAME, (LPCTSTR)App->CL_Scene->Current_TXL_FileName);
}

// *************************************************************************
// *	  		Get_BitMap:- Terry and Hazel Flanigan 2023				   *
// *************************************************************************
void A_TextureDialog::Get_BitMap()
{
	m_pDoc = (CFusionDoc*)App->m_pMainFrame->GetCurrentDoc();
	WadFileEntry* BitmapPtr = m_pDoc->GetDibBitmap(m_CurrentTexture);

	HWND	PreviewWnd;
	HBITMAP	hbm;
	//HBITMAP	ahbm;
	HDC		hDC;

	PreviewWnd = GetDlgItem(TextureDlg_Hwnd, IDC_BASETEXTURE2);
	hDC = GetDC(PreviewWnd);
	hbm = CreateHBitmapFromgeBitmap(BitmapPtr->bmp, hDC);

	if(geBitmap_HasAlpha(BitmapPtr->bmp))
	{
		hbm = CreateHBitmapFromgeBitmap(geBitmap_GetAlpha(BitmapPtr->bmp), hDC);
		if (hbm == NULL)
		{
			App->Say("Cant Assign Bitmap");
			Sel_BaseBitmap = NULL;
			return;
		}

		Sel_BaseBitmap = hbm;
	}
	else
	{
		hbm = CreateHBitmapFromgeBitmap(BitmapPtr->bmp, hDC);
		if (hbm == NULL)
		{
			App->Say("Cant Assign Bitmap");
			Sel_BaseBitmap = NULL;
			return;
		}

		Sel_BaseBitmap = hbm;
	}

	App->CL_TextureDialog->BasePicHeight = BitmapPtr->Height;
	App->CL_TextureDialog->BasePicWidth = BitmapPtr->Width;

	ReleaseDC(PreviewWnd, hDC);
	InvalidateRect(GetDlgItem(TextureDlg_Hwnd, IDC_BASETEXTURE2), NULL, TRUE);

}

// *************************************************************************
// *				CreateHBitmapFromgeBitmap  06/06/08 		  		   *
// *************************************************************************
HBITMAP A_TextureDialog::CreateHBitmapFromgeBitmap (geBitmap *Bitmap, HDC hdc)
{
	geBitmap * Lock;
	gePixelFormat Format;
	geBitmap_Info info;
	HBITMAP hbm = NULL;

	// <> choose format to be 8,16,or 24, whichever is closest to Bitmap
	Format = GE_PIXELFORMAT_24BIT_BGR;

	if ( geBitmap_GetBits(Bitmap) )
	{
		Lock = Bitmap;
	}
	else
	{
		if ( ! geBitmap_LockForRead(Bitmap, &Lock, 0, 0, Format,	GE_FALSE,0) )
		{
			return NULL;
		}
	}

	geBitmap_GetInfo(Lock,&info,NULL);

	if ( info.Format != Format )
		return NULL;

	{
		void * bits;
		BITMAPINFOHEADER bmih;
		int pelbytes;

		pelbytes = gePixelFormat_BytesPerPel(Format);
		bits = geBitmap_GetBits(Lock);

		bmih.biSize = sizeof(bmih);
		bmih.biHeight = - info.Height;
		bmih.biPlanes = 1;
		bmih.biBitCount = 24;
		bmih.biCompression = BI_RGB;
		bmih.biSizeImage = 0;
		bmih.biXPelsPerMeter = bmih.biYPelsPerMeter = 10000;
		bmih.biClrUsed = bmih.biClrImportant = 0;

		if ( (info.Stride*pelbytes) == (((info.Stride*pelbytes)+3)&(~3)) )
		{
			bmih.biWidth = info.Stride;
			hbm = CreateDIBitmap( hdc, &bmih , CBM_INIT , bits, (BITMAPINFO *)&bmih , DIB_RGB_COLORS );
		}
		else
		{
			void * newbits;
			int Stride;

			bmih.biWidth = info.Width;
			Stride = (((info.Width*pelbytes)+3)&(~3));
			newbits = geRam_Allocate(Stride * info.Height);
			if ( newbits )
			{
				char *newptr,*oldptr;
				int y;

				newptr = (char *)newbits;
				oldptr = (char *)bits;
				for(y=0; y<info.Height; y++)
				{
					memcpy(newptr,oldptr,(info.Width)*pelbytes);
					oldptr += info.Stride*pelbytes;
					newptr += Stride;
				}
				hbm = CreateDIBitmap( hdc, &bmih , CBM_INIT , newbits, (BITMAPINFO *)&bmih , DIB_RGB_COLORS );
				geRam_Free(newbits);
			}
		}
	}

	if ( Lock != Bitmap )
	{
		geBitmap_UnLock (Lock);
	}

	return hbm;
}

// *************************************************************************
// *			Fill_ListBox:- Terry and Hazel Flanigan 2023			   *
// *************************************************************************
void A_TextureDialog::Fill_ListBox()
{
	if (f_TextureDlg_Active == 1)
	{
		m_pDoc = (CFusionDoc*)App->m_pMainFrame->GetCurrentDoc();

		CWadFile *pWad;
		pWad = NULL;

		SendDlgItemMessage(TextureDlg_Hwnd, IDC_LISTTDTEXTURES, LB_RESETCONTENT, (WPARAM)0, (LPARAM)0);

		pWad = Level_GetWadFile (m_pDoc->pLevel);
		if (pWad == NULL)
		{
			App->Say("Error Getting Wad File");
			return;
		}

		for (int index = 0; index < pWad->mBitmapCount; index++)
		{
			char mName[MAX_PATH];

			CString Name = pWad->mBitmaps[index].Name;
			strcpy(mName,Name);


			int LBIndex = SendDlgItemMessage(TextureDlg_Hwnd, IDC_LISTTDTEXTURES, LB_ADDSTRING, (WPARAM)0,(LPARAM) mName);

			ItemData[index] = LBIndex;

			//// Listbox is sorted, so we need to put the wad file index into the item data.
			//int lbIndex = m_TextureList.AddString( (LPCTSTR) Name );
			//if (lbIndex != LB_ERR)
			//{
			//	m_TextureList.SetItemData (lbIndex, index);
			//}
		}
				SendDlgItemMessage(TextureDlg_Hwnd, IDC_LISTTDTEXTURES,LB_SETCURSEL, (WPARAM)0, (LPARAM)0);
				List_Selection_Changed();
	}
}


//IDC_LISTTDTEXTURES