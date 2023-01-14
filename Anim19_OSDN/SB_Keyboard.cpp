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
#include "GD19_App.h"
#include "SB_Keyboard.h"


SB_Keyboard::SB_Keyboard()
{
	Rate = 0;
	OldPos.ZERO;
	Block_Keyboard = 0;

}


SB_Keyboard::~SB_Keyboard()
{
}

// *************************************************************************
// *						Keyboard_Monitor Terry						   *
// *************************************************************************
void SB_Keyboard::Keyboard_Monitor(float deltaTime)
{
	if (Block_Keyboard == 0)
	{
		//------------------------------------------------ Space Key - Jump and Selection
		if (GetAsyncKeyState(VK_SPACE) < 0 && App->SBC_Scene->Player_Added == 1)
		{
			if (App->SBC_Ogre->OgreListener->GD_Selection_Mode == 0)
			{
				if (App->SBC_Ogre->OgreListener->GD_Run_Physics == 1)
				{
					App->SBC_Scene->B_Player[0]->jump2(btVector3(0, 1, 0));// , 4.2);
				}
			}
			else
			{
				App->SBC_Ogre->OgreListener->SelectEntity_World();
			}
		}

		//------------------------------------------------ Y Key
		if (GetAsyncKeyState(89) < 0)
		{

		}

		//------------------------------------------------ N Key
		if (GetAsyncKeyState(78) < 0)
		{

		}

		//------------------------------------------------ Forward
		if (GetAsyncKeyState(VK_UP) < 0 && App->SBC_Scene->Player_Added == 1 && App->SBC_Ogre->OgreListener->GD_CameraMode == Enums::CamDetached)
		{
			App->SBC_Scene->B_Player[0]->Move_Player(btVector3(0, 0, -1), deltaTime);
			App->SBC_Scene->B_Player[0]->IsMOving = 1;
		}
		else
		{
			if (App->SBC_Scene->Player_Added == 1 && App->SBC_Scene->B_Player[0]->IsMOving == 1 && App->SBC_Ogre->OgreListener->GD_CameraMode == Enums::CamDetached)
			{
				App->SBC_Scene->B_Player[0]->Stop();
				App->SBC_Scene->B_Player[0]->IsMOving = 0;
			}
		}
		//------------------------------------------------ Back
		if (GetAsyncKeyState(VK_DOWN) < 0 && App->SBC_Scene->Player_Added == 1 && App->SBC_Ogre->OgreListener->GD_CameraMode == Enums::CamDetached)
		{
			App->SBC_Scene->B_Player[0]->Move_Player(btVector3(0, 0, 1), deltaTime);
			App->SBC_Scene->B_Player[0]->IsMOving_Back = 1;
		}
		else
		{
			if (App->SBC_Scene->Player_Added == 1 && App->SBC_Scene->B_Player[0]->IsMOving_Back == 1 && App->SBC_Ogre->OgreListener->GD_CameraMode == Enums::CamDetached)
			{
				App->SBC_Scene->B_Player[0]->Stop();
				App->SBC_Scene->B_Player[0]->IsMOving_Back = 0;
			}
		}

		//------------------------------------------------ Turn Right
		if (GetAsyncKeyState(VK_RIGHT) < 0 && App->SBC_Scene->Player_Added == 1)
		{
			App->SBC_Ogre->OgreListener->toggleTimer -= deltaTime;

			if (App->SBC_Ogre->OgreListener->toggleTimer < 0)
			{
				Ogre::Vector3 Rotate;
				Rotate.x = 0;
				Rotate.y = 1;
				Rotate.z = 0;

				float Delta = App->Cl_Utilities->DegreesToRadians(1);

				//App->SBC_Scene->B_Player[0]->Rotate(Rotate, false);

				App->SBC_Ogre->OgreListener->toggleTimer = 0.01;
			}
		}

		//------------------------------------------------ Turn Left
		if (GetAsyncKeyState(VK_LEFT) < 0 && App->SBC_Scene->Player_Added == 1)
		{
			App->SBC_Ogre->OgreListener->toggleTimer -= deltaTime;

			if (App->SBC_Ogre->OgreListener->toggleTimer < 0)
			{
				Ogre::Vector3 Rotate;
				Rotate.x = 0;
				Rotate.y = -1;
				Rotate.z = 0;

				float Delta = App->Cl_Utilities->DegreesToRadians(1);

				//App->SBC_Scene->B_Player[0]->Rotate(Rotate, false);

				App->SBC_Ogre->OgreListener->toggleTimer = 0.01;
			}
		}

		//------------------------------------------------ Q key Down in Fly Mode
		if (GetAsyncKeyState(69) < 0)
		{
			if (App->SBC_Ogre->OgreListener->GD_CameraMode == Enums::CamDetached)
			{
				Rate = (App->SBC_Ogre->OgreListener->mMoveSensitivity / 1000) * 2; //FlyRate;

				OldPos = App->SBC_Ogre->OgreListener->mCam->getPosition();

				OldPos.y += Rate;

				App->SBC_Ogre->OgreListener->mCam->setPosition(OldPos);
			}
		}

		//------------------------------------------------ E key Up in Fly Mode
		if (GetAsyncKeyState(81) < 0)
		{
			if (App->SBC_Ogre->OgreListener->GD_CameraMode == Enums::CamDetached)
			{
				Rate = (App->SBC_Ogre->OgreListener->mMoveSensitivity / 1000) * 2; //FlyRate;

				OldPos = App->SBC_Ogre->OgreListener->mCam->getPosition();

				OldPos.y -= Rate;

				App->SBC_Ogre->OgreListener->mCam->setPosition(OldPos);
			}
		}
		//------------------------------------------------
		if (App->SBC_Ogre->OgreListener->Wheel < 0) // Mouse Wheel Forward
		{
			if (App->SBC_Ogre->OgreListener->GD_CameraMode == Enums::CamDetached)
			{
				App->SBC_Ogre->OgreListener->mTranslateVector.z = -App->SBC_Ogre->OgreListener->mMoveScale * 30;
			}
			/*else
			{
				if (App->SBC_Player->PlayerAdded == 1)
				{
					App->SBC_Player->IsMOving = 1;
					App->SBC_Player->Forward(deltaTime);
				}
				else
				{
					if (App->SBC_Player->IsMOving == 1)
					{
						App->SBC_Player->Stop();
						App->SBC_Player->IsMOving = 0;
					}
				}
			}*/
		}

		//------------------------------------------------ Move Forward
		if (GetAsyncKeyState(87) < 0) // W Key
		{
			if (App->SBC_Ogre->OgreListener->GD_CameraMode == Enums::CamDetached)
			{
				App->SBC_Ogre->OgreListener->mTranslateVector.z = -App->SBC_Ogre->OgreListener->mMoveScale;
			}
			else
			{
				if (App->SBC_Scene->Player_Added == 1)
				{
					App->SBC_Scene->B_Player[0]->Move_Player(btVector3(0, 0, -1), deltaTime);
					App->SBC_Scene->B_Player[0]->IsMOving = 1;
				}
			}
		}
		else
		{
			if (App->SBC_Ogre->OgreListener->GD_CameraMode == Enums::CamDetached)
			{

			}
			else if (App->SBC_Scene->Player_Added == 1 && App->SBC_Scene->B_Player[0]->IsMOving == 1)
			{
				App->SBC_Scene->B_Player[0]->Stop();
				App->SBC_Scene->B_Player[0]->IsMOving = 0;
			}
		}

		if (App->SBC_Ogre->OgreListener->Wheel > 0) // Mouse Wheel Back
		{
			if (App->SBC_Ogre->OgreListener->GD_CameraMode == Enums::CamDetached)
			{
				App->SBC_Ogre->OgreListener->mTranslateVector.z = App->SBC_Ogre->OgreListener->mMoveScale * 30;
			}
			/*else
			{
			if (App->SBC_Player->PlayerAdded == 1)
			{
			App->SBC_Player->Back();
			}
			}*/
		}

		//------------------------------------------------ Move Back
		if (GetAsyncKeyState(83) < 0) // S Key	
		{

			if (App->SBC_Ogre->OgreListener->GD_CameraMode == Enums::CamDetached)
			{
				App->SBC_Ogre->OgreListener->mTranslateVector.z = App->SBC_Ogre->OgreListener->mMoveScale;
			}
			else
			{
				if (App->SBC_Scene->Player_Added == 1)
				{
					App->SBC_Scene->B_Player[0]->Move_Player(btVector3(0, 0, 1), deltaTime);
					App->SBC_Scene->B_Player[0]->IsMOving_Back = 1;
				}
			}
		}
		else
		{
			if (App->SBC_Ogre->OgreListener->GD_CameraMode == Enums::CamDetached)
			{

			}
			else if (App->SBC_Scene->Player_Added == 1 && App->SBC_Scene->B_Player[0]->IsMOving_Back == 1)
			{
				App->SBC_Scene->B_Player[0]->Stop();
				App->SBC_Scene->B_Player[0]->IsMOving_Back = 0;
			}
		}

		//------------------------------------------------ Move Right
		if (GetAsyncKeyState(65) < 0)
		{
			if (App->SBC_Ogre->OgreListener->GD_CameraMode == Enums::CamDetached)
			{
				App->SBC_Ogre->OgreListener->mTranslateVector.x = -App->SBC_Ogre->OgreListener->mMoveScale;
			}
			else
			{
				if (App->SBC_Scene->Player_Added == 1)
				{
					App->SBC_Scene->B_Player[0]->Move_Player(btVector3(1, 0, 0), deltaTime);
					App->SBC_Scene->B_Player[0]->IsMOving_Right = 1;
				}
			}
		}
		else
		{
			if (App->SBC_Ogre->OgreListener->GD_CameraMode == Enums::CamDetached)
			{

			}
			else if (App->SBC_Scene->Player_Added == 1 && App->SBC_Scene->B_Player[0]->IsMOving_Right == 1)
			{
				App->SBC_Scene->B_Player[0]->Stop();
				App->SBC_Scene->B_Player[0]->IsMOving_Right = 0;
			}
		}

		//------------------------------------------------ Move Left
		if (GetAsyncKeyState(68) < 0)
		{
			if (App->SBC_Ogre->OgreListener->GD_CameraMode == Enums::CamDetached)
			{
				App->SBC_Ogre->OgreListener->mTranslateVector.x = App->SBC_Ogre->OgreListener->mMoveScale;
			}
			else
			{
				if (App->SBC_Scene->Player_Added == 1)
				{
					App->SBC_Scene->B_Player[0]->Move_Player(btVector3(-1, 0, 0), deltaTime);
					App->SBC_Scene->B_Player[0]->IsMOving_Left = 1;
				}
			}
		}
		else
		{
			if (App->SBC_Ogre->OgreListener->GD_CameraMode == Enums::CamDetached)
			{

			}
			else if (App->SBC_Scene->Player_Added == 1 && App->SBC_Scene->B_Player[0]->IsMOving_Left == 1)
			{
				App->SBC_Scene->B_Player[0]->Stop();
				App->SBC_Scene->B_Player[0]->IsMOving_Left = 0;
			}
		}

		//------------------------------------------------ Escape 
		if (GetAsyncKeyState(VK_ESCAPE) < 0) // Back to Editor mode;
		{
			if (App->SBC_Scene->GameMode_Running_Flag == 1 || App->SBC_Scene->FullScreenMode_Flag == 1)
			{
				if (App->SBC_Front_Dlg->Use_Front_Dlg_Flag == 1)
				{
					App->SBC_Ogre->OgreListener->Pl_LeftMouseDown = 0;
					App->SBC_Ogre->OgreListener->Block_Mouse = 1;
					App->SBC_Keyboard->Block_Keyboard = 1;
					App->Block_Mouse_Buttons = 1;

					ReleaseCapture();
					App->SBC_Ogre->OgreListener->Pl_LeftMouseDown = 0;
					SetCursor(App->CUR);

					App->SBC_Front_Dlg->Show_Front_Dlg_Flag = 1;
				}
				else
				{
					App->SBC_Ogre->ExitFullScreen();
				}
			}
		}
	}
}
