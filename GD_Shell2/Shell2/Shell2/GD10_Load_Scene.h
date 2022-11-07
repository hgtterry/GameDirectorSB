#pragma once
class GD10_Load_Scene
{
public:
	GD10_Load_Scene();
	~GD10_Load_Scene();

	bool Load_Config_File();

	bool OpenScene(bool AskForScene);

	bool LoadCameraDetails();
	bool LoadOptionsDetails40();
	bool Load_Player_Locations40();
	bool Load_Stock_Sounds40();

	float LVolume;
	float LPan;
	float LData0;
	float LData1;
	bool LIs3d;
	bool LLoop;

	char Scene_FileName[255];
	char Scene_Path_FileName[2048];
	char SubFolder[1024];

protected:



	bool gdLoader_LoadGDScene_New();

	void Load_Scene40();
	bool Load_Player40();
	bool Load_Environment40();
	bool Load_Objects40();
	void Load_MoveEntity40(int Count);
	bool Populate_Level40();

	char ReadBuf[256];
	FILE *LoadScene;
	FILE *LoadObjects;
};

