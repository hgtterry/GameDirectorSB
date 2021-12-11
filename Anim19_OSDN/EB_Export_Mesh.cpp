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

#include "Ogre.h"
#include "OgreXMLMeshSerializer.h"
#include "OgreMeshSerializer.h"
#include "OgreXMLSkeletonSerializer.h"
#include "OgreSkeletonSerializer.h"
#include "OgreXMLPrerequisites.h"
#include "OgreDefaultHardwareBufferManager.h"
#include "OgreProgressiveMeshGenerator.h"
#include "OgreDistanceLodStrategy.h"
#include <iostream>
#include <sys/stat.h>

#include "EB_Export_Mesh.h"

#pragma warning (disable : 4101)

using namespace std;
using namespace Ogre;

EB_Export_Mesh::EB_Export_Mesh()
{
	
	meshSerializer = nullptr;
	xmlMeshSerializer = nullptr;
	
	mDecompileFolder[0] = 0;
	mOgreMeshFileName[0] = 0;
	mOgreScriptFileName[0] = 0;
	mOgreSkellFileName[0] = 0;
	mOgreSkellTagName[0] = 0;

	nx = 0;
	ny = 0;
	nz = 0;

	u = 0;
	v = 0;

	DoSkell = 0;
}


EB_Export_Mesh::~EB_Export_Mesh()
{
}

// *************************************************************************
// *					Export_AssimpToOgre Terry Bernie  			 	   *
// *************************************************************************
bool EB_Export_Mesh::Export_AssimpToOgre(void)
{
	mDecompileFolder[0] = 0;
	mOgreMeshFileName[0] = 0;
	mOgreScriptFileName[0] = 0;
	mOgreSkellFileName[0] = 0;
	mOgreSkellTagName[0] = 0;

	strcpy(App->CL_Vm_FileIO->BrowserMessage, "Select Folder To Place Ogre Files a sub folder will be created");
	int Test = App->CL_Vm_FileIO->StartBrowser("");

	if (Test == 0) { return 1; }

	Test = CreateDirectoryMesh();

	if (Test == 0){ return 1; }

	strcpy(mOgreMeshFileName, App->CL_Vm_Model->JustName);
	strcpy(mOgreScriptFileName, App->CL_Vm_Model->JustName);
	strcpy(mOgreSkellFileName, App->CL_Vm_Model->JustName);
	strcpy(mOgreSkellTagName, App->CL_Vm_Model->JustName);

	strcat(mOgreMeshFileName, ".mesh");
	strcat(mOgreScriptFileName, ".material");
	strcat(mOgreSkellFileName, ".skeleton");

	DecompileTextures();
	
	//CreateMaterialFile(mOgreScriptFileName);

	StartRenderToXML(1);

	// ---------------------------------------------------- 
	char SourceFile[1024];
	strcpy(SourceFile, mCurrentFolder);
	strcat(SourceFile, "\\");
	strcat(SourceFile, XmlMeshFileName);

	strcpy(Source_Path_FileName, SourceFile);

	int Len = strlen(XmlMeshFileName);
	XmlMeshFileName[Len - 4] = 0;

	char DestFile[1024];
	strcpy(DestFile, mCurrentFolder);
	strcat(DestFile, "\\");
	strcat(DestFile, XmlMeshFileName);

	strcpy(Dest_Path_FileName, DestFile);

	//App->Say(Source_Path_FileName);
	//App->Say(Dest_Path_FileName);

	Convert_To_Mesh();
	
	App->Say("Converted");

	return 1;
}

// *************************************************************************
// *							StartRenderToXML			   		   	   *
// *************************************************************************
bool EB_Export_Mesh::StartRenderToXML(int LTextureFormat)
{

	S_XMLStore[0] = new XMLStore_Type2;
	S_XMLStore[0]->SortedPolyCount = 0;

	char XmlFileName[256];
	char XFIle[256];


	strcpy(XmlFileName, App->CL_Vm_Model->FileName);

	int Len = strlen(XmlFileName);
	XmlFileName[Len - 4] = 0;



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
	
	WritePolyFile = fopen(XmlMeshFileName, "wt");
	if (!WritePolyFile)
	{
		return 0;
	}

	fprintf(WritePolyFile, "%s\n", "<mesh>");
	fprintf(WritePolyFile, "%s\n", "    <submeshes>");

	int Count = 0;
	while (Count < App->CL_Vm_Model->GroupCount)
	{
		RenderToXML(Count);
		WriteNewXML(Count);
		Count++;
	}


	fprintf(WritePolyFile, "%s\n", "    </submeshes>");

	if (DoSkell == 1)
	{
		fprintf(WritePolyFile, "%s%s%s\n", "    <skeletonlink name=\"", XmlSkellTagName, "\" />");
	}

	fprintf(WritePolyFile, "%s\n", "</mesh>");

	fclose(WritePolyFile);

	if (S_XMLStore[0])
	{
		delete S_XMLStore[0];
		S_XMLStore[0] = NULL;

	}


	//char RunFile[1024];

	//strcpy(RunFile, App->EquityDirecory_FullPath);
	//strcat(RunFile, "\\");
	//strcat(RunFile, "OgreXmlConverter.exe");

	////App->Say("Converted");

	//ShellExecute(0, "open", RunFile, XmlMeshFileName, NULL, SW_SHOW);
	//remove("OgreXMLConverter.log");
	//remove(XmlMeshFileName);
	return 1;
}

// *************************************************************************
// *							WriteNewXML					   		   	   *
// *************************************************************************
bool EB_Export_Mesh::WriteNewXML(int GroupIndex)
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
bool EB_Export_Mesh::WriteSubMesh(int GroupIndex)
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

	char SubMesh[256];
	strcpy(SubMesh, "        <submesh material=\"");

	strcpy(MatName, App->CL_Vm_Model->JustName);
	strcat(MatName, "_");
	strcat(MatName, App->CL_Vm_Model->S_MeshGroup[GroupIndex]->MaterialName);

	fprintf(WritePolyFile, "%s%s%s %s\n", SubMesh, MatName, "\" usesharedvertices=\"false\"", "use32bitindexes=\"false\" operationtype=\"triangle_list\">");

	//------------------------------- PolyGons
	fprintf(WritePolyFile, "%s%i%s\n", "            <faces count=\"", PolyCount, "\">");

	while (Count<NewCount / 3)
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
	while (Count<NewCount)
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

// *************************************************************************
// *							RenderToXML					   		   	   *
// *************************************************************************
bool EB_Export_Mesh::RenderToXML(int GroupIndex)
{
	int FaceCount = 0;
	int XMLCount = 0;
	int Face = 0;

	int A = 0;
	int B = 0;
	int C = 0;

	while (FaceCount < App->CL_Vm_Model->S_MeshGroup[GroupIndex]->GroupFaceCount)
	{
		A = App->CL_Vm_Model->S_MeshGroup[GroupIndex]->Face_Data[FaceCount].a;
		B = App->CL_Vm_Model->S_MeshGroup[GroupIndex]->Face_Data[FaceCount].b;
		C = App->CL_Vm_Model->S_MeshGroup[GroupIndex]->Face_Data[FaceCount].c;

		// first vector in face and vertic + normal and uv 
		S_XMLStore[0]->XMLvertex[XMLCount].x = App->CL_Vm_Model->S_MeshGroup[GroupIndex]->vertex_Data[A].x;
		S_XMLStore[0]->XMLvertex[XMLCount].y = App->CL_Vm_Model->S_MeshGroup[GroupIndex]->vertex_Data[A].y;
		S_XMLStore[0]->XMLvertex[XMLCount].z = App->CL_Vm_Model->S_MeshGroup[GroupIndex]->vertex_Data[A].z;

		S_XMLStore[0]->mapcoord[XMLCount].u = App->CL_Vm_Model->S_MeshGroup[GroupIndex]->MapCord_Data[A].u;
		S_XMLStore[0]->mapcoord[XMLCount].v = App->CL_Vm_Model->S_MeshGroup[GroupIndex]->MapCord_Data[A].v;

		S_XMLStore[0]->XMLnormal[XMLCount].x = App->CL_Vm_Model->S_MeshGroup[GroupIndex]->Normal_Data[A].x;
		S_XMLStore[0]->XMLnormal[XMLCount].y = App->CL_Vm_Model->S_MeshGroup[GroupIndex]->Normal_Data[A].y;
		S_XMLStore[0]->XMLnormal[XMLCount].z = App->CL_Vm_Model->S_MeshGroup[GroupIndex]->Normal_Data[A].z;

		S_XMLStore[0]->BoneIndex[XMLCount] = 0;// SN[cube.polygon[Count].a].BoneIndex;
		S_XMLStore[0]->XMLpolygon[Face].a = XMLCount;
		XMLCount++;

		// second vector in face and vertic + normal and uv 
		S_XMLStore[0]->XMLvertex[XMLCount].x = App->CL_Vm_Model->S_MeshGroup[GroupIndex]->vertex_Data[B].x;
		S_XMLStore[0]->XMLvertex[XMLCount].y = App->CL_Vm_Model->S_MeshGroup[GroupIndex]->vertex_Data[B].y;
		S_XMLStore[0]->XMLvertex[XMLCount].z = App->CL_Vm_Model->S_MeshGroup[GroupIndex]->vertex_Data[B].z;

		S_XMLStore[0]->mapcoord[XMLCount].u = App->CL_Vm_Model->S_MeshGroup[GroupIndex]->MapCord_Data[B].u;
		S_XMLStore[0]->mapcoord[XMLCount].v = App->CL_Vm_Model->S_MeshGroup[GroupIndex]->MapCord_Data[B].v;

		S_XMLStore[0]->XMLnormal[XMLCount].x = App->CL_Vm_Model->S_MeshGroup[GroupIndex]->Normal_Data[B].x;
		S_XMLStore[0]->XMLnormal[XMLCount].y = App->CL_Vm_Model->S_MeshGroup[GroupIndex]->Normal_Data[B].y;
		S_XMLStore[0]->XMLnormal[XMLCount].z = App->CL_Vm_Model->S_MeshGroup[GroupIndex]->Normal_Data[B].z;

		S_XMLStore[0]->BoneIndex[XMLCount] = 0;// SN[cube.polygon[Count].a].BoneIndex;
		S_XMLStore[0]->XMLpolygon[Face].b = XMLCount;
		XMLCount++;

		// third vector in face and vertic + normal and uv 
		S_XMLStore[0]->XMLvertex[XMLCount].x = App->CL_Vm_Model->S_MeshGroup[GroupIndex]->vertex_Data[C].x;
		S_XMLStore[0]->XMLvertex[XMLCount].y = App->CL_Vm_Model->S_MeshGroup[GroupIndex]->vertex_Data[C].y;
		S_XMLStore[0]->XMLvertex[XMLCount].z = App->CL_Vm_Model->S_MeshGroup[GroupIndex]->vertex_Data[C].z;

		S_XMLStore[0]->mapcoord[XMLCount].u = App->CL_Vm_Model->S_MeshGroup[GroupIndex]->MapCord_Data[C].u;
		S_XMLStore[0]->mapcoord[XMLCount].v = App->CL_Vm_Model->S_MeshGroup[GroupIndex]->MapCord_Data[C].v;

		S_XMLStore[0]->XMLnormal[XMLCount].x = App->CL_Vm_Model->S_MeshGroup[GroupIndex]->Normal_Data[C].x;
		S_XMLStore[0]->XMLnormal[XMLCount].y = App->CL_Vm_Model->S_MeshGroup[GroupIndex]->Normal_Data[C].y;
		S_XMLStore[0]->XMLnormal[XMLCount].z = App->CL_Vm_Model->S_MeshGroup[GroupIndex]->Normal_Data[C].z;

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
// *						CreateMaterialFile				   		   	   *
// *************************************************************************
void EB_Export_Mesh::CreateMaterialFile(char* MatFileName)
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
// *			DecompileTextures  30/03/04   					   	   	   *
// *************************************************************************
bool EB_Export_Mesh::DecompileTextures(void)
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
// *							CreateDirectoryMesh			   		   	   *
// *************************************************************************
bool EB_Export_Mesh::CreateDirectoryMesh(void)
{

	char NewDirectory[200];
	strcpy(NewDirectory, App->CL_Vm_Model->JustName);

	strcat(NewDirectory, "_Ogre");

	strcat(App->CL_Vm_FileIO->szSelectedDir, NewDirectory);

	if (_mkdir(App->CL_Vm_FileIO->szSelectedDir) == 0)
	{
		strcpy(mDecompileFolder, App->CL_Vm_FileIO->szSelectedDir);
		_chdir(App->CL_Vm_FileIO->szSelectedDir);
	}
	else
	{
		_chdir(App->CL_Vm_FileIO->szSelectedDir);
	}

	_getcwd(mCurrentFolder, 1024);


	//App->Say(App->CL_Vm_FileIO->szSelectedDir);
	//App->Say(mCurrentFolder);

	return 1;
}



// *************************************************************************
// *	  				 Convert_To_Mesh	Terry Bernie				   *
// *************************************************************************
bool EB_Export_Mesh::Convert_To_Mesh()
{
	try
	{
		
		XmlOptions opts = parseArgs();

		opts.source = Source_Path_FileName;
		opts.dest = Dest_Path_FileName;

		meshSerializer = new MeshSerializer();
		xmlMeshSerializer = new XMLMeshSerializer();
	
		XMLToBinary(opts);

	}
	catch (Exception& e)
	{

		MessageBox(App->MainHwnd, "Failed", "Message", MB_OK);
		return 1;
	}

	Pass::processPendingPassUpdates(); // make sure passes are cleaned up

	delete xmlMeshSerializer;
	delete meshSerializer;
	
	MessageBox(NULL, "Converted Terry 2", "Message", MB_OK);

	return 0;
}

// *************************************************************************
// *	  					 parseArgs	Terry Bernie					   *
// *************************************************************************
XmlOptions EB_Export_Mesh::parseArgs()
{
	XmlOptions opts;

	opts.interactiveMode = false;
	opts.lodValue = 250000;
	opts.lodFixed = 0;
	opts.lodPercent = 20;
	opts.numLods = 0;
	opts.nuextremityPoints = 0;
	opts.mergeTexcoordResult = 0;
	opts.mergeTexcoordToDestroy = 0;
	opts.usePercent = true;
	opts.generateEdgeLists = true;
	opts.generateTangents = false;
	opts.tangentSemantic = VES_TANGENT;
	opts.tangentUseParity = false;
	opts.tangentSplitMirrored = false;
	opts.tangentSplitRotated = false;
	opts.reorganiseBuffers = true;
	opts.optimiseAnimations = true;
	opts.quietMode = true;
	opts.endian = Serializer::ENDIAN_NATIVE;
	opts.source = " ";
	opts.dest = " ";

	return opts;
}

// *************************************************************************
// *	  					 XMLToBinary	Terry Bernie				   *
// *************************************************************************
void EB_Export_Mesh::XMLToBinary(XmlOptions opts)
{

	// Read root element and decide from there what type
	String response;
	TiXmlDocument* doc = new TiXmlDocument(opts.source.c_str());
	// Some double-parsing here but never mind
	if (!doc->LoadFile())
	{
		delete doc;
		exit(1);
	}
	TiXmlElement* root = doc->RootElement();
	if (!_stricmp(root->Value(), "mesh"))
	{
		delete doc;
		MeshPtr newMesh = MeshManager::getSingleton().createManual("conversion",
			ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME);
		VertexElementType colourElementType;
		if (opts.d3d)
			colourElementType = VET_COLOUR_ARGB;
		else
			colourElementType = VET_COLOUR_ABGR;

		xmlMeshSerializer->importMesh(opts.source, colourElementType, newMesh.getPointer());

		// Re-jig the buffers?
		// Make sure animation types are up to date first
		newMesh->_determineAnimationTypes();
		if (opts.reorganiseBuffers)
		{

			// Shared geometry
			if (newMesh->sharedVertexData)
			{
				// Automatic
				VertexDeclaration* newDcl =
					newMesh->sharedVertexData->vertexDeclaration->getAutoOrganisedDeclaration(
						newMesh->hasSkeleton(), newMesh->hasVertexAnimation(), newMesh->getSharedVertexDataAnimationIncludesNormals());
				if (*newDcl != *(newMesh->sharedVertexData->vertexDeclaration))
				{
					// Usages don't matter here since we're onlly exporting
					BufferUsageList bufferUsages;
					for (size_t u = 0; u <= newDcl->getMaxSource(); ++u)
						bufferUsages.push_back(HardwareBuffer::HBU_STATIC_WRITE_ONLY);
					newMesh->sharedVertexData->reorganiseBuffers(newDcl, bufferUsages);
				}
			}
			// Dedicated geometry
			Mesh::SubMeshIterator smIt = newMesh->getSubMeshIterator();
			while (smIt.hasMoreElements())
			{
				SubMesh* sm = smIt.getNext();
				if (!sm->useSharedVertices)
				{
					const bool hasVertexAnim = sm->getVertexAnimationType() != Ogre::VAT_NONE;

					// Automatic
					VertexDeclaration* newDcl =
						sm->vertexData->vertexDeclaration->getAutoOrganisedDeclaration(
							newMesh->hasSkeleton(), hasVertexAnim, sm->getVertexAnimationIncludesNormals());
					if (*newDcl != *(sm->vertexData->vertexDeclaration))
					{
						// Usages don't matter here since we're onlly exporting
						BufferUsageList bufferUsages;
						for (size_t u = 0; u <= newDcl->getMaxSource(); ++u)
							bufferUsages.push_back(HardwareBuffer::HBU_STATIC_WRITE_ONLY);
						sm->vertexData->reorganiseBuffers(newDcl, bufferUsages);
					}
				}
			}

		}

		// Prompt for LOD generation?
		bool genLod = false;
		bool askLodDtls = false;
		if (!opts.interactiveMode) // derive from params if in batch mode
		{
			askLodDtls = false;
			if (opts.numLods == 0)
			{
				genLod = false;
			}
			else
			{
				genLod = true;
			}
		}
		else if (opts.numLods == 0) // otherwise only ask if not specified on command line
		{
			if (newMesh->getNumLodLevels() > 1)
			{

				while (response == "")
				{
					cin >> response;
					StringUtil::toLowerCase(response);
					if (response == "u")
					{
						// Do nothing
					}
					else if (response == "d")
					{
						newMesh->removeLodLevels();
					}
					else if (response == "r")
					{
						genLod = true;
						askLodDtls = true;

					}
					else
					{

						response = "";
					}
				}// while response == ""
			}
			else // no existing LOD
			{
				std::cout << "\nWould you like to generate LOD information? (y/n) ";
				while (response == "")
				{
					cin >> response;
					StringUtil::toLowerCase(response);
					if (response == "n")
					{
						// Do nothing
					}
					else if (response == "y")
					{
						genLod = true;
						askLodDtls = true;
					}
					else
					{

						response = "";
					}
				}
			}
		}

		if (genLod)
		{
			unsigned short numLod;
			LodConfig lodConfig;
			lodConfig.levels.clear();
			lodConfig.mesh = newMesh->clone(newMesh->getName());
			lodConfig.strategy = DistanceLodSphereStrategy::getSingletonPtr();

			LodLevel lodLevel;
			lodLevel.reductionMethod = LodLevel::VRM_PROPORTIONAL;

			if (askLodDtls)
			{
				cout << "\nHow many extra LOD levels would you like to generate? ";
				cin >> numLod;

				cout << "\nWhat LOD strategy should be used? ";
				cin >> opts.lodStrategy;

				cout << "\nWhat unit of reduction would you like to use:" <<
					"\n(f)ixed or (p)roportional? ";
				response = "";
				while (response == "") {
					cin >> response;
					StringUtil::toLowerCase(response);
					if (response == "f")
					{
						lodLevel.reductionMethod = LodLevel::VRM_CONSTANT;

					}
					else if (response == "p")
					{
						lodLevel.reductionMethod = LodLevel::VRM_PROPORTIONAL;

					}
					else {

						response = "";
					}
				}
				cin >> lodLevel.reductionValue;
				if (lodLevel.reductionMethod == LodLevel::VRM_PROPORTIONAL)
				{
					// Percentage -> parametric
					lodLevel.reductionValue *= 0.01f;
				}



				for (unsigned short iLod = 0; iLod < numLod; ++iLod)
				{

					lodConfig.levels.push_back(lodLevel);
				}
			}
			else
			{
				numLod = opts.numLods;
				lodLevel.reductionMethod = opts.usePercent ?
					LodLevel::VRM_PROPORTIONAL : LodLevel::VRM_CONSTANT;
				if (opts.usePercent)
				{
					lodLevel.reductionValue = opts.lodPercent * 0.01f;
				}
				else
				{
					lodLevel.reductionValue = (Ogre::Real)opts.lodFixed;
				}
				Real currDist = 0;
				for (unsigned short iLod = 0; iLod < numLod; ++iLod)
				{
					currDist += opts.lodValue;
					Real currDistSq = Ogre::Math::Sqr(currDist);
					lodLevel.distance = currDistSq;
					lodConfig.levels.push_back(lodLevel);
				}

			}

			newMesh->setLodStrategy(LodStrategyManager::getSingleton().getStrategy(opts.lodStrategy));
			ProgressiveMeshGenerator pm;
			pm.generateLodLevels(lodConfig);
		}

		if (opts.interactiveMode)
		{

			while (response == "")
			{
				cin >> response;
				StringUtil::toLowerCase(response);
				if (response == "y")
				{
					// Do nothing
				}
				else if (response == "n")
				{
					opts.generateEdgeLists = false;
				}
				else
				{

					response = "";
				}
			}



			while (response == "")
			{
				cin >> response;
				StringUtil::toLowerCase(response);
				if (response == "y")
				{
					opts.generateTangents = true;
				}
				else if (response == "n")
				{
					// Do nothing
				}
				else
				{

					response = "";
				}
			}
		}

		if (opts.generateEdgeLists)
		{
			if (!opts.quietMode)
			{

			}
			newMesh->buildEdgeList();
		}

		if (opts.generateTangents)
		{
			unsigned short srcTex, destTex;
			if (!opts.quietMode)
			{

			}
			bool existing;
			try {
				existing = newMesh->suggestTangentVectorBuildParams(opts.tangentSemantic, srcTex, destTex);
			}
			catch (Exception &e) {
				std::cerr << "WARNING: While checking for existing tangents: " << e.getFullDescription() << std::endl;
				std::cerr << "NOTE: Tangents were NOT generated for this mesh!" << std::endl;
				existing = false;
				opts.generateTangents = false;
			}
			if (existing)
			{

				while (response == "")
				{
					cin >> response;
					StringUtil::toLowerCase(response);
					if (response == "y")
					{
						// Do nothing
					}
					else if (response == "n")
					{
						opts.generateTangents = false;
					}
					else
					{
						std::cout << "Did not understand \"" << response << "\" please try again:" << std::endl;
						response = "";
					}
				}

			}
			if (opts.generateTangents)
			{
				if (!opts.quietMode)
				{

				}
				newMesh->buildTangentVectors(opts.tangentSemantic, srcTex, destTex,
					opts.tangentSplitMirrored, opts.tangentSplitRotated, opts.tangentUseParity);
			}
		}

		if (opts.mergeTexcoordResult != opts.mergeTexcoordToDestroy)
		{
			newMesh->mergeAdjacentTexcoords(opts.mergeTexcoordResult, opts.mergeTexcoordToDestroy);
		}

		if (opts.nuextremityPoints)
		{
			Mesh::SubMeshIterator smIt = newMesh->getSubMeshIterator();
			while (smIt.hasMoreElements())
			{
				SubMesh* sm = smIt.getNext();
				sm->generateExtremes(opts.nuextremityPoints);
			}
		}

		meshSerializer->exportMesh(newMesh.getPointer(), opts.dest, opts.endian);

		// Clean up the conversion mesh
		MeshManager::getSingleton().remove("conversion");
	}
	else if (!_stricmp(root->Value(), "skeleton"))
	{
		delete doc;
		//SkeletonPtr newSkel = SkeletonManager::getSingleton().create("conversion",
		//	ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME);
		//xmlSkeletonSerializer->importSkeleton(opts.source, newSkel.getPointer());
		//if (opts.optimiseAnimations)
		//{
		//	newSkel->optimiseAllAnimations();
		//}
		//skeletonSerializer->exportSkeleton(newSkel.getPointer(), opts.dest, SKELETON_VERSION_LATEST, opts.endian);

		//// Clean up the conversion skeleton
		//SkeletonManager::getSingleton().remove("conversion");
	}
	else
	{
		delete doc;
	}

}
