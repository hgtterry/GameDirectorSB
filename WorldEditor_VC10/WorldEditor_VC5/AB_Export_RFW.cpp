
#include "stdafx.h"
#include "AB_App.h"
#include "AB_Export_RFW.h"
#include "FUSIONDoc.h"
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

#pragma warning (disable:4100)

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
	WriteScene = NULL;
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
// * Equity_Export_RFW		ExportTo_RFW	// Old Exporter				   *
// *************************************************************************
void AB_Export_RFW::ExportTo_RFW(const char *FileName, int ExpSelected, geBoolean ExpLights, geBoolean ExpFiles)
{
/*	App->pCFusionDoc = (CFusionDoc*)App->m_pMainFrame->GetCurrentDoc();

	{
		// update view information in level
		ViewStateInfo *pViewStateInfo;
		POSITION		pos;
		CFusionView	*	pView;
		int iView;

		pos = 	App->pCFusionDoc->GetFirstViewPosition();
		while( pos != NULL )
		{
			pView = (CFusionView*)	App->pCFusionDoc->GetNextView(pos) ;
			switch (Render_GetViewType (pView->VCam))
			{
				case VIEWSOLID :
				case VIEWTEXTURE :
				case VIEWWIRE :
					iView = 0;
					break;
				case VIEWTOP :
					iView = 1;
					break;
				case VIEWFRONT :
					iView = 2;
					break;
				case VIEWSIDE :
					iView = 3;
					break;
				default :
					iView = -1;
			}
			if (iView != -1)
			{
				pViewStateInfo = Level_GetViewStateInfo (pLevel, iView);
				pViewStateInfo->IsValid = GE_TRUE;
				pViewStateInfo->ZoomFactor = Render_GetZoom (pView->VCam);
				Render_GetPitchRollYaw (pView->VCam, &pViewStateInfo->PitchRollYaw);
				Render_GetCameraPos (pView->VCam, &pViewStateInfo->CameraPos);
			}
		}
	}

// changed QD 12/03
	BrushList *BList;
	geBoolean fResult;

	BList = Level_GetBrushes (pLevel);
	if(!ExpSelected&&!ExpFiles)
		fResult = App->ABC_Export_RFW->Level_ExportTo_RFW(reinterpret_cast<tag_Level2 *> (pLevel), FileName, BList, ExpSelected, ExpLights, -1);

	else
	{
		int i, GroupID, GroupCount;
		char NewFileName[MAX_PATH];
		strcpy(NewFileName, FileName);
		GroupID=-1;
		GroupCount=1;

		if(ExpFiles)
		{
			GroupListType *GroupList;

			GroupList=Level_GetGroups(pLevel);
			GroupCount=Group_GetCount(GroupList);
		}

		for(i=0;i<GroupCount;i++)
		{
			BrushList *SBList;
			Brush *pBrush;
			BrushIterator bi;

			SBList=BrushList_Create();

			pBrush = BrushList_GetFirst (BList, &bi);
			while (pBrush != NULL)
			{
				if(!strstr(Brush_GetName(pBrush),".act"))
				{
					if(!ExpSelected || SelBrushList_Find(pSelBrushes, pBrush))
					{
						if(!ExpFiles || Brush_GetGroupId(pBrush)==i)
						{
							Brush *pClone =	Brush_Clone(pBrush);
							BrushList_Append(SBList, pClone);
						}
					}
				}

				pBrush = BrushList_GetNext(&bi);
			}
			// do CSG
			{
				ModelIterator	mi;
				int				i, CurId = 0;
				ModelInfo_Type	*ModelInfo;
				Model			*pMod;

				BrushList_ClearAllCSG (SBList);

				BrushList_DoCSG(SBList, CurId, ::fdocBrushCSGCallback, this);

				//build individual model mini trees
				ModelInfo = Level_GetModelInfo (pLevel);
				pMod = ModelList_GetFirst (ModelInfo->Models, &mi);

				for(i=0;i < ModelList_GetCount(ModelInfo->Models);i++)
				{
					CurId = Model_GetId (pMod);

					BrushList_DoCSG(SBList, CurId, ::fdocBrushCSGCallback, this);
				}
			}

			if(ExpFiles)
			{
				GroupID=i;

				//build individual filenames
				char Name[MAX_PATH];
				char c[2];
				c[1]='\0';
				::FilePath_GetName (FileName, Name);
				c[0] = (char)(48+(i-i%100)/100);
				strcat(Name, c);
				c[0] = (char)(48+((i-i%10)/10)%10);
				strcat(Name, c);
				c[0] = (char)(48+i%10);
				strcat(Name, c);

				::FilePath_ChangeName(FileName, Name, NewFileName);
			}

			fResult =App->ABC_Export_RFW->Level_ExportTo_RFW(reinterpret_cast<tag_Level2 *> (pLevel), NewFileName, SBList, ExpSelected, ExpLights, GroupID);
			if(!fResult)
				ConPrintf("Error exporting group %i\n", i);
			BrushList_Destroy(&SBList);
		}

	}
// end change 12/03

	if(fResult == GE_FALSE)
	{
		// Ok, the save was successful.  Gun any ".old" files we
		// ..have laying around for this file.
		ConPrintf("Error exporting file\n");
	}
	else
	{
			App->Say("Exported");
	}*/
}

// *************************************************************************
// *						Write_Project_File Terry Flanigan 			   *
// *************************************************************************
bool AB_Export_RFW::Write_Project_File(char* Path_And_File,const char* Filename)
{
	char NewFile[MAX_PATH];

	if (stricmp(Filename + strlen(Filename) - 5, ".G3ds") == 0)
	{
		strcpy(NewFile, Filename);
		int Len = strlen(NewFile);
		NewFile[Len - 5] = 0;

		strcat(NewFile,".Wepf");
	}

	WriteScene = NULL;

	WriteScene = fopen(NewFile, "wt");
	if (!WriteScene)
	{
		App->Say("Cant Create Save File");
		return 0;
	}

	fprintf(WriteScene, "%s\n", "[World_Data]");

	fprintf(WriteScene, "%s%s\n", "3dt_Path_FileName=",App->CL_World->mCurrent_3DT_PathAndFile);


	fprintf(WriteScene, "%s%s\n", "G3ds_Path_FileName=",Filename);


	fprintf(WriteScene, "%s%s\n", "Txl_Path_FileName=", App->CL_World->mCurrent_TXL_FilePath);


	fprintf(WriteScene, "%s\n", " ");
	fclose(WriteScene);

	return 1;
}
