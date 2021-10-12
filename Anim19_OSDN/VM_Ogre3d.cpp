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
	CreateMeshFile(mOgreMeshFileName);
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
	int MatCount = App->CL_Vm_Model->TextureCount;

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
		ogreSubMesh->vertexData->vertexCount = App->CL_Vm_Model->S_MeshGroup[i]->GroupVertCount;//App->CA_Milk_Import->GetNumVertices();//S_XMLStore[0]->SXMLCount;
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
		for (j = 0; j < ogreSubMesh->vertexData->vertexCount; ++j)
		{
			*pPos++ = App->CL_Vm_Model->S_MeshGroup[i]->vertex_Data[j].x;
			*pPos++ = App->CL_Vm_Model->S_MeshGroup[i]->vertex_Data[j].y;
			*pPos++ = App->CL_Vm_Model->S_MeshGroup[i]->vertex_Data[j].z;

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
		ogreSubMesh->indexData->indexCount = App->CL_Vm_Model->S_MeshGroup[i]->GroupVertCount;//group->triangleIndices.size()*3;

		Ogre::HardwareIndexBufferSharedPtr ibuf = Ogre::HardwareBufferManager::getSingleton().
			createIndexBuffer(Ogre::HardwareIndexBuffer::IT_16BIT,
				ogreSubMesh->indexData->indexCount, Ogre::HardwareBuffer::HBU_STATIC_WRITE_ONLY);
		ogreSubMesh->indexData->indexBuffer = ibuf;
		unsigned short *pIdx = static_cast<unsigned short*>(
			ibuf->lock(Ogre::HardwareBuffer::HBL_DISCARD));

		for (j = 0; j < ogreSubMesh->indexData->indexCount; j += 3)
		{
			unsigned short nIndices[3];
			float UV_Indices[2];
			float Norm_Indices[3];

			nIndices[0] = j;
			nIndices[1] = j + 1;
			nIndices[2] = j + 2;

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

		Ogre::VertexDeclaration* newDecl =
			ogreSubMesh->vertexData->vertexDeclaration->getAutoOrganisedDeclaration(
				foundBoneAssignment, false, 0);
		Ogre::BufferUsageList bufferUsages;
		for (size_t u = 0; u <= newDecl->getMaxSource(); ++u)
			bufferUsages.push_back(Ogre::HardwareBuffer::HBU_STATIC_WRITE_ONLY);
		ogreSubMesh->vertexData->reorganiseBuffers(newDecl, bufferUsages);
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

	int numMaterials = App->CL_Vm_Model->TextureCount;

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
