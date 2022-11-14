/*	
	Copyright (c) 2009 - 2013 W.T.Flanigan Bernard Parkin and H.C.Flanigan

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
#include "OgreStringConverter.h"
#include "OgreException.h"

#include <OgreRenderWindow.h>

#include "CollisionTools.h"
#include "CustomTypes.h"

using namespace Ogre;
//using namespace OgreBites;

class BT_PhysicsListener : public FrameListener, public WindowEventListener
{
public:
	BT_PhysicsListener(Camera* cam,Terrain * terrain);
	~BT_PhysicsListener(void);

	Ogre::Overlay*	mDebugOverlay;
	Ogre::Overlay*	mNameOverlay;
	//MOC::CollisionTools* mCollisionTools;
	bool frameStarted(const FrameEvent& evt);
	bool frameEnded(const FrameEvent& evt);
	bool frameRenderingQueued(const FrameEvent& evt);

	void MoveCamera(void);

	bool Capture_RightMouse(void);
	bool Capture_LeftMouse(void);
	bool Capture_Mouse_FirstPerson(void);

	bool Capture_Mouse_Free(void);

	void showDebugOverlay(bool show);
	
	bool Update_Game_Logic(float DeltaTime);

	int	Selected_Entity_Index;

	Ogre::Camera* mCam;
	Ogre::Camera* Pl_mDummyCamera;
	Vector3		Pl_mDummyTranslateVector;

	Radian		mRotX;
	Radian		mRotY;
	Vector3		mTranslateVector;
	float		mMoveScale;
	float		mMoveSensitivity;
	float		mMoveSensitivityMouse;
	Vector3		mCam_mTranslateVector;

	POINT		Pl_pt;
	long		Pl_Cent500X;
	long		Pl_Cent500Y;

	float		Mouse_X;

	double		toggleTimer;
	float		ProjectionMove;
	float		Delta;
	bool		DoProjectionMove;
	bool		ProjectionDirection;
	bool		Block_RenderingQueued;
	float		Pl_DeltaMouse;
	bool		Pl_LeftMouseDown;
	bool		Pl_RightMouseDown;

	int			Wheel;

	int Pl_MouseX;
	int Pl_MouseY;

	bool	GD_Selection_Mode;
	bool	GD_Run_Physics;
	bool	GD_MeshViewer_Running;
	bool	GD_Dubug_Physics;
	float	GD_SpinRate;
	int		GD_CameraMode;


	bool StopOgre;
	bool Debug_FPS;

	bool Gen_Test;

	// Ogre Animation
	bool Animate_Ogre_KeyFrame;
	bool Animate_Ogre;

	Ogre::AnimationState*   Animate_State;
	Ogre::AnimationState*   Animate_State2;
	float AnimationScale;
	float KeyFrame_Speed;

	int		View_Height;
	int		View_Width;
	//MOC::CollisionTools* mCollisionTools;

};
