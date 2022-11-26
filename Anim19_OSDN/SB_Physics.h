/*
Copyright (c) 2021 Stage Builder and Equity -- Inflanite Software W.T.Flanigan H.C.Flanigan

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
class SB_Physics
{
public:
	SB_Physics();
	~SB_Physics();

	void Start_Physics_Console(void);
	bool Start_Physics_Pannel();
	void Reset_Physics(void);
	void Reset_Triggers(void);

	bool Physics_Console_Dlg_Active;

	// Enable Disable Physics [231121]
	void Enable_Physics(bool Enable);
	void Physics_On(bool Enable);

	HWND PhysicsPannel_Hwnd;

protected:

	static LRESULT CALLBACK Start_Physics_Proc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);
	static LRESULT CALLBACK Physics_Console_Proc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);

	void Init_Bmps_Physics();

	void Update_Model(void);

	bool Toggle_Enable_Flag;
};

