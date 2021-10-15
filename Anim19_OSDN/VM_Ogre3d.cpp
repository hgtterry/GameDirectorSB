#include "stdafx.h"
#include "GD19_App.h"
#include "VM_Ogre3d.h"


VM_Ogre3d::VM_Ogre3d()
{
	strcpy(mDecompileFolder, " ");
	strcpy(mOgreMeshFileName, " ");
	strcpy(mOgreScriptFileName, " ");
	strcpy(mOgreSkellFileName, " ");
	strcpy(mOgreSkellTagName, " ");
}


VM_Ogre3d::~VM_Ogre3d()
{
}

// *************************************************************************
// *					Export_AssimpToOgre Terry Bernie  			 	   *
// *************************************************************************
bool VM_Ogre3d::Export_AssimpToOgre(void)
{

	int test = 0;
	test = CreateDirectoryMesh();
	if (test == 0)
	{
		return 0;
	}

	strcpy(mOgreMeshFileName, App->CL_Vm_Model->JustName);
	strcpy(mOgreScriptFileName, App->CL_Vm_Model->JustName);
	strcpy(mOgreSkellFileName, App->CL_Vm_Model->JustName);
	strcpy(mOgreSkellTagName, App->CL_Vm_Model->JustName);

	strcat(mOgreMeshFileName, ".mesh");
	strcat(mOgreScriptFileName, ".material");
	strcat(mOgreSkellFileName, ".skeleton");

	Ogre::MaterialManager &mm = Ogre::MaterialManager::getSingleton();
	//matMgrSgl = OGRE_NEW MaterialManager();
	//matMgrSgl  = Ogre::MaterialManager;
	//matMgrSgl->initialise();

	//	if (mDoExportTextures == 1 && App->S_Counters[0]->TextureCount > 0)
	//	{
	DecompileTextures();
	//	}
	//	if (mDoExportMesh == 1)
	//	{
	//CreateMeshFile(mOgreMeshFileName);
	App->Cl_Vm_XMLExport->StartRenderToXML(1);
	//	}

	//	if (mDoCreateMaterialFile == 1 && App->S_Counters[0]->TextureCount > 0)
	//	{
	CreateMaterialFile(mOgreScriptFileName);
	//	}

	//delete matMgrSgl;
	return 1;
}

// *************************************************************************
// *							CreateDirectoryMesh			   		   	   *
// *************************************************************************
bool VM_Ogre3d::CreateDirectoryMesh(void)
{
	char NewDirectory[200];
	strcpy(NewDirectory, App->CL_Vm_Model->JustName);

	strcat(NewDirectory, "_Ogre");

	strcat(App->CL_Vm_FileIO->szSelectedDir, "\\");
	strcat(App->CL_Vm_FileIO->szSelectedDir, NewDirectory);

	//App->Say(App->CL_Vm_FileIO->szSelectedDir);

	if (_mkdir(App->CL_Vm_FileIO->szSelectedDir) == 0)
	{
		strcpy(mDecompileFolder, App->CL_Vm_FileIO->szSelectedDir);
		_chdir(App->CL_Vm_FileIO->szSelectedDir);
	}
	else
	{
		_chdir(App->CL_Vm_FileIO->szSelectedDir);
	}

	return 1;
}

// *************************************************************************
// *			DecomPileTextures  30/03/04   					   	   	   *
// *************************************************************************
bool VM_Ogre3d::DecompileTextures(void)
{
	int MatCount = App->CL_Vm_Model->GroupCount;

	char FileName[255];

	int Loop = 0;
	while (Loop<MatCount)
	{
		strcpy(FileName, App->CL_Vm_Model->S_MeshGroup[Loop]->Text_FileName);

		HBITMAP Data;

		Data = App->CL_Vm_Model->S_MeshGroup[Loop]->Base_Bitmap;

		if (_stricmp(FileName + strlen(FileName) - 4, ".tga") == 0)
		{
			int Len = strlen(FileName);
			FileName[Len - 4] = 0;
			strcat(FileName, ".jpg");

			App->CL_Vm_Textures->HBITMAP_TO_BmpFile(Data, FileName, "");
			App->CL_Vm_Textures->Jpg_To_Tga24(FileName);
		}
		else if (_stricmp(FileName + strlen(FileName) - 4, ".png") == 0)
		{
			int Len = strlen(FileName);
			FileName[Len - 4] = 0;
			strcat(FileName, ".jpg");

			App->CL_Vm_Textures->HBITMAP_TO_BmpFile(Data, FileName, "");
			App->CL_Vm_Textures->Jpg_To_png24(FileName);
		}
		else if (_stricmp(FileName + strlen(FileName) - 4, ".jpg") == 0)
		{
			int Len = strlen(FileName);
			FileName[Len - 4] = 0;
			strcat(FileName, ".bmp");

			App->CL_Vm_Textures->HBITMAP_TO_BmpFile(Data, FileName, "");
			App->CL_Vm_Textures->Bmp_To_Jpg(FileName);
		}
		else
		{

			App->CL_Vm_Textures->HBITMAP_TO_BmpFile(Data, FileName, "");
		}

		Loop++;
	}
	return 1;
}

// *************************************************************************
// *						CreateMeshFile  						 	   *
// *************************************************************************
bool VM_Ogre3d::CreateMeshFile(char* MatFileName)
{
	char MaterialNumber[255];
	bool foundBoneAssignment = false;
	float TempV = 0;
	/*int wh, numbones;
	int intweight[3], intbones[3];*/

	Ogre::SkeletonManager SkeletonMgr;
	Ogre::DefaultHardwareBufferManager *bufferManager = 0;

	//	Ogre::MeshManager MeshMgr;

	Ogre::MeshPtr ogreMesh = Ogre::MeshManager::getSingleton().create("export",
		Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME);

	int GroupCount = App->CL_Vm_Model->GroupCount;
	int i = 0;
	Ogre::Vector3 min, max, currpos;
	Ogre::Real maxSquaredRadius;
	bool first = true;

	for (i = 0; i < GroupCount; i++)
	{
		Ogre::SubMesh* ogreSubMesh = ogreMesh->createSubMesh();

		int matIdx = App->CL_Vm_Model->S_MeshGroup[i]->MaterialIndex;

		if (matIdx == -1)
		{
			ogreSubMesh->setMaterialName("BaseWhite");
		}
		else
		{
			char MatName[255];
			_itoa(i, MaterialNumber, 10);
			strcpy(MatName, App->CL_Vm_Model->JustName);
			strcat(MatName, "_Material_");
			strcat(MatName, MaterialNumber);

			/*char MatName[255];
			strcpy(MatName,App->S_MeshGroup[i]->MatName);*/
			ogreSubMesh->setMaterialName(MatName);
		}
		//------------------------------------------

		ogreSubMesh->vertexData = new Ogre::VertexData();
		ogreSubMesh->vertexData->vertexCount = App->CL_Vm_Model->S_MeshGroup[i]->GroupFaceCount*3;//App->CA_Milk_Import->GetNumVertices();//S_XMLStore[0]->SXMLCount;
		ogreSubMesh->vertexData->vertexStart = 0;
		Ogre::VertexBufferBinding* bind = ogreSubMesh->vertexData->vertexBufferBinding;
		Ogre::VertexDeclaration* decl = ogreSubMesh->vertexData->vertexDeclaration;
		// Always 1 texture layer, 2D coords
#define POSITION_BINDING 0
#define NORMAL_BINDING 1
#define TEXCOORD_BINDING 2
		decl->addElement(POSITION_BINDING, 0, Ogre::VET_FLOAT3, Ogre::VES_POSITION);
		decl->addElement(NORMAL_BINDING, 0, Ogre::VET_FLOAT3, Ogre::VES_NORMAL);
		decl->addElement(TEXCOORD_BINDING, 0, Ogre::VET_FLOAT2, Ogre::VES_TEXTURE_COORDINATES);
		// Create buffers
		Ogre::HardwareVertexBufferSharedPtr pbuf = Ogre::HardwareBufferManager::getSingleton().
			createVertexBuffer(decl->getVertexSize(POSITION_BINDING), ogreSubMesh->vertexData->vertexCount,
				Ogre::HardwareBuffer::HBU_DYNAMIC, false);
		Ogre::HardwareVertexBufferSharedPtr nbuf = Ogre::HardwareBufferManager::getSingleton().
			createVertexBuffer(decl->getVertexSize(NORMAL_BINDING), ogreSubMesh->vertexData->vertexCount,
				Ogre::HardwareBuffer::HBU_DYNAMIC, false);
		Ogre::HardwareVertexBufferSharedPtr tbuf = Ogre::HardwareBufferManager::getSingleton().
			createVertexBuffer(decl->getVertexSize(TEXCOORD_BINDING), ogreSubMesh->vertexData->vertexCount,
				Ogre::HardwareBuffer::HBU_DYNAMIC, false);

		bind->setBinding(POSITION_BINDING, pbuf);
		bind->setBinding(NORMAL_BINDING, nbuf);
		bind->setBinding(TEXCOORD_BINDING, tbuf);

		ogreSubMesh->useSharedVertices = false;

		float* pPos = static_cast<float*>(
			pbuf->lock(Ogre::HardwareBuffer::HBL_DISCARD));

		size_t j;

		int A = 0;
		int B = 0;
		int C = 0;

		for (j = 0; j < App->CL_Vm_Model->S_MeshGroup[i]->GroupFaceCount; j++)
		{
			A = App->CL_Vm_Model->S_MeshGroup[i]->Face_Data[j].a;
			B = App->CL_Vm_Model->S_MeshGroup[i]->Face_Data[j].b;
			C = App->CL_Vm_Model->S_MeshGroup[i]->Face_Data[j].c;

			*pPos++ = App->CL_Vm_Model->S_MeshGroup[i]->vertex_Data[A].x;
			*pPos++ = App->CL_Vm_Model->S_MeshGroup[i]->vertex_Data[A].y;
			*pPos++ = App->CL_Vm_Model->S_MeshGroup[i]->vertex_Data[A].z;

			*pPos++ = App->CL_Vm_Model->S_MeshGroup[i]->vertex_Data[B].x;
			*pPos++ = App->CL_Vm_Model->S_MeshGroup[i]->vertex_Data[B].y;
			*pPos++ = App->CL_Vm_Model->S_MeshGroup[i]->vertex_Data[B].z;

			*pPos++ = App->CL_Vm_Model->S_MeshGroup[i]->vertex_Data[C].x;
			*pPos++ = App->CL_Vm_Model->S_MeshGroup[i]->vertex_Data[C].y;
			*pPos++ = App->CL_Vm_Model->S_MeshGroup[i]->vertex_Data[C].z;

			currpos = Ogre::Vector3(App->CL_Vm_Model->S_MeshGroup[i]->vertex_Data[j].x, App->CL_Vm_Model->S_MeshGroup[i]->vertex_Data[j].y, App->CL_Vm_Model->S_MeshGroup[i]->vertex_Data[j].z);
			if (first)
			{
				min = max = currpos;
				maxSquaredRadius = currpos.squaredLength();
				first = false;
			}
			else
			{
				min.makeFloor(currpos);
				max.makeCeil(currpos);
				maxSquaredRadius = std::max(maxSquaredRadius, currpos.squaredLength());
			}
		}

		pbuf->unlock();

		float* pTex = static_cast<float*>(
			tbuf->lock(Ogre::HardwareBuffer::HBL_DISCARD));

		float* pNorm = static_cast<float*>(
			nbuf->lock(Ogre::HardwareBuffer::HBL_DISCARD));
		ogreSubMesh->indexData->indexCount = App->CL_Vm_Model->S_MeshGroup[i]->GroupFaceCount;//group->triangleIndices.size()*3;

		Ogre::HardwareIndexBufferSharedPtr ibuf = Ogre::HardwareBufferManager::getSingleton().
			createIndexBuffer(Ogre::HardwareIndexBuffer::IT_16BIT,
				ogreSubMesh->indexData->indexCount, Ogre::HardwareBuffer::HBU_STATIC_WRITE_ONLY);
		ogreSubMesh->indexData->indexBuffer = ibuf;
		unsigned short *pIdx = static_cast<unsigned short*>(
			ibuf->lock(Ogre::HardwareBuffer::HBL_DISCARD));

		int index = 0;
		int UVindex = 0;
		
		for (j = 0; j < App->CL_Vm_Model->S_MeshGroup[i]->GroupFaceCount; j++)
		{
			unsigned short nIndices[3];
			float UV_Indices[2];
			float Norm_Indices[3];

			nIndices[0] = App->CL_Vm_Model->S_MeshGroup[i]->Face_Data[j].a;
			nIndices[1] = App->CL_Vm_Model->S_MeshGroup[i]->Face_Data[j].b;
			nIndices[2] = App->CL_Vm_Model->S_MeshGroup[i]->Face_Data[j].c;

			int k, vertIdx;

			for (k = 0; k < 3; ++k)
			{
				vertIdx = nIndices[k];
				// Face index
				pIdx[j + k] = vertIdx;

				UV_Indices[0] = App->CL_Vm_Model->S_MeshGroup[i]->MapCord_Data[vertIdx].u;
				UV_Indices[1] = 1 - App->CL_Vm_Model->S_MeshGroup[i]->MapCord_Data[vertIdx].v;

				Norm_Indices[0] = App->CL_Vm_Model->S_MeshGroup[i]->Normal_Data[vertIdx].x;
				Norm_Indices[1] = App->CL_Vm_Model->S_MeshGroup[i]->Normal_Data[vertIdx].y;
				Norm_Indices[2] = App->CL_Vm_Model->S_MeshGroup[i]->Normal_Data[vertIdx].z;

				pTex[(vertIdx * 2)] = UV_Indices[0];
				pTex[(vertIdx * 2) + 1] = UV_Indices[1];
				pNorm[(vertIdx * 3)] = Norm_Indices[0];
				pNorm[(vertIdx * 3) + 1] = Norm_Indices[1];
				pNorm[(vertIdx * 3) + 2] = Norm_Indices[2];
			}

		} // Faces

		nbuf->unlock();
		ibuf->unlock();
		tbuf->unlock();

		/*Ogre::VertexDeclaration* newDecl =
			ogreSubMesh->vertexData->vertexDeclaration->getAutoOrganisedDeclaration(
				foundBoneAssignment, false, 0);
		Ogre::BufferUsageList bufferUsages;
		for (size_t u = 0; u <= newDecl->getMaxSource(); ++u)
			bufferUsages.push_back(Ogre::HardwareBuffer::HBU_STATIC_WRITE_ONLY);
		ogreSubMesh->vertexData->reorganiseBuffers(newDecl, bufferUsages);*/
	}

	ogreMesh->_setBoundingSphereRadius(Ogre::Math::Sqrt(maxSquaredRadius));
	ogreMesh->_setBounds(Ogre::AxisAlignedBox(min, max), false);

	Ogre::MeshSerializer serializer;
	serializer.exportMesh(ogreMesh.getPointer(), MatFileName);

	return 1;
}

// *************************************************************************
// *						CreateMaterialFile				   		   	   *
// *************************************************************************
void VM_Ogre3d::CreateMaterialFile(char* MatFileName)
{
	char MatName[255];
	char File[255];
	char MaterialNumber[255];

	Ogre::String OMatFileName = MatFileName;
	Ogre::String OFile;
	Ogre::String OMatName;

	int numMaterials = App->CL_Vm_Model->GroupCount;

	Ogre::MaterialManager &matMgrSgl = Ogre::MaterialManager::getSingleton();
	//matMgrSgl.initialise();

	Ogre::MaterialSerializer matSer;

	for (int i = 0; i < numMaterials; ++i)
	{
		_itoa(i, MaterialNumber, 10);
		strcpy(MatName, App->CL_Vm_Model->JustName);
		strcat(MatName, "_Material_");
		strcat(MatName, MaterialNumber);

		strcpy(File, App->CL_Vm_Model->S_MeshGroup[i]->Text_FileName);

		OMatName = MatName;
		OFile = File;

		Ogre::MaterialPtr ogremat = matMgrSgl.create(OMatName,
			Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME);

		
		if (0 < strlen(File))
		{
			ogremat->getTechnique(0)->getPass(0)->createTextureUnitState(File);
		}

		matSer.queueForExport(ogremat);
	}

	matSer.exportQueued(OMatFileName);

}

// *************************************************************************
// *					Load_OgreModel Terry Flanigan 					   *
// *************************************************************************
bool VM_Ogre3d::Load_OgreModel(void)
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
void VM_Ogre3d::AddToScene(void)
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
void VM_Ogre3d::Create_MeshGroups()
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
bool VM_Ogre3d::Extract_Mesh_Two()
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
void VM_Ogre3d::Get_SubPoseMeshInstance(Ogre::MeshPtr mesh,
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
