/*
Copyright (c) 2022 - 2023 GameDirectorSB and EquityME -- HGTInflanite Software W.T.Flanigan H.C.Flanigan

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
#include "WV_App.h"
#include "WV_Keyboard.h"


WV_Keyboard::WV_Keyboard()
{
	Rate = 0;
	OldPos.ZERO;
	Block_Keyboard = 0;

}


WV_Keyboard::~WV_Keyboard()
{
}

// *************************************************************************
// *						Keyboard_Mode_Model							   *
// *************************************************************************
void WV_Keyboard::Keyboard_Mode_Model(float deltaTime)
{
	//	Pan Up
	if (GetAsyncKeyState(69) < 0) // E key 
	{
		Ogre::Real Rate;
		Rate = (App->CL_Ogre->OgreListener->mMoveSensitivity / 1000) * 2;

		Ogre::Vector3 OldPos;
		OldPos = App->CL_Ogre->OgreListener->mCam->getPosition();

		OldPos.y += Rate;
		App->CL_Ogre->OgreListener->mCam->setPosition(OldPos);
	}

	// Pan Down
	if (GetAsyncKeyState(81) < 0)  // Q Key
	{
		Ogre::Real Rate;
		Rate = (App->CL_Ogre->OgreListener->mMoveSensitivity / 1000) * 2;

		Ogre::Vector3 OldPos;
		OldPos = App->CL_Ogre->OgreListener->mCam->getPosition();

		OldPos.y -= Rate;
		App->CL_Ogre->OgreListener->mCam->setPosition(OldPos);
	}

	// Forward
	if (App->CL_Ogre->OgreListener->Wheel < 0) // Mouse Wheel Forward
	{
		App->CL_Ogre->OgreListener->mTranslateVector.z = -App->CL_Ogre->OgreListener->mMoveScale * 30;
	}
	if (GetAsyncKeyState(87) < 0) // W Key
	{
		App->CL_Ogre->OgreListener->mTranslateVector.z = -App->CL_Ogre->OgreListener->mMoveScale;
	}
	
	// Back
	if (App->CL_Ogre->OgreListener->Wheel > 0) // Mouse Wheel Back
	{
		App->CL_Ogre->OgreListener->mTranslateVector.z = App->CL_Ogre->OgreListener->mMoveScale * 30;
	}
	if (GetAsyncKeyState(83) < 0) // S Key	
	{
		App->CL_Ogre->OgreListener->mTranslateVector.z = App->CL_Ogre->OgreListener->mMoveScale;
	}

	// Pan Left
	if (GetAsyncKeyState(65) < 0) // A Key
	{
		App->CL_Ogre->OgreListener->mTranslateVector.x = App->CL_Ogre->OgreListener->mMoveScale;
	}

	// Pan Right
	if (GetAsyncKeyState(68) < 0)  // D Key
	{
		App->CL_Ogre->OgreListener->mTranslateVector.x = -App->CL_Ogre->OgreListener->mMoveScale;
	}
}

// *************************************************************************
// *						Keyboard_Mode_Free							   *
// *************************************************************************
void WV_Keyboard::Keyboard_Mode_Free(float deltaTime)
{
	// Forward
	if (GetAsyncKeyState(87) < 0) // W Key
	{
		if (App->CL_Ogre->OgreListener->CameraMode == Enums::CamDetached)
		{
			App->CL_Ogre->OgreListener->mTranslateVector.z = -App->CL_Ogre->OgreListener->mMoveScale;
		}

		App->CL_SplitterViews->Update_Views();
	}

	// Back
	if (GetAsyncKeyState(83) < 0) // S Key	
	{
		if (App->CL_Ogre->OgreListener->CameraMode == Enums::CamDetached)
		{
			App->CL_Ogre->OgreListener->mTranslateVector.z = App->CL_Ogre->OgreListener->mMoveScale;
		}

		App->CL_SplitterViews->Update_Views();
	}

	// Pan Down
	if (GetAsyncKeyState(81) < 0) // Q Key	
	{
		if (App->CL_Ogre->OgreListener->CameraMode == Enums::CamDetached)
		{
			Rate = (App->CL_Ogre->OgreListener->mMoveSensitivity / 1000) * 2; //FlyRate;

			OldPos = App->CL_Ogre->OgreListener->mCam->getPosition();

			OldPos.y -= Rate;

			App->CL_Ogre->OgreListener->mCam->setPosition(OldPos);
		}

		App->CL_SplitterViews->Update_Views();
	}

	//	Pan Up
	if (GetAsyncKeyState(69) < 0) // E Key
	{
		if (App->CL_Ogre->OgreListener->CameraMode == Enums::CamDetached)
		{
			Rate = (App->CL_Ogre->OgreListener->mMoveSensitivity / 1000) * 2; //FlyRate;

			OldPos = App->CL_Ogre->OgreListener->mCam->getPosition();

			OldPos.y += Rate;

			App->CL_Ogre->OgreListener->mCam->setPosition(OldPos);
		}

		App->CL_SplitterViews->Update_Views();
	}

	// Pan Left
	if (GetAsyncKeyState(65) < 0) // A Key
	{
		if (App->CL_Ogre->OgreListener->CameraMode == Enums::CamDetached)
		{
			App->CL_Ogre->OgreListener->mTranslateVector.x = -App->CL_Ogre->OgreListener->mMoveScale;
		}

		App->CL_SplitterViews->Update_Views();
	}

	// Pan Right
	if (GetAsyncKeyState(68) < 0) // D Key
	{
		if (App->CL_Ogre->OgreListener->CameraMode == Enums::CamDetached)
		{
			App->CL_Ogre->OgreListener->mTranslateVector.x = App->CL_Ogre->OgreListener->mMoveScale;
		}

		App->CL_SplitterViews->Update_Views();
	}

}


// *************************************************************************
// *					Keyboard_Mode_First Terry						   *
// *************************************************************************
void WV_Keyboard::Keyboard_Mode_First(float deltaTime)
{
	//if (Block_Keyboard == 0)
	//{
		/*if (App->SBC_3DT->timeUntilNextToggle >= 0)
		{
			App->SBC_3DT->timeUntilNextToggle -= deltaTime;
		}
		

		------------------------------------------------ Space Key - Jump and Selection
		if (GetAsyncKeyState(VK_SPACE) < 0 && App->SBC_Scene->Player_Added == 1)
		{
			if (App->CL_Ogre->OgreListener->GD_Selection_Mode == 0)
			{
				if (App->CL_Ogre->OgreListener->GD_Run_Physics == 1)
				{
					App->SBC_DCC->jump();
				}
			}
			else
			{
				App->CL_Ogre->OgreListener->SelectEntity_World();
			}
		}*/

		/*------------------------------------------------ Y Key
		if (GetAsyncKeyState(89) < 0)
		{
			if (App->CL_Vm_ImGui->Show_Object_Selection == 1)
			{
				App->SBC_TopTabs->Toggle_Select_Flag = 0;
				App->SBC_Markers->mPickSight->hide();
				App->CL_Ogre->OgreListener->GD_Selection_Mode = 0;

				RedrawWindow(App->SBC_TopTabs->Camera_TB_hWnd, NULL, NULL, RDW_INVALIDATE | RDW_UPDATENOW);

				App->SBC_FileView->SelectItem(App->SBC_Scene->V_Object[App->CL_Ogre->OgreListener->Selected_Entity_Index]->FileViewItem);
				App->CL_Vm_ImGui->Show_Object_Selection = 0;
			}
		}*/

	//	------------------------------------------------ N Key
	//	if (GetAsyncKeyState(78) < 0)
	//	{
	//		if (App->CL_Vm_ImGui->Show_Object_Selection == 1)
	//		{
	//			App->SBC_TopTabs->Toggle_Select_Flag = 0;
	//			App->SBC_Markers->mPickSight->hide();
	//			App->CL_Ogre->OgreListener->GD_Selection_Mode = 0;

	//			RedrawWindow(App->SBC_TopTabs->Camera_TB_hWnd, NULL, NULL, RDW_INVALIDATE | RDW_UPDATENOW);

	//			App->CL_Vm_ImGui->Show_Object_Selection = 0;
	//		}
	//	}

	//	------------------------------------------------ Forward
		if (GetAsyncKeyState(VK_UP) < 0 && App->CL_Scene->Player_Added == 1 && App->CL_Ogre->OgreListener->GD_CameraMode == Enums::CamDetached)
		{
			if (App->CL_Scene->Player_Added == 1)
			{
				App->CL_DCC->mMoveDirection = (btVector3(0, 0, -1));// walkDirection
				//App->CL_Player->Check_Collisions_New();
				App->CL_Scene->B_Player[0]->IsMOving = 1;
			}
		}
		else
		{
			if (App->CL_Scene->Player_Added == 1 && App->CL_Scene->B_Player[0]->IsMOving == 1 && App->CL_Ogre->OgreListener->GD_CameraMode == Enums::CamDetached)
			{
				App->CL_DCC->mMoveDirection = (btVector3(0, 0, 0));// walkDirection
				App->CL_Scene->B_Player[0]->IsMOving = 0;
			}
		}
	//	------------------------------------------------ Back
	//	if (GetAsyncKeyState(VK_DOWN) < 0 && App->SBC_Scene->Player_Added == 1 && App->CL_Ogre->OgreListener->GD_CameraMode == Enums::CamDetached)
	//	{
	//		App->SBC_DCC->mMoveDirection = (btVector3(0, 0, 1));// walkDirection
	//		App->SBC_Scene->B_Player[0]->IsMOving_Back = 1;
	//	}
	//	else
	//	{
	//		if (App->SBC_Scene->Player_Added == 1 && App->SBC_Scene->B_Player[0]->IsMOving_Back == 1 && App->CL_Ogre->OgreListener->GD_CameraMode == Enums::CamDetached)
	//		{
	//			App->SBC_DCC->mMoveDirection = (btVector3(0, 0, 0));// walkDirection
	//			App->SBC_Scene->B_Player[0]->IsMOving_Back = 0;
	//		}
	//	}

	//	------------------------------------------------ Turn Right
	//	if (GetAsyncKeyState(VK_RIGHT) < 0 && App->SBC_Scene->Player_Added == 1)
	//	{
	//		App->CL_Ogre->OgreListener->toggleTimer -= deltaTime;

	//		if (App->CL_Ogre->OgreListener->toggleTimer < 0)
	//		{
	//			Ogre::Vector3 Rotate;
	//			Rotate.x = 0;
	//			Rotate.y = 1;
	//			Rotate.z = 0;

	//			float Delta = App->Cl_Utilities->DegreesToRadians(1);

	//			App->SBC_Scene->B_Player[0]->Rotate_FromCam(Rotate, 0.001, false);

	//			App->CL_Ogre->OgreListener->toggleTimer = 0.01;
	//		}
	//	}

	//	------------------------------------------------ Turn Left
	//	if (GetAsyncKeyState(VK_LEFT) < 0 && App->SBC_Scene->Player_Added == 1)
	//	{
	//		App->CL_Ogre->OgreListener->toggleTimer -= deltaTime;

	//		if (App->CL_Ogre->OgreListener->toggleTimer < 0)
	//		{
	//			Ogre::Vector3 Rotate;
	//			Rotate.x = 0;
	//			Rotate.y = -1;
	//			Rotate.z = 0;

	//			float Delta = App->Cl_Utilities->DegreesToRadians(1);

	//			App->SBC_Scene->B_Player[0]->Rotate_FromCam(Rotate, 0.001, false);

	//			App->CL_Ogre->OgreListener->toggleTimer = 0.01;
	//		}
	//	}

	//	------------------------------------------------ E key Up in Fly Mode
	//	if (GetAsyncKeyState(69) < 0)
	//	{
	//		if (App->CL_Ogre->OgreListener->GD_CameraMode == Enums::CamDetached)
	//		{
	//			Rate = (App->CL_Ogre->OgreListener->mMoveSensitivity / 1000) * 2; //FlyRate;

	//			OldPos = App->CL_Ogre->OgreListener->mCam->getPosition();

	//			OldPos.y += Rate;

	//			App->CL_Ogre->OgreListener->mCam->setPosition(OldPos);
	//		}
	//		else
	//		{
	//			if (App->SBC_3DT->timeUntilNextToggle <= 0)
	//			{
	//				App->SBC_3DT->Fire(deltaTime);
	//				App->SBC_3DT->timeUntilNextToggle = 0.5;
	//			}
	//		}
	//	}

	//	------------------------------------------------ Q key Down in Fly Mode
	//	if (GetAsyncKeyState(81) < 0)
	//	{
	//		if (App->CL_Ogre->OgreListener->GD_CameraMode == Enums::CamDetached)
	//		{
	//			Rate = (App->CL_Ogre->OgreListener->mMoveSensitivity / 1000) * 2; //FlyRate;

	//			OldPos = App->CL_Ogre->OgreListener->mCam->getPosition();

	//			OldPos.y -= Rate;

	//			App->CL_Ogre->OgreListener->mCam->setPosition(OldPos);
	//		}
	//	}
	//	------------------------------------------------
	//	if (App->CL_Ogre->OgreListener->Wheel < 0) // Mouse Wheel Forward
	//	{
	//		if (App->CL_Ogre->OgreListener->GD_CameraMode == Enums::CamDetached)
	//		{
	//			App->CL_Ogre->OgreListener->mTranslateVector.z = -App->CL_Ogre->OgreListener->mMoveScale * 30;
	//		}
	//		/*else
	//		{
	//			if (App->SBC_Player->PlayerAdded == 1)
	//			{
	//				App->SBC_Player->IsMOving = 1;
	//				App->SBC_Player->Forward(deltaTime);
	//			}
	//			else
	//			{
	//				if (App->SBC_Player->IsMOving == 1)
	//				{
	//					App->SBC_Player->Stop();
	//					App->SBC_Player->IsMOving = 0;
	//				}
	//			}
	//		}*/
	//	}

		//	------------------------------------------------ Move Forward
		if (GetAsyncKeyState(87) < 0) // W Key
		{

			if (App->CL_Scene->Player_Added == 1)
			{
				App->CL_DCC->mMoveDirection = (btVector3(0, 0, -1));
				//App->CL_Player->Check_Collisions_New();
				App->CL_Scene->B_Player[0]->IsMOving = 1;
			}
			
		}
		else
		{
			if (App->CL_Scene->Player_Added == 1 && App->CL_Scene->B_Player[0]->IsMOving == 1)
			{
				App->CL_DCC->mMoveDirection = (btVector3(0, 0, 0));
				App->CL_Scene->B_Player[0]->IsMOving = 0;
			}
		}
		
	//	if (App->CL_Ogre->OgreListener->Wheel > 0) // Mouse Wheel Back
	//	{
	//		if (App->CL_Ogre->OgreListener->GD_CameraMode == Enums::CamDetached)
	//		{
	//			App->CL_Ogre->OgreListener->mTranslateVector.z = App->CL_Ogre->OgreListener->mMoveScale * 30;
	//		}
	//		/*else
	//		{
	//		if (App->SBC_Player->PlayerAdded == 1)
	//		{
	//		App->SBC_Player->Back();
	//		}
	//		}*/
	//	}

		//	------------------------------------------------ Move Back
		if (GetAsyncKeyState(83) < 0) // S Key	
		{

			if (App->CL_Scene->Player_Added == 1)
			{
				App->CL_DCC->mMoveDirection = (btVector3(0, 0, 1));
				//App->SBC_Player->Check_Collisions_New();
				App->CL_Scene->B_Player[0]->IsMOving_Back = 1;
			}

		}
		else
		{
			if (App->CL_Scene->Player_Added == 1 && App->CL_Scene->B_Player[0]->IsMOving_Back == 1)
			{
				App->CL_DCC->mMoveDirection = (btVector3(0, 0, 0));
				App->CL_Scene->B_Player[0]->IsMOving_Back = 0;
			}
		}

		//	------------------------------------------------ Move Right
		if (GetAsyncKeyState(65) < 0)
		{

			if (App->CL_Scene->Player_Added == 1)
			{
				App->CL_DCC->mMoveDirection = (btVector3(1, 0, 0));// walkDirection
				//App->CL_Player->Check_Collisions_New();
				App->CL_Scene->B_Player[0]->IsMOving_Right = 1;
			}
		}
		else
		{
			if (App->CL_Scene->Player_Added == 1 && App->CL_Scene->B_Player[0]->IsMOving_Right == 1)
			{
				App->CL_DCC->mMoveDirection = (btVector3(0, 0, 0));// walkDirection
				App->CL_Scene->B_Player[0]->IsMOving_Right = 0;
			}
		}

		//	------------------------------------------------ Move Left
		if (GetAsyncKeyState(68) < 0)
		{
			
				if (App->CL_Scene->Player_Added == 1)
				{
					App->CL_DCC->mMoveDirection = (btVector3(-1, 0, 0));// walkDirection
					//App->CL_Player->Check_Collisions_New();
					App->CL_Scene->B_Player[0]->IsMOving_Left = 1;
				}
			
		}
		else
		{
			if (App->CL_Scene->Player_Added == 1 && App->CL_Scene->B_Player[0]->IsMOving_Left == 1)
			{
				App->CL_DCC->mMoveDirection = (btVector3(0, 0, 0));// walkDirection
				App->CL_Scene->B_Player[0]->IsMOving_Left = 0;
			}
		}

	//	------------------------------------------------ Escape 
	//	if (GetAsyncKeyState(VK_ESCAPE) < 0) // Back to Editor mode;
	//	{
	//		if (App->SBC_Scene->GameMode_Running_Flag == 1 || App->SBC_Scene->FullScreenMode_Flag == 1)
	//		{
	//			if (App->SBC_Front_Dlg->Use_Front_Dlg_Flag == 1)
	//			{
	//				App->CL_Ogre->OgreListener->Pl_LeftMouseDown = 0;
	//				App->CL_Ogre->OgreListener->Block_Mouse = 1;
	//				App->SBC_Keyboard->Block_Keyboard = 1;
	//				App->Block_Mouse_Buttons = 1;

	//				ReleaseCapture();
	//				App->CL_Ogre->OgreListener->Pl_LeftMouseDown = 0;
	//				SetCursor(App->CUR);

	//				App->SBC_Front_Dlg->Show_Front_Dlg_Flag = 1;
	//			}
	//			else
	//			{
	//				App->CL_Ogre->ExitFullScreen();
	//			}
	//		}
	//	}
	//}
}