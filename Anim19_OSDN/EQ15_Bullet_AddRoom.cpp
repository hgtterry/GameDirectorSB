/*
Copyright(c) Equity15 2019 Inflanite Software W.T.Flanigan H.C.Flanigan

This software is provided 'as-is', without any express or implied
warranty.In no event will the authors be held liable for any damages
arising from the use of this software.

Permission is granted to anyone to use this software for any purpose,
including commercial applications, and to alter it and redistribute it
freely, subject to the following restrictions :

1. The origin of this software must not be misrepresented; you must not
claim that you wrote the original software.If you use this software
in a product, an acknowledgment in the product documentation would be
appreciated but is not required.

2. Altered source versions must be plainly marked as such, and must not be
misrepresented as being the original software.

3. This notice may not be removed or altered from any source
distribution.
*/

#include "stdafx.h"
#include "GD19_App.h"
#include "EQ15_Bullet_AddRoom.h"


EQ15_Bullet_AddRoom::EQ15_Bullet_AddRoom()
{
}


EQ15_Bullet_AddRoom::~EQ15_Bullet_AddRoom()
{
}


// *************************************************************************
// *					AddToScene Terry Flanigan 						   *
// *************************************************************************
void EQ15_Bullet_AddRoom::AddToScene(bool Create_Player)
{
	int Index = 0;// App->Cl_Scene_Data->ObjectCount;


	if (App->Cl_Scene_Data->Cl_Object[Index])
	{
		if (App->Cl_Scene_Data->Cl_Object[Index]->OgreEntity && App->Cl_Scene_Data->Cl_Object[Index]->OgreNode)
		{
			App->Cl_Scene_Data->Cl_Object[Index]->OgreNode->detachAllObjects();
			App->Cl19_Ogre->mSceneMgr->destroySceneNode(App->Cl_Scene_Data->Cl_Object[Index]->OgreNode);
			App->Cl19_Ogre->mSceneMgr->destroyEntity(App->Cl_Scene_Data->Cl_Object[Index]->OgreEntity);
			App->Cl_Scene_Data->Cl_Object[Index]->OgreEntity = NULL;
			App->Cl_Scene_Data->Cl_Object[Index]->OgreNode = NULL;

			delete App->Cl_Scene_Data->Cl_Object[Index];
			App->Cl_Scene_Data->Cl_Object[Index] = nullptr;
		}
	}

	App->Cl_Scene_Data->Cl_Object[Index] = new GD19_Objects();
	App->Cl_Scene_Data->Cl_Object[Index]->Object_ID = 0;// App->Cl_Scene_Data->Object_ID_Counter;

	GD19_Objects* Object = App->Cl_Scene_Data->Cl_Object[Index];

	Ogre::ResourceGroupManager::getSingleton().destroyResourceGroup(App->Cl19_Ogre->Level_Resource_Group);
	Ogre::ResourceGroupManager::getSingleton().createResourceGroup(App->Cl19_Ogre->Level_Resource_Group);

	Ogre::ResourceGroupManager::getSingleton().addResourceLocation(App->CL_Vm_Model->Model_FolderPath,
		"FileSystem",
		App->Cl19_Ogre->Level_Resource_Group);

	try
	{
		Ogre::ResourceGroupManager::getSingleton().initialiseAllResourceGroups();
	}
	catch (...)
	{

	}

	Object->OgreEntity = App->Cl19_Ogre->mSceneMgr->createEntity("UserMesh", App->CL_Vm_Model->FileName, App->Cl19_Ogre->Level_Resource_Group);
	Object->OgreNode = App->Cl19_Ogre->mSceneMgr->getRootSceneNode()->createChildSceneNode();
	Object->OgreNode->attachObject(Object->OgreEntity);

	Object->OgreNode->setVisible(true);
	Object->OgreNode->setPosition(0, 0, 0);
	Object->OgreNode->setScale(1, 1, 1);

	Object->create_New_Trimesh(Object->OgreEntity);

	Object->Usage = Enums::Usage_Room;

	App->SBC_Scene->Area_Added = 1;

	App->Cl_Grid->Grid_SetVisible(1);

	App->Cl_Scene_Data->ObjectCount++;
}

// *************************************************************************
//							Add_New_Room Terry							   *
// *************************************************************************
bool EQ15_Bullet_AddRoom::Add_New_Room(void)
{
	int Index = App->Cl_Scene_Data->ObjectCount;


	App->Cl_Scene_Data->Cl_Object[Index] = new GD19_Objects();
	App->Cl_Scene_Data->Cl_Object[Index]->Object_ID = App->Cl_Scene_Data->Object_ID_Counter;

	// Only on newly created objects
	App->Cl_Scene_Data->Object_ID_Counter++;

	GD19_Objects* Object = App->Cl_Scene_Data->Cl_Object[Index];

	strcpy(Object->Name, App->Cl_Mesh_Viewer->Object_Name);
	strcpy(Object->MeshName, App->Cl_Mesh_Viewer->Selected_MeshFile);
	strcpy(Object->MeshName_FullPath, App->Cl_Mesh_Viewer->Selected_MeshFile);

	char PathFile[256];
	char ConNum[256];
	char ATest[256];

	strcpy_s(ATest, "GDEnt_");
	_itoa(Index, ConNum, 10);
	strcat(ATest, ConNum);

	strcpy(PathFile, Object->MeshName);
	Object->OgreEntity = App->Cl19_Ogre->mSceneMgr->createEntity(ATest, PathFile, App->Cl19_Ogre->App_Resource_Group);
	Object->OgreNode = App->Cl19_Ogre->mSceneMgr->getRootSceneNode()->createChildSceneNode();
	Object->OgreNode->attachObject(Object->OgreEntity);

	Object->OgreNode->setVisible(true);
	Object->OgreNode->setScale(Object->Mesh_Scale);

	Ogre::Vector3 Pos = App->Cl_Objects_Com->Centre_of_Trimesh(Index);
	Object->Mesh_Pos = Pos;
	Object->OgreNode->setPosition(Pos);

	//---------------------- Tri_Mesh

	Object->create_New_Trimesh(Object->OgreEntity);

	Object->Usage = Enums::Usage_Room;

	App->Cl_Scene_Data->Scene_Has_Area = 1;
	App->Cl_Scene_Data->SceneLoaded = 1;

	ShowWindow(App->GD_Properties_Hwnd, 1);

	App->Cl_Scene_Data->ObjectCount++;  // Must be last line

	return 1;
}

// *************************************************************************
//						create_New_TrimeshTerry Bernie					   *
// *************************************************************************
btBvhTriangleMeshShape* EQ15_Bullet_AddRoom::create_New_Trimesh(Ogre::Entity* ent)
{
	int Index = 0;// App->Cl_Scene_Data->ObjectCount;

	GD19_Objects* Object = App->Cl_Scene_Data->Cl_Object[Index];


	// Get the mesh from the entity
	Ogre::MeshPtr myMesh = ent->getMesh();
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

		//App->Say("here");
	}

	const bool useQuantizedAABB = true;
	btBvhTriangleMeshShape* mShape = new btBvhTriangleMeshShape(triMesh, false, true);
	//mShape->buildOptimizedBvh();

	float x = Object->OgreNode->getPosition().x;
	float y = Object->OgreNode->getPosition().y;
	float z = Object->OgreNode->getPosition().z;

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
		0,  // mass
		myMotionState,// initial position
		mShape,      // collision shape of body
		inertia   // local inertia
	);

	Object->bt_body = new btRigidBody(rigidBodyCI);
	Object->bt_body->clearForces();
	Object->bt_body->setLinearVelocity(btVector3(0, 0, 0));
	Object->bt_body->setAngularVelocity(btVector3(0, 0, 0));
	Object->bt_body->setWorldTransform(startTransform);

	Object->bt_body->setCustomDebugColor(btVector3(0, 1, 1));
	int f = Object->bt_body->getCollisionFlags();
	Object->bt_body->setCollisionFlags(f | btCollisionObject::CF_DISABLE_VISUALIZE_OBJECT);

	Object->Type = Enums::Bullet_Type_Static;
	Object->Shape = Enums::Shape_TriMesh;


	Object->bt_body->setUserIndex(123);
	Object->bt_body->setUserIndex2(Index);

	Object->Collect_Object_Data();

	App->Cl_Bullet->dynamicsWorld->addRigidBody(Object->bt_body);

	Object->Physics_Valid = 1;
	return mShape;
}
