#pragma once
class VM_Motions
{
public:
	VM_Motions();
	~VM_Motions();

	void Play_SelectedMotion(void);
	void Stop_SelectedMotion(void);


	void Populate_Combo(void);


	float Current_StartTime;
	float Current_EndTime;
};

