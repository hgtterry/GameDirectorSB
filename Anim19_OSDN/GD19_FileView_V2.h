#pragma once
class GD19_FileView_V2
{
public:
	GD19_FileView_V2();
	~GD19_FileView_V2();

	void ImGui_FileView2(void);

	bool Add_Player_Name(char* File);
	bool Add_Area_Name(char* File);
	bool Add_ObjectName(char* File);
	bool Add_SoundName(char* File);
	bool Add_MessageName(char* File);
	bool Add_MoveEntities(char* File);
	bool Add_Collectable_Name(char* File);
	bool Add_Teleporter_Name(char* File);

	int GetJustIndex_ByName(char* Name);
	
	bool Select_ObjectFV(int Index);

	void PopUp_AddObject();
	void PopUp_Rename(int Selected_Object);
	
	bool OpenObjects;
	bool SelectObject;
	bool RightMouseDown;
	int Chosen_Object_Index;

protected:

	void Update_Properties_Objects(char* Name);
	void Update_Properties_Sounds(char* Name);
	void Update_Properties_Messages(char* Name);
	void Update_Properties_MoveEntities(char* Name);
	void Update_Properties_Collectables(char* Name);
	void Update_Properties_Teleporters(char* Name);
	void Update_Properties_Areas(char* Name);
	void Update_Properties_Players(char* Name);

	int Object_Names_Count;
	std::vector<std::string> Object_Names_Vec;

	int Sound_Names_Count;
	std::vector<std::string> Sound_Names_Vec;

	int Message_Names_Count;
	std::vector<std::string> Message_Names_Vec;

	int MoveEntities_Names_Count;
	std::vector<std::string> MoveEntities_Names_Vec;

	int Collectables_Names_Count;
	std::vector<std::string> Collectables_Names_Vec;

	int Teleporters_Names_Count;
	std::vector<std::string> Teleporters_Names_Vec;

	int Areas_Names_Count;
	std::vector<std::string> Areas_Names_Vec;

	int Players_Names_Count;
	std::vector<std::string> Players_Names_Vec;

	char Selected_Object_Name[255];
	char Selected_Sound_Name[255];
	char Selected_Message_Name[255];
	char Selected_MoveEntities_Name[255];
	char Selected_Collectables_Name[255];
	char Selected_Teleporters_Name[255];
	char Selected_Areas_Name[255];
	char Selected_Players_Name[255];

	bool Block;

};

