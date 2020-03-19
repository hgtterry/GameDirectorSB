#pragma once
class GD19_Save_Scene
{
public:
	GD19_Save_Scene(void);
	~GD19_Save_Scene(void);

	bool SaveGDScene_40(bool AskForFile);
	bool Create_NewScene();

	bool Write_Player_Locations_New();

	char New_Scene_File[1024];
	char New_Scene_Path_File[1024];
	char mLevel_Directory[1024];

protected:

	//  New 210619
	bool WritePlayerSetup_New();
	bool WriteEnvironment_New();
	bool WriteObjects_New();
	bool WriteStock_New();
	bool WriteOptions_New();

	bool Write_NewScene();

	bool Write_Stock_Sounds_New();

	char SceneVersion[16];

	char SubFolder[1024];

	FILE *WriteScene;
};

