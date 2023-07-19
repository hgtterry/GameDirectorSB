/*
Copyright (c) 2022 EquitySB Inflanite Software W.T.Flanigan H.C.Flanigan

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
class SB_Dimensions
{

public:
	SB_Dimensions();
	~SB_Dimensions();

	void ImGui_Dimensions(void);
	void UpDate_Physics_And_Visuals(int Index);
	void Dimesions_Select(void);

	bool Show_Dimensions;

	bool Show_Position;
	bool Show_Scale;
	bool Show_Rotation;

	void ImGui_Position_Area(void);
	void ImGui_Rotation_Area(void);
	void ImGui_Scale_Area(void);

protected:

	void ImGui_Position(void);
	void Set_Position(float X, float Y, float Z);

	void ImGui_Scale(void);
	void Set_Scale(bool Mode, float X, float Y, float Z);

	void ImGui_Rotation(void);

	void Set_Physics_Position(int Index);

	bool PosX_Selected;
	bool PosY_Selected;
	bool PosZ_Selected;

	bool ScaleX_Selected;
	bool ScaleY_Selected;
	bool ScaleZ_Selected;

	bool RotationX_Selected;
	bool RotationY_Selected;
	bool RotationZ_Selected;

	bool Scale_Lock;

	float Model_Pos_Delta;
	float Model_Scale_Delta;
	float Model_Rotation_Delta;
};

