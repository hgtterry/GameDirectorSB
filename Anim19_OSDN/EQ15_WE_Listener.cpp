#include "stdafx.h"
#include "GD19_App.h"
#include "EQ15_WE_Listener.h"


EQ15_WE_Listener::EQ15_WE_Listener()
{
	mMoveScale = 0;
	mMoveSensitivity = 50;

	WE_Cam = nullptr;
}


EQ15_WE_Listener::~EQ15_WE_Listener()
{
}


// *************************************************************************
// *			WE_RenderingQueued   Terry Flanigan						   *
// *************************************************************************
bool EQ15_WE_Listener::WE_RenderingQueued(const FrameEvent& evt)
{
	Ogre::Radian Rotation_Speed;
	Rotation_Speed = 1 / (float)57.3;
	App->Cl_Vm_MeshDesign->MvNode->yaw(Rotation_Speed);
	
	ModelMode(evt.timeSinceLastFrame);
	return 1;
}

// *************************************************************************
// *							ModelMode   							   *
// *************************************************************************
void EQ15_WE_Listener::ModelMode(float DeltaTime)
{
	mRotX = 0;
	mRotY = 0;
	mTranslateVector = Ogre::Vector3::ZERO;

	mMoveScale = mMoveSensitivity  * DeltaTime;

	if (GetAsyncKeyState(69) < 0) // Q key Down in Fly Mode
	{
		Ogre::Real Rate;
		Rate = (mMoveSensitivity / 1000) * 2;    //0.1;//FlyRate;

		Ogre::Vector3 OldPos;
		OldPos = WE_Cam->getPosition();

		OldPos.y += Rate;
		WE_Cam->setPosition(OldPos);
	}
	//------------------------------------------------
	if (GetAsyncKeyState(81) < 0) // E key Up in Fly Mode
	{
		Ogre::Real Rate;
		Rate = (mMoveSensitivity / 1000) * 2;// 0.1;//FlyRate;

		Ogre::Vector3 OldPos;
		OldPos = WE_Cam->getPosition();

		OldPos.y -= Rate;
		WE_Cam->setPosition(OldPos);
	}
	//------------------------------------------------
	//if (Wheel < 0) // Mouse Wheel Forward
	//{
	//	mTranslateVector.z = -mMoveScale * 30;
	//}
	if (GetAsyncKeyState(87) < 0) // W Key
	{
		mTranslateVector.z = -mMoveScale;
	}
	//////------------------------------------------------
	////// back
	//if (Wheel > 0) // Mouse Wheel Back
	//{
	//	mTranslateVector.z = mMoveScale * 30;
	//}
	if (GetAsyncKeyState(83) < 0) // S Key	
	{
		mTranslateVector.z = mMoveScale;
	}
	//------------------------------------------------
	// Right
	if (GetAsyncKeyState(65) < 0)
	{
		mTranslateVector.x = mMoveScale;
	}
	// Left
	if (GetAsyncKeyState(68) < 0)
	{
		mTranslateVector.x = -mMoveScale;
	}

	if (GetAsyncKeyState(VK_ESCAPE) < 0) // Back to full Screen;
	{
		if (App->FullScreen == 1)
		{
			App->FullScreen = 0;
			App->Cl19_Ogre->ExitFullScreen();
		}
	}

	// Left Mouse
	//if (Pl_LeftMouseDown == 1 && Pl_RightMouseDown == 0)
	//{
	//	Capture_LeftMouse_Model();
	//}

	//// Right Mouse
	//if (Pl_LeftMouseDown == 0 && Pl_RightMouseDown == 1)
	//{
	//	Capture_RightMouse_World();
	//}

	MoveCamera();
}

// *************************************************************************
// *				moveCamera   Terry Bernie							   *
// *************************************************************************
void EQ15_WE_Listener::MoveCamera(void)
{
	WE_Cam->yaw(mRotX);
	WE_Cam->pitch(mRotY);
	WE_Cam->moveRelative(mTranslateVector); // Position Relative
	//Wheel = 0;
}