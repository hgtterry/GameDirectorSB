#pragma once
class SB_Objects_FFile
{
public:
	SB_Objects_FFile(void);
	~SB_Objects_FFile(void);

	bool Add_Objects_FromFile(); // From File
	bool Add_Object_FFile(int Object_Index);
	bool Add_SoundEntity_FFile(int Object_Index);
	bool Add_MessageEntity_FFile(int Object_Index);
	bool Add_MoveEntity_FFile(int Object_Index);
	bool Add_CollectableEntity_FFile(int Object_Index);
	bool Add_TeleportEntity_FFile(int Object_Index);

	void Add_Physics_Static_Box_FFile(bool Dynamic, int Object_Index);
	void Add_Physics_Static_Sphere_FFile(bool Dynamic, int Object_Index);
	void Add_Physics_Static_Capsule_FFile(bool Dynamic, int Object_Index);
	void Add_Physics_Static_Cylinder_FFile(bool Dynamic, int Object_Index);
	void Add_Physics_Static_Cone_FFile(bool Dynamic, int Object_Index);
};

