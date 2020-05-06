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

#include "Ogre.h"

class VM_Render : public RenderQueueListener
{
public:
	VM_Render(void);
	~VM_Render(void);

	void Reset_Class(void);

	float RX;
	float RZ;

	float Hair_1PosX;
	float Hair_1PosY;
	float Hair_1PosZ;

	float Hair_1RotX;
	float Hair_1RotY;
	float Hair_1RotZ;
	//int SelectedJointIndex;

	bool ShowTextured;
	bool ShowFaces;
	bool ShowBones;
	bool ShowPoints;
	bool ShowNormals;
	bool ShowBoundingBox;
	bool PlayActive;
	bool Light_Activated;
	bool ShowOnlySubMesh;
	bool Show_HideGroup;
	bool Show_Crosshair;

	void TestLight(void);

protected:

	virtual void renderQueueStarted(Ogre::uint8 queueGroupId, const String& invocation, 
		bool& skipThisInvocation);

	virtual void renderQueueEnded(Ogre::uint8 queueGroupId, const String& invocation, 
		bool& repeatThisInvocation);

	void PreRender();
	void PostRender();
	void Render_Loop();
	void Translate(void);

	bool Assimp_Render_Textures(void);
	bool Assimp_Textured_Parts(int Count);

	bool Assimp_Render_Points(void);
	bool Render_As_Points_Parts(int Count);

	bool Assimp_Render_Faces(void);
	bool Assimp_Face_Parts(int Count);

	void Assimp_Render_Normals(void);
	void Render_As_Normals_Parts(int Count);

	bool As_RenderBones();

	void Render_BoundingBoxModel(void);

	bool RenderPoints(void);
	bool RenderMeshOnly(void);

	bool RF_Render_All_Groups();
	bool RF_Render_Just_Group();
	void RF_Render_Normals(void);

	void RenderCrossHair(void);

};

