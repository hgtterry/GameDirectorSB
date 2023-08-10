/*
Copyright (c) 2021 Scene Builder and Equity -- Inflanite Software W.T.Flanigan H.C.Flanigan

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
#include "Base_Player.h"


Base_Player::Base_Player()
{
	mDummyCamera = App->CLSB_Ogre->mSceneMgr->createCamera("PlayerRay");

	CameraPitch =	nullptr;
	Player_Ent =	nullptr;
	Player_Node =	nullptr;

	Phys_Body =		nullptr;
	Phys_Shape =	nullptr;

	mMoveDirection.setValue(0, 0, 0);

	StartPos.x = 0;
	StartPos.y = 0;
	StartPos.z = 0;

	Physics_Rotation = btQuaternion(1, 0, 0, 0);

	Forward_Timer = 0;
	Ground_speed = 10000;

	Limit_Look_Up = 45;
	Limit_Look_Down = -45;

	Altered = 1;

	Capsule_Mass = 1.0;
	Capsule_Radius = 4.4;
	Capsule_Height = 17.0;

	PlayerHeight = 16.0;

	TurnRate = 0.000008;

	Compenstate = 100;

	mOnGround = 1;
	IsMOving = 0;
	IsMOving_Back = 0;
	IsMOving_Right = 0;
	IsMOving_Left = 0;

	mJump = 0;
	mJumpSpeed = 4.5;

	Physics_Debug_On = 1;

	FileViewItem = nullptr;

	strcpy(Player_Name, "Player_1");
}


Base_Player::~Base_Player()
{
}


// *************************************************************************
// *	  		Rotate_FromCam:- Terry and Hazel Flanigan 2022			   *
// *************************************************************************
void Base_Player::Rotate_FromCam(const Ogre::Vector3 axis, float delta, bool normalize)
{
	float test = (delta * 180) / 3.14159265359;

	btTransform xform = Phys_Body->getWorldTransform();
	btMatrix3x3 R = xform.getBasis();
	R = R * btMatrix3x3(btQuaternion(btVector3(axis[0], axis[1], axis[2]), test));

	xform.setBasis(R);
	Phys_Body->setWorldTransform(xform);
}

