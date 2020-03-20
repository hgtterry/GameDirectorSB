/*
Copyright (c) Vima19 Inflanite Software W.T.Flanigan H.C.Flanigan

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
#include "VM_Genisis3D.h"
#include "stdio.h"
#include "stdarg.h"

#define GE_BODYINST_FACELIST_SIZE_FOR_TRIANGLE (8)
#define GE_BODY_REALLY_BIG_NUMBER (9e9f)
#define PUPPET_DEFAULT_MAX_DYNAMIC_LIGHTS 3

typedef enum
{
	GE_BODYINST_FACE_TRIANGLE,
	GE_BODYINST_FACE_TRISTRIP,
	GE_BODYINST_FACE_TRIFAN
} geBodyInst_FaceType;


VM_Genisis3D::VM_Genisis3D()
{
	ActorDef_Memory =	nullptr;
	ActorBody_Memory =	nullptr;
	TestActor =			nullptr;
}


VM_Genisis3D::~VM_Genisis3D()
{
}

// *************************************************************************
// *						LoadActor Terry Bernie					 	   *
// *************************************************************************
void VM_Genisis3D::LoadActor(void)
{

	AddActor(App->CL_Vm_Model->Path_FileName);

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
bool VM_Genisis3D::AddActor(char* FileName)
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

	RenderActor(TestActor->Puppet, TestActor->Pose);

	Animate(0);

	App->Say("Loaded2");

	//GetUVs();

	//Set_Scene();

	return 1;
}

// *************************************************************************
// *						Animate Terry Bernie	 			  	 	   *
// *************************************************************************
bool VM_Genisis3D::Animate(int Do)
{
	//if (Do == 1)
	//{
	//	geMotion *Motion = geActor_GetMotionByName(ActorDef_Memory, MotionName);

	//	if (m_CurrentPose>FrameSpeed)
	//	{
	//		//if (MotionLoop == 1)
	//		{
	//			m_CurrentPose = 0;
	//		}
	//		/*else
	//		{
	//		App->C_Ogre->RenderListener->PlayActive = 0;
	//		App->TogglePlayBmp();
	//		return 1;
	//		}*/
	//	}

	//	geActor_SetPose(TestActor, Motion, m_CurrentPose, NULL);

	//	m_CurrentPose += (geFloat)AnimationSpeed;
	//}
	//if (Do == 2)
	//{
	//	if (m_CurrentPose>FrameSpeed)
	//	{
	//		m_CurrentPose = 0;
	//	}

	//	geMotion *Motion = geActor_GetMotionByName(ActorDef_Memory, MotionName);
	//	geActor_SetPose(TestActor, Motion, m_CurrentPose, NULL);

	//	m_CurrentPose += (geFloat)AnimationSpeed * 5;
	//}

	//if (Do == 3)
	//{
	//	if (m_CurrentPose>FrameSpeed)
	//	{
	//		m_CurrentPose = 0;
	//	}

	//	geMotion *Motion = geActor_GetMotionByName(ActorDef_Memory, MotionName);
	//	geActor_SetPose(TestActor, Motion, m_CurrentPose, NULL);

	//	m_CurrentPose -= (geFloat)AnimationSpeed * 5;
	//}

	//if (Do == 4)
	//{
	//	/*if (m_CurrentPose>FrameSpeed)
	//	{
	//	m_CurrentPose = 0;
	//	}*/

	//	geMotion *Motion = geActor_GetMotionByName(ActorDef_Memory, MotionName);
	//	geActor_SetPose(TestActor, Motion, m_CurrentPose, NULL);
	//}

	//int Count = 0;
	//float x;
	//float y;
	//float z;
	//int face1;
	//int face2;
	//int face3;
	//App->CL_Model_Data->VertCount = TestActor->Puppet->BodyInstance->ExportGeometry.SkinVertexCount;

	//App->CL_Model_Data->vertex_Data.resize(App->CL_Model_Data->VertCount);

	//while (Count < App->CL_Model_Data->VertCount)
	//{
	//	x = TestActor->Puppet->BodyInstance->ExportGeometry.SkinVertexArray[Count].SVPoint.X;
	//	y = TestActor->Puppet->BodyInstance->ExportGeometry.SkinVertexArray[Count].SVPoint.Y;
	//	z = TestActor->Puppet->BodyInstance->ExportGeometry.SkinVertexArray[Count].SVPoint.Z;

	//	App->CL_Model_Data->vertex_Data[Count].x = x;
	//	App->CL_Model_Data->vertex_Data[Count].y = y;
	//	App->CL_Model_Data->vertex_Data[Count].z = z;

	//	Count++;
	//}

	//Count = 0;
	//App->CL_Model_Data->NormalsCount = TestActor->Puppet->BodyInstance->ExportGeometry.NormalCount;

	//App->CL_Model_Data->Normal_Data.resize(App->CL_Model_Data->NormalsCount);

	//while (Count < App->CL_Model_Data->NormalsCount)
	//{
	//	x = TestActor->Puppet->BodyInstance->ExportGeometry.NormalArray[Count].X;
	//	y = TestActor->Puppet->BodyInstance->ExportGeometry.NormalArray[Count].Y;
	//	z = TestActor->Puppet->BodyInstance->ExportGeometry.NormalArray[Count].Z;

	//	App->CL_Model_Data->Normal_Data[Count].x = x;
	//	App->CL_Model_Data->Normal_Data[Count].y = y;
	//	App->CL_Model_Data->Normal_Data[Count].z = z;

	//	Count++;
	//}

	//App->CL_Model_Data->FaceCount = TestActor->Puppet->BodyInstance->BodyTemplate->SkinFaces->FaceCount;

	//App->CL_Model_Data->Face_Data.resize(App->CL_Model_Data->FaceCount);
	//App->CL_Model_Data->MatIndex_Data.resize(App->CL_Model_Data->FaceCount);

	//Count = 0;
	//while (Count < App->CL_Model_Data->FaceCount)
	//{
	//	face1 = TestActor->Puppet->BodyInstance->BodyTemplate->SkinFaces[GE_BODY_HIGHEST_LOD].FaceArray[Count].VtxIndex[0];
	//	face2 = TestActor->Puppet->BodyInstance->BodyTemplate->SkinFaces[GE_BODY_HIGHEST_LOD].FaceArray[Count].VtxIndex[1];
	//	face3 = TestActor->Puppet->BodyInstance->BodyTemplate->SkinFaces[GE_BODY_HIGHEST_LOD].FaceArray[Count].VtxIndex[2];

	//	App->CL_Model_Data->MatIndex_Data[Count] = TestActor->Puppet->BodyInstance->BodyTemplate->SkinFaces[GE_BODY_HIGHEST_LOD].FaceArray[Count].MaterialIndex;

	//	App->CL_Model_Data->Face_Data[Count].a = face1;
	//	App->CL_Model_Data->Face_Data[Count].b = face2;
	//	App->CL_Model_Data->Face_Data[Count].c = face3;

	//	Count++;
	//}

	//RenderActor(TestActor->Puppet, TestActor->Pose);

	//                        //App->CL_Actor_Loader->UpDateMeshAnimation();

	//if (App->CL_Model_Data->Model_Loaded == 1)
	//{
	//	GetBoundingBoxModel_Update();
	//}

	return 1;
}

// *************************************************************************
// *						RenderActor Terry Bernie	   		  	 	   *
// *************************************************************************
bool VM_Genisis3D::RenderActor(const gePuppet *P, const gePose *Joints)
{
	const geXFArray *JointTransforms;
	geVec3d Scale;
	const geBodyInst_Geometry *G;

	JointTransforms = gePose_GetAllJointTransforms(Joints);

	gePose_GetScale(Joints, &Scale);

	G = GetGeometry(P->BodyInstance, &Scale, JointTransforms, 0);

	return 1;
}

// *************************************************************************
// *					GetGeometry	Terry Bernie	   			  	 	   *
// *************************************************************************
geBodyInst_Geometry *VM_Genisis3D::GetGeometry(
	const geBodyInst *BI,
	const geVec3d *ScaleVector,
	const geXFArray *BoneTransformArray,
	int LevelOfDetail)
{
	geBodyInst_Geometry *G;
	const geBody *B;
	geXForm3d *BoneXFArray;
	int      BoneXFCount = 0;
	geBody_Index BoneIndex;

	geBoolean GottaUpdateFaces = GE_FALSE;
	assert(BI != NULL);
	assert(BoneTransformArray != NULL);
	assert(geBody_IsValid(BI->BodyTemplate) != GE_FALSE);


	G = TGetGeometryPrep((geBodyInst *)BI, LevelOfDetail);

	if (G == NULL)
	{
		App->Say("Cant Create TGetGeometryPrep");
		return NULL;
	}

	B = BI->BodyTemplate;

	BoneXFArray = geXFArray_GetElements(BoneTransformArray, &BoneXFCount);
	if (BoneXFArray == NULL)
	{
		App->Say("Cant Create BoneXFArray");
		return NULL;
	}
	if (BoneXFCount != B->BoneCount)
	{
		App->Say("BoneXFCount Miss Match");
		return NULL;
	}
	{
		int i, LevelOfDetailBit;

		{
			// transform all appropriate points
			geBody_XSkinVertex *S;
			geBodyInst_SkinVertex  *D;
			LevelOfDetailBit = 1 << LevelOfDetail;
			BoneIndex = -1;  // S->BoneIndex won't ever be this.
			geVec3d_Set(&(G->Maxs), -GE_BODY_REALLY_BIG_NUMBER, -GE_BODY_REALLY_BIG_NUMBER, -GE_BODY_REALLY_BIG_NUMBER);
			geVec3d_Set(&(G->Mins), GE_BODY_REALLY_BIG_NUMBER, GE_BODY_REALLY_BIG_NUMBER, GE_BODY_REALLY_BIG_NUMBER);

			for (i = B->XSkinVertexCount, S = B->XSkinVertexArray, D = G->SkinVertexArray;
				i>0;
				i--, S++, D++)
			{
				geXForm3d ObjectToWorld;
				if (S->BoneIndex != BoneIndex)
				{ //Keep XSkinVertexArray sorted by BoneIndex for best performance
					BoneIndex = S->BoneIndex;
					TPostScale(&BoneXFArray[BoneIndex], ScaleVector, &ObjectToWorld);
				}
				if (S->LevelOfDetailMask && LevelOfDetailBit)
				{
					geVec3d *VecDestPtr = &(D->SVPoint);
					geXForm3d_Transform(&(ObjectToWorld),
						&(S->XPoint), VecDestPtr);
					D->SVU = S->XU;
					D->SVV = S->XV;
					if (VecDestPtr->X > G->Maxs.X) G->Maxs.X = VecDestPtr->X;
					if (VecDestPtr->X < G->Mins.X) G->Mins.X = VecDestPtr->X;
					if (VecDestPtr->Y > G->Maxs.Y) G->Maxs.Y = VecDestPtr->Y;
					if (VecDestPtr->Y < G->Mins.Y) G->Mins.Y = VecDestPtr->Y;
					if (VecDestPtr->Z > G->Maxs.Z) G->Maxs.Z = VecDestPtr->Z;
					if (VecDestPtr->Z < G->Mins.Z) G->Mins.Z = VecDestPtr->Z;
					D->ReferenceBoneIndex = BoneIndex;
				}
			}
		}

		{
			geBody_Normal *S;
			geVec3d *D;
			// rotate all appropriate normals
			for (i = B->SkinNormalCount, S = B->SkinNormalArray, D = G->NormalArray;
				i>0;
				i--, S++, D++)
			{
				if (S->LevelOfDetailMask && LevelOfDetailBit)
				{
					geXForm3d_Rotate(&(BoneXFArray[S->BoneIndex]),
						&(S->Normal), D);
				}
			}
		}
	}
	if (LevelOfDetail != BI->LastLevelOfDetail)
	{
		// build face list to export
		int i, j;
		geBody_Index Count;
		const geBody_Triangle *T;
		geBody_Index *D;
		Count = B->SkinFaces[LevelOfDetail].FaceCount;

		for (i = 0, T = B->SkinFaces[LevelOfDetail].FaceArray, D = G->FaceList;
			i<Count;
			i++, T++, B++)
		{
			*D = GE_BODYINST_FACE_TRIANGLE;
			D++;
			*D = T->MaterialIndex;
			D++;
			for (j = 0; j<3; j++)
			{
				*D = T->VtxIndex[j];
				D++;
				*D = T->NormalIndex[j];
				D++;
			}
		}
		assert(((uint32)D) - ((uint32)G->FaceList) == (uint32)(G->FaceListSize));
		G->FaceCount = Count;
		((geBodyInst *)BI)->LastLevelOfDetail = LevelOfDetail;
	}
	return G;
}

// *************************************************************************
// *						TPostScale Terry Bernie	 			  	 	   *
// *************************************************************************
void VM_Genisis3D::TPostScale(const geXForm3d *M, const geVec3d *S, geXForm3d *Scaled)
{
	Scaled->AX = M->AX * S->X;
	Scaled->BX = M->BX * S->X;
	Scaled->CX = M->CX * S->X;

	Scaled->AY = M->AY * S->Y;
	Scaled->BY = M->BY * S->Y;
	Scaled->CY = M->CY * S->Y;

	Scaled->AZ = M->AZ * S->Z;
	Scaled->BZ = M->BZ * S->Z;
	Scaled->CZ = M->CZ * S->Z;
	Scaled->Translation = M->Translation;
}

// *************************************************************************
// *						TGetGeometryPrep	   			  		 	   *
// *************************************************************************
geBodyInst_Geometry* VM_Genisis3D::TGetGeometryPrep(geBodyInst *BI, int LevelOfDetail)
{
	const geBody *B;
	geBodyInst_Geometry *G;

	assert(BI != NULL);
	assert(geBody_IsValid(BI->BodyTemplate) != GE_FALSE);
	B = BI->BodyTemplate;

	G = &(BI->ExportGeometry);
	assert(G != NULL);

	if (G->SkinVertexCount != B->XSkinVertexCount)
	{
		if (G->SkinVertexArray != NULL)
		{
			geRam_Free(G->SkinVertexArray);
		}
		G->SkinVertexArray = GE_RAM_ALLOCATE_ARRAY(geBodyInst_SkinVertex, B->XSkinVertexCount);
		if (G->SkinVertexArray == NULL)
		{

			G->SkinVertexCount = 0;
			return NULL;
		}
		G->SkinVertexCount = B->XSkinVertexCount;
	}

	if (G->NormalCount != B->SkinNormalCount)
	{
		if (G->NormalArray != NULL)
		{
			geRam_Free(G->NormalArray);
		}
		G->NormalArray = GE_RAM_ALLOCATE_ARRAY(geVec3d, B->SkinNormalCount);
		if (G->NormalArray == NULL)
		{
			G->NormalCount = 0;
			return NULL;
		}
		G->NormalCount = B->SkinNormalCount;
	}

	if (BI->FaceCount != B->SkinFaces[GE_BODY_HIGHEST_LOD].FaceCount)
	{
		if (G->FaceList != NULL)
		{
			geRam_Free(G->FaceList);
		}
		G->FaceListSize = sizeof(geBody_Index) *
			B->SkinFaces[GE_BODY_HIGHEST_LOD].FaceCount *
			GE_BODYINST_FACELIST_SIZE_FOR_TRIANGLE;

		G->FaceList = GE_RAM_ALLOCATE_ARRAY(geBody_Index,
			B->SkinFaces[GE_BODY_HIGHEST_LOD].FaceCount *
			GE_BODYINST_FACELIST_SIZE_FOR_TRIANGLE);

		if (G->FaceList == NULL)
		{
			BI->FaceCount = 0;
			return NULL;
		}
		BI->FaceCount = B->SkinFaces[GE_BODY_HIGHEST_LOD].FaceCount;
	}
	return G;
}

// *************************************************************************
// *						BuildActor Terry Bernie     		  	 	   *
// *************************************************************************
bool VM_Genisis3D::BuildActor(geActor *Actor)
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
gePuppet *VM_Genisis3D::CreatePuppet(geVFile *TextureFS, const geBody *B)
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
geBodyInst* VM_Genisis3D::CreateGeometry(const geBody *B)
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
