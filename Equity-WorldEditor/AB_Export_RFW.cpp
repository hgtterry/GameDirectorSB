
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
// * 						OnFileExportGDSB:- hgtterry					   *
// *************************************************************************
void AB_Export_RFW::OnFileExportGDSB() 
{
	bool Test = App->CL_FileIO->SaveSelectedFile("Equity   *.G3ds\0**.G3ds\0", App->CL_Scene->Current_3DT_Just_Path);

	if (Test == 1)
	{
		bool Check = App->CL_FileIO->CheckExtention(App->CL_FileIO->PathFileName);
		if (Check==0)
		{
			strcat(App->CL_FileIO->PathFileName, ".G3ds");
			strcat(App->CL_FileIO->FileName, ".G3ds");
		}

		App->pCFusionDoc = (CFusionDoc*)App->m_pMainFrame->GetCurrentDoc();
		App->pCFusionDoc->ExportTo_RFW(App->CL_FileIO->PathFileName, 1, 0, 0);
	}	
}

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


	Write_Project_File("GDSB.Wepf",Filename);

	return WriteRslt;
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

	fprintf(WriteScene, "%s\n", "[WE_Fast_Load]");
	fprintf(WriteScene, "%s%s\n", "Pref_WE_JustFileName=",App->CL_Scene->Current_3DT_File);
	fprintf(WriteScene, "%s%s\n", "Pref_WE_Path_FileName=",Filename);
	fprintf(WriteScene, "%s%s\n", "Pref_Txl_Path_FileName=", App->CL_Scene->Current_TXL_FilePath);

	fprintf(WriteScene, "%s%s\n", "Pref_Ogre_JustFileName=", "Test");
	fprintf(WriteScene, "%s%s\n", "Pref_Ogre_Path_FileName=", "Test");

	fprintf(WriteScene, "%s\n", " ");
	fclose(WriteScene);

	return 1;
}
