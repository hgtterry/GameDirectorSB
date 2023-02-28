#include "stdafx.h"
#include "ME_App.h"
#include "ME_Ogre3D.h"


ME_Ogre3D::ME_Ogre3D()
{
	OgreModel_Ent = nullptr;
	OgreModel_Node = nullptr;

	NoTexture = 0;
	NoMaterialFileFound = 0;

	TempResourceGroup = "TemporyResourceGroup";

	
}


ME_Ogre3D::~ME_Ogre3D()
{
}

// *************************************************************************
// *					Load_OgreModel Terry Bernie 					   *
// *************************************************************************
bool ME_Ogre3D::Load_OgreModel(void)
{
	Ogre::ResourceGroupManager::getSingleton().createResourceGroup(TempResourceGroup);

	NoTexture = 0;
	NoMaterialFileFound = 0;

	AddToScene();

	Create_MeshGroups();
	Extract_Mesh_Two();

	//App->CL_Model_Data->HasMesh = 1;

	App->CL_Model->Set_BondingBox_Model(1);

	Get_SkeletonInstance();

	Get_BoneNames();

	Get_Motions();

	Get_Textures();

	bool SkellAnimation = OgreModel_Ent->hasSkeleton();
	Ogre::SkeletonInstance *skeletonInstance = OgreModel_Ent->getSkeleton();

	if (skeletonInstance && SkellAnimation == 1)
	{
		if (App->CL_Model->MotionCount > 0)
		{
			Ogre::Animation *animation = skeletonInstance->getAnimation(0);
			strcpy(App->CL_Motions->Selected_Motion_Name, animation->getName().c_str());

			strcpy(App->CL_Motions->Decode_MotionByName, App->CL_Motions->Selected_Motion_Name);
			App->CL_Ogre->Ogre_Listener->Animate_State = OgreModel_Ent->getAnimationState(App->CL_Motions->Selected_Motion_Name);
		}
	}

	return 1;
}

// *************************************************************************
// *					AddToScene Terry Bernie 						   *
// *************************************************************************
void ME_Ogre3D::AddToScene(void)
{

	if (OgreModel_Ent && OgreModel_Node)
	{
		OgreModel_Node->detachAllObjects();
		App->CL_Ogre->mSceneMgr->destroySceneNode(OgreModel_Node);
		App->CL_Ogre->mSceneMgr->destroyEntity(OgreModel_Ent);
		OgreModel_Ent = nullptr;
		OgreModel_Node = nullptr;
	}

	Ogre::ResourceGroupManager::getSingleton().destroyResourceGroup(TempResourceGroup);
	Ogre::ResourceGroupManager::getSingleton().createResourceGroup(TempResourceGroup);

	Ogre::ResourceGroupManager::getSingleton().addResourceLocation(App->CL_Model->Texture_FolderPath,
		"FileSystem",
		TempResourceGroup);

	try
	{
		Ogre::ResourceGroupManager::getSingleton().initialiseAllResourceGroups();
	}
	catch (...)
	{

	}

	OgreModel_Ent = App->CL_Ogre->mSceneMgr->createEntity("UserMesh", App->CL_Model->FileName, TempResourceGroup);
	OgreModel_Node = App->CL_Ogre->mSceneMgr->getRootSceneNode()->createChildSceneNode();
	OgreModel_Node->attachObject(OgreModel_Ent);

	OgreModel_Node->setVisible(false);
	OgreModel_Node->setPosition(0, 0, 0);
	OgreModel_Node->setScale(1, 1, 1);

	App->CL_Grid->Grid_SetVisible(1);
}

// *************************************************************************
// *						Create_MeshGroups Terry Bernie		  	 	   *
// *************************************************************************
void ME_Ogre3D::Create_MeshGroups()
{
	char GroupName[255];
	char GroupNum[255];

	int SubMeshCount = OgreModel_Ent->getNumSubEntities();

	int Count = 0;
	while (Count < SubMeshCount)
	{
		App->CL_Model->Create_Mesh_Group(Count);

		App->CL_Model->Group[Count]->GroupVertCount = 0;
		App->CL_Model->Group[Count]->MaterialIndex = -1;

		strcpy(App->CL_Model->Group[Count]->Text_FileName, "No_Texture");

		itoa(Count, GroupNum, 10);
		strcpy(GroupName, "Group_");
		strcat(GroupName, GroupNum);

		strcpy(App->CL_Model->Group[Count]->GroupName, GroupName);

		//---------------
		Ogre::SubMesh const* subMesh = OgreModel_Ent->getSubEntity(Count)->getSubMesh();


		//---------------
		char JustName[MAX_PATH];
		strcpy(JustName, subMesh->getMaterialName().c_str());

		char TestName;
		App->CL_FileIO->CheckPath(JustName, JustName, &TestName);
		strcpy(App->CL_Model->Group[Count]->MaterialName, &TestName);
		//---------------
		
		App->CL_Model->Group[Count]->GroupVertCount = subMesh->vertexData->vertexCount;
		App->CL_Model->Group[Count]->IndicesCount = subMesh->vertexData->vertexCount;

		//---------------
		App->CL_Model->Group[Count]->ListView_Item = App->CL_FileView->Add_Group(GroupName, Count);

		Count++;
	}

	App->CL_Model->TextureCount = SubMeshCount;
	App->CL_Model->GroupCount = SubMeshCount;

	App->CL_FileView->Set_FolderActive(App->CL_FileView->GD_GroupsFolder);
}

// *************************************************************************
// *						Extract_Mesh_Two				   		 	   *
// *************************************************************************
bool ME_Ogre3D::Extract_Mesh_Two()
{
	int FaceCount = 0;
	int FaceNum = 0;
	int FaceIndexNum = 0;
	int mFaceIndex = 0;
	int xx = 0;
	size_t vertex_count, index_count;
	Vector3* vertices;
	Vector3* normals;
	unsigned long* indices;

	Ogre::int16* BoneIndices;	// Bone Index

	int SubMeshCount = OgreModel_Ent->getNumSubEntities();

	unsigned int Vertloop = 0;
	unsigned int Faceloop = 0;
	int Count = 0;

	while (Count<SubMeshCount)
	{
		Get_SubPoseMeshInstance(OgreModel_Ent->getMesh(), vertex_count, vertices, index_count, indices, Count, BoneIndices);

		int mUVTest = NewGet_SubPoseTextureUV(OgreModel_Ent->getMesh(), Count);

		NewGet_SubPoseNormals(OgreModel_Ent->getMesh(), vertex_count, normals, Count);


		App->CL_Model->Group[Count]->vertex_Data.resize(index_count);
		App->CL_Model->Group[Count]->Normal_Data.resize(index_count);
		App->CL_Model->Group[Count]->MapCord_Data.resize(index_count);
		App->CL_Model->Group[Count]->Face_Data.resize(index_count);
		App->CL_Model->Group[Count]->FaceIndex_Data.resize(index_count);

		App->CL_Model->Group[Count]->BoneIndex_Data.resize(index_count);

		FaceIndexNum = 0;
		int Faceit = 0;
		FaceCount = 0;
		Vertloop = 0;
		xx = 0;
		while (Vertloop < vertex_count) // Process Vertices
		{
			App->CL_Model->Group[Count]->vertex_Data[Vertloop].x = vertices[Vertloop].x;
			App->CL_Model->Group[Count]->vertex_Data[Vertloop].y = vertices[Vertloop].y;
			App->CL_Model->Group[Count]->vertex_Data[Vertloop].z = vertices[Vertloop].z;

			App->CL_Model->Group[Count]->BoneIndex_Data[Vertloop].Index = BoneIndices[Vertloop]; // Bone Index 

			if (mUVTest)
			{
				App->CL_Model->Group[Count]->MapCord_Data[Vertloop].u = MeshTextureCoords[Vertloop].x;
				App->CL_Model->Group[Count]->MapCord_Data[Vertloop].v = 1 - MeshTextureCoords[Vertloop].y;
			}

			App->CL_Model->Group[Count]->Normal_Data[Vertloop].x = normals[Vertloop].x;
			App->CL_Model->Group[Count]->Normal_Data[Vertloop].y = normals[Vertloop].y;
			App->CL_Model->Group[Count]->Normal_Data[Vertloop].z = normals[Vertloop].z;

			Vertloop++;
		}

		FaceIndexNum = 0;
		Faceloop = 0;
		while (Faceloop < index_count) // Process Faces
		{
			App->CL_Model->Group[Count]->Face_Data[FaceIndexNum].a = indices[Faceloop];
			Faceloop++;
			App->CL_Model->Group[Count]->Face_Data[FaceIndexNum].b = indices[Faceloop];
			Faceloop++;
			App->CL_Model->Group[Count]->Face_Data[FaceIndexNum].c = indices[Faceloop];
			Faceloop++;

			FaceIndexNum++;

			App->CL_Model->Group[Count]->FaceIndex_Data[xx].Index = mFaceIndex;

			xx++;
			mFaceIndex++;
		}

		App->CL_Model->Group[Count]->GroupFaceCount = FaceIndexNum;
		App->CL_Model->Group[Count]->GroupVertCount = Vertloop;
		App->CL_Model->Group[Count]->IndicesCount = Vertloop;

		App->CL_Model->VerticeCount = App->CL_Model->VerticeCount + Vertloop;
		App->CL_Model->FaceCount = App->CL_Model->FaceCount + FaceIndexNum;


		GetBoneAssignment(OgreModel_Ent->getMesh(), Count, 0);

		Count++;
	}

	return 1;
}

// *************************************************************************
// *					GetBoneAssignment Terry Bernie					   *
// *************************************************************************
bool ME_Ogre3D::GetBoneAssignment(Ogre::MeshPtr mesh, int SubMesh, HWND hDlg)
{
	int Count = 0;
	Ogre::SubMesh* mSubmesh = mesh->getSubMesh(SubMesh);

	//// Bone assignments
	if (mesh->hasSkeleton())
	{
		Ogre::SubMesh::BoneAssignmentIterator BI = mSubmesh->getBoneAssignmentIterator();

		while (BI.hasMoreElements())
		{
			BI.getNext();
			Count++;
		}
	}

	App->CL_Model->Group[SubMesh]->BA_BoneIndex_Data.resize(Count);
	App->CL_Model->Group[SubMesh]->BA_BoneVertexIndex_Data.resize(Count);
	App->CL_Model->Group[SubMesh]->BA_Weight_Data.resize(Count);

	App->CL_Model->Group[SubMesh]->BoneAssignMentCount = Count;

	Count = 0;
	if (mesh->hasSkeleton())
	{
		Ogre::SubMesh::BoneAssignmentIterator BI = mSubmesh->getBoneAssignmentIterator();

		while (BI.hasMoreElements())
		{
			Ogre::VertexBoneAssignment_s bb = BI.getNext();

			App->CL_Model->Group[SubMesh]->BA_BoneIndex_Data[Count].Index = bb.boneIndex; // Bone Index 
			App->CL_Model->Group[SubMesh]->BA_BoneVertexIndex_Data[Count].Index = bb.vertexIndex;
			App->CL_Model->Group[SubMesh]->BA_Weight_Data[Count].Float1 = bb.weight;

			Count++;
		}
	}

	return 1;
}

// *************************************************************************
// *					NewGet_SubPoseNormals Terry Bernie				   *
// *************************************************************************
bool ME_Ogre3D::NewGet_SubPoseNormals(Ogre::MeshPtr mesh,size_t &vertex_count,Ogre::Vector3* &Normals,int SubMesh)
{

	bool added_shared = false;
	size_t current_offset = 0;
	size_t shared_offset = 0;
	size_t next_offset = 0;
	size_t index_offset = 0;

	const Vector3 &position = Vector3::ZERO;
	const Quaternion &orient = Quaternion::IDENTITY;
	const Vector3 &scale = Vector3::UNIT_SCALE;

	vertex_count = 0;

	Ogre::SubMesh* submesh = mesh->getSubMesh(SubMesh);

	vertex_count = submesh->vertexData->vertexCount;

	Normals = new Ogre::Vector3[vertex_count];

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
			vertex_data->vertexDeclaration->findElementBySemantic(Ogre::VES_NORMAL);

		Ogre::HardwareVertexBufferSharedPtr vbuf =
			vertex_data->vertexBufferBinding->getBuffer(posElem->getSource());

		unsigned char* vertex =
			static_cast<unsigned char*>(vbuf->lock(Ogre::HardwareBuffer::HBL_READ_ONLY));

		float* pReal;

		for (size_t j = 0; j < vertex_data->vertexCount; ++j, vertex += vbuf->getVertexSize())
		{
			posElem->baseVertexPointerToElement(vertex, &pReal);
			Ogre::Vector3 pt(pReal[0], pReal[1], pReal[2]);
			Normals[current_offset + j] = (orient * (pt * scale)) + position;
		}

		vbuf->unlock();
	}
	return 1;
}

// *************************************************************************
// *					Get_SubPoseMeshInstance Terry Bernie			   *
// *************************************************************************
void ME_Ogre3D::Get_SubPoseMeshInstance(Ogre::MeshPtr mesh,size_t &vertex_count,Ogre::Vector3* &vertices,size_t &index_count,
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

		if (OgreModel_Ent->hasSkeleton() == 1)
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

// *************************************************************************
// *					NewGet_SubPoseTextureUV Terry Bernie			   *
// *************************************************************************
bool ME_Ogre3D::NewGet_SubPoseTextureUV(Ogre::MeshPtr mesh, int SubMesh)
{
	Ogre::SubMesh* submesh = mesh->getSubMesh(SubMesh);
	int m_iCoordSet = 0;

	//// Get vertex UV coordinates
	//std::vector<Vector2> MeshTextureCoords;
	{
		Ogre::VertexData* vertex_data = submesh->useSharedVertices ? mesh->sharedVertexData : submesh->vertexData;
		// Get last set of texture coordinates
		int i = 0;
		const VertexElement* texcoordElem;
		const VertexElement* pCurrentElement = NULL;
		do
		{
			texcoordElem = pCurrentElement;
			pCurrentElement = vertex_data->vertexDeclaration->findElementBySemantic(Ogre::VES_TEXTURE_COORDINATES, i++);
		} while (pCurrentElement);
		m_iCoordSet = i - 2;
		if (!texcoordElem)
		{
			App->Say("no TextCords");
			return false;
		}
		HardwareVertexBufferSharedPtr vbuf = vertex_data->vertexBufferBinding->getBuffer(texcoordElem->getSource());
		unsigned char* vertex = static_cast<unsigned char*>(vbuf->lock(Ogre::HardwareBuffer::HBL_READ_ONLY));

		float* pReal;

		MeshTextureCoords.resize(vertex_data->vertexCount);

		for (size_t j = 0; j < vertex_data->vertexCount; ++j, vertex += vbuf->getVertexSize())
		{
			texcoordElem->baseVertexPointerToElement(vertex, &pReal);
			MeshTextureCoords[j] = Vector2(pReal[0], pReal[1]);
		}

		vbuf->unlock();
	}

	return true;
}

// *************************************************************************
// *					Get_SkeletonInstance Terry Bernie				   *
// *************************************************************************
bool ME_Ogre3D::Get_SkeletonInstance(void)
{
	
	int Loop = 0;
	if (!OgreModel_Ent)
	{
		return 0;
	}

	Ogre::SkeletonInstance *skeletonInstance = OgreModel_Ent->getSkeleton();

	if (skeletonInstance)
	{
		App->CL_Model->BoneCount = skeletonInstance->getNumBones();

		Ogre::Skeleton::BoneIterator itor = skeletonInstance->getBoneIterator();
		while (itor.hasMoreElements())
		{
			Ogre::Bone *bone = itor.getNext();

			App->CL_Model->S_Bones[Loop] = new Bone_Type;

			Ogre::Node *Parent = bone->getParent();
			if (Parent == NULL)
			{
				App->CL_Model->S_Bones[Loop]->Parent = -1;
			}
			else
			{
				Ogre::String ParentName = Parent->getName();
				Ogre::Bone *Parentbone = skeletonInstance->getBone(ParentName);
				App->CL_Model->S_Bones[Loop]->Parent = Parentbone->getHandle();
			}

			strcpy(App->CL_Model->S_Bones[Loop]->BoneName, bone->getName().c_str());

			App->CL_Model->S_Bones[Loop]->TranslationStart.X = bone->_getDerivedPosition().x;
			App->CL_Model->S_Bones[Loop]->TranslationStart.Y = bone->_getDerivedPosition().y;
			App->CL_Model->S_Bones[Loop]->TranslationStart.Z = bone->_getDerivedPosition().z;

			Loop++;
		}
	}
	return 1;
}

// *************************************************************************
// *	  					Get_BoneNames Terry Bernie					   *
// *************************************************************************
void ME_Ogre3D::Get_BoneNames(void)
{
	Ogre::SkeletonInstance *skeletonInstance = OgreModel_Ent->getSkeleton();

	int Count = 0;
	if (skeletonInstance)
	{
		char BoneName[255];
		//IsAnimated = 1;

		for (unsigned short i = 0; i<skeletonInstance->getNumBones(); ++i)
		{
			Ogre::Bone *mBones = skeletonInstance->getBone(i);
			strcpy(BoneName, mBones->getName().c_str());

			//App->CL_FileView->Add_BoneName(BoneName, i);
			Count = i;
		}

		//App->CL_FileView->Set_FolderActive(App->CL_FileView->HT_BonesFolder);
	}
	else
	{
		//App->S_Counters[0]->BoneCount = 0;
		//App->CL_FileView->Set_FolderInactive(App->CL_FileView->HT_BonesFolder);
	}
}

// *************************************************************************
// *	  				Get_Motions Terry Bernie						   *
// *************************************************************************
void ME_Ogre3D::Get_Motions(void)
{
	Ogre::SkeletonInstance *skeletonInstance = OgreModel_Ent->getSkeleton();

	int Count = 0;
	if (skeletonInstance)
	{
		int AnimationCount = skeletonInstance->getNumAnimations();
		if (AnimationCount == 0)
		{
			//IsAnimated = 0;
			App->CL_Model->MotionCount = 0;
			//App->C_FileView->Set_FolderInactive(App->C_FileView->HT_MotionsFolder);
		}
		else
		{
			char AniName[255];
			//IsAnimated = 1;

			for (unsigned short i = 0; i<skeletonInstance->getNumAnimations(); ++i)
			{
				Ogre::Animation *animation = skeletonInstance->getAnimation(i);
				strcpy(AniName, animation->getName().c_str());

				App->CL_FileView->Add_MotionFile(AniName, Count);
				Count = i;
			}

			App->CL_Model->MotionCount = Count + 1;

			/*Ogre::Animation *animation = skeletonInstance->getAnimation(0);
			strcpy(SelectedMotion,animation->getName().c_str());

			SetDlgItemText(App->CentralView_Hwnd,IDC_STMOTIONFILE,(LPCTSTR)SelectedMotion);
			strcpy(App->CL_Animations->Decode_MotionByName,SelectedMotion);

			App->C_Ogre->OgreListener->Animate_State = App->C_Ogre->OgreModel_Ent->getAnimationState(SelectedMotion);*/
			App->CL_FileView->Set_FolderActive(App->CL_FileView->GD_AnimationFolder);
		}
	}
	else
	{
		/*IsAnimated = 0;
		App->S_Counters[0]->MotionCount = 0;
		App->C_FileView->Set_FolderInactive(App->C_FileView->HT_MotionsFolder);*/
	}
}

// *************************************************************************
// *							AnimationExtract_Mesh			   	 	   *
// *************************************************************************
bool ME_Ogre3D::AnimationExtract_Mesh(bool DefaultPose)
{
	int FaceCount = 0;
	int FaceNum = 0;
	int FaceIndexNum = 0;
	size_t vertex_count, index_count;
	Vector3* vertices;
	//	Vector3* normals;
	unsigned long* indices;

	int SubMeshCount = OgreModel_Ent->getNumSubEntities();
	int loop = 0;
	int Count = 0;

	while (Count<SubMeshCount)
	{
		Get_AnimationInstance(OgreModel_Ent->getMesh(), vertex_count, vertices, index_count, indices, Count, DefaultPose);
		Count++;
	}

	return 1;
}
// *************************************************************************
// *					Get_AnimationInstance Terry Bernie				   *
// *************************************************************************
void ME_Ogre3D::Get_AnimationInstance(Ogre::MeshPtr mesh,
	size_t &vertex_count,
	Ogre::Vector3* &vertices,
	size_t &index_count,
	unsigned long* &indices,
	int SubMesh,
	bool DefaultPose)
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

	index_count = submesh->indexData->indexCount;

	// Allocate space for the vertices and indices
	vertices = new Ogre::Vector3[vertex_count];
	indices = new unsigned long[index_count];

	Ogre::VertexData* vertex_data;

	//-------------------- Get Data
	if (DefaultPose == 0)
	{
		vertex_data = submesh->useSharedVertices ? OgreModel_Ent->_getSkelAnimVertexData() : OgreModel_Ent->getSubEntity(SubMesh)->_getSkelAnimVertexData();
	}
	else
	{
		vertex_data = submesh->useSharedVertices ? mesh->sharedVertexData : submesh->vertexData;
	}

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

		for (size_t j = 0; j < vertex_data->vertexCount; ++j, vertex += vbuf->getVertexSize())
		{
			posElem->baseVertexPointerToElement(vertex, &pReal);
			Ogre::Vector3 pt(pReal[0], pReal[1], pReal[2]);
			vertices[current_offset + j] = (orient * (pt * scale)) + position;
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

	int loop = 0;
	while (loop < vertex_count)
	{
		App->CL_Model->Group[SubMesh]->vertex_Data[loop].x = vertices[loop].x;
		App->CL_Model->Group[SubMesh]->vertex_Data[loop].y = vertices[loop].y;
		App->CL_Model->Group[SubMesh]->vertex_Data[loop].z = vertices[loop].z;

		loop++;
	}

	delete vertices;
	delete indices;
}

// *************************************************************************
// *							 UpdateBones_Orge						   *
// *************************************************************************
bool ME_Ogre3D::UpdateBones_Orge(bool Reset)
{
	int Loop = 0;
	if (!OgreModel_Ent)
	{
		return 0;
	}

	Ogre::SkeletonInstance *skeletonInstance = OgreModel_Ent->getSkeleton();

	if (skeletonInstance)
	{
		if (Reset == 1)
		{
			skeletonInstance->reset(false);
		}

		Ogre::Skeleton::BoneIterator itor = skeletonInstance->getBoneIterator();
		while (itor.hasMoreElements())
		{
			Ogre::Bone *bone = itor.getNext();

			App->CL_Model->S_Bones[Loop]->TranslationStart.X = bone->_getDerivedPosition().x;
			App->CL_Model->S_Bones[Loop]->TranslationStart.Y = bone->_getDerivedPosition().y;
			App->CL_Model->S_Bones[Loop]->TranslationStart.Z = bone->_getDerivedPosition().z;

			//App->CL_Model_Data->S_Bones[Loop]->TranslationStart.X = bone->_getDerivedOrientation().

			Loop++;
		}
	}
	return 1;
}

// *************************************************************************
// *	  					Get_Textures Terry Bernie					   *
// *************************************************************************
void ME_Ogre3D::Get_Textures(void)
{
	App->CL_Load_Textures->Load_Textures_Ogre3D();

}