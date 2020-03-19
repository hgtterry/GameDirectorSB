#pragma once
class GD19_Object_Properties
{
public:
	GD19_Object_Properties(void);
	~GD19_Object_Properties(void);

	void Start_GD_Properties(void);

	void Update_Properties_Sound(void);
	void Update_Properties_Mesh(void);
	void Update_Properties_Physics(void);
	void Update_Properties_Player_Physics(void);
	void Update_Properties_Player(void);
	void Update_Properties_Move(void);

	void Set_DataView(void);

	int LastCellSelected;
	int Selected_Object_Index;

	bool ToggleObjectDebug;
	bool Object_Selection;
	bool Physics_Selection;
	bool Is_Player;

	int Edit_Type;
	int Usage_Type;

protected:

	static LRESULT CALLBACK GD_Properties_Proc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);
};

