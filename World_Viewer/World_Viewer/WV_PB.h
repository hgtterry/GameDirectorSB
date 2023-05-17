#pragma once
class WV_PB
{
public:

	WV_PB(void);
	~WV_PB(void);

	bool StartNewProgressBar();
	bool Set_Progress(const char* ProcessText, float TotalSteps);
	bool Set_Progress_Text(const char* ProcessText);
	bool Stop_Progress_Bar(const char* ProcessText);
	bool Nudge(const char* Message);
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

