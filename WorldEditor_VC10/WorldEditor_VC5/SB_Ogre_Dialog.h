#pragma once
class SB_Ogre_Dialog
{
public:
	SB_Ogre_Dialog(void);
	~SB_Ogre_Dialog(void);

	void Start_Ogre_Dialog();

	ATOM SB_Ogre_Dialog::MyRegisterClass(HINSTANCE hInstance);

	TCHAR szWindowClass[100];            // the main window class name

	HWND OgreView_3D_hWnd;
	HWND TestHwnd;

	static bool CALLBACK Ogre3D_Proc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);

private:
	static LRESULT CALLBACK Ogre_Dialog_Proc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);
	
};

