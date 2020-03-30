/*
Copyright (c) GameDirector 2019 Inflanite Software W.T.Flanigan H.C.Flanigan B.Parkin

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

#include "Ogre.h"
#include "OgreOverlay.h"
#include "OgreOverlayManager.h"
#include "OgreRenderWindow.h"

#include "CollisionTools.h"
#include "CustomTypes.h"

using namespace Ogre;

class GD19_OgreListener : public FrameListener
{
public:
	GD19_OgreListener(void);
	~GD19_OgreListener(void);

	bool frameStarted(const FrameEvent& evt);
	bool frameEnded(const FrameEvent& evt);
	bool frameRenderingQueued(const FrameEvent& evt);

	void worldMode(float DeltaTime);

	void MoveCamera(void);
	bool Capture_Mouse_Free(void);
	bool Capture_RightMouse(void);
	bool Capture_Mouse_FirstPerson(void);
	bool Capture_LeftMouse(void);

	bool SelectEntity(void);

	Ogre::Camera* mCam;
	Ogre::Camera* Pl_mDummyCamera;
	Vector3		Pl_mDummyTranslateVector;

	Ogre::Overlay*	mNameOverlay;

	Radian		mRotX;
	Radian		mRotY;
	Vector3		mTranslateVector;
	int			Wheel;
	double		toggleTimer;

	float		mMoveScale;
	float		mMoveSensitivity;
	float		mMoveSensitivityMouse;

	float		AnimationScale;

	int Pl_MouseX;
	int Pl_MouseY;

	POINT		Pl_pt;
	long		Pl_Cent500X;
	long		Pl_Cent500Y;

	float		Pl_DeltaMouse;

	bool		Pl_LeftMouseDown;
	bool		Pl_RightMouseDown;

	bool	GD_Run_Physics;
	bool	GD_Dubug_Physics;
	bool	GD_MeshViewer_Running;
	float	GD_SpinRate;
	bool	GD_Selection_Mode;
	bool	Show_ImGui_Panels;
	int		GD_CameraMode;

	int		View_Height;
	int		View_Width;


	int	Selected_Entity_Index;
	Ogre::String Pl_Entity_Name;

	Ogre::AnimationState*   Animate_State; // needs init
	Ogre::AnimationState*   Animate_State2;

	bool Animate_Ogre;
	bool ShowFPS;
	bool StopOgre;
	bool FollowPlayer;
	int Object_ToFollow;

	MOC::CollisionTools* mCollisionTools;

	btScalar   _desiredVelocity;

	bool CameraMode;

};

