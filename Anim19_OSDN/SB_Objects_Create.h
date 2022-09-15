#pragma once
class SB_Objects_Create
{
public:

	SB_Objects_Create(void);
	~SB_Objects_Create(void);

	bool Add_Objects_From_File(); // From File
	bool Dispatcher_New();
	void Update_MV_Details();
	bool Add_New_Object(int Index);

	

protected:

	void Add_Physics_Box(bool Dynamic,int Index);
	void Add_Physics_Sphere(bool Dynamic, int Index);
	void Add_Physics_Capsule(bool Dynamic, int Index);
	void Add_Physics_Cylinder(bool Dynamic, int Index);
	void Add_Physics_Cone(bool Dynamic, int Index);

	char m_ResourcePath[MAX_PATH];
};

