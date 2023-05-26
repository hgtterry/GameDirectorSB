#pragma once

#include "Parse3dt.h"
#include "Box3d.h"
#include "face.h"




typedef struct TexInfoTag
{
	geVec3d VecNormal;
	geFloat xScale, yScale;
	int xShift, yShift;
	geFloat	Rotate;			// texture rotation angle in degrees
	TexInfo_Vectors TVecs;
	int Dib;				// index into the wad
	char Name[16];
	geBoolean DirtyFlag;
	geVec3d Pos;
	int txSize, tySize;		// texture size (not currently used)
	geXForm3d XfmFaceAngle;	// face rotation angle
} TexInfo;


typedef struct FaceTag
{
	int			NumPoints;
	int			Flags;
	::Plane		Face_Plane;
	int			LightIntensity;
	geFloat		Reflectivity;
	geFloat		Translucency;
	geFloat		MipMapBias;
	geFloat		LightXScale, LightYScale;
	TexInfo		Tex;
	geVec3d* Points;
} Face;

struct tag_FaceList
{
	int NumFaces;
	int Limit;
	Face** Faces;
	geBoolean Dirty;
	Box3d Bounds;
};

typedef struct FaceTag Face;
typedef struct tag_FaceList FaceList;

class WV_Faces
{
public:
	WV_Faces();
	~WV_Faces();

	FaceList* WV_Faces::FaceList_CreateFromFile(Parse3dt* Parser, int VersionMajor, int VersionMinor, const char** Expected);

	FaceList* FaceList_Create(int NumFaces);
	void FaceList_AddFace(FaceList* pList, Face* pFace);
	void FaceList_Destroy(FaceList** ppList);

	void FaceList_SetTranslucency(const FaceList* fl, geFloat trans);
	void FaceList_SetTransparent(const FaceList* fl, geBoolean trans);
};

