/*
Copyright (c) 2022 Scene Builder and Equity -- Inflanite Software W.T.Flanigan H.C.Flanigan

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
class SB_Object
{
public:
	SB_Object(void);
	~SB_Object(void);

	void Hide_AllObjects_Except(int Index, bool Show);
	void Delete_Object();
	void Rename_Object(int Index);
	void Clear_Modified_Objects();
	Ogre::Vector3 GetPlacement(int Distance = -6);

	Ogre::Vector3 Get_BoundingBox_World_Centre(int Object_Index);
	float GetMesh_BB_Radius(SceneNode* mNode);

	int GetIndex_By_Name(char* Name);

	void Copy_Object(int Object_Index);

	Ogre::Vector3 GetMesh_BB_Size(SceneNode* mNode);

	bool Show_Physics_Debug;
	bool Show_Mesh_Debug;
	bool Hide_All_Except_Flag;

protected:

};

