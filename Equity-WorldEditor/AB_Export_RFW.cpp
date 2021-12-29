
#include "stdafx.h"
#include "AB_App.h"
#include "AB_Export_RFW.h"

#include "level.h"
#include "Parse3dt.h"
#include "EntTypeName.h"
#include <assert.h>
#include "ram.h"
#include "units.h"
#include "util.h"
#include "FilePath.h"
// changed QD 12/03
#include <malloc.h>
#include "typeio.h"


#define NUM_VIEWS (4)

struct tag_Level2
{
    BrushList *Brushes;
	CEntityArray *Entities;
    char *WadPath;
	char *HeadersDir;
	// changed QD Actors
	char *ActorsDir;
	geBoolean ShowActors;
	char *PawnIniPath;
	// end change
	EntTypeNameList	*EntTypeNames;
	GroupListType *Groups;
	SizeInfo	*WadSizeInfos;
	CWadFile	*WadFile;
	EntityTable	*pEntityDefs;

	ModelInfo_Type	ModelInfo;

	SkyFaceTexture SkyFaces[6];
	geVec3d SkyRotationAxis;
	geFloat SkyRotationSpeed;
	geFloat	SkyTextureScale;
	
	// level edit settings
	CompileParamsType CompileParams;
	int GroupVisSetting;
	EntityViewList *pEntityView;

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

AB_Export_RFW::AB_Export_RFW()
{

}

AB_Export_RFW::~AB_Export_RFW()
{

}

// changed QD 12/03
#define CHUNK_MAIN3DS		0x4d4d
#define CHUNK_VERSION		0x0002
#define CHUNK_EDIT3DS		0x3d3d
#define CHUNK_MESH_VERSION	0x3d3e
// global chunks
#define CHUNK_COLORRGB      0x0011
#define CHUNK_PERCENT		0x0030
// Object chunks
/*
#define CHUNK_OBJBLOCK		0x4000
#define CHUNK_TRIMESH		0x4100
#define CHUNK_VERTLIST		0x4110
#define CHUNK_FACELIST		0x4120
#define CHUNK_MAPLIST		0x4140
#define CHUNK_SMOOTHLIST	0x4150
*/
// Material chunks
#define CHUNK_MATBLOCK		0xAFFF
#define CHUNK_MATNAME		0xA000
#define CHUNK_MATAMB		0xA010 // Ambient color
#define CHUNK_MATDIFF		0xA020 // Diffuse color
#define CHUNK_MATSPEC		0xA030 // Specular color
#define CHUNK_MATSHININESS	0xA040
#define CHUNK_MATSHIN2PCT	0xA041
#define CHUNK_MATTRANS		0xA050
#define CHUNK_MATXPFALL		0xA052
#define CHUNK_MATREFBLUR	0xA053
#define CHUNK_MATSHADING	0xA100
#define CHUNK_MATDECAL		0xA084
#define CHUNK_MATWIRESIZE	0xA087
#define CHUNK_MAP			0xA200
#define CHUNK_MAPNAME		0xA300 // name of bitmap
#define CHUNK_MAPTILING		0xA351

// Keyframe chunks
#define CHUNK_KEYFRAME		0xB000
#define CHUNK_KF_HDR		0xB00a
#define CHUNK_KF_SEG		0xB008 // start, end
#define CHUNK_KF_CURTIME	0xB009

#define MASTER_SCALE		0x0100

// *************************************************************************
// *							Level_ExportTo_RFW						   *
// *************************************************************************
bool AB_Export_RFW::Level_ExportTo_RFW(Level2 *pLevel, const char *Filename, BrushList *BList,int ExpSelected, geBoolean ExpLights, int GroupID)
{

	FILE	*f;
	geBoolean WriteRslt;
	int size, i;
	geBoolean *WrittenTex;

	if(!pLevel) return GE_FALSE;
	if(!Filename) return GE_FALSE;

	// error checking required!
	f = fopen(Filename, "wb");

	if (!f)	return GE_FALSE;

	WriteRslt = GE_FALSE;

	// get the number of textures
	WrittenTex=(geBoolean *)calloc(sizeof(geBoolean), pLevel->WadFile->mBitmapCount);
	// which textures are used?
	BrushList_GetUsedTextures(BList, WrittenTex, pLevel->WadFile);

	const int FileLength = 11;

	fseek(f, 32L, SEEK_SET);

	// write all used materials to the file
	for(i=0;i<pLevel->WadFile->mBitmapCount;i++)
	{
		if(WrittenTex[i])
		{
			// 3ds only allows DOS 8.3 file names, so cut the name if necessary
			char matname[FileLength];
			int j,k;
			strncpy (matname, pLevel->WadFile->mBitmaps[i].Name, FileLength-1);
			matname[FileLength-1] = '\0';
			for(j=0;matname[j]!='\0';j++);

			TypeIO_WriteUshort(f, CHUNK_MATBLOCK);
			TypeIO_WriteInt(f, 6+6+j+1 +(3*15) + 102 +6 +8 +6+j+5 +8);

			// write material name
			TypeIO_WriteUshort(f, CHUNK_MATNAME);
			TypeIO_WriteInt(f,(6+j+1));
			for(k=0;k<=j;k++)
				TypeIO_WriteUChar(f, matname[k]);

			// ambient color
			TypeIO_WriteUshort(f, CHUNK_MATAMB);		//0xA010  Ambient color
			TypeIO_WriteInt(f,6+6+3);

			TypeIO_WriteUshort(f, CHUNK_COLORRGB);
			TypeIO_WriteInt(f,6+3);
			TypeIO_WriteUChar(f, (char)120);
			TypeIO_WriteUChar(f, (char)120);
			TypeIO_WriteUChar(f, (char)120);

			// diffuse color
			TypeIO_WriteUshort(f, CHUNK_MATDIFF);		//0xA020  Diffuse color
			TypeIO_WriteInt(f,6+6+3);

			TypeIO_WriteUshort(f, CHUNK_COLORRGB);
			TypeIO_WriteInt(f,6+3);
			TypeIO_WriteUChar(f, (char)120);
			TypeIO_WriteUChar(f, (char)120);
			TypeIO_WriteUChar(f, (char)120);

			// specular color
			TypeIO_WriteUshort(f, CHUNK_MATSPEC);		//0xA030  Specular color
			TypeIO_WriteInt(f,6+6+3);

			TypeIO_WriteUshort(f, CHUNK_COLORRGB);
			TypeIO_WriteInt(f,6+3);
			TypeIO_WriteUChar(f, (char)120);
			TypeIO_WriteUChar(f, (char)120);
			TypeIO_WriteUChar(f, (char)120);

			TypeIO_WriteUshort(f, CHUNK_MATSHININESS);
			TypeIO_WriteInt(f,14);
			TypeIO_WriteUshort(f, CHUNK_PERCENT);
			TypeIO_WriteInt(f,8);
			TypeIO_WriteUshort(f, 0);

			TypeIO_WriteUshort(f, CHUNK_MATSHIN2PCT);
			TypeIO_WriteInt(f,14);
			TypeIO_WriteUshort(f, CHUNK_PERCENT);
			TypeIO_WriteInt(f,8);
			TypeIO_WriteUshort(f, 0);

			TypeIO_WriteUshort(f, CHUNK_MATTRANS);
			TypeIO_WriteInt(f,14);
			TypeIO_WriteUshort(f, CHUNK_PERCENT);
			TypeIO_WriteInt(f,8);
			TypeIO_WriteUshort(f, 0);

			TypeIO_WriteUshort(f, CHUNK_MATXPFALL);
			TypeIO_WriteInt(f,14);
			TypeIO_WriteUshort(f, CHUNK_PERCENT);
			TypeIO_WriteInt(f,8);
			TypeIO_WriteUshort(f, 0);

			TypeIO_WriteUshort(f, CHUNK_MATREFBLUR);
			TypeIO_WriteInt(f,14);
			TypeIO_WriteUshort(f, CHUNK_PERCENT);
			TypeIO_WriteInt(f,8);
			TypeIO_WriteUshort(f, 0);

			TypeIO_WriteUshort(f, CHUNK_MATSHADING);
			TypeIO_WriteInt(f,8);
			TypeIO_WriteUshort(f, 3);

			TypeIO_WriteUshort(f, CHUNK_MATDECAL);
			TypeIO_WriteInt(f,14);
			TypeIO_WriteUshort(f, CHUNK_PERCENT);
			TypeIO_WriteInt(f,8);
			TypeIO_WriteUshort(f, 0);

			TypeIO_WriteUshort(f, CHUNK_MATWIRESIZE);
			TypeIO_WriteInt(f,10);
			TypeIO_WriteFloat(f, 1.0f);

			// texture map
			TypeIO_WriteUshort(f, CHUNK_MAP);
			TypeIO_WriteInt(f,6+8+6+j+5+8);

			TypeIO_WriteUshort(f, CHUNK_PERCENT);
			TypeIO_WriteInt(f,8);
			TypeIO_WriteUshort(f, 100);

			// write map name
			TypeIO_WriteUshort(f, CHUNK_MAPNAME);
			TypeIO_WriteInt(f, 6+j+5);
			for(k=0;k<j;k++)
				TypeIO_WriteUChar(f, matname[k]);
			TypeIO_WriteUChar(f, '.');
			if(geBitmap_HasAlpha(pLevel->WadFile->mBitmaps[i].bmp))
			{
				TypeIO_WriteUChar(f, 't');
				TypeIO_WriteUChar(f, 'g');
				TypeIO_WriteUChar(f, 'a');
			}
			else
			{
				TypeIO_WriteUChar(f, 'b');
				TypeIO_WriteUChar(f, 'm');
				TypeIO_WriteUChar(f, 'p');
			}

			TypeIO_WriteUChar(f, '\0');

			TypeIO_WriteUshort(f, CHUNK_MAPTILING);
			TypeIO_WriteInt(f,8);
			TypeIO_WriteUshort(f, 0);
		}
	}

	// write out the master scale
	TypeIO_WriteUshort(f, MASTER_SCALE);
	TypeIO_WriteInt(f, 10);
	TypeIO_WriteFloat(f, 1.0f);

	// export the brushes
	if (BrushList_ExportTo3ds (BList, f, GE_FALSE) == GE_FALSE) goto WriteDone;

// changed QD 12/03
	int size_kf;
	size_kf=0;

	size = ftell(f);

	// move back to the bginning of the file
	fseek(f, 0L, SEEK_SET );

	TypeIO_WriteUshort(f,CHUNK_MAIN3DS);
	TypeIO_WriteInt(f, size);

	TypeIO_WriteUshort(f, CHUNK_VERSION);
	TypeIO_WriteInt(f, 10);
	TypeIO_WriteInt(f, 3);

	TypeIO_WriteUshort(f,CHUNK_EDIT3DS);
// changed QD 12/03
	TypeIO_WriteInt(f, size-16-size_kf);
// end change
	TypeIO_WriteUshort(f,CHUNK_MESH_VERSION);
	TypeIO_WriteInt(f, 10);
	TypeIO_WriteInt(f, 3);

	WriteRslt = GE_TRUE;

WriteDone:

	free(WrittenTex);

	if (fclose(f) != 0) return GE_FALSE;

// changed QD 12/03
	if((size-size_kf)<=42)
		_unlink(Filename);
// end change

	return WriteRslt;
}
