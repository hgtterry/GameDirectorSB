#include "stdafx.h"
#include "GD19_App.h"
#include "EQ15_Ogre_Import.h"


EQ15_Ogre_Import::EQ15_Ogre_Import()
{
}


EQ15_Ogre_Import::~EQ15_Ogre_Import()
{
}

// *************************************************************************
// *					Load_OgreModel Terry Flanigan 					   *
// *************************************************************************
bool EQ15_Ogre_Import::Load_OgreModel(void)
{
	/*NoTexture = 0;
	NoMaterialFileFound = 0;*/

	AddToScene();

	Create_MeshGroups();

	Extract_Mesh_Two();

	/*App->CL_Model_Data->HasMesh = 1;

	App->CL_Model_Data->Create_BondingBox_Model();

	Get_SkeletonInstance();

	Get_BoneNames();

	Get_Motions();

	Get_Textures();

	bool SkellAnimation = App->Cl_Ogre->OgreModel_Ent->hasSkeleton();
	Ogre::SkeletonInstance *skeletonInstance = App->Cl_Ogre->OgreModel_Ent->getSkeleton();

	if (skeletonInstance && SkellAnimation == 1)
	{
	if (App->CL_Model_Data->MotionCount > 0)
	{
	Ogre::Animation *animation = skeletonInstance->getAnimation(0);
	strcpy(App->CL_Motions->SelectedMotion, animation->getName().c_str());
	strcpy(App->CL_Motions->Decode_MotionByName, App->CL_Motions->SelectedMotion);
	App->Cl_Ogre->OgreListener->Animate_State = App->Cl_Ogre->OgreModel_Ent->getAnimationState(App->CL_Motions->SelectedMotion);
	}
	}*/

	return 1;
}

// *************************************************************************
// *					AddToScene Terry Flanigan 						   *
// *************************************************************************
void EQ15_Ogre_Import::AddToScene(void)
{

	if (App->Cl19_Ogre->OgreModel_Ent && App->Cl19_Ogre->OgreModel_Node)
	{
		App->Cl19_Ogre->OgreModel_Node->detachAllObjects();
		App->Cl19_Ogre->mSceneMgr->destroySceneNode(App->Cl19_Ogre->OgreModel_Node);
		App->Cl19_Ogre->mSceneMgr->destroyEntity(App->Cl19_Ogre->OgreModel_Ent);
		App->Cl19_Ogre->OgreModel_Ent = NULL;
		App->Cl19_Ogre->OgreModel_Node = NULL;
	}

	Ogre::ResourceGroupManager::getSingleton().destroyResourceGroup(App->Cl19_Ogre->TempResourceGroup);
	Ogre::ResourceGroupManager::getSingleton().createResourceGroup(App->Cl19_Ogre->TempResourceGroup);

	Ogre::ResourceGroupManager::getSingleton().addResourceLocation(App->CL_Vm_Model->Texture_FolderPath,
		"FileSystem",
		App->Cl19_Ogre->TempResourceGroup);

	try
	{
		Ogre::ResourceGroupManager::getSingleton().initialiseAllResourceGroups();
	}
	catch (...)
	{

	}

	App->Cl19_Ogre->OgreModel_Ent = App->Cl19_Ogre->mSceneMgr->createEntity("UserMesh", App->CL_Vm_Model->FileName, App->Cl19_Ogre->TempResourceGroup);
	App->Cl19_Ogre->OgreModel_Node = App->Cl19_Ogre->mSceneMgr->getRootSceneNode()->createChildSceneNode();
	App->Cl19_Ogre->OgreModel_Node->attachObject(App->Cl19_Ogre->OgreModel_Ent);

	App->Cl19_Ogre->OgreModel_Node->setVisible(true);
	App->Cl19_Ogre->OgreModel_Node->setPosition(0, 0, 0);
	App->Cl19_Ogre->OgreModel_Node->setScale(1, 1, 1);

	App->Cl_Grid->Grid_SetVisible(1);
}

// *************************************************************************
// *					Create_MeshGroups Terry Flanigan		  	 	   *
// *************************************************************************
void EQ15_Ogre_Import::Create_MeshGroups()
{
	char GroupName[255];
	char GroupNum[255];

	int SubMeshCount = App->Cl19_Ogre->OgreModel_Ent->getNumSubEntities();

	int Count = 0;
	while (Count<SubMeshCount)
	{

		App->CL_Vm_Model->Create_S_MeshGroup(Count); // Create new Mesh Group
		App->CL_Vm_Model->S_MeshGroup[Count]->GroupVertCount = 0;
		App->CL_Vm_Model->S_MeshGroup[Count]->MaterialIndex = -1;

		//App->CL_Model_Data->S_MeshGroup[Count]->EqIndex = Count+1;
		//App->CL_FBX->EqIndexCount++;

		//App->S_MeshGroup[Count]->MaterialIndex = mesh->mMaterialIndex;

		strcpy(App->CL_Vm_Model->S_MeshGroup[Count]->Text_FileName, "No_Texture");

		_itoa(Count, GroupNum, 10);
		strcpy(GroupName, "Group_");
		strcat(GroupName, GroupNum);

		strcpy(App->CL_Vm_Model->S_MeshGroup[Count]->GroupName, GroupName);

		//---------------
		Ogre::SubMesh const *subMesh = App->Cl19_Ogre->OgreModel_Ent->getSubEntity(Count)->getSubMesh();
		strcpy(App->CL_Vm_Model->S_MeshGroup[Count]->MaterialName, subMesh->getMaterialName().c_str());

		//subMesh->useSharedVertices;

		App->CL_Vm_Model->S_MeshGroup[Count]->GroupVertCount = subMesh->vertexData->vertexCount;
		App->CL_Vm_Model->S_MeshGroup[Count]->IndicesCount = subMesh->vertexData->vertexCount;
		//---------------

		Count++;
	}

	App->CL_Vm_Model->TextureCount = SubMeshCount;
	App->CL_Vm_Model->GroupCount = SubMeshCount;
}

// *************************************************************************
// *						Extract_Mesh_Two				   		 	   *
// *************************************************************************
bool EQ15_Ogre_Import::Extract_Mesh_Two()
{
	//int FaceCount = 0;
	//int FaceNum = 0;
	//int FaceIndexNum = 0;
	//int mFaceIndex = 0;
	//int xx = 0;
	//size_t vertex_count, index_count;
	//Vector3* vertices;
	//Vector3* normals;
	//unsigned long* indices;

	//Ogre::int16* BoneIndices;	// Bone Index

	//int SubMeshCount = App->Cl19_Ogre->OgreModel_Ent->getNumSubEntities();

	//unsigned int Vertloop = 0;
	//unsigned int Faceloop = 0;
	//int Count = 0;

	//while (Count<SubMeshCount)
	//{
	//	Get_SubPoseMeshInstance(App->Cl19_Ogre->OgreModel_Ent->getMesh(), vertex_count, vertices, index_count, indices, Count, BoneIndices);

	//	int mUVTest = NewGet_SubPoseTextureUV(App->Cl19_Ogre->OgreModel_Ent->getMesh(), Count);
	//	NewGet_SubPoseNormals(App->Cl19_Ogre->OgreModel_Ent->getMesh(), vertex_count, normals, Count);


	//	App->CL_Vm_Model->S_MeshGroup[Count]->vertex_Data.resize(index_count);
	//	App->CL_Vm_Model->S_MeshGroup[Count]->Normal_Data.resize(index_count);
	//	App->CL_Vm_Model->S_MeshGroup[Count]->MapCord_Data.resize(index_count);
	//	App->CL_Vm_Model->S_MeshGroup[Count]->Face_Data.resize(index_count);
	//	App->CL_Vm_Model->S_MeshGroup[Count]->FaceIndex_Data.resize(index_count);

	//	App->CL_Vm_Model->S_MeshGroup[Count]->BoneIndex_Data.resize(index_count);

	//	FaceIndexNum = 0;
	//	int Faceit = 0;
	//	FaceCount = 0;
	//	Vertloop = 0;
	//	xx = 0;
	//	while (Vertloop < vertex_count) // Process Vertices
	//	{
	//		App->CL_Vm_Model->S_MeshGroup[Count]->vertex_Data[Vertloop].x = vertices[Vertloop].x;
	//		App->CL_Vm_Model->S_MeshGroup[Count]->vertex_Data[Vertloop].y = vertices[Vertloop].y;
	//		App->CL_Vm_Model->S_MeshGroup[Count]->vertex_Data[Vertloop].z = vertices[Vertloop].z;

	//		App->CL_Vm_Model->S_MeshGroup[Count]->BoneIndex_Data[Vertloop].Index = BoneIndices[Vertloop]; // Bone Index 

	//		if (mUVTest)
	//		{
	//			App->CL_Vm_Model->S_MeshGroup[Count]->MapCord_Data[Vertloop].u = MeshTextureCoords[Vertloop].x;
	//			App->CL_Vm_Model->S_MeshGroup[Count]->MapCord_Data[Vertloop].v = 1 - MeshTextureCoords[Vertloop].y;
	//		}

	//		App->CL_Vm_Model->S_MeshGroup[Count]->Normal_Data[Vertloop].x = normals[Vertloop].x;
	//		App->CL_Vm_Model->S_MeshGroup[Count]->Normal_Data[Vertloop].y = normals[Vertloop].y;
	//		App->CL_Vm_Model->S_MeshGroup[Count]->Normal_Data[Vertloop].z = normals[Vertloop].z;

	//		Vertloop++;
	//	}

	//	FaceIndexNum = 0;
	//	Faceloop = 0;
	//	while (Faceloop < index_count) // Process Faces
	//	{
	//		App->CL_Vm_Model->S_MeshGroup[Count]->Face_Data[FaceIndexNum].a = indices[Faceloop];
	//		Faceloop++;
	//		App->CL_Vm_Model->S_MeshGroup[Count]->Face_Data[FaceIndexNum].b = indices[Faceloop];
	//		Faceloop++;
	//		App->CL_Vm_Model->S_MeshGroup[Count]->Face_Data[FaceIndexNum].c = indices[Faceloop];
	//		Faceloop++;

	//		FaceIndexNum++;

	//		App->CL_Vm_Model->S_MeshGroup[Count]->FaceIndex_Data[xx].Index = mFaceIndex;

	//		xx++;
	//		mFaceIndex++;
	//	}

	//	App->CL_Vm_Model->S_MeshGroup[Count]->GroupFaceCount = FaceIndexNum;
	//	App->CL_Vm_Model->S_MeshGroup[Count]->GroupVertCount = Vertloop;
	//	App->CL_Vm_Model->S_MeshGroup[Count]->IndicesCount = Vertloop;

	//	App->CL_Vm_Model->VerticeCount = App->CL_Vm_Model->VerticeCount + Vertloop;
	//	App->CL_Vm_Model->FaceCount = App->CL_Vm_Model->FaceCount + FaceIndexNum;


	//	GetBoneAssignment(App->Cl19_Ogre->OgreModel_Ent->getMesh(), Count, 0);

	//	Count++;
	//}

	return 1;
}

// *************************************************************************
// *					Get_SubPoseMeshInstance Terry Bernie			   *
// *************************************************************************
void EQ15_Ogre_Import::Get_SubPoseMeshInstance(Ogre::MeshPtr mesh,
	size_t &vertex_count,
	Ogre::Vector3* &vertices,
	size_t &index_count,
	unsigned long* &indices,
	int SubMesh,
	Ogre::int16* &BoneIndices)
{
	bool added_shared = false;
	size_t current_offset = 0;
	size_t shared_offset = 0;
	size_t next_offset = 0;
	size_t index_offset = 0;


	const Vector3 &position = Vector3::ZERO;
	const Quaternion &orient = Quaternion::IDENTITY;
	const Vector3 &scale = Vector3::UNIT_SCALE;

	vertex_count = index_count = 0;
	Ogre::SubMesh* submesh = mesh->getSubMesh(SubMesh);

	vertex_count = submesh->vertexData->vertexCount;
	Ogre::SubMesh::VertexBoneAssignmentList plist = submesh->getBoneAssignments();

	index_count = submesh->indexData->indexCount;

	// Allocate space for the vertices and indices
	vertices = new Ogre::Vector3[vertex_count];
	BoneIndices = new Ogre::int16[vertex_count]; // Create Space for Bone Indexs 
	indices = new unsigned long[index_count];

	//-------------------- Get Data
	Ogre::VertexData* vertex_data = submesh->useSharedVertices ? mesh->sharedVertexData : submesh->vertexData;

	if ((!submesh->useSharedVertices) || (submesh->useSharedVertices && !added_shared))
	{
		if (submesh->useSharedVertices)
		{
			added_shared = true;
			shared_offset = current_offset;
		}

		const Ogre::VertexElement* posElem =
			vertex_data->vertexDeclaration->findElementBySemantic(Ogre::VES_POSITION);

		Ogre::HardwareVertexBufferSharedPtr vbuf =
			vertex_data->vertexBufferBinding->getBuffer(posElem->getSource());

		unsigned char* vertex =
			static_cast<unsigned char*>(vbuf->lock(Ogre::HardwareBuffer::HBL_READ_ONLY));

		float* pReal;

		if (App->Cl19_Ogre->OgreModel_Ent->hasSkeleton() == 1)
		{
			Ogre::SubMesh::BoneAssignmentIterator itor = submesh->getBoneAssignmentIterator();

			for (size_t j = 0; j < vertex_data->vertexCount; ++j, vertex += vbuf->getVertexSize())
			{
				Ogre::VertexBoneAssignment_s bb = itor.getNext();
				posElem->baseVertexPointerToElement(vertex, &pReal);
				Ogre::Vector3 pt(pReal[0], pReal[1], pReal[2]);
				vertices[current_offset + j] = (orient * (pt * scale)) + position;
				BoneIndices[j] = bb.boneIndex;
			}
		}
		else
		{
			for (size_t j = 0; j < vertex_data->vertexCount; ++j, vertex += vbuf->getVertexSize())
			{
				posElem->baseVertexPointerToElement(vertex, &pReal);
				Ogre::Vector3 pt(pReal[0], pReal[1], pReal[2]);
				vertices[current_offset + j] = (orient * (pt * scale)) + position;
			}
		}

		vbuf->unlock();
		next_offset += vertex_data->vertexCount;
	}

	Ogre::IndexData* index_data = submesh->indexData;
	size_t numTris = index_data->indexCount / 3;
	Ogre::HardwareIndexBufferSharedPtr ibuf = index_data->indexBuffer;

	bool use32bitindexes = (ibuf->getType() == Ogre::HardwareIndexBuffer::IT_32BIT);

	unsigned long* pLong = static_cast<unsigned long*>(ibuf->lock(Ogre::HardwareBuffer::HBL_READ_ONLY));
	unsigned short* pShort = reinterpret_cast<unsigned short*>(pLong);

	size_t offset = (submesh->useSharedVertices) ? shared_offset : current_offset;

	if (use32bitindexes)
	{
		for (size_t k = 0; k < numTris * 3; ++k)
		{
			indices[index_offset++] = pLong[k] + static_cast<unsigned long>(offset);
		}
	}
	else
	{
		for (size_t k = 0; k < numTris * 3; ++k)
		{
			indices[index_offset++] = static_cast<unsigned long>(pShort[k]) +
				static_cast<unsigned long>(offset);
		}
	}

	ibuf->unlock();
	current_offset = next_offset;
}
