#pragma once
class GD19_Dialogs
{
public:
	GD19_Dialogs(void);
	~GD19_Dialogs(void);

	bool Dialog_TrueFlase(HWND Parent);
	bool Dialog_Float();
	bool Dialog_Int();
	bool Dialog_Text(int Usage);
	bool Dialog_DropGen();
	void Start_Gen_ListBox(int ListType);
	void Start_Projection();

	void Start_DataView();

	void YesNo(char *Text, char *Text2);
	void Message(char *pString);

	void Start_Mouse_Sensitivity();

	bool GameMode_StartPosition_Dlg();

	bool Canceled;
	bool TrueFlase;
	int CheckNames;

	char btext[100];
	char Chr_DropText[100];
	char Chr_Text[255];
	char Chr_Float[50];
	char Chr_Int[50];

	char Message_Text[255];
	char MessageString[255];
	char MessageString2[255];

	float mFloat;
	int mInt;

	int DropList_Data;
	int Object_Index;

	bool Mouse_Normal2;
	bool Mouse_Slow2;
	bool Mouse_VerySlow2;
	bool Mouse_Fast2;

	int ListBox_Index;
	
protected:
	
	static LRESULT CALLBACK Dialog_TrueFlase_Proc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);
	static LRESULT CALLBACK Dialog_Float_Proc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);
	static LRESULT CALLBACK Dialog_Text_Proc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);
	static LRESULT CALLBACK Dialog_Int_Proc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);
	static LRESULT CALLBACK Gen_ListBox_Proc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);
	static LRESULT CALLBACK Dialog_DropGen_Proc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);
	static LRESULT CALLBACK GameMode_StartPosition_Dlg_Proc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);

	static LRESULT CALLBACK Start_DataView_Proc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);

	static LRESULT CALLBACK YesNo_Proc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);
	static LRESULT CALLBACK Message_Proc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);

	static LRESULT CALLBACK Mouse_Sensitivity_Proc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);
	static LRESULT CALLBACK Projection_Proc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);

	void List_Messages_Stock(HWND List);
	void List_Sounds_Stock(HWND List);

	void ListObjects(HWND DropHwnd);
	void ListAxis(HWND DropHwnd);

	void List_Locations(HWND DropHwnd);

	bool Active_Dlg_Float;
	bool Active_Dlg_Int;

	bool Location_Dlg_Active;

	HWND LocationDlg_hWnd;

	int mListType;

};

