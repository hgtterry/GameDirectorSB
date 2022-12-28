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

#pragma once
class Base_Player
{
public:
	Base_Player();
	~Base_Player();

	void Stop(void);
	void Jump(const Ogre::Vector3 axis, float force);
	void jump2(const btVector3& dir);
	void Move_Player(const btVector3 &walkDirection,float delta);
	void Rotate_FromCam(const Ogre::Vector3 axis, float delta, bool normalize);
	bool SelectEntity_World(void);

	Ogre::Camera*		CameraPitch;
	Ogre::Entity*		Player_Ent;
	Ogre::SceneNode*	Player_Node;

	Ogre::Camera* mDummyCamera;
	Vector3		mDummyTranslateVector;

	Ogre::String Pl_Entity_Name;
	char Selected_Object_Name[MAX_PATH];
	int	Selected_Entity_Index;
	float Compenstate;


	btRigidBody *Phys_Body;
	btCollisionShape *Phys_Shape;

	Ogre::Vector3 StartPos;
	btQuaternion Physics_Rotation;

	btVector3 mJumpDir;;

	float Forward_Timer;
	float Ground_speed;

	float TurnRate;

	float Capsule_Mass;
	float Capsule_Radius;
	float Capsule_Height;

	float Limit_Look_Up;
	float Limit_Look_Down;
	float mJumpSpeed;
	float PlayerHeight;
	bool Altered;
	bool mOnGround;
	bool IsMOving;
	bool IsMOving_Back;
	bool IsMOving_Right;
	bool IsMOving_Left;
	bool mJump;
	bool Physics_Debug_On;

	HTREEITEM FileViewItem;

	char Player_Name[255]; // Players Name must be unique [171221]


	btVector3 mMoveDirection;

	btScalar mSpeedDamping = 10.1;
	btScalar mMaxLinearVelocity2 = pow(15 / 3.6, 2);
	btScalar mWalkAccel = 25.0;
};

