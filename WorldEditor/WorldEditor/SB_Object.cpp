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
	BasketBall_Done = 0;
}

SB_Object::~SB_Object()
{
}

// *************************************************************************
// *					Do_Basketball (Terry Bernie)					   *
// *************************************************************************
void SB_Object::Do_Basketball()
{
	if (BasketBall_Done == 0)
	{
	
		App->CLSB_Scene->V_Object.push_back(new Base_Object());
		App->CLSB_Scene->Object_Count = 1;

		Base_Object* m_Object = App->CLSB_Scene->V_Object[0];

		m_Object->Object_Ent = App->CLSB_Ogre->mSceneMgr->createEntity("Ball", "basketball.mesh", App->CLSB_Ogre->App_Resource_Group);
		m_Object->Object_Node = App->CLSB_Ogre->mSceneMgr->getRootSceneNode()->createChildSceneNode();
		m_Object->Object_Node->attachObject(m_Object->Object_Ent);

		m_Object->Object_Node->setVisible(true);

		m_Object->Object_Node->setPosition(0, -10, -50);
		m_Object->Object_Node->scale(2, 2, 2);

		AxisAlignedBox worldAAB = m_Object->Object_Ent->getBoundingBox();
		worldAAB.transformAffine(m_Object->Object_Node->_getFullTransform());
		Ogre::Vector3 Centre = worldAAB.getCenter();

		btTransform startTransform;
		startTransform.setIdentity();
		startTransform.setRotation(btQuaternion(0.0f, 0.0f, 0.0f, 1));

		btScalar mass;
		mass = 1.0f;

		btVector3 localInertia(0, 0, 0);
		btVector3 initialPosition(Centre.x, Centre.y, Centre.z);

		startTransform.setOrigin(initialPosition);

		float Radius = 16;// App->CL_Object->GetMesh_BB_Radius(Object_Node);


		btCollisionShape* newRigidShape = new btSphereShape(Radius);
		newRigidShape->calculateLocalInertia(mass, localInertia);

		App->CLSB_Bullet->collisionShapes.push_back(newRigidShape);

		btDefaultMotionState* myMotionState = new btDefaultMotionState(startTransform);

		btRigidBody::btRigidBodyConstructionInfo rbInfo(mass, myMotionState, newRigidShape, localInertia);

		m_Object->Phys_Body = new btRigidBody(rbInfo);
		m_Object->Phys_Body->setRestitution(1.0);
		m_Object->Phys_Body->setFriction(2.5);
		m_Object->Phys_Body->setUserPointer(m_Object->Object_Node);
		m_Object->Phys_Body->setWorldTransform(startTransform);

		int f = m_Object->Phys_Body->getCollisionFlags();
		m_Object->Phys_Body->setCollisionFlags(f | btCollisionObject::CF_DISABLE_VISUALIZE_OBJECT);

		m_Object->Usage = Enums::Usage_Dynamic;
		m_Object->Phys_Body->setUserIndex(Enums::Usage_Dynamic);
		m_Object->Phys_Body->setUserIndex2(0);

		App->CLSB_Bullet->dynamicsWorld->addRigidBody(m_Object->Phys_Body);

		BasketBall_Done = 1;
	}

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
