#pragma once
class GD19_Objects_Com
{
public:
	GD19_Objects_Com(void);
	~GD19_Objects_Com(void);

	Ogre::Vector3 Centre_of_Trimesh(int Object_Index);
	bool GetMesh_BB_Data(int SL, Ogre::SceneNode* Node);
	Ogre::Vector3 GetMesh_BB_Size(SceneNode* mNode);
	float GetMesh_BB_Radius(SceneNode* mNode);
	btTransform Set_Physics_PosRot(int Object_Index);
	void Set_Physics_Scale(int Object_Index);

	bool Copy_Object();
	bool Paste_Object();

	bool Pre_Paste();
	bool Post_Paste();

	int CopyObject_Index;
};

