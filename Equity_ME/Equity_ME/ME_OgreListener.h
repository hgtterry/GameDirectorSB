/*
Copyright (c) 2022 Equity_ME Model Editor -- Inflanite Software W.T.Flanigan H.C.Flanigan

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

class ME_OgreListener : public Ogre::FrameListener
{
public:
	ME_OgreListener();
	~ME_OgreListener();

	bool frameStarted(const Ogre::FrameEvent& evt);
	bool frameEnded(const Ogre::FrameEvent& evt);
	bool frameRenderingQueued(const Ogre::FrameEvent& evt);

	bool Stop_Ogre;  // Stop the Ogre Engine [150122]

	int		View_Height;	// Ogre window Height [150122]
	int		View_Width;		// Ogre window WIdth [150122]

protected:

	void Model_Mode(float DeltaTime);
	void MoveCamera(void);
	bool Capture_LeftMouse_Model(void);
	bool Capture_RightMouse_Model(void);

	Ogre::Camera* mCam; // Copy Ogre Main Camera Handle [280122]

	Ogre::Radian		mRotX; // Camera Rotation X [280122]
	Ogre::Radian		mRotY; // Camera Rotation Y [280122]
	Ogre::Vector3		mTranslateVector; // Camera Rotation XYZ[280122]

	float mMoveSensitivity;
	float mMoveScale;

	int Pl_MouseX;
	int Pl_MouseY;

	POINT		Pl_pt;
	long		Pl_Cent500X;
	long		Pl_Cent500Y;

	float		mMoveSensitivityMouse;
	float		Pl_DeltaMouse;
	bool		Pl_LeftMouseDown;
	bool		Pl_RightMouseDown;
	

	int	Wheel;
};

