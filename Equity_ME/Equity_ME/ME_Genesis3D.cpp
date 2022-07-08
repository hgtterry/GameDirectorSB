/*
Copyright (c) 2022 Equity_ME Model Editor -- HGT Software W.T.Flanigan H.C.Flanigan

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
#include "ME_Genesis3D.h"


ME_Genesis3D::ME_Genesis3D()
{
	ActorDef_Memory = nullptr;
	ActorBody_Memory = nullptr;
	TestActor = nullptr;
}


ME_Genesis3D::~ME_Genesis3D()
{
}

// *************************************************************************
// *						LoadActor Terry Bernie					 	   *
// *************************************************************************
void ME_Genesis3D::LoadActor(void)
{

	AddActor(App->CL_Model->Path_FileName);

	//SetCounters();

	////	ListMotions();

	//GetDefaultBones();

	//LoadActorTextures();

	//GetBoundingBoxModel_Create();

	//FileView_AddMotions();

	//App->CL_Model_Data->HasMesh = 1;
}

// *************************************************************************
// *						AddActor Terry Bernie	  			  	 	   *
// *************************************************************************
bool ME_Genesis3D::AddActor(char* FileName)
{
	if (TestActor)
	{
		TestActor = nullptr;
	}

	geVFile* HFile;

	HFile = geVFile_OpenNewSystem(NULL, GE_VFILE_TYPE_DOS,
		FileName, NULL, GE_VFILE_OPEN_READONLY);

	if (HFile)
	{
		ActorDef_Memory = geActor_DefCreateFromFile(HFile);

		if (ActorDef_Memory)
		{
			TestActor = geActor_Create(ActorDef_Memory);

			geActor_SetScale(TestActor, 1, 1, 1);

			BuildActor(TestActor);
		}
		else
		{
			App->Say("Cant Create HFile");
			return 0;
		}
	}

	geVFile_Close(HFile);

	/*RenderActor(TestActor->Puppet, TestActor->Pose);

	Animate(0);

	GetUVs();*/

	//Set_Scene();

	return 1;
}

// *************************************************************************
// *						BuildActor Terry Bernie     		  	 	   *
// *************************************************************************
bool ME_Genesis3D::BuildActor(geActor *Actor)
{
	Actor->Puppet = CreatePuppet(Actor->ActorDefinition->TextureFileContext,Actor->ActorDefinition->Body);

	if (Actor->Puppet == NULL)
	{
		App->Say("Cant Create Puppet");
		return GE_FALSE;
	}

	return GE_TRUE;
}

// *************************************************************************
// *						CreatePuppet	   					  	 	   *
// *************************************************************************
gePuppet* ME_Genesis3D::CreatePuppet(geVFile *TextureFS, const geBody *B)
{
	gePuppet *P;

	assert(geBody_IsValid(B) != GE_FALSE);

	P = GE_RAM_ALLOCATE_STRUCT(gePuppet);
	if (P == NULL)
	{
		App->Say("Cant Create Mem for Puppet");
		return NULL;
	}

	memset(P, 0, sizeof(*P));

	P->BodyInstance = NULL;
	P->MaxDynamicLightsToUse = 3;//PUPPET_DEFAULT_MAX_DYNAMIC_LIGHTS;
	P->LightReferenceBoneIndex = GE_POSE_ROOT_JOINT;

	P->FillLightNormal.X = -0.2f;
	P->FillLightNormal.Y = 1.0f;
	P->FillLightNormal.Z = 0.4f;
	geVec3d_Normalize(&(P->FillLightNormal));
	P->FillLightColor.Red = 0.25f;
	P->FillLightColor.Green = 0.25f;
	P->FillLightColor.Blue = 0.25f;
	P->UseFillLight = GE_TRUE;

	P->AmbientLightIntensity.Red = 0.1f;
	P->AmbientLightIntensity.Green = 0.1f;
	P->AmbientLightIntensity.Blue = 0.1f;
	P->AmbientLightFromFloor = GE_TRUE;

	P->DoShadow = GE_FALSE;
	P->ShadowScale = 0.0f;
	P->ShadowBoneIndex = GE_POSE_ROOT_JOINT;
	P->TextureFileContext = TextureFS;

	P->BodyInstance = CreateGeometry(B);
	if (P->BodyInstance == NULL)
	{
		App->Say("Cant Create Geometry");
		gePuppet_Destroy(&P);
		return NULL;
	}

	return P;
}

// *************************************************************************
// *						CreateGeometry Terry Bernie   			   	   *
// *************************************************************************
geBodyInst* ME_Genesis3D::CreateGeometry(const geBody *B)
{
	geBodyInst *BI;
	assert(B != NULL);
	assert(geBody_IsValid(B) != GE_FALSE);

	BI = GE_RAM_ALLOCATE_STRUCT(geBodyInst);
	//BI = new geBodyInst;
	if (BI == NULL)
	{
		App->Say("Cant Create Mem for Geometry");
		return NULL;
	}
	BI->BodyTemplate = B;
	{
		geBodyInst_Geometry *G = &(BI->ExportGeometry);
		G->SkinVertexCount = 0;
		G->SkinVertexArray = NULL;

		G->NormalCount = 0;
		G->NormalArray = NULL;

		G->FaceCount = (geBody_Index)0;
		G->FaceListSize = 0;
		G->FaceList = NULL;
	}

	BI->LastLevelOfDetail = -1;
	BI->FaceCount = 0;

	return BI;
}
