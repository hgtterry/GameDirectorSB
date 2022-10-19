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

:- Terry and Hazel Flanigan 2022

*/

#include "stdafx.h"
#include "GD19_App.h"
#include "SB_MeshView_Listener.h"

SB_MeshView_Listener::SB_MeshView_Listener()
{
	mMoveScale = 0;
	mMoveSensitivity = 50;
	Wheel_Move = 0;

	Show_Model_Data = 0;

	Pl_DeltaMouse = 0;
	Pl_MouseX = 0;
	Pl_MouseY = 0;
	Pl_Cent500X = 500;
	Pl_Cent500Y = 500;

	mMoveSensitivityMouse = 50;

	Pl_LeftMouseDown = 0;
	Pl_RightMouseDown = 0;

	WE_Cam = nullptr;

	View_Height = 0;
	View_Width = 0;

	WE_Cam = App->SBC_MeshViewer->mCameraMeshView;
}

SB_MeshView_Listener::~SB_MeshView_Listener()
{
}

// *************************************************************************
// *				frameStarted   Terry Bernie							   *
// *************************************************************************
bool SB_MeshView_Listener::frameStarted(const FrameEvent& evt)
{
	//FlashWindow(App->SBC_MeshViewer->MainDlgHwnd, true);
	/*if (App->Cl19_Ogre->OgreListener->Equity_Running == 1)
	{
		if (App->SBC_Equity->Use_Imgui == 1)
		{
			App->SBC_Equity->Get_View_Height_Width();
			App->SBC_Equity->EB_imgui.NewFrame(evt.timeSinceLastFrame, (float)View_Width, (float)View_Height);

			if (App->SBC_Equity->Show_Gui_Debug == 1)
			{
				Render_ImGui();
			}

		}

		return true;
	}*/

	return true;
}


// *************************************************************************
// *			frameRenderingQueued   Terry Bernie						   *
// *************************************************************************
bool SB_MeshView_Listener::frameRenderingQueued(const FrameEvent& evt)
{
	ModelMode(evt.timeSinceLastFrame);
	return 1;
}


// *************************************************************************
// *							ModelMode   							   *
// *************************************************************************
void SB_MeshView_Listener::ModelMode(float DeltaTime)
{
	mRotX = 0;
	mRotY = 0;
	mTranslateVector = Ogre::Vector3::ZERO;

	mMoveScale = mMoveSensitivity * DeltaTime;

	//if (GetAsyncKeyState(69) < 0) // Q key Down in Fly Mode
	//{
	//	Ogre::Real Rate;
	//	Rate = (mMoveSensitivity / 1000) * 4;    //0.1;//FlyRate;

	//	Ogre::Vector3 OldPos;
	//	OldPos = WE_Cam->getPosition();

	//	OldPos.y += Rate;
	//	WE_Cam->setPosition(OldPos);
	//}
	////------------------------------------------------
	//if (GetAsyncKeyState(81) < 0) // E key Up in Fly Mode
	//{
	//	Ogre::Real Rate;
	//	Rate = (mMoveSensitivity / 1000) * 4;// 0.1;//FlyRate;

	//	Ogre::Vector3 OldPos;
	//	OldPos = WE_Cam->getPosition();

	//	OldPos.y -= Rate;
	//	WE_Cam->setPosition(OldPos);
	//}
	////------------------------------------------------
	if (Wheel_Move < 0) // Mouse Wheel Forward
	{
		mTranslateVector.z = -mMoveScale * 30;
	}
	//if (GetAsyncKeyState(87) < 0) // W Key
	//{
	//	mTranslateVector.z = -mMoveScale;
	//}
	////------------------------------------------------
	//// back
	if (Wheel_Move > 0) // Mouse Wheel Back
	{
		mTranslateVector.z = mMoveScale * 30;
	}
	//if (GetAsyncKeyState(83) < 0) // S Key	
	//{
	//	mTranslateVector.z = mMoveScale;
	//}
	////------------------------------------------------
	//// Right
	//if (GetAsyncKeyState(65) < 0)
	//{
	//	mTranslateVector.x = mMoveScale;
	//}
	//// Left
	//if (GetAsyncKeyState(68) < 0)
	//{
	//	mTranslateVector.x = -mMoveScale;
	//}

	//if (GetAsyncKeyState(VK_ESCAPE) < 0) // Back to full Screen;
	//{
	//	if (App->FullScreen == 1)
	//	{
	//		App->FullScreen = 0;
	//		App->Cl19_Ogre->ExitFullScreen();
	//	}
	//}

	// Left Mouse
	if (Pl_LeftMouseDown == 1 && Pl_RightMouseDown == 0)
	{
		Capture_LeftMouse_Model();
	}

	// Right Mouse
	if (Pl_LeftMouseDown == 0 && Pl_RightMouseDown == 1)
	{
		Capture_RightMouse_Model();
	}

	MoveCamera();
}

// *************************************************************************
// *				moveCamera   Terry Bernie							   *
// *************************************************************************
void SB_MeshView_Listener::MoveCamera(void)
{
	WE_Cam->yaw(mRotX);
	WE_Cam->pitch(mRotY);
	WE_Cam->moveRelative(mTranslateVector); // Position Relative
	Wheel_Move = 0;
}

// *************************************************************************
// *					Capture_LeftMouse_Model							   *
// *************************************************************************
bool SB_MeshView_Listener::Capture_LeftMouse_Model(void)
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
			App->SBC_MeshViewer->GridNode->yaw(Ogre::Degree(-Pl_DeltaMouse * (mMoveSensitivityMouse / 1000) * 2), Ogre::Node::TS_LOCAL);
			App->SBC_MeshViewer->MvNode->yaw(Ogre::Degree(-Pl_DeltaMouse * (mMoveSensitivityMouse / 1000) * 2), Ogre::Node::TS_LOCAL);
			SetCursorPos(500, 500);
		}
	}
	else if (Pl_MouseX > Pl_Cent500X)
	{
		long test = Pl_MouseX - Pl_Cent500X; // Positive

		if (test > 2)
		{
			Pl_DeltaMouse = float(Pl_MouseX - Pl_Cent500X);
			App->SBC_MeshViewer->GridNode->yaw(Ogre::Degree(Pl_DeltaMouse * (mMoveSensitivityMouse / 1000) * 2), Ogre::Node::TS_LOCAL);
			App->SBC_MeshViewer->MvNode->yaw(Ogre::Degree(Pl_DeltaMouse * (mMoveSensitivityMouse / 1000) * 2), Ogre::Node::TS_LOCAL);

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
			App->SBC_MeshViewer->GridNode->pitch(Ogre::Degree(-Pl_DeltaMouse * (mMoveSensitivityMouse / 1000) * 2), Ogre::Node::TS_PARENT);
			App->SBC_MeshViewer->MvNode->pitch(Ogre::Degree(-Pl_DeltaMouse * (mMoveSensitivityMouse / 1000) * 2), Ogre::Node::TS_PARENT);
			SetCursorPos(500, 500);
		}
	}
	else if (Pl_MouseY > Pl_Cent500Y)
	{
		long test = Pl_MouseY - Pl_Cent500Y; // Positive

		if (test > 2)
		{
			Pl_DeltaMouse = float(Pl_MouseY - Pl_Cent500Y);
			App->SBC_MeshViewer->GridNode->pitch(Ogre::Degree(Pl_DeltaMouse * (mMoveSensitivityMouse / 1000) * 2), Ogre::Node::TS_PARENT);
			App->SBC_MeshViewer->MvNode->pitch(Ogre::Degree(Pl_DeltaMouse * (mMoveSensitivityMouse / 1000) * 2), Ogre::Node::TS_PARENT);
			SetCursorPos(500, 500);
		}
	}

	return 1;
}

// *************************************************************************
// *					Capture_RightMouse_Model Terry					   *
// *************************************************************************
bool SB_MeshView_Listener::Capture_RightMouse_Model(void)
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
			mTranslateVector.x = Pl_DeltaMouse * (mMoveSensitivityMouse / 1000);
			SetCursorPos(500, 500);
		}
	}
	else if (Pl_MouseX > Pl_Cent500X)
	{
		long test = Pl_MouseX - Pl_Cent500X; // Positive

		if (test > 2)
		{
			Pl_DeltaMouse = float(Pl_MouseX - Pl_Cent500X);
			mTranslateVector.x = -Pl_DeltaMouse * (mMoveSensitivityMouse / 1000);
			SetCursorPos(500, 500);
		}
	}

	//// Up Down
	if (Pl_MouseY < Pl_Cent500Y)
	{
		long test = Pl_Cent500Y - Pl_MouseY; // Positive

		if (test > 2)
		{
			Pl_DeltaMouse = float(Pl_Cent500Y - Pl_MouseY);

			Ogre::Real Rate;
			Rate = Pl_DeltaMouse * (mMoveSensitivityMouse / 1000);

			Ogre::Vector3 OldPos;
			OldPos = WE_Cam->getPosition();

			OldPos.y -= Rate;
			WE_Cam->setPosition(OldPos);
			SetCursorPos(500, 500);
		}

	}
	else if (Pl_MouseY > Pl_Cent500Y)
	{
		long test = Pl_MouseY - Pl_Cent500Y; // Positive

		if (test > 2)
		{
			Pl_DeltaMouse = float(Pl_MouseY - Pl_Cent500Y);

			Ogre::Real Rate;
			Rate = Pl_DeltaMouse * (mMoveSensitivityMouse / 1000);

			Ogre::Vector3 OldPos;
			OldPos = WE_Cam->getPosition();

			OldPos.y += Rate;
			WE_Cam->setPosition(OldPos);
			SetCursorPos(500, 500);
		}

	}

	return 1;
}
