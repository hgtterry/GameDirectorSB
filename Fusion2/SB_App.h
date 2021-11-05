// SB_App.h: interface for the SB_App class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SB_APP_H__32FF1015_03E8_4EB9_BE5C_D9E4748043B5__INCLUDED_)
#define AFX_SB_APP_H__32FF1015_03E8_4EB9_BE5C_D9E4748043B5__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class SB_App  
{
public:
	SB_App();
	virtual ~SB_App();

	void Say(const char* Message);

	bool Start_EquityTab();

	bool Init();
	void SetBrushes_Fonts(void);

	bool UpdateTab_Dialog(HWND hDlg);

	bool Show_Dialog(bool flag);

	int	NumSelEntities;

	HWND EqutyTab_Hwnd;

	HBRUSH AppBackground;
	HBRUSH DialogBackGround;
	HBRUSH BlackBrush;
	HBRUSH Brush_White;
	HBRUSH Brush_Red;
	HBRUSH Brush_Blue;
	HBRUSH Brush_Green;
	HBRUSH Brush_But_Pressed;
	HBRUSH Brush_But_Normal;
	HBRUSH Brush_But_Hover;
	HBRUSH Brush_Tabs;
	HBRUSH Brush_Tabs_UnSelected;

	HFONT Font_CB12;
	HFONT Font_CB15;
	HFONT Font_Arial20;
	HFONT Font_CB15_Bold;
	
protected:

	static LRESULT CALLBACK EquityTab_Proc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);

};

extern SB_App* App;

#endif // !defined(AFX_SB_APP_H__32FF1015_03E8_4EB9_BE5C_D9E4748043B5__INCLUDED_)
