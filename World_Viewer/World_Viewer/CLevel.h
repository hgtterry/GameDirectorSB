#pragma once

#include "CGroup.h"
#define LEVEL_VERSION_MAJOR	1
//#define LEVEL_VERSION_MINOR 16		// version 1.16 06/01/98 - eli - Removed palette dependencies (no more PalPath)
//#define LEVEL_VERSION_MINOR 17		// version 1.17 06/10/98 - jim - added LightXScale and LightYScale to face
//#define LEVEL_VERSION_MINOR 18		// version 1.18 06/17/98 - jim - read paths as literal strings
//#define LEVEL_VERSION_MINOR 19		// version 1.19 06/26/98 - jim - Quote group and model names
//#define LEVEL_VERSION_MINOR 20		// version 1.20 07/06/98 - jim - Store build and edit information in level file
//#define LEVEL_VERSION_MINOR 21		// VERSION 1.21 07/14/98 - jim - removed entity RenderOrigin field
//#define LEVEL_VERSION_MINOR 22		// version 1.22 07/27/98 - jim - Added level options (draw scale and lightmap scale)
//#define LEVEL_VERSION_MINOR 23		// version 1.23 08/20/98 - jim - Added hull thickness to cylinder template
//#define LEVEL_VERSION_MINOR 24		// version 1.24 08/26/98 - jim - Quoted texture name in brush and texinfo I/O
//#define LEVEL_VERSION_MINOR 25		// Version 1.25 10/06/98 - jim - Add support for Gouraud and flat shading faces
//#define LEVEL_VERSION_MINOR 26		// Version 1.26 10/14/98 - jim - Add sky box rotation axis and speed
//#define LEVEL_VERSION_MINOR 27		// Version 1.27 10/27/98 - Ken - New face flags and values
//#define LEVEL_VERSION_MINOR 28		// Version 1.28 10/27/98 - Ken - Sky texture scale
//#define LEVEL_VERSION_MINOR 29		// Version 1.29 12/09/98 - Jim - Added sheet brushes
//#define LEVEL_VERSION_MINOR 30		// Version 1.30 12/22/98 - Jim - Added face transparent flag
//#define LEVEL_VERSION_MINOR 31		// Version 1.31 01/05/99 - jim - Added headers directory
//#define LEVEL_VERSION_MINOR 32		// Version 1.32 11/04/99 - Brian - Face Info save out Base Vec for Tex Lock
//#define LEVEL_VERSION_MINOR 33		// Version 1.33 08/15/03 - QD - Added ActorsDirectory, PawnIniPath; TexRotation is saved as float
#define LEVEL_VERSION_MINOR 34			// Version 1.34 11/09/03 - QD - changed Arch template

typedef struct tag_Level Level;

enum { GridMetric = 0, GridTexel = 1 };

enum
{
	GridSize_Centimeter = 1,
	GridSize_Decimeter = 10,
	GridSize_Meter = 100
};

typedef struct
{
	geBoolean UseGrid;
	int GridType;

	int SnapType;
	int MetricSnapSize;
	int TexelSnapSize;
	int RotationSnap;
} GridInfo;

typedef struct
{
	geBoolean IsValid;
	float ZoomFactor;
	geVec3d PitchRollYaw;
	geVec3d CameraPos;
} ViewStateInfo;


class CLevel
{
public:
	CLevel();
	~CLevel();

	Level* Level_CreateFromFile(const char* FileName);
	Level* Level_Create(const char* pWadName, const char* HeadersDir, const char* ActorsDir, const char* PawnIni);
	GroupListType* Level_GetGroups(Level* pLevel);
	BrushList* Level_GetBrushes(Level* pLevel);
	int Level_GetGroupVisibility(const Level* pLevel);
	float Level_GetGridSnapSize(const Level* pLevel);
	int Level_GetGridType(const Level* pLevel);

};

