#pragma once
class EQ15_Physics
{
public:
	EQ15_Physics();
	~EQ15_Physics();

	bool Start_Physics_Pannel();
	
	void Enable_Physics(void);

	HWND PhysicsPannel_Hwnd;

protected:

	static LRESULT CALLBACK Start_Physics_Proc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);

	void Update_Model(void);

};

