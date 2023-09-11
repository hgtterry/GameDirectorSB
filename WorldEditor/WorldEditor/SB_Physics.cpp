/*
Copyright (c) 2023 World Editor -- HGT Software W.T.Flanigan H.C.Flanigan

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
#include "SB_Physics.h"

SB_Physics::SB_Physics(void)
{
}

SB_Physics::~SB_Physics(void)
{
}

// *************************************************************************
//							Set_Physics Terry Bernie					   *
// *************************************************************************
void SB_Physics::Set_Physics(int Index)
{
	App->CLSB_Scene->V_Object[Index]->Physics_Quat = App->CLSB_Scene->V_Object[Index]->Object_Node->getOrientation();

	float w = App->CLSB_Scene->V_Object[Index]->Physics_Quat.w;
	float x = App->CLSB_Scene->V_Object[Index]->Physics_Quat.x;
	float y = App->CLSB_Scene->V_Object[Index]->Physics_Quat.y;
	float z = App->CLSB_Scene->V_Object[Index]->Physics_Quat.z;
	App->CLSB_Scene->V_Object[Index]->Phys_Body->getWorldTransform().setRotation(btQuaternion(x, y, z, w));

	App->CLSB_Scene->V_Object[Index]->Object_Node->setScale(App->CLSB_Scene->V_Object[Index]->Mesh_Scale);

	Ogre::Vector3 Scale = App->CLSB_Scene->V_Object[Index]->Object_Node->getScale();
	App->CLSB_Scene->V_Object[Index]->Phys_Body->getCollisionShape()->setLocalScaling(btVector3(Scale.x, Scale.y, Scale.z));

	UpDate_Physics_And_Visuals(Index);

	App->CLSB_Scene->V_Object[Index]->Physics_Valid = 1;
}

// *************************************************************************
// *				UpDate_Physics_And_Visuals Terry Flanigtan		 	   *
// *************************************************************************
void SB_Physics::UpDate_Physics_And_Visuals(int Index)
{
	if (App->CLSB_Scene->V_Object[Index]->Shape == Enums::Shape_TriMesh)
	{

	}
	else
	{
		//if (App->SBC_Scene->V_Object[Index]->Physics_Valid == 1)
		{
			Set_Physics_Position(Index);
		}
	}


	//App->SBC_Markers->MarkerBB_Addjust(Index);

	// Needs Looking at
	//App->SBC_Scene->V_Object[Index]->Altered = 1;
	//App->SBC_FileView->Mark_Altered(App->SBC_Scene->V_Object[Index]->FileViewItem);
	//App->SBC_Scene->Scene_Modified = 1;
}

// *************************************************************************
// *	  				Set_Physics_Position Terry Flanigan				   *
// *************************************************************************
void SB_Physics::Set_Physics_Position(int Index)
{
	AxisAlignedBox worldAAB = App->CLSB_Scene->V_Object[Index]->Object_Ent->getBoundingBox();
	worldAAB.transformAffine(App->CLSB_Scene->V_Object[Index]->Object_Node->_getFullTransform());
	Ogre::Vector3 Centre = worldAAB.getCenter();
	App->CLSB_Scene->V_Object[Index]->Phys_Body->getWorldTransform().setOrigin(btVector3(Centre.x, Centre.y, Centre.z));
	App->CLSB_Scene->V_Object[Index]->Physics_Pos = Centre;
}
