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
#include "BT_App.h"
#include "SB_Aera.h"


SB_Aera::SB_Aera()
{
	Area_Props_HWND = nullptr;

	Show_Physics_Debug = 0;
}


SB_Aera::~SB_Aera()
{
}


// *************************************************************************
// *		Add_Aera_To_Project:- Terry and Hazel Flanigan 2022			   *
// *************************************************************************
void SB_Aera::Add_Aera_To_Project(int Index,char* FileName,char* Resource_Location)
{
	//App->Log_Messageg("void SB_Aera::Add_Aera_To_Project(int Index,char* FileName,char* Resource_Location)");

	/*if (App->GDCL_Scene_Data->B_Area[Index])
	{
		if (App->GDCL_Scene_Data->B_Area[Index]->Area_Ent && App->GDCL_Scene_Data->B_Area[Index]->Area_Node)
		{
			App->GDCL_Scene_Data->B_Area[Index]->Area_Node->detachAllObjects();
			App->Ogre17->mSceneMgr->destroySceneNode(App->GDCL_Scene_Data->B_Area[Index]->Area_Node);
			App->Ogre17->mSceneMgr->destroyEntity(App->GDCL_Scene_Data->B_Area[Index]->Area_Ent);
			App->GDCL_Scene_Data->B_Area[Index]->Area_Ent = NULL;
			App->GDCL_Scene_Data->B_Area[Index]->Area_Node = NULL;

			delete App->GDCL_Scene_Data->B_Area[Index];
			App->GDCL_Scene_Data->B_Area[Index] = nullptr;
		}
	}*/

	App->GDCL_Scene_Data->B_Area[Index] = new Base_Area();
	Base_Area* Area = App->GDCL_Scene_Data->B_Area[Index];

	Area->Object_ID = 0; //App->Cl_Scene_Data->Object_ID_Counter;
	strcpy(Area->Area_FileName, FileName);
	strcpy(Area->Area_Resource_Path, Resource_Location); // with back slash

	Area->Area_Ent = App->Ogre17->mSceneMgr->createEntity("UserMesh", Area->Area_FileName, App->GDCL_Scene_Data->Project_Resource_Group);
	Area->Area_Node = App->Ogre17->mSceneMgr->getRootSceneNode()->createChildSceneNode();
	Area->Area_Node->attachObject(Area->Area_Ent);

	Area->Area_Node->setVisible(true);
	Area->Area_Node->setPosition(0, 0, 0);
	Area->Area_Node->setScale(1, 1, 1);

	create_Area_Trimesh_New(Index,Area);

	Area->Usage = 0;// Enums::Usage_Room;

	App->GDCL_Scene_Data->Area_Added = 1;

}

// *************************************************************************
//			create_Aera_Trimesh_New:- Terry and Hazel Flanigan 2022		   *
// *************************************************************************
btBvhTriangleMeshShape* SB_Aera::create_Area_Trimesh_New(int Index,Base_Area* Object)
{
	
	// Get the mesh from the entity
	Ogre::MeshPtr myMesh = Object->Area_Ent->getMesh();
	Ogre::Mesh::SubMeshIterator SubMeshIter = myMesh->getSubMeshIterator();

	// Create the triangle mesh
	btTriangleMesh* triMesh = NULL;
	btVector3 vert0, vert1, vert2;
	int i = 0;

	while (SubMeshIter.hasMoreElements())
	{
		i = 0;
		Ogre::SubMesh* subMesh = SubMeshIter.getNext();
		Ogre::IndexData* indexData = subMesh->indexData;
		Ogre::VertexData* vertexData = subMesh->vertexData;

		// -------------------------------------------------------
		// Get the position element
		const Ogre::VertexElement* posElem = vertexData->vertexDeclaration->findElementBySemantic(Ogre::VES_POSITION);
		// Get a pointer to the vertex buffer
		Ogre::HardwareVertexBufferSharedPtr vBuffer = vertexData->vertexBufferBinding->getBuffer(posElem->getSource());
		// Get a pointer to the index buffer
		Ogre::HardwareIndexBufferSharedPtr iBuffer = indexData->indexBuffer;

		// -------------------------------------------------------
		// The vertices and indices used to create the triangle mesh
		std::vector<Ogre::Vector3> vertices;
		vertices.reserve(vertexData->vertexCount);
		std::vector<unsigned long> indices;
		indices.reserve(indexData->indexCount);

		// -------------------------------------------------------
		// Lock the Vertex Buffer (READ ONLY)
		unsigned char* vertex = static_cast<unsigned char*> (vBuffer->lock(Ogre::HardwareBuffer::HBL_READ_ONLY));
		float* pReal = NULL;

		for (size_t j = 0; j < vertexData->vertexCount; ++j, vertex += vBuffer->getVertexSize()) {
			posElem->baseVertexPointerToElement(vertex, &pReal);
			Ogre::Vector3 pt(pReal[0], pReal[1], pReal[2]);

			vertices.push_back(pt);
		}
		vBuffer->unlock();
		// -------------------------------------------------------
		bool use32bitindexes = (iBuffer->getType() == Ogre::HardwareIndexBuffer::IT_32BIT);

		// -------------------------------------------------------
		// Lock the Index Buffer (READ ONLY)
		unsigned long* pLong = static_cast<unsigned long*> (iBuffer->lock(Ogre::HardwareBuffer::HBL_READ_ONLY));
		unsigned short* pShort = reinterpret_cast<unsigned short*> (pLong);

		if (use32bitindexes) {
			for (size_t k = 0; k < indexData->indexCount; ++k) {
				//
				indices.push_back(pLong[k]);
			}
		}
		else {
			for (size_t k = 0; k < indexData->indexCount; ++k) {
				//
				indices.push_back(static_cast<unsigned long> (pShort[k]));
			}
		}
		iBuffer->unlock();

		// -------------------------------------------------------
		// We now have vertices and indices ready to go
		// ----

		if (triMesh == nullptr)
		{
			triMesh = new btTriangleMesh(use32bitindexes);
		}

		for (size_t y = 0; y < indexData->indexCount / 3; y++) {
			// Set each vertex
			vert0.setValue(vertices[indices[i]].x, vertices[indices[i]].y, vertices[indices[i]].z);
			vert1.setValue(vertices[indices[i + 1]].x, vertices[indices[i + 1]].y, vertices[indices[i + 1]].z);
			vert2.setValue(vertices[indices[i + 2]].x, vertices[indices[i + 2]].y, vertices[indices[i + 2]].z);

			// Add the triangle into the triangle mesh
			triMesh->addTriangle(vert0, vert1, vert2);

			// Increase index count
			i += 3;
		}

	}

	const bool useQuantizedAABB = true;
	btBvhTriangleMeshShape* mShape = new btBvhTriangleMeshShape(triMesh, false, true);
	//mShape->buildOptimizedBvh();

	float x = Object->Area_Node->getPosition().x;
	float y = Object->Area_Node->getPosition().y;
	float z = Object->Area_Node->getPosition().z;

	Object->Physics_Pos = Ogre::Vector3(x, y, z);
	Object->Physics_Rot = Ogre::Vector3(0, 0, 0);
	Object->Physics_Quat = Ogre::Quaternion(1, 0, 0, 0);

	btVector3 inertia(0, 0, 0);
	mShape->calculateLocalInertia(0.0, inertia);

	btTransform startTransform;
	startTransform.setIdentity();
	startTransform.setRotation(btQuaternion(0.0f, 0.0f, 0.0f, 1));
	btVector3 initialPosition(x, y, z);
	startTransform.setOrigin(initialPosition);

	btDefaultMotionState* myMotionState = new btDefaultMotionState(startTransform);

	//myMotionState = new btDefaultMotionState(btTransform(btQuaternion(0, 0, 0, 1), btVector3(0, 0, 0)));

	btRigidBody::btRigidBodyConstructionInfo rigidBodyCI
	(
		0,				// mass
		myMotionState,	// initial position
		mShape,			// collision shape of body
		inertia			// local inertia
	);

	Object->Phys_Body = new btRigidBody(rigidBodyCI);
	Object->Phys_Body->clearForces();
	Object->Phys_Body->setLinearVelocity(btVector3(0, 0, 0));
	Object->Phys_Body->setAngularVelocity(btVector3(0, 0, 0));
	Object->Phys_Body->setWorldTransform(startTransform);

	Object->Phys_Body->setCustomDebugColor(btVector3(0, 1, 1));
	int f = Object->Phys_Body->getCollisionFlags();
	Object->Phys_Body->setCollisionFlags(f | btCollisionObject::CF_DISABLE_VISUALIZE_OBJECT);

	Object->Type = Enums::Bullet_Type_Static;
	Object->Shape = Enums::Shape_TriMesh;


	Object->Phys_Body->setUserIndex(123);
	Object->Phys_Body->setUserIndex2(Index);

	Object->Collect_Object_Data();

	App->GDCL_Bullet->dynamicsWorld->addRigidBody(Object->Phys_Body);

	Object->Physics_Valid = 1;
	return mShape;
}

// *************************************************************************
// *	  Set_Environment_Defaults:- Terry and Hazel Flanigan 2022		   *
// *************************************************************************
void SB_Aera::Set_Environment_Defaults(int Index)
{
	//----------------------- Sound
	strcpy(App->GDCL_Scene_Data->B_Area[0]->S_Environment[0]->Sound_File, "The_Sun.ogg");
	App->GDCL_Scene_Data->B_Area[0]->S_Environment[0]->SndFile = NULL;
	App->GDCL_Scene_Data->B_Area[0]->S_Environment[0]->Play = 1;
	App->GDCL_Scene_Data->B_Area[0]->S_Environment[0]->Loop = 1;
	App->GDCL_Scene_Data->B_Area[0]->S_Environment[0]->SndVolume = 0.5;

	//----------------------- Light
	App->GDCL_Scene_Data->B_Area[0]->S_Environment[0]->AmbientColour.x = 1;
	App->GDCL_Scene_Data->B_Area[0]->S_Environment[0]->AmbientColour.y = 1;
	App->GDCL_Scene_Data->B_Area[0]->S_Environment[0]->AmbientColour.z = 1;

	App->GDCL_Scene_Data->B_Area[0]->S_Environment[0]->DiffuseColour.x = 0;
	App->GDCL_Scene_Data->B_Area[0]->S_Environment[0]->DiffuseColour.y = 0;
	App->GDCL_Scene_Data->B_Area[0]->S_Environment[0]->DiffuseColour.z = 0;

	App->GDCL_Scene_Data->B_Area[0]->S_Environment[0]->SpecularColour.x = 0;
	App->GDCL_Scene_Data->B_Area[0]->S_Environment[0]->SpecularColour.y = 0;
	App->GDCL_Scene_Data->B_Area[0]->S_Environment[0]->SpecularColour.z = 0;

	App->GDCL_Scene_Data->B_Area[0]->S_Environment[0]->Light_Position.x = 0;
	App->GDCL_Scene_Data->B_Area[0]->S_Environment[0]->Light_Position.y = 0;
	App->GDCL_Scene_Data->B_Area[0]->S_Environment[0]->Light_Position.z = 0;

	// Sky
	App->GDCL_Scene_Data->B_Area[0]->S_Environment[0]->Curvature = 15;
	App->GDCL_Scene_Data->B_Area[0]->S_Environment[0]->Distance = 4000;
	App->GDCL_Scene_Data->B_Area[0]->S_Environment[0]->Enabled = 0;
	strcpy(App->GDCL_Scene_Data->B_Area[0]->S_Environment[0]->Material, "Examples/CloudySky");
	App->GDCL_Scene_Data->B_Area[0]->S_Environment[0]->Tiling = 15;
	App->GDCL_Scene_Data->B_Area[0]->S_Environment[0]->type = 1;

	// Fog
	App->GDCL_Scene_Data->B_Area[0]->S_Environment[0]->Fog_On = 0;
	App->GDCL_Scene_Data->B_Area[0]->S_Environment[0]->Fog_Mode = FOG_LINEAR;
	App->GDCL_Scene_Data->B_Area[0]->S_Environment[0]->Fog_Density = 0.001000;
	App->GDCL_Scene_Data->B_Area[0]->S_Environment[0]->Fog_Start = 50;
	App->GDCL_Scene_Data->B_Area[0]->S_Environment[0]->Fog_End = 300;
	App->GDCL_Scene_Data->B_Area[0]->S_Environment[0]->Fog_Colour = Ogre::Vector3(1, 1, 1);
}