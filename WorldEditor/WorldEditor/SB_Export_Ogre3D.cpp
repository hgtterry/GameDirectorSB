/*
Copyright (c) 2023 World Editor -- HGT Software W.T.Flanigan H.C.Flanigan

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

#include "StdAfx.h"
#include "AB_App.h"
#include "SB_Export_Ogre3D.h"

SB_Export_Ogre3D::SB_Export_Ogre3D(void)
{
	mDirectory_Name[0] = 0;
	mSelected_Directory[0] = 0;

	mWorld_File_Path[0] = 0;
	mWorld_File_PathAndFile[0] = 0;

	mExport_Just_Name[0] = 0;

	mExport_Path[0] = 0;
	mExport_PathAndFile_Material[0] = 0;
	mExport_PathAndFile_Mesh[0] = 0;

	strcpy(mWorld_Mesh_JustName, "World");

	x, y, z = 0;
	nx, ny, nz = 0;
	u, v = 0;

	Export_Manual = NULL;
	World_Manual = NULL;

	World_Node = NULL;
	World_Ent = NULL;
	NameIndex = 0;
}

SB_Export_Ogre3D::~SB_Export_Ogre3D(void)
{
	
}

// *************************************************************************
// *		Set_Export_Paths:- Terry and Hazel Flanigan 2023		 	   *
// *************************************************************************
void SB_Export_Ogre3D::Set_Export_Paths(void)
{
	char ExportFolder[MAX_PATH];

	strcpy(mSelected_Directory, App->CLSB_Exporter->mFolder_Path);
	strcpy(mDirectory_Name, App->CLSB_Exporter->mDirectory_Name);
	strcpy(mExport_Just_Name, App->CLSB_Exporter->mJustName);

	strcpy(mExport_Path, mSelected_Directory);
	strcat(mExport_Path, "\\");
	strcat(mExport_Path, mDirectory_Name);
	strcat(mExport_Path, "\\");

	strcpy(mExport_PathAndFile_Mesh, mExport_Path);
	strcat(mExport_PathAndFile_Mesh, mExport_Just_Name);
	strcat(mExport_PathAndFile_Mesh, ".mesh");
	
	strcpy(mExport_PathAndFile_Material, mExport_Path);
	strcat(mExport_PathAndFile_Material, mExport_Just_Name);
	strcat(mExport_PathAndFile_Material, ".material");

	x, y, z = 0;
	nx, ny, nz = 0;
	u, v = 0;

}

// *************************************************************************
// *	  		Export_To_Ogre3D:- Terry and Hazel Flanigan 2022		   *
// *************************************************************************
void SB_Export_Ogre3D::Export_To_Ogre3D(bool Create)
{
	Set_Export_Paths();

	CreateDirectory(mExport_Path, NULL);

	if (Create == 1)
	{
		Export_Manual = App->CLSB_Ogre->mSceneMgr->createManualObject("OgreManual2");
		Export_Manual->setRenderQueueGroup(2);
	}

	int A = 0;
	int B = 0;
	int C = 0;

	Export_Manual->setDynamic(false);
	Export_Manual->setCastShadows(false);

	Export_Manual->estimateVertexCount(App->CLSB_Model->VerticeCount);
	Export_Manual->estimateIndexCount(App->CLSB_Model->FaceCount);

	char MaterialNumber[255];
	char MatName[255];

	int GroupCountTotal = App->CLSB_Model->Get_Groupt_Count();
	int Count = 0;
	int FaceCount = 0;
	int FaceIndex = 0;

	while (Count < GroupCountTotal)
	{
		_itoa(Count, MaterialNumber, 10);
		strcpy(MatName, mExport_Just_Name);
		strcat(MatName, "_Material_");
		strcat(MatName, MaterialNumber);

		Export_Manual->begin(MatName, Ogre::RenderOperation::OT_TRIANGLE_LIST);

		FaceCount = 0;
		FaceIndex = 0;

		while (FaceCount < App->CLSB_Model->Group[Count]->GroupFaceCount)
		{
			A = App->CLSB_Model->Group[Count]->Face_Data[FaceCount].a;
			B = App->CLSB_Model->Group[Count]->Face_Data[FaceCount].b;
			C = App->CLSB_Model->Group[Count]->Face_Data[FaceCount].c;

			// --------------------------------------------------

			Get_Data(Count, A);

			Export_Manual->position(Ogre::Vector3(x, y, z));
			Export_Manual->textureCoord(Ogre::Vector2(u, 1 - v));
			Export_Manual->normal(Ogre::Vector3(nx, ny, nz));
			Export_Manual->index(FaceIndex);
			FaceIndex++;

			Get_Data(Count, B);

			Export_Manual->position(Ogre::Vector3(x, y, z));
			Export_Manual->textureCoord(Ogre::Vector2(u, 1 - v));
			Export_Manual->normal(Ogre::Vector3(nx, ny, nz));
			Export_Manual->index(FaceIndex);
			FaceIndex++;

			Get_Data(Count, C);

			Export_Manual->position(Ogre::Vector3(x, y, z));
			Export_Manual->textureCoord(Ogre::Vector2(u, 1 - v));
			Export_Manual->normal(Ogre::Vector3(nx, ny, nz));
			Export_Manual->index(FaceIndex);

			FaceIndex++;
			FaceCount++;
		}

		Export_Manual->end();

		Count++;
	}


	if (Export_Manual->getNumSections() == 0)
	{
		App->Say("Can not create Ogre Sections");
		return;
	}

	Ogre::MeshPtr mesh = Export_Manual->convertToMesh("TestMesh");

	mesh->setAutoBuildEdgeLists(true);
	mesh->buildEdgeList();

	App->CLSB_Ogre->mSceneMgr->destroyManualObject(Export_Manual);

	Ogre::MeshSerializer* ms = new Ogre::MeshSerializer();
	ms->exportMesh(mesh.get(), mExport_PathAndFile_Mesh);
	delete(ms);

	DecompileTextures_TXL(mExport_Path);

	CreateMaterialFile(mExport_PathAndFile_Material);

}

// *************************************************************************
// *		Set_World_Paths:- Terry and Hazel Flanigan 2023			 	   *
// *************************************************************************
void SB_Export_Ogre3D::Set_World_Paths(void)
{
	char Num[100];
	itoa(NameIndex, Num, 10);

	strcpy(mWorld_Mesh_JustName, "World");
	strcat(mWorld_Mesh_JustName, Num);

	strcpy(mWorld_File_PathAndFile, App->WorldEditor_Directory);
	strcat(mWorld_File_PathAndFile, "\\");
	strcat(mWorld_File_PathAndFile, "Data");
	strcat(mWorld_File_PathAndFile, "\\");
	strcat(mWorld_File_PathAndFile, "World_Test");

	strcpy(mWorld_File_Path, mWorld_File_PathAndFile);

	strcat(mWorld_File_PathAndFile, "\\");
	strcat(mWorld_File_PathAndFile, mWorld_Mesh_JustName);
	strcat(mWorld_File_PathAndFile, ".mesh");

	strcpy(mExport_Just_Name, mWorld_Mesh_JustName);

	NameIndex++;

	x, y, z = 0;
	nx, ny, nz = 0;
	u, v = 0;
}

// *************************************************************************
// *	  		Convert_ToOgre3D:- Terry and Hazel Flanigan 2022		   *
// *************************************************************************
void SB_Export_Ogre3D::Convert_ToOgre3D(bool Create)
{
	Set_World_Paths();

	if (Create == 1)
	{
		World_Manual = App->CLSB_Ogre->mSceneMgr->createManualObject("OgreManual2");
		World_Manual->setRenderQueueGroup(2);
	}

	int A = 0;
	int B = 0;
	int C = 0;

	World_Manual->setDynamic(false);
	World_Manual->setCastShadows(false);

	World_Manual->estimateVertexCount(App->CLSB_Model->VerticeCount);
	World_Manual->estimateIndexCount(App->CLSB_Model->FaceCount);

	char MaterialNumber[255];
	char MatName[255];

	int GroupCountTotal = App->CLSB_Model->Get_Groupt_Count();
	int Count = 0;
	int FaceCount = 0;
	int FaceIndex = 0;

	while (Count < GroupCountTotal)
	{
		_itoa(Count, MaterialNumber, 10);
		strcpy(MatName, mWorld_Mesh_JustName);
		strcat(MatName, "_Material_");
		strcat(MatName, MaterialNumber);

		World_Manual->begin(MatName, Ogre::RenderOperation::OT_TRIANGLE_LIST);

		FaceCount = 0;
		FaceIndex = 0;

		while (FaceCount < App->CLSB_Model->Group[Count]->GroupFaceCount)
		{
			A = App->CLSB_Model->Group[Count]->Face_Data[FaceCount].a;
			B = App->CLSB_Model->Group[Count]->Face_Data[FaceCount].b;
			C = App->CLSB_Model->Group[Count]->Face_Data[FaceCount].c;

			// --------------------------------------------------

			Get_Data(Count, A);

			World_Manual->position(Ogre::Vector3(x, y, z));
			World_Manual->textureCoord(Ogre::Vector2(u, 1 - v));
			World_Manual->normal(Ogre::Vector3(nx, ny, nz));
			World_Manual->index(FaceIndex);
			FaceIndex++;

			Get_Data(Count, B);

			World_Manual->position(Ogre::Vector3(x, y, z));
			World_Manual->textureCoord(Ogre::Vector2(u, 1 - v));
			World_Manual->normal(Ogre::Vector3(nx, ny, nz));
			World_Manual->index(FaceIndex);
			FaceIndex++;

			Get_Data(Count, C);

			World_Manual->position(Ogre::Vector3(x, y, z));
			World_Manual->textureCoord(Ogre::Vector2(u,1 - v));
			World_Manual->normal(Ogre::Vector3(nx, ny, nz));
			World_Manual->index(FaceIndex);

			FaceIndex++;
			FaceCount++;
		}

		World_Manual->end();

		Count++;
	}

	
	if (World_Manual->getNumSections() == 0)
	{
		App->Say("Can not create Ogre Sections");
	}

	Ogre::MeshPtr mesh = World_Manual->convertToMesh("TestMesh");

	mesh->setAutoBuildEdgeLists(true);
	mesh->buildEdgeList();

	App->CLSB_Ogre->mSceneMgr->destroyManualObject(World_Manual);

	Ogre::MeshSerializer* ms = new Ogre::MeshSerializer();
	ms->exportMesh(mesh.get(), mWorld_File_PathAndFile);
	delete(ms);

	char OutputFolder[MAX_PATH];
	strcpy(OutputFolder, mWorld_File_Path);
	strcat(OutputFolder, "\\");

	DecompileTextures_TXL(OutputFolder);

	char Material_PathAndFile[MAX_PATH];
	strcpy(Material_PathAndFile, mWorld_File_Path);
	strcat(Material_PathAndFile, "\\");
	strcat(Material_PathAndFile, mWorld_Mesh_JustName);
	strcat(Material_PathAndFile, ".material");

	CreateMaterialFile(Material_PathAndFile);
	
	char Name[MAX_PATH];
	strcpy(Name, mWorld_Mesh_JustName);
	strcat(Name, ".mesh");
	
	if (World_Ent)
	{
		World_Node->detachAllObjects();
		App->CLSB_Ogre->mSceneMgr->destroySceneNode(World_Node);
		App->CLSB_Ogre->mSceneMgr->destroyEntity(World_Ent);

		World_Node = NULL;
		World_Ent = NULL;

		//Ogre::ResourcePtr ptr = Ogre::MeshManager::getSingleton().getByName(Name,App->CLSB_Ogre->World_Resource_Group);
		//ptr->unload();

		//Ogre::MeshManager::getSingleton().remove(Name);

		Ogre::ResourceGroupManager::getSingleton().destroyResourceGroup(App->CLSB_Ogre->World_Resource_Group);
		Ogre::ResourceGroupManager::getSingleton().createResourceGroup(App->CLSB_Ogre->World_Resource_Group);

		Ogre::ResourceGroupManager::getSingleton().addResourceLocation(mWorld_File_Path, "FileSystem", App->CLSB_Ogre->World_Resource_Group);
		Ogre::ResourceGroupManager::getSingleton().clearResourceGroup(App->CLSB_Ogre->World_Resource_Group);
		Ogre::ResourceGroupManager::getSingleton().initialiseResourceGroup(App->CLSB_Ogre->World_Resource_Group);

		Debug
	}
	else
	{
		Ogre::ResourceGroupManager::getSingleton().addResourceLocation(mWorld_File_Path, "FileSystem", App->CLSB_Ogre->World_Resource_Group);
	}

	World_Ent = App->CLSB_Ogre->mSceneMgr->createEntity(Name);
	World_Node = App->CLSB_Ogre->mSceneMgr->getRootSceneNode()->createChildSceneNode();
	World_Node->attachObject(World_Ent);

	World_Node->setPosition(0, 0, 0);
	World_Node->setVisible(true);
	World_Node->setScale(1, 1, 1);
}

// *************************************************************************
// *			Get_Data:- Terry and Hazel Flanigan 2023  			   	   *
// *************************************************************************
void SB_Export_Ogre3D::Get_Data(int Index, int FaceIndex)
{
	x = App->CLSB_Model->Group[Index]->vertex_Data[FaceIndex].x;
	y = App->CLSB_Model->Group[Index]->vertex_Data[FaceIndex].y;
	z = App->CLSB_Model->Group[Index]->vertex_Data[FaceIndex].z;

	u = App->CLSB_Model->Group[Index]->MapCord_Data[FaceIndex].u;
	v = App->CLSB_Model->Group[Index]->MapCord_Data[FaceIndex].v;

	nx = App->CLSB_Model->Group[Index]->Normal_Data[FaceIndex].x;
	ny = App->CLSB_Model->Group[Index]->Normal_Data[FaceIndex].y;
	nz = App->CLSB_Model->Group[Index]->Normal_Data[FaceIndex].z;
}

// *************************************************************************
// *		DecompileTextures_TXL:- Terry and Hazel Flanigan 2023  	   	   *
// *************************************************************************
bool SB_Export_Ogre3D::DecompileTextures_TXL(char* PathAndFile)
{

	char buf[MAX_PATH];

	int GroupCount = 0;
	int GroupCountTotal = App->CLSB_Model->Get_Groupt_Count();

	while (GroupCount < GroupCountTotal)
	{
		strcpy(buf, App->CLSB_Model->Group[GroupCount]->Text_FileName);
		int Len = strlen(buf);
		buf[Len - 4] = 0;

		App->CLSB_Textures->Extract_TXL_Texture(buf, PathAndFile);

		GroupCount++;
	}


	return 1;
}

// *************************************************************************
// *		CreateMaterialFile:- Terry and Hazel Flanigan 2023		   	   *
// *************************************************************************
void SB_Export_Ogre3D::CreateMaterialFile(char* MatFileName)
{
	char MatName[255];
	char File[255];
	char MaterialNumber[255];

	Ogre::String OMatFileName = MatFileName;
	Ogre::String OFile;
	Ogre::String OMatName;

	int numMaterials = App->CLSB_Model->GroupCount;

	Ogre::MaterialManager& matMgrSgl = Ogre::MaterialManager::getSingleton();

	Ogre::MaterialSerializer matSer;

	for (int i = 0; i < numMaterials; ++i)
	{
		_itoa(i, MaterialNumber, 10);
		strcpy(MatName, mExport_Just_Name);
		strcat(MatName, "_Material_");
		strcat(MatName, MaterialNumber);

		strcpy(File, App->CLSB_Model->Group[i]->Text_FileName);

		OMatName = MatName;
		OFile = File;

		Ogre::MaterialPtr ogremat = matMgrSgl.create(OMatName,
			Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME);


		if (0 < strlen(File))
		{
			ogremat->getTechnique(0)->getPass(0)->createTextureUnitState(File);

			if (_stricmp(File + strlen(File) - 4, ".TGA") == 0)
			{
				ogremat->getTechnique(0)->getPass(0)->setAlphaRejectSettings(Ogre::CMPF_GREATER, 128);
			}
		}

		matSer.queueForExport(ogremat);
	}

	matSer.exportQueued(OMatFileName);
}
