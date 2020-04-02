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

	MotionName[0] = 0;

	FrameSpeed = (float)1.15;;
	m_CurrentPose = NULL;
	AnimationSpeed = (float)0.005;
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

	SetCounters();

	GetDefaultBones();

	if (App->CL_Vm_Model->MotionCount > 0)
	{
		Get_MotionNames();
		App->CL_Vm_Motions->Populate_Combo();
	}

	Get_TextureNames();

	
	LoadActorTextures();

	App->Say("Loaded5");

	GetBoundingBoxModel_Create();

	//App->CL_Vm_Model->HasMesh = 1;

}

// *************************************************************************
// *						Get_TextureNames Terry Bernie			 	   *
// *************************************************************************
void VM_Genisis3D::Get_TextureNames(void)
{
	const char *MaterialName;
	int Count = 0;
	int MatIndex = 0;

	int mTexturesCount = App->CL_Vm_Model->TextureCount;

	App->CL_Vm_Model->TextureNames_Data.resize(mTexturesCount);

	while (Count < mTexturesCount)
	{
		MaterialName = geStrBlock_GetString(ActorDef_Memory->Body->MaterialNames, Count);
		strcpy(App->CL_Vm_Model->TextureNames_Data[Count].Name, MaterialName);
		Count++;
	}	
}

// *************************************************************************
// *						Get_MotionNames Terry Bernie			 	   *
// *************************************************************************
void VM_Genisis3D::Get_MotionNames(void)
{
	const char *TempMotionName;
	int Count = 0;
	
	int mMotionsCount = App->CL_Vm_Model->MotionCount;

	App->CL_Vm_Model->MotionNames_Data.resize(mMotionsCount);

	while (Count < mMotionsCount)
	{
		TempMotionName = geActor_GetMotionName(ActorDef_Memory, Count);
		strcpy(App->CL_Vm_Model->MotionNames_Data[Count].Name, TempMotionName);
		Count++;
	}
}

// *************************************************************************
// *				GetBoundingBoxModel_Create Terry Bernie				   *
// *************************************************************************
bool VM_Genisis3D::GetBoundingBoxModel_Create(void)
{

	App->CL_Vm_Model->S_BoundingBox[0] = new AABB_Type;

	App->CL_Vm_Model->S_BoundingBox[0]->BB_Min[0].x = App->CL_Vm_Model->vertex_Data[0].x;
	App->CL_Vm_Model->S_BoundingBox[0]->BB_Min[0].y = App->CL_Vm_Model->vertex_Data[0].y;
	App->CL_Vm_Model->S_BoundingBox[0]->BB_Min[0].z = App->CL_Vm_Model->vertex_Data[0].z;

	App->CL_Vm_Model->S_BoundingBox[0]->BB_Max[0].x = App->CL_Vm_Model->vertex_Data[0].x;
	App->CL_Vm_Model->S_BoundingBox[0]->BB_Max[0].y = App->CL_Vm_Model->vertex_Data[0].y;
	App->CL_Vm_Model->S_BoundingBox[0]->BB_Max[0].z = App->CL_Vm_Model->vertex_Data[0].z;

	int Count = 0;
	int VertCount = 0;
	//while (Count<App->S_Counters[0]->GroupCount)
	//{
	VertCount = 0;
	while (VertCount < App->CL_Vm_Model->VerticeCount)
	{
		if (App->CL_Vm_Model->vertex_Data[VertCount].x < App->CL_Vm_Model->S_BoundingBox[0]->BB_Min[0].x) App->CL_Vm_Model->S_BoundingBox[0]->BB_Min[0].x = App->CL_Vm_Model->vertex_Data[VertCount].x;
		if (App->CL_Vm_Model->vertex_Data[VertCount].y < App->CL_Vm_Model->S_BoundingBox[0]->BB_Min[0].y) App->CL_Vm_Model->S_BoundingBox[0]->BB_Min[0].y = App->CL_Vm_Model->vertex_Data[VertCount].y;
		if (App->CL_Vm_Model->vertex_Data[VertCount].z < App->CL_Vm_Model->S_BoundingBox[0]->BB_Min[0].z) App->CL_Vm_Model->S_BoundingBox[0]->BB_Min[0].z = App->CL_Vm_Model->vertex_Data[VertCount].z;
		if (App->CL_Vm_Model->vertex_Data[VertCount].x > App->CL_Vm_Model->S_BoundingBox[0]->BB_Max[0].x) App->CL_Vm_Model->S_BoundingBox[0]->BB_Max[0].x = App->CL_Vm_Model->vertex_Data[VertCount].x;
		if (App->CL_Vm_Model->vertex_Data[VertCount].y > App->CL_Vm_Model->S_BoundingBox[0]->BB_Max[0].y) App->CL_Vm_Model->S_BoundingBox[0]->BB_Max[0].y = App->CL_Vm_Model->vertex_Data[VertCount].y;
		if (App->CL_Vm_Model->vertex_Data[VertCount].z > App->CL_Vm_Model->S_BoundingBox[0]->BB_Max[0].z)App->CL_Vm_Model->S_BoundingBox[0]->BB_Max[0].z = App->CL_Vm_Model->vertex_Data[VertCount].z;
		VertCount++;
	}
	//	Count++;
	//}

	App->CL_Vm_Model->S_BoundingBox[0]->Size[0].x = (fabs(App->CL_Vm_Model->S_BoundingBox[0]->BB_Max[0].x - App->CL_Vm_Model->S_BoundingBox[0]->BB_Min[0].x));
	App->CL_Vm_Model->S_BoundingBox[0]->Size[0].y = (fabs(App->CL_Vm_Model->S_BoundingBox[0]->BB_Max[0].y - App->CL_Vm_Model->S_BoundingBox[0]->BB_Min[0].y));
	App->CL_Vm_Model->S_BoundingBox[0]->Size[0].z = (fabs(App->CL_Vm_Model->S_BoundingBox[0]->BB_Max[0].z - App->CL_Vm_Model->S_BoundingBox[0]->BB_Min[0].z));

	App->CL_Vm_Model->S_BoundingBox[0]->radius = (App->CL_Vm_Model->S_BoundingBox[0]->Size[0].x>App->CL_Vm_Model->S_BoundingBox[0]->Size[0].z) ? App->CL_Vm_Model->S_BoundingBox[0]->Size[0].z / 2.0f : App->CL_Vm_Model->S_BoundingBox[0]->Size[0].x / 2.0f;

	App->CL_Vm_Model->S_BoundingBox[0]->Centre[0].x = (App->CL_Vm_Model->S_BoundingBox[0]->BB_Min[0].x + App->CL_Vm_Model->S_BoundingBox[0]->BB_Max[0].x) / 2.0f;
	App->CL_Vm_Model->S_BoundingBox[0]->Centre[0].y = (App->CL_Vm_Model->S_BoundingBox[0]->BB_Min[0].y + App->CL_Vm_Model->S_BoundingBox[0]->BB_Max[0].y) / 2.0f;
	App->CL_Vm_Model->S_BoundingBox[0]->Centre[0].z = (App->CL_Vm_Model->S_BoundingBox[0]->BB_Min[0].z + App->CL_Vm_Model->S_BoundingBox[0]->BB_Max[0].z) / 2.0f;

	return 1;
}

// *************************************************************************
// *					GetMotion  ( Terry Bernie ) 					   *
// *************************************************************************
bool VM_Genisis3D::GetMotion(char *mMotionName)
{
	geMotion* Motion = NULL;
	float StartTime = 0;
	float EndTime = 0;

	strcpy(MotionName, mMotionName);

	Motion = geActor_GetMotionByName(ActorDef_Memory, MotionName);
	if (Motion == NULL)
	{
		return 0;
	}

	geMotion_GetTimeExtents(Motion, &StartTime, &EndTime);
	FrameSpeed = EndTime;

	App->CL_Vm_Motions->Current_StartTime = StartTime;
	App->CL_Vm_Motions->Current_EndTime = EndTime;
	return 1;
}

// *************************************************************************
// *					GetDefaultBones Terry Bernie	   			  	   *
// *************************************************************************
bool VM_Genisis3D::GetDefaultBones(void)
{
	const char *BoneName;

	const char *BoneNameQ;
	int pb;
	int BoneCount = 0;
	geXForm3d  A;
	geXForm3d  B;

	BoneCount = geBody_GetBoneCount(ActorDef_Memory->Body);

	int Count = 0;
	while (Count<BoneCount)
	{
		App->CL_Vm_Model->S_Bones[Count] = new Bone_Type;

		geBody_GetBone(ActorDef_Memory->Body, Count, &BoneNameQ, &A, &pb);
		geActor_GetBoneTransform(TestActor, BoneNameQ, &B);

		App->CL_Vm_Model->S_Bones[Count]->Parent = pb;

		App->CL_Vm_Model->S_Bones[Count]->Boneverts.x = B.Translation.X;
		App->CL_Vm_Model->S_Bones[Count]->Boneverts.y = B.Translation.Y;
		App->CL_Vm_Model->S_Bones[Count]->Boneverts.z = B.Translation.Z;

		App->CL_Vm_Model->S_Bones[Count]->TranslationStart.X = B.Translation.X;
		App->CL_Vm_Model->S_Bones[Count]->TranslationStart.Y = B.Translation.Y;
		App->CL_Vm_Model->S_Bones[Count]->TranslationStart.Z = B.Translation.Z;

		BoneName = geStrBlock_GetString(ActorDef_Memory->Body->BoneNames, Count);
		strcpy(App->CL_Vm_Model->S_Bones[Count]->BoneName, BoneName);

		//App->CL_FileView->Add_BoneName(App->CL_Vm_Model->S_Bones[Count]->BoneName, Count);
		Count++;
	}

	if (BoneCount > 0)
	{
		//App->CL_FileView->Set_FolderActive(App->CL_FileView->HT_BonesFolder);
	}
	return 1;
}

// *************************************************************************
// *					GetBoneMoveMent Terry Bernie	   			  	   *
// *************************************************************************
void VM_Genisis3D::GetBoneMoveMent(void)
{
	const char *BoneNameQ;
	int pb;
	int BoneCount = 0;
	geXForm3d  A;
	geXForm3d  B;
	geVec3d Angels;

	BoneCount = geBody_GetBoneCount(ActorDef_Memory->Body);

	int Count = 0;
	while (Count<BoneCount)
	{
		geBody_GetBone(ActorDef_Memory->Body, Count, &BoneNameQ, &A, &pb);
		geActor_GetBoneTransform(TestActor, BoneNameQ, &B);

		geXForm3d_GetEulerAngles(&B, &Angels);

		App->CL_Vm_Model->S_Bones[Count]->Boneverts.x = B.Translation.X;
		App->CL_Vm_Model->S_Bones[Count]->Boneverts.y = B.Translation.Y;
		App->CL_Vm_Model->S_Bones[Count]->Boneverts.z = B.Translation.Z;

		App->CL_Vm_Model->S_Bones[Count]->TranslationStart.X = B.Translation.X;
		App->CL_Vm_Model->S_Bones[Count]->TranslationStart.Y = B.Translation.Y;
		App->CL_Vm_Model->S_Bones[Count]->TranslationStart.Z = B.Translation.Z;

		Count++;
	}
}

// *************************************************************************
// *					SetCounters Terry Bernin		  			 	   *
// *************************************************************************
void VM_Genisis3D::SetCounters(void)
{
	App->CL_Vm_Model->TextureCount = ActorDef_Memory->Body->MaterialCount;
	App->CL_Vm_Model->MotionCount = ActorDef_Memory->MotionCount;
	App->CL_Vm_Model->BoneCount = ActorDef_Memory->Body->BoneCount;

	//App->CL_Vm_Model->VertCount = ActorDef_Memory->Body->XSkinVertexCount;
	//	App->S_Counters[0]->PolygonCount =	 ActorDef_Memory->Body->SkinFaces[GE_BODY_HIGHEST_LOD].FaceCount;
	//	App->S_Counters[0]->UVCount =		 App->S_Counters[0]->PolygonCount*3;
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
	GetUVs();

	//Set_Scene();

	return 1;
}

// *************************************************************************
// *						Animate Terry Bernie	 			  	 	   *
// *************************************************************************
bool VM_Genisis3D::Animate(int Do)
{
	if (Do == 1)
	{
		geMotion *Motion = geActor_GetMotionByName(ActorDef_Memory, MotionName);

		if (m_CurrentPose>FrameSpeed)
		{
			//if (MotionLoop == 1)
			{
				m_CurrentPose = 0;
			}
			/*else
			{
			App->C_Ogre->RenderListener->PlayActive = 0;
			App->TogglePlayBmp();
			return 1;
			}*/
		}

		geActor_SetPose(TestActor, Motion, m_CurrentPose, NULL);

		m_CurrentPose += (geFloat)AnimationSpeed;
	}
	if (Do == 2)
	{
		if (m_CurrentPose>FrameSpeed)
		{
			m_CurrentPose = 0;
		}

		geMotion *Motion = geActor_GetMotionByName(ActorDef_Memory, MotionName);
		geActor_SetPose(TestActor, Motion, m_CurrentPose, NULL);

		m_CurrentPose += (geFloat)AnimationSpeed * 5;
	}

	if (Do == 3)
	{
		if (m_CurrentPose>FrameSpeed)
		{
			m_CurrentPose = 0;
		}

		geMotion *Motion = geActor_GetMotionByName(ActorDef_Memory, MotionName);
		geActor_SetPose(TestActor, Motion, m_CurrentPose, NULL);

		m_CurrentPose -= (geFloat)AnimationSpeed * 5;
	}

	if (Do == 4)
	{
		/*if (m_CurrentPose>FrameSpeed)
		{
		m_CurrentPose = 0;
		}*/

		geMotion *Motion = geActor_GetMotionByName(ActorDef_Memory, MotionName);
		geActor_SetPose(TestActor, Motion, m_CurrentPose, NULL);
	}

	int Count = 0;
	float x;
	float y;
	float z;
	int face1;
	int face2;
	int face3;

	int mVertCount = TestActor->Puppet->BodyInstance->ExportGeometry.SkinVertexCount;
	App->CL_Vm_Model->VerticeCount = mVertCount;
	App->CL_Vm_Model->vertex_Data.resize(mVertCount);

	while (Count < mVertCount)
	{
		x = TestActor->Puppet->BodyInstance->ExportGeometry.SkinVertexArray[Count].SVPoint.X;
		y = TestActor->Puppet->BodyInstance->ExportGeometry.SkinVertexArray[Count].SVPoint.Y;
		z = TestActor->Puppet->BodyInstance->ExportGeometry.SkinVertexArray[Count].SVPoint.Z;

		App->CL_Vm_Model->vertex_Data[Count].x = x;
		App->CL_Vm_Model->vertex_Data[Count].y = y;
		App->CL_Vm_Model->vertex_Data[Count].z = z;

		Count++;
	}

	Count = 0;
	int mNormsCount = TestActor->Puppet->BodyInstance->ExportGeometry.NormalCount;
	App->CL_Vm_Model->NormalsCount = mNormsCount;
	App->CL_Vm_Model->Normal_Data.resize(mNormsCount);

	while (Count < mNormsCount)
	{
		x = TestActor->Puppet->BodyInstance->ExportGeometry.NormalArray[Count].X;
		y = TestActor->Puppet->BodyInstance->ExportGeometry.NormalArray[Count].Y;
		z = TestActor->Puppet->BodyInstance->ExportGeometry.NormalArray[Count].Z;

		App->CL_Vm_Model->Normal_Data[Count].x = x;
		App->CL_Vm_Model->Normal_Data[Count].y = y;
		App->CL_Vm_Model->Normal_Data[Count].z = z;

		Count++;
	}

	Count = 0;
	int mFaceCount = TestActor->Puppet->BodyInstance->BodyTemplate->SkinFaces->FaceCount;
	App->CL_Vm_Model->FaceCount = mFaceCount;

	App->CL_Vm_Model->Face_Data.resize(mFaceCount);
	App->CL_Vm_Model->MatIndex_Data.resize(mFaceCount);

	while (Count < mFaceCount)
	{
		face1 = TestActor->Puppet->BodyInstance->BodyTemplate->SkinFaces[GE_BODY_HIGHEST_LOD].FaceArray[Count].VtxIndex[0];
		face2 = TestActor->Puppet->BodyInstance->BodyTemplate->SkinFaces[GE_BODY_HIGHEST_LOD].FaceArray[Count].VtxIndex[1];
		face3 = TestActor->Puppet->BodyInstance->BodyTemplate->SkinFaces[GE_BODY_HIGHEST_LOD].FaceArray[Count].VtxIndex[2];

		App->CL_Vm_Model->MatIndex_Data[Count] = TestActor->Puppet->BodyInstance->BodyTemplate->SkinFaces[GE_BODY_HIGHEST_LOD].FaceArray[Count].MaterialIndex;

		App->CL_Vm_Model->Face_Data[Count].a = face1;
		App->CL_Vm_Model->Face_Data[Count].b = face2;
		App->CL_Vm_Model->Face_Data[Count].c = face3;

		Count++;
	}

	RenderActor(TestActor->Puppet, TestActor->Pose);

	//                        //App->CL_Actor_Loader->UpDateMeshAnimation();

	//if (App->CL_Vm_Model->Model_Loaded == 1)
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

// *************************************************************************
// *						GetUVs								  	 	   *
// *************************************************************************
bool VM_Genisis3D::GetUVs()
{
	int Count = 0;
	float U = 0;
	float V = 0;
	int mUVsNum = TestActor->Puppet->BodyInstance->ExportGeometry.SkinVertexCount;

	App->CL_Vm_Model->MapCord_Data.resize(mUVsNum);

	while (Count<mUVsNum)
	{
		U = TestActor->Puppet->BodyInstance->ExportGeometry.SkinVertexArray[Count].SVU;
		V = TestActor->Puppet->BodyInstance->ExportGeometry.SkinVertexArray[Count].SVV;

		App->CL_Vm_Model->MapCord_Data[Count].u = U;
		App->CL_Vm_Model->MapCord_Data[Count].v = V;
		App->CL_Vm_Model->MapCord_Data[Count].v = 1 - V;

		Count++;
	}
	return 1;
}


// *************************************************************************
// *						LoadActorTextures							   *
// *************************************************************************
bool VM_Genisis3D::LoadActorTextures(void)
{
	strcpy(TempTextureFile_BMP, App->CL_Vm_Model->Texture_FolderPath);
	strcat(TempTextureFile_BMP, "TextureLoad.bmp");

	strcpy(TempTextureFile_TGA, App->CL_Vm_Model->Texture_FolderPath);
	strcat(TempTextureFile_TGA, "TextureLoad.tga");

	if (App->CL_Vm_Model->TextureCount == 0) { return 0; } // No Textures to processes

	const char *MaterialName;
	int TgaLoaded = 0;
	int BmpLoaded = 0;
	int MatIndex = 0;
	int Count = 0;

	// ----------------------------------------------------------------- Textures used by actor
	SetTexture_Type();			// Collect only textures in actor
	CreateTextureInfo();		// Create Empty Texture Structures
	FillTextureInfo();			// Populate Structures
	//							// ----------------------------------------------------------------- All Textures

	App->CL_Vm_Model->GroupCount = App->CL_Vm_Model->S_Texture[0]->UsedTextureCount;

	while (Count < App->CL_Vm_Model->S_Texture[0]->UsedTextureCount)
	{
		MatIndex = App->CL_Vm_Model->S_TextureInfo[Count]->ActorMaterialIndex;
		MaterialName = geStrBlock_GetString(ActorDef_Memory->Body->MaterialNames, Count);//App->CL_Vm_Model->S_Texture[0]->MatIndex[Count].Index);

		App->CL_Vm_Model->Create_S_MeshGroup(Count);

		App->CL_Vm_Model->S_MeshGroup[Count]->Soil_TextureIndex = Count;
		strcpy(App->CL_Vm_Model->S_MeshGroup[Count]->GroupName, MaterialName);
		strcpy(App->CL_Vm_Model->S_MeshGroup[Count]->Text_FileName, MaterialName);

		//&App->C_RF_Com->Store_bitmap_TextureInfoIndex(Count);

		if (App->CL_Vm_Model->S_TextureInfo[Count]->HasGEBitmap == 1)
		{
			if (App->CL_Vm_Model->S_TextureInfo[Count]->GEHasAlpha == 1)
			{
				App->CL_Vm_Textures->Genesis_WriteTGA(TempTextureFile_TGA, App->CL_Vm_Model->S_TextureInfo[Count]->Bitmap);
				App->CL_Vm_Textures->Soil_Load_Texture(App->CL_Vm_Textures->g_Texture, TempTextureFile_TGA, MatIndex);
				TgaLoaded = 1;// Signal bmp Loaded for delete
			}
			else
			{
				if (App->CL_Vm_Model->S_TextureInfo[Count]->HasGEBitmap == 1)
				{
					App->CL_Vm_Textures->Genesis_WriteToBmp(App->CL_Vm_Model->S_TextureInfo[Count]->Bitmap, TempTextureFile_BMP);

					//App->CL_Textures->TexureToWinPreviewFullPath(Count, TempTextureFile_BMP);

					App->CL_Vm_Textures->Soil_Load_Texture(App->CL_Vm_Textures->g_Texture, TempTextureFile_BMP, MatIndex);
					BmpLoaded = 1;// Signal bmp Loaded for delete
				}
			}
		}

		Count++;
	}

	if (BmpLoaded == 1)
	{
		DeleteFile((LPCTSTR)TempTextureFile_BMP);
	}

	if (TgaLoaded == 1)
	{
		DeleteFile((LPCTSTR)TempTextureFile_TGA);
	}

	////Update_Model_File_View();

	return 1;
}

// *************************************************************************
// *						SetTexture_Type Terry Bernie				   *
// *************************************************************************
bool VM_Genisis3D::SetTexture_Type(void)
{
	const char *MaterialName;
	int MatIndex = -1;
	int OldIndex = -1;
	int UsedCount = 0;
	int Count = 0;
	while (Count < App->CL_Vm_Model->FaceCount)
	{
		MatIndex = ActorDef_Memory->Body->SkinFaces[GE_BODY_HIGHEST_LOD].FaceArray[Count].MaterialIndex;

		if (MatIndex>OldIndex)
		{
			MaterialName = geStrBlock_GetString(ActorDef_Memory->Body->MaterialNames, MatIndex);
			App->CL_Vm_Model->S_Texture[0]->MatIndex[UsedCount].Index = MatIndex;

			strcpy(App->CL_Vm_Model->S_Texture[0]->TextureName[UsedCount].Name, MaterialName);

			UsedCount++;
			OldIndex = MatIndex;
		}
		Count++;
	}

	App->CL_Vm_Model->S_Texture[0]->UsedTextureCount = UsedCount;

	return GE_TRUE;
}
// *************************************************************************
// *					CreateTextureInfo Terry Bernie	   		 	   	   *
// *************************************************************************
void VM_Genisis3D::CreateTextureInfo(void)
{
	int Count = 0;

	while (Count < App->CL_Vm_Model->S_Texture[0]->UsedTextureCount)
	{
		App->CL_Vm_Model->S_TextureInfo[Count] = new GLTextureInfo_Type;
		App->CL_Vm_Model->S_TextureInfo[Count]->Tga = 0;
		App->CL_Vm_Model->S_TextureInfo[Count]->type = 0;

		App->CL_Vm_Model->S_TextureInfo[Count]->GEHasAlpha = 0;

		Count++;
	}
}

// *************************************************************************
// *					FillTextureInfo	Terry Bernie	   		 	   	   *
// *************************************************************************
bool VM_Genisis3D::FillTextureInfo(void)
{
	int Count = 0;
	int Index = 0;
	float R, G, B = 0;
	geBitmap* Bitmap;
	const char *MName;
	geBitmap* Lock;
	geBitmap_Info Info;
	int test = 0;

	ActorDef_Memory = geActor_GetActorDef(TestActor);
	ActorBody_Memory = geActor_GetBody(ActorDef_Memory);

	while (Count < App->CL_Vm_Model->S_Texture[0]->UsedTextureCount)
	{

		strcpy(App->CL_Vm_Model->S_TextureInfo[Count]->MaterialName, App->CL_Vm_Model->S_Texture[0]->TextureName[Count].Name);
		App->CL_Vm_Model->S_TextureInfo[Count]->ActorMaterialIndex = App->CL_Vm_Model->S_Texture[0]->MatIndex[Count].Index;

		Index = App->CL_Vm_Model->S_TextureInfo[Count]->ActorMaterialIndex;

		App->CL_Vm_Model->S_TextureInfo[Count]->HasGEBitmap = 0; // Assume no Genesis Bitmap
		geBody_GetMaterial(ActorBody_Memory, Index, &MName, &Bitmap, &R, &G, &B);
		if (Bitmap)
		{
			App->CL_Vm_Model->S_TextureInfo[Count]->Bitmap = Bitmap;
			App->CL_Vm_Model->S_TextureInfo[Count]->HasGEBitmap = 1;

			geBitmap_LockForReadNative(Bitmap, &Lock, 0, 0);
			geBitmap_GetInfo(Lock, &Info, NULL);

			App->CL_Vm_Model->S_TextureInfo[Count]->GEWitdth = Info.Width;
			App->CL_Vm_Model->S_TextureInfo[Count]->GEHeight = Info.Height;
			App->CL_Vm_Model->S_TextureInfo[Count]->GEFormat = Info.Format;
			App->CL_Vm_Model->S_TextureInfo[Count]->GEHasColorKey = Info.HasColorKey;

			App->CL_Vm_Model->S_TextureInfo[Count]->GEHasAlpha = 0; // Assune no Alpha
			test = geBitmap_HasAlpha(Lock);
			if (test == 1)
			{
				App->CL_Vm_Model->S_TextureInfo[Count]->GEHasAlpha = 1;
			}

			geBitmap_UnLock(Lock);
			geBitmap_RefreshMips(Bitmap);
		}

		App->CL_Vm_Model->S_TextureInfo[Count]->R = R;
		App->CL_Vm_Model->S_TextureInfo[Count]->G = G;
		App->CL_Vm_Model->S_TextureInfo[Count]->B = B;

		Count++;
	}

	return 1;
}
