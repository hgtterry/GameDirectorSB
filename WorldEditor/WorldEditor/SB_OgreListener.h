/*
Copyright (c) World_Viewer 2023 Inflanite Software W.T.Flanigan H.C.Flanigan

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

//using namespace Ogre;

class SB_OgreListener : public FrameListener
{
public:
	SB_OgreListener(void);
	~SB_OgreListener(void);

	void Reset_Class(void);
	bool frameStarted(const FrameEvent& evt);
	bool frameEnded(const FrameEvent& evt);
	bool frameRenderingQueued(const FrameEvent& evt);

	bool Update_Game_Logic(float DeltaTime);

	void WorldMode(float DeltaTime);

	void Camera_Mode_Model(float DeltaTime);
	void Camera_Mode_Free(float DeltaTime);

	void MoveCamera(void);


	bool Capture_RightMouse_Model(void);


	// -------- Good
	bool Capture_Left_Mouse_Free(void);
	bool Capture_Right_Mouse_Free(void);
	// --------------------------------



	bool Capture_Mouse_FirstPerson(float DeltaTime);

	bool Capture_LeftMouse_World(void);
	bool Capture_LeftMouse_Model(void);

	bool Capture_LeftMouse(void);

	Ogre::Camera* mCam;
	Ogre::Camera* Pl_mDummyCamera;
	Vector3		Pl_mDummyTranslateVector;

	Radian		mRotX;
	Radian		mRotY;
	Vector3		mTranslateVector;
	int			Wheel;
	double		toggleTimer;

	float		mMoveScale;
	float		mMoveSensitivity;
	float		mMoveSensitivityMouse;

	float		AnimationScale;
	float		OgreFrameTime;

	int Pl_MouseX;
	int Pl_MouseY;

	bool		Block_Mouse;

	POINT		Pl_pt;
	long		Pl_Cent500X;
	long		Pl_Cent500Y;

	float		Pl_DeltaMouse;

	bool		Pl_LeftMouseDown;
	bool		Pl_RightMouseDown;

	bool	GD_Run_Physics;
	bool	Dubug_Physics_Draw; // Draw Physics Debug Global Flag [211121]
	bool	Equity_Running;		// Equity Editor Running [191221]
	bool	MeshViewer_Running;	// Mesh Viewer Running [191221]
	bool	Show_DemoWindow;

	float	GD_SpinRate;
	bool	GD_Selection_Mode;
	bool	Show_ImGui_Panels;
	int		GD_CameraMode;

	int		View_Height;
	int		View_Width;

	int		ImGui_Render_Tab;

	int Bullet_Step;

	int	Selected_Entity_Index;
	Ogre::String Pl_Entity_Name;
	char Selected_Object_Name[MAX_PATH];
	float DistanceToCollision;

	Ogre::AnimationState*   Animate_State; // needs init
	Ogre::AnimationState*   Animate_State2;

	bool Animate_Ogre;
	bool ShowFPS;
	bool StopOgre;
	int Object_ToFollow;

	MOC::CollisionTools* mCollisionTools;

	//btScalar   _desiredVelocity;

	int CameraMode;

	CMainFrame* m_pMainFrame;
	CFusionDoc* m_pDoc;
};

