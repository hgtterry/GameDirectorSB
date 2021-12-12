#include "stdafx.h"
#include "GD19_App.h"
#include "EQ15_Ogre_Import.h"


EQ15_Ogre_Import::EQ15_Ogre_Import()
{
	NoTexture = 0;
	NoMaterialFileFound = 0; // Returns 1 No Material File Found;
	ExternalResourceLoaded = 0;

}


EQ15_Ogre_Import::~EQ15_Ogre_Import()
{
}

// *************************************************************************
// *					Load_OgreModel Terry Flanigan 					   *
// *************************************************************************
bool EQ15_Ogre_Import::Load_OgreModel(void)
{
	NoTexture = 0;
	NoMaterialFileFound = 0;

	AddToScene();

	Create_MeshGroups();

	Extract_Mesh_Two();

	//App->CL_Vm_Model->HasMesh = 1;

	App->CL_Vm_Model->Create_BondingBox_Model();

	/*Get_SkeletonInstance();

	Get_BoneNames();

	Get_Motions();*/

	Get_Textures();

	/*bool SkellAnimation = App->Cl_Ogre->OgreModel_Ent->hasSkeleton();
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

	Ogre::ResourceGroupManager::getSingleton().destroyResourceGroup(App->Cl19_Ogre->Level_Resource_Group);
	Ogre::ResourceGroupManager::getSingleton().createResourceGroup(App->Cl19_Ogre->Level_Resource_Group);

	Ogre::ResourceGroupManager::getSingleton().addResourceLocation(App->CL_Vm_Model->Texture_FolderPath,
		"FileSystem",
		App->Cl19_Ogre->Level_Resource_Group);

	try
	{
		Ogre::ResourceGroupManager::getSingleton().initialiseAllResourceGroups();
	}
	catch (...)
	{

	}

	App->Cl19_Ogre->OgreModel_Ent = App->Cl19_Ogre->mSceneMgr->createEntity("EquityMesh", App->CL_Vm_Model->FileName, App->Cl19_Ogre->Level_Resource_Group);
	App->Cl19_Ogre->OgreModel_Node = App->Cl19_Ogre->mSceneMgr->getRootSceneNode()->createChildSceneNode();
	App->Cl19_Ogre->OgreModel_Node->attachObject(App->Cl19_Ogre->OgreModel_Ent);

	App->Cl19_Ogre->OgreModel_Node->setVisible(false);
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

	App->CL_Vm_Model->S_Texture[0]->UsedTextureCount = App->CL_Vm_Model->GroupCount;
	App->CL_Vm_Textures->CreateTextureInfo();
}

// *************************************************************************
// *						Extract_Mesh_Two				   		 	   *
// *************************************************************************
bool EQ15_Ogre_Import::Extract_Mesh_Two()
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

	int SubMeshCount = App->Cl19_Ogre->OgreModel_Ent->getNumSubEntities();

	unsigned int Vertloop = 0;
	unsigned int Faceloop = 0;
	int Count = 0;

	while (Count<SubMeshCount)
	{
		Get_SubPoseMeshInstance(App->Cl19_Ogre->OgreModel_Ent->getMesh(), vertex_count, vertices, index_count, indices, Count, BoneIndices);

		int mUVTest = NewGet_SubPoseTextureUV(App->Cl19_Ogre->OgreModel_Ent->getMesh(), Count);
		int mNormalsTest = NewGet_SubPoseNormals(App->Cl19_Ogre->OgreModel_Ent->getMesh(), vertex_count, normals, Count);


		App->CL_Vm_Model->S_MeshGroup[Count]->vertex_Data.resize(index_count);
		App->CL_Vm_Model->S_MeshGroup[Count]->Normal_Data.resize(index_count);
		App->CL_Vm_Model->S_MeshGroup[Count]->MapCord_Data.resize(index_count);
		App->CL_Vm_Model->S_MeshGroup[Count]->Face_Data.resize(index_count);
		App->CL_Vm_Model->S_MeshGroup[Count]->FaceIndex_Data.resize(index_count);

		App->CL_Vm_Model->S_MeshGroup[Count]->BoneIndex_Data.resize(index_count);

		FaceIndexNum = 0;
		int Faceit = 0;
		FaceCount = 0;
		Vertloop = 0;
		xx = 0;
		while (Vertloop < vertex_count) // Process Vertices
		{
			App->CL_Vm_Model->S_MeshGroup[Count]->vertex_Data[Vertloop].x = vertices[Vertloop].x;
			App->CL_Vm_Model->S_MeshGroup[Count]->vertex_Data[Vertloop].y = vertices[Vertloop].y;
			App->CL_Vm_Model->S_MeshGroup[Count]->vertex_Data[Vertloop].z = vertices[Vertloop].z;

			App->CL_Vm_Model->S_MeshGroup[Count]->BoneIndex_Data[Vertloop].Index = BoneIndices[Vertloop]; // Bone Index 

			if (mUVTest)
			{
				App->CL_Vm_Model->S_MeshGroup[Count]->MapCord_Data[Vertloop].u = MeshTextureCoords[Vertloop].x;
				App->CL_Vm_Model->S_MeshGroup[Count]->MapCord_Data[Vertloop].v = 1 - MeshTextureCoords[Vertloop].y;
			}

			App->CL_Vm_Model->S_MeshGroup[Count]->Normal_Data[Vertloop].x = normals[Vertloop].x;
			App->CL_Vm_Model->S_MeshGroup[Count]->Normal_Data[Vertloop].y = normals[Vertloop].y;
			App->CL_Vm_Model->S_MeshGroup[Count]->Normal_Data[Vertloop].z = normals[Vertloop].z;

			Vertloop++;
		}

		FaceIndexNum = 0;
		Faceloop = 0;
		while (Faceloop < index_count) // Process Faces
		{
			App->CL_Vm_Model->S_MeshGroup[Count]->Face_Data[FaceIndexNum].a = indices[Faceloop];
			Faceloop++;
			App->CL_Vm_Model->S_MeshGroup[Count]->Face_Data[FaceIndexNum].b = indices[Faceloop];
			Faceloop++;
			App->CL_Vm_Model->S_MeshGroup[Count]->Face_Data[FaceIndexNum].c = indices[Faceloop];
			Faceloop++;

			FaceIndexNum++;

			App->CL_Vm_Model->S_MeshGroup[Count]->FaceIndex_Data[xx].Index = mFaceIndex;

			xx++;
			mFaceIndex++;
		}

		App->CL_Vm_Model->S_MeshGroup[Count]->GroupFaceCount = FaceIndexNum;
		App->CL_Vm_Model->S_MeshGroup[Count]->GroupVertCount = Vertloop;
		App->CL_Vm_Model->S_MeshGroup[Count]->IndicesCount = Vertloop;

		App->CL_Vm_Model->VerticeCount = App->CL_Vm_Model->VerticeCount + Vertloop;
		App->CL_Vm_Model->FaceCount = App->CL_Vm_Model->FaceCount + FaceIndexNum;


		//GetBoneAssignment(App->Cl19_Ogre->OgreModel_Ent->getMesh(), Count, 0);

		Count++;
	}

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

// *************************************************************************
// *					NewGet_SubPoseTextureUV Terry Bernie			   *
// *************************************************************************
bool EQ15_Ogre_Import::NewGet_SubPoseTextureUV(Ogre::MeshPtr mesh, int SubMesh)
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
// *					NewGet_SubPoseNormals Terry Bernie				   *
// *************************************************************************
bool EQ15_Ogre_Import::NewGet_SubPoseNormals(Ogre::MeshPtr mesh,
	size_t &vertex_count,
	Ogre::Vector3* &Normals,
	int SubMesh)
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
// *	  					Get_Textures Terry Bernie					   *
// *************************************************************************
void EQ15_Ogre_Import::Get_Textures(void)
{
	int SubMeshCount = App->Cl19_Ogre->OgreModel_Ent->getNumSubEntities();

	int mMaterialindex = 0;
	int Count = 0;
	char MatName[255];
	char TextureName[255];
	char SubMeshName[255];
	//char buf[255];

	strcpy(SubMeshName, "SubMesh_");

	while (Count<SubMeshCount)
	{
		Ogre::SubMesh const *subMesh = App->Cl19_Ogre->OgreModel_Ent->getSubEntity(Count)->getSubMesh();
		strcpy(MatName, subMesh->getMaterialName().c_str());

		/*_itoa(Count, buf, 10);
		strcpy(SubMeshName, "SubMesh_");
		strcat(SubMeshName, buf);*/

		Ogre::MaterialPtr material = Ogre::MaterialManager::getSingleton().getByName(MatName);

		if (material.isNull())
		{
			NoMaterialFileFound = 1; // Flag we dont have a texture yet
									 //App->Say_Int(NoMaterialFileFound);
		}
		else
		{
			Ogre::Technique *technique = material->getTechnique(0);
			if (technique == NULL)
			{

			}
			else
			{
				Ogre::Pass *pass;
				pass = technique->getPass(0);
				if (pass == NULL)
				{
				}
				else
				{
					int TextureUnitCount = pass->getNumTextureUnitStates();
					if (TextureUnitCount == 0)
					{
						strcpy(App->CL_Vm_Model->S_MeshGroup[Count]->Text_FileName, "No_Texture");
						//App->S_MeshGroup[Count]->IsValid = 0;
						NoTexture = 1;
					}
					else
					{
						Ogre::TextureUnitState *textureUnit = pass->getTextureUnitState(0);

						Ogre::String TxtName = textureUnit->getTextureName();

						strcpy(TextureName, TxtName.c_str());

						strcpy(App->CL_Vm_Model->S_MeshGroup[Count]->Text_FileName, TextureName);

						// New 25 august 2013 

						NoTexture = 0;

						bool result = 0;
						result = App->CL_Vm_FileIO->SearchFolders(App->CL_Vm_Model->Texture_FolderPath, TextureName);

						if (result == 1) // Texture Found in Mesh Folder
						{
							char ImageFullPath[1024];
							strcpy(ImageFullPath, App->CL_Vm_Model->Texture_FolderPath);
							strcat(ImageFullPath, TextureName);

							strcpy(App->CL_Vm_Textures->TextureFileName, TextureName);

							strcpy(App->CL_Vm_Model->S_MeshGroup[Count]->Text_PathFileName, ImageFullPath);
							strcpy(App->CL_Vm_Model->S_MeshGroup[Count]->Text_FileName, TextureName);
							
							strcpy(App->CL_Vm_Model->S_MeshGroup[mMaterialindex]->Text_PathFileName, ImageFullPath);
							strcpy(App->CL_Vm_Textures->TextureFileName, ImageFullPath);

							App->CL_Vm_Textures->TexureToWinPreviewFullPath(Count, ImageFullPath);
							

							App->CL_Vm_Model->S_MeshGroup[Count]->MaterialIndex = mMaterialindex;

							App->CL_Vm_Textures->Soil_DecodeTextures(mMaterialindex);

							App->CL_Vm_Model->S_MeshGroup[Count]->MaterialIndex = mMaterialindex;
							App->CL_Vm_Model->S_TextureInfo[Count]->ActorMaterialIndex = mMaterialindex;
							mMaterialindex++;
						}
						else
						{
							//if (ExternalResourceLoaded == 1) // Search for texture via resource file
							//{
							//	Scan_ResourcesNew(ResourcePathAndFile, Count);

							//	strcpy(App->CL_Vm_Textures->TextureFileName, App->CL_Vm_Model->S_MeshGroup[Count]->Text_PathFileName);

							//	App->CL_Vm_Model->S_MeshGroup[Count]->MaterialIndex = mMaterialindex;

							//	App->CL_Vm_Textures->Soil_DecodeTextures(mMaterialindex);
							//	mMaterialindex++;
							//}
						}
					}
				}
			}
		}

		Count++;
	}

}
