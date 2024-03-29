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
#include "SB_Object.h"

SB_Object::SB_Object()
{

}

SB_Object::~SB_Object()
{
}

// *************************************************************************
//		Get_BoundingBox_World_Centre:- Terry and Hazel Flanigan 2023	   *
// *************************************************************************
Ogre::Vector3 SB_Object::Get_BoundingBox_World_Centre(int Object_Index)
{
	/*if (App->SBC_Scene->V_Object[Object_Index]->Shape == Enums::Shape_TriMesh)
	{
		Ogre::Vector3 Pos = App->SBC_Scene->V_Object[Object_Index]->Object_Node->getPosition();
		return Pos;
	}
	else*/
	{
		AxisAlignedBox worldAAB = App->CLSB_Scene->V_Object[Object_Index]->Object_Ent->getBoundingBox();
		worldAAB.transformAffine(App->CLSB_Scene->V_Object[Object_Index]->Object_Node->_getFullTransform());
		Ogre::Vector3 Centre = worldAAB.getCenter();

		return Centre;
	}
}

// *************************************************************************
// *	  		GetMesh_BB_Radius:- Terry and Hazel Flanigan 2022		   *
// *************************************************************************
float SB_Object::GetMesh_BB_Radius(SceneNode* mNode)
{
	AxisAlignedBox aab = mNode->getAttachedObject(0)->getBoundingBox();
	Ogre::Vector3 min = aab.getMinimum() * mNode->getScale();
	Ogre::Vector3 max = aab.getMaximum() * mNode->getScale();
	Ogre::Vector3 center = aab.getCenter() * mNode->getScale();
	Ogre::Vector3 size(fabs(max.x - min.x), fabs(max.y - min.y), fabs(max.z - min.z));
	float radius = (size.x > size.z) ? size.z / 2.0f : size.x / 2.0f;

	return radius;
}
