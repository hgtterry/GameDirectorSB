/*
Copyright (c) 2022- 2023 Equity_ME Model Editor -- Inflanite Software W.T.Flanigan H.C.Flanigan

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
#include "ME_App.h"
#include "ME_Keyboard.h"

ME_Keyboard::ME_Keyboard()
{
}

ME_Keyboard::~ME_Keyboard()
{
}

// *************************************************************************
// *		Keyboard_Mode_Model:- Terry and Hazel Flanigan 2023			   *
// *************************************************************************
void ME_Keyboard::Keyboard_Mode_Model(float deltaTime)
{
	//	Pan Up
	if (GetAsyncKeyState(69) < 0) // E key 
	{
		Ogre::Real Rate;
		Rate = (App->CL_Ogre->Ogre_Listener->mMoveSensitivity / 1000) * 2;

		Ogre::Vector3 OldPos;
		OldPos = App->CL_Ogre->Ogre_Listener->mCam->getPosition();

		OldPos.y += Rate;
		App->CL_Ogre->Ogre_Listener->mCam->setPosition(OldPos);
	}

	// Pan Down
	if (GetAsyncKeyState(81) < 0)  // Q Key
	{
		Ogre::Real Rate;
		Rate = (App->CL_Ogre->Ogre_Listener->mMoveSensitivity / 1000) * 2;

		Ogre::Vector3 OldPos;
		OldPos = App->CL_Ogre->Ogre_Listener->mCam->getPosition();

		OldPos.y -= Rate;
		App->CL_Ogre->Ogre_Listener->mCam->setPosition(OldPos);
	}

	// Forward
	if (App->CL_Ogre->Ogre_Listener->Wheel < 0) // Mouse Wheel Forward
	{
		App->CL_Ogre->Ogre_Listener->mTranslateVector.z = -App->CL_Ogre->Ogre_Listener->mMoveScale * 30;
	}
	if (GetAsyncKeyState(87) < 0) // W Key
	{
		App->CL_Ogre->Ogre_Listener->mTranslateVector.z = -App->CL_Ogre->Ogre_Listener->mMoveScale;
	}

	// Back
	if (App->CL_Ogre->Ogre_Listener->Wheel > 0) // Mouse Wheel Back
	{
		App->CL_Ogre->Ogre_Listener->mTranslateVector.z = App->CL_Ogre->Ogre_Listener->mMoveScale * 30;
	}
	if (GetAsyncKeyState(83) < 0) // S Key	
	{
		App->CL_Ogre->Ogre_Listener->mTranslateVector.z = App->CL_Ogre->Ogre_Listener->mMoveScale;
	}

	// Pan Left
	if (GetAsyncKeyState(65) < 0) // A Key
	{
		App->CL_Ogre->Ogre_Listener->mTranslateVector.x = App->CL_Ogre->Ogre_Listener->mMoveScale;
	}

	// Pan Right
	if (GetAsyncKeyState(68) < 0)  // D Key
	{
		App->CL_Ogre->Ogre_Listener->mTranslateVector.x = -App->CL_Ogre->Ogre_Listener->mMoveScale;
	}

}
