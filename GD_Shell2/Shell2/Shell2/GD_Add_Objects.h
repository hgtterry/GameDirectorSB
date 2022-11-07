#pragma once
class GD_Add_Objects
{
public:
	GD_Add_Objects(void);
	~GD_Add_Objects(void);

	bool Add_Object();

	void Add_Stock_Message();

	bool Add_CollectableEntity(int Object_Index);

	bool Add_TeleportEntity(int Object_Index);

	Ogre::Vector3 GetMesh_Center(int Index,SceneNode* mNode);
	bool GetMesh_BB_Data(int SL,Ogre::SceneNode *Node);
	Ogre::Vector3 GetMesh_BB_Size(SceneNode* mNode);
	float GetMesh_BB_Radius(SceneNode* mNode);


protected:

	btBvhTriangleMeshShape* createTrimesh ( Ogre::Entity* ent,int Object_Index );

	void Add_Physics_Static_Box(bool Dynamic,int Object_Index);
	void Add_Physics_Static_Cone(bool Dynamic,int Object_Index);
	void Add_Physics_Static_Sphere(bool Dynamic,int Object_Index);
	void Add_Physics_Static_Capsule(bool Dynamic,int Object_Index);
	void Add_Physics_Static_Cylinder(bool Dynamic,int Object_Index);


	bool Add_SoundEntity(int Object_Index);
	bool Add_MessageEntity(int Object_Index);
	bool Add_MoveEntity(int Object_Index);

	btTransform Set_Physics_PosRot(int Object_Index);
	void Set_Physics_Scale(int Object_Index);
};

