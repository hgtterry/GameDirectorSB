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
#include "StdAfx.h"
#include "BT_App.h"
#include "BT_PhysicsListener.h"
#pragma warning( disable : 4996 4311 4305)

BT_PhysicsListener::BT_PhysicsListener(Camera* cam,Terrain * terrain)
{

	GD_SpinRate = 1;
	GD_MeshViewer_Running = 0;
	GD_Run_Physics = 0;
	GD_Dubug_Physics = 0;
	GD_CameraMode = Enums::CamDetached;
	GD_Selection_Mode = 0;
	Selected_Entity_Index = 0;

	StopOgre = 0;

	Gen_Test = 0;

	//mDebugOverlay = OverlayManager::getSingleton().getByName("Core/DebugOverlaySmall");
	//mDebugOverlay->hide();

	//mNameOverlay = OverlayManager::getSingleton().getByName("Core/ObjectNameOverlay");
	//mNameOverlay->hide();

	//showDebugOverlay(true);

	Wheel = 0;
	mCam = App->Ogre17->mCamera;
	Pl_mDummyCamera = App->Ogre17->mSceneMgr->createCamera("PickCamera");

	mMoveScale = 0;
	mMoveSensitivity = 50;
	mMoveSensitivityMouse = 50;
	KeyFrame_Speed = 0.500;

	Pl_LeftMouseDown = 1;
	Pl_RightMouseDown = 0;

	Pl_Cent500X = 500;
	Pl_Cent500Y = 500;
	
	Pl_DeltaMouse = 0;

	Pl_MouseX = 0;
	Pl_MouseY = 0;

	Debug_FPS = 1;

	Mouse_X = 0;

	toggleTimer = 0.01;
	ProjectionMove = 0;
	DoProjectionMove = 0;
	Delta = 0;
	ProjectionDirection = 0;

	// Ogre Animation
	Animate_Ogre_KeyFrame = 0;
	Animate_Ogre = 0;
	Animate_State = NULL;
	Animate_State2 = NULL;
	AnimationScale = 1;

	//mCollisionTools = new MOC::CollisionTools(App->Cl_Ogre->mSceneMgr);
	//mCollisionTools->setHeightAdjust(3.5f);
	
}

BT_PhysicsListener::~BT_PhysicsListener(void)
{
}
// *************************************************************************
// *				frameStarted   Terry Bernie							   *
// *************************************************************************
bool BT_PhysicsListener::frameStarted(const FrameEvent& evt)
{
	
	if ( GD_Run_Physics == 1)
	{
		{
			App->GDCL_Bullet->dynamicsWorld->stepSimulation(evt.timeSinceLastFrame*2); //suppose you have 60 frames per second

			//App->GDCL_Player->PostStep(NULL);

			for (int j =App->GDCL_Bullet->dynamicsWorld->getNumCollisionObjects()-1; j>=0 ;j--)
			{
				btCollisionObject* obj = App->GDCL_Bullet->dynamicsWorld->getCollisionObjectArray()[j];
				btRigidBody* body = btRigidBody::upcast(obj);
				btTransform trans;
				if (body && body->getMotionState())
				{
					int UI = body->getUserIndex();
					int Index = body->getUserIndex2();

					/*if (UI == 20)
					{
						body->getMotionState()->getWorldTransform(trans);
						void *userPointer = body->getUserPointer();
						btQuaternion orientation = trans.getRotation();
						App->Cl_Ogre->Test_Node->setPosition(Ogre::Vector3(trans.getOrigin().getX(), trans.getOrigin().getY(), trans.getOrigin().getZ()));
						App->Cl_Ogre->Test_Node->setOrientation(Ogre::Quaternion(orientation.getW(), orientation.getX(), orientation.getY(), orientation.getZ()));
					}*/

					if (UI == Enums::Usage_Dynamic)
					{
						body->getMotionState()->getWorldTransform(trans);
						btQuaternion orientation = trans.getRotation();

						Ogre::Vector3 BB = App->GDCL_Add_Objects->GetMesh_Center(Index,App->GDCL_Scene_Data->S_Object[Index]->OgreNode);
						Ogre::Vector3 WC = App->GDCL_Utilities->Get_BoundingBox_World_Centre(Index);

						float x = trans.getOrigin().getX();
						float y = trans.getOrigin().getY();
						float z = trans.getOrigin().getZ();

						App->GDCL_Scene_Data->S_Object[Index]->OgreNode->setPosition(Ogre::Vector3(x,y,z));
						App->GDCL_Scene_Data->S_Object[Index]->OgreNode->setOrientation(Ogre::Quaternion(orientation.getW(), orientation.getX(), orientation.getY(), orientation.getZ()));
					
						WC = App->GDCL_Utilities->Get_BoundingBox_World_Centre(Index);

						Ogre::Vector3 NewPos = Ogre::Vector3(x,y,z)-WC;
						App->GDCL_Scene_Data->S_Object[Index]->OgreNode->setPosition((Ogre::Vector3(x,y,z))+NewPos);
					}

					/*if (UI == Enums::Usage_Player && App->GDCL_Player->PlayerAdded == 1)
					{
						body->getMotionState()->getWorldTransform(trans);
						void *userPointer = body->getUserPointer();
						btQuaternion orientation = trans.getRotation();
						App->GDCL_Player->Player_Node->setPosition(Ogre::Vector3(trans.getOrigin().getX(), trans.getOrigin().getY(), trans.getOrigin().getZ()));
						App->GDCL_Player->Player_Node->setOrientation(Ogre::Quaternion(orientation.getW(), orientation.getX(), orientation.getY(), orientation.getZ()));
						App->GDCL_Player->Player_Node->pitch(Ogre::Degree(180));
					}*/
				} else
				{
					trans = obj->getWorldTransform();
				}
			}
		}

		if (GD_Run_Physics == 1 && App->GDCL_Scene_Data->Player_Added == 1)
		{
			btTransform trans;
			App->GDCL_Scene_Data->B_Player[0]->Phys_Body->getMotionState()->getWorldTransform(trans);
			btQuaternion orientation = trans.getRotation();
			App->GDCL_Scene_Data->B_Player[0]->Player_Node->setPosition(Ogre::Vector3(trans.getOrigin().getX(), trans.getOrigin().getY(), trans.getOrigin().getZ()));
			App->GDCL_Scene_Data->B_Player[0]->Player_Node->setOrientation(Ogre::Quaternion(orientation.getW(), orientation.getX(), orientation.getY(), orientation.getZ()));
			App->GDCL_Scene_Data->B_Player[0]->Player_Node->pitch(Ogre::Degree(180));
		}
	}
	return true;
}
// *************************************************************************
// *				frameEnded   Terry Bernie							   *
// *************************************************************************
bool BT_PhysicsListener::frameEnded(const FrameEvent& evt)
{
	if (StopOgre == 1)
	{
		return false;
	}

	return true;
}
// *************************************************************************
// *			frameRenderingQueued   Terry Bernie						   *
// *************************************************************************
bool  BT_PhysicsListener::frameRenderingQueued(const FrameEvent& evt)
{
	if (GetAsyncKeyState(VK_ESCAPE) < 0) // Back to full Screen;
	{
		StopOgre = 1;
	}

	mRotX = 0;
	mRotY = 0;
	mTranslateVector = Ogre::Vector3::ZERO;

	
	mMoveScale = mMoveSensitivity  * evt.timeSinceLastFrame;

	if (GD_CameraMode == Enums::CamFirst)
	{
		
		Ogre::Vector3 Pos;
		Ogre::Radian mmPitch;
		Ogre::Radian mYaw;

		Pos = App->GDCL_Scene_Data->B_Player[0]->Player_Node->getPosition();

		mmPitch = App->GDCL_Scene_Data->B_Player[0]->CameraPitch->getOrientation().getPitch();
		mYaw = App->GDCL_Scene_Data->B_Player[0]->Player_Node->getOrientation().getYaw();
		Pos.y = Pos.y + App->GDCL_Scene_Data->B_Player[0]->PlayerHeight;

		App->Ogre17->mCamera->setPosition(Pos);
		App->Ogre17->mCamera->setOrientation(Ogre::Quaternion(1, 0, 0, 0));
		App->Ogre17->mCamera->yaw(mYaw);
		App->Ogre17->mCamera->pitch(mmPitch);
		App->Ogre17->mCamera->yaw(Ogre::Degree(180));
	}

	//------------------------------------------------ Jump and Selection
	//if (GetAsyncKeyState(VK_SPACE) < 0 && App->GDCL_Player->PlayerAdded == 1) 
	{
		//App->GDCL_Player->Jump(Ogre::Vector3(1,1,0),1.2);
	}

	
	//------------------------------------------------ Forward
	//if (GetAsyncKeyState(VK_UP) < 0 && App->GDCL_Player->PlayerAdded == 1 && GD_CameraMode == Enums::CamDetached) 
	{
		//App->GDCL_Player->Forward();
		//App->GDCL_Player->IsMOving = 1;
	}
	//else 
	{
		//if(App->GDCL_Player->PlayerAdded == 1 && App->GDCL_Player->IsMOving == 1 && GD_CameraMode == Enums::CamDetached)
		{
			//App->GDCL_Player->Stop();
			//App->GDCL_Player->IsMOving = 0;
		}
	}
	//------------------------------------------------ Back
	//if (GetAsyncKeyState(VK_DOWN) < 0 && App->GDCL_Player->PlayerAdded == 1 && GD_CameraMode == Enums::CamDetached) 
	{
		//App->GDCL_Player->Back();
		//App->GDCL_Player->IsMOving_Back = 1;
	}
	//else 
	{
		//if(App->GDCL_Player->PlayerAdded == 1 && App->GDCL_Player->IsMOving_Back == 1 && GD_CameraMode == Enums::CamDetached)
		{
			//App->GDCL_Player->Stop();
			//App->GDCL_Player->IsMOving_Back = 0;
		}
	}
	
	//------------------------------------------------ Turn Right
	/*if (GetAsyncKeyState(VK_RIGHT) < 0 && App->GDCL_Player->PlayerAdded == 1) 
	{
		toggleTimer -= evt.timeSinceLastFrame;

		if (toggleTimer < 0)
		{
			Ogre::Vector3 Rotate;
			Rotate.x = 0;
			Rotate.y = 1;
			Rotate.z = 0;

			float Delta = App->GDCL_Utilities->DegreesToRadians(1);

			App->GDCL_Player->Rotate(Rotate,false);

			toggleTimer = 0.01;
		}
	}*/

	//------------------------------------------------ Turn Left
	/*if (GetAsyncKeyState(VK_LEFT) < 0 && App->GDCL_Player->PlayerAdded == 1) 
	{
		toggleTimer -= evt.timeSinceLastFrame;

		if (toggleTimer < 0)
		{
			Ogre::Vector3 Rotate;
			Rotate.x = 0;
			Rotate.y = -1;
			Rotate.z = 0;

			float Delta = App->GDCL_Utilities->DegreesToRadians(1);

			App->GDCL_Player->Rotate(Rotate,false);

			toggleTimer = 0.01;
		}
	}*/

	
	if (GetAsyncKeyState(69) < 0) // Q key Down in Fly Mode
	{
		App->SBC_Physics->Enable_Physics(1); //App->Ogre17->PhysicsFrameListener->GD_Run_Physics = 1;
		GD_CameraMode = Enums::CamFirst;
	}
	////------------------------------------------------
	//if (GetAsyncKeyState(81) < 0) // E key Up in Fly Mode
	//{
	//	Ogre::Real Rate;
	//	Rate = (mMoveSensitivity/1000)*2;// 0.1;//FlyRate;

	//	Ogre::Vector3 OldPos;
	//	OldPos=mCam->getPosition();

	//	OldPos.y -= Rate;
	//	mCam->setPosition(OldPos);
	//}
	//------------------------------------------------
	//if (Wheel < 0) // Mouse Wheel Forward
	//{
	//	if(GD_CameraMode == Enums::CamDetached)
	//	{
	//		mTranslateVector.z = -mMoveScale *30;
	//	}
	//	else
	//	{
	//		if (App->GDCL_Player->PlayerAdded == 1) 
	//		{
	//			App->GDCL_Player->IsMOving = 1;
	//			App->GDCL_Player->Forward();
	//		}
	//		else 
	//		{
	//			if(App->GDCL_Player->IsMOving == 1)
	//			{
	//				App->GDCL_Player->Stop();
	//				App->GDCL_Player->IsMOving = 0;
	//			}
	//		}
	//	}
	//}

	//------------------------------------------------ Forward
	if (GetAsyncKeyState(87) < 0) // W Key
	{
		if (GD_CameraMode == Enums::CamDetached)
		{
			mTranslateVector.z = -mMoveScale;
		}
		else
		{
			if (App->GDCL_Scene_Data->Player_Added == 1)
			{

				App->GDCL_Scene_Data->B_Player[0]->Forward(evt.timeSinceLastFrame);
				App->GDCL_Scene_Data->B_Player[0]->IsMOving = 1;
			}
		}
	}
	else
	{
		if (GD_CameraMode == Enums::CamDetached)
		{

		}
		else if (App->GDCL_Scene_Data->Player_Added == 1 && App->GDCL_Scene_Data->B_Player[0]->IsMOving == 1)
		{
			App->GDCL_Scene_Data->B_Player[0]->Stop();
			App->GDCL_Scene_Data->B_Player[0]->IsMOving = 0;
		}
	}
	
	//if (Wheel > 0) // Mouse Wheel Back
	//{
	//	if(GD_CameraMode == Enums::CamDetached)
	//	{
	//		mTranslateVector.z = mMoveScale *30;
	//	}
	//	else
	//	{
	//		if (App->GDCL_Player->PlayerAdded == 1) 
	//		{
	//			App->GDCL_Player->Back();
	//		}
	//	}
	//}

	//------------------------------------------------ Back
	if (GetAsyncKeyState(83) < 0) // S Key	
	{

		if (GD_CameraMode == Enums::CamDetached)
		{
			mTranslateVector.z = mMoveScale;
		}
		else
		{
			if (App->GDCL_Scene_Data->Player_Added == 1)
			{
				App->GDCL_Scene_Data->B_Player[0]->Back();
				App->GDCL_Scene_Data->B_Player[0]->IsMOving_Back = 1;
			}
		}
	}
	else
	{
		if (GD_CameraMode == Enums::CamDetached)
		{

		}
		else if (App->GDCL_Scene_Data->Player_Added == 1 && App->GDCL_Scene_Data->B_Player[0]->IsMOving_Back == 1)
		{
			App->GDCL_Scene_Data->B_Player[0]->Stop();
			App->GDCL_Scene_Data->B_Player[0]->IsMOving_Back = 0;
		}
	}

	//------------------------------------------------
	// Right
	if (GetAsyncKeyState(65) < 0)
	{
		if (GD_CameraMode == Enums::CamDetached)
		{
			mTranslateVector.x = -mMoveScale;
		}
		else
		{
			if (App->GDCL_Scene_Data->Player_Added == 1)
			{
				App->GDCL_Scene_Data->B_Player[0]->Move_Right();
				App->GDCL_Scene_Data->B_Player[0]->IsMOving_Right = 1;
			}
		}
	}
	else
	{
		if (GD_CameraMode == Enums::CamDetached)
		{

		}
		else if (App->GDCL_Scene_Data->Player_Added == 1 && App->GDCL_Scene_Data->B_Player[0]->IsMOving_Right == 1)
		{
			App->GDCL_Scene_Data->B_Player[0]->Stop();
			App->GDCL_Scene_Data->B_Player[0]->IsMOving_Right = 0;
		}
	}

	// Left
	if (GetAsyncKeyState(68) < 0)
	{
		if (GD_CameraMode == Enums::CamDetached)
		{
			mTranslateVector.x = mMoveScale;
		}
		else
		{
			if (App->GDCL_Scene_Data->Player_Added == 1)
			{
				App->GDCL_Scene_Data->B_Player[0]->Move_Left();
				App->GDCL_Scene_Data->B_Player[0]->IsMOving_Left = 1;
			}
		}
	}
	else
	{
		if (GD_CameraMode == Enums::CamDetached)
		{

		}
		else if (App->GDCL_Scene_Data->Player_Added == 1 && App->GDCL_Scene_Data->B_Player[0]->IsMOving_Left == 1)
		{
			App->GDCL_Scene_Data->B_Player[0]->Stop();
			App->GDCL_Scene_Data->B_Player[0]->IsMOving_Left = 0;
		}
	}


	if (GetAsyncKeyState(VK_ESCAPE) < 0) // Back to full Screen;
	{
		StopOgre = 1;
	}

	//// Left Mouse
	if(Pl_LeftMouseDown == 1 && Pl_RightMouseDown == 0)
	{
		if(GD_CameraMode == Enums::CamFirst)
		{
			Capture_Mouse_FirstPerson();
			SetCursorPos(500,500);
		}
		else if(GD_CameraMode == Enums::CamNone)
		{
			Capture_LeftMouse();
		}
		else
		{
			Capture_Mouse_Free();
		}
	}

	if(Pl_LeftMouseDown == 1 && GD_CameraMode == Enums::CamDetached)
	{
		SetCursorPos(500,500);
	}

	MoveCamera();

	if (App->GDCL_Collision->DoMove == 1)
	{
		App->GDCL_Collision->MoveObject(evt.timeSinceLastFrame);
	}
	return 1;
}

// *************************************************************************
// *				moveCamera   Terry Bernie							   *
// *************************************************************************
void BT_PhysicsListener::MoveCamera(void)
{
	mCam->yaw(mRotX);
	mCam->pitch(mRotY);   
	mCam->moveRelative(mTranslateVector); // Position Relative
	Wheel = 0;
}

// *************************************************************************
// *				Capture_LeftMouse   Terry Bernie					   *
// *************************************************************************
bool BT_PhysicsListener::Capture_LeftMouse(void)
{
	//GetCursorPos(&Pl_pt);

	//Pl_MouseX = (int(Pl_pt.x));
	//Pl_MouseY = (int(Pl_pt.y));

	////// Left Right
	//if(Pl_MouseX < Pl_Cent500X)
	//{
	//	long test = Pl_Cent500X - Pl_MouseX; // Positive

	//	if (test > 2)
	//	{
	//		Pl_DeltaMouse = float(Pl_Cent500X - Pl_MouseX);
	//		App->Cl_Grid->GridNode->yaw(Ogre::Degree(-Pl_DeltaMouse * (mMoveSensitivityMouse/1000)*2),Ogre::Node::TS_LOCAL);
	//		App->Cl_Grid->HairNode->yaw(Ogre::Degree(-Pl_DeltaMouse * (mMoveSensitivityMouse/1000)*2),Ogre::Node::TS_LOCAL);
	//		App->Cl_Grid->DummyNode->yaw(Ogre::Degree(-Pl_DeltaMouse * (mMoveSensitivityMouse/1000)*2),Ogre::Node::TS_LOCAL);
	//		App->Cl_Ogre->RenderListener->RZ = App->Cl_Ogre->RenderListener->RZ -(Pl_DeltaMouse * (mMoveSensitivityMouse/1000)*2);
	//		SetCursorPos(500,500);
	//	}
	//}
	//else if(Pl_MouseX > Pl_Cent500X)
	//{
	//	long test = Pl_MouseX - Pl_Cent500X; // Positive

	//	if (test > 2)
	//	{
	//		Pl_DeltaMouse = float(Pl_MouseX - Pl_Cent500X);
	//		App->Cl_Grid->GridNode->yaw(Ogre::Degree(Pl_DeltaMouse * (mMoveSensitivityMouse/1000)*2),Ogre::Node::TS_LOCAL);
	//		App->Cl_Grid->HairNode->yaw(Ogre::Degree(Pl_DeltaMouse * (mMoveSensitivityMouse/1000)*2),Ogre::Node::TS_LOCAL);
	//		App->Cl_Grid->DummyNode->yaw(Ogre::Degree(Pl_DeltaMouse * (mMoveSensitivityMouse/1000)*2),Ogre::Node::TS_LOCAL);
	//		App->Cl_Ogre->RenderListener->RZ = App->Cl_Ogre->RenderListener->RZ +(Pl_DeltaMouse * (mMoveSensitivityMouse/1000)*2);
	//		SetCursorPos(500,500);
	//	}
	//}

	//// Up Down
	//if(Pl_MouseY < Pl_Cent500Y)
	//{
	//	long test = Pl_Cent500Y - Pl_MouseY; // Positive

	//	if (test > 2)
	//	{
	//		Pl_DeltaMouse = float(Pl_Cent500Y - Pl_MouseY);
	//		App->Cl_Grid->GridNode->pitch(Ogre::Degree(-Pl_DeltaMouse * (mMoveSensitivityMouse/1000)*2),Ogre::Node::TS_PARENT);
	//		App->Cl_Grid->HairNode->pitch(Ogre::Degree(-Pl_DeltaMouse * (mMoveSensitivityMouse/1000)*2),Ogre::Node::TS_PARENT);
	//		App->Cl_Grid->DummyNode->pitch(Ogre::Degree(-Pl_DeltaMouse * (mMoveSensitivityMouse/1000)*2),Ogre::Node::TS_PARENT);
	//		App->Cl_Ogre->RenderListener->RX = App->Cl_Ogre->RenderListener->RX -(Pl_DeltaMouse * (mMoveSensitivityMouse/1000)*2);
	//		SetCursorPos(500,500);
	//	}
	//}
	//else if(Pl_MouseY > Pl_Cent500Y)
	//{
	//	long test = Pl_MouseY - Pl_Cent500Y; // Positive

	//	if (test > 2)
	//	{
	//		Pl_DeltaMouse = float(Pl_MouseY - Pl_Cent500Y);
	//		App->Cl_Grid->GridNode->pitch(Ogre::Degree(Pl_DeltaMouse * (mMoveSensitivityMouse/1000)*2),Ogre::Node::TS_PARENT);
	//		App->Cl_Grid->HairNode->pitch(Ogre::Degree(Pl_DeltaMouse * (mMoveSensitivityMouse/1000)*2),Ogre::Node::TS_PARENT);
	//		App->Cl_Grid->DummyNode->pitch(Ogre::Degree(Pl_DeltaMouse * (mMoveSensitivityMouse/1000)*2),Ogre::Node::TS_PARENT);
	//		App->Cl_Ogre->RenderListener->RX = App->Cl_Ogre->RenderListener->RX +(Pl_DeltaMouse * (mMoveSensitivityMouse/1000)*2);
	//		SetCursorPos(500,500);
	//	}
	//}

	return 1;
}
// *************************************************************************
// *				Capture_RightMouse   Terry Bernie					   *
// *************************************************************************
bool BT_PhysicsListener::Capture_RightMouse(void)
{
	/*if (App->GDCL_Dialogs->Mouse_Move_Mode == Enums::Edit_Mouse_Active)
	{
		return 1;
	}*/

	if(GD_CameraMode == Enums::CamFirst)
	{
		return 1;
	}

	GetCursorPos(&Pl_pt);

	Pl_MouseX = (int(Pl_pt.x));
	Pl_MouseY = (int(Pl_pt.y));

	//// Left Right
	if(Pl_MouseX < Pl_Cent500X)
	{
		long test = Pl_Cent500X - Pl_MouseX; // Positive

		if (test > 2)
		{
			Pl_DeltaMouse = float(Pl_Cent500X - Pl_MouseX);
			mTranslateVector.x = Pl_DeltaMouse * (mMoveSensitivityMouse/1000);
			SetCursorPos(500,500);
		}
	}
	else if(Pl_MouseX > Pl_Cent500X)
	{
		long test = Pl_MouseX - Pl_Cent500X; // Positive

		if (test > 2)
		{
			Pl_DeltaMouse = float(Pl_MouseX - Pl_Cent500X);
			mTranslateVector.x = -Pl_DeltaMouse * (mMoveSensitivityMouse/1000);
			SetCursorPos(500,500);
		}
	}

	//// Up Down
	if(Pl_MouseY < Pl_Cent500Y)
	{
		long test = Pl_Cent500Y - Pl_MouseY; // Positive

		if (test > 2)
		{
			Pl_DeltaMouse = float(Pl_Cent500Y - Pl_MouseY);

			Ogre::Real Rate;
			Rate = Pl_DeltaMouse * (mMoveSensitivityMouse/1000);

			Ogre::Vector3 OldPos;
			OldPos=mCam->getPosition();

			OldPos.y -= Rate;
			mCam->setPosition(OldPos);
			SetCursorPos(500,500);
		}

	}
	else if(Pl_MouseY > Pl_Cent500Y)
	{
		long test = Pl_MouseY - Pl_Cent500Y; // Positive

		if (test > 2)
		{
			Pl_DeltaMouse = float(Pl_MouseY - Pl_Cent500Y);

			Ogre::Real Rate;
			Rate = Pl_DeltaMouse * (mMoveSensitivityMouse/1000);

			Ogre::Vector3 OldPos;
			OldPos = mCam->getPosition();

			OldPos.y += Rate;
			mCam->setPosition(OldPos);
			SetCursorPos(500,500);
		}

	}

	return 1;
}

// *************************************************************************
// *				Capture_Mouse_FirstPerson   Terry Bernie			   *
// *************************************************************************
bool BT_PhysicsListener::Capture_Mouse_FirstPerson(void)
{

	/*if (Stop_PhysX_Render==0)
	{*/
		GetCursorPos(&Pl_pt);

		Pl_MouseX = (int(Pl_pt.x));
		Pl_MouseY = (int(Pl_pt.y));

		// Left Right
		if(Pl_MouseX < Pl_Cent500X)
		{
			long test = Pl_Cent500X - Pl_MouseX; // Positive
			if (test > 1)
			{
				Pl_DeltaMouse = float(Pl_Cent500X - Pl_MouseX);

				Ogre::Vector3 Rotate;
				Rotate.x = 0;
				Rotate.y = -1;
				Rotate.z = 0;

				//float mTurn = ((float)App->GDCL_Scene_Data->B_Player[0]->TurnRate*Pl_DeltaMouse);
				float mTurn = (Pl_DeltaMouse * (float)0.00040);
				App->GDCL_Scene_Data->B_Player[0]->Rotate_FromCam(Rotate, mTurn, false);

			}
		}
		else if(Pl_MouseX > Pl_Cent500X)
		{
			long test = Pl_MouseX - Pl_Cent500X; // Positive

			if (test > 1)
			{
				Pl_DeltaMouse = float(Pl_MouseX - Pl_Cent500X);

				Ogre::Vector3 Rotate;
				Rotate.x = 0;
				Rotate.y = 1;
				Rotate.z = 0;
				
				float mTurn = (Pl_DeltaMouse * (float)0.00040 );
				App->GDCL_Scene_Data->B_Player[0]->Rotate_FromCam(Rotate, mTurn, false);
			}
		}

		//Up Down
		if (Pl_MouseY < Pl_Cent500Y)
		{
			long test = Pl_Cent500Y - Pl_MouseY; // Positive

			if (test > 2)
			{
				Pl_DeltaMouse = float(Pl_Cent500Y - Pl_MouseY);
				Ogre::Radian pp = Degree(Pl_DeltaMouse * (float)0.03);
				App->GDCL_Scene_Data->B_Player[0]->CameraPitch->pitch(pp);
			}
		}
		else if (Pl_MouseY > Pl_Cent500Y)
		{
			long test = Pl_MouseY - Pl_Cent500Y; // Positive

			if (test > 2)
			{
				Pl_DeltaMouse = float(Pl_MouseY - Pl_Cent500Y);
				Ogre::Radian pp = Degree(-Pl_DeltaMouse * (float)0.03);
				App->GDCL_Scene_Data->B_Player[0]->CameraPitch->pitch(pp);
			}
		}

	//	MoveCamera();
	//}
	return 1;
}

// *************************************************************************
// *				Capture_Mouse_Free   Terry Bernie						   *
// *************************************************************************
bool BT_PhysicsListener::Capture_Mouse_Free(void)
{
	
	/*if (Stop_PhysX_Render==0)
	{*/
		GetCursorPos(&Pl_pt);

		Pl_MouseX = (int(Pl_pt.x));
		Pl_MouseY = (int(Pl_pt.y));

		// Left Right
		if(Pl_MouseX < Pl_Cent500X)
		{
			long test = Pl_Cent500X - Pl_MouseX; // Positive
			if (test > 2)
			{
				Pl_DeltaMouse = float(Pl_Cent500X - Pl_MouseX);
				mRotX = Degree(Pl_DeltaMouse * (float)0.03);//S_Player[0]->TurnRate);
			}
		}
		else if(Pl_MouseX > Pl_Cent500X)
		{
			long test = Pl_MouseX - Pl_Cent500X; // Positive

			if (test > 2)
			{
				Pl_DeltaMouse = float(Pl_MouseX - Pl_Cent500X);
				mRotX = Degree(-Pl_DeltaMouse * (float)0.03);//S_Player[0]->TurnRate);
			}
		}

		// Up Down
		if(Pl_MouseY < Pl_Cent500Y)
		{
			long test = Pl_Cent500Y - Pl_MouseY; // Positive

			if (test > 2)
			{
				Pl_DeltaMouse = float(Pl_Cent500Y - Pl_MouseY);
				mRotY = Degree(Pl_DeltaMouse * (float)0.03);//S_Player[0]->TurnRate);
			}
		}
		else if(Pl_MouseY > Pl_Cent500Y)
		{
			long test = Pl_MouseY - Pl_Cent500Y; // Positive

			if (test > 2)
			{
				Pl_DeltaMouse = float(Pl_MouseY - Pl_Cent500Y);
				mRotY = Degree(-Pl_DeltaMouse * (float)0.03);//S_Player[0]->TurnRate);
			}
		}

	//	MoveCamera();
	//}
	return 1;
}

// *************************************************************************
// *					showDebugOverlay   Terry Bernie					   *
// *************************************************************************
void BT_PhysicsListener::showDebugOverlay(bool show)
{
	if (mDebugOverlay)
	{
		if (show)
			mDebugOverlay->show();
		else
			mDebugOverlay->hide();
	}
}


