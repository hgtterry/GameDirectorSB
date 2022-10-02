#pragma once
class SB_Objects_Create
{
public:

	SB_Objects_Create(void);
	~SB_Objects_Create(void);

	bool Add_Objects_From_File(); // From File
	bool Dispatcher_New();
	void Add_Objects_From_MeshViewer();
	bool Add_New_Object(int Index);
	bool Add_New_Message();
	bool Add_New_Sound();
	bool Add_New_Area();

	btBvhTriangleMeshShape* create_Area_Trimesh_New(int Index, Base_Area* Object);

	char DestinationFile[MAX_PATH];
	char SourceFile[MAX_PATH];

protected:

	void Set_Physics(int Index);

	void Add_Physics_Box(bool Dynamic,int Index);
	void Add_Physics_Sphere(bool Dynamic, int Index);
	void Add_Physics_Capsule(bool Dynamic, int Index);
	void Add_Physics_Cylinder(bool Dynamic, int Index);
	void Add_Physics_Cone(bool Dynamic, int Index);

	bool Add_Message_Entity(int Index);
	bool Add_Sound_Entity(int Index);

	bool First_Area_Start_Project();

	char m_ResourcePath[MAX_PATH];
};

