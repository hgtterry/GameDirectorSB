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
	CameraPitch =	nullptr;
	Player_Ent =	nullptr;
	Player_Node =	nullptr;

	Phys_Body =		nullptr;
	Phys_Shape =	nullptr;

	StartPos.x = 0;
	StartPos.y = -50;
	StartPos.z = 0;

	Forward_Timer = 0;
	Ground_speed = 4.2;

	strcpy(Player_Name, "No_Set");
}


Base_Player::~Base_Player()
{
}

// *************************************************************************
// *	  					Forward Terry Bernie						   *
// *************************************************************************
void Base_Player::Forward(float delta)
{
	Forward_Timer -= delta;

	if (Forward_Timer < 0)
	{
		Forward_Timer = 0.01; // 0.01

		btVector3 vel;

		btTransform xform = Phys_Body->getWorldTransform();
		btVector3 cur = Phys_Body->getLinearVelocity();
		btVector3 basis = xform.getBasis()[2];
		vel = -Ground_speed * 10 * basis;
		Phys_Body->setLinearVelocity(btVector3(vel[0], cur[1], vel[2]));

	}

	//Check_Collisions();
}
