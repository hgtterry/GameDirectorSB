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

#include "Ogre.h"

#pragma once
class SB_MeshView_Listener : public FrameListener
{
public:
	SB_MeshView_Listener();
	~SB_MeshView_Listener();

	bool frameRenderingQueued(const FrameEvent& evt);
	bool frameStarted(const FrameEvent& evt); // Comes From Directly From Oger Render Listener [081221]

	int		Wheel_Move;
	bool	Pl_LeftMouseDown;	// Triger Left Mouse Presed [081221]
	bool	Pl_RightMouseDown;	// Triger Right Mouse Presed [081221]

	bool	Show_Model_Data; // Show Model Data ImGui [081221]

	int		View_Height;	// Height of Render Window [081221]
	int		View_Width;		// Width of Render Window [081221]

	float		mMoveSensitivity;
	float		mMoveSensitivityMouse;

	Ogre::Camera* WE_Cam;

protected:

	void ModelMode(float DeltaTime);
	void MoveCamera(void);

	bool Capture_LeftMouse_Model(void);
	bool Capture_RightMouse_Model(void);

	Radian		mRotX;
	Radian		mRotY;
	Vector3		mTranslateVector;

	float		mMoveScale;


	float		Pl_DeltaMouse;
	int			Pl_MouseX;
	int			Pl_MouseY;

	POINT		Pl_pt;
	long		Pl_Cent500X;
	long		Pl_Cent500Y;
};

