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
#include "direct.h"

SB_Export_Ogre3D::SB_Export_Ogre3D(void)
{
	mDecompileFolder[0] = 0;
	mOgreMeshFileName[0] = 0;
	mOgreScriptFileName[0] = 0;
	mOgreSkellFileName[0] = 0;
	mOgreSkellTagName[0] = 0;

	XmlMeshFileName[0] = 0;
	XmlScriptFileName[0] = 0;
	XmlSkellFileName[0] = 0;
	XmlSkellTagName[0] = 0;

	NewDirectory[0] = 0;
	Directory_Name[0] = 0;
	mCurrentFolder[0] = 0;

	nx = 0;
	ny = 0;
	nz = 0;

	u = 0;
	v = 0;

	WritePolyFile = nullptr;

	Add_Sub_Folder = 1;
}

SB_Export_Ogre3D::~SB_Export_Ogre3D(void)
{
}

// *************************************************************************
// *					Export_AssimpToOgre Terry Bernie  			 	   *
// *************************************************************************
bool SB_Export_Ogre3D::Export_AssimpToOgre(void)
{
	mDecompileFolder[0] = 0;
	mOgreMeshFileName[0] = 0;
	mOgreScriptFileName[0] = 0;
	mOgreSkellFileName[0] = 0;
	mOgreSkellTagName[0] = 0;
	Directory_Name[0] = 0;

	strcpy(Directory_Name, App->CLSB_Model->JustName);
	strcat(Directory_Name, "_Ogre");

	strcpy(App->CLSB_FileIO->BrowserMessage, "Select Folder To Place Ogre Files a sub folder will be created");
	int Test = App->CLSB_FileIO->StartBrowser(App->CLSB_Model->Model_FolderPath);
	if (Test == 0) { return 1; }

	App->CLSB_Exporter->Start_Export_Dlg();
	if (App->CLSB_Exporter->Is_Canceled == 1) { return 1; }

	//App->CL_PB->StartNewProgressBar();
	//App->CL_PB->Set_Progress("Building Scene/Game", 15);

	//App->CL_PB->Nudge("CreateDirectoryMesh");

	Test = CreateDirectoryMesh();
	if (Test == 0) { return 1; }

	strcpy(mOgreMeshFileName, App->CLSB_Model->JustName);
	strcpy(mOgreScriptFileName, App->CLSB_Model->JustName);
	strcpy(mOgreSkellFileName, App->CLSB_Model->JustName);
	strcpy(mOgreSkellTagName, App->CLSB_Model->JustName);

	strcat(mOgreMeshFileName, ".mesh");
	strcat(mOgreScriptFileName, ".material");
	strcat(mOgreSkellFileName, ".skeleton");

	//App->CL_PB->Nudge("DecompileTextures");

	DecompileTextures();

	//App->CL_PB->Nudge("CreateMaterialFile");
	CreateMaterialFile(mOgreScriptFileName);

	//App->CL_PB->Nudge("Write_XML_File");
	Write_XML_File();

	//// ---------------------------------------------------- 
	//char SourceFile[1024];
	//char OldFile[1024];

	//App->CL_PB->Nudge("Transfer");
	//strcpy(OldFile, XmlMeshFileName);

	//strcpy(SourceFile, mCurrentFolder);
	//strcat(SourceFile, "\\");
	//strcat(SourceFile, XmlMeshFileName);

	//strcpy(Source_Path_FileName, SourceFile);

	//int Len = strlen(XmlMeshFileName);
	//XmlMeshFileName[Len - 4] = 0;

	//char DestFile[1024];
	//strcpy(DestFile, mCurrentFolder);
	//strcat(DestFile, "\\");
	//strcat(DestFile, XmlMeshFileName);

	//strcpy(Dest_Path_FileName, DestFile);

	//App->CL_PB->Nudge("Convert_To_Mesh");
	//Convert_To_Mesh();

	//App->CL_PB->Nudge("Remove Temp Files");
	//remove(OldFile);

	//App->CL_PB->Nudge("Convert_To_Mesh");
	//App->CL_PB->Nudge("Convert_To_Mesh");
	//App->CL_PB->Nudge("Convert_To_Mesh");
	//App->CL_PB->Nudge("Convert_To_Mesh");

	//App->CL_PB->Stop_Progress_Bar("Export to Ogre Format Completed");

	return 1;
}

// *************************************************************************
// *							CreateDirectoryMesh			   		   	   *
// *************************************************************************
bool SB_Export_Ogre3D::CreateDirectoryMesh(void)
{
	/*if (App->CL_Export_Ogre3D->Export_As_RF)
	{
		strcpy(App->CL_Equity_SB->Pref_Ogre_Path, App->CL_FileIO->szSelectedDir);
		App->CL_Equity_SB->Write_Project_File()
	}*/

	if (Add_Sub_Folder == 0)
	{
		strcpy(NewDirectory, "");
		_chdir(App->CLSB_FileIO->szSelectedDir);
	}
	else
	{
		strcpy(NewDirectory, "\\");
		strcat(NewDirectory, Directory_Name);

		strcat(App->CLSB_FileIO->szSelectedDir, NewDirectory);

		if (_mkdir(App->CLSB_FileIO->szSelectedDir) == 0)
		{
			strcpy(mDecompileFolder, App->CLSB_FileIO->szSelectedDir);
			_chdir(App->CLSB_FileIO->szSelectedDir);
		}
		else
		{
			App->CLSB_Dialogs->YesNo("File Exsits", "Do you want to update File");

			bool Doit = App->CLSB_Dialogs->Canceled;
			if (Doit == 0)
			{
				strcpy(mDecompileFolder, App->CLSB_FileIO->szSelectedDir);
				_chdir(App->CLSB_FileIO->szSelectedDir);
			}
			else
			{
				return 0;
			}
		}

	}

	_getcwd(mCurrentFolder, MAX_PATH);

	return 1;
}

// *************************************************************************
// *			DecompileTextures  30/03/04   					   	   	   *
// *************************************************************************
bool SB_Export_Ogre3D::DecompileTextures(void)
{
	int MatCount = App->CLSB_Model->GroupCount;

	char FileName[255];

	int Loop = 0;
	while (Loop < MatCount)
	{
		strcpy(FileName, App->CLSB_Model->Group[Loop]->Text_FileName);

		HBITMAP Data;

		Data = App->CLSB_Model->Group[Loop]->Base_Bitmap;

		if (_stricmp(FileName + strlen(FileName) - 4, ".tga") == 0)
		{

			char mDirectory[MAX_PATH];
			_getcwd(mDirectory, MAX_PATH);
			strcat(mDirectory, "\\");
			strcat(mDirectory, FileName);

			App->CLSB_Textures->WriteTGA(mDirectory, App->CLSB_Model->Group[Loop]->RF_Bitmap);
		}
		else if (_stricmp(FileName + strlen(FileName) - 4, ".png") == 0)
		{
			int Len = strlen(FileName);
			FileName[Len - 4] = 0;
			strcat(FileName, ".jpg");

			App->CLSB_Textures->HBITMAP_TO_BmpFile(Data, FileName, "");
			App->CLSB_Textures->Jpg_To_png24(FileName);
		}
		else if (_stricmp(FileName + strlen(FileName) - 4, ".jpg") == 0)
		{
			int Len = strlen(FileName);
			FileName[Len - 4] = 0;
			strcat(FileName, ".bmp");

			App->CLSB_Textures->HBITMAP_TO_BmpFile(Data, FileName, "");
			App->CLSB_Textures->Bmp_To_Jpg(FileName);
		}
		else
		{

			App->CLSB_Textures->HBITMAP_TO_BmpFile(Data, FileName, "");
		}

		Loop++;
	}
	return 1;
}

// *************************************************************************
// *						CreateMaterialFile				   		   	   *
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
	//matMgrSgl.initialise();

	Ogre::MaterialSerializer matSer;

	for (int i = 0; i < numMaterials; ++i)
	{
		_itoa(i, MaterialNumber, 10);
		strcpy(MatName, App->CLSB_Model->JustName);
		strcat(MatName, "_Material_");
		strcat(MatName, MaterialNumber);

		strcpy(File, App->CLSB_Model->Group[i]->Text_FileName);

		OMatName = MatName;
		OFile = File;

		Ogre::MaterialPtr ogremat = matMgrSgl.create(OMatName,
			Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME);


		if (0 < strlen(File))
		{
			/*if (_stricmp(File + strlen(File) - 4, ".TGA") == 0)
			{
				App->Say(File);
			}*/

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

// *************************************************************************
// *							Write_XML_File				   		   	   *
// *************************************************************************
bool SB_Export_Ogre3D::Write_XML_File()
{
	S_XMLStore[0] = new XMLStore_Type;
	S_XMLStore[0]->SortedPolyCount = 0;

	char XmlFileName[256];
	char XFIle[256];

	strcpy(XmlFileName, App->CLSB_Model->JustName);

	strcpy(XmlMeshFileName, XmlFileName);
	strcpy(XmlScriptFileName, XmlFileName);
	strcpy(XmlSkellFileName, XmlFileName);
	strcpy(XmlSkellTagName, XmlFileName);

	strcpy(XFIle, XmlFileName);

	strcat(XmlScriptFileName, "_");
	strcat(XmlSkellTagName, "_");

	strcpy(XFIle, XmlMeshFileName);

	strcat(XmlMeshFileName, ".mesh.xml");
	strcat(XmlScriptFileName, ".material");
	strcat(XmlSkellFileName, ".skeleton.xml");
	strcat(XmlSkellTagName, ".skeleton");

	WritePolyFile = nullptr;

	WritePolyFile = fopen(XmlMeshFileName, "wt");
	if (!WritePolyFile)
	{
		return 0;
	}

	fprintf(WritePolyFile, "%s\n", "<mesh>");
	fprintf(WritePolyFile, "%s\n", "    <submeshes>");

	int Count = 0;
	while (Count < App->CLSB_Model->GroupCount)
	{
		RenderToXML(Count);
		WriteNewXML(Count);
		Count++;
	}


	fprintf(WritePolyFile, "%s\n", "    </submeshes>");

	/*if (DoSkell == 1)
	{
		fprintf(WritePolyFile, "%s%s%s\n", "    <skeletonlink name=\"", XmlSkellTagName, "\" />");
	}*/

	fprintf(WritePolyFile, "%s\n", "</mesh>");

	fclose(WritePolyFile);

	if (S_XMLStore[0])
	{
		delete S_XMLStore[0];
		S_XMLStore[0] = NULL;

	}

	return 1;
}

// *************************************************************************
// *							RenderToXML					   		   	   *
// *************************************************************************
bool SB_Export_Ogre3D::RenderToXML(int GroupIndex)
{
	int FaceCount = 0;
	int XMLCount = 0;
	int Face = 0;

	int A = 0;
	int B = 0;
	int C = 0;

	while (FaceCount < App->CLSB_Model->Group[GroupIndex]->GroupFaceCount)
	{
		A = App->CLSB_Model->Group[GroupIndex]->Face_Data[FaceCount].a;
		B = App->CLSB_Model->Group[GroupIndex]->Face_Data[FaceCount].b;
		C = App->CLSB_Model->Group[GroupIndex]->Face_Data[FaceCount].c;

		// first vector in face and vertic + normal and uv 
		S_XMLStore[0]->XMLvertex[XMLCount].x = App->CLSB_Model->Group[GroupIndex]->vertex_Data[A].x;
		S_XMLStore[0]->XMLvertex[XMLCount].y = App->CLSB_Model->Group[GroupIndex]->vertex_Data[A].y;
		S_XMLStore[0]->XMLvertex[XMLCount].z = App->CLSB_Model->Group[GroupIndex]->vertex_Data[A].z;

		S_XMLStore[0]->mapcoord[XMLCount].u = App->CLSB_Model->Group[GroupIndex]->MapCord_Data[A].u;
		S_XMLStore[0]->mapcoord[XMLCount].v = App->CLSB_Model->Group[GroupIndex]->MapCord_Data[A].v;

		S_XMLStore[0]->XMLnormal[XMLCount].x = App->CLSB_Model->Group[GroupIndex]->Normal_Data[A].x;
		S_XMLStore[0]->XMLnormal[XMLCount].y = App->CLSB_Model->Group[GroupIndex]->Normal_Data[A].y;
		S_XMLStore[0]->XMLnormal[XMLCount].z = App->CLSB_Model->Group[GroupIndex]->Normal_Data[A].z;

		S_XMLStore[0]->BoneIndex[XMLCount] = 0;// SN[cube.polygon[Count].a].BoneIndex;
		S_XMLStore[0]->XMLpolygon[Face].a = XMLCount;
		XMLCount++;

		// second vector in face and vertic + normal and uv 
		S_XMLStore[0]->XMLvertex[XMLCount].x = App->CLSB_Model->Group[GroupIndex]->vertex_Data[B].x;
		S_XMLStore[0]->XMLvertex[XMLCount].y = App->CLSB_Model->Group[GroupIndex]->vertex_Data[B].y;
		S_XMLStore[0]->XMLvertex[XMLCount].z = App->CLSB_Model->Group[GroupIndex]->vertex_Data[B].z;

		S_XMLStore[0]->mapcoord[XMLCount].u = App->CLSB_Model->Group[GroupIndex]->MapCord_Data[B].u;
		S_XMLStore[0]->mapcoord[XMLCount].v = App->CLSB_Model->Group[GroupIndex]->MapCord_Data[B].v;

		S_XMLStore[0]->XMLnormal[XMLCount].x = App->CLSB_Model->Group[GroupIndex]->Normal_Data[B].x;
		S_XMLStore[0]->XMLnormal[XMLCount].y = App->CLSB_Model->Group[GroupIndex]->Normal_Data[B].y;
		S_XMLStore[0]->XMLnormal[XMLCount].z = App->CLSB_Model->Group[GroupIndex]->Normal_Data[B].z;

		S_XMLStore[0]->BoneIndex[XMLCount] = 0;// SN[cube.polygon[Count].a].BoneIndex;
		S_XMLStore[0]->XMLpolygon[Face].b = XMLCount;
		XMLCount++;

		// third vector in face and vertic + normal and uv 
		S_XMLStore[0]->XMLvertex[XMLCount].x = App->CLSB_Model->Group[GroupIndex]->vertex_Data[C].x;
		S_XMLStore[0]->XMLvertex[XMLCount].y = App->CLSB_Model->Group[GroupIndex]->vertex_Data[C].y;
		S_XMLStore[0]->XMLvertex[XMLCount].z = App->CLSB_Model->Group[GroupIndex]->vertex_Data[C].z;

		S_XMLStore[0]->mapcoord[XMLCount].u = App->CLSB_Model->Group[GroupIndex]->MapCord_Data[C].u;
		S_XMLStore[0]->mapcoord[XMLCount].v = App->CLSB_Model->Group[GroupIndex]->MapCord_Data[C].v;

		S_XMLStore[0]->XMLnormal[XMLCount].x = App->CLSB_Model->Group[GroupIndex]->Normal_Data[C].x;
		S_XMLStore[0]->XMLnormal[XMLCount].y = App->CLSB_Model->Group[GroupIndex]->Normal_Data[C].y;
		S_XMLStore[0]->XMLnormal[XMLCount].z = App->CLSB_Model->Group[GroupIndex]->Normal_Data[C].z;

		S_XMLStore[0]->BoneIndex[XMLCount] = 0;// SN[cube.polygon[Count].a].BoneIndex;
		S_XMLStore[0]->XMLpolygon[Face].c = XMLCount;
		XMLCount++;
		Face++;

		FaceCount++;
	}

	S_XMLStore[0]->SXMLCount = XMLCount;

	return 1;
}

// *************************************************************************
// *							WriteNewXML					   		   	   *
// *************************************************************************
bool SB_Export_Ogre3D::WriteNewXML(int GroupIndex)
{
	WriteSubMesh(GroupIndex);

	fprintf(WritePolyFile, "%s\n", "                </vertexbuffer>");
	fprintf(WritePolyFile, "%s\n", "            </geometry>");
	fprintf(WritePolyFile, "%s\n", "        </submesh>");

	return 1;
}

// *************************************************************************
// *							WriteSubMesh				   		   	   *
// *************************************************************************
bool SB_Export_Ogre3D::WriteSubMesh(int GroupIndex)
{
	float x = 0;
	float y = 0;
	float z = 0;

	int a = 0;
	int b = 0;
	int c = 0;

	char MatName[256];

	float V = 0;
	int NewCount = S_XMLStore[0]->SXMLCount;
	int PolyCount = S_XMLStore[0]->SXMLCount / 3;
	int VertCount = S_XMLStore[0]->SXMLCount;
	int Count = 0;


	//------------------------------- texture
	char MaterialNumber[255];
	char SubMesh[256];
	strcpy(SubMesh, "        <submesh material=\"");

	/*strcpy(MatName, App->CL_Model->JustName);
	strcat(MatName, "_");
	strcat(MatName, App->CL_Model->Group[GroupIndex]->MaterialName);*/

	_itoa(GroupIndex, MaterialNumber, 10);
	strcpy(MatName, App->CLSB_Model->JustName);
	strcat(MatName, "_Material_");
	strcat(MatName, MaterialNumber);

	fprintf(WritePolyFile, "%s%s%s %s\n", SubMesh, MatName, "\" usesharedvertices=\"false\"", "use32bitindexes=\"false\" operationtype=\"triangle_list\">");

	//------------------------------- PolyGons
	fprintf(WritePolyFile, "%s%i%s\n", "            <faces count=\"", PolyCount, "\">");

	while (Count < NewCount / 3)
	{
		a = S_XMLStore[0]->XMLpolygon[Count].a;
		b = S_XMLStore[0]->XMLpolygon[Count].b;
		c = S_XMLStore[0]->XMLpolygon[Count].c;

		fprintf(WritePolyFile, "%s%i%s%i%s%i%s\n", "                <face v1=\"", a, "\" v2=\"", b, "\" v3=\"", c, "\" />");
		Count++;
	}

	fprintf(WritePolyFile, "%s\n", "            </faces>");

	//------------------------------- Vertices
	fprintf(WritePolyFile, "%s%i%s\n", "            <geometry vertexcount=\"", VertCount, "\">");
	fprintf(WritePolyFile, "%s\n", "                <vertexbuffer positions=\"true\" normals=\"true\" texture_coord_dimensions_0=\"2\" texture_coords=\"1\">");

	Count = 0;
	while (Count < NewCount)
	{
		fprintf(WritePolyFile, "%s\n", "                    <vertex>");
		x = S_XMLStore[0]->XMLvertex[Count].x;
		y = S_XMLStore[0]->XMLvertex[Count].y;
		z = S_XMLStore[0]->XMLvertex[Count].z;

		u = S_XMLStore[0]->mapcoord[Count].u;
		V = S_XMLStore[0]->mapcoord[Count].v;

		v = 1 - V; // Swop V From RF to Ogre format

		nx = S_XMLStore[0]->XMLnormal[Count].x;
		ny = S_XMLStore[0]->XMLnormal[Count].y;
		nz = S_XMLStore[0]->XMLnormal[Count].z;

		fprintf(WritePolyFile, "%s%f%s%f%s%f%s\n", "                        <position x=\"", x, "\" y=\"", y, "\" z=\"", z, "\" />");
		fprintf(WritePolyFile, "%s%f%s%f%s%f%s\n", "                        <normal x=\"", nx, "\" y=\"", ny, "\" z=\"", nz, "\" />");
		fprintf(WritePolyFile, "%s%f%s%f%s\n", "                        <texcoord u=\"", u, "\" v=\"", v, "\" />");

		fprintf(WritePolyFile, "%s\n", "                    </vertex>");
		Count++;

	}

	return 1;
}
