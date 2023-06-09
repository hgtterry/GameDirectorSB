/****************************************************************************************/
/*  FusionTabControls.cpp                                                               */
/*                                                                                      */
/*  Author:       Jim Mischel, Ken Baird, Jeff Lomax, John Moore                        */
/*  Description:  Tab control ui stuff                                                  */
/*                                                                                      */
/*  The contents of this file are subject to the Genesis3D Public License               */
/*  Version 1.01 (the "License"); you may not use this file except in                   */
/*  compliance with the License. You may obtain a copy of the License at                */
/*  http://www.genesis3d.com                                                            */
/*                                                                                      */
/*  Software distributed under the License is distributed on an "AS IS"                 */
/*  basis, WITHOUT WARRANTY OF ANY KIND, either express or implied.  See                */
/*  the License for the specific language governing rights and limitations              */
/*  under the License.                                                                  */
/*                                                                                      */
/*  The Original Code is Genesis3D, released March 25, 1999.                            */
/*  Copyright (C) 1996-1999 Eclipse Entertainment, L.L.C. All Rights Reserved           */
/*                                                                                      */
/****************************************************************************************/

/*	This class will handle all coordination between the user tab interface
	and the current document.  If the user clicks on a tab, it has to update
	itself using information from the current document.  If the user makes
	changes in the tab, it has to make sure that the current document is
	updated in return... */

#include "stdafx.h"
#include "FusionTabControls.h"
#include "ChildFrm.h"
#include "FusionDoc.h"
#include "Model.h"

#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CFusionTabControls

CFusionTabControls::CFusionTabControls( CDialogBar* pDBar)
{
	//	Create a pointer to the main window...
	//m_pMainFrame		=(CMainFrame *)AfxGetMainWnd();
	//LastView			=(CMainFrame *)AfxGetMainWnd();

	//ModelTab			=NULL;
	
	//	Create a pointer to the main window's CDialogBar...
	//m_pDialogBar		=pDBar;
}

CFusionTabControls::~CFusionTabControls()
{
	
}/* ~CFusionTabControls */


BEGIN_MESSAGE_MAP(CFusionTabControls, CTabCtrl)
	//{{AFX_MSG_MAP(CFusionTabControls)
	ON_NOTIFY_REFLECT(TCN_SELCHANGE, OnSelchange)
	ON_WM_SETFOCUS()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CFusionTabControls message handlers

//struct TabItem
//{
//	UINT WhichTab;
//	char *Text;
//};
//
//static const TabItem Tabs[] = 
//{
//	{TEXTURE_TAB,		"Textures"},
//	{GROUP_TAB,			"Groups"},
//};
	 
//static const int NumTabs = sizeof (Tabs) / sizeof (TabItem);

BOOL CFusionTabControls::CreateTabs()
{
	/*int tab;

	for (tab = 0; tab < NumTabs; ++tab)
	{
		TC_ITEM item;
	
		item.mask = TCIF_TEXT;
		item.pszText = Tabs[tab].Text;
		InsertItem (Tabs[tab].WhichTab, &item);
	}

	m_CurrentTab = GetCurSel();*/

	return TRUE;
}

#pragma warning (disable:4100)
void CFusionTabControls::OnSelchange(NMHDR* pNMHDR, LRESULT* pResult) 
{
	//	Which tab is now currently selected?
	/*m_CurrentTab = GetCurSel();	

	UpdateTabs();

	*pResult = 0;*/
}
#pragma warning (default:4100)


const char *CFusionTabControls::GetCurrentTexture()
{
	//return m_pTextureDialog->GetCurrentTexture();
	return "u";
}

void	CFusionTabControls::SelectTexture(int SelNum)
{
	
}

void CFusionTabControls::UpdateTextures (void)
{
	
}


//	Use this whenever the user closes all documents...
void CFusionTabControls::DisableAllTabDialogs()
{

}/* CFusionTabControls::DisableAllTabDialogs */


void CFusionTabControls::OnSetFocus(CWnd* pOldWnd) 
{
//	CTabCtrl::OnSetFocus(pOldWnd);
//	LastView=pOldWnd;
}
