/*
Copyright (c) 2023 World Editor -- HGT Software W.T.Flanigan H.C.Flanigan

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

#include "stdafx.h"
#include "AB_App.h"
#include "SB_Panels.h"

SB_Panels::SB_Panels()
{
}

SB_Panels::~SB_Panels()
{
}

// *************************************************************************
// *	  	Centre_QC_Dialog:- Terry and Hazel Flanigan 2023			   *
// *************************************************************************
void SB_Panels::Centre_QC_Dialog()
{
	RECT rcl;

	GetClientRect(App->MainHwnd, &rcl);
	int MX = rcl.right/2;
	int MY = rcl.bottom;
	int Top = rcl.top;

	GetClientRect(App->CLSB_TopTabs->Top_Tabs_Hwnd, &rcl);
	int PX = rcl.right/2;
	int PY = rcl.bottom;


	SetWindowPos(App->CLSB_TopTabs->Top_Tabs_Hwnd, NULL, (MX-PX), Top + 100,
		0, 0, SWP_NOSIZE | SWP_NOZORDER);
}
