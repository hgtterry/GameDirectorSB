// TezTest.cpp : implementation file
//

#include "stdafx.h"
#include "fusion.h"
#include "TezTest.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// TezTest dialog


TezTest::TezTest(CWnd* pParent /*=NULL*/)
	: CDialog(TezTest::IDD, pParent)
{
	//{{AFX_DATA_INIT(TezTest)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT

	SBC_bbb = new bbbb();
}


void TezTest::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(TezTest)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(TezTest, CDialog)
	//{{AFX_MSG_MAP(TezTest)
	ON_UPDATE_COMMAND_UI(ID_FILE_EXPORT_AUTODESK3DS, OnUpdateFileExportAutodesk3ds)
	ON_COMMAND(ID_FILE_EXPORT_AUTODESK3DS, OnFileExportAutodesk3ds)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// TezTest message handlers

void TezTest::OnUpdateFileExportAutodesk3ds(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	SBC_bbb->Test();
}

void TezTest::OnFileExportAutodesk3ds() 
{
	SBC_bbb->Test();
	// TODO: Add your command handler code here
	
}

int TezTest::DoModal() 
{
	// TODO: Add your specialized code here and/or call the base class
	
	return CDialog::DoModal();
}

BOOL TezTest::Create(LPCTSTR lpszClassName, LPCTSTR lpszWindowName, DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID, CCreateContext* pContext) 
{
	// TODO: Add your specialized code here and/or call the base class
	
	return CDialog::Create(IDD, pParentWnd);
}
