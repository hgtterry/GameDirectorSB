/*
Copyright (c) 2022 Equity_ME Model Editor -- Inflanite Software W.T.Flanigan H.C.Flanigan

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
#include "ME_App.h"
#include "ME_Assimp.h"


ME_Assimp::ME_Assimp()
{
	SelectedPreset = 8 + 8388608 + 64 + aiProcess_PreTransformVertices;
	mTotalVertices = 0;
}


ME_Assimp::~ME_Assimp()
{
}

// *************************************************************************
// *						logInfo Terry Bernie				  	 	   *
// *************************************************************************
void ME_Assimp::logInfo(std::string logString)
{
	Assimp::DefaultLogger::get()->info(logString.c_str());
}

// *************************************************************************
// *						logDebug Terry Bernie				  	 	   *
// *************************************************************************
void ME_Assimp::logDebug(const char* logString)
{
	Assimp::DefaultLogger::get()->debug(logString);
}

// *************************************************************************
// *						LoadFile Terry Bernie				  	 	   *
// *************************************************************************
bool ME_Assimp::LoadFile(const char* pFile)
{

	//SelectedPreset = GetUserPresets(); // See what user wants

	const aiScene* scene = aiImportFile(pFile, SelectedPreset);

	if (!scene)
	{
		char buf[1024];
		strcpy(buf, aiGetErrorString());
////		App->Say(buf);
		return false;
	}
	else
	{

////	GetBasicInfo(scene);

////		Create_MeshGroups(scene);

////		Get_Group_VertCount(scene);

////		StoreMeshData(scene);
	
////		LoadTextures();
		
////		App->CL_Vm_Model->Create_BondingBox_Model();

	}

	aiReleaseImport(scene);
	return 1;
}
