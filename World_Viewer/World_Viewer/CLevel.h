#pragma once

//#include "BrushTemplate.h"

typedef struct tag_Level Level;


#define NUM_VIEWS (4)

struct tag_Level
{
	BrushList* Brushes;
	//CEntityArray* Entities;
	char* WadPath;
	char* HeadersDir;
	// changed QD Actors
	char* ActorsDir;
	geBoolean ShowActors;
	char* PawnIniPath;
	// end change
	//EntTypeNameList* EntTypeNames;
	GroupListType* Groups;
	SizeInfo* WadSizeInfos;
	CWadFile* WadFile;
	//EntityTable* pEntityDefs;

	ModelInfo_Type	ModelInfo;

	SkyFaceTexture SkyFaces[6];
	geVec3d SkyRotationAxis;
	geFloat SkyRotationSpeed;
	geFloat	SkyTextureScale;

	// level edit settings
	//CompileParamsType CompileParams;
	int GroupVisSetting;
	//EntityViewList* pEntityView;

	GridInfo GridSettings;
	geBoolean BspRebuildFlag;
	ViewStateInfo ViewInfo[NUM_VIEWS];

	BrushTemplate_Arch ArchTemplate;
	BrushTemplate_Box	BoxTemplate;
	BrushTemplate_Cone	ConeTemplate;
	BrushTemplate_Cylinder CylinderTemplate;
	BrushTemplate_Spheroid	SpheroidTemplate;
	BrushTemplate_Staircase StaircaseTemplate;

	geVec3d TemplatePos;

	float DrawScale;		// default draw scale
	float LightmapScale;	// default lightmap scale
};

class CLevel
{
public:
	CLevel();
	~CLevel();

	Level* Level_CreateFromFile(const char* FileName);
	Level* Level_Create(const char* pWadName, const char* HeadersDir, const char* ActorsDir, const char* PawnIni);

};

