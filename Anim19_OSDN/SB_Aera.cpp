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
#include "resource.h"
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
// *	  					Reset_Class Bernie							   *
// *************************************************************************
void SB_Aera::Reset_Class(void)
{
	int Count = 0;

	while (Count < App->SBC_Scene->Area_Count) // Remove Ogre Objects
	{
		if (App->SBC_Scene->SBC_Base_Area[Count])
		{
			if (App->SBC_Scene->SBC_Base_Area[Count]->Area_Ent && App->SBC_Scene->SBC_Base_Area[Count]->Area_Node)
			{
				App->Cl19_Ogre->mSceneMgr->destroySceneNode(App->SBC_Scene->SBC_Base_Area[Count]->Area_Node);
				App->Cl19_Ogre->mSceneMgr->destroyEntity(App->SBC_Scene->SBC_Base_Area[Count]->Area_Ent);
				App->SBC_Scene->SBC_Base_Area[Count]->Area_Ent = nullptr;
				App->SBC_Scene->SBC_Base_Area[Count]->Area_Node = nullptr;
			}

			delete App->SBC_Scene->SBC_Base_Area[Count];
			App->SBC_Scene->SBC_Base_Area[Count] = nullptr;
		}

		Count++;
	}

	App->SBC_Scene->Area_Count = 0;
	App->SBC_Scene->Area_Added = 0;

}

// *************************************************************************
// *	  				Start_Area_PropsPanel Terry Bernie				   *
// *************************************************************************
bool SB_Aera::Start_Area_PropsPanel()
{

	Area_Props_HWND = CreateDialog(App->hInst, (LPCTSTR)IDD_PROPS_AERA, App->SBC_Properties->Properties_Dlg_hWnd, (DLGPROC)Area_PropsPanel_Proc);
	return 1;
}
// *************************************************************************
// *				Area_PropsPanel_Proc  Terry Bernie					   *
// *************************************************************************
LRESULT CALLBACK SB_Aera::Area_PropsPanel_Proc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{

	switch (message)
	{
	case WM_INITDIALOG:
	{
		
		SendDlgItemMessage(hDlg, IDC_PHYSICSAREADEBUG, WM_SETFONT, (WPARAM)App->Font_CB15, MAKELPARAM(TRUE, 0));

		return TRUE;
	}
	case WM_CTLCOLORSTATIC:
	{
		return FALSE;
	}

	case WM_CTLCOLORDLG:
	{
		return (LONG)App->DialogBackGround;
	}

	case WM_NOTIFY:
	{
		LPNMHDR some_item = (LPNMHDR)lParam;

		if (some_item->idFrom == IDC_PHYSICSAREADEBUG && some_item->code == NM_CUSTOMDRAW)
		{
			LPNMCUSTOMDRAW item = (LPNMCUSTOMDRAW)some_item;
			App->Custom_Button_Toggle(item, App->SBC_Aera->Show_Physics_Debug);
			return CDRF_DODEFAULT;
		}
		
		return CDRF_DODEFAULT;
	}

	case WM_COMMAND:

		if (LOWORD(wParam) == IDC_PHYSICSAREADEBUG)
		{
			int f = App->SBC_Scene->SBC_Base_Area[0]->Phys_Body->getCollisionFlags();

			if (App->SBC_Aera->Show_Physics_Debug == 1)
			{
				App->SBC_Aera->Show_Physics_Debug = 0;
				App->SBC_Scene->SBC_Base_Area[0]->Phys_Body->setCollisionFlags(f ^ btCollisionObject::CF_DISABLE_VISUALIZE_OBJECT);

				App->Cl19_Ogre->BulletListener->Render_Debug_Flag = 0;
				App->Cl19_Ogre->RenderFrame();
				App->Cl19_Ogre->BulletListener->Render_Debug_Flag = 1;
			}
			else
			{
				App->SBC_Aera->Show_Physics_Debug = 1;
				App->SBC_Scene->SBC_Base_Area[0]->Phys_Body->setCollisionFlags(f ^ btCollisionObject::CF_DISABLE_VISUALIZE_OBJECT);
			}

			return 1;
		}


		break;
	}
	return FALSE;
}

// *************************************************************************
// *						Hide_Area_Dlg Terry Bernie 					   *
// *************************************************************************
void SB_Aera::Hide_Area_Dlg(bool Show)
{
	ShowWindow(Area_Props_HWND, Show);
}

// *************************************************************************
// *					Add_Area Terry Flanigan 						   *
// *************************************************************************
void SB_Aera::Add_Area()
{
	//char ConNum[256];
	//char ATest[256];
	/*strcpy_s(ATest, "GDEnt_");
	_itoa(Index, ConNum, 10);
	strcat(ATest, ConNum);*/

	int Index = App->SBC_Scene->Area_Count;


	if (App->SBC_Scene->SBC_Base_Area[Index])
	{
		if (App->SBC_Scene->SBC_Base_Area[Index]->Area_Ent && App->SBC_Scene->SBC_Base_Area[Index]->Area_Node)
		{
			App->SBC_Scene->SBC_Base_Area[Index]->Area_Node->detachAllObjects();
			App->Cl19_Ogre->mSceneMgr->destroySceneNode(App->SBC_Scene->SBC_Base_Area[Index]->Area_Node);
			App->Cl19_Ogre->mSceneMgr->destroyEntity(App->SBC_Scene->SBC_Base_Area[Index]->Area_Ent);
			App->SBC_Scene->SBC_Base_Area[Index]->Area_Ent = NULL;
			App->SBC_Scene->SBC_Base_Area[Index]->Area_Node = NULL;

			delete App->SBC_Scene->SBC_Base_Area[Index];
			App->SBC_Scene->SBC_Base_Area[Index] = nullptr;
		}
	}

	App->SBC_Scene->SBC_Base_Area[Index] = new Base_Area();
	App->SBC_Scene->SBC_Base_Area[Index]->Object_ID = 0; //App->Cl_Scene_Data->Object_ID_Counter;

	Base_Area* Object = App->SBC_Scene->SBC_Base_Area[Index];

	Ogre::ResourceGroupManager::getSingleton().destroyResourceGroup(App->Cl19_Ogre->Level_Resource_Group);
	Ogre::ResourceGroupManager::getSingleton().createResourceGroup(App->Cl19_Ogre->Level_Resource_Group);

	App->Say(App->CL_Vm_Model->Model_FolderPath);

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

	Object->Area_Ent = App->Cl19_Ogre->mSceneMgr->createEntity("UserMesh", App->CL_Vm_Model->FileName, App->Cl19_Ogre->Level_Resource_Group);
	Object->Area_Node = App->Cl19_Ogre->mSceneMgr->getRootSceneNode()->createChildSceneNode();
	Object->Area_Node->attachObject(Object->Area_Ent);

	Object->Area_Node->setVisible(true);
	Object->Area_Node->setPosition(0, 0, 0);
	Object->Area_Node->setScale(1, 1, 1);

	create_Area_Trimesh(Object);

	Object->Usage = Enums::Usage_Room;

	App->SBC_Scene->Area_Added = 1;

	App->Cl_Grid->Grid_SetVisible(1);

	App->SBC_Scene->Area_Count++;
}

// *************************************************************************
//						create_Aera_TrimeshTerry Bernie					   *
// *************************************************************************
btBvhTriangleMeshShape* SB_Aera::create_Area_Trimesh(Base_Area* Object)
{
	int Index = App->SBC_Scene->Area_Count;

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

	App->Cl_Bullet->dynamicsWorld->addRigidBody(Object->Phys_Body);

	Object->Physics_Valid = 1;
	return mShape;
}

//---------------------------------------------------------------------------------- New 24/07/22

// *************************************************************************
// *					Add_Aera_To_Project Terry Bernie 				   *
// *************************************************************************
void SB_Aera::Add_Aera_To_Project(int Index,char* FileName,char* Resource_Location)
{

	if (App->SBC_Scene->SBC_Base_Area[Index])
	{
		if (App->SBC_Scene->SBC_Base_Area[Index]->Area_Ent && App->SBC_Scene->SBC_Base_Area[Index]->Area_Node)
		{
			App->SBC_Scene->SBC_Base_Area[Index]->Area_Node->detachAllObjects();
			App->Cl19_Ogre->mSceneMgr->destroySceneNode(App->SBC_Scene->SBC_Base_Area[Index]->Area_Node);
			App->Cl19_Ogre->mSceneMgr->destroyEntity(App->SBC_Scene->SBC_Base_Area[Index]->Area_Ent);
			App->SBC_Scene->SBC_Base_Area[Index]->Area_Ent = NULL;
			App->SBC_Scene->SBC_Base_Area[Index]->Area_Node = NULL;

			delete App->SBC_Scene->SBC_Base_Area[Index];
			App->SBC_Scene->SBC_Base_Area[Index] = nullptr;
		}
	}

	App->SBC_Scene->SBC_Base_Area[Index] = new Base_Area();
	Base_Area* Area = App->SBC_Scene->SBC_Base_Area[Index];

	Area->Object_ID = 0; //App->Cl_Scene_Data->Object_ID_Counter;
	strcpy(Area->Area_FileName, FileName);
	strcpy(Area->Area_Resource_Path, Resource_Location); // with back slash

	bool Test = Ogre::ResourceGroupManager::getSingleton().resourceGroupExists(App->SBC_Import_Room->TempResourceGroup);
	if (Test == 1)
	{
		Ogre::ResourceGroupManager::getSingleton().destroyResourceGroup(App->SBC_Import_Room->TempResourceGroup);
	}

	Ogre::ResourceGroupManager::getSingleton().createResourceGroup(App->SBC_Import_Room->TempResourceGroup);

	Ogre::ResourceGroupManager::getSingleton().addResourceLocation(Resource_Location,
		"FileSystem",
		App->SBC_Import_Room->TempResourceGroup);

	try
	{
		Ogre::ResourceGroupManager::getSingleton().initialiseAllResourceGroups();
	}
	catch (...)
	{

	}

	Area->Area_Ent = App->Cl19_Ogre->mSceneMgr->createEntity("UserMesh", Area->Area_FileName, App->Cl19_Ogre->Level_Resource_Group);
	Area->Area_Node = App->Cl19_Ogre->mSceneMgr->getRootSceneNode()->createChildSceneNode();
	Area->Area_Node->attachObject(Area->Area_Ent);

	Area->Area_Node->setVisible(true);
	Area->Area_Node->setPosition(0, 0, 0);
	Area->Area_Node->setScale(1, 1, 1);

	create_Area_Trimesh_New(Index,Area);

	Area->Usage = Enums::Usage_Room;
}

// *************************************************************************
//					create_Aera_Trimesh_New Terry Bernie				   *
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

	App->Cl_Bullet->dynamicsWorld->addRigidBody(Object->Phys_Body);

	Object->Physics_Valid = 1;
	return mShape;
}