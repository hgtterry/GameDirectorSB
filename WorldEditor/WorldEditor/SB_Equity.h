#pragma once
class SB_Equity
{
public:
	SB_Equity(void);
	~SB_Equity(void);

	void Start_Equity_Dialog_New();

	bool Auto_Load_File();
	void Show_Equity_Dialog(bool Show);

	void Set_Mode_Equity();
	
	void Do_Equity();
	void Do_Preview_Selected();
	void Do_Preview_All();
	void Resize_3DView();

	bool mAutoLoad;
	bool First_Run;
	bool EquitySB_Dialog_Created;
	bool EquitySB_Dialog_Visible;
	int Equity_Start_Mode;

	HWND OgreView_3D_hWnd;
	HWND Render_Buttons_hWnd;

	bool Close_Equity_Flag;

	Ogre::Vector3 Position_Offsets;

	static LRESULT CALLBACK Ogre3D_New_Proc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);

private:

	static LRESULT CALLBACK Equity_Dialog_New_Proc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);

	static LRESULT CALLBACK Render_Buttons_Proc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);


	bool Start_Render_Buttons();
	void Init_Bmps_Globals(void);

	void Get_CurrentDocument();

	CFusionDoc* m_pDoc;
};

