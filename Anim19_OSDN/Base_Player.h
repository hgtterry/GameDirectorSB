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

	void Forward(float delta);
	void Back(void);

	void Move_Left(void);
	void Move_Right(void);

	Ogre::Camera*		CameraPitch;
	Ogre::Entity*		Player_Ent;
	Ogre::SceneNode*	Player_Node;

	btRigidBody *Phys_Body;
	btCollisionShape *Phys_Shape;

	Ogre::Vector3 StartPos;

	float Forward_Timer;
	float Ground_speed;

	char Player_Name[255]; // Players Name must be unique [171221]
};

