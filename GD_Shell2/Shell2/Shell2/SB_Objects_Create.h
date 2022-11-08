/*
Copyright (c) 2021 Scene Builder and Equity -- Inflanite Software W.T.Flanigan H.C.Flanigan

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
class SB_Objects_Create
{
public:

	SB_Objects_Create(void);
	~SB_Objects_Create(void);

	bool Add_Objects_From_File(); // From File
	bool Dispatch_MeshViewer();
	void Add_Objects_From_MeshViewer();
	bool Add_New_Object(int Index, bool From_MeshViewer);
	bool Add_New_Sound();
	bool Add_New_Area();
	bool Add_New_Move_Entity();
	bool Add_New_Teleporter();

	void Set_Physics(int Index);

	btBvhTriangleMeshShape* create_Area_Trimesh_New(int Index, Base_Area* Object);

	char DestinationFile[MAX_PATH];
	char SourceFile[MAX_PATH];

protected:

	void Add_Physics_Box(bool Dynamic,int Index);
	void Add_Physics_Sphere(bool Dynamic, int Index);
	void Add_Physics_Capsule(bool Dynamic, int Index);
	void Add_Physics_Cylinder(bool Dynamic, int Index);
	void Add_Physics_Cone(bool Dynamic, int Index);

	btBvhTriangleMeshShape* create_New_Trimesh(int Index);

	bool Create_Sound_Entity(int Index);
	bool Create_Move_Entity(int Index);
	bool Create_TeleportEntity(int Index);
	bool Create_Colectable_Entity(int Index);

	bool First_Area_Start_Project();

	char m_ResourcePath[MAX_PATH];
};

