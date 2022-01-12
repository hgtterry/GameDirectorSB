#pragma once
class ME_App
{
public:
	ME_App();
	~ME_App();

	bool InitApp(void);
	bool SetMainWin_Centre(void);

	HINSTANCE hInst;	// Store instance handle in our global variable [120122]

	HWND MainHwnd;		// Main Window hWnd [120122]
	HWND Fdlg;			// Main Window BackGround [120122]
	HWND ViewGLhWnd;	// Ogre Render Window [120122]
	

	char EquityDirecory_FullPath[MAX_PATH];
};

