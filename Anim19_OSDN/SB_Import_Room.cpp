#include "stdafx.h"
#include "GD19_App.h"
#include "SB_Import_Room.h"



SB_Import_Room::SB_Import_Room()
{
	Room_FileName[0] = 0,
	Room_Path_FileName[0] = 0,

	TempResourceGroup = "TemporyResourceGroup";
}


SB_Import_Room::~SB_Import_Room()
{
}

// *************************************************************************
// *						Room_Loader Terry Bernie					   *
// *************************************************************************
bool SB_Import_Room::Room_Loader(char* Extension, char* Extension2)
{
	int Result = Open_Room_File(Extension, Extension2, NULL);
	if (Result == 0)
	{
		return 1;
	}

	Ogre::ResourceGroupManager::getSingleton().createResourceGroup(TempResourceGroup);
	//App->EBC_Model->Clear_ModelData();

	Set_Paths();

	AddToScene();
	
	App->CL_Vm_Model->Model_Loaded = 1;

	App->SBC_Scene->Area_Added = 1;

	App->Cl_Grid->Grid_SetVisible(1);

	App->SBC_Scene->Area_Count++;

	App->Cl19_Ogre->OgreListener->GD_CameraMode = Enums::CamDetached;

	App->SBC_Player->Create_Player_Object();

	App->Cl_Bullet->Reset_Physics();
	App->SBC_Physics->Enable_Physics(1);

	App->SBC_Player->FileViewItem = App->SBC_FileView->Add_PlayerFile("Player", 0);
	App->SBC_FileView->Redraw_FileView();

	App->SBC_Scene->Scene_Loaded = 1;

	App->Cl_Scene_Data->Scene_Has_Area = 1;

	App->Say("Model Loaded");
	return 1;
}

// *************************************************************************
// *						Set_Paths Terry Bernie						   *
// *************************************************************************
void SB_Import_Room::Set_Paths(void)
{
	char Model_FolderPath[255];
	char Path_FileName[255];

	strcpy(FileName, Room_FileName);
	strcpy(Path_FileName, Room_Path_FileName);

	// Get Texture path assumed at this point to be where model is
	int len1 = strlen(FileName);
	int len2 = strlen(Path_FileName);
	strcpy(Model_FolderPath, Path_FileName);
	Model_FolderPath[len2 - len1] = 0;

	strcpy(Texture_FolderPath, Model_FolderPath);

}

// *************************************************************************
// *					AddToScene Terry Bernie 						   *
// *************************************************************************
void SB_Import_Room::AddToScene(void)
{
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
	Base_Area* Area = App->SBC_Scene->SBC_Base_Area[Index];

	Area->Object_ID = 0; //App->Cl_Scene_Data->Object_ID_Counter;
	strcpy(Area->Area_FileName, FileName);
	strcpy(Area->Area_Resource_Path, Texture_FolderPath); // with back slash

	Ogre::ResourceGroupManager::getSingleton().destroyResourceGroup(TempResourceGroup);
	Ogre::ResourceGroupManager::getSingleton().createResourceGroup(TempResourceGroup);

	Ogre::ResourceGroupManager::getSingleton().addResourceLocation(Texture_FolderPath,
		"FileSystem",
		TempResourceGroup);

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

	create_Area_Trimesh(Area);

	Area->Usage = Enums::Usage_Room;

}

// *************************************************************************
//						create_Aera_TrimeshTerry Bernie					   *
// *************************************************************************
btBvhTriangleMeshShape* SB_Import_Room::create_Area_Trimesh(Base_Area* Object)
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

// *************************************************************************
// *					Open_Room_File Terry Bernie						   *
// *************************************************************************
bool SB_Import_Room::Open_Room_File(char* Extension, char* Title, char* StartDirectory)
{
	strcpy(Room_FileName, "");
	strcpy(Room_Path_FileName, "");

	ZeroMemory(&ofn, sizeof(ofn));
	ofn.lStructSize = sizeof(ofn);
	ofn.hwndOwner = App->MainHwnd;
	ofn.hInstance = App->hInst;
	ofn.lpstrFile = Room_Path_FileName;						// full path and file name
	ofn.nMaxFile = sizeof(Room_Path_FileName);
	ofn.lpstrFilter = Extension;

	ofn.nFilterIndex = 1;
	ofn.lpstrFileTitle = Room_FileName;						// Just File Name
	ofn.nMaxFileTitle = sizeof(Room_FileName);;
	ofn.lpstrInitialDir = StartDirectory;
	ofn.lpstrTitle = Title;
	ofn.Flags = OFN_PATHMUSTEXIST |
		OFN_FILEMUSTEXIST |
		OFN_EXPLORER |
		OFN_HIDEREADONLY |
		OFN_FILEMUSTEXIST;

	if (GetOpenFileName(&ofn) == TRUE)
	{
		return 1;
	}
	return 0;
}