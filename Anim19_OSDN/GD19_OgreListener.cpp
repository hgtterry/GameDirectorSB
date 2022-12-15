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

#include "stdafx.h"
#include "GD19_App.h"
#include "GD19_OgreListener.h"



GD19_OgreListener::GD19_OgreListener(void)
{
	mCam = App->SBC_Ogre->mCamera;
	Pl_mDummyCamera = App->SBC_Ogre->mSceneMgr->createCamera("PickCamera");

	Wheel = 0;
	StopOgre = 0;
	ShowFPS = 1;
	Show_DemoWindow = 0;
	
	GD_CameraMode = Enums::CamNone;

	Pl_mDummyTranslateVector = Ogre::Vector3::ZERO;

	mMoveScale = 0;
	mMoveSensitivity = 50;
	mMoveSensitivityMouse = 50;

	Pl_LeftMouseDown = 0;
	Pl_RightMouseDown = 0;

	Pl_DeltaMouse = 0;
	Pl_MouseX = 0;
	Pl_MouseY = 0;

	Pl_Cent500X = App->CursorPosX;
	Pl_Cent500Y = App->CursorPosY;

	GD_Run_Physics = 0;
	Dubug_Physics_Draw = 0;
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
	
	mCollisionTools = new MOC::CollisionTools(App->SBC_Ogre->mSceneMgr);
	mCollisionTools->setHeightAdjust(3.5f);

	CameraMode = 1;  // Model Mode

	ImGui_Render_Tab = Enums::ImGui_Camera;

}

GD19_OgreListener::~GD19_OgreListener(void)
{
	
}

// *************************************************************************
// *						Reset_Class Terry Bernie					   *
// *************************************************************************
void GD19_OgreListener::Reset_Class(void)
{
	Animate_Ogre = 0;
	CameraMode = 1;  // Model Mode
	ImGui_Render_Tab = Enums::ImGui_Camera;
}

// *************************************************************************
// *				frameStarted   Terry Bernie							   *
// *************************************************************************
bool GD19_OgreListener::frameStarted(const FrameEvent& evt)
{
	Update_Game_Logic(evt.timeSinceLastFrame);
	return true;
}

// *************************************************************************
// *			frameRenderingQueued   Terry Bernie						   *
// *************************************************************************
bool GD19_OgreListener::frameRenderingQueued(const FrameEvent& evt)
{

	OgreFrameTime = evt.timeSinceLastFrame;

	if (App->SBC_Ogre->Block_RenderingQueued == 1)
	{
		return 1;
	}

	if (MeshViewer_Running == 1)
	{
		return 1;
	}

	App->SBC_Ogre->Block_RenderingQueued = 1;

	if (App->CL_Vm_ImGui->Show_Progress_Bar == 1)
	{
		App->SBC_Ogre->m_imgui.render();
		return 1;
	}

	App->SBC_Ogre->m_imgui.render();

	mRotX = 0;
	mRotY = 0;
	mTranslateVector = Ogre::Vector3::ZERO;

	mMoveScale = mMoveSensitivity  * evt.timeSinceLastFrame;

	if (GD_CameraMode == Enums::CamFirst)
	{
		Ogre::Vector3 Pos;
		Ogre::Radian mmPitch;
		Ogre::Radian mYaw;

		Pos = App->SBC_Scene->B_Player[0]->Player_Node->getPosition();
		
		mmPitch = App->SBC_Scene->B_Player[0]->CameraPitch->getOrientation().getPitch();
		mYaw = App->SBC_Scene->B_Player[0]->Player_Node->getOrientation().getYaw();
		Pos.y = Pos.y + App->SBC_Scene->B_Player[0]->PlayerHeight;

		App->SBC_Ogre->mCamera->setPosition(Pos);
		App->SBC_Ogre->mCamera->setOrientation(Ogre::Quaternion(1, 0, 0, 0));
		App->SBC_Ogre->mCamera->yaw(mYaw);
		App->SBC_Ogre->mCamera->pitch(mmPitch);
		App->SBC_Ogre->mCamera->yaw(Ogre::Degree(180));
	}

	App->Cl_Keyboard->Keyboard_Monitor(evt.timeSinceLastFrame);

	// Left Mouse
	if (Pl_LeftMouseDown == 1 && Pl_RightMouseDown == 0)
	{
		if (GD_CameraMode == Enums::CamFirst)
		{
			Capture_Mouse_FirstPerson(evt.timeSinceLastFrame);
			SetCursorPos(App->CursorPosX, App->CursorPosY);
		}
		else if (GD_CameraMode == Enums::CamNone)
		{
			Capture_LeftMouse();
		}
		else
		{
			Capture_Mouse_Free();	
		}
	}

	if (Pl_LeftMouseDown == 1 && GD_CameraMode == Enums::CamDetached)
	{
		SetCursorPos(App->CursorPosX, App->CursorPosY);
	}

	// Right Mouse
	if (Pl_LeftMouseDown == 0 && Pl_RightMouseDown == 1)
	{
		Capture_RightMouse_World();
	}

	MoveCamera();

	if (App->SBC_Collision->DoMove == 1)
	{
		App->SBC_Collision->MoveObject_Listener(evt.timeSinceLastFrame);
	}

	App->SBC_Ogre->Block_RenderingQueued = 0;

	return 1;
}

// *************************************************************************
// *				frameEnded   Terry Bernie							   *
// *************************************************************************
bool GD19_OgreListener::frameEnded(const FrameEvent& evt)
{

	if (StopOgre == 1)
	{
		return false;
	}

	return true;
}

// *************************************************************************
// *				Update_Game_Logic   Terry Bernie					   *
// *************************************************************************
bool GD19_OgreListener::Update_Game_Logic(float DeltaTime)
{

	if (App->CL_Vm_ImGui->Show_Progress_Bar == 1)
	{
		App->SBC_Ogre->Get_View_Height_Width();

		App->SBC_Ogre->m_imgui.NewFrame(DeltaTime, (float)View_Width, (float)View_Height);
		App->CL_Vm_ImGui->ImGui_ProgressBar();
		return true;
	}

	App->SBC_Ogre->Get_View_Height_Width();
	App->SBC_Ogre->m_imgui.NewFrame(DeltaTime, (float)View_Width, (float)View_Height);


	int Count = 0;
	while (Count < App->SBC_Scene->Counters_Count)
	{
		if (App->SBC_Scene->B_Counter[Count]->Show_Panel_Flag == 1)
		{
			App->SBC_Scene->B_Counter[Count]->Render_ImGui_Panel();
		}

		Count++;
	}

	Count = 0;
	while (Count < App->SBC_Scene->Object_Count)
	{
		if (App->SBC_Scene->B_Object[Count]->Usage == Enums::Usage_Message)
		{
			if (App->SBC_Scene->B_Object[Count]->Show_Message_Flag == 1)
			{
				App->SBC_Scene->B_Object[Count]->Render_ImGui_Panel();
			}
		}

		Count++;
	}

	App->CL_Vm_ImGui->ImGui_Render_Loop();
	App->SBC_Debug->Debug_Render_Loop();
	App->SBC_Dimensions->Dimesions_Select();

	if (Show_DemoWindow == 1)
	{
		ImGui::ShowDemoWindow();
	}
	
	if (Dubug_Physics_Draw == 1)
	{
		App->SBC_Bullet->dynamicsWorld->debugDrawWorld();
	}

	if (GD_Run_Physics == 1)
	{
		App->SBC_Bullet->dynamicsWorld->stepSimulation(DeltaTime * 2); //suppose you have 60 frames per second	

		for (int j = App->SBC_Bullet->dynamicsWorld->getNumCollisionObjects() - 1; j >= 0; j--)
		{
			btCollisionObject* obj = App->SBC_Bullet->dynamicsWorld->getCollisionObjectArray()[j];
			btRigidBody* body = btRigidBody::upcast(obj);
			btTransform trans;

			if (body && body->getMotionState())
			{
				int UI = body->getUserIndex();
				int Index = body->getUserIndex2();


				if (UI == Enums::Usage_Dynamic && App->SBC_Scene->B_Object[Index]->Deleted == 0)
				{
					body->getMotionState()->getWorldTransform(trans);
					btQuaternion orientation = trans.getRotation();

					float x = trans.getOrigin().getX();
					float y = trans.getOrigin().getY();
					float z = trans.getOrigin().getZ();

					App->SBC_Scene->B_Object[Index]->Object_Node->setPosition(Ogre::Vector3(x, y, z));
					App->SBC_Scene->B_Object[Index]->Object_Node->setOrientation(Ogre::Quaternion(orientation.getW(), orientation.getX(), orientation.getY(), orientation.getZ()));

					Ogre::Vector3 WC = App->SBC_Object->Get_BoundingBox_World_Centre(Index);

					Ogre::Vector3 NewPos = Ogre::Vector3(x, y, z) - WC;
					App->SBC_Scene->B_Object[Index]->Object_Node->setPosition((Ogre::Vector3(x, y, z)) + NewPos);
				}

			}
			else
			{
				trans = obj->getWorldTransform();
			}
		}
	}

	if (GD_Run_Physics == 1 && App->SBC_Scene->Player_Added == 1)
	{
		btTransform trans;
		App->SBC_Scene->B_Player[0]->Phys_Body->getMotionState()->getWorldTransform(trans);
		btQuaternion orientation = trans.getRotation();
		App->SBC_Scene->B_Player[0]->Player_Node->setPosition(Ogre::Vector3(trans.getOrigin().getX(), trans.getOrigin().getY(), trans.getOrigin().getZ()));
		App->SBC_Scene->B_Player[0]->Player_Node->setOrientation(Ogre::Quaternion(orientation.getW(), orientation.getX(), orientation.getY(), orientation.getZ()));
		App->SBC_Scene->B_Player[0]->Player_Node->pitch(Ogre::Degree(180));
	}
	return true;
}

// *************************************************************************
// *				Capture_LeftMouse   Terry Bernie					   *
// *************************************************************************
bool GD19_OgreListener::Capture_LeftMouse(void)
{
	if (!ImGui::GetIO().WantCaptureMouse)
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
				App->SBC_Grid->GridNode->yaw(Ogre::Degree(-Pl_DeltaMouse * (mMoveSensitivityMouse / 1000) * 2), Ogre::Node::TS_LOCAL);
				App->SBC_Grid->HairNode->yaw(Ogre::Degree(-Pl_DeltaMouse * (mMoveSensitivityMouse / 1000) * 2), Ogre::Node::TS_LOCAL);
				App->SBC_Grid->DummyNode->yaw(Ogre::Degree(-Pl_DeltaMouse * (mMoveSensitivityMouse / 1000) * 2), Ogre::Node::TS_LOCAL);
				///App->SBC_Ogre->RenderListener->RZ = App->SBC_Ogre->RenderListener->RZ - (Pl_DeltaMouse * (mMoveSensitivityMouse / 1000) * 2);
				SetCursorPos(App->CursorPosX, App->CursorPosY);
			}
		}
		else if (Pl_MouseX > Pl_Cent500X)
		{
			long test = Pl_MouseX - Pl_Cent500X; // Positive

			if (test > 2)
			{
				Pl_DeltaMouse = float(Pl_MouseX - Pl_Cent500X);
				App->SBC_Grid->GridNode->yaw(Ogre::Degree(Pl_DeltaMouse * (mMoveSensitivityMouse / 1000) * 2), Ogre::Node::TS_LOCAL);
				App->SBC_Grid->HairNode->yaw(Ogre::Degree(Pl_DeltaMouse * (mMoveSensitivityMouse / 1000) * 2), Ogre::Node::TS_LOCAL);
				App->SBC_Grid->DummyNode->yaw(Ogre::Degree(Pl_DeltaMouse * (mMoveSensitivityMouse / 1000) * 2), Ogre::Node::TS_LOCAL);
				///App->SBC_Ogre->RenderListener->RZ = App->SBC_Ogre->RenderListener->RZ + (Pl_DeltaMouse * (mMoveSensitivityMouse / 1000) * 2);
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
				App->SBC_Grid->GridNode->pitch(Ogre::Degree(-Pl_DeltaMouse * (mMoveSensitivityMouse / 1000) * 2), Ogre::Node::TS_PARENT);
				App->SBC_Grid->HairNode->pitch(Ogre::Degree(-Pl_DeltaMouse * (mMoveSensitivityMouse / 1000) * 2), Ogre::Node::TS_PARENT);
				App->SBC_Grid->DummyNode->pitch(Ogre::Degree(-Pl_DeltaMouse * (mMoveSensitivityMouse / 1000) * 2), Ogre::Node::TS_PARENT);
				///App->SBC_Ogre->RenderListener->RX = App->SBC_Ogre->RenderListener->RX - (Pl_DeltaMouse * (mMoveSensitivityMouse / 1000) * 2);
				SetCursorPos(App->CursorPosX, App->CursorPosY);
			}
		}
		else if (Pl_MouseY > Pl_Cent500Y)
		{
			long test = Pl_MouseY - Pl_Cent500Y; // Positive

			if (test > 2)
			{
				Pl_DeltaMouse = float(Pl_MouseY - Pl_Cent500Y);
				App->SBC_Grid->GridNode->pitch(Ogre::Degree(Pl_DeltaMouse * (mMoveSensitivityMouse / 1000) * 2), Ogre::Node::TS_PARENT);
				App->SBC_Grid->HairNode->pitch(Ogre::Degree(Pl_DeltaMouse * (mMoveSensitivityMouse / 1000) * 2), Ogre::Node::TS_PARENT);
				App->SBC_Grid->DummyNode->pitch(Ogre::Degree(Pl_DeltaMouse * (mMoveSensitivityMouse / 1000) * 2), Ogre::Node::TS_PARENT);
				///App->SBC_Ogre->RenderListener->RX = App->SBC_Ogre->RenderListener->RX + (Pl_DeltaMouse * (mMoveSensitivityMouse / 1000) * 2);
				SetCursorPos(App->CursorPosX, App->CursorPosY);
			}
		}
	}

	return 1;
}

// *************************************************************************
// *							WorldMode   							   *
// *************************************************************************
void GD19_OgreListener::WorldMode(float DeltaTime)
{
	//float start = DeltaTime;

	//App->SBC_Ogre->m_imgui.render();

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

	//	App->SBC_Ogre->mCamera->setPosition(Pos);
	//	App->SBC_Ogre->mCamera->setOrientation(Ogre::Quaternion(1, 0, 0, 0));
	//	App->SBC_Ogre->mCamera->yaw(mYaw);
	//	//App->SBC_Ogre->mCamera->pitch(mmPitch);
	//	App->SBC_Ogre->mCamera->yaw(Ogre::Degree(180));
	//}

	//App->Cl_Keyboard->Keyboard_Monitor(DeltaTime);

	//if (GetAsyncKeyState(VK_ESCAPE) < 0) // Back to full Screen;
	//{
	//	App->SBC_Ogre->ExitFullScreen();
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

	//if (App->Cl_Collision->DoMove == 1)
	//{
	//	App->Cl_Collision->MoveObject(DeltaTime);
	//}
}

// *************************************************************************
// *							ModelMode   							   *
// *************************************************************************
void GD19_OgreListener::ModelMode(float DeltaTime)
{
	mRotX = 0;
	mRotY = 0;
	mTranslateVector = Ogre::Vector3::ZERO;

	mMoveScale = mMoveSensitivity  * DeltaTime;

	App->SBC_Ogre->m_imgui.render();

	if (GetAsyncKeyState(88) < 0)
	{
		//SelectEntity();
	}

	if (GetAsyncKeyState(69) < 0) // Q key Down in Fly Mode
	{
		Ogre::Real Rate;
		Rate = (mMoveSensitivity / 1000) * 2;    //0.1;//FlyRate;

		Ogre::Vector3 OldPos;
		OldPos = mCam->getPosition();

		OldPos.y += Rate;
		mCam->setPosition(OldPos);
	}
	//------------------------------------------------
	if (GetAsyncKeyState(81) < 0) // E key Up in Fly Mode
	{
		Ogre::Real Rate;
		Rate = (mMoveSensitivity / 1000) * 2;// 0.1;//FlyRate;

		Ogre::Vector3 OldPos;
		OldPos = mCam->getPosition();

		OldPos.y -= Rate;
		mCam->setPosition(OldPos);
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
	////------------------------------------------------
	//// back
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
			App->SBC_Ogre->ExitFullScreen();
		}
	}

	if (GetAsyncKeyState(VK_END) < 0) // Back to full Screen;
	{
		//SelectEntity();
	}

	// Left Mouse
	if (Pl_LeftMouseDown == 1 && Pl_RightMouseDown == 0)
	{
		Capture_LeftMouse_Model();
	}

	// Right Mouse
	if (Pl_LeftMouseDown == 0 && Pl_RightMouseDown == 1)
	{
		Capture_RightMouse_World();
	}

	MoveCamera();
}

// *************************************************************************
// *				moveCamera   Terry Bernie							   *
// *************************************************************************
void GD19_OgreListener::MoveCamera(void)
{

	mCam->yaw(mRotX);
	mCam->pitch(mRotY);
	mCam->moveRelative(mTranslateVector); // Position Relative
	Wheel = 0;

}

// *************************************************************************
// *				Capture_Mouse_Free_World   Terry Bernie				   *
// *************************************************************************
bool GD19_OgreListener::Capture_Mouse_Free(void)
{
	if (!ImGui::GetIO().WantCaptureMouse)
	{
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
	}

	return 1;
}

// *************************************************************************
// *				Capture_LeftMouse_World   Terry Bernie				   *
// *************************************************************************
bool GD19_OgreListener::Capture_LeftMouse_World(void)
{
	if (!ImGui::GetIO().WantCaptureMouse)
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
				App->SBC_Grid->GridNode->yaw(Ogre::Degree(-Pl_DeltaMouse * (mMoveSensitivityMouse / 1000) * 2), Ogre::Node::TS_LOCAL);
				App->SBC_Grid->HairNode->yaw(Ogre::Degree(-Pl_DeltaMouse * (mMoveSensitivityMouse / 1000) * 2), Ogre::Node::TS_LOCAL);
				App->SBC_Grid->DummyNode->yaw(Ogre::Degree(-Pl_DeltaMouse * (mMoveSensitivityMouse / 1000) * 2), Ogre::Node::TS_LOCAL);
				///App->SBC_Ogre->RenderListener->RZ = App->SBC_Ogre->RenderListener->RZ - (Pl_DeltaMouse * (mMoveSensitivityMouse / 1000) * 2);
				SetCursorPos(App->CursorPosX, App->CursorPosY);
			}
		}
		else if (Pl_MouseX > Pl_Cent500X)
		{
			long test = Pl_MouseX - Pl_Cent500X; // Positive

			if (test > 2)
			{
				Pl_DeltaMouse = float(Pl_MouseX - Pl_Cent500X);
				App->SBC_Grid->GridNode->yaw(Ogre::Degree(Pl_DeltaMouse * (mMoveSensitivityMouse / 1000) * 2), Ogre::Node::TS_LOCAL);
				App->SBC_Grid->HairNode->yaw(Ogre::Degree(Pl_DeltaMouse * (mMoveSensitivityMouse / 1000) * 2), Ogre::Node::TS_LOCAL);
				App->SBC_Grid->DummyNode->yaw(Ogre::Degree(Pl_DeltaMouse * (mMoveSensitivityMouse / 1000) * 2), Ogre::Node::TS_LOCAL);
				///App->SBC_Ogre->RenderListener->RZ = App->SBC_Ogre->RenderListener->RZ + (Pl_DeltaMouse * (mMoveSensitivityMouse / 1000) * 2);
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
				App->SBC_Grid->GridNode->pitch(Ogre::Degree(-Pl_DeltaMouse * (mMoveSensitivityMouse / 1000) * 2), Ogre::Node::TS_PARENT);
				App->SBC_Grid->HairNode->pitch(Ogre::Degree(-Pl_DeltaMouse * (mMoveSensitivityMouse / 1000) * 2), Ogre::Node::TS_PARENT);
				App->SBC_Grid->DummyNode->pitch(Ogre::Degree(-Pl_DeltaMouse * (mMoveSensitivityMouse / 1000) * 2), Ogre::Node::TS_PARENT);
				///App->SBC_Ogre->RenderListener->RX = App->SBC_Ogre->RenderListener->RX - (Pl_DeltaMouse * (mMoveSensitivityMouse / 1000) * 2);
				SetCursorPos(App->CursorPosX, App->CursorPosY);
			}
		}
		else if (Pl_MouseY > Pl_Cent500Y)
		{
			long test = Pl_MouseY - Pl_Cent500Y; // Positive

			if (test > 2)
			{
				Pl_DeltaMouse = float(Pl_MouseY - Pl_Cent500Y);
				App->SBC_Grid->GridNode->pitch(Ogre::Degree(Pl_DeltaMouse * (mMoveSensitivityMouse / 1000) * 2), Ogre::Node::TS_PARENT);
				App->SBC_Grid->HairNode->pitch(Ogre::Degree(Pl_DeltaMouse * (mMoveSensitivityMouse / 1000) * 2), Ogre::Node::TS_PARENT);
				App->SBC_Grid->DummyNode->pitch(Ogre::Degree(Pl_DeltaMouse * (mMoveSensitivityMouse / 1000) * 2), Ogre::Node::TS_PARENT);
				///App->SBC_Ogre->RenderListener->RX = App->SBC_Ogre->RenderListener->RX + (Pl_DeltaMouse * (mMoveSensitivityMouse / 1000) * 2);
				SetCursorPos(App->CursorPosX, App->CursorPosY);
			}
		}
	}

	return 1;
}

// *************************************************************************
// *					Capture_LeftMouse_Model							   *
// *************************************************************************
bool GD19_OgreListener::Capture_LeftMouse_Model(void)
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
			App->SBC_Grid->GridNode->yaw(Ogre::Degree(-Pl_DeltaMouse * (mMoveSensitivityMouse / 1000) * 2), Ogre::Node::TS_LOCAL);
			App->SBC_Grid->HairNode->yaw(Ogre::Degree(-Pl_DeltaMouse * (mMoveSensitivityMouse / 1000) * 2), Ogre::Node::TS_LOCAL);
			App->SBC_Grid->DummyNode->yaw(Ogre::Degree(-Pl_DeltaMouse * (mMoveSensitivityMouse / 1000) * 2), Ogre::Node::TS_LOCAL);
			//App->SBC_Ogre->RenderListener->RZ = App->SBC_Ogre->RenderListener->RZ - (Pl_DeltaMouse * (mMoveSensitivityMouse / 1000) * 2);
			SetCursorPos(App->CursorPosX, App->CursorPosY);
		}
	}
	else if (Pl_MouseX > Pl_Cent500X)
	{
		long test = Pl_MouseX - Pl_Cent500X; // Positive

		if (test > 2)
		{
			Pl_DeltaMouse = float(Pl_MouseX - Pl_Cent500X);
			App->SBC_Grid->GridNode->yaw(Ogre::Degree(Pl_DeltaMouse * (mMoveSensitivityMouse / 1000) * 2), Ogre::Node::TS_LOCAL);
			App->SBC_Grid->HairNode->yaw(Ogre::Degree(Pl_DeltaMouse * (mMoveSensitivityMouse / 1000) * 2), Ogre::Node::TS_LOCAL);
			App->SBC_Grid->DummyNode->yaw(Ogre::Degree(Pl_DeltaMouse * (mMoveSensitivityMouse / 1000) * 2), Ogre::Node::TS_LOCAL);
			//App->SBC_Ogre->RenderListener->RZ = App->SBC_Ogre->RenderListener->RZ + (Pl_DeltaMouse * (mMoveSensitivityMouse / 1000) * 2);
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
			App->SBC_Grid->GridNode->pitch(Ogre::Degree(-Pl_DeltaMouse * (mMoveSensitivityMouse / 1000) * 2), Ogre::Node::TS_PARENT);
			App->SBC_Grid->HairNode->pitch(Ogre::Degree(-Pl_DeltaMouse * (mMoveSensitivityMouse / 1000) * 2), Ogre::Node::TS_PARENT);
			App->SBC_Grid->DummyNode->pitch(Ogre::Degree(-Pl_DeltaMouse * (mMoveSensitivityMouse / 1000) * 2), Ogre::Node::TS_PARENT);
			//App->SBC_Ogre->RenderListener->RX = App->SBC_Ogre->RenderListener->RX - (Pl_DeltaMouse * (mMoveSensitivityMouse / 1000) * 2);
			SetCursorPos(App->CursorPosX, App->CursorPosY);
		}
	}
	else if (Pl_MouseY > Pl_Cent500Y)
	{
		long test = Pl_MouseY - Pl_Cent500Y; // Positive

		if (test > 2)
		{
			Pl_DeltaMouse = float(Pl_MouseY - Pl_Cent500Y);
			App->SBC_Grid->GridNode->pitch(Ogre::Degree(Pl_DeltaMouse * (mMoveSensitivityMouse / 1000) * 2), Ogre::Node::TS_PARENT);
			App->SBC_Grid->HairNode->pitch(Ogre::Degree(Pl_DeltaMouse * (mMoveSensitivityMouse / 1000) * 2), Ogre::Node::TS_PARENT);
			App->SBC_Grid->DummyNode->pitch(Ogre::Degree(Pl_DeltaMouse * (mMoveSensitivityMouse / 1000) * 2), Ogre::Node::TS_PARENT);
			//App->SBC_Ogre->RenderListener->RX = App->SBC_Ogre->RenderListener->RX + (Pl_DeltaMouse * (mMoveSensitivityMouse / 1000) * 2);
			SetCursorPos(App->CursorPosX, App->CursorPosY);
		}
	}

	return 1;
}

// *************************************************************************
// *				Capture_Mouse_FirstPerson_World   Terry Bernie		   *
// *************************************************************************
bool GD19_OgreListener::Capture_Mouse_FirstPerson(float DeltaTime)
{

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
			float mTurn = (App->SBC_Scene->B_Player[0]->TurnRate * Pl_DeltaMouse) * Delta2;

			App->SBC_Scene->B_Player[0]->Rotate_FromCam(Ogre::Vector3(0,-1,0), mTurn, false);
		
		}
	}
	else if (Pl_MouseX > Pl_Cent500X)
	{
		long test = Pl_MouseX - Pl_Cent500X; // Rotate Right

		if (test > 2)
		{
			Pl_DeltaMouse = float(Pl_MouseX - Pl_Cent500X);

			float Delta2 = DeltaTime * 150;
			float mTurn = (App->SBC_Scene->B_Player[0]->TurnRate * Pl_DeltaMouse) * Delta2;

			App->SBC_Scene->B_Player[0]->Rotate_FromCam(Ogre::Vector3(0,1,0), mTurn, false);
		}
	}

	//Up Down
	if (Pl_MouseY < Pl_Cent500Y)
	{
		long test = Pl_Cent500Y - Pl_MouseY; // Look Up

		if (test > 1)
		{
			if (App->SBC_Scene->B_Player[0]->CameraPitch->getOrientation().getPitch().valueDegrees() > App->SBC_Scene->B_Player[0]->Limit_Look_Up)
			{

			}
			else
			{
				Pl_DeltaMouse = float(Pl_Cent500Y - Pl_MouseY);
				Ogre::Radian pp = Degree(Pl_DeltaMouse * DeltaTime) * 2;
				App->SBC_Scene->B_Player[0]->CameraPitch->pitch(pp);
			}

		}

	}
	else if (Pl_MouseY > Pl_Cent500Y)
	{
		long test = Pl_MouseY - Pl_Cent500Y; // Look Down

		if (test > 1)
		{
			if (App->SBC_Scene->B_Player[0]->CameraPitch->getOrientation().getPitch().valueDegrees() < App->SBC_Scene->B_Player[0]->Limit_Look_Down)
			{

			}
			else
			{
				Pl_DeltaMouse = float(Pl_MouseY - Pl_Cent500Y);
				Ogre::Radian pp = Degree(-Pl_DeltaMouse * DeltaTime) * 2;
				App->SBC_Scene->B_Player[0]->CameraPitch->pitch(pp);
			}
		}
	}

	return 1;
}

// *************************************************************************
// *					Capture_RightMouse_Model Terry					   *
// *************************************************************************
bool GD19_OgreListener::Capture_RightMouse_Model(void)
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
// *				Capture_RightMouse_World   Terry Bernie				   *
// *************************************************************************
bool GD19_OgreListener::Capture_RightMouse_World(void)
{

	/*if (App->CL10_Dimensions->Mouse_Move_Mode == Enums::Edit_Mouse_Active)
	{
		return 1;
	}

	if (GD_CameraMode == Enums::CamFirst)
	{
		return 1;
	}*/

	if (App->SBC_Ogre->OgreListener->GD_CameraMode == Enums::CamDetached)
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
// *					SelectEntity_World   Terry Bernie				   *
// *************************************************************************
bool GD19_OgreListener::SelectEntity_World(void)
{
	Ogre::SceneNode *mNode;
	Vector3 oldPos = App->SBC_Ogre->mCamera->getPosition();
	Pl_mDummyCamera->setPosition(oldPos);

	Ogre::Quaternion Q;
	Q = App->SBC_Ogre->mCamera->getOrientation();

	Pl_mDummyCamera->setOrientation(Q);
	Pl_mDummyTranslateVector = Ogre::Vector3::ZERO;

	Pl_mDummyTranslateVector.z = -10000.0;
	Pl_mDummyCamera->moveRelative(Pl_mDummyTranslateVector);

	if (mCollisionTools->collidesWithEntity(oldPos, Pl_mDummyCamera->getPosition(), 1.0f, 0, -1))
	{
		mNode = mCollisionTools->pentity->getParentSceneNode();

		Pl_Entity_Name = mCollisionTools->pentity->getName();
		char buff[255];
		strcpy(buff, Pl_Entity_Name.c_str());
		//App->Say(buff);


		//mNameOverlay->show();
		App->CL_Vm_ImGui->Show_Object_Selection = 1;

		bool test = Ogre::StringUtil::match("Plane0", Pl_Entity_Name, true);
		if (test == 1)
		{
			Pl_Entity_Name = "---------";
		}
		else
		{
			bool test = Ogre::StringUtil::match("Player_1", Pl_Entity_Name, true);
			if (test == 1)
			{
				Pl_Entity_Name = "Player_1";
				//OverlayElement* guiName = OverlayManager::getSingleton().getOverlayElement("Core/ObjectName");
				//guiName->setCaption("Player_1");
				//mNameOverlay->show();
				return 1;
				//mNameOverlay->show();
			}
			else
			{
				char *pdest;
				int IntNum = 0;
				char buffer[255];

				strcpy(buffer, Pl_Entity_Name.c_str());
				pdest = strstr(buffer, "GDEnt_");
				if (pdest != NULL)
				{
					sscanf((buffer + 6), "%i", &IntNum);

					//if (IntNum > 0)
					{
						App->SBC_Visuals->MarkerBB_Addjust(IntNum);
						Selected_Entity_Index = IntNum;
						//OverlayElement* guiName = OverlayManager::getSingleton().getOverlayElement("Core/ObjectName");
						//guiName->setCaption(App->SBC_Scene->B_Object[IntNum]->Mesh_Name);
						strcpy(Selected_Object_Name, App->SBC_Scene->B_Object[IntNum]->Mesh_Name);
						//mNameOverlay->show();
						return 1;
					}
				}
			}

			//OverlayElement* guiName = OverlayManager::getSingleton().getOverlayElement("Core/ObjectName");
			//guiName->setCaption("-------------");
		}

	}

	return 1;
}


