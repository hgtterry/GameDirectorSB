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

#pragma once

#include "Gen_Structures.h"
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

class SB_Genesis3D
{
public:
	SB_Genesis3D();
	~SB_Genesis3D();

	void LoadActor(void);
	bool GetMotion(char *mMotionName);
	bool Animate(int Do);
	void GetBoneMoveMent(void);

	geActor_Def* ActorDef_Memory;

	float m_CurrentPose;

	char MotionName[255];

protected:

	bool AddActor(char* FileName);
	void SetCounters(void);
	bool GetDefaultBones(void);
	bool LoadActorTextures(void);

	bool BuildActor(geActor *Actor);

	gePuppet *CreatePuppet(geVFile *TextureFS, const geBody *B);
	geBodyInst* CreateGeometry(const geBody *B);
	bool RenderActor(const gePuppet *P, const gePose *Joints);

	geBodyInst_Geometry* GetGeometry(
		const geBodyInst *BI,
		const geVec3d *ScaleVector,
		const geXFArray *BoneTransformArray,
		int LevelOfDetail);

	geBodyInst_Geometry* TGetGeometryPrep(geBodyInst *BI, int LevelOfDetail);

	void TPostScale(const geXForm3d *M, const geVec3d *S, geXForm3d *Scaled);

	bool Set_BondingBox_Model(bool Create);
	
	bool GetUVs();

	bool SetTexture_Type(void);
	void CreateTextureInfo(void);
	bool FillTextureInfo(void);

	bool Update_Model_File_View(void);

	bool FileView_AddMotions(void);
	

	geBody* ActorBody_Memory;
	geActor * TestActor;

	float FrameSpeed;
	float AnimationSpeed;

	char TempTextureFile_BMP[MAX_PATH];
	char TempTextureFile_TGA[MAX_PATH];
};

