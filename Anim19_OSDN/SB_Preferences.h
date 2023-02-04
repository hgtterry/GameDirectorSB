/*
Copyright (c) 2021 EquitySB and EquityME -- Inflanite Software W.T.Flanigan H.C.Flanigan

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
class SB_Preferences
{
public:
	SB_Preferences();
	~SB_Preferences();

	void Start_Preferences_GUI();
	void Preferences_GUI();
	void Close_Preferences_GUI();

	bool Show_Preferences_GUI;
	int Preferences_Page;


	void Set_Defaults();
	bool Write_Preferences();
	bool Read_Preferences();

	// Start Up
	char QL_User_File[MAX_PATH];

	bool Prefs_TestFile_Flag;
	bool Prefs_StartScreen_Flag;
	bool Prefs_FullScreen_Flag;
	bool Prefs_Load_LastScene_Flag;

	// Game Options
	bool Prefs_PlayerCanJump_Flag;

protected:

	FILE *WriteScene;

	float PosX;
	float PosY;
};


