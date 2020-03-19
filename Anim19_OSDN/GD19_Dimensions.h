/*
	Copyright (c) GD10 (GameDirector) 2019 Inflanite Software W.T.Flanigan B.Parkin H.C.Flanigan

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
class GD19_Dimensions
{
public:

	GD19_Dimensions(void);
	~GD19_Dimensions(void);

	bool Start_Postion();
	bool Start_Rotation_Dlg();
	bool Start_Scale_Dlg();

	void DecodeMovment(void);

	void Set_Physics_Position(int Index);

	void UpDate_Physics_And_Visuals(int Index);

	int Mouse_Move_Mode;

	float PosStep;

	bool Set_ScaleLock;

	int MouseXE;
	int MouseYE;

	int OldMXE;
	int OldMYE;

	float Pl_CenterX;
	float Pl_CenterY;

	float Model_XRotate;
	float Model_YRotate;
	float Model_ZRotate;

	float Model_XTranslate;
	float Model_YTranslate;
	float Model_ZTranslate;

	float DeltaMouse;

	HWND PositionDlg_Hwnd;
	HWND RotationDlg_Hwnd;
	HWND ScaleDlg_Hwnd;

protected:

	static LRESULT CALLBACK Postion_Proc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);
	static LRESULT CALLBACK Rotation_Proc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);
	static LRESULT CALLBACK Scale_Proc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);
	static LRESULT CALLBACK More_Rotation_Proc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);


	void SetTransStepsOptions(HWND hDlg);
	void SetRotationStepsOptions(HWND hDlg);

	void Select_Properties_Update(void);

	void ScaleLock(HWND hDlg);

	bool ScaleObject(Ogre::Vector3 Direction);
	bool MoveObject(Ogre::Vector3 Direction);

	float Last_Xpos;
	float Last_Ypos;
	float Last_Zpos;

	float Last_XScale;
	float Last_YScale;
	float Last_ZScale;

	float Last_XRotation;
	float Last_YRotation;
	float Last_ZRotation;

	Ogre::Quaternion Last_Rotation;

	bool Use_Mouse; // Use Mouse to Scale Position and Rotate Mesh_X;
	bool Use_Mouse_X;
	bool Use_Mouse_Y;
	bool Use_Mouse_Z;

	int Object_Index;
	int Dimensions_Mode;


	float Model_XScale;
	float Model_YScale;
	float Model_ZScale;

	bool LockAxis;

	bool Position_Dlg_Active;
	bool Rotation_Dlg_Active;
	bool Scale_Dlg_Active;

	POINT MousePoint;
};

