/*
Copyright (c) 2021 Scene Builder and Equity -- Inflanite Software W.T.Flanigan H.C.Flanigan

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
class SB_Player
{
public:
	SB_Player();
	~SB_Player();

	void Reset_Class(void);

	void Create_Player_Object(void);

	bool Start_Player_PropsPanel();
	void Hide_Player_Dlg(bool Show);

	bool OnGround() const;

	void Adjust_Capsule(void);

	void Check_Collisions(void);
	void Check_Collisions_New(void);

	void Save_Location(char* name);
	void Goto_Location(int Index);

	int Col_numManifolds;
	int Col_Player_Index;
	int Col_Usage_Index;
	int Col_Object_Index;

	int Round;
	float Distance;
	int Life_Time;
	int Last_ColisionIndex;

	bool is_Animated;

	bool Toggle_Objects_Flag;
	bool Toggle_Physics_Flag;

	bool ShowDebug;
	bool Show_Physics_Debug; // Show Physics Debug For Player [021221]
	
	HWND Player_Props_HWND;

	// Strucure to be
	Ogre::Vector3 Current_Position;
	btVector3 Physics_Position;
	btQuaternion Physics_Rotation;

protected:

	static LRESULT CALLBACK Player_PropsPanel_Proc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);
	static LRESULT CALLBACK Locations_Proc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);

	void Start_Locations_Dlg();

	void Initialize();
	
};

