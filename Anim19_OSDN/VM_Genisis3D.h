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

#pragma once

#include "Genesis.h"
#include "ram.h"
#include "strblock.h"
#include "Puppet.h"

#include "body.h"
#include "quatern.h"
#include "ram.h"
#include "strblock.h"
#include "vph.h"
#include "mkbody.h"
#include "bitmap.h"

#define	Q_PI	3.14159265358979323846

typedef float   TVec3[3];

class VM_Genisis3D
{
public:
	VM_Genisis3D();
	~VM_Genisis3D();

	void Reset_Class(void);

	bool Import_LoadActor(void);

	bool GetMotion(char *mMotionName);

	void GetBoneMoveMent(void);
	bool Animate(int Do);

	bool GetBoundingBoxModel_Update(void);

	void Export_As_Actor(void);

	bool MoveActor(void);
	bool ScaleActor(float SX, float SY, float SZ);

	bool ChangeTexture(char* TextureFile);
	bool DefaultPose(void);

	bool AddFace_N(geBody *B,
		const geVec3d *Vertex1, const geVec3d *Normal1,
		geFloat U1, geFloat V1, int BoneIndex1,
		const geVec3d *Vertex2, const geVec3d *Normal2,
		geFloat U2, geFloat V2, int BoneIndex2,
		const geVec3d *Vertex3, const geVec3d *Normal3,
		geFloat U3, geFloat V3, int BoneIndex3,
		int MaterialIndex);

	bool AddSkinVertex_N(geBody *B,
		const geVec3d *Vertex,
		geFloat U, geFloat V,
		geBody_Index BoneIndex,
		geBody_Index *Index);

	bool AddNormal_N(geBody *B,
		const geVec3d *Normal,
		geBody_Index BoneIndex,
		geBody_Index *Index);

	bool AddToFaces_N(geBody *B, geBody_Triangle *F, int DetailLevel);

	bool SortSkinVertices_N(geBody *B);

	bool SwapVertexIndices_N(geBody *B, geBody_Index Index1, geBody_Index Index2);

	bool XSkinVertexCompare_N(
		const geBody_XSkinVertex *SV1,
		const geBody_XSkinVertex *SV2);

	char MotionName[255];
	float m_CurrentPose;
	float AnimationSpeed;
	float Frame_End_Time;

	geActor_Def* ActorDef_Memory;
	geBody* ActorBody_Memory;
	geActor * TestActor;

	geVec3d Actor_Position;
	geVec3d Actor_Rotation;
	geVec3d Actor_Rotation_Old;

	geVec3d Actor_Scale;

protected:

	bool Import_AddActor(char* FileName);
	bool BuildActor(geActor *Actor);
	gePuppet* CreatePuppet(geVFile *TextureFS, const geBody *B);
	geBodyInst* CreateGeometry(const geBody *B);

	bool RenderActor(const gePuppet *P, const gePose *Joints);

	geBodyInst_Geometry *GetGeometry(
		const geBodyInst *BI,
		const geVec3d *ScaleVector,
		const geXFArray *BoneTransformArray,
		int LevelOfDetail);

	geBodyInst_Geometry* TGetGeometryPrep(geBodyInst *BI, int LevelOfDetail);
	void TPostScale(const geXForm3d *M, const geVec3d *S, geXForm3d *Scaled);

	bool GetUVs();

	void SetCounters(void);
	bool GetDefaultBones(void);
	void Get_MotionNames(void);
	void Get_TextureNames(void);

	bool Import_LoadActorTextures(void);
	bool SetTexture_Type(void);
	void CreateTextureInfo(void);
	bool FillTextureInfo(void);

	bool Export_Actor_To_Actor(char* FileName, geActor_Def *mActorDef);
	bool Export_SaveMatric();
	bool Export_SaveMatric_Bones(int Index);
	bool Export_SortMesh();
	bool Export_VectorIRotate(const geXForm3d* matrix, const geVec3d* v, geVec3d* result);

	bool GetBoundingBoxModel_Create(void);

	// ---------------------------------------------------- Export Routines
	bool MakeOBJActor(char* Filename, bool Decompile);
	bool AddBone(void);
	bool MakeBoneMatrix(void);
	bool AngleMatrix(const TVec3 angles);
	bool AddFaces_Assimp(void);
	bool VectorIRotate(const geXForm3d* matrix, const geVec3d* v, geVec3d* result);
	bool ReadTextures(int Count);
	bool AddTextureToActor(void);
	bool AddDummyTexture();
	bool HbitmapToSaveBmp(void);

	geBody* NewBody;

	int ParentBone;
	float PosX;
	float PosY;
	float PosZ;

	float RotX;
	float RotY;
	float RotZ;
	geXForm3d BoneMatrix;
	float TempMatrix_t[3][4];
	TVec3 Vec3;
	char CTextureName[255];
	char TextureFileName[1024];
	char BoneName[255];

	//------------------------------------------------

	char TempTextureFile_BMP[1024];
	char TempTextureFile_TGA[1024];

};

