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

#include "stdafx.h"
#include "AB_App.h"
#include "SB_OgreListener.h"



SB_OgreListener::SB_OgreListener(void)
{
	mCam = App->CLSB_Ogre->mCamera;
	Pl_mDummyCamera = App->CLSB_Ogre->mSceneMgr->createCamera("PickCamera");
	
	Wheel = 0;
	StopOgre = 0;
	ShowFPS = 1;
	Show_DemoWindow = 0;
	
	GD_CameraMode = 10;// Enums::CamModel;

	Pl_mDummyTranslateVector = Ogre::Vector3::ZERO;

	mMoveScale = 0;
	mMoveSensitivity = 50;
	mMoveSensitivityMouse = 50;

	Block_Mouse = 0;

	Pl_LeftMouseDown = 0;
	Pl_RightMouseDown = 0;

	Pl_DeltaMouse = 0;
	Pl_MouseX = 0;
	Pl_MouseY = 0;

	Pl_Cent500X = App->CursorPosX;
	Pl_Cent500Y = App->CursorPosY;

	Bullet_Step = 2;

	GD_Run_Physics = 0;
	Dubug_Physics_Draw = 0;
	Dubug_Physics_DrawAll = 0;

	Equity_Running = 0;
	MeshViewer_Running = 0;

	GD_SpinRate = 1;
	GD_Selection_Mode = 0;

	Object_ToFollow = 1;

	OgreFrameTime = 0;

	Show_ImGui_Panels = 1;

	View_Height = 0;
	View_Width = 0;

	Selected_Entity_Index = 0;

	toggleTimer = 0.01;

	Animate_Ogre = 0;
	AnimationScale = 1;
	
	mCollisionTools = new MOC::CollisionTools(App->CLSB_Ogre->mSceneMgr);
	mCollisionTools->setHeightAdjust(3.5f);
	DistanceToCollision = 0;

	CameraMode = Enums::CamModel;// CamDetached; // 2

	m_pDoc = NULL;
	m_pMainFrame = NULL;
}

SB_OgreListener::~SB_OgreListener(void)
{
	
}

// *************************************************************************
// *			Reset_Class:- Terry and Hazel Flanigan 2023				   *
// *************************************************************************
void SB_OgreListener::Reset_Class(void)
{
	Animate_Ogre = 0;
	CameraMode = 2;  // Model Mode
}

// *************************************************************************
// *			frameStarted:- Terry and Hazel Flanigan 2023			   *
// *************************************************************************
bool SB_OgreListener::frameStarted(const FrameEvent& evt)
{
	Update_Game_Logic(evt.timeSinceLastFrame);
	return true;
}

// *************************************************************************
// *		frameRenderingQueued:- Terry and Hazel Flanigan 2023		   *
// *************************************************************************
bool SB_OgreListener::frameRenderingQueued(const FrameEvent& evt)
{
	
	OgreFrameTime = evt.timeSinceLastFrame;

	App->CLSB_Ogre->m_imgui.render();
	
	/*if (App->CL_Ogre->Block_RenderingQueued == 1)
	{
		return 1;
	}

	App->CL_Ogre->Block_RenderingQueued = 1;*/


	if (App->CLSB_Equity->EquitySB_Dialog_Visible == 0)
	{
		App->CLSB_Keyboard->Keyboard_Mode_WorldEditor(evt.timeSinceLastFrame);
		return 1;
	}
	
	if (CameraMode == Enums::CamFirst)
	{

		mRotX = 0;
		mRotY = 0;
		mTranslateVector = Ogre::Vector3::ZERO;

		mMoveScale = mMoveSensitivity * evt.timeSinceLastFrame;

		Ogre::Vector3 Pos;
		Ogre::Radian mmPitch;
		Ogre::Radian mYaw;

		Pos = App->CLSB_Scene->B_Player[0]->Player_Node->getPosition();

		mmPitch = App->CLSB_Scene->B_Player[0]->CameraPitch->getOrientation().getPitch();
		mYaw = App->CLSB_Scene->B_Player[0]->Player_Node->getOrientation().getYaw();
		Pos.y = Pos.y + App->CLSB_Scene->B_Player[0]->PlayerHeight;

		App->CLSB_Ogre->mCamera->setPosition(Pos);
		App->CLSB_Ogre->mCamera->setOrientation(Ogre::Quaternion(1, 0, 0, 0));
		App->CLSB_Ogre->mCamera->yaw(mYaw);
		App->CLSB_Ogre->mCamera->pitch(mmPitch);
		App->CLSB_Ogre->mCamera->yaw(Ogre::Degree(180));


		App->CLSB_Keyboard->Keyboard_Mode_First(evt.timeSinceLastFrame);

		if (Pl_LeftMouseDown == 1 && Pl_RightMouseDown == 0)
		{
			Capture_Mouse_FirstPerson(evt.timeSinceLastFrame);
			SetCursorPos(App->CursorPosX, App->CursorPosY);
		}

		App->CLSB_Player->updateAction(NULL, evt.timeSinceLastFrame);

		MoveCamera();
		//App->Flash_Window();
		//App->CL_Ogre->Block_RenderingQueued = 0;
		return 1;
	}


	if (CameraMode == Enums::CamModel)
	{
		Camera_Mode_Model(evt.timeSinceLastFrame);

		//App->CL_Ogre->Block_RenderingQueued = 0;
		return 1;
	}

	if (CameraMode == Enums::CamDetached)
	{
		Camera_Mode_Free(evt.timeSinceLastFrame);

		//App->CL_Ogre->Block_RenderingQueued = 0;
		return 1;
	}

	/*if (CameraMode == 3)
	{
		Capture_Mouse_FirstPerson(evt.timeSinceLastFrame);
		return 1;
	}*/


	//OgreFrameTime = evt.timeSinceLastFrame;

	
	return 1;
}

// *************************************************************************
// *			frameEnded:- Terry and Hazel Flanigan 2023				   *
// *************************************************************************
bool SB_OgreListener::frameEnded(const FrameEvent& evt)
{
	if (StopOgre == 1)
	{
		return false;
	}


	m_pMainFrame = (CMainFrame*)AfxGetMainWnd(); // MFC POO
	char info[256];
	m_pDoc = (CFusionDoc*)m_pMainFrame->GetCurrentDoc();
	m_pDoc->GetCursorInfo(info, 255);

	return true;
}

// *************************************************************************
// *		Camera_Mode_Free:- Terry and Hazel Flanigan 2023   			   *
// *************************************************************************
void SB_OgreListener::Camera_Mode_Free(float DeltaTime)
{
	//App->CL_Ogre->m_imgui.render();

	mRotX = 0;
	mRotY = 0;
	mTranslateVector = Ogre::Vector3::ZERO;

	mMoveScale = mMoveSensitivity * DeltaTime;

	App->CLSB_Keyboard->Keyboard_Mode_Free(DeltaTime);

	if (Pl_LeftMouseDown == 1 && Pl_RightMouseDown == 0)
	{
		Capture_Left_Mouse_Free();
		SetCursorPos(App->CursorPosX, App->CursorPosY);
	}

	// Right Mouse
	if (Pl_LeftMouseDown == 0 && Pl_RightMouseDown == 1)
	{
		Capture_Right_Mouse_Free();
	}
	

	MoveCamera();
}

// *************************************************************************
// *				Capture_Left_Mouse_Free   Terry Bernie				   *
// *************************************************************************
bool SB_OgreListener::Capture_Left_Mouse_Free(void)
{
	//if (!ImGui::GetIO().WantCaptureMouse)
	//{
	GetCursorPos(&Pl_pt);
	Pl_MouseX = (int(Pl_pt.x));
	Pl_MouseY = (int(Pl_pt.y));

	// Left Right
	if (Pl_MouseX < Pl_Cent500X)
	{
		long test = Pl_Cent500X - Pl_MouseX; // Positive
		if (test > 2)
		{
			Pl_DeltaMouse = float(Pl_Cent500X - Pl_MouseX);
			mRotX = Degree(Pl_DeltaMouse * (float)0.03);//S_Player[0]->TurnRate);
		}
	}
	else if (Pl_MouseX > Pl_Cent500X)
	{
		long test = Pl_MouseX - Pl_Cent500X; // Positive

		if (test > 2)
		{
			Pl_DeltaMouse = float(Pl_MouseX - Pl_Cent500X);
			mRotX = Degree(-Pl_DeltaMouse * (float)0.03);//S_Player[0]->TurnRate);
		}
	}

	// Up Down
	if (Pl_MouseY < Pl_Cent500Y)
	{
		long test = Pl_Cent500Y - Pl_MouseY; // Positive

		if (test > 2)
		{
			Pl_DeltaMouse = float(Pl_Cent500Y - Pl_MouseY);
			mRotY = Degree(Pl_DeltaMouse * (float)0.03);//S_Player[0]->TurnRate);
		}
	}
	else if (Pl_MouseY > Pl_Cent500Y)
	{
		long test = Pl_MouseY - Pl_Cent500Y; // Positive

		if (test > 2)
		{
			Pl_DeltaMouse = float(Pl_MouseY - Pl_Cent500Y);
			mRotY = Degree(-Pl_DeltaMouse * (float)0.03);//S_Player[0]->TurnRate);
		}
	}
	//}

	return 1;
}

// *************************************************************************
// *				Capture_Right_Mouse_Free   Terry Bernie				   *
// *************************************************************************
bool SB_OgreListener::Capture_Right_Mouse_Free(void)
{

	if (CameraMode == Enums::CamDetached)
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
				SetCursorPos(App->CursorPosX, App->CursorPosY);
			}
		}
		else if (Pl_MouseX > Pl_Cent500X)
		{
			long test = Pl_MouseX - Pl_Cent500X; // Positive

			if (test > 2)
			{
				Pl_DeltaMouse = float(Pl_MouseX - Pl_Cent500X);
				mTranslateVector.x = -Pl_DeltaMouse * (mMoveSensitivityMouse / 1000);
				SetCursorPos(App->CursorPosX, App->CursorPosY);
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
				OldPos = mCam->getPosition();

				OldPos.y -= Rate;
				mCam->setPosition(OldPos);
				SetCursorPos(App->CursorPosX, App->CursorPosY);
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
				OldPos = mCam->getPosition();

				OldPos.y += Rate;
				mCam->setPosition(OldPos);
				SetCursorPos(App->CursorPosX, App->CursorPosY);
			}

		}
	}

	return 1;
}

// *************************************************************************
// *		Camera_Mode_Model:- Terry and Hazel Flanigan 2023  			   *
// *************************************************************************
void SB_OgreListener::Camera_Mode_Model(float DeltaTime)
{
	//App->CL_Ogre->m_imgui.render();

	mRotX = 0;
	mRotY = 0;
	mTranslateVector = Ogre::Vector3::ZERO;

	mMoveScale = mMoveSensitivity * DeltaTime;

	App->CLSB_Keyboard->Keyboard_Mode_Model(DeltaTime);
	
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
// *					Capture_LeftMouse_Model							   *
// *************************************************************************
bool SB_OgreListener::Capture_LeftMouse_Model(void)
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
			App->CLSB_Grid->GridNode->yaw(Ogre::Degree(-Pl_DeltaMouse * (mMoveSensitivityMouse / 1000) * 2), Ogre::Node::TS_LOCAL);
			App->CLSB_Grid->HairNode->yaw(Ogre::Degree(-Pl_DeltaMouse * (mMoveSensitivityMouse / 1000) * 2), Ogre::Node::TS_LOCAL);
			App->CLSB_Grid->DummyNode->yaw(Ogre::Degree(-Pl_DeltaMouse * (mMoveSensitivityMouse / 1000) * 2), Ogre::Node::TS_LOCAL);
			App->CLSB_Ogre->RenderListener->RZ = App->CLSB_Ogre->RenderListener->RZ - (Pl_DeltaMouse * (mMoveSensitivityMouse / 1000) * 2);
			SetCursorPos(App->CursorPosX, App->CursorPosY);
		}
	}
	else if (Pl_MouseX > Pl_Cent500X)
	{
		long test = Pl_MouseX - Pl_Cent500X; // Positive

		if (test > 2)
		{
			Pl_DeltaMouse = float(Pl_MouseX - Pl_Cent500X);
			App->CLSB_Grid->GridNode->yaw(Ogre::Degree(Pl_DeltaMouse * (mMoveSensitivityMouse / 1000) * 2), Ogre::Node::TS_LOCAL);
			App->CLSB_Grid->HairNode->yaw(Ogre::Degree(Pl_DeltaMouse * (mMoveSensitivityMouse / 1000) * 2), Ogre::Node::TS_LOCAL);
			App->CLSB_Grid->DummyNode->yaw(Ogre::Degree(Pl_DeltaMouse * (mMoveSensitivityMouse / 1000) * 2), Ogre::Node::TS_LOCAL);
			App->CLSB_Ogre->RenderListener->RZ = App->CLSB_Ogre->RenderListener->RZ + (Pl_DeltaMouse * (mMoveSensitivityMouse / 1000) * 2);
			SetCursorPos(App->CursorPosX, App->CursorPosY);
		}
	}

	// Up Down
	if (Pl_MouseY < Pl_Cent500Y)
	{
		long test = Pl_Cent500Y - Pl_MouseY; // Positive

		if (test > 2)
		{
			Pl_DeltaMouse = float(Pl_Cent500Y - Pl_MouseY);
			App->CLSB_Grid->GridNode->pitch(Ogre::Degree(-Pl_DeltaMouse * (mMoveSensitivityMouse / 1000) * 2), Ogre::Node::TS_PARENT);
			App->CLSB_Grid->HairNode->pitch(Ogre::Degree(-Pl_DeltaMouse * (mMoveSensitivityMouse / 1000) * 2), Ogre::Node::TS_PARENT);
			App->CLSB_Grid->DummyNode->pitch(Ogre::Degree(-Pl_DeltaMouse * (mMoveSensitivityMouse / 1000) * 2), Ogre::Node::TS_PARENT);
			App->CLSB_Ogre->RenderListener->RX = App->CLSB_Ogre->RenderListener->RX - (Pl_DeltaMouse * (mMoveSensitivityMouse / 1000) * 2);
			SetCursorPos(App->CursorPosX, App->CursorPosY);
		}
	}
	else if (Pl_MouseY > Pl_Cent500Y)
	{
		long test = Pl_MouseY - Pl_Cent500Y; // Positive

		if (test > 2)
		{
			Pl_DeltaMouse = float(Pl_MouseY - Pl_Cent500Y);
			App->CLSB_Grid->GridNode->pitch(Ogre::Degree(Pl_DeltaMouse * (mMoveSensitivityMouse / 1000) * 2), Ogre::Node::TS_PARENT);
			App->CLSB_Grid->HairNode->pitch(Ogre::Degree(Pl_DeltaMouse * (mMoveSensitivityMouse / 1000) * 2), Ogre::Node::TS_PARENT);
			App->CLSB_Grid->DummyNode->pitch(Ogre::Degree(Pl_DeltaMouse * (mMoveSensitivityMouse / 1000) * 2), Ogre::Node::TS_PARENT);
			App->CLSB_Ogre->RenderListener->RX = App->CLSB_Ogre->RenderListener->RX + (Pl_DeltaMouse * (mMoveSensitivityMouse / 1000) * 2);
			SetCursorPos(App->CursorPosX, App->CursorPosY);
		}
	}

	return 1;
}

// *************************************************************************
// *					Capture_RightMouse_Model Terry					   *
// *************************************************************************
bool SB_OgreListener::Capture_RightMouse_Model(void)
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
			SetCursorPos(App->CursorPosX, App->CursorPosY);
		}
	}
	else if (Pl_MouseX > Pl_Cent500X)
	{
		long test = Pl_MouseX - Pl_Cent500X; // Positive

		if (test > 2)
		{
			Pl_DeltaMouse = float(Pl_MouseX - Pl_Cent500X);
			mTranslateVector.x = -Pl_DeltaMouse * (mMoveSensitivityMouse / 1000);
			SetCursorPos(App->CursorPosX, App->CursorPosY);
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
			OldPos = mCam->getPosition();

			OldPos.y -= Rate;
			mCam->setPosition(OldPos);
			SetCursorPos(App->CursorPosX, App->CursorPosY);
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
			OldPos = mCam->getPosition();

			OldPos.y += Rate;
			mCam->setPosition(OldPos);
			SetCursorPos(App->CursorPosX, App->CursorPosY);
		}

	}

	return 1;
}

// *************************************************************************
// *				moveCamera   Terry Bernie							   *
// *************************************************************************
void SB_OgreListener::MoveCamera(void)
{
	mCam->yaw(mRotX);
	mCam->pitch(mRotY);
	mCam->moveRelative(mTranslateVector); // Position Relative
	Wheel = 0;

}

// *************************************************************************
// *			Update_Game_Logic:- Terry and Hazel Flanigan 2023		   *
// *************************************************************************
bool SB_OgreListener::Update_Game_Logic(float DeltaTime)
{

	App->CLSB_Ogre->Get_View_Height_Width();
	App->CLSB_Ogre->m_imgui.NewFrame(DeltaTime, (float)View_Width, (float)View_Height);

	if (App->CLSB_Equity->EquitySB_Dialog_Visible == 0)
	{
		App->CLSB_Keyboard->Keyboard_Mode_WorldEditor(NULL);
		return true;
	}

	App->CLSB_ImGui->Render_FPS();
	App->CLSB_Dimensions->Dimesions_Select();

	//if (GD_Run_Physics == 1)
	{
		App->CLSB_Bullet->dynamicsWorld->debugDrawWorld();
	}

	if (GD_Run_Physics == 1)
	{
		App->CLSB_Bullet->dynamicsWorld->stepSimulation(DeltaTime * Bullet_Step);
	}

	//if (App->CLSB_Model->Player_Added == 1)
	//{
	//	//App->Flash_Window();
	//	App->CLSB_Player->updateAction(NULL, DeltaTime);
	//}

	//if (Show_DemoWindow == 1)
	//{
		//ImGui::ShowDemoWindow();
	//}

	App->CLSB_ImGui->ImGui_Editor_Loop();

	if (GD_Run_Physics == 1 && App->CLSB_Scene->Player_Added == 1)
	{
		//App->Flash_Window();
		btTransform trans;
		App->CLSB_Scene->B_Player[0]->Phys_Body->getMotionState()->getWorldTransform(trans);
		btQuaternion orientation = trans.getRotation();
		App->CLSB_Scene->B_Player[0]->Player_Node->setPosition(Ogre::Vector3(trans.getOrigin().getX(), trans.getOrigin().getY(), trans.getOrigin().getZ()));
		App->CLSB_Scene->B_Player[0]->Player_Node->setOrientation(Ogre::Quaternion(orientation.getW(), orientation.getX(), orientation.getY(), orientation.getZ()));
		App->CLSB_Scene->B_Player[0]->Player_Node->pitch(Ogre::Degree(180));
	}

	return true;
}

// *************************************************************************
// *		Capture_LeftMouse:- Terry and Hazel Flanigan 2023			   *
// *************************************************************************
bool SB_OgreListener::Capture_LeftMouse(void)
{
	//if (!ImGui::GetIO().WantCaptureMouse)
	//{
	//	GetCursorPos(&Pl_pt);

	//	Pl_MouseX = (int(Pl_pt.x));
	//	Pl_MouseY = (int(Pl_pt.y));

	//	//// Left Right
	//	if (Pl_MouseX < Pl_Cent500X)
	//	{
	//		long test = Pl_Cent500X - Pl_MouseX; // Positive

	//		if (test > 2)
	//		{
	//			Pl_DeltaMouse = float(Pl_Cent500X - Pl_MouseX);
	//			App->CL_Grid->GridNode->yaw(Ogre::Degree(-Pl_DeltaMouse * (mMoveSensitivityMouse / 1000) * 2), Ogre::Node::TS_LOCAL);
	//			App->CL_Grid->HairNode->yaw(Ogre::Degree(-Pl_DeltaMouse * (mMoveSensitivityMouse / 1000) * 2), Ogre::Node::TS_LOCAL);
	//			App->CL_Grid->DummyNode->yaw(Ogre::Degree(-Pl_DeltaMouse * (mMoveSensitivityMouse / 1000) * 2), Ogre::Node::TS_LOCAL);
	//			///App->CL_Ogre->RenderListener->RZ = App->CL_Ogre->RenderListener->RZ - (Pl_DeltaMouse * (mMoveSensitivityMouse / 1000) * 2);
	//			SetCursorPos(App->CursorPosX, App->CursorPosY);
	//		}
	//	}
	//	else if (Pl_MouseX > Pl_Cent500X)
	//	{
	//		long test = Pl_MouseX - Pl_Cent500X; // Positive

	//		if (test > 2)
	//		{
	//			Pl_DeltaMouse = float(Pl_MouseX - Pl_Cent500X);
	//			App->CL_Grid->GridNode->yaw(Ogre::Degree(Pl_DeltaMouse * (mMoveSensitivityMouse / 1000) * 2), Ogre::Node::TS_LOCAL);
	//			App->CL_Grid->HairNode->yaw(Ogre::Degree(Pl_DeltaMouse * (mMoveSensitivityMouse / 1000) * 2), Ogre::Node::TS_LOCAL);
	//			App->CL_Grid->DummyNode->yaw(Ogre::Degree(Pl_DeltaMouse * (mMoveSensitivityMouse / 1000) * 2), Ogre::Node::TS_LOCAL);
	//			///App->CL_Ogre->RenderListener->RZ = App->CL_Ogre->RenderListener->RZ + (Pl_DeltaMouse * (mMoveSensitivityMouse / 1000) * 2);
	//			SetCursorPos(App->CursorPosX, App->CursorPosY);
	//		}
	//	}

	//	// Up Down
	//	if (Pl_MouseY < Pl_Cent500Y)
	//	{
	//		long test = Pl_Cent500Y - Pl_MouseY; // Positive

	//		if (test > 2)
	//		{
	//			Pl_DeltaMouse = float(Pl_Cent500Y - Pl_MouseY);
	//			App->CL_Grid->GridNode->pitch(Ogre::Degree(-Pl_DeltaMouse * (mMoveSensitivityMouse / 1000) * 2), Ogre::Node::TS_PARENT);
	//			App->CL_Grid->HairNode->pitch(Ogre::Degree(-Pl_DeltaMouse * (mMoveSensitivityMouse / 1000) * 2), Ogre::Node::TS_PARENT);
	//			App->CL_Grid->DummyNode->pitch(Ogre::Degree(-Pl_DeltaMouse * (mMoveSensitivityMouse / 1000) * 2), Ogre::Node::TS_PARENT);
	//			///App->CL_Ogre->RenderListener->RX = App->CL_Ogre->RenderListener->RX - (Pl_DeltaMouse * (mMoveSensitivityMouse / 1000) * 2);
	//			SetCursorPos(App->CursorPosX, App->CursorPosY);
	//		}
	//	}
	//	else if (Pl_MouseY > Pl_Cent500Y)
	//	{
	//		long test = Pl_MouseY - Pl_Cent500Y; // Positive

	//		if (test > 2)
	//		{
	//			Pl_DeltaMouse = float(Pl_MouseY - Pl_Cent500Y);
	//			App->CL_Grid->GridNode->pitch(Ogre::Degree(Pl_DeltaMouse * (mMoveSensitivityMouse / 1000) * 2), Ogre::Node::TS_PARENT);
	//			App->CL_Grid->HairNode->pitch(Ogre::Degree(Pl_DeltaMouse * (mMoveSensitivityMouse / 1000) * 2), Ogre::Node::TS_PARENT);
	//			App->CL_Grid->DummyNode->pitch(Ogre::Degree(Pl_DeltaMouse * (mMoveSensitivityMouse / 1000) * 2), Ogre::Node::TS_PARENT);
	//			///App->CL_Ogre->RenderListener->RX = App->CL_Ogre->RenderListener->RX + (Pl_DeltaMouse * (mMoveSensitivityMouse / 1000) * 2);
	//			SetCursorPos(App->CursorPosX, App->CursorPosY);
	//		}
	//	}
	//}

	return 1;
}

// *************************************************************************
// *							WorldMode   							   *
// *************************************************************************
void SB_OgreListener::WorldMode(float DeltaTime)
{
	//float start = DeltaTime;

	//App->CL_Ogre->m_imgui.render();

	//mRotX = 0;
	//mRotY = 0;
	//mTranslateVector = Ogre::Vector3::ZERO;

	//mMoveScale = mMoveSensitivity  * DeltaTime;

	//if (GD_CameraMode == Enums::CamFirst)
	//{
	//	Ogre::Vector3 Pos;
	//	Ogre::Radian mmPitch;
	//	Ogre::Radian mYaw;

	//	if (FollowPlayer == 1)
	//	{
	//		Pos = App->SBC_Scene->SBC_Base_Player[0]->Player_Node->getPosition();
	//		//Ogre::Quaternion  CQ = App->SBC_Player->Player_Node->getOrientation();

	//		mmPitch = App->SBC_Scene->SBC_Base_Player[0]->CameraPitch->getOrientation().getPitch();
	//		mYaw = App->SBC_Scene->SBC_Base_Player[0]->Player_Node->getOrientation().getYaw();
	//		Pos.y = Pos.y + App->SBC_Scene->SBC_Base_Player[0]->PlayerHeight;

	//	}
	//	else
	//	{
	//		btVector3 Centre;
	//		Centre = App->Cl_Scene_Data->Cl_Object[Object_ToFollow]->bt_body->getWorldTransform().getOrigin();
	//		Pos.x = Centre.getX();
	//		Pos.y = Centre.getY();
	//		Pos.z = Centre.getZ();

	//		//mmPitch = App->Cl_Scene_Data->Cl_Object[Object_ToFollow]->OgreNode->getOrientation().getPitch();
	//		mYaw = App->Cl_Scene_Data->Cl_Object[Object_ToFollow]->OgreNode->getOrientation().getYaw();
	//		Pos.y = Pos.y + App->SBC_Scene->SBC_Base_Player[0]->PlayerHeight;
	//	}

	//	App->CL_Ogre->mCamera->setPosition(Pos);
	//	App->CL_Ogre->mCamera->setOrientation(Ogre::Quaternion(1, 0, 0, 0));
	//	App->CL_Ogre->mCamera->yaw(mYaw);
	//	//App->CL_Ogre->mCamera->pitch(mmPitch);
	//	App->CL_Ogre->mCamera->yaw(Ogre::Degree(180));
	//}

	//App->Cl_Keyboard->Keyboard_Monitor(DeltaTime);

	//if (GetAsyncKeyState(VK_ESCAPE) < 0) // Back to full Screen;
	//{
	//	//App->CL_Ogre->ExitFullScreen();
	//}

	//// Left Mouse
	//if (Pl_LeftMouseDown == 1 && Pl_RightMouseDown == 0)
	//{
	//	if (GD_CameraMode == Enums::CamFirst)
	//	{
	//		//Capture_Mouse_FirstPerson_World();
	//		SetCursorPos(500, 500);
	//	}
	//	else if (GD_CameraMode == Enums::CamNone)
	//	{
	//		Capture_LeftMouse_World();
	//	}
	//	else
	//	{
	//		//Capture_Mouse_Free_World();
	//	}
	//}

	//if (Pl_LeftMouseDown == 1 && GD_CameraMode == Enums::CamDetached)
	//{

	//	if (!ImGui::GetIO().WantCaptureMouse)
	//	{
	//		SetCursorPos(500, 500);
	//	}
	//}

	//// Right Mouse
	//if (Pl_LeftMouseDown == 0 && Pl_RightMouseDown == 1)
	//{
	//	Capture_RightMouse_World();
	//}

	//MoveCamera();

	///*if (App->Cl_Collision->DoMove == 1)
	//{
	//	App->Cl_Collision->MoveObject(DeltaTime);
	//}*/
}

// *************************************************************************
// *				Capture_LeftMouse_World   Terry Bernie				   *
// *************************************************************************
bool SB_OgreListener::Capture_LeftMouse_World(void)
{
	//if (!ImGui::GetIO().WantCaptureMouse)
	//{
	//	GetCursorPos(&Pl_pt);

	//	Pl_MouseX = (int(Pl_pt.x));
	//	Pl_MouseY = (int(Pl_pt.y));

	//	//// Left Right
	//	if (Pl_MouseX < Pl_Cent500X)
	//	{
	//		long test = Pl_Cent500X - Pl_MouseX; // Positive

	//		if (test > 2)
	//		{
	//			Pl_DeltaMouse = float(Pl_Cent500X - Pl_MouseX);
	//			App->SBC_Grid->GridNode->yaw(Ogre::Degree(-Pl_DeltaMouse * (mMoveSensitivityMouse / 1000) * 2), Ogre::Node::TS_LOCAL);
	//			App->SBC_Grid->HairNode->yaw(Ogre::Degree(-Pl_DeltaMouse * (mMoveSensitivityMouse / 1000) * 2), Ogre::Node::TS_LOCAL);
	//			App->SBC_Grid->DummyNode->yaw(Ogre::Degree(-Pl_DeltaMouse * (mMoveSensitivityMouse / 1000) * 2), Ogre::Node::TS_LOCAL);
	//			///App->CL_Ogre->RenderListener->RZ = App->CL_Ogre->RenderListener->RZ - (Pl_DeltaMouse * (mMoveSensitivityMouse / 1000) * 2);
	//			SetCursorPos(App->CursorPosX, App->CursorPosY);
	//		}
	//	}
	//	else if (Pl_MouseX > Pl_Cent500X)
	//	{
	//		long test = Pl_MouseX - Pl_Cent500X; // Positive

	//		if (test > 2)
	//		{
	//			Pl_DeltaMouse = float(Pl_MouseX - Pl_Cent500X);
	//			App->SBC_Grid->GridNode->yaw(Ogre::Degree(Pl_DeltaMouse * (mMoveSensitivityMouse / 1000) * 2), Ogre::Node::TS_LOCAL);
	//			App->SBC_Grid->HairNode->yaw(Ogre::Degree(Pl_DeltaMouse * (mMoveSensitivityMouse / 1000) * 2), Ogre::Node::TS_LOCAL);
	//			App->SBC_Grid->DummyNode->yaw(Ogre::Degree(Pl_DeltaMouse * (mMoveSensitivityMouse / 1000) * 2), Ogre::Node::TS_LOCAL);
	//			///App->CL_Ogre->RenderListener->RZ = App->CL_Ogre->RenderListener->RZ + (Pl_DeltaMouse * (mMoveSensitivityMouse / 1000) * 2);
	//			SetCursorPos(App->CursorPosX, App->CursorPosY);
	//		}
	//	}

	//	// Up Down
	//	if (Pl_MouseY < Pl_Cent500Y)
	//	{
	//		long test = Pl_Cent500Y - Pl_MouseY; // Positive

	//		if (test > 2)
	//		{
	//			Pl_DeltaMouse = float(Pl_Cent500Y - Pl_MouseY);
	//			App->SBC_Grid->GridNode->pitch(Ogre::Degree(-Pl_DeltaMouse * (mMoveSensitivityMouse / 1000) * 2), Ogre::Node::TS_PARENT);
	//			App->SBC_Grid->HairNode->pitch(Ogre::Degree(-Pl_DeltaMouse * (mMoveSensitivityMouse / 1000) * 2), Ogre::Node::TS_PARENT);
	//			App->SBC_Grid->DummyNode->pitch(Ogre::Degree(-Pl_DeltaMouse * (mMoveSensitivityMouse / 1000) * 2), Ogre::Node::TS_PARENT);
	//			///App->CL_Ogre->RenderListener->RX = App->CL_Ogre->RenderListener->RX - (Pl_DeltaMouse * (mMoveSensitivityMouse / 1000) * 2);
	//			SetCursorPos(App->CursorPosX, App->CursorPosY);
	//		}
	//	}
	//	else if (Pl_MouseY > Pl_Cent500Y)
	//	{
	//		long test = Pl_MouseY - Pl_Cent500Y; // Positive

	//		if (test > 2)
	//		{
	//			Pl_DeltaMouse = float(Pl_MouseY - Pl_Cent500Y);
	//			App->SBC_Grid->GridNode->pitch(Ogre::Degree(Pl_DeltaMouse * (mMoveSensitivityMouse / 1000) * 2), Ogre::Node::TS_PARENT);
	//			App->SBC_Grid->HairNode->pitch(Ogre::Degree(Pl_DeltaMouse * (mMoveSensitivityMouse / 1000) * 2), Ogre::Node::TS_PARENT);
	//			App->SBC_Grid->DummyNode->pitch(Ogre::Degree(Pl_DeltaMouse * (mMoveSensitivityMouse / 1000) * 2), Ogre::Node::TS_PARENT);
	//			///App->CL_Ogre->RenderListener->RX = App->CL_Ogre->RenderListener->RX + (Pl_DeltaMouse * (mMoveSensitivityMouse / 1000) * 2);
	//			SetCursorPos(App->CursorPosX, App->CursorPosY);
	//		}
	//	}
	//}

	return 1;
}

// *************************************************************************
// *				Capture_Mouse_FirstPerson_World   Terry Bernie		   *
// *************************************************************************
bool SB_OgreListener::Capture_Mouse_FirstPerson(float DeltaTime)
{
	if (App->CLSB_Scene->Player_Added == 0)
	{
		return 0;
	}
	
	GetCursorPos(&Pl_pt);

	Pl_MouseX = (int(Pl_pt.x));
	Pl_MouseY = (int(Pl_pt.y));

	// Left Right
	if (Pl_MouseX < Pl_Cent500X)
	{
		long test = Pl_Cent500X - Pl_MouseX; // Rotate Left
		if (test > 2)
		{
			Pl_DeltaMouse = float(Pl_Cent500X - Pl_MouseX);

			float Delta2 = DeltaTime * 150;
			float mTurn = (App->CLSB_Scene->B_Player[0]->TurnRate * Pl_DeltaMouse) * Delta2;

			App->CLSB_Scene->B_Player[0]->Rotate_FromCam(Ogre::Vector3(0,-1,0), mTurn, false);
		
		}
	}
	else if (Pl_MouseX > Pl_Cent500X)
	{
		long test = Pl_MouseX - Pl_Cent500X; // Rotate Right
		if (test > 2)
		{
			Pl_DeltaMouse = float(Pl_MouseX - Pl_Cent500X);

			float Delta2 = DeltaTime * 150;
			float mTurn = (App->CLSB_Scene->B_Player[0]->TurnRate * Pl_DeltaMouse)* Delta2;

			App->CLSB_Scene->B_Player[0]->Rotate_FromCam(Ogre::Vector3(0,1,0), mTurn, false);

		}
	}

	//Up Down
	if (Pl_MouseY < Pl_Cent500Y)
	{
		long test = Pl_Cent500Y - Pl_MouseY; // Look Up

		if (test > 1)
		{
			if (App->CLSB_Scene->B_Player[0]->CameraPitch->getOrientation().getPitch().valueDegrees() > App->CLSB_Scene->B_Player[0]->Limit_Look_Up)
			{

			}
			else
			{
				Pl_DeltaMouse = float(Pl_Cent500Y - Pl_MouseY);
				Ogre::Radian pp = Degree(Pl_DeltaMouse * DeltaTime) * 2;
				App->CLSB_Scene->B_Player[0]->CameraPitch->pitch(pp);
			}
		}

	}
	else if (Pl_MouseY > Pl_Cent500Y)
	{
		long test = Pl_MouseY - Pl_Cent500Y; // Look Down

		if (test > 1)
		{
			if (App->CLSB_Scene->B_Player[0]->CameraPitch->getOrientation().getPitch().valueDegrees() < App->CLSB_Scene->B_Player[0]->Limit_Look_Down)
			{

			}
			else
			{
				Pl_DeltaMouse = float(Pl_MouseY - Pl_Cent500Y);
				Ogre::Radian pp = Degree(-Pl_DeltaMouse * DeltaTime) * 2;
				App->CLSB_Scene->B_Player[0]->CameraPitch->pitch(pp);
			}
		}
	}

	return 1;
}






