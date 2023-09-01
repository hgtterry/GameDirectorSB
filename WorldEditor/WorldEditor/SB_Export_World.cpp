/*
Copyright (c) 2023 World Editor -- HGT Software W.T.Flanigan H.C.Flanigan

This software is provided 'as-is', without any express or implied
warranty. In no event will the authors be held liable for any damages
arising from the use of this software.

Permission is granted to anyone to use this software for any purpose,
including commercial applications, and to alter it and redistribute it
freely, subject to the following restrictions:

1. The origin of this software must not be misrepresented; you must not
claim that you wrote the original software. If you use this software
in a product, an acknowledgment in the product documentation would be
appreciated but is not required.

2. Altered source versions must be plainly marked as such, and must not be
misrepresented as being the original software.

3. This notice may not be removed or altered from any source
distribution.
*/

#include "stdafx.h"
#include "AB_App.h"
#include "SB_Export_World.h"

#include "FUSIONDoc.h"
#include "FUSIONView.h"
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

//#include "Entity.h"

#pragma warning( disable : 4101 4100 4800)

#define NUM_VIEWS (4)

enum BrushFlags
{
	BRUSH_SOLID = 0x0001,
	BRUSH_WINDOW = 0x0002,
	BRUSH_WAVY = 0x0004,
	BRUSH_DETAIL = 0x0008,	//not included in vis calculations
	BRUSH_HOLLOWCUT = 0x0010,
	BRUSH_TRANSLUCENT = 0x0020,
	BRUSH_EMPTY = 0x0040,
	BRUSH_SUBTRACT = 0x0080,
	BRUSH_CLIP = 0x0100,
	BRUSH_FLOCKING = 0x0200,
	BRUSH_HOLLOW = 0x0400,
	BRUSH_SHEET = 0x0800,
	BRUSH_HIDDEN = 0x1000,
	BRUSH_LOCKED = 0x2000,
	BRUSH_HINT = 0x4000,
	BRUSH_AREA = 0x8000
	// All flags larger than 0x8000 (i.e. 0x00010000 through 0x80000000)
	// are reserved for user contents.
};

struct tag_Level3
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

SB_Export_World::SB_Export_World(void)
{
	WriteScene = NULL;
	WriteScene_TXT = NULL;
}

SB_Export_World::~SB_Export_World(void)
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
// * 		Export_World_GD3D:- Terry and Hazel Flanigan 2023			   *
// *************************************************************************
void SB_Export_World::Export_World_GD3D(bool Silent)
{
	App->Get_Current_Document();
	
	if (Silent == 0)
	{
		bool Test = App->CLSB_FileIO->SaveSelectedFile("Equity   *.G3ds\0**.G3ds\0", App->CL_World->mCurrent_3DT_Path);

		if (Test == 1)
		{
			bool Check = App->CLSB_FileIO->CheckExtention(App->CLSB_FileIO->PathFileName);
			if (Check==0)
			{
				strcat(App->CLSB_FileIO->PathFileName, ".G3ds");
				strcat(App->CLSB_FileIO->FileName, ".G3ds");
			}

			ExportTo_RFW(App->CLSB_FileIO->PathFileName, 1, 0, 0);
		}
	}
	else
	{

		char Path[MAX_PATH];
		strcpy(Path,App->WorldEditor_Directory);
		strcat(Path,"Data\\Temp.G3ds");
		ExportTo_RFW(Path, 1, 0, 0);
	}
}


static geBoolean fdocBrushCSGCallback2 (const Brush *pBrush, void *lParam)
{
	return (App->m_pDoc->BrushIsVisible (pBrush) && (!Brush_IsHint(pBrush)) && (!Brush_IsClip(pBrush)));
}

// *************************************************************************
// *				ExportTo_RFW	// Old Exporter						   *
// *************************************************************************
void SB_Export_World::ExportTo_RFW(const char *FileName, int ExpSelected, geBoolean ExpLights, geBoolean ExpFiles)
{
	{
		// update view information in level
		ViewStateInfo *pViewStateInfo;
		POSITION		pos;
		CFusionView	*	pView;
		int iView;

		pos = App->m_pDoc->GetFirstViewPosition();
		while( pos != NULL )
		{
			pView = (CFusionView*)App->m_pDoc->GetNextView(pos) ;
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
				pViewStateInfo = Level_GetViewStateInfo (App->m_pDoc->pLevel, iView);
				pViewStateInfo->IsValid = GE_TRUE;
				pViewStateInfo->ZoomFactor = Render_GetZoom (pView->VCam);
				Render_GetPitchRollYaw (pView->VCam, &pViewStateInfo->PitchRollYaw);
				Render_GetCameraPos (pView->VCam, &pViewStateInfo->CameraPos);
			}
		}
	}

	
// changed QD 12/03 77
	BrushList *BList;
	geBoolean fResult;

	BList = Level_GetBrushes (App->m_pDoc->pLevel);
	if(!ExpSelected&&!ExpFiles)
	{
		fResult = App->CLSB_Export_World->Level_Build_G3ds(reinterpret_cast<tag_Level3 *> (App->m_pDoc->pLevel), FileName, BList, ExpSelected, ExpLights, -1);
	}
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

			GroupList=Level_GetGroups(App->m_pDoc->pLevel);
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
				if(!strstr(App->CL_Brush->Brush_GetName(pBrush),".act"))
				{
					if(!ExpSelected || SelBrushList_Find(App->m_pDoc->pSelBrushes, pBrush))
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

				BrushList_DoCSG(SBList, CurId, ::fdocBrushCSGCallback2, this);

				//build individual model mini trees
				ModelInfo = Level_GetModelInfo (App->m_pDoc->pLevel);
				pMod = ModelList_GetFirst (ModelInfo->Models, &mi);

				for(i=0;i < ModelList_GetCount(ModelInfo->Models);i++)
				{
					CurId = Model_GetId (pMod);

					BrushList_DoCSG(SBList, CurId, ::fdocBrushCSGCallback2,this);
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
			
			fResult = App->CLSB_Export_World->Level_Build_G3ds(reinterpret_cast<tag_Level3 *> (App->m_pDoc->pLevel), NewFileName, SBList, ExpSelected, ExpLights, GroupID);
			if(!fResult)
				App->Say("Error exporting group");
			BrushList_Destroy(&SBList);
		}

	}
// end change 12/03

	if(fResult == GE_FALSE)
	{
		// Ok, the save was successful.  Gun any ".old" files we
		// ..have laying around for this file.
		App->Say("Error exporting file");
	}
	else
	{
			//App->Say("Exported 2");
	}
}

// *************************************************************************
// *			Level_Build_G3ds:- Terry and Hazel Flanigan 2023		   *
// *************************************************************************
bool SB_Export_World::Level_Build_G3ds(Level3 *pLevel, const char *Filename, BrushList *BList,int ExpSelected, geBoolean ExpLights, int GroupID)
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
bool SB_Export_World::Write_Project_File(char* Path_And_File,const char* Filename)
{
	char NewFile[MAX_PATH];

	if (stricmp(Filename + strlen(Filename) - 5, ".G3ds") == 0)
	{
		strcpy(NewFile, Filename);
		int Len = strlen(NewFile);
		NewFile[Len - 5] = 0;

		strcat(NewFile,".Wepf");
	}
	else
	{
		strcpy(NewFile, Filename);
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

	CEntity *pCameraEntity = App->CLSB_Camera_WE->FindCameraEntity();
	geVec3d CameraPosition;
	CameraPosition = pCameraEntity->mOrigin;

	fprintf(WriteScene, "%s\n", "[Special]");
	fprintf(WriteScene, "%s %f %f %f\n", "Position=",CameraPosition.X,CameraPosition.Y,CameraPosition.Z);

	geVec3d Angles;
	pCameraEntity->GetAngles( &Angles, Level_GetEntityDefs (App->m_pDoc->pLevel) );
	fprintf(WriteScene, "%s %f %f %f\n", "Angles=",Angles.X,Angles.Y,Angles.Z);


	fclose(WriteScene);

	return 1;
}

// *************************************************************************
// * 		Export_World_Text:- Terry and Hazel Flanigan 2023			   *
// *************************************************************************
void SB_Export_World::Export_World_Text(int ExpSelected)
{
	App->CLSB_Model->BrushCount = 0;
	

	WriteScene_TXT = NULL;

	char Path[MAX_PATH];
	strcpy(Path, App->WorldEditor_Directory);
	strcat(Path, "Data\\3DSTemp.txt");

	WriteScene_TXT = fopen(Path, "wt");
	if (!WriteScene_TXT)
	{
		App->Say("Cant Create Save File");
		return;
	}

	fprintf(WriteScene_TXT, "%s\n", "[GameDirector]");

	BrushList* BList;
	geBoolean fResult;

	BList = Level_GetBrushes(App->m_pDoc->pLevel);
	if (!ExpSelected)
	{
		fResult = Level_Build_Text_G3ds(reinterpret_cast<tag_Level3*> (App->m_pDoc->pLevel), "FileName", BList, 0, 0, -1);
	}
	else
	{
		int i, GroupID, GroupCount;
		char NewFileName[MAX_PATH];
		GroupID = -1;
		GroupCount = 1;

		for (i = 0; i < GroupCount; i++)
		{
			BrushList* SBList;
			Brush* pBrush;
			BrushIterator bi;

			SBList = BrushList_Create();
			pBrush = BrushList_GetFirst(BList, &bi);

			while (pBrush != NULL)
			{

				if (SelBrushList_Find(App->m_pDoc->pSelBrushes, pBrush))
				{
					Brush* pClone = Brush_Clone(pBrush);
					BrushList_Append(SBList, pClone);
				}

				pBrush = BrushList_GetNext(&bi);
			}
			// do CSG
			{
				ModelIterator	mi;
				int				i, CurId = 0;
				ModelInfo_Type* ModelInfo;
				Model* pMod;

				BrushList_ClearAllCSG(SBList);

				BrushList_DoCSG(SBList, CurId, ::fdocBrushCSGCallback2, this);

				//build individual model mini trees
				ModelInfo = Level_GetModelInfo(App->m_pDoc->pLevel);
				pMod = ModelList_GetFirst(ModelInfo->Models, &mi);

				for (i = 0; i < ModelList_GetCount(ModelInfo->Models); i++)
				{
					CurId = Model_GetId(pMod);

					BrushList_DoCSG(SBList, CurId, ::fdocBrushCSGCallback2, this);
				}
			}

			fResult = Level_Build_Text_G3ds(reinterpret_cast<tag_Level3*> (App->m_pDoc->pLevel), NewFileName, SBList, 0, 0, -1);
			if (!fResult)
			{
				App->Say("Error exporting group");
			}

			BrushList_Destroy(&SBList);
		}
	}

	fclose(WriteScene_TXT);

	//App->Say("Saved");
}

// *************************************************************************
// *		Level_Build_Text_G3ds:- Terry and Hazel Flanigan 2023		   *
// *************************************************************************
bool SB_Export_World::Level_Build_Text_G3ds(Level3* pLevel, const char* Filename, BrushList* BList, int ExpSelected, geBoolean ExpLights, int GroupID)
{
	int i;
	geBoolean* WrittenTex;

	WrittenTex = (geBoolean*)calloc(sizeof(geBoolean), pLevel->WadFile->mBitmapCount);

	// which textures are used?
	BrushList_GetUsedTextures(BList, WrittenTex, pLevel->WadFile);

	// Add Textures GL
	int AdjustedIndex = 0;
	for (i = 0; i < pLevel->WadFile->mBitmapCount; i++)
	{
		if (WrittenTex[i])
		{
			char matname[MAX_PATH];
			int j, k;
			strncpy(matname, pLevel->WadFile->mBitmaps[i].Name, MAX_PATH - 1);
			fprintf(WriteScene_TXT, "%i %s %i\n", AdjustedIndex, matname,i);
			AdjusedIndex_Store[AdjustedIndex] = i;

			AddTexture_GL(NULL, matname, AdjustedIndex);

			AdjustedIndex++;

		}
	}

	BrushList_ExportToText(BList, GE_FALSE);

	free(WrittenTex);

	return 1;
}

static int	BrushCount;
static int	SubBrushCount;

// *************************************************************************
// *		BrushList_ExportToText:- Terry and Hazel Flanigan 2023		   *
// *************************************************************************
bool SB_Export_World::BrushList_ExportToText(BrushList* BList, geBoolean SubBrush)
{
	Brush* pBrush;
	BrushIterator bi;

	pBrush = BrushList_GetFirst(BList, &bi);

	while (pBrush != NULL)
	{
		if (!Brush_ExportToText(pBrush)) return GE_FALSE;
		pBrush = BrushList_GetNext(&bi);

		if (SubBrush)
		{
			SubBrushCount++;
		}
		else
		{
			BrushCount++;
		}
	}

	SubBrushCount = 0;

	if (!SubBrush)
	{
		BrushCount = 0;
	}

	return GE_TRUE;
}

#include "facelist.h"
// *************************************************************************
// *		Brush_ExportToText:- Terry and Hazel Flanigan 2023			   *
// *************************************************************************
bool SB_Export_World::Brush_ExportToText(const Brush* b)
{
	assert(ofile);
	assert(b);

	switch (b->Type)
	{
	case	BRUSH_MULTI:
		return BrushList_ExportToText(b->BList,GE_TRUE);

	case	BRUSH_LEAF:
		if (b->BList)
		{
			return BrushList_ExportToText(b->BList,GE_TRUE);
		}
		else
		{
			if (!(b->Flags & (BRUSH_HOLLOW | BRUSH_HOLLOWCUT | BRUSH_SUBTRACT)))
			{
				return FaceList_ExportToText(b,b->Faces, BrushCount, SubBrushCount);
			}
			else if ((b->Flags & BRUSH_SUBTRACT) && !(b->Flags & (BRUSH_HOLLOW | BRUSH_HOLLOWCUT)))
				BrushCount--;
		}
		break;


	case	BRUSH_CSG:
		if (!(b->Flags & (BRUSH_HOLLOW | BRUSH_HOLLOWCUT | BRUSH_SUBTRACT)))
			return FaceList_ExportToText(b,b->Faces, BrushCount, SubBrushCount);
		break;
	default:
		assert(0);		// invalid brush type
		break;
	}

	return GE_TRUE;
}

struct tag_FaceList
{
	int NumFaces;
	int Limit;
	Face** Faces;
	geBoolean Dirty;
	Box3d Bounds;
};

// *************************************************************************
// *							FaceList_ExportToText					   *
// *************************************************************************
bool SB_Export_World::FaceList_ExportToText(const Brush* b,const FaceList* pList, int BrushCount, int SubBrushCount)
{

	App->CLSB_Model->Create_Brush(App->CLSB_Model->BrushCount);


	int i, j, k, num_faces, num_verts, num_mats, num_chars, curnum_verts;
	char matname[MAX_PATH];

	char* matf = (char*)calloc(sizeof(char), pList->NumFaces);

	assert(pList != NULL);
	assert(f != NULL);

	num_faces = num_verts = num_mats = num_chars = 0;
	// get the total number of verts, faces and materials of the object

	for (i = 0; i < pList->NumFaces; i++)
	{
		curnum_verts = Face_GetNumPoints(pList->Faces[i]);
		num_faces += (curnum_verts - 2);
		num_verts += curnum_verts;

		if (!matf[i])
		{
			matf[i] = 1;
			num_mats++;

			for (j = i + 1; j < pList->NumFaces; j++)
			{
				if (strcmp(Face_GetTextureName(pList->Faces[i]), Face_GetTextureName(pList->Faces[j])) == 0)
					matf[j] = 1;
			}

			strncpy(matname, Face_GetTextureName(pList->Faces[i]), MAX_PATH);
		}
	}

	for (i = 0; i < pList->NumFaces; i++)
		matf[i] = 0;

	// Name of Brush SubBrush
	fprintf(WriteScene_TXT,"%s_%i_%i\n",b->Name,BrushCount, SubBrushCount);
	
	// -----------------------------------  Vertices
	int VertIndex = 0;
	fprintf(WriteScene_TXT, "# Number of Vertices = %i \n", num_verts);
	App->CLSB_Model->B_Brush[App->CLSB_Model->BrushCount]->Vertice_Count = num_verts;
	App->CLSB_Model->B_Brush[App->CLSB_Model->BrushCount]->vertex_Data.resize(num_verts);
	App->CLSB_Model->B_Brush[App->CLSB_Model->BrushCount]->Normal_Data.resize(num_verts);
	
	for (i = 0; i < pList->NumFaces; i++)
	{
		const geVec3d* verts;
		verts = Face_GetPoints(pList->Faces[i]);
		curnum_verts = Face_GetNumPoints(pList->Faces[i]);
		for (j = 0; j < curnum_verts; j++)
		{
			fprintf(WriteScene_TXT, "V = %f %f %f\n", verts[j].X, verts[j].Y, verts[j].Z);
			App->CLSB_Model->B_Brush[App->CLSB_Model->BrushCount]->vertex_Data[VertIndex].x = verts[j].X;
			App->CLSB_Model->B_Brush[App->CLSB_Model->BrushCount]->vertex_Data[VertIndex].y = verts[j].Y;
			App->CLSB_Model->B_Brush[App->CLSB_Model->BrushCount]->vertex_Data[VertIndex].z = verts[j].Z;

			App->CLSB_Model->B_Brush[App->CLSB_Model->BrushCount]->Normal_Data[VertIndex].x = 0.5;
			App->CLSB_Model->B_Brush[App->CLSB_Model->BrushCount]->Normal_Data[VertIndex].y = 0.5;
			App->CLSB_Model->B_Brush[App->CLSB_Model->BrushCount]->Normal_Data[VertIndex].z = 0.5;

			VertIndex++;
		}
	}

	int UVIndex = 0;
	// -----------------------------------  UVS
	App->CLSB_Model->B_Brush[App->CLSB_Model->BrushCount]->MapCord_Data.resize(num_verts);
	for (i = 0; i < pList->NumFaces; i++)
	{
		const TexInfo_Vectors* TVecs = Face_GetTextureVecs(pList->Faces[i]);
		const geVec3d* verts;
		geVec3d uVec, vVec;
		geFloat U, V;

		int txSize, tySize;

		Face_GetTextureSize(pList->Faces[i], &txSize, &tySize);

		// make sure that the texture size is set correctly (division!)
		if (txSize == 0)
			txSize = 32;
		if (tySize == 0)
			tySize = 32;

		geVec3d_Scale(&TVecs->uVec, 1.f / (geFloat)txSize, &uVec);
		geVec3d_Scale(&TVecs->vVec, -1.f / (geFloat)tySize, &vVec);

		verts = Face_GetPoints(pList->Faces[i]);
		curnum_verts = Face_GetNumPoints(pList->Faces[i]);

		for (j = 0; j < curnum_verts; j++)
		{
			U = geVec3d_DotProduct(&(verts[j]), &uVec);
			V = geVec3d_DotProduct(&(verts[j]), &vVec);
			U += (TVecs->uOffset / txSize);
			V -= (TVecs->vOffset / tySize);

			fprintf(WriteScene_TXT, "UV = %f %f\n", U,V);
			App->CLSB_Model->B_Brush[App->CLSB_Model->BrushCount]->MapCord_Data[UVIndex].u = U;
			App->CLSB_Model->B_Brush[App->CLSB_Model->BrushCount]->MapCord_Data[UVIndex].v = V;
			UVIndex++;
		}
	}

	int FaceIndex = 0;
	// -----------------------------------  Faces
	fprintf(WriteScene_TXT, "# Number of Faces = %i \n", num_faces);
	App->CLSB_Model->B_Brush[App->CLSB_Model->BrushCount]->Face_Count = num_faces;
	App->CLSB_Model->B_Brush[App->CLSB_Model->BrushCount]->Face_Data.resize(num_faces);
	num_verts = 0;
	for (i = 0; i < pList->NumFaces; i++)
	{
		curnum_verts = Face_GetNumPoints(pList->Faces[i]);
		for (j = 0; j < curnum_verts - 2; j++)
		{
			fprintf(WriteScene_TXT, "F = %i %i %i\n", num_verts, num_verts + 2 + j, num_verts + 1 + j);
			App->CLSB_Model->B_Brush[App->CLSB_Model->BrushCount]->Face_Data[FaceIndex].a = num_verts;
			App->CLSB_Model->B_Brush[App->CLSB_Model->BrushCount]->Face_Data[FaceIndex].b = num_verts + 2 + j;
			App->CLSB_Model->B_Brush[App->CLSB_Model->BrushCount]->Face_Data[FaceIndex].c = num_verts + 1 + j;

			FaceIndex++;
		}

		num_verts += curnum_verts;
	}

	// -----------------------------------  Texture IDs
	App->CLSB_Model->B_Brush[App->CLSB_Model->BrushCount]->TextID_Data.resize(200);
	for (i = 0; i < pList->NumFaces; i++)
	{
		if (!matf[i])
		{
			matf[i] = 1;

			int curnum_faces = (Face_GetNumPoints(pList->Faces[i]) - 2);

			for (j = i + 1; j < pList->NumFaces; j++)
			{
				if (strcmp(Face_GetTextureName(pList->Faces[i]), Face_GetTextureName(pList->Faces[j])) == 0)
				{
					curnum_faces += (Face_GetNumPoints(pList->Faces[j]) - 2);
				}
			}

			strncpy(matname, Face_GetTextureName(pList->Faces[i]), 11);
			
			// Material Name
			int DibId =Get_Adjusted_Index(Face_GetTextureDibId(pList->Faces[i]));
			fprintf(WriteScene_TXT, "MT = %i %s %i\n", i, matname, DibId);
			
			// write number of faces that have this texture
			fprintf(WriteScene_TXT, "# Number of Faces = %i \n", curnum_faces);

			// write face numbers
			curnum_faces = 0;
			for (j = 0; j < i; j++)
			{
				curnum_faces += (Face_GetNumPoints(pList->Faces[j]) - 2);
			}

			curnum_verts = Face_GetNumPoints(pList->Faces[i]);
			for (j = 0; j < curnum_verts - 2; j++)
			{
				int DibId2 = Get_Adjusted_Index(Face_GetTextureDibId(pList->Faces[i]));
				App->CLSB_Model->B_Brush[App->CLSB_Model->BrushCount]->TextID_Data[curnum_faces + j].ID = DibId2;
				fprintf(WriteScene_TXT, "FN %i %i\n", curnum_faces + j, DibId2);
			
			}

			curnum_faces += (curnum_verts - 2);

			for (j = i + 1; j < pList->NumFaces; j++)
			{
				curnum_verts = Face_GetNumPoints(pList->Faces[j]);
				if (strcmp(Face_GetTextureName(pList->Faces[i]), Face_GetTextureName(pList->Faces[j])) == 0)
				{
					matf[j] = 1;
					for (k = 0; k < curnum_verts - 2; k++)
					{
						int DibId2 = Get_Adjusted_Index(Face_GetTextureDibId(pList->Faces[i]));
						App->CLSB_Model->B_Brush[App->CLSB_Model->BrushCount]->TextID_Data[curnum_faces+k].ID = DibId2;
						fprintf(WriteScene_TXT, "FN = %i %i\n", curnum_faces + k, DibId2);
			
					}
				}

				curnum_faces += (curnum_verts - 2);
			}
		}
	}


	fprintf(WriteScene_TXT, "%s\n","-----------------------");
	int poo = 0;
	while (poo < num_faces)
	{
		int dd = App->CLSB_Model->B_Brush[App->CLSB_Model->BrushCount]->TextID_Data[poo].ID;
		fprintf(WriteScene_TXT, "DN = %i\n", dd);
		poo++;
	}
	fprintf(WriteScene_TXT, "%s\n", "-----------------------");


	free(matf);

	App->CLSB_Model->BrushCount++;
	
	return GE_TRUE;
}

// *************************************************************************
// *							Get_Adjusted_Index						   *
// *************************************************************************
int SB_Export_World::Get_Adjusted_Index(int RealIndex)
{
	int Count = 0;
	while (Count < 500)
	{
		if (AdjusedIndex_Store[Count] == RealIndex)
		{
			return Count;
		}

		Count++;
	}

	return -1;
}

// *************************************************************************
// *			AddTexture_GL:- Terry and Hazel Flanigan 2023		  	   *
// *************************************************************************
bool SB_Export_World::AddTexture_GL(geVFile* BaseFile, const char* TextureName, int GroupIndex)
{
	App->Get_Current_Document();

	HWND	PreviewWnd;
	HBITMAP	hbm;
	HDC		hDC;

	geBitmap* Bitmap = NULL;
	CWadFile* pWad;
	pWad = NULL;
	pWad = Level_GetWadFile(App->m_pDoc->pLevel);
	for (int index = 0; index < pWad->mBitmapCount; index++)
	{
		char mName[MAX_PATH];

		CString Name = pWad->mBitmaps[index].Name;
		strcpy(mName, Name);

		bool test = strcmp(mName, TextureName);
		if (test == 0)
		{
			Bitmap = pWad->mBitmaps[index].bmp;

			char TempTextureFile_BMP[MAX_PATH];
			strcpy(TempTextureFile_BMP, App->WorldEditor_Directory);
			strcat(TempTextureFile_BMP, "\\");
			strcat(TempTextureFile_BMP, "TextureLoad.bmp");

			App->CLSB_Textures->Genesis_WriteToBmp(Bitmap, TempTextureFile_BMP);

			App->CLSB_Textures->Soil_Load_Texture(App->CLSB_Ogre->RenderListener->g_BrushTexture, TempTextureFile_BMP, GroupIndex);

			DeleteFile((LPCTSTR)TempTextureFile_BMP);
		}
	}

	return TRUE;
}
