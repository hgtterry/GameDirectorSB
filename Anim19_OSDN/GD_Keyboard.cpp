#include "stdafx.h"
#include "GD19_App.h"
#include "GD_Keyboard.h"


GD_Keyboard::GD_Keyboard()
{
	Rate = 0;
	OldPos.ZERO;
	//mCamera = App->Cl19_Ogre->OgreListener->mCam;

}


GD_Keyboard::~GD_Keyboard()
{
}

// *************************************************************************
// *						Keyboard_Monitor Terry						   *
// *************************************************************************
void GD_Keyboard::Keyboard_Monitor(float deltaTime)
{
	//------------------------------------------------ O Key - Change to Object
	if (GetAsyncKeyState(79) < 0 && App->Cl19_Ogre->OgreListener->GD_CameraMode == Enums::CamFirst)
	{
		
		App->Cl19_Ogre->OgreListener->FollowPlayer = 0;
	}

	if (GetAsyncKeyState(80) < 0 && App->Cl19_Ogre->OgreListener->GD_CameraMode == Enums::CamFirst)
	{

		App->Cl19_Ogre->OgreListener->FollowPlayer = 1; // P Key - Change to Player
	}

	//------------------------------------------------ Space Key - Jump and Selection
	if (GetAsyncKeyState(VK_SPACE) < 0 && App->SBC_Scene->Player_Added == 1)
	{
		if (App->Cl19_Ogre->OgreListener->GD_Selection_Mode == 0)
		{
			App->SBC_Scene->SBC_Base_Player[0]->Jump(Ogre::Vector3(1, 1, 0), 1.2);
		}
		else
		{
			App->Cl19_Ogre->OgreListener->SelectEntity_World();
		}
	}

	//------------------------------------------------ Y Key
	if (GetAsyncKeyState(89) < 0 && App->Cl19_Ogre->OgreListener->mNameOverlay->isVisible() == 1)
	{
		App->Cl19_Ogre->OgreListener->mNameOverlay->hide();

		if (App->Cl19_Ogre->OgreListener->Pl_Entity_Name == "Player_1")
		{
			App->SBC_FileView->SelectItem(App->SBC_Player->FileViewItem);
		}
		else
		{
			App->SBC_FileView->Select_Item(App->Cl19_Ogre->OgreListener->Selected_Entity_Index);
		}

	}

	//------------------------------------------------ N Key
	if (GetAsyncKeyState(78) < 0 && App->Cl19_Ogre->OgreListener->mNameOverlay->isVisible() == 1)
	{
		App->Cl19_Ogre->OgreListener->mNameOverlay->hide();
	}

	//------------------------------------------------ Forward
	if (GetAsyncKeyState(VK_UP) < 0 && App->SBC_Scene->Player_Added == 1 && App->Cl19_Ogre->OgreListener->GD_CameraMode == Enums::CamDetached)
	{
		App->SBC_Scene->SBC_Base_Player[0]->Forward(deltaTime);
		App->SBC_Scene->SBC_Base_Player[0]->IsMOving = 1;
	}
	else
	{
		if (App->SBC_Scene->Player_Added == 1 && App->SBC_Scene->SBC_Base_Player[0]->IsMOving == 1 && App->Cl19_Ogre->OgreListener->GD_CameraMode == Enums::CamDetached)
		{
			App->SBC_Scene->SBC_Base_Player[0]->Stop();
			App->SBC_Scene->SBC_Base_Player[0]->IsMOving = 0;
		}
	}
	//------------------------------------------------ Back
	if (GetAsyncKeyState(VK_DOWN) < 0 && App->SBC_Scene->Player_Added == 1 && App->Cl19_Ogre->OgreListener->GD_CameraMode == Enums::CamDetached)
	{
		App->SBC_Scene->SBC_Base_Player[0]->Back();
		App->SBC_Scene->SBC_Base_Player[0]->IsMOving_Back = 1;
	}
	else
	{
		if (App->SBC_Scene->Player_Added == 1 && App->SBC_Scene->SBC_Base_Player[0]->IsMOving_Back == 1 && App->Cl19_Ogre->OgreListener->GD_CameraMode == Enums::CamDetached)
		{
			App->SBC_Scene->SBC_Base_Player[0]->Stop();
			App->SBC_Scene->SBC_Base_Player[0]->IsMOving_Back = 0;
		}
	}

	//------------------------------------------------ Turn Right
	if (GetAsyncKeyState(VK_RIGHT) < 0 && App->SBC_Scene->Player_Added == 1)
	{
		App->Cl19_Ogre->OgreListener->toggleTimer -= deltaTime;

		if (App->Cl19_Ogre->OgreListener->toggleTimer < 0)
		{
			Ogre::Vector3 Rotate;
			Rotate.x = 0;
			Rotate.y = 1;
			Rotate.z = 0;

			float Delta = App->Cl_Utilities->DegreesToRadians(1);

			App->SBC_Scene->SBC_Base_Player[0]->Rotate(Rotate, false);

			App->Cl19_Ogre->OgreListener->toggleTimer = 0.01;
		}
	}

	//------------------------------------------------ Turn Left
	if (GetAsyncKeyState(VK_LEFT) < 0 && App->SBC_Scene->Player_Added == 1)
	{
		App->Cl19_Ogre->OgreListener->toggleTimer -= deltaTime;

		if (App->Cl19_Ogre->OgreListener->toggleTimer < 0)
		{
			Ogre::Vector3 Rotate;
			Rotate.x = 0;
			Rotate.y = -1;
			Rotate.z = 0;

			float Delta = App->Cl_Utilities->DegreesToRadians(1);

			App->SBC_Scene->SBC_Base_Player[0]->Rotate(Rotate, false);

			App->Cl19_Ogre->OgreListener->toggleTimer = 0.01;
		}
	}

	//------------------------------------------------ Q key Down in Fly Mode
	if (GetAsyncKeyState(69) < 0)
	{
		Rate = (App->Cl19_Ogre->OgreListener->mMoveSensitivity / 1000) * 2; //FlyRate;

		OldPos = App->Cl19_Ogre->OgreListener->mCam->getPosition();

		OldPos.y += Rate;

		App->Cl19_Ogre->OgreListener->mCam->setPosition(OldPos);
	}
	
	//------------------------------------------------ E key Up in Fly Mode
	if (GetAsyncKeyState(81) < 0)
	{
		Rate = (App->Cl19_Ogre->OgreListener->mMoveSensitivity / 1000) * 2; //FlyRate;

		OldPos = App->Cl19_Ogre->OgreListener->mCam->getPosition();

		OldPos.y -= Rate;

		App->Cl19_Ogre->OgreListener->mCam->setPosition(OldPos);
	}
	//------------------------------------------------
	if (App->Cl19_Ogre->OgreListener->Wheel < 0) // Mouse Wheel Forward
	{
		if (App->Cl19_Ogre->OgreListener->GD_CameraMode == Enums::CamDetached)
		{
			App->Cl19_Ogre->OgreListener->mTranslateVector.z = -App->Cl19_Ogre->OgreListener->mMoveScale * 30;
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
		if (App->Cl19_Ogre->OgreListener->GD_CameraMode == Enums::CamDetached)
		{
			App->Cl19_Ogre->OgreListener->mTranslateVector.z = -App->Cl19_Ogre->OgreListener->mMoveScale;
		}
		else
		{
			if (App->SBC_Scene->Player_Added == 1)
			{

				App->SBC_Scene->SBC_Base_Player[0]->Forward(deltaTime);
				App->SBC_Scene->SBC_Base_Player[0]->IsMOving = 1;
			}
		}
	}
	else
	{
		if (App->Cl19_Ogre->OgreListener->GD_CameraMode == Enums::CamDetached)
		{

		}
		else if (App->SBC_Scene->Player_Added == 1 && App->SBC_Scene->SBC_Base_Player[0]->IsMOving == 1)
		{
			App->SBC_Scene->SBC_Base_Player[0]->Stop();
			App->SBC_Scene->SBC_Base_Player[0]->IsMOving = 0;
		}
	}

	if (App->Cl19_Ogre->OgreListener->Wheel > 0) // Mouse Wheel Back
	{
		if (App->Cl19_Ogre->OgreListener->GD_CameraMode == Enums::CamDetached)
		{
			App->Cl19_Ogre->OgreListener->mTranslateVector.z = App->Cl19_Ogre->OgreListener->mMoveScale * 30;
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

		if (App->Cl19_Ogre->OgreListener->GD_CameraMode == Enums::CamDetached)
		{
			App->Cl19_Ogre->OgreListener->mTranslateVector.z = App->Cl19_Ogre->OgreListener->mMoveScale;
		}
		else
		{
			if (App->SBC_Scene->Player_Added == 1)
			{
				App->SBC_Scene->SBC_Base_Player[0]->Back();
				App->SBC_Scene->SBC_Base_Player[0]->IsMOving_Back = 1;
			}
		}
	}
	else
	{
		if (App->Cl19_Ogre->OgreListener->GD_CameraMode == Enums::CamDetached)
		{

		}
		else if (App->SBC_Scene->Player_Added == 1 && App->SBC_Scene->SBC_Base_Player[0]->IsMOving_Back == 1)
		{
			App->SBC_Scene->SBC_Base_Player[0]->Stop();
			App->SBC_Scene->SBC_Base_Player[0]->IsMOving_Back = 0;
		}
	}

	//------------------------------------------------ Move Right
	if (GetAsyncKeyState(65) < 0)
	{
		if (App->Cl19_Ogre->OgreListener->GD_CameraMode == Enums::CamDetached)
		{
			App->Cl19_Ogre->OgreListener->mTranslateVector.x = -App->Cl19_Ogre->OgreListener->mMoveScale;
		}
		else
		{
			if (App->SBC_Scene->Player_Added == 1)
			{
				App->SBC_Scene->SBC_Base_Player[0]->Move_Right();
				App->SBC_Scene->SBC_Base_Player[0]->IsMOving_Right = 1;
			}
		}
	}
	else
	{
		if (App->Cl19_Ogre->OgreListener->GD_CameraMode == Enums::CamDetached)
		{

		}
		else if (App->SBC_Scene->Player_Added == 1 && App->SBC_Scene->SBC_Base_Player[0]->IsMOving_Right == 1)
		{
			App->SBC_Scene->SBC_Base_Player[0]->Stop();
			App->SBC_Scene->SBC_Base_Player[0]->IsMOving_Right = 0;
		}
	}

	//------------------------------------------------ Move Left
	if (GetAsyncKeyState(68) < 0)
	{
		if (App->Cl19_Ogre->OgreListener->GD_CameraMode == Enums::CamDetached)
		{
			App->Cl19_Ogre->OgreListener->mTranslateVector.x = App->Cl19_Ogre->OgreListener->mMoveScale;
		}
		else
		{
			if (App->SBC_Scene->Player_Added == 1)
			{
				App->SBC_Scene->SBC_Base_Player[0]->Move_Left();
				App->SBC_Scene->SBC_Base_Player[0]->IsMOving_Left = 1;
			}
		}
	}
	else
	{
		if (App->Cl19_Ogre->OgreListener->GD_CameraMode == Enums::CamDetached)
		{

		}
		else if (App->SBC_Scene->Player_Added == 1 && App->SBC_Scene->SBC_Base_Player[0]->IsMOving_Left == 1)
		{
			App->SBC_Scene->SBC_Base_Player[0]->Stop();
			App->SBC_Scene->SBC_Base_Player[0]->IsMOving_Left = 0;
		}
	}

	//------------------------------------------------ Escape 
	if (GetAsyncKeyState(VK_ESCAPE) < 0) // Back to full Screen;
	{
		App->Cl19_Ogre->ExitFullScreen();
	}

}
