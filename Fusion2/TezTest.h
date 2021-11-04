#if !defined(AFX_TEZTEST_H__E4AF3808_4D99_4911_A2D3_522FDFBA0845__INCLUDED_)
#define AFX_TEZTEST_H__E4AF3808_4D99_4911_A2D3_522FDFBA0845__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// TezTest.h : header file
//

#include "bbbb.h"

/////////////////////////////////////////////////////////////////////////////
// TezTest dialog

class TezTest : public CDialog
{
// Construction
public:
	TezTest(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(TezTest)
	enum { IDD = IDD_EXPORT3DSDIALOG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	bbbb*	SBC_bbb;
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(TezTest)
	public:
	virtual int DoModal();
	virtual BOOL Create(LPCTSTR lpszClassName, LPCTSTR lpszWindowName, DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID, CCreateContext* pContext = NULL);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(TezTest)
	afx_msg void OnUpdateFileExportAutodesk3ds(CCmdUI* pCmdUI);
	afx_msg void OnFileExportAutodesk3ds();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TEZTEST_H__E4AF3808_4D99_4911_A2D3_522FDFBA0845__INCLUDED_)
