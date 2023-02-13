#pragma once
class GD19_PB
{
public:

	GD19_PB(void);
	~GD19_PB(void);

	bool StartNewProgressBar();
	bool Set_Progress(char* ProcessText, float TotalSteps);
	bool Set_Progress_Text(char* ProcessText);
	bool Stop_Progress_Bar(char* ProcessText);
	bool Nudge(char* Message);
	bool Close();

	HWND ProgBarHwnd;

	HWND Dio;
	int Pani;

	int g_pos;

	HWND Bar;

	float Steps;
	bool ClearBarDlg;


protected:

	static LRESULT CALLBACK ProgressNewBarProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);
};

