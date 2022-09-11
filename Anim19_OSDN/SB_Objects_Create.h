#pragma once
class SB_Objects_Create
{
public:

	SB_Objects_Create(void);
	~SB_Objects_Create(void);

	bool Dispatcher_New();
	void Update_MV_Details();
	bool Add_New_Object(int Index);

	

protected:

	void Add_New_Physics_Static_Box(bool Dynamic,int Index);

	char m_ResourcePath[MAX_PATH];
};

