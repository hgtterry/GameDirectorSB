/*
Copyright (c) 2022 GameDirectorSB and EquityME -- HGTInflanite Software W.T.Flanigan H.C.Flanigan

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
#include "SB_Com_Area.h"


SB_Com_Area::SB_Com_Area()
{
	
}

SB_Com_Area::~SB_Com_Area()
{
}

// *************************************************************************
// *	  		Reset_Class:- Terry and Hazel Flanigan 2022				   *
// *************************************************************************
void SB_Com_Area::Reset_Class(void)
{
	int Count = 0;

	while (Count < App->SBC_Scene->Area_Count) // Remove Ogre Objects
	{
		if (App->SBC_Scene->B_Area[Count])
		{
			if (App->SBC_Scene->B_Area[Count]->Area_Ent && App->SBC_Scene->B_Area[Count]->Area_Node)
			{
				App->SBC_Ogre->mSceneMgr->destroySceneNode(App->SBC_Scene->B_Area[Count]->Area_Node);
				App->SBC_Ogre->mSceneMgr->destroyEntity(App->SBC_Scene->B_Area[Count]->Area_Ent);
				App->SBC_Scene->B_Area[Count]->Area_Ent = nullptr;
				App->SBC_Scene->B_Area[Count]->Area_Node = nullptr;
			}

			delete App->SBC_Scene->B_Area[Count];
			App->SBC_Scene->B_Area[Count] = nullptr;
		}

		Count++;
	}

	App->SBC_Scene->Area_Count = 0;
	App->SBC_Scene->Area_Added = 0;

}

// *************************************************************************
//				Add_New_Area:- Terry and Hazel Flanigan 2022			   *
// *************************************************************************
bool SB_Com_Area::Add_New_Area()
{
	if (App->SBC_Scene->Area_Count == 0)
	{
		App->SBC_Project_Create->Add_First_New_Area();
	}
	else
	{
		int Index = App->SBC_Scene->Area_Count;

		App->SBC_Scene->B_Area[Index] = new Base_Area();
		Set_Area_Defaults(Index);

		Base_Area* Area = App->SBC_Scene->B_Area[Index];
		
		Area->This_Object_UniqueID = App->SBC_Scene->UniqueID_Area_Count;

		Ogre::Vector3 Pos = App->SBC_Object->GetPlacement(-50);
		Area->Mesh_Pos = Pos;

		Add_Aera_To_Project(Index, App->SBC_MeshViewer->Selected_MeshFile, App->SBC_MeshViewer->mResource_Folder);
		
		HTREEITEM Temp = App->SBC_FileView->Add_Item(App->SBC_FileView->FV_Areas_Folder, Area->Area_Name, Index, true);
		Area->FileViewItem = Temp;

		App->SBC_FileView->SelectItem(Area->FileViewItem);

		App->SBC_Scene->UniqueID_Area_Count++;
		App->SBC_Scene->Area_Count++;

		App->SBC_Scene->Scene_Modified = 1;
	}
	return 1;
}

// *************************************************************************
// *		Add_Aera_To_Project:- Terry and Hazel Flanigan 2022 		   *
// *************************************************************************
void SB_Com_Area::Add_Aera_To_Project(int Index, char* FileName, char* Resource_Location)
{
	char B_Name[MAX_PATH];
	char ConNum[MAX_PATH];

	char Mesh_File[MAX_PATH];
	strcpy(Mesh_File, FileName);

	Base_Area* Area = App->SBC_Scene->B_Area[Index];

	strcpy_s(B_Name, "Area_");
	_itoa(Index, ConNum, 10);
	strcat(B_Name, ConNum);
	strcpy(App->SBC_Scene->B_Area[Index]->Area_Name, B_Name);

	strcpy(Area->Area_FileName, FileName);
	strcpy(Area->Area_Resource_Path, Resource_Location); 

	Area->Area_Ent = App->SBC_Ogre->mSceneMgr->createEntity(App->SBC_Scene->B_Area[Index]->Area_Name, Mesh_File, App->SBC_Scene->Project_Resource_Group);
	Area->Area_Node = App->SBC_Ogre->mSceneMgr->getRootSceneNode()->createChildSceneNode();
	Area->Area_Node->attachObject(Area->Area_Ent);

	Area->Area_Node->setVisible(true);
	Area->Area_Node->setPosition(Area->Mesh_Pos);
	Area->Area_Node->setScale(Area->Mesh_Scale);
	Area->Area_Node->setOrientation(Area->Mesh_Quat);

	Create_Area_Trimesh(Index, Area);

	Area->Usage = Enums::Usage_Room;

	App->SBC_Scene->Area_Added = 1;
}

// *************************************************************************
// *		Create_Aera_Trimesh_New:- Terry and Hazel Flanigan 2022		   *
// *************************************************************************
btBvhTriangleMeshShape* SB_Com_Area::Create_Area_Trimesh(int Index, Base_Area* Object)
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

	App->SBC_Bullet->dynamicsWorld->addRigidBody(Object->Phys_Body);

	Set_Physics(Index);

	Object->Physics_Valid = 1;
	return mShape;
}

// *************************************************************************
// *	Get_BoundingBox_World_Centre:- Terry and Hazel Flanigan 2022	   *
// *************************************************************************
Ogre::Vector3 SB_Com_Area::Get_BoundingBox_World_Centre(int Object_Index)
{
	if (App->SBC_Scene->B_Area[Object_Index]->Shape == Enums::Shape_TriMesh)
	{
		Ogre::Vector3 Pos = App->SBC_Scene->B_Area[Object_Index]->Area_Node->getPosition();
		return Pos;
	}
	else
	{
		AxisAlignedBox worldAAB = App->SBC_Scene->B_Area[Object_Index]->Area_Ent->getBoundingBox();
		worldAAB.transformAffine(App->SBC_Scene->B_Area[Object_Index]->Area_Node->_getFullTransform());
		Ogre::Vector3 Centre = worldAAB.getCenter();

		return Centre;
	}
}

// *************************************************************************
//				Set_Physics:- Terry and Hazel Flanigan 2022				   *
// *************************************************************************
void SB_Com_Area::Set_Physics(int Index)
{
	float w = 0;
	float x = 0;
	float y = 0;
	float z = 0;

	// ----------- Position
	x = App->SBC_Scene->B_Area[Index]->Mesh_Pos.x;
	y = App->SBC_Scene->B_Area[Index]->Mesh_Pos.y;
	z = App->SBC_Scene->B_Area[Index]->Mesh_Pos.z;

	App->SBC_Scene->B_Area[Index]->Phys_Body->getWorldTransform().setOrigin(btVector3(x, y, z));
	App->SBC_Scene->B_Area[Index]->Physics_Pos = Ogre::Vector3(x, y, z);

	// ----------- Rotation
	App->SBC_Scene->B_Area[Index]->Physics_Quat = App->SBC_Scene->B_Area[Index]->Area_Node->getOrientation();

	w = App->SBC_Scene->B_Area[Index]->Physics_Quat.w;
	x = App->SBC_Scene->B_Area[Index]->Physics_Quat.x;
	y = App->SBC_Scene->B_Area[Index]->Physics_Quat.y;
	z = App->SBC_Scene->B_Area[Index]->Physics_Quat.z;

	App->SBC_Scene->B_Area[Index]->Phys_Body->getWorldTransform().setRotation(btQuaternion(x, y, z, w));

	// ----------- Scale
	Ogre::Vector3 Scale = App->SBC_Scene->B_Area[Index]->Area_Node->getScale();
	App->SBC_Scene->B_Area[Index]->Phys_Body->getCollisionShape()->setLocalScaling(btVector3(Scale.x, Scale.y, Scale.z));

	App->SBC_Scene->B_Area[Index]->Physics_Valid = 1;
}

// *************************************************************************
// *	  UpDate_Physics_And_Visuals:- Terry and Hazel Flanigan 2022 	   *
// *************************************************************************
void SB_Com_Area::UpDate_Physics_And_Visuals(int Index)
{
	if (App->SBC_Scene->B_Area[Index]->Shape == Enums::Shape_TriMesh)
	{

	}
	else
	{
		//Set_Physics_Position(Index);
	}


	App->SBC_Visuals->MarkerBB_Addjust(Index);

	// Needs Looking at
	App->SBC_Scene->B_Area[Index]->Altered = 1;
	App->SBC_FileView->Mark_Altered(App->SBC_Scene->B_Area[Index]->FileViewItem);
	App->SBC_Scene->Scene_Modified = 1;
}


// *************************************************************************
// *		Set_Area_Defaults:- Terry and Hazel Flanigan 2022		  	   *
// *************************************************************************
void SB_Com_Area::Set_Area_Defaults(int Index)
{
	// Actor Scale ------------------------------------------------------
	App->SBC_Scene->B_Area[Index]->Mesh_Scale.x = 1;
	App->SBC_Scene->B_Area[Index]->Mesh_Scale.y = 1;
	App->SBC_Scene->B_Area[Index]->Mesh_Scale.z = 1;

	// Actor Pos
	App->SBC_Scene->B_Area[Index]->Mesh_Pos.x = 0;
	App->SBC_Scene->B_Area[Index]->Mesh_Pos.y = 0;
	App->SBC_Scene->B_Area[Index]->Mesh_Pos.z = 0;

	// Mesh Rotation
	App->SBC_Scene->B_Area[Index]->Mesh_Rot.x = 0;
	App->SBC_Scene->B_Area[Index]->Mesh_Rot.y = 0;
	App->SBC_Scene->B_Area[Index]->Mesh_Rot.z = 0;

	// Mesh Quat
	App->SBC_Scene->B_Area[Index]->Mesh_Quat.w = 1;
	App->SBC_Scene->B_Area[Index]->Mesh_Quat.x = 0;
	App->SBC_Scene->B_Area[Index]->Mesh_Quat.y = 0;
	App->SBC_Scene->B_Area[Index]->Mesh_Quat.z = 0;

	// Physics Scale ------------------------------------------------------
	App->SBC_Scene->B_Area[Index]->Physics_Scale.x = 1;
	App->SBC_Scene->B_Area[Index]->Physics_Scale.y = 1;
	App->SBC_Scene->B_Area[Index]->Physics_Scale.z = 1;

	// Physics Pos
	App->SBC_Scene->B_Area[Index]->Physics_Pos.x = 0;
	App->SBC_Scene->B_Area[Index]->Physics_Pos.y = 0;
	App->SBC_Scene->B_Area[Index]->Physics_Pos.z = 0;

	// Physics Rotation
	App->SBC_Scene->B_Area[Index]->Physics_Rot.x = 0;
	App->SBC_Scene->B_Area[Index]->Physics_Rot.y = 0;
	App->SBC_Scene->B_Area[Index]->Physics_Rot.z = 0;

	// Physics Quat
	App->SBC_Scene->B_Area[Index]->Physics_Quat.w = 1;
	App->SBC_Scene->B_Area[Index]->Physics_Quat.x = 0;
	App->SBC_Scene->B_Area[Index]->Physics_Quat.y = 0;
	App->SBC_Scene->B_Area[Index]->Physics_Quat.z = 0;
	App->SBC_Scene->B_Area[Index]->Physics_Valid = 0;
	return;
}
