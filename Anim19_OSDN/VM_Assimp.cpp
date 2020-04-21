#include "stdafx.h"
#include "GD19_App.h"
#include "VM_Assimp.h"


VM_Assimp::VM_Assimp()
{
	SelectedPreset = 8 + 8388608 + 64 + aiProcess_PreTransformVertices;
	mTotalVertices = 0;
}


VM_Assimp::~VM_Assimp()
{
}

// *************************************************************************
// *						logInfo Terry Bernie				  	 	   *
// *************************************************************************
void VM_Assimp::logInfo(std::string logString)
{
	Assimp::DefaultLogger::get()->info(logString.c_str());
}

// *************************************************************************
// *						logDebug Terry Bernie				  	 	   *
// *************************************************************************
void VM_Assimp::logDebug(const char* logString)
{
	Assimp::DefaultLogger::get()->debug(logString);
}

// *************************************************************************
// *						LoadFile Terry Bernie				  	 	   *
// *************************************************************************
bool VM_Assimp::LoadFile(const char* pFile)
{

	//SelectedPreset = GetUserPresets(); // See what user wants

	const aiScene* scene = aiImportFile(pFile, SelectedPreset);

	if (!scene)
	{
		char buf[1024];
		strcpy(buf, aiGetErrorString());
		//App->Cl_Ogre->Loading_Text(buf, 1);
		return false;
	}
	else
	{

		/*App->Cl_Ogre->Loading_Text("Loading GetBasicInfo", 1);
		GetBasicInfo(scene);

		App->Cl_Ogre->Loading_Text("Loading Create_MeshGroups", 1);
		Create_MeshGroups(scene);

		Get_Group_VertCount(scene);

		App->Cl_Ogre->Loading_Text("Loading StoreMeshData", 1);
		StoreMeshData(scene);

		App->Cl_Ogre->Loading_Text("Loading Textures", 1);

		if (App->Cl_Importer->Is_RFEditPro == 1)
		{
			LoadTextures_RFEditPro();
		}
		else
		{
			LoadTextures();
		}

		App->Cl_Ogre->Loading_Text("Loading Creating BBox", 1);
		App->CL_Model_Data->Create_BondingBox_Model();*/

	}

	aiReleaseImport(scene);
	return 1;
}
