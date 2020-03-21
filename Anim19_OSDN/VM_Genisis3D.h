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

class VM_Genisis3D
{
public:
	VM_Genisis3D();
	~VM_Genisis3D();

	void LoadActor(void);

	char MotionName[255];
	float m_CurrentPose;
	float AnimationSpeed;
	float FrameSpeed;

protected:

	bool AddActor(char* FileName);
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

	bool Animate(int Do);

	bool GetUVs();

	geActor_Def* ActorDef_Memory;
	geBody* ActorBody_Memory;
	geActor * TestActor;
};

