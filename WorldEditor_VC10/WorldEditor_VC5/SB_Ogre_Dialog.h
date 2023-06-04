#pragma once
class SB_Ogre_Dialog
{
public:
	SB_Ogre_Dialog(void);
	~SB_Ogre_Dialog(void);

	void Switch_3D_Window();
	void Start_Ogre_Dialog();

	HWND OgreView_3D_hWnd;
	HWND TestHwnd;

	static LRESULT CALLBACK Ogre3D_Proc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);

private:
	static LRESULT CALLBACK Ogre_Dialog_Proc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);
	
};

