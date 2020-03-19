#pragma once
class GD19_Load_Scene
{
public:
	GD19_Load_Scene(void);
	~GD19_Load_Scene(void);

	bool OpenScene(bool AskForScene);

	bool LoadCameraDetails();
	bool LoadOptionsDetails40();
	bool Load_Player_Locations40();

	float LVolume;
	float LPan;
	float LData0;
	float LData1;
	bool LIs3d;
	bool LLoop;
	bool File_Is_Loading;

protected:



	bool gdLoader_LoadGDScene_New();

	void Load_Scene40();
	bool Load_Player40();
	bool Load_Environment40();
	bool Load_Objects40();
	void Load_MoveEntity40(int Count);
	bool Populate_Level40();

	bool Load_Stock_Sounds40();

	char SubFolder[1024];

	char ReadBuf[256];
	FILE *LoadScene;
	FILE *LoadObjects;
};

