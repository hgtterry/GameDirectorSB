// bbbb.h: interface for the bbbb class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_BBBB_H__67B2FFEC_5DC4_4CF1_A56B_A9CCE45B6835__INCLUDED_)
#define AFX_BBBB_H__67B2FFEC_5DC4_4CF1_A56B_A9CCE45B6835__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class bbbb  
{
public:
	bbbb();
	virtual ~bbbb();

	bool Test();
	bool Dialog_Text();

protected:

	static LRESULT CALLBACK Dialog_Text_Proc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);


};

#endif // !defined(AFX_BBBB_H__67B2FFEC_5DC4_4CF1_A56B_A9CCE45B6835__INCLUDED_)
