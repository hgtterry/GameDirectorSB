/*
Copyright (c) 2022 Equity_ME Model Editor -- HGT Software W.T.Flanigan H.C.Flanigan

This software is provided 'as-is', without any express or implied
warranty. In no event will the authors be held liable for any damages
arising from the use of this software.

Permission is granted to anyone to use this software for any purpose,
including commercial applications, and to alter it and redistribute it
freely, subject to the following restrictions:

1. The origin of this software must not be misrepresented; you must not
claim that you wrote the original software. If you use this software
in a product, an acknowledgment in the product documentation would be
appreciated but is not required.

2. Altered source versions must be plainly marked as such, and must not be
misrepresented as being the original software.

3. This notice may not be removed or altered from any source
distribution.
*/

#pragma once
class ME_Motions
{
public:
	ME_Motions();
	~ME_Motions();

	bool Start_Motions_Dialog();
	bool Update_Motions();
	void Play_SelectedMotion(void);
	void Stop_SelectedMotion(void);
	void Change_SelectedMotion(char* mMotionName);

	char Selected_Motion_Name[255];
	char Decode_MotionByName[255];

	int Selected_Motion_FV_Index; // FIleView Index

	float Current_StartTime;
	float Current_EndTime;

	bool RightMotions_Visable;
	HWND RightMotions_Hwnd;
protected:

	static LRESULT CALLBACK Motions_Proc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);
};

