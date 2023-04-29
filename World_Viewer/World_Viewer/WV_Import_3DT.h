#pragma once

#include "brush.h"
//#include "level.h"

typedef struct SizeInfoTag
{
	long	TexWidth, TexHeight;
	long	ScreenWidth, ScreenHeight;
	uint8* TexData, * ScreenData;
	uint32* ZData;
} SizeInfo;

typedef struct tag_Level Level;

struct tag_Level
{
	BrushList* Brushes;
	//CEntityArray* Entities;
	char* WadPath;
	char* HeadersDir;
	
	char* ActorsDir;
	geBoolean ShowActors;
	char* PawnIniPath;
	
	//EntTypeNameList* EntTypeNames;
	//GroupListType* Groups;
	SizeInfo* WadSizeInfos;
	CWadFile* WadFile;
	//EntityTable* pEntityDefs;

	//ModelInfo_Type	ModelInfo;

	//SkyFaceTexture SkyFaces[6];
	//geVec3d SkyRotationAxis;
	//geFloat SkyRotationSpeed;
	//geFloat	SkyTextureScale;

	// level edit settings
	//CompileParamsType CompileParams;
	int GroupVisSetting;
	//EntityViewList* pEntityView;

	//GridInfo GridSettings;
	geBoolean BspRebuildFlag;
	//ViewStateInfo ViewInfo[NUM_VIEWS];

	//BrushTemplate_Arch ArchTemplate;
	//BrushTemplate_Box	BoxTemplate;
	//BrushTemplate_Cone	ConeTemplate;
	//BrushTemplate_Cylinder CylinderTemplate;
	//BrushTemplate_Spheroid	SpheroidTemplate;
	//BrushTemplate_Staircase StaircaseTemplate;

	geVec3d TemplatePos;

	float DrawScale;		// default draw scale
	float LightmapScale;	// default lightmap scale
};

class WV_Import_3DT
{
public:
	WV_Import_3DT();
	~WV_Import_3DT();

	bool Load(const char* FileName);

	Level* Level_CreateFromFile(const char* FileName); //, const char** ErrMsg, const char* DefaultHeadersDir, const char* DefaultActorsDir, const char* DefaultPawnIni);
	Level* Level_Create(const char* pWadName, const char* HeadersDir, const char* ActorsDir, const char* PawnIni);

	char* Util_Strdup(const char* s);
};

