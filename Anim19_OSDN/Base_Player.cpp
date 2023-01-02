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
#include "GD19_App.h"
#include "Base_Player.h"


Base_Player::Base_Player()
{
	mDummyCamera = App->SBC_Ogre->mSceneMgr->createCamera("PlayerRay");

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
	Ground_speed = 4.2;

	Limit_Look_Up = 45;
	Limit_Look_Down = -45;

	Altered = 1;

	Capsule_Mass = 1.0;
	Capsule_Radius = 4.4;
	Capsule_Height = 17.0;

	PlayerHeight = 16.0;

	TurnRate = 0.000005;

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
// *	  					Stop Terry Bernie							   *
// *************************************************************************
void Base_Player::Stop(void)
{
	//Get_Height();

	btTransform transform;
	Phys_Body->getMotionState()->getWorldTransform(transform);
	btMatrix3x3& basis = transform.getBasis();
	btMatrix3x3 inv = basis.transpose();

	btVector3 dv = mMoveDirection * (1);

	btVector3 linearVelocity = inv * Phys_Body->getLinearVelocity();
	linearVelocity = dv;

	Phys_Body->setLinearVelocity(basis * linearVelocity);

}

// *************************************************************************
// *	  					Jump Terry Bernie							   *
// *************************************************************************
void Base_Player::Jump(const Ogre::Vector3 axis, float force)
{
	if (mJump == 0)
	{
		mJump = 1;
	}
	
	Get_Height();

	btVector3 pos = Phys_Body->getWorldTransform().getOrigin();
	pos[1] = pos[1] + 0.5;

	Phys_Body->getWorldTransform().setOrigin(btVector3(pos[0], pos[1], pos[2]));

	App->SBC_Player->Check_Collisions_New();

	if (App->SBC_Ogre->OgreListener->DistanceToCollision < 14)
	{
		mJump = 0;
	}
	//mJump = 0;
}

// *************************************************************************
// *	  					Jump2 Terry Bernie							   *
// *************************************************************************
void Base_Player::jump2(const btVector3& dir)
{
	return;
	Get_Height();

	mJump = 1;

	if (App->SBC_Ogre->OgreListener->DistanceToCollision > 14)
	{
		return;
	}

	

	mJumpDir = dir;
	//if (dir.fuzzyZero()) {
		mJumpDir.setValue(0, 1, 0);
	//}
	//mJumpDir.normalize();
		btTransform transform;
		Phys_Body->getMotionState()->getWorldTransform(transform);
		btMatrix3x3& basis = transform.getBasis();
		btMatrix3x3 inv = basis.transpose();

	btVector3 linearVelocity = inv * Phys_Body->getLinearVelocity();

	linearVelocity += -1.0 * mJumpDir;

	Get_Height();

	if (App->SBC_Ogre->OgreListener->DistanceToCollision < 14)
	{
		mJump = 0;
	}

	Phys_Body->setLinearVelocity(basis * linearVelocity);
}

// *************************************************************************
// *	  		Move_Player:- Terry and Hazel Flanigan 2022				   *
// *************************************************************************
void Base_Player::Move_Player(const btVector3 &walkDirection,float delta)
{
	Get_Height();

	mMoveDirection = walkDirection;

	btTransform transform;
	Phys_Body->getMotionState()->getWorldTransform(transform);
	btMatrix3x3& basis = transform.getBasis();
	btMatrix3x3 inv = basis.transpose();

	btVector3 linearVelocity = inv * Phys_Body->getLinearVelocity();

	if (mMoveDirection.fuzzyZero() && mOnGround) 
	{
		linearVelocity *= mSpeedDamping;
	}
	else if (mOnGround || linearVelocity[2] > 0) 
	{
		btVector3 dv = mMoveDirection * (App->SBC_Scene->B_Player[0]->Ground_speed * delta);
		linearVelocity = dv;

		if (mJump == 0)
		{
			linearVelocity[1] = Compenstate;
		}
		else
		{
			linearVelocity[1] = linearVelocity[1] +1.50;
		}
	}

	//if (mJump) 
	//{
	//	linearVelocity += 10 * mJumpDir;
	//	mJump = false;
	//	//cancelStep();
	//}

	Phys_Body->setLinearVelocity(basis * linearVelocity);

	App->SBC_Player->Check_Collisions_New();
}


// *************************************************************************
// *	  			Rotate:- Terry and Hazel Flanigan 2022				   *
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

// *************************************************************************
// *					Get_Height   Terry Bernie						   *
// *************************************************************************
bool Base_Player::Get_Height(void)
{

	App->SBC_Ogre->OgreListener->DistanceToCollision = 0;

	Ogre::SceneNode* mNode;
	Vector3 FirstPos = Player_Node->getPosition();
	mDummyCamera->setPosition(FirstPos);

	mDummyTranslateVector = Ogre::Vector3::ZERO;

	mDummyTranslateVector.y = -100.0;
	mDummyCamera->moveRelative(mDummyTranslateVector);

	if (App->SBC_Ogre->OgreListener->mCollisionTools->collidesWithEntity(FirstPos, mDummyCamera->getPosition(), 1.0f, 0, -1))
	{
		mNode = App->SBC_Ogre->OgreListener->mCollisionTools->pentity->getParentSceneNode();
		
		App->SBC_Ogre->OgreListener->Pl_Entity_Name = App->SBC_Ogre->OgreListener->mCollisionTools->pentity->getName();
		App->SBC_Ogre->OgreListener->DistanceToCollision = App->SBC_Ogre->OgreListener->mCollisionTools->distToColl;

		if (App->SBC_Ogre->OgreListener->DistanceToCollision > 14)
		{
			Compenstate = 80;
		}
		else
		{
			Compenstate = 5;
		}

		char buff[255];
		strcpy(buff, App->SBC_Ogre->OgreListener->Pl_Entity_Name.c_str());
	
	}

	return 1;
}

