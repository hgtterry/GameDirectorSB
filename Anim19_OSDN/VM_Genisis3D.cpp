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
#include "resource.h"
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

	Frame_End_Time = (float)1.15;;
	m_CurrentPose = 0;
	AnimationSpeed = (float)0.005;

	NewBody = nullptr;

	Actor_Position.X = 0;
	Actor_Position.Y = 0;
	Actor_Position.Z = 0;

	Actor_Rotation.X = 0;
	Actor_Rotation.Y = 0;
	Actor_Rotation.Z = 0;

	Actor_Scale.X = 0;
	Actor_Scale.Y = 0;
	Actor_Scale.Z = 0;

	ParentBone = -1;

	PosX = 0;
	PosY = 0;
	PosZ = 0;

	RotX = 0;
	RotY = 0;
	RotZ = 0;
}


VM_Genisis3D::~VM_Genisis3D()
{

}

// *************************************************************************
// *						Reset_Class Terry Bernie				 	   *
// *************************************************************************
void VM_Genisis3D::Reset_Class(void)
{
	ActorDef_Memory = nullptr;
	ActorBody_Memory = nullptr;
	TestActor = nullptr;

	MotionName[0] = 0;

	Frame_End_Time = (float)1.15;;
	m_CurrentPose = NULL;
	AnimationSpeed = (float)0.005;

	Actor_Position.X = 0;
	Actor_Position.Y = 0;
	Actor_Position.Z = 0;

	Actor_Rotation.X = 0;
	Actor_Rotation.Y = 0;
	Actor_Rotation.Z = 0;

	Actor_Scale.X = 0;
	Actor_Scale.Y = 0;
	Actor_Scale.Z = 0;

	PosX = 0;
	PosY = 0;
	PosZ = 0;

	RotX = 0;
	RotY = 0;
	RotZ = 0;

}
// *************************************************************************
// *						LoadActor Terry Bernie					 	   *
// *************************************************************************
bool VM_Genisis3D::Import_LoadActor(void)
{

	bool Test = Import_AddActor(App->CL_Vm_Model->Path_FileName);
	if (Test == 0)
	{
		return 0;
	}

	SetCounters();

	GetDefaultBones();

	if (App->CL_Vm_Model->MotionCount > 0)
	{
		Get_MotionNames();
		strcpy(MotionName, App->CL_Vm_Model->MotionNames_Data[0].Name);
	}

	Get_TextureNames();

	
	Import_LoadActorTextures();

	GetBoundingBoxModel_Create();

	//App->CL_Vm_Model->HasMesh = 1;

	return 1;
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
// *				GetBoundingBoxModel_Update Terry Bernie				   *
// *************************************************************************
bool VM_Genisis3D::GetBoundingBoxModel_Update(void)
{

	App->CL_Vm_Model->S_BoundingBox[0]->BB_Min[0].x = App->CL_Vm_Model->vertex_Data[0].x;
	App->CL_Vm_Model->S_BoundingBox[0]->BB_Min[0].y = App->CL_Vm_Model->vertex_Data[0].y;
	App->CL_Vm_Model->S_BoundingBox[0]->BB_Min[0].z = App->CL_Vm_Model->vertex_Data[0].z;

	App->CL_Vm_Model->S_BoundingBox[0]->BB_Max[0].x = App->CL_Vm_Model->vertex_Data[0].x;
	App->CL_Vm_Model->S_BoundingBox[0]->BB_Max[0].y = App->CL_Vm_Model->vertex_Data[0].y;
	App->CL_Vm_Model->S_BoundingBox[0]->BB_Max[0].z = App->CL_Vm_Model->vertex_Data[0].z;

	int Count = 0;
	int VertCount = 0;

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
	Frame_End_Time = EndTime;

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
bool VM_Genisis3D::Import_AddActor(char* FileName)
{
	if (TestActor)
	{
		TestActor = nullptr;
	}

	geVFile* HFile = nullptr;


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
			App->Say("Cant Create ActorDef_Memory");
			geVFile_Close(HFile);
			return 0;
		}
	}
	else
	{
		App->Say("Cant Create HFile");
		return 0;
	}

	geVFile_Close(HFile);

	RenderActor(TestActor->Puppet, TestActor->Pose);

	Animate(0);
	GetUVs();

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

		if (m_CurrentPose>Frame_End_Time)
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
		if (m_CurrentPose>Frame_End_Time)
		{
			m_CurrentPose = 0;
		}

		geMotion *Motion = geActor_GetMotionByName(ActorDef_Memory, MotionName);
		geActor_SetPose(TestActor, Motion, m_CurrentPose, NULL);

		m_CurrentPose += (geFloat)AnimationSpeed * 5;
	}

	if (Do == 3)
	{
		if (m_CurrentPose>Frame_End_Time)
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

	if (App->CL_Vm_Model->Model_Loaded == 1)
	{
		GetBoundingBoxModel_Update();
	}

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

	App->CL_Vm_Model->UVCount = TestActor->Puppet->BodyInstance->ExportGeometry.SkinVertexCount;

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
bool VM_Genisis3D::Import_LoadActorTextures(void)
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
		MaterialName = App->CL_Vm_Model->S_TextureInfo[Count]->MaterialName; // Now Correct

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

					App->CL_Vm_Textures->TexureToWinPreviewFullPath(Count, TempTextureFile_BMP);

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

// *************************************************************************
// *					Export_As_Actor Terry Berine					   *
// *************************************************************************
void VM_Genisis3D::Export_As_Actor(void)
{
	
	App->CL_Vm_FileIO->Create_Output_Folder("_Actor");  // Create Main Folder for Output

	char Temp[1024];
	strcpy(Temp, App->CL_Vm_FileIO->OutputFolder);
	strcat(Temp, App->CL_Vm_Model->JustName);
	strcat(Temp, ".act");

	if (App->CL_Vm_Model->Model_Type == LoadedFile_Actor)
	{
		Export_Actor_To_Actor(Temp, App->CL_Vm_Genesis3D->ActorDef_Memory);
	}
	else
	{
		App->CL_Vm_Model->Convert_To_GlobalMesh();
		MakeOBJActor(Temp, 0);
	}
}

// *************************************************************************
// *							MakeOBJActor						 	   *
// *************************************************************************
bool VM_Genisis3D::MakeOBJActor(char* Filename, bool Decompile)
{
	NewBody = geBody_Create();

	geVFile *VF = NULL;
	geActor_Def *ActorDef = NULL;

	ActorDef = geActor_DefCreate();
	geActor_SetBody(ActorDef, NewBody);

	AddBone();
	AddFaces_Assimp();

	int Count = 0;
	int NumMatrials = App->CL_Vm_Model->GroupCount;

	while (Count < NumMatrials)
	{

		char buf[255];
		sprintf(buf, "%s%i", "Dummy", Count);

		strcpy(CTextureName, buf);//App->S_MeshGroup[Count]->GroupName);

		ReadTextures(Count);
		Count++;
	}

	char F_Name[255];
	strcpy(F_Name, Filename);

	VF = geVFile_OpenNewSystem(NULL, GE_VFILE_TYPE_DOS, F_Name, NULL, GE_VFILE_OPEN_CREATE);

	if (VF)
	{
		geActor_DefWriteToFile(ActorDef, VF);
		geVFile_Close(VF);

		/*if (Decompile == 1)
		{
			char Temp[1024];
			strcpy(Temp, App->CL_Vm_FileIO->OutputFolder);
			strcat(Temp, App->CL_Vm_Model->JustName);
			strcat(Temp, ".bdy");
			Decompile_Body(Temp, ActorDef);

			App->CL_FileIO->Create_Texture_Folder();
			Decompile_Textures(ActorDef);
		}*/

		geActor_DefDestroy(&ActorDef); // cleans up all motions and body*/
		return 1;
	}

	geVFile_Close(VF);
	geActor_DefDestroy(&ActorDef); // cleans up all motions and body*/
	App->Say("Cant create Actor");
	return 1;
}

// *************************************************************************
// *						ReadTextures Terry Bernie  		  		 	   *
// *************************************************************************
bool VM_Genisis3D::ReadTextures(int Count)
{
	//AddDummyTexture();

	HBITMAP HbmpTemp;

	HbmpTemp = App->CL_Vm_Model->S_MeshGroup[Count]->Base_Bitmap;

	App->CL_Vm_Textures->HBITMAP_TO_BmpFile(HbmpTemp, "Etemp.bmp", "");
	strcpy(TextureFileName, "Etemp.bmp");
	AddTextureToActor();

	remove("Etemp.bmp");

	return 1;
}

// *************************************************************************
// *					AddTextureToActor Terry Bernie					   *
// *************************************************************************
bool VM_Genisis3D::AddTextureToActor(void)
{
	geVFile *VF;
	geBitmap *Bmp;
	bool LetTextureGo = 0;

	int Index = 0;
	VF = geVFile_OpenNewSystem(NULL, GE_VFILE_TYPE_DOS, TextureFileName, NULL, GE_VFILE_OPEN_READONLY);
	if (VF == NULL)
	{
		AddDummyTexture();
		return 0;
	}
	else
	{
		Bmp = geBitmap_CreateFromFile(VF);
		geVFile_Close(VF);
		if (Bmp == NULL)
		{
			App->Say("Cant Read Texture ");
			return GE_FALSE;
		}
		if (geBitmap_SetColorKey(Bmp, GE_TRUE, 255, GE_TRUE) == GE_FALSE)
		{
			App->Say("Cant Set Colors");
			return GE_FALSE;
		}
		//-------------------------------------- Test for Dup Name	

		float R, G, B = 0;
		geBitmap* Bitmap;
		const char *MaterialName;

		char Temp[256];
		int Loop = 0;
		int BodyMatCount = geBody_GetMaterialCount(NewBody);
		while (Loop<BodyMatCount)
		{
			char bufnum[256];
			geBody_GetMaterial(NewBody, Loop, &MaterialName, &Bitmap, &R, &G, &B);
			strcpy(Temp, MaterialName);

			int test = strcmp(Temp, CTextureName);
			if (test == 0)
			{
				_itoa(Loop, bufnum, 10);
				strcat(CTextureName, bufnum);
				break;
			}
			Loop++;
		}
		//----------------------------------------------------------------	

		if (LetTextureGo == 0)
		{
			int W, H, TwoPower;
			W = geBitmap_Width(Bmp);
			H = geBitmap_Height(Bmp);

			for (TwoPower = 1; TwoPower <= 2048; TwoPower *= 2)
			{
				if (TwoPower == W)
					break;
			}
			if (TwoPower > 2048)
			{
				App->Say("You need to resize your texture in a paint program");
				AddDummyTexture();
				return 0;
			}

			for (TwoPower = 1; TwoPower <= 2048; TwoPower *= 2)
			{
				if (TwoPower == H)
					break;
			}
			if (TwoPower > 2048)
			{
				App->Say("You need to resize your texture in a paint program");
				AddDummyTexture();
				return 0;
			}

		}
		if (geBody_AddMaterial(NewBody, CTextureName, Bmp, 255.0f, 255.0f, 255.0f, &Index) == GE_FALSE)
		{
			App->Say("Could Not Add Texture To Body ");
			return GE_FALSE;
		}
	}

	return 1;
}

// *************************************************************************
// *					AddDummyTexture Terry Bernie	   			 	   *
// *************************************************************************
bool VM_Genisis3D::AddDummyTexture()
{
	geVFile *VF;
	geBitmap *Bmp = NULL;

	HbitmapToSaveBmp();

	VF = geVFile_OpenNewSystem(NULL, GE_VFILE_TYPE_DOS, "Etemp.bmp", NULL, GE_VFILE_OPEN_READONLY);
	if (VF == NULL)
	{
		App->Say("Cant Create Dummy Texture");
	}
	else
	{
		Bmp = geBitmap_CreateFromFile(VF);
		geVFile_Close(VF);
		if (Bmp == NULL)
		{
			App->Say("Cant Read Texture ");
			return GE_FALSE;
		}
		if (geBitmap_SetColorKey(Bmp, GE_TRUE, 255, GE_TRUE) == GE_FALSE)
		{
			App->Say("Cant Set Colors");
			return GE_FALSE;
		}
	}
	int Index = 0;

	if (geBody_AddMaterial(NewBody, CTextureName, Bmp, 255, 255, 255, &Index) == GE_FALSE)
	{

		App->Say("Could Not Add Texture To Body ");
		App->CL_Vm_Textures->RemoveFile("Etemp.bmp", "");
		return GE_FALSE;
	}

	App->CL_Vm_Textures->RemoveFile("Etemp.bmp", "");
	return 1;
}

// *************************************************************************
// *						HbitmapToSaveBmp Terry Bernie   	 	 	   *
// *************************************************************************
bool VM_Genisis3D::HbitmapToSaveBmp(void) // Old Routine needs new one Terry 24/04/13
{
	HBITMAP hbmpTemp;
	hbmpTemp = LoadBitmap(App->hInst, MAKEINTRESOURCE(IDB_DUMMY));

	App->CL_Vm_Textures->HBITMAP_TO_BmpFile(hbmpTemp, "Etemp.bmp", "");
	return 1;
}

// *************************************************************************
// *							AddFaces_Assimp		  		  		 	   *
// *************************************************************************
bool VM_Genisis3D::AddFaces_Assimp(void)
{
	int Count = 0;
	int FaceCount = App->CL_Vm_Model->FaceCount;

	const geVec3d* vertices[3];

	geVec3d Fvert[3];
	geVec3d normals[3];

	const char* bonename;
	geActor * NewActor1;

	int Add = 0;

	normals[0].X = 1;
	normals[0].Y = 1;
	normals[0].Z = 1;

	normals[1].X = 1;
	normals[1].Y = 1;
	normals[1].Z = 1;

	normals[2].X = 1;
	normals[2].Y = 1;
	normals[2].Z = 1;

	float tu1 = 1;
	float tv1 = 0;

	float tu2 = 1;
	float tv2 = 1;

	float tu3 = 0;
	float tv3 = 0;

	int BoneIndex = 0;
	int MaterialIndex = 0;

	geActor_Def *ActorDef = NULL;
	ActorDef = geActor_DefCreate();
	geActor_SetBody(ActorDef, NewBody);
	NewActor1 = geActor_Create(ActorDef);

	App->CL_Vm_ImGui->Set_ProgressCount(App->CL_Vm_Model->FaceCount);
	App->CL_Vm_ImGui->Start_ProgressBar();
	

	while (Count < App->CL_Vm_Model->FaceCount)
	{

		Fvert[0].X = App->CL_Vm_Model->vertex_Data[App->CL_Vm_Model->Face_Data[Count].a].x;
		Fvert[0].Y = App->CL_Vm_Model->vertex_Data[App->CL_Vm_Model->Face_Data[Count].a].y;
		Fvert[0].Z = App->CL_Vm_Model->vertex_Data[App->CL_Vm_Model->Face_Data[Count].a].z;

		Fvert[1].X = App->CL_Vm_Model->vertex_Data[App->CL_Vm_Model->Face_Data[Count].b].x;
		Fvert[1].Y = App->CL_Vm_Model->vertex_Data[App->CL_Vm_Model->Face_Data[Count].b].y;
		Fvert[1].Z = App->CL_Vm_Model->vertex_Data[App->CL_Vm_Model->Face_Data[Count].b].z;

		Fvert[2].X = App->CL_Vm_Model->vertex_Data[App->CL_Vm_Model->Face_Data[Count].c].x;
		Fvert[2].Y = App->CL_Vm_Model->vertex_Data[App->CL_Vm_Model->Face_Data[Count].c].y;
		Fvert[2].Z = App->CL_Vm_Model->vertex_Data[App->CL_Vm_Model->Face_Data[Count].c].z;

		vertices[0] = &Fvert[0];
		vertices[1] = &Fvert[1];
		vertices[2] = &Fvert[2];

		MaterialIndex = App->CL_Vm_Model->MatIndex_Data[Count];

		float tu1 = App->CL_Vm_Model->MapCord_Data[App->CL_Vm_Model->Face_Data[Count].a].u;
		float tv1 = 1 - App->CL_Vm_Model->MapCord_Data[App->CL_Vm_Model->Face_Data[Count].a].v;

		float tu2 = App->CL_Vm_Model->MapCord_Data[App->CL_Vm_Model->Face_Data[Count].b].u;
		float tv2 = 1 - App->CL_Vm_Model->MapCord_Data[App->CL_Vm_Model->Face_Data[Count].b].v;

		float tu3 = App->CL_Vm_Model->MapCord_Data[App->CL_Vm_Model->Face_Data[Count].c].u;
		float tv3 = 1 - App->CL_Vm_Model->MapCord_Data[App->CL_Vm_Model->Face_Data[Count].c].v;

		normals[0].X = App->CL_Vm_Model->Normal_Data[App->CL_Vm_Model->Face_Data[Count].a].x;
		normals[0].Y = App->CL_Vm_Model->Normal_Data[App->CL_Vm_Model->Face_Data[Count].a].y;
		normals[0].Z = App->CL_Vm_Model->Normal_Data[App->CL_Vm_Model->Face_Data[Count].a].z;

		normals[1].X = App->CL_Vm_Model->Normal_Data[App->CL_Vm_Model->Face_Data[Count].b].x;
		normals[1].Y = App->CL_Vm_Model->Normal_Data[App->CL_Vm_Model->Face_Data[Count].b].y;
		normals[1].Z = App->CL_Vm_Model->Normal_Data[App->CL_Vm_Model->Face_Data[Count].b].z;

		normals[2].X = App->CL_Vm_Model->Normal_Data[App->CL_Vm_Model->Face_Data[Count].c].x;
		normals[2].Y = App->CL_Vm_Model->Normal_Data[App->CL_Vm_Model->Face_Data[Count].c].y;
		normals[2].Z = App->CL_Vm_Model->Normal_Data[App->CL_Vm_Model->Face_Data[Count].c].z;

		geVec3d angle;
		geXForm3d B;
		int pb = 0;
		for (int j = 0; j<3; j++)
		{
			geBody_GetBone(NewBody, 0, &bonename, &B, &pb);

			geActor_GetBoneTransform(NewActor1, bonename, &B);

			angle.X = normals[j].X;
			angle.Y = normals[j].Y;
			angle.Z = normals[j].Z;

			VectorIRotate(&B, &angle, &angle);

			normals[j].X = angle.X;
			normals[j].Y = angle.Y;
			normals[j].Z = angle.Z;
		}

		if (AddFace_N(NewBody,
			vertices[0], &normals[0], tu1, tv1, BoneIndex,
			vertices[1], &normals[1], tu2, tv2, BoneIndex,
			vertices[2], &normals[2], tu3, tv3, BoneIndex,
			MaterialIndex) == GE_FALSE)
		{
			App->Say("Could not add face for mesh");
			App->Say_Int(Count);
			return 0;
		}

		App->CL_Vm_ImGui->Nudge();
		Count++;
	}

	App->CL_Vm_ImGui->Stop_ProgressBar();
	return 1;
}

// *************************************************************************
// *					VectorIRotate Terry Bernie  			 	 	   *
// *************************************************************************
bool VM_Genisis3D::VectorIRotate(const geXForm3d* matrix, const geVec3d* v, geVec3d* result)
{
	geVec3d angle;

	angle = *v;

	result->X = angle.X*matrix->AX + angle.Y*matrix->BX + angle.Z*matrix->CX;

	result->Y = angle.X*matrix->AY + angle.Y*matrix->BY + angle.Z*matrix->CY;

	result->Z = angle.X*matrix->AZ + angle.Y*matrix->BZ + angle.Z*matrix->CZ;

	return 1;
}


// *************************************************************************
// *						AddBone Terry Bernie					 	   *
// *************************************************************************
bool VM_Genisis3D::AddBone(void)
{
	int Index = 0;
	geXForm3d matrix;
	geQuaternion gQ;
	geVec3d v;

	PosX = 0;
	PosY = 0;
	PosZ = 0;

	RotX = 0;
	RotY = 0;
	RotZ = 0;

	ParentBone = -1;

	strcpy(BoneName, "joint1");
	MakeBoneMatrix();

	matrix = BoneMatrix;

	v = matrix.Translation;

	geQuaternion_FromMatrix(&matrix, &gQ);
	gQ.W = -gQ.W;

	geQuaternion_ToMatrix(&gQ, &matrix);
	matrix.Translation = v;

	geXForm3d_Orthonormalize(&matrix);

	if (ParentBone == -1) { ParentBone = GE_BODY_NO_PARENT_BONE; }

	// attach the bone
	if (geBody_AddBone(NewBody, ParentBone, BoneName, &matrix, &Index) == GE_FALSE)
	{
		return 0;
	}

	return 1;
}

// *************************************************************************
// *						MakeBoneMatrix Terry Bernie  			 	   *
// *************************************************************************
bool VM_Genisis3D::MakeBoneMatrix(void)
{
	Vec3[0] = RotX * 180 / (float)Q_PI;
	Vec3[1] = RotY * 180 / (float)Q_PI;
	Vec3[2] = RotZ * 180 / (float)Q_PI;

	AngleMatrix(Vec3);

	TempMatrix_t[0][3] = PosX;
	TempMatrix_t[1][3] = PosY;
	TempMatrix_t[2][3] = PosZ;

	BoneMatrix.AX = TempMatrix_t[0][0];
	BoneMatrix.AY = TempMatrix_t[1][0];
	BoneMatrix.AZ = TempMatrix_t[2][0];

	BoneMatrix.BX = TempMatrix_t[0][1];
	BoneMatrix.BY = TempMatrix_t[1][1];
	BoneMatrix.BZ = TempMatrix_t[2][1];

	BoneMatrix.CX = TempMatrix_t[0][2];
	BoneMatrix.CY = TempMatrix_t[1][2];
	BoneMatrix.CZ = TempMatrix_t[2][2];

	BoneMatrix.Translation.X = TempMatrix_t[0][3];
	BoneMatrix.Translation.Y = TempMatrix_t[1][3];
	BoneMatrix.Translation.Z = TempMatrix_t[2][3];

	return 1;
}
// *************************************************************************
// *						AngleMatrix Terry Bernie				 	   *
// *************************************************************************
bool VM_Genisis3D::AngleMatrix(const TVec3 angles)
{
	float		angle;
	float		sr, sp, sy, cr, cp, cy;

	angle = angles[2] * (Q_PI * 2 / 360);
	sy = sin(angle);
	cy = cos(angle);
	angle = angles[1] * (Q_PI * 2 / 360);
	sp = sin(angle);
	cp = cos(angle);
	angle = angles[0] * (Q_PI * 2 / 360);
	sr = sin(angle);
	cr = cos(angle);

	// matrix = (Z * Y) * X
	TempMatrix_t[0][0] = cp*cy;
	TempMatrix_t[1][0] = cp*sy;
	TempMatrix_t[2][0] = -sp;
	TempMatrix_t[0][1] = sr*sp*cy + cr*-sy;
	TempMatrix_t[1][1] = sr*sp*sy + cr*cy;
	TempMatrix_t[2][1] = sr*cp;
	TempMatrix_t[0][2] = (cr*sp*cy + -sr*-sy);
	TempMatrix_t[1][2] = (cr*sp*sy + -sr*cy);
	TempMatrix_t[2][2] = cr*cp;
	TempMatrix_t[0][3] = 0.0;
	TempMatrix_t[1][3] = 0.0;
	TempMatrix_t[2][3] = 0.0;
	return 1;
}


// *************************************************************************
// *						Actor_To_Actor Terry Bernie			  	 	   *
// *************************************************************************
bool VM_Genisis3D::Export_Actor_To_Actor(char* FileName, geActor_Def *mActorDef)
{
	Export_SaveMatric();
	Export_SortMesh();

	geVFile *VF = NULL;

	VF = geVFile_OpenNewSystem(NULL, GE_VFILE_TYPE_DOS, FileName, NULL, GE_VFILE_OPEN_CREATE);
	if (VF)
	{
		geActor_DefWriteToFile(mActorDef, VF);
	}
	else
	{
		return 0;
	}

	geVFile_Close(VF);

	return 1;
}

// *************************************************************************
// *							Export_SaveMatric	    				   *
// *************************************************************************
bool VM_Genisis3D::Export_SaveMatric()
{
	int pb;
	const char *BoneNameQ;
	geXForm3d  A;
	int Count = 0;
	int BoneCount = ActorDef_Memory->Body->BoneCount;

	while (Count<BoneCount)
	{
		geBody_GetBone(ActorDef_Memory->Body, Count, &BoneNameQ, &A, &pb);
		if (pb<0)
		{
			Export_SaveMatric_Bones(Count);
		}
		Count++;
	}

	return 1;
}

// *************************************************************************
// *						Export_SaveMatric_Bones	    				   *
// *************************************************************************
bool VM_Genisis3D::Export_SaveMatric_Bones(int Index)
{
	int pb;
	const char *BoneNameQ;

	geXForm3d  A;
	geXForm3d  B;
	geBody_GetBone(ActorDef_Memory->Body, Index, &BoneNameQ, &A, &pb);
	geActor_GetBoneTransform(TestActor, BoneNameQ, &B);

	ActorDef_Memory->Body->BoneArray[Index].AttachmentMatrix.AX = B.AX;
	ActorDef_Memory->Body->BoneArray[Index].AttachmentMatrix.AY = B.AY;
	ActorDef_Memory->Body->BoneArray[Index].AttachmentMatrix.AZ = B.AZ;

	ActorDef_Memory->Body->BoneArray[Index].AttachmentMatrix.BX = B.BX;
	ActorDef_Memory->Body->BoneArray[Index].AttachmentMatrix.BY = B.BY;
	ActorDef_Memory->Body->BoneArray[Index].AttachmentMatrix.BZ = B.BZ;

	ActorDef_Memory->Body->BoneArray[Index].AttachmentMatrix.CX = B.CX;
	ActorDef_Memory->Body->BoneArray[Index].AttachmentMatrix.CY = B.CY;
	ActorDef_Memory->Body->BoneArray[Index].AttachmentMatrix.CZ = B.CZ;

	ActorDef_Memory->Body->BoneArray[Index].AttachmentMatrix.Translation.X = B.Translation.X;
	ActorDef_Memory->Body->BoneArray[Index].AttachmentMatrix.Translation.Y = B.Translation.Y;
	ActorDef_Memory->Body->BoneArray[Index].AttachmentMatrix.Translation.Z = B.Translation.Z;

	return 1;
}

// *************************************************************************
// *						Export_SortMesh					  		 	   *
// *************************************************************************
bool VM_Genisis3D::Export_SortMesh()
{
	int Count = 0;
	float x;
	float y;
	float z;
	int BoneID = 0;
	const char* bonename;
	geXForm3d B;
	int pb = 0;

	int VertNum = TestActor->Puppet->BodyInstance->ExportGeometry.SkinVertexCount;
	while (Count < VertNum)
	{

		BoneID = TestActor->Puppet->BodyInstance->ExportGeometry.SkinVertexArray[Count].ReferenceBoneIndex;

		x = TestActor->Puppet->BodyInstance->ExportGeometry.SkinVertexArray[Count].SVPoint.X;
		y = TestActor->Puppet->BodyInstance->ExportGeometry.SkinVertexArray[Count].SVPoint.Y;
		z = TestActor->Puppet->BodyInstance->ExportGeometry.SkinVertexArray[Count].SVPoint.Z;

		App->CL_Vm_Model->vertex_Data[Count].x = x;
		App->CL_Vm_Model->vertex_Data[Count].y = y;
		App->CL_Vm_Model->vertex_Data[Count].z = z;

		geBody_GetBone(ActorBody_Memory, BoneID, &bonename, &B, &pb);

		geActor_GetBoneTransform(TestActor, bonename, &B); // Here

		geVec3d angle;

		angle.X = App->CL_Vm_Model->vertex_Data[Count].x - B.Translation.X;
		angle.Y = App->CL_Vm_Model->vertex_Data[Count].y - B.Translation.Y;
		angle.Z = App->CL_Vm_Model->vertex_Data[Count].z - B.Translation.Z;

		Export_VectorIRotate(&B, &angle, &angle);

		ActorDef_Memory->Body->XSkinVertexArray[Count].XPoint.X = angle.X;
		ActorDef_Memory->Body->XSkinVertexArray[Count].XPoint.Y = angle.Y;
		ActorDef_Memory->Body->XSkinVertexArray[Count].XPoint.Z = angle.Z;

		Count++;
	}

	return 1;
}

// *************************************************************************
// *					Export_VectorIRotate Terry Bernie  		 	 	   *
// *************************************************************************
bool VM_Genisis3D::Export_VectorIRotate(const geXForm3d* matrix, const geVec3d* v, geVec3d* result)
{
	geVec3d angle;

	angle = *v;

	result->X = angle.X*matrix->AX + angle.Y*matrix->BX + angle.Z*matrix->CX;

	result->Y = angle.X*matrix->AY + angle.Y*matrix->BY + angle.Z*matrix->CY;

	result->Z = angle.X*matrix->AZ + angle.Y*matrix->BZ + angle.Z*matrix->CZ;

	return 1;
}


//**************************************************************************
// *						ScaleActor 									   *
// *************************************************************************
bool VM_Genisis3D::ScaleActor(float SX, float SY, float SZ)
{
	gePose *P;
	geVec3d Scale;
	Scale.X = SX;
	Scale.Y = SY;
	Scale.Z = SZ;

	int i;
	gePose_Joint *J;

	P = TestActor->Pose;
	P->Scale = Scale;

	for (i = 0, J = &(P->JointArray[0]); i<P->JointCount; i++, J++)
	{
		//AnimateProgressBar();
		J->AttachmentTransform.Translation.X = J->UnscaledAttachmentTranslation.X * Scale.X;
		J->AttachmentTransform.Translation.Y = J->UnscaledAttachmentTranslation.Y * Scale.Y;
		J->AttachmentTransform.Translation.Z = J->UnscaledAttachmentTranslation.Z * Scale.Z;

		ActorDef_Memory->Body->BoneArray[i].AttachmentMatrix.Translation.X = J->AttachmentTransform.Translation.X;
		ActorDef_Memory->Body->BoneArray[i].AttachmentMatrix.Translation.Y = J->AttachmentTransform.Translation.Y;
		ActorDef_Memory->Body->BoneArray[i].AttachmentMatrix.Translation.Z = J->AttachmentTransform.Translation.Z;

		J->Touched = GE_TRUE;

		/*J->UnscaledAttachmentTranslation.X = J->UnscaledAttachmentTranslation.X * Scale.X;
		J->UnscaledAttachmentTranslation.Y = J->UnscaledAttachmentTranslation.Y * Scale.Y;
		J->UnscaledAttachmentTranslation.Z = J->UnscaledAttachmentTranslation.Z * Scale.Z;*/
	}
	P->Touched = GE_TRUE;

	Animate(0);
	GetBoneMoveMent();

	Animate(0);
	GetBoneMoveMent();

	return 1;
}
// *************************************************************************
// *								MoveActor		 					   *
// *************************************************************************
bool VM_Genisis3D::MoveActor(void)
{
	if (App->CL_Vm_Model->Model_Loaded == 1)
	{
		geXForm3d XForm;
		geVec3d Angles;

		Angles.X = App->Cl_Utilities->DegreesToRadians(Actor_Rotation.X);
		Angles.Y = App->Cl_Utilities->DegreesToRadians(Actor_Rotation.Y);
		Angles.Z = App->Cl_Utilities->DegreesToRadians(Actor_Rotation.Z);

		geXForm3d_SetIdentity(&XForm);

		geXForm3d_RotateX(&XForm, Angles.X);
		geXForm3d_RotateY(&XForm, Angles.Y);
		geXForm3d_RotateZ(&XForm, Angles.Z);

		geXForm3d_Translate(&XForm, Actor_Position.X, Actor_Position.Y, Actor_Position.Z);

		geActor_ClearPose(TestActor, &XForm);

		RenderActor(TestActor->Puppet, TestActor->Pose);
		GetBoneMoveMent();
		Animate(0);
	}

	return 1;
}

// *************************************************************************
// *							Genesis_ChangeTexture	 			  	   *
// *************************************************************************
bool VM_Genisis3D::ChangeTexture(char* TextureFile)
{
	geVFile *VF;
	geBitmap *Bmp = NULL;

	if (_stricmp(TextureFile + strlen(TextureFile) - 4, ".bmp") != 0)
	{
		App->Say("Not A BMP");
		return GE_FALSE;
	}

	VF = geVFile_OpenNewSystem(NULL, GE_VFILE_TYPE_DOS, TextureFile, NULL, GE_VFILE_OPEN_READONLY);
	if (VF == NULL)
	{
		
		App->Say("Can't CreateFile");
		return GE_FALSE;
	}

	Bmp = geBitmap_CreateFromFile(VF);

	geVFile_Close(VF);

	if (Bmp == NULL)
	{
		App->Say("Can't Create Bitmap");
		return GE_FALSE;
	}
	if (geBitmap_SetColorKey(Bmp, GE_TRUE, 255, GE_TRUE) == GE_FALSE)
	{
		App->Say("Can't Set Colour Key");
		return GE_FALSE;
	}

	int textureID = 0;

	geBody_SetMaterial(ActorDef_Memory->Body, textureID, Bmp, 255, 255, 255);

	return 1;
}

// *************************************************************************
// *					DefaultPose ( Terry Bernie )  			 	 	   *
// *************************************************************************
bool VM_Genisis3D::DefaultPose(void)
{
	geVec3d Angles;

	Angles.X = App->Cl_Utilities->DegreesToRadians(Actor_Rotation.X);
	Angles.Y = App->Cl_Utilities->DegreesToRadians(Actor_Rotation.Y);
	Angles.Z = App->Cl_Utilities->DegreesToRadians(Actor_Rotation.Z);

	geXForm3d MedXForm;
	geXForm3d_SetIdentity(&MedXForm);

	geXForm3d_RotateX(&MedXForm, Angles.X);
	geXForm3d_RotateY(&MedXForm, Angles.Y);
	geXForm3d_RotateZ(&MedXForm, Angles.Z);

	geXForm3d_Translate(&MedXForm, Actor_Position.X, Actor_Position.Y, Actor_Position.Z);

	geActor_ClearPose(TestActor, &MedXForm);// &MedXForm

	RenderActor(TestActor->Puppet, TestActor->Pose);
	Animate(0);

	return 1;
}


#define GE_BODY_HIGHEST_LOD_MASK	( 1 << GE_BODY_HIGHEST_LOD )

// *************************************************************************
// *						AddFace_N ( Terry Bernie )  			  	   *
// *************************************************************************
bool VM_Genisis3D::AddFace_N(geBody *B,
	const geVec3d *Vertex1, const geVec3d *Normal1,
	geFloat U1, geFloat V1, int BoneIndex1,
	const geVec3d *Vertex2, const geVec3d *Normal2,
	geFloat U2, geFloat V2, int BoneIndex2,
	const geVec3d *Vertex3, const geVec3d *Normal3,
	geFloat U3, geFloat V3, int BoneIndex3,
	int MaterialIndex)
{
	geBody_Triangle F;

	assert(B != NULL);
	assert(Vertex1 != NULL);
	assert(Normal1 != NULL);
	assert(geBody_IsValid(B) != GE_FALSE);

	assert(BoneIndex1 >= 0);
	assert(BoneIndex1 < B->BoneCount);

	assert(Vertex2 != NULL);
	assert(Normal2 != NULL);
	assert(BoneIndex2 >= 0);
	assert(BoneIndex2 < B->BoneCount);

	assert(Vertex3 != NULL);
	assert(Normal3 != NULL);
	assert(BoneIndex3 >= 0);
	assert(BoneIndex3 < B->BoneCount);

	assert(MaterialIndex >= 0);
	assert(MaterialIndex < B->MaterialCount);

	if (AddSkinVertex_N(B, Vertex1, U1, V1, (geBody_Index)BoneIndex1, &(F.VtxIndex[0])) == GE_FALSE)
	{	// error already recorded
		return GE_FALSE;
	}
	if (AddSkinVertex_N(B, Vertex2, U2, V2, (geBody_Index)BoneIndex2, &(F.VtxIndex[1])) == GE_FALSE)
	{	// error already recorded
		return GE_FALSE;
	}
	if (AddSkinVertex_N(B, Vertex3, U3, V3, (geBody_Index)BoneIndex3, &(F.VtxIndex[2])) == GE_FALSE)
	{	// error already recorded
		return GE_FALSE;
	}

	if (AddNormal_N(B, Normal1, (geBody_Index)BoneIndex1, &(F.NormalIndex[0])) == GE_FALSE)
	{	// error already recorded
		return GE_FALSE;
	}
	if (AddNormal_N(B, Normal2, (geBody_Index)BoneIndex2, &(F.NormalIndex[1])) == GE_FALSE)
	{	// error already recorded
		return GE_FALSE;
	}
	if (AddNormal_N(B, Normal3, (geBody_Index)BoneIndex3, &(F.NormalIndex[2])) == GE_FALSE)
	{	// error already recorded
		return GE_FALSE;
	}

	F.MaterialIndex = (geBody_Index)MaterialIndex;
	if (AddToFaces_N(B, &F, GE_BODY_HIGHEST_LOD) == GE_FALSE)
	{	// error already recorded
		return GE_FALSE;
	}

	SortSkinVertices_N(B);

	return GE_TRUE;

}

// *************************************************************************
// *					SortSkinVertices_N ( Terry Bernie ) 		  	   *
// *************************************************************************
bool VM_Genisis3D::SortSkinVertices_N(geBody *B)
{
	int i, j;
	int Count;
	geBoolean AnyChanges = GE_FALSE;
	assert(B != NULL);

	Count = B->XSkinVertexCount;
	for (i = 0; i<Count; i++)
	{
		for (j = 0; j<Count - 1; j++)
		{
			if (B->XSkinVertexArray[j].BoneIndex > B->XSkinVertexArray[j + 1].BoneIndex)
			{
				geBody_XSkinVertex Swap;

				Swap = B->XSkinVertexArray[j];
				B->XSkinVertexArray[j] = B->XSkinVertexArray[j + 1];
				B->XSkinVertexArray[j + 1] = Swap;
				SwapVertexIndices_N(B, (geBody_Index)j, (geBody_Index)(j + 1));
				AnyChanges = GE_TRUE;
			}
		}
		if (AnyChanges != GE_TRUE)
		{
			break;
		}
		AnyChanges = GE_FALSE;
	}
	return GE_TRUE;
}

// *************************************************************************
// *				SwapVertexIndices_N ( Terry Bernie )			  	   *
// *************************************************************************
bool VM_Genisis3D::SwapVertexIndices_N(geBody *B, geBody_Index Index1, geBody_Index Index2)
// zips through all triangles, and swaps index1 and index2.
{
	int i, j, lod;
	geBody_Index Count;
	geBody_Triangle *T;

	assert(B != NULL);
	for (lod = 0; lod< GE_BODY_NUMBER_OF_LOD; lod++)
	{
		Count = B->SkinFaces[lod].FaceCount;
		for (i = 0, T = B->SkinFaces[lod].FaceArray;
			i<Count;
			i++, T++)
		{
			for (j = 0; j<3; j++)
			{
				if (T->VtxIndex[j] == Index1)
				{
					T->VtxIndex[j] = Index2;
				}
				else
				{
					if (T->VtxIndex[j] == Index2)
					{
						T->VtxIndex[j] = Index1;
					}
				}
			}
		}
	}
	return GE_TRUE;
}

#define MAX(aa,bb)   ( (aa)>(bb)?(aa):(bb) )
#define MIN(aa,bb)   ( (aa)<(bb)?(aa):(bb) )

// *************************************************************************
// *					AddSkinVertex_N ( Terry Bernie ) 			  	   *
// *************************************************************************
bool VM_Genisis3D::AddSkinVertex_N(geBody *B,
	const geVec3d *Vertex,
	geFloat U, geFloat V,
	geBody_Index BoneIndex,
	geBody_Index *Index)
{
	geBody_Bone *Bone;
	geBody_XSkinVertex *SV;
	geBody_XSkinVertex NewSV;
	int i;
	assert(B != NULL);
	assert(Vertex != NULL);
	assert(Index != NULL);
	assert(geBody_IsValid(B) != GE_FALSE);

	assert(B->XSkinVertexCount + 1 > 0);

	NewSV.XPoint = *Vertex;
	NewSV.XU = U;
	NewSV.XV = V;
	NewSV.LevelOfDetailMask = GE_BODY_HIGHEST_LOD_MASK;
	NewSV.BoneIndex = BoneIndex;

	assert(B->BoneCount > BoneIndex);
	Bone = &(B->BoneArray[BoneIndex]);


	// see if new Vertex is alreay in XSkinVertexArray
	for (i = 0; i<B->XSkinVertexCount; i++)
	{
		SV = &(B->XSkinVertexArray[i]);
		if (SV->BoneIndex == BoneIndex)
		{
			if (XSkinVertexCompare_N(SV, &NewSV) == GE_TRUE)
			{
				*Index = (geBody_Index)i;
				return GE_TRUE;
			}
		}
	}
	// new Vertex needs to be added to XSkinVertexArray
	SV = GE_RAM_REALLOC_ARRAY(B->XSkinVertexArray,
		geBody_XSkinVertex, (B->XSkinVertexCount + 1));
	if (SV == NULL)
	{
		//geErrorLog_Add(ERR_BODY_ENOMEM, NULL);
		App->Say("Cant Create XSkinVertexArray");
		
		return GE_FALSE;
	}
	B->XSkinVertexArray = SV;

	B->XSkinVertexArray[B->XSkinVertexCount] = NewSV;
	*Index = B->XSkinVertexCount;

	Bone->BoundingBoxMin.X = MIN(Bone->BoundingBoxMin.X, NewSV.XPoint.X);
	Bone->BoundingBoxMin.Y = MIN(Bone->BoundingBoxMin.Y, NewSV.XPoint.Y);
	Bone->BoundingBoxMin.Z = MIN(Bone->BoundingBoxMin.Z, NewSV.XPoint.Z);
	Bone->BoundingBoxMax.X = MAX(Bone->BoundingBoxMax.X, NewSV.XPoint.X);
	Bone->BoundingBoxMax.Y = MAX(Bone->BoundingBoxMax.Y, NewSV.XPoint.Y);
	Bone->BoundingBoxMax.Z = MAX(Bone->BoundingBoxMax.Z, NewSV.XPoint.Z);

	B->XSkinVertexCount++;
	return GE_TRUE;
}

#define GE_BODY_TOLERANCE (0.001f)


// *************************************************************************
// *					XSkinVertexCompare_N ( Terry Bernie ) 		 	   *
// *************************************************************************
bool VM_Genisis3D::XSkinVertexCompare_N(
	const geBody_XSkinVertex *SV1,
	const geBody_XSkinVertex *SV2)
{
	assert(SV1 != NULL);
	assert(SV2 != NULL);
	if (geVec3d_Compare(&(SV1->XPoint), &(SV2->XPoint),
		GE_BODY_TOLERANCE) == GE_FALSE)
	{
		return GE_FALSE;
	}
	if (geVec3d_Compare(&(SV1->XPoint), &(SV2->XPoint),
		GE_BODY_TOLERANCE) == GE_FALSE)
	{
		return GE_FALSE;
	}
	if (fabs(SV1->XU - SV2->XU) > GE_BODY_TOLERANCE)
	{
		return GE_FALSE;
	}
	if (fabs(SV1->XV - SV2->XV) > GE_BODY_TOLERANCE)
	{
		return GE_FALSE;
	}
	return GE_TRUE;
}


// *************************************************************************
// *						AddNormal_N ( Terry Bernie ) 			  	   *
// *************************************************************************
bool VM_Genisis3D::AddNormal_N(geBody *B,
	const geVec3d *Normal,
	geBody_Index BoneIndex,
	geBody_Index *Index)
{
	geBody_Normal *NewNormalArray;
	geBody_Normal *N;
	geVec3d NNorm;
	int i;

	assert(B != NULL);
	assert(Normal != NULL);
	assert(Index != NULL);
	assert(geBody_IsValid(B) != GE_FALSE);

	assert(B->SkinNormalCount + 1 > 0);
	NNorm = *Normal;
	geVec3d_Normalize(&NNorm);
	// see if new normal is alreay in SkinNormalArray
	for (i = 0, N = B->SkinNormalArray; i<B->SkinNormalCount; i++, N++)
	{
		if (N->BoneIndex == BoneIndex)
		{
			if (geVec3d_Compare(&(N->Normal), &NNorm, GE_BODY_TOLERANCE) == GE_TRUE)
			{
				*Index = (geBody_Index)i;
				return GE_TRUE;
			}
		}
	}

	//  new normal needs to be added to SkinNormalArray
	NewNormalArray = GE_RAM_REALLOC_ARRAY(B->SkinNormalArray,
		geBody_Normal, (B->SkinNormalCount + 1));
	if (NewNormalArray == NULL)
	{
		//geErrorLog_Add(ERR_BODY_ENOMEM, NULL);
		App->Say("Cant Create NewNormalArray");
		return GE_FALSE;
	}
	B->SkinNormalArray = NewNormalArray;
	B->SkinNormalArray[B->SkinNormalCount].Normal = NNorm;
	B->SkinNormalArray[B->SkinNormalCount].BoneIndex = BoneIndex;
	B->SkinNormalArray[B->SkinNormalCount].LevelOfDetailMask = GE_BODY_HIGHEST_LOD_MASK;
	*Index = B->SkinNormalCount;
	B->SkinNormalCount++;
	return GE_TRUE;
}

// *************************************************************************
// *					AddToFaces_N ( Terry Bernie ) 				 	   *
// *************************************************************************
bool VM_Genisis3D::AddToFaces_N(geBody *B, geBody_Triangle *F, int DetailLevel)
{
	geBody_Triangle *NewFaceArray;
	geBody_TriangleList *FL;

	assert(B != NULL);
	assert(F != NULL);
	assert(DetailLevel >= 0);
	assert(DetailLevel < GE_BODY_NUMBER_OF_LOD);
	assert(geBody_IsValid(B) != GE_FALSE);

	FL = &(B->SkinFaces[DetailLevel]);

	assert(F->MaterialIndex >= 0);
	assert(F->MaterialIndex < B->MaterialCount);

	NewFaceArray = GE_RAM_REALLOC_ARRAY(FL->FaceArray,
		geBody_Triangle, (FL->FaceCount + 1));
	if (NewFaceArray == NULL)
	{
		//geErrorLog_Add(ERR_BODY_ENOMEM, NULL);
		App->Say("Cant Create NewFaceArray");
		return GE_FALSE;
	}

	FL->FaceArray = NewFaceArray;

	{
		int i;
		// insertion sort new face into FaceArray keyed on MaterialIndex
		geBody_Index MaterialIndex = F->MaterialIndex;
		for (i = FL->FaceCount; i >= 1; i--)
		{
			if (FL->FaceArray[i - 1].MaterialIndex <= MaterialIndex)
				break;
			FL->FaceArray[i] = FL->FaceArray[i - 1];
		}

		FL->FaceArray[i] = *F;
	}
	FL->FaceCount++;

	return GE_TRUE;
}


