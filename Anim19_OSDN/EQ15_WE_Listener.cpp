#include "stdafx.h"
#include "GD19_App.h"
#include "EQ15_WE_Listener.h"


EQ15_WE_Listener::EQ15_WE_Listener()
{
	mMoveScale = 0;
	mMoveSensitivity = 50;
	Wheel = 0;

	Pl_DeltaMouse = 0;
	Pl_MouseX = 0;
	Pl_MouseY = 0;
	Pl_Cent500X = 500;
	Pl_Cent500Y = 500;

	mMoveSensitivityMouse = 50;

	Pl_LeftMouseDown = 0;
	Pl_RightMouseDown = 0;

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
	/*Ogre::Radian Rotation_Speed;
	Rotation_Speed = 1 / (float)57.3;
	App->Cl_Vm_MeshDesign->MvNode->yaw(Rotation_Speed);*/
	
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
		Rate = (mMoveSensitivity / 1000) * 4;    //0.1;//FlyRate;

		Ogre::Vector3 OldPos;
		OldPos = WE_Cam->getPosition();

		OldPos.y += Rate;
		WE_Cam->setPosition(OldPos);
	}
	//------------------------------------------------
	if (GetAsyncKeyState(81) < 0) // E key Up in Fly Mode
	{
		Ogre::Real Rate;
		Rate = (mMoveSensitivity / 1000) * 4;// 0.1;//FlyRate;

		Ogre::Vector3 OldPos;
		OldPos = WE_Cam->getPosition();

		OldPos.y -= Rate;
		WE_Cam->setPosition(OldPos);
	}
	//------------------------------------------------
	if (Wheel < 0) // Mouse Wheel Forward
	{
		mTranslateVector.z = -mMoveScale * 30;
	}
	if (GetAsyncKeyState(87) < 0) // W Key
	{
		mTranslateVector.z = -mMoveScale;
	}
	//------------------------------------------------
	// back
	if (Wheel > 0) // Mouse Wheel Back
	{
		mTranslateVector.z = mMoveScale * 30;
	}
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
	if (Pl_LeftMouseDown == 1 && Pl_RightMouseDown == 0)
	{
		Capture_LeftMouse_Model();
	}

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
	Wheel = 0;
}

// *************************************************************************
// *					Capture_LeftMouse_Model							   *
// *************************************************************************
bool EQ15_WE_Listener::Capture_LeftMouse_Model(void)
{
	GetCursorPos(&Pl_pt);

	Pl_MouseX = (int(Pl_pt.x));
	Pl_MouseY = (int(Pl_pt.y));

	//// Left Right
	if (Pl_MouseX < Pl_Cent500X)
	{
		long test = Pl_Cent500X - Pl_MouseX; // Positive

		if (test > 2)
		{
			Pl_DeltaMouse = float(Pl_Cent500X - Pl_MouseX);
			App->Cl_Vm_MeshDesign->GridNode->yaw(Ogre::Degree(-Pl_DeltaMouse * (mMoveSensitivityMouse / 1000) * 2), Ogre::Node::TS_LOCAL);
			App->Cl_Vm_MeshDesign->HairNode->yaw(Ogre::Degree(-Pl_DeltaMouse * (mMoveSensitivityMouse / 1000) * 2), Ogre::Node::TS_LOCAL);
			App->Cl_Vm_MeshDesign->RenderListener->RZ = App->Cl_Vm_MeshDesign->RenderListener->RZ - (Pl_DeltaMouse * (mMoveSensitivityMouse / 1000) * 2);
			SetCursorPos(500, 500);
		}
	}
	else if (Pl_MouseX > Pl_Cent500X)
	{
		long test = Pl_MouseX - Pl_Cent500X; // Positive

		if (test > 2)
		{
			Pl_DeltaMouse = float(Pl_MouseX - Pl_Cent500X);
			App->Cl_Vm_MeshDesign->GridNode->yaw(Ogre::Degree(Pl_DeltaMouse * (mMoveSensitivityMouse / 1000) * 2), Ogre::Node::TS_LOCAL);
			App->Cl_Vm_MeshDesign->HairNode->yaw(Ogre::Degree(Pl_DeltaMouse * (mMoveSensitivityMouse / 1000) * 2), Ogre::Node::TS_LOCAL);
			App->Cl_Vm_MeshDesign->RenderListener->RZ = App->Cl_Vm_MeshDesign->RenderListener->RZ + (Pl_DeltaMouse * (mMoveSensitivityMouse / 1000) * 2);
			SetCursorPos(500, 500);
		}
	}

	// Up Down
	if (Pl_MouseY < Pl_Cent500Y)
	{
		long test = Pl_Cent500Y - Pl_MouseY; // Positive

		if (test > 2)
		{
			Pl_DeltaMouse = float(Pl_Cent500Y - Pl_MouseY);
			App->Cl_Vm_MeshDesign->GridNode->pitch(Ogre::Degree(-Pl_DeltaMouse * (mMoveSensitivityMouse / 1000) * 2), Ogre::Node::TS_PARENT);
			App->Cl_Vm_MeshDesign->HairNode->pitch(Ogre::Degree(-Pl_DeltaMouse * (mMoveSensitivityMouse / 1000) * 2), Ogre::Node::TS_PARENT);
			App->Cl_Vm_MeshDesign->RenderListener->RX = App->Cl_Vm_MeshDesign->RenderListener->RX - (Pl_DeltaMouse * (mMoveSensitivityMouse / 1000) * 2);
			SetCursorPos(500, 500);
		}
	}
	else if (Pl_MouseY > Pl_Cent500Y)
	{
		long test = Pl_MouseY - Pl_Cent500Y; // Positive

		if (test > 2)
		{
			Pl_DeltaMouse = float(Pl_MouseY - Pl_Cent500Y);
			App->Cl_Vm_MeshDesign->GridNode->pitch(Ogre::Degree(Pl_DeltaMouse * (mMoveSensitivityMouse / 1000) * 2), Ogre::Node::TS_PARENT);
			App->Cl_Vm_MeshDesign->HairNode->pitch(Ogre::Degree(Pl_DeltaMouse * (mMoveSensitivityMouse / 1000) * 2), Ogre::Node::TS_PARENT);
			App->Cl_Vm_MeshDesign->RenderListener->RX = App->Cl_Vm_MeshDesign->RenderListener->RX + (Pl_DeltaMouse * (mMoveSensitivityMouse / 1000) * 2);
			SetCursorPos(500, 500);
		}
	}

	return 1;
}