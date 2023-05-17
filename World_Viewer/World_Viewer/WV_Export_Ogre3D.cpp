#include "stdafx.h"
#include "WV_App.h"

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

#include "WV_Export_Ogre3D.h"

#include "il.h"
#include "ilu.h"
#include "ilut.h"

#include "bitmap.h"
#include "bitmap._h"
#include "bitmap.__h"

#pragma warning( disable : 4101)

WV_Export_Ogre::WV_Export_Ogre()
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

	Source_Path_FileName[0] = 0;
	Dest_Path_FileName[0] = 0;

	mCurrentFolder[0] = 0;
	Directory_Name[0] = 0;
	NewDirectory[0] = 0;
	Add_Sub_Folder = 1;

	Export_As_RF = 0;

	nx = 0;
	ny = 0;
	nz = 0;

	u = 0;
	v = 0;

	WritePolyFile = nullptr;
}


WV_Export_Ogre::~WV_Export_Ogre()
{
}

// *************************************************************************
// *		Export_AssimpToOgre:- Terry and Hazel Flanigan 2023  	 	   *
// *************************************************************************
bool WV_Export_Ogre::Export_AssimpToOgre(void)
{
	mDecompileFolder[0] = 0;
	mOgreMeshFileName[0] = 0;
	mOgreScriptFileName[0] = 0;
	mOgreSkellFileName[0] = 0;
	mOgreSkellTagName[0] = 0;

	strcpy(Directory_Name, App->CL_Scene->JustName);
	strcat(Directory_Name, "_Ogre");

	strcpy(App->CL_Loader->szSelectedDir, App->CL_Scene->Model_FolderPath);

	App->CL_PB->StartNewProgressBar();
	App->CL_PB->Set_Progress("Building Scene/Game", 15);

	App->CL_PB->Nudge("CreateDirectoryMesh");

	int Test = CreateDirectoryMesh();
	if (Test == 0) { return 1; }

	strcpy(mOgreMeshFileName, App->CL_Scene->JustName);
	strcpy(mOgreScriptFileName, App->CL_Scene->JustName);
	strcpy(mOgreSkellFileName, App->CL_Scene->JustName);
	strcpy(mOgreSkellTagName, App->CL_Scene->JustName);

	strcat(mOgreMeshFileName, ".mesh");
	strcat(mOgreScriptFileName, ".material");
	strcat(mOgreSkellFileName, ".skeleton");

	strcpy(App->CL_Load_Ogre->ModelName, mOgreMeshFileName);

	App->CL_PB->Nudge("DecompileTextures");
	DecompileTextures();

	App->CL_PB->Nudge("CreateMaterialFile");
	CreateMaterialFile(mOgreScriptFileName);

	App->CL_PB->Nudge("Write_XML_File");
	Write_XML_File();

	// ---------------------------------------------------- 
	char SourceFile[1024];
	char OldFile[1024];

	App->CL_PB->Nudge("Transfer");
	strcpy(OldFile, XmlMeshFileName);

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

	App->CL_PB->Nudge("Convert_To_Mesh");
	Convert_To_Mesh();

	App->CL_PB->Nudge("Remove Temp Files");
	remove(OldFile);

	App->CL_PB->Nudge("Convert_To_Mesh");
	App->CL_PB->Nudge("Convert_To_Mesh");
	App->CL_PB->Nudge("Convert_To_Mesh");
	App->CL_PB->Nudge("Convert_To_Mesh");
	
	App->CL_PB->Stop_Progress_Bar("Export to Ogre Format Completed");

	App->CL_Load_Ogre->AddToScene();

	return 1;
}

// *************************************************************************
// *	  		Convert_To_Mesh:- Terry and Hazel Flanigan 2023			   *
// *************************************************************************
bool WV_Export_Ogre::Convert_To_Mesh()
{
	try
	{

		XmlOptions opts = parseArgs();

		opts.source = Source_Path_FileName;
		opts.dest = Dest_Path_FileName;

		meshSerializer = new MeshSerializer();
		xmlMeshSerializer = new XMLMeshSerializer();

		App->CL_PB->Nudge("XMLToBinary");
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

	return 0;
}

// *************************************************************************
// *	  		XMLToBinary:- Terry and Hazel Flanigan 2023				   *
// *************************************************************************
void WV_Export_Ogre::XMLToBinary(XmlOptions opts)
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

		App->CL_PB->Nudge("Generate Edge Lists");
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

		App->CL_PB->Nudge("Export Mesh");
		meshSerializer->exportMesh(newMesh.getPointer(), opts.dest, opts.endian);

		// Clean up the conversion mesh
		App->CL_PB->Nudge("Cleaning Up");
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

// *************************************************************************
// *	  			parseArgs:- Terry and Hazel Flanigan 2023			   *
// *************************************************************************
XmlOptions WV_Export_Ogre::parseArgs()
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
// *		CreateDirectoryMesh:- Terry and Hazel Flanigan 2023		   	   *
// *************************************************************************
bool WV_Export_Ogre::CreateDirectoryMesh(void)
{

	if (Add_Sub_Folder == 0)
	{
		strcpy(NewDirectory, "");
		_chdir(App->CL_Loader->szSelectedDir);
	}
	else
	{
		strcpy(NewDirectory, "\\");
		strcat(NewDirectory, Directory_Name);
		
		strcat(App->CL_Loader->szSelectedDir, NewDirectory);

		if (_mkdir(App->CL_Loader->szSelectedDir) == 0)
		{
			strcpy(mDecompileFolder, App->CL_Loader->szSelectedDir);
			_chdir(App->CL_Loader->szSelectedDir);
		}
		else
		{
			//App->CL_Dialogs->YesNo("File Exsits", "Do you want to update File");

			bool Doit = 0;// App->CL_Dialogs->Canceled;
			if (Doit == 0)
			{
				strcpy(mDecompileFolder, App->CL_Loader->szSelectedDir);
				_chdir(App->CL_Loader->szSelectedDir);
			}
			else
			{
				return 0;
			}
		}

	}
	
	strcpy(App->CL_Load_Ogre->ResourcePath, App->CL_Loader->szSelectedDir);

	_getcwd(mCurrentFolder, 1024);

	return 1;
}

// *************************************************************************
// *		CreateMaterialFile:- Terry and Hazel Flanigan 2023		   	   *
// *************************************************************************
void WV_Export_Ogre::CreateMaterialFile(char* MatFileName)
{
	char MatName[255];
	char File[255];
	char MaterialNumber[255];

	Ogre::String OMatFileName = MatFileName;
	Ogre::String OFile;
	Ogre::String OMatName;

	int numMaterials = App->CL_Scene->GroupCount;

	Ogre::MaterialManager &matMgrSgl = Ogre::MaterialManager::getSingleton();
	//matMgrSgl.initialise();

	Ogre::MaterialSerializer matSer;

	for (int i = 0; i < numMaterials; ++i)
	{
		_itoa(i, MaterialNumber, 10);
		strcpy(MatName, App->CL_Scene->JustName);
		strcat(MatName, "_Material_");
		strcat(MatName, MaterialNumber);

		strcpy(File, App->CL_Scene->Group[i]->Text_FileName);

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
// *			Write_XML_File:- Terry and Hazel Flanigan 2023		   	   *
// *************************************************************************
bool WV_Export_Ogre::Write_XML_File()
{

	S_XMLStore[0] = new XMLStore_Type;
	S_XMLStore[0]->SortedPolyCount = 0;

	char XmlFileName[256];
	char XFIle[256];

	strcpy(XmlFileName, App->CL_Scene->JustName);


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
	while (Count < App->CL_Scene->GroupCount)
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
// *			RenderToXML:- Terry and Hazel Flanigan 2023			   	   *
// *************************************************************************
bool WV_Export_Ogre::RenderToXML(int GroupIndex)
{
	int FaceCount = 0;
	int XMLCount = 0;
	int Face = 0;

	int A = 0;
	int B = 0;
	int C = 0;

	while (FaceCount < App->CL_Scene->Group[GroupIndex]->GroupFaceCount)
	{
		A = App->CL_Scene->Group[GroupIndex]->Face_Data[FaceCount].a;
		B = App->CL_Scene->Group[GroupIndex]->Face_Data[FaceCount].b;
		C = App->CL_Scene->Group[GroupIndex]->Face_Data[FaceCount].c;

		// first vector in face and vertic + normal and uv 
		S_XMLStore[0]->XMLvertex[XMLCount].x = App->CL_Scene->Group[GroupIndex]->vertex_Data[A].x;
		S_XMLStore[0]->XMLvertex[XMLCount].y = App->CL_Scene->Group[GroupIndex]->vertex_Data[A].y;
		S_XMLStore[0]->XMLvertex[XMLCount].z = App->CL_Scene->Group[GroupIndex]->vertex_Data[A].z;

		S_XMLStore[0]->mapcoord[XMLCount].u = App->CL_Scene->Group[GroupIndex]->MapCord_Data[A].u;
		S_XMLStore[0]->mapcoord[XMLCount].v = App->CL_Scene->Group[GroupIndex]->MapCord_Data[A].v;

		S_XMLStore[0]->XMLnormal[XMLCount].x = App->CL_Scene->Group[GroupIndex]->Normal_Data[A].x;
		S_XMLStore[0]->XMLnormal[XMLCount].y = App->CL_Scene->Group[GroupIndex]->Normal_Data[A].y;
		S_XMLStore[0]->XMLnormal[XMLCount].z = App->CL_Scene->Group[GroupIndex]->Normal_Data[A].z;

		S_XMLStore[0]->BoneIndex[XMLCount] = 0;// SN[cube.polygon[Count].a].BoneIndex;
		S_XMLStore[0]->XMLpolygon[Face].a = XMLCount;
		XMLCount++;

		// second vector in face and vertic + normal and uv 
		S_XMLStore[0]->XMLvertex[XMLCount].x = App->CL_Scene->Group[GroupIndex]->vertex_Data[B].x;
		S_XMLStore[0]->XMLvertex[XMLCount].y = App->CL_Scene->Group[GroupIndex]->vertex_Data[B].y;
		S_XMLStore[0]->XMLvertex[XMLCount].z = App->CL_Scene->Group[GroupIndex]->vertex_Data[B].z;

		S_XMLStore[0]->mapcoord[XMLCount].u = App->CL_Scene->Group[GroupIndex]->MapCord_Data[B].u;
		S_XMLStore[0]->mapcoord[XMLCount].v = App->CL_Scene->Group[GroupIndex]->MapCord_Data[B].v;

		S_XMLStore[0]->XMLnormal[XMLCount].x = App->CL_Scene->Group[GroupIndex]->Normal_Data[B].x;
		S_XMLStore[0]->XMLnormal[XMLCount].y = App->CL_Scene->Group[GroupIndex]->Normal_Data[B].y;
		S_XMLStore[0]->XMLnormal[XMLCount].z = App->CL_Scene->Group[GroupIndex]->Normal_Data[B].z;

		S_XMLStore[0]->BoneIndex[XMLCount] = 0;// SN[cube.polygon[Count].a].BoneIndex;
		S_XMLStore[0]->XMLpolygon[Face].b = XMLCount;
		XMLCount++;

		// third vector in face and vertic + normal and uv 
		S_XMLStore[0]->XMLvertex[XMLCount].x = App->CL_Scene->Group[GroupIndex]->vertex_Data[C].x;
		S_XMLStore[0]->XMLvertex[XMLCount].y = App->CL_Scene->Group[GroupIndex]->vertex_Data[C].y;
		S_XMLStore[0]->XMLvertex[XMLCount].z = App->CL_Scene->Group[GroupIndex]->vertex_Data[C].z;

		S_XMLStore[0]->mapcoord[XMLCount].u = App->CL_Scene->Group[GroupIndex]->MapCord_Data[C].u;
		S_XMLStore[0]->mapcoord[XMLCount].v = App->CL_Scene->Group[GroupIndex]->MapCord_Data[C].v;

		S_XMLStore[0]->XMLnormal[XMLCount].x = App->CL_Scene->Group[GroupIndex]->Normal_Data[C].x;
		S_XMLStore[0]->XMLnormal[XMLCount].y = App->CL_Scene->Group[GroupIndex]->Normal_Data[C].y;
		S_XMLStore[0]->XMLnormal[XMLCount].z = App->CL_Scene->Group[GroupIndex]->Normal_Data[C].z;

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
// *			WriteNewXML:- Terry and Hazel Flanigan 2023		   		   *
// *************************************************************************
bool WV_Export_Ogre::WriteNewXML(int GroupIndex)
{
	WriteSubMesh(GroupIndex);

	fprintf(WritePolyFile, "%s\n", "                </vertexbuffer>");
	fprintf(WritePolyFile, "%s\n", "            </geometry>");
	fprintf(WritePolyFile, "%s\n", "        </submesh>");

	return 1;
}

// *************************************************************************
// *			WriteSubMesh:- Terry and Hazel Flanigan 2023		   	   *
// *************************************************************************
bool WV_Export_Ogre::WriteSubMesh(int GroupIndex)
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
	strcpy(MatName, App->CL_Scene->JustName);
	strcat(MatName, "_Material_");
	strcat(MatName, MaterialNumber);

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
// *		DecompileTextures:- Terry and Hazel Flanigan 2023  		  	   *
// *************************************************************************
bool WV_Export_Ogre::DecompileTextures(void)
{
	int MatCount = App->CL_Scene->GroupCount;

	char FileName[255];

	int Loop = 0;
	while (Loop < MatCount)
	{
		strcpy(FileName, App->CL_Scene->Group[Loop]->Text_FileName);

		HBITMAP Data;

		Data = App->CL_Scene->Group[Loop]->Base_Bitmap;

		if (_stricmp(FileName + strlen(FileName) - 4, ".tga") == 0)
		{

			char mDirectory[MAX_PATH];
			_getcwd(mDirectory, MAX_PATH);
			strcat(mDirectory, "\\");
			strcat(mDirectory, FileName);

			WriteTGA(mDirectory, App->CL_Scene->Group[Loop]->RF_Bitmap);
		}
		else if (_stricmp(FileName + strlen(FileName) - 4, ".png") == 0)
		{
			int Len = strlen(FileName);
			FileName[Len - 4] = 0;
			strcat(FileName, ".jpg");

			HBITMAP_TO_BmpFile(Data, FileName, "");
			Jpg_To_png24(FileName);
		}
		else if (_stricmp(FileName + strlen(FileName) - 4, ".jpg") == 0)
		{
			int Len = strlen(FileName);
			FileName[Len - 4] = 0;
			strcat(FileName, ".bmp");

			HBITMAP_TO_BmpFile(Data, FileName, "");
			Bmp_To_Jpg(FileName);
		}
		else
		{

			HBITMAP_TO_BmpFile(Data, FileName, "");
		}

		Loop++;
	}

	return 1;
}

// *************************************************************************
// *			Jpg_To_png24:- Terry and Hazel Flanigan 2023			   *
// *************************************************************************
bool WV_Export_Ogre::Jpg_To_png24(char* File)
{
	char OldFile[1024];
	strcpy(OldFile, File);

	ilLoadImage(File);

	int Len = strlen(File);
	File[Len - 4] = 0;
	strcat(File, ".png");

	ilSaveImage(File);

	remove(OldFile);
	return 1;
}

// *************************************************************************
// *			Bmp_To_Jpg:- Terry and Hazel Flanigan 2023		  	 	   *
// *************************************************************************
bool WV_Export_Ogre::Bmp_To_Jpg(char* File)
{
	char OldFile[1024];
	strcpy(OldFile, File);

	bool test = ilLoadImage(File);
	if (test == 0)
	{
		App->Say("Failed to load Texture Bmp_To_Jpg");
	}

	int Len = strlen(File);
	File[Len - 4] = 0;
	strcat(File, ".jpg");

	ilSaveImage(File);

	remove(OldFile);
	return 1;
}

// *************************************************************************
// *		HBITMAP_TO_BmpFile:- Terry and Hazel Flanigan 2023			   *
// *************************************************************************
bool WV_Export_Ogre::HBITMAP_TO_BmpFile(HBITMAP Bitmap, char* Filename, char* SaveFolder)
{
	HDC hDC;
	int iBits;
	WORD wBitCount;
	DWORD dwPaletteSize = 0, dwBmBitsSize = 0, dwDIBSize = 0, dwWritten = 0;
	BITMAP Bitmap0;
	BITMAPFILEHEADER bmfHdr;
	BITMAPINFOHEADER bi;
	LPBITMAPINFOHEADER lpbi;
	HANDLE fh, hDib, hPal, hOldPal2 = NULL;
	hDC = CreateDC(TEXT("DISPLAY"), NULL, NULL, NULL);
	iBits = GetDeviceCaps(hDC, BITSPIXEL) * GetDeviceCaps(hDC, PLANES);
	DeleteDC(hDC);
	if (iBits <= 1)
		wBitCount = 1;
	else if (iBits <= 4)
		wBitCount = 4;
	else if (iBits <= 8)
		wBitCount = 8;
	else
		wBitCount = 24;
	GetObject(Bitmap, sizeof(Bitmap0), (LPSTR)&Bitmap0);
	bi.biSize = sizeof(BITMAPINFOHEADER);
	bi.biWidth = Bitmap0.bmWidth;
	bi.biHeight = -Bitmap0.bmHeight;
	bi.biPlanes = 1;
	bi.biBitCount = wBitCount;
	bi.biCompression = BI_RGB;
	bi.biSizeImage = 0;
	bi.biXPelsPerMeter = 0;
	bi.biYPelsPerMeter = 0;
	bi.biClrImportant = 0;
	bi.biClrUsed = 256;
	dwBmBitsSize = ((Bitmap0.bmWidth * wBitCount + 31) & ~31) / 8
		* Bitmap0.bmHeight;
	hDib = GlobalAlloc(GHND, dwBmBitsSize + dwPaletteSize + sizeof(BITMAPINFOHEADER));
	lpbi = (LPBITMAPINFOHEADER)GlobalLock(hDib);
	*lpbi = bi;

	hPal = GetStockObject(DEFAULT_PALETTE);
	if (hPal)
	{
		hDC = GetDC(NULL);
		hOldPal2 = SelectPalette(hDC, (HPALETTE)hPal, FALSE);
		RealizePalette(hDC);
	}


	GetDIBits(hDC, Bitmap, 0, (UINT)Bitmap0.bmHeight, (LPSTR)lpbi + sizeof(BITMAPINFOHEADER)
		+ dwPaletteSize, (BITMAPINFO*)lpbi, DIB_RGB_COLORS);

	if (hOldPal2)
	{
		SelectPalette(hDC, (HPALETTE)hOldPal2, TRUE);
		RealizePalette(hDC);
		ReleaseDC(NULL, hDC);
	}

	fh = CreateFile(Filename, GENERIC_WRITE, 0, NULL, CREATE_ALWAYS,
		FILE_ATTRIBUTE_NORMAL | FILE_FLAG_SEQUENTIAL_SCAN, NULL);

	if (fh == INVALID_HANDLE_VALUE)
		return FALSE;

	bmfHdr.bfType = 0x4D42; // "BM"
	dwDIBSize = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER) + dwPaletteSize + dwBmBitsSize;
	bmfHdr.bfSize = dwDIBSize;
	bmfHdr.bfReserved1 = 0;
	bmfHdr.bfReserved2 = 0;
	bmfHdr.bfOffBits = (DWORD)sizeof(BITMAPFILEHEADER) + (DWORD)sizeof(BITMAPINFOHEADER) + dwPaletteSize;

	WriteFile(fh, (LPSTR)&bmfHdr, sizeof(BITMAPFILEHEADER), &dwWritten, NULL);

	WriteFile(fh, (LPSTR)lpbi, dwDIBSize, &dwWritten, NULL);
	GlobalUnlock(hDib);
	GlobalFree(hDib);
	CloseHandle(fh);

	return 1;
}

// *************************************************************************
// *				WriteTGA:- Terry and Hazel Flanigan 2023		  	   *
// *************************************************************************
int WV_Export_Ogre::WriteTGA(const char* pszFile, geBitmap* pBitmap)
{
	geBitmap* pLock = NULL;
	geBitmap* pLockA = NULL;
	gePixelFormat   Format;
	gePixelFormat   FormatA;
	geBitmap_Info   BitmapInfo;
	int             nErrorCode = TPACKERROR_UNKNOWN;      // Return code
	TGAHEADER		tgah;
	long			footer = 0;
	char			signature[18] = "TRUEVISION-XFILE.";

	uint8* pPixelData;
	uint8* pPixelDataA;

	int             i, j;
	HANDLE          hFile = NULL;
	DWORD           nBytesWritten;

	// Create the .TGA file.
	hFile = CreateFile(pszFile,
		GENERIC_READ | GENERIC_WRITE,
		(DWORD)0,
		NULL,
		CREATE_ALWAYS,
		FILE_ATTRIBUTE_NORMAL,
		(HANDLE)NULL);

	if (hFile == INVALID_HANDLE_VALUE)
		return TPACKERROR_CREATEFILE;

	// get 24-bit bitmap
	Format = GE_PIXELFORMAT_24BIT_BGR;
	FormatA = GE_PIXELFORMAT_8BIT_GRAY;

	if (geBitmap_GetBits(pBitmap))
	{
		pLock = pBitmap;
	}
	else
	{
		if (!geBitmap_LockForRead(pBitmap, &pLock, 0, 0, Format, GE_FALSE, 0))
		{
			return FALSE;
		}
	}

	if (geBitmap_GetBits(geBitmap_GetAlpha(pBitmap)))
	{
		pLockA = geBitmap_GetAlpha(pBitmap);
	}
	else
	{
		if (!geBitmap_LockForRead(geBitmap_GetAlpha(pBitmap), &pLockA, 0, 0, FormatA, GE_FALSE, 0))
		{
			return FALSE;
		}
	}

	geBitmap_GetInfo(pLock, &BitmapInfo, NULL);
	if (BitmapInfo.Format != Format)
	{
		nErrorCode = TPACKERROR_UNKNOWN;
		goto ExitWriteBitmap;
	}


	tgah.IDLength = 0;
	tgah.ColorMapType = 0;
	tgah.ImageType = 2; // we create an uncompressed, true color image
	tgah.CMFirstEntry = 0;
	tgah.CMLength = 0;
	tgah.CMEntrySize = 0;
	tgah.Xorigin = 0;
	tgah.Yorigin = 0;

	tgah.Width = (uint16)BitmapInfo.Width;
	tgah.Height = (uint16)BitmapInfo.Height;

	tgah.PixelDepth = 32;
	tgah.ImageDescriptor = 8; //00001000 - not flipped, 8 alpha bits


	pPixelData = (uint8*)geBitmap_GetBits(pLock);

	pPixelDataA = (uint8*)geBitmap_GetBits(pLockA);

	// Write the tga header
	if (!WriteFile(hFile, (LPVOID)&tgah, sizeof(TGAHEADER), (LPDWORD)&nBytesWritten, (NULL)))
	{
		nErrorCode = TPACKERROR_WRITE;
		goto ExitWriteBitmap;
	}

	// write pixels
	pPixelData += 3 * tgah.Width * (tgah.Height - 1);
	pPixelDataA += tgah.Width * (tgah.Height - 1);
	for (i = 0; i < tgah.Height; i++)
	{
		for (j = 0; j < tgah.Width; j++)
		{
			if (!WriteFile(hFile, (LPVOID)pPixelData, 3, (LPDWORD)&nBytesWritten, (NULL)))
			{
				nErrorCode = TPACKERROR_WRITE;
				goto ExitWriteBitmap;
			}

			pPixelData += 3;


			if (!WriteFile(hFile, (LPVOID)pPixelDataA, 1, (LPDWORD)&nBytesWritten, (NULL)))
			{
				nErrorCode = TPACKERROR_WRITE;
				goto ExitWriteBitmap;
			}
			pPixelDataA++;
		}

		pPixelData -= 2 * 3 * tgah.Width;
		pPixelDataA -= 2 * tgah.Width;
	}

	// write the signature
	if (!WriteFile(hFile, (LPVOID)&footer, 4, (LPDWORD)&nBytesWritten, (NULL)))
	{
		nErrorCode = TPACKERROR_WRITE;
		goto ExitWriteBitmap;
	}

	if (!WriteFile(hFile, (LPVOID)&footer, 4, (LPDWORD)&nBytesWritten, (NULL)))
	{
		nErrorCode = TPACKERROR_WRITE;
		goto ExitWriteBitmap;
	}

	if (!WriteFile(hFile, (LPVOID)signature, 18, (LPDWORD)&nBytesWritten, (NULL)))
	{
		nErrorCode = TPACKERROR_WRITE;
		goto ExitWriteBitmap;
	}

	CloseHandle(hFile);
	hFile = NULL;

	// Success!
	nErrorCode = TPACKERROR_OK;

ExitWriteBitmap:

	// Clean-up
	//------------------------------------
	// Make sure the file gets closed
	if (hFile)
		CloseHandle(hFile);

	// Unlock the geBitmap
	if (pLock != pBitmap)
	{
		geBitmap_UnLock(pLock);
	}

	if (pLockA != geBitmap_GetAlpha(pBitmap))
	{
		geBitmap_UnLock(pLockA);
	}

	return nErrorCode;
}
