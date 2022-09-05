#pragma once
class SB_Objects_Create
{
public:

	SB_Objects_Create(void);
	~SB_Objects_Create(void);

	bool Dispatcher_New();
	void Update_MV_Details();

	char m_ResourcePath[MAX_PATH];

protected:

	bool Add_New_Object();
	void Add_New_Physics_Static_Box(bool Dynamic);
};

