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
#include "A_File.h"

//#include "level.h"
#include "EntTypeName.h"
#include "EntView.h"
#include "units.h"
#include "util.h"
#include "FUSIONView.h"

struct tag_BrushList
{
	Brush* First;
	Brush* Last;
};

#define NUM_VIEWS (4)
struct tag_Level
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

SB_File_WE::SB_File_WE(void)
{
	FileName_3dt[0] = 0;
	PathFileName_3dt[0] = 0;

	Quick_load_Flag = 0;
}

SB_File_WE::~SB_File_WE(void)
{
}

typedef struct
{
	CFusionDoc *pDoc;
	Level *NewLevel;
} fdocAddPremadeData;


// *************************************************************************
// * 			( Static in Class )	fdocSetEntityVisibility				   *
// *************************************************************************
static geBoolean fdocSetEntityVisibility (CEntity &Ent, void *lParam)
{
	EntityViewEntry *pEntry = (EntityViewEntry *)lParam;

	if (Ent.GetClassname () == pEntry->pName)
	{
		Ent.SetVisible (pEntry->IsVisible);
	}
	return GE_TRUE;
}

// *************************************************************************
// *			Open_Dialog:- Terry and Hazel Flanigan 2023				   *
// *************************************************************************
bool SB_File_WE::Open_Dialog()
{
	bool test = Open_File_Dialog("World File   **.3dt\0*.3dt\0", " Open World File", NULL);
	if (test == 0)
	{
		return 0;
	}

	return 1;
}

// *************************************************************************
// *			Start_Load:- Terry and Hazel Flanigan 2023 				   *
// *************************************************************************
bool SB_File_WE::Start_Load(const char* FileName, bool UseDialogLoader)
{
	//MessageBox(NULL, "New Load", "ME Know Also", MB_OK);

	App->Get_Current_Document();

	// Check Old File is not Modified
	if (App->m_pDoc && (App->m_pDoc->IsModified() == TRUE))
	{
		char Text[200];
		strcpy(Text, "Save Changes To ");
		strcat(Text, App->CL_World->mCurrent_3DT_File);

		App->CLSB_Dialogs->YesNoCancel("File has been Modified",Text);

		if (App->CLSB_Dialogs->YesNoCancel_Result == 1)
		{
			Save_Document();
		}

		if (App->CLSB_Dialogs->YesNoCancel_Result == 2)
		{
		}

		if (App->CLSB_Dialogs->YesNoCancel_Result == 3)
		{
			return 0;
		}
	}

	if (UseDialogLoader == 1)
	{
		bool test = Open_Dialog();
		if (test == 0)
		{
			return 0;
		}
	}

	// Select All
	App->CLSB_Doc->SelectAll();
	App->CLSB_Doc->UpdateAllViews(UAV_ALL3DVIEWS, NULL);
	App->CL_TabsGroups_Dlg->Update_Dlg_SelectedBrushesCount();

	// Delete All Bruses and Faces
	App->CLSB_Doc->DeleteCurrentThing();
	
	App->m_pDoc->SetTitle(" ");

	bool Test = Open_3dt_File();
	if (Test == 1)
	{
		App->CL_World->Reset_Editor();

		App->CLSB_Camera_WE->Reset_Camera_Position();
		App->CLSB_Camera_WE->Reset_Camera_Angles();

		Reset_View(1.0);

		App->CLSB_Doc->IsNewDocument = 0;
		App->m_pDoc->SetModifiedFlag(FALSE);

		App->CLSB_TopTabs->Update_Dlg_Controls();

		App->CLSB_Level->Check_For_Centre_Brush(); // Centre Brush XYZ

		App->CLSB_Doc->Lock_AllTextures();
		
		App->Say("Loaded", PathFileName_3dt);
	}
	else
	{
		App->Say("Can not Open File", PathFileName_3dt);
	}

	
	return 1;
}

// *************************************************************************
// *			Open_3dt_File:- Terry and Hazel Flanigan 2023			   *
// *************************************************************************
bool SB_File_WE::Open_3dt_File()
{
	Load_File(PathFileName_3dt);

	App->m_pDoc->SetTitle(PathFileName_3dt);
	App->m_pDoc->SetPathName(PathFileName_3dt, FALSE);

	App->CL_World->Set_Paths();

	if (Quick_load_Flag == 0)
	{
		App->CL_TextureDialog->Fill_ListBox();
	}
	else
	{
		char Txlpath[MAX_PATH];
		strcpy(Txlpath, App->WorldEditor_Directory);
		strcat(Txlpath, "Levels\\First_Project_Prj\\Equity.txl");

		Level_SetWadPath(App->CLSB_Doc->pLevel, Txlpath);
		App->CL_World->Set_Current_TxlPath();
		App->m_pDoc->UpdateAfterWadChange();
		App->CL_TextureDialog->Fill_ListBox();

		strcpy(App->CL_World->mCurrent_TXL_FileName, Txlpath);

	}

	App->CLSB_Level->Check_For_Centre_Brush(); // Centre Brush XYZ
	App->CLSB_Level->Check_For_Centre_Texture(); // Centre Texture Dummy

	App->CL_TabsGroups_Dlg->Fill_ListBox();

	App->CLSB_Level->Change_Centre_Brush_Texture();

	App->CL_World->Set_Paths();
	App->CL_World->Reset_Editor();

	App->CLSB_RecentFiles->RecentFile_Files_Update();

	return 1;
}



// *************************************************************************
// *								Load_File 							   *
// *************************************************************************
bool SB_File_WE::Load_File(const char *FileName)
{

	App->Get_Current_Document();
	
	const char		*Errmsg, *WadPath;
	int				i;
	Level			*NewLevel;
	EntityViewList	*pEntityView;
	const Prefs *pPrefs = App->m_pDoc->GetPrefs ();

	/*char WorkingDir[MAX_PATH];
	FilePath_GetDriveAndDir(FileName, WorkingDir);
	::SetCurrentDirectory(WorkingDir);*/
	
	bool Test = NewLevel = Level_CreateFromFile (FileName, &Errmsg, Prefs_GetHeadersList (pPrefs),
		Prefs_GetActorsList(pPrefs), Prefs_GetPawnIni(pPrefs));

	if (NewLevel == NULL)
	{
		goto LoadError;
	}

	// get fully-qualified path name to texture library
	WadPath = Level_GetWadPath (NewLevel);

	if (!Level_LoadWad (NewLevel))
	{
		App->Say("Can not open TXL File");
	}

	Level_EnumLeafBrushes (NewLevel, NewLevel, Level_FaceFixupCallback);

	if (App->CLSB_Doc->pLevel != NULL)
	{
		Level_Destroy (&App->CLSB_Doc->pLevel);
	}

	App->CLSB_Doc->pLevel = NewLevel;

	// Validate data, groups are read after entities and brushes, so this must be last
	if(App->m_pDoc->ValidateEntities( ) == FALSE || App->m_pDoc->ValidateBrushes( ) == FALSE )
	{
		//m_pDoc->SelectTab( m_pDoc->CONSOLE_TAB ) ;
		App->Say("Can not open Validate Brushes");
	}

	GroupIterator gi;
	GroupListType *Groups;
	
	Groups = Level_GetGroups (App->CLSB_Doc->pLevel);
	App->CLSB_Doc->mCurrentGroup = Group_GetFirstId (Groups, &gi);
	{
		Brush *pBox = BrushTemplate_CreateBox (Level_GetBoxTemplate (App->CLSB_Doc->pLevel));
		if (pBox != NULL)
		{
			CreateNewTemplateBrush(pBox);
		}
		else
		{
			App->Say("Error");
		}
	}

	// update entity visibility info
	pEntityView	=Level_GetEntityVisibilityInfo (App->CLSB_Doc->pLevel);
	for (i = 0; i < pEntityView->nEntries; ++i)
	{
		Level_EnumEntities (App->CLSB_Doc->pLevel, &pEntityView->pEntries[i], ::fdocSetEntityVisibility);
	}

	
	AddCameraEntityToLevel();

	App->m_pDoc->DoGeneralSelect();

	return GE_TRUE;
LoadError:
	if (NewLevel != NULL)
	{
		Level_Destroy (&NewLevel);
	}

	App->Say("Error Loading File");
	return GE_FALSE;
}

// *************************************************************************
// * 						CreateNewTemplateBrush						   *
// *************************************************************************
void SB_File_WE::CreateNewTemplateBrush(Brush *pBrush)
{
	geVec3d *pTemplatePos;
	geVec3d MoveVec;
	geVec3d BrushPos;

	assert (pBrush != NULL);

	if (App->m_pDoc->BTemplate != NULL)
	{
		Brush_Destroy (&App->m_pDoc->BTemplate);
	}

	App->m_pDoc->BTemplate = pBrush;
	App->m_pDoc->CurBrush = pBrush;

	App->m_pDoc->TempEnt	= FALSE;
	App->m_pDoc->SetDefaultBrushTexInfo (App->m_pDoc->CurBrush);
	Brush_Bound (App->m_pDoc->CurBrush);
	Brush_Center (App->m_pDoc->CurBrush, &BrushPos);

	pTemplatePos = Level_GetTemplatePos (App->CLSB_Doc->pLevel);
	geVec3d_Subtract (pTemplatePos, &BrushPos, &MoveVec);
	Brush_Move (App->m_pDoc->CurBrush, &MoveVec);

	App->CLSB_Doc->UpdateAllViews (UAV_ALL3DVIEWS, NULL);
	App->m_pDoc->SetModifiedFlag ();
}

// *************************************************************************
// * 						AddCameraEntityToLevel						   *
// *************************************************************************
void SB_File_WE::AddCameraEntityToLevel(void)
{
	CEntity* pCameraEntity = App->CLSB_Camera_WE->FindCameraEntity();
	if (!pCameraEntity)
	{
		// Make default camera entity
		CEntity CameraEntity ;
		CString cstr;

		App->m_pDoc->CreateEntityFromName( "Camera", CameraEntity ) ;
		cstr.LoadString( IDS_CAMERAENTITYNAME ) ;
		CameraEntity.SetKeyValue ("%name%", cstr );
		CameraEntity.SetOrigin ( 0.0f, 0.0f, 0.0f, Level_GetEntityDefs (App->CLSB_Doc->pLevel) );
		Level_AddEntity (App->CLSB_Doc->pLevel, CameraEntity);
	}

	//AddZeroEntityToLevel();
}

// *************************************************************************
// * 						AddZeroEntityToLevel						   *
// *************************************************************************
void SB_File_WE::AddZeroEntityToLevel(void)
{
	//CEntity* pCameraEntity = App->CLSB_Camera_WE->FindCameraEntity();
	//if (!pCameraEntity)
	{
		// Make default camera entity
		CEntity ZeroEntity;
		CString cstr;

		App->m_pDoc->CreateEntityFromName("Zero", ZeroEntity);
		cstr.LoadString(IDS_CAMERAENTITYNAME);
		ZeroEntity.SetKeyValue("%name%", "Zero");
		ZeroEntity.SetOrigin(0.0f, 0.0f, 0.0f, Level_GetEntityDefs(App->CLSB_Doc->pLevel));
		Level_AddEntity(App->CLSB_Doc->pLevel, ZeroEntity);
	}
}

// *************************************************************************
// * 			( Static in Class )	fdocAddPremadeEntity				   *
// *************************************************************************
static geBoolean fdocAddPremadeEntity (CEntity &Ent, void *lParam)
{
	fdocAddPremadeData *pData;
	CEntityArray *Entities;
	CEntity *NewEnt;
	int Index;

	if (!(Ent.IsCamera()))
	{
	pData = (fdocAddPremadeData *)lParam;

	Index = Level_AddEntity (App->CLSB_Doc->pLevel, Ent);
	Entities = Level_GetEntities (App->CLSB_Doc->pLevel);
	NewEnt = &((*Entities)[Index]);

	pData->pDoc->SelectEntity (NewEnt);
	}

	return GE_TRUE;
}


// *************************************************************************
// * 							ImportFile								   *
// *************************************************************************
bool SB_File_WE::ImportFile (const char *PathName, const geVec3d *location)
{
	//Debug
	App->m_pDoc = (CFusionDoc*)App->m_pMainFrame->GetCurrentDoc();

	App->m_pDoc->SetModifiedFlag();

	SetCursor(AfxGetApp()->LoadStandardCursor(IDC_WAIT));

	const char		*ErrMsg = "#ERROR#";
	Level			*NewLevel;
	EntityViewList	*pEntityView;
	int				i;
	const Prefs *pPrefs = App->m_pDoc->GetPrefs ();

	NewLevel = Level_CreateFromFile(PathName, &ErrMsg, Prefs_GetHeadersList (pPrefs),Prefs_GetActorsList (pPrefs), Prefs_GetPawnIni (pPrefs));

	if (NewLevel == NULL)
	{
		SetCursor(AfxGetApp()->LoadStandardCursor(IDC_ARROW));
		AfxMessageBox (ErrMsg, MB_OK + MB_ICONERROR);
		return GE_FALSE;
	}

	// Unselects everything so that brushes/entities can be added
	App->CLSB_Doc->ResetAllSelections ();

	// move the object to the new position
	Level_TranslateAll (NewLevel, location);

	{
		// copy any groups (except default...)
		int GroupId;
		GroupListType *NewGroups;
		GroupListType *OldGroups;
		GroupIterator gi;

		OldGroups = Level_GetGroups (App->CLSB_Doc->pLevel);
		NewGroups = Level_GetGroups (NewLevel);

		Level_CollapseGroups (App->CLSB_Doc->pLevel, 1);
		Level_CollapseGroups (NewLevel, Group_GetCount (OldGroups));

		GroupId = Group_GetFirstId (NewGroups, &gi);
		while (GroupId != NO_MORE_GROUPS)
		{
			if (GroupId != 0)	// don't add default group
			{
				Group *pGroup;
				Group *NewGroup;
				char GroupName[MAX_PATH];

				pGroup = GroupList_GetFromId (NewGroups, GroupId);
				strcpy (GroupName, Group_GetName (pGroup));

				// make sure that group name doesn't conflict
				while (Group_GetIdFromName (OldGroups, GroupName) != NO_MORE_GROUPS)
				{
					strcat (GroupName, "x");
				}

				NewGroup = Group_Clone (pGroup);
				Group_SetGroupName (NewGroup, GroupName);

				GroupList_Add (OldGroups, NewGroup);
			}
			GroupId = Group_GetNextId (NewGroups, &gi);
		}
	}

	{
		// copy models
		ModelList *NewModels, *OldModels;
		ModelIterator mi;
		Model *pModel;

		OldModels = Level_GetModelInfo (App->CLSB_Doc->pLevel)->Models;
		NewModels = Level_GetModelInfo (NewLevel)->Models;

		Level_CollapseModels (App->CLSB_Doc->pLevel, 1);
		Level_CollapseModels (NewLevel, ModelList_GetCount (OldModels) + 1);

		pModel = ModelList_GetFirst (NewModels, &mi);
		while (pModel != NULL)
		{
			Model *NewModel;
			char ModelName[MAX_PATH];

			// make sure names don't clash
			strcpy (ModelName, Model_GetName (pModel));
			while (ModelList_FindByName (OldModels, ModelName) != NULL)
			{
				strcat (ModelName, "x");
			}
			NewModel = Model_Clone (pModel);
			Model_SetName (NewModel, ModelName);
			ModelList_AddModel (OldModels, NewModel);

			pModel = ModelList_GetNext (NewModels, &mi);
		}
	}

	{
		fdocAddPremadeData AddPremadeData;

		AddPremadeData.pDoc = App->m_pDoc;//this;
		AddPremadeData.NewLevel = NewLevel;
		//changed QD Actors
		CEntityArray *Entities;

		Entities = Level_GetEntities (NewLevel);

		for(i=0;i < Entities->GetSize();i++)
		{
			Brush *pBrush = (*Entities)[i].GetActorBrush();

			if(pBrush!=NULL)
			{
				SelBrushList_Remove(App->m_pDoc->pSelBrushes, pBrush);
				Level_RemoveBrush(NewLevel, pBrush);
				(*Entities)[i].DeleteActorBrush();
			}
		}
		// end change
		// add entities
		Level_EnumEntities (NewLevel, &AddPremadeData, ::fdocAddPremadeEntity);
	}

	{
		// add brushes
		Brush *pBrush, *NewBrush;
		BrushList *NewBrushes;
		BrushIterator bi;

		// fixup DIB ids on brush faces
		Level_EnumLeafBrushes (NewLevel, App->CLSB_Doc->pLevel, Level_FaceFixupCallback);

		// Move brushes from loaded level to doc's level
		NewBrushes = Level_GetBrushes (NewLevel);
		pBrush = BrushList_GetFirst (NewBrushes, &bi);
		while (pBrush != NULL)
		{
			NewBrush = pBrush;
			pBrush = BrushList_GetNext (&bi);
			Level_RemoveBrush (NewLevel, NewBrush);
			Level_AppendBrush (App->CLSB_Doc->pLevel, NewBrush);
		}
	}

	// update entity visibility info
	pEntityView	=Level_GetEntityVisibilityInfo (App->CLSB_Doc->pLevel);
	for (i = 0; i < pEntityView->nEntries; ++i)
	{
		Level_EnumEntities (App->CLSB_Doc->pLevel, &pEntityView->pEntries[i], ::fdocSetEntityVisibility);
	}

	Level_Destroy (&NewLevel);

	SetCursor(AfxGetApp()->LoadStandardCursor(IDC_ARROW));

	return 1;
}

// *************************************************************************
// * 			( Static in Class )	Level_BrushListToTexels				   *
// *************************************************************************
static void Level_BrushListToTexels(Level *pLevel)
{
	int				i;
	Brush			*cb;
	BrushIterator	bi;
	Face			*f;
	geFloat			uscale, vscale;

	cb = BrushList_GetFirst (pLevel->Brushes, &bi);
	while (cb != NULL)
	{
		for(i=0;i < Brush_GetNumFaces(cb);i++)
		{
			f	=Brush_GetFace(cb, i);
			Face_GetTextureScale(f, &uscale, &vscale);
			Face_SetTextureScale(f, CENTIMETERS_TO_ENGINE(uscale), CENTIMETERS_TO_ENGINE(vscale));
		}
		cb = BrushList_GetNext (&bi);
	}
}

// *************************************************************************
// * 						Level_CreateFromFile						   *
// *************************************************************************
Level* SB_File_WE::Level_CreateFromFile (const char *FileName, const char **ErrMsg, const char *DefaultHeadersDir,const char *DefaultActorsDir, const char *DefaultPawnIni)
{
	int NumModels;
	int VersionMajor, VersionMinor;
	int NumGroups = 0;
	int NumBrushes = 0;
	int NumEntities;
	Parse3dt *Parser;
	const char *Expected = "!*ERROR*!";
	int k;
	Level *pLevel = NULL;
	char WadPath[MAX_PATH];
	char HeadersDir[MAX_PATH];

	char ActorsDir[MAX_PATH];
	char PawnIniPath[MAX_PATH];


	assert (FileName != NULL);

	Parser = Parse3dt_Create (FileName);
	if (Parser == NULL)
	{
		*ErrMsg = "Can't open file";
		return NULL;
	}

	Expected = "3dtVersion";
	if (!Parse3dt_GetVersion (Parser, &VersionMajor, &VersionMinor)) goto DoneLoad;

	if(VersionMajor > LEVEL_VERSION_MAJOR)
	{
		*ErrMsg = "Version mismatch.";
		return NULL ;
	}

	if	(VersionMajor <= 1 && VersionMinor < 16)
	{
		char	PalPath[_MAX_PATH];

		if (!Parse3dt_GetPath (Parser, (Expected = "PalLoc"), PalPath)) goto DoneLoad;
	}

	// texture library path
	if ((VersionMajor <= 1) && (VersionMinor < 18))
	{
		if (!Parse3dt_GetPath (Parser, (Expected = "WadLoc"), WadPath)) goto DoneLoad;
	}
	else
	{
		if (!Parse3dt_GetLiteral(Parser, (Expected = "TextureLib"), WadPath))
		{
			goto DoneLoad;
		}

		char m_FileName[MAX_PATH];
		strcpy(m_FileName, FileName);

		bool test = Resolve_TXL_File(WadPath, m_FileName);
		if (test == 0)
		{
			goto DoneLoad;
		}

	}

	// headers directory
	if ((VersionMajor <= 1) && (VersionMinor < 31))
	{
		strcpy (HeadersDir, DefaultHeadersDir);
	}
	else
	{
		if (!Parse3dt_GetLiteral (Parser, (Expected = "HeadersDir"), HeadersDir)) goto DoneLoad;
	}
// changed QD Actors
	// actors directory
	if ((VersionMajor <= 1) && (VersionMinor < 33))
	{
		strcpy (ActorsDir, DefaultActorsDir);
	}
	else
	{
		if (!Parse3dt_GetLiteral (Parser, (Expected = "ActorsDir"), ActorsDir)) goto DoneLoad;
	}
	// PawnIni
	if ((VersionMajor <= 1) && (VersionMinor < 33))
	{
		strcpy (PawnIniPath, DefaultPawnIni);
	}
	else
	{
		if (!Parse3dt_GetLiteral (Parser, (Expected = "PawnIni"), PawnIniPath)) goto DoneLoad;
	}

	pLevel = Level_Create (WadPath, HeadersDir, ActorsDir, PawnIniPath);
// end change
	if (pLevel == NULL)
	{
		*ErrMsg = "Error creating level.";
		return NULL;
	}


	if ((VersionMajor == 1) && (VersionMinor < 15))
	{
		if (!Parse3dt_GetInt  (Parser, (Expected = "NumBrushes"), &NumBrushes)) goto DoneLoad;
	}
	if (!Parse3dt_GetInt  (Parser, (Expected = "NumEntities"), &NumEntities)) goto DoneLoad;
	if (!Parse3dt_GetInt  (Parser, (Expected = "NumModels"), &NumModels)) goto DoneLoad;

	if ((VersionMajor > 1) || ((VersionMajor == 1) && (VersionMinor >= 3)))
	{
		if (!Parse3dt_GetInt (Parser, (Expected = "NumGroups"), &NumGroups)) goto DoneLoad;
	}


	if ((VersionMajor == 1) && (VersionMinor < 15))
	{
		for (k = 0; k < NumBrushes; k++)
		{
			Brush *pBrush;

			pBrush	=Brush_CreateFromFile(Parser, VersionMajor, VersionMinor, &Expected);
			if (pBrush == NULL) goto DoneLoad;
			BrushList_Append (pLevel->Brushes, pBrush);
			
		}
	}
	else
	{
		if (pLevel->Brushes != NULL)
		{
			BrushList_Destroy (&pLevel->Brushes);
		}

		pLevel->Brushes = BrushList_CreateFromFile (Parser, VersionMajor, VersionMinor, &Expected);
		if (pLevel->Brushes == NULL)
			goto DoneLoad;
	}

	if((VersionMajor > 1) || ((VersionMajor == 1) && (VersionMinor < 6)))
	{
		Level_BrushListToTexels (pLevel);
	}

	// collapse model list so numbers are consecutive
	Level_CollapseModels (pLevel, 1);

	goto AllDone;

DoneLoad:
	*ErrMsg = Parse3dt_Error (Parser, "Expected %s", Expected);

//DoneLoad1:
	if (pLevel != NULL)
	{
		Level_Destroy (&pLevel);
	}

AllDone:
	if (Parser != NULL)
	{
		Parse3dt_Destroy (&Parser);
	}

	//fixup hollows
	if(pLevel != NULL)
	{
		BrushList_MakeHollowsMulti(pLevel->Brushes);
	}

	return pLevel;
}

// *************************************************************************
// *		Resolve_TXL_File:- Terry and Hazel Flanigan 2023			   *
// *************************************************************************
bool SB_File_WE::Resolve_TXL_File(char* WadPath, char* FileName)
{
	// Check Folder in file if not check Level Folder
	bool test = App->CLSB_FileIO->Check_File_Exist(WadPath);
	if (test == 0)
	{
		char m_NewPath[MAX_PATH];
		char m_3DT_PathAndFile[MAX_PATH];

		char m_Txl_FileName[MAX_PATH];
		char m_3DT_FileName[MAX_PATH];

		strcpy(m_3DT_PathAndFile, FileName);
		App->CL_World->Get_FileName_FromPath(m_3DT_PathAndFile, m_3DT_PathAndFile);
		strcpy(m_3DT_FileName, App->CL_World->JustFileName);

		int len1 = strlen(m_3DT_FileName);
		int len2 = strlen(m_3DT_PathAndFile);
		strcpy(m_NewPath, FileName);
		m_NewPath[len2 - len1] = 0;

		App->CL_World->Get_FileName_FromPath(WadPath, WadPath);

		strcpy(m_Txl_FileName, App->CL_World->JustFileName);
		strcat(m_NewPath, m_Txl_FileName);

		bool test = App->CLSB_FileIO->Check_File_Exist(m_NewPath);
		if (test == 0)
		{
			App->Say("Cant Find Txl File in 3dt Folder");
			return 0;
		}
		else
		{
			strcpy(WadPath, m_NewPath);
		}

		return 1;
	}

	return 1;
}

// *************************************************************************
// *		Open_File_Dialog:- Terry and Hazel Flanigan 2023			   *
// *************************************************************************
bool SB_File_WE::Open_File_Dialog(char* Extension, char* Title, char* StartDirectory)
{
	FileName_3dt[0] = 0;
	PathFileName_3dt[0] = 0;

	OPENFILENAME ofn;

	ZeroMemory(&ofn, sizeof(ofn));
	ofn.lStructSize = sizeof(ofn);
	ofn.hwndOwner = App->MainHwnd;
	ofn.hInstance = App->hInst;
	ofn.lpstrFile = PathFileName_3dt;						// full path and file name
	ofn.nMaxFile = sizeof(PathFileName_3dt);
	ofn.lpstrFilter = Extension;

	ofn.nFilterIndex = 1;
	ofn.lpstrFileTitle = FileName_3dt;						// Just File Name
	ofn.nMaxFileTitle = sizeof(FileName_3dt);;
	ofn.lpstrInitialDir = StartDirectory;
	ofn.lpstrTitle = Title;
	ofn.Flags = OFN_PATHMUSTEXIST |
		OFN_FILEMUSTEXIST |
		OFN_EXPLORER |
		OFN_HIDEREADONLY |
		OFN_FILEMUSTEXIST;

	if (GetOpenFileName(&ofn) == TRUE)
	{
		return 1;
	}

	return 0;
}

// *************************************************************************
// *	          Save_Document:- Terry and Hazel Flanigan 2023	           *
// *************************************************************************
void SB_File_WE::Save_Document()
{
	App->Get_Current_Document();

	if (App->CLSB_File_WE->Save(App->CL_World->mCurrent_3DT_PathAndFile) == GE_FALSE)
	{
		App->Say("Error: Unable to save file");
		return;;
	}

	App->CLSB_Doc->IsNewDocument = 0;
	App->m_pDoc->SetModifiedFlag(FALSE);

	App->Say("Saved", App->CL_World->mCurrent_3DT_PathAndFile);
}

// *************************************************************************
// *				Save:- Terry and Hazel Flanigan 2023				   *
// *************************************************************************
bool SB_File_WE::Save(const char* FileName)
{
	App->Get_Current_Document();

	// update view information in level
	ViewStateInfo* pViewStateInfo;
	POSITION		pos;
	CFusionView* pView;
	int iView;

	pos = App->m_pDoc->GetFirstViewPosition();
	while (pos != NULL)
	{
		pView = (CFusionView*)App->m_pDoc->GetNextView(pos);
		switch (Render_GetViewType(pView->VCam))
		{
		case VIEWSOLID:
		case VIEWTEXTURE:
		case VIEWWIRE:
			iView = 0;
			break;
		case VIEWTOP:
			iView = 1;
			break;
		case VIEWFRONT:
			iView = 2;
			break;
		case VIEWSIDE:
			iView = 3;
			break;
		default:
			iView = -1;
		}
		if (iView != -1)
		{
			pViewStateInfo = Level_GetViewStateInfo(App->CLSB_Doc->pLevel, iView);
			pViewStateInfo->IsValid = GE_TRUE;
			pViewStateInfo->ZoomFactor = Render_GetZoom(pView->VCam);
			Render_GetPitchRollYaw(pView->VCam, &pViewStateInfo->PitchRollYaw);
			Render_GetCameraPos(pView->VCam, &pViewStateInfo->CameraPos);
		}
	}

	// and then write the level info to the file
	return Level_WriteToFile2(App->CLSB_Doc->pLevel, FileName);
}

// *************************************************************************
// *		Level_WriteToFile2:- Terry and Hazel Flanigan 2023			   *
// *************************************************************************
bool SB_File_WE::Level_WriteToFile2(Level* pLevel, const char* Filename)
{
	FILE* ArFile;
	char QuotedString[MAX_PATH];
	geBoolean WriteRslt;

	assert(pLevel != NULL);
	assert(Filename != NULL);

	// error checking required!
	ArFile = fopen(Filename, "wt");

	if (ArFile == NULL)
	{
		return GE_FALSE;
	}

	WriteRslt = GE_FALSE;
	if (fprintf(ArFile, "3dtVersion %d.%d\n", LEVEL_VERSION_MAJOR, LEVEL_VERSION_MINOR) < 0) goto WriteDone;

	Util_QuoteString(App->CLSB_Doc->pLevel->WadPath, QuotedString);
	if (fprintf(ArFile, "TextureLib %s\n", QuotedString) < 0) goto WriteDone;

	Util_QuoteString(App->CLSB_Doc->pLevel->HeadersDir, QuotedString);
	if (fprintf(ArFile, "HeadersDir %s\n", QuotedString) < 0) goto WriteDone;

	// changed QD Actors
	Util_QuoteString(App->CLSB_Doc->pLevel->ActorsDir, QuotedString);
	if (fprintf(ArFile, "ActorsDir %s\n", QuotedString) < 0) goto WriteDone;

	Util_QuoteString(App->CLSB_Doc->pLevel->PawnIniPath, QuotedString);
	if (fprintf(ArFile, "PawnIni %s\n", QuotedString) < 0) goto WriteDone;
	// remove ActorBrushes from List, so they don't get written to the file
	int i;
	for (i = 0; i < App->CLSB_Doc->pLevel->Entities->GetSize(); ++i)
	{
		Brush* b = (*(App->CLSB_Doc->pLevel->Entities))[i].GetActorBrush();
		if (b != NULL)
			Level_RemoveBrush(App->CLSB_Doc->pLevel, b);
	}
	// end change

	if (fprintf(ArFile, "NumEntities %d\n", App->CLSB_Doc->pLevel->Entities->GetSize()) < 0) goto WriteDone;
	if (fprintf(ArFile, "NumModels %d\n", ModelList_GetCount(App->CLSB_Doc->pLevel->ModelInfo.Models)) < 0) goto WriteDone;
	if (fprintf(ArFile, "NumGroups %d\n", Group_GetCount(App->CLSB_Doc->pLevel->Groups)) < 0) goto WriteDone;
	if (BrushList_Write(App->CLSB_Doc->pLevel->Brushes, ArFile) == GE_FALSE) goto WriteDone;
	
	fprintf(ArFile, "Equity %s\n", "V1.1");
	// changed QD Actors
	// add ActorBrushes to the List again
	for (i = 0; i < App->CLSB_Doc->pLevel->Entities->GetSize(); ++i)
	{
		Brush* b = (*(App->CLSB_Doc->pLevel->Entities))[i].GetActorBrush();
		if (b != NULL)
			Level_AppendBrush(App->CLSB_Doc->pLevel, b);
	}
	// end change
	WriteRslt = GE_TRUE;

WriteDone:

	char path[MAX_PATH];
	strcpy(path, Filename);

	if (fclose(ArFile) != 0)
	{
		App->Say("Error Cant Save File", path);
		return GE_FALSE;
	}

	return GE_TRUE;
}

// *************************************************************************
// *			Reset_View:- Terry and Hazel Flanigan 2023				   *
// *************************************************************************
void SB_File_WE::Reset_View(float Zoom)
{
	App->Get_Current_Document();

	CView* pAView = NULL;
	CFusionView* pView;

	POSITION		pos;
	pos = App->m_pDoc->GetFirstViewPosition();
	pView = (CFusionView*)App->m_pDoc->GetNextView(pos);
	Render_SetZoom(pView->VCam, Zoom);
	pView->OnViewportCenteroncamera();

	pView = (CFusionView*)App->m_pDoc->GetNextView(pos);
	Render_SetZoom(pView->VCam, Zoom);
	pView->OnViewportCenteroncamera();

	pView = (CFusionView*)App->m_pDoc->GetNextView(pos);
	Render_SetZoom(pView->VCam, Zoom);
	pView->OnViewportCenteroncamera();
}

// *************************************************************************
// *			New_File:- Terry and Hazel Flanigan 2023				   *
// *************************************************************************
bool SB_File_WE::New_File()
{
	App->Get_Current_Document();

	App->CLSB_Doc->SelectAll();
	App->CLSB_Doc->UpdateAllViews(UAV_ALL3DVIEWS, NULL);
	App->CL_TabsGroups_Dlg->Update_Dlg_SelectedBrushesCount();

	// Delete All Bruses and Faces
	App->CLSB_Doc->DeleteCurrentThing();

	App->m_pDoc->SetTitle("X");

	const char* DefaultWadName;
	const Prefs* pPrefs = App->m_pDoc->GetPrefs();

	App->m_pDoc->LastTemplateTypeName = "Box";

	DefaultWadName = Prefs_GetTxlName(pPrefs);

	strcpy(App->m_pDoc->LastPath, Prefs_GetProjectDir(pPrefs));
	
	const char* WadPath = App->m_pDoc->FindTextureLibrary(DefaultWadName);

	//App->m_pDoc->pLevel = Level_Create(WadPath, Prefs_GetHeadersList(pPrefs),
		//Prefs_GetActorsList(pPrefs), Prefs_GetPawnIni(pPrefs));


	if (!Level_LoadWad(App->CLSB_Doc->pLevel))
	{
		CString Msg;

		AfxFormatString1(Msg, IDS_CANTLOADTXL, WadPath);
		AfxMessageBox(Msg, MB_OK + MB_ICONERROR);
	}


	App->m_pDoc->pSelBrushes = SelBrushList_Create();
	App->CLSB_Doc->pTempSelBrushes = SelBrushList_Create();
	App->m_pDoc->pSelFaces = SelFaceList_Create();

	App->m_pDoc->SetLockAxis(0);	// Start with no axis locked

	{
		BrushTemplate_Box* pBoxTemplate;
		pBoxTemplate = Level_GetBoxTemplate(App->CLSB_Doc->pLevel);

		App->m_pDoc->BTemplate = BrushTemplate_CreateBox(pBoxTemplate);
	}

	Brush_Bound(App->m_pDoc->BTemplate);
	App->m_pDoc->CurBrush = App->m_pDoc->BTemplate;

	geVec3d_Clear(&App->CLSB_Doc->SelectedGeoCenter);

	char PathAndFile[MAX_PATH];
	strcpy(PathAndFile, App->m_pDoc->LastPath);
	strcat(PathAndFile, "\\");
	strcat(PathAndFile, "New_File.3dt");

	App->m_pDoc->SetTitle("New_File.3dt");
	App->m_pDoc->SetPathName(PathAndFile, FALSE);

	App->CL_World->Set_Paths();

	App->CL_CreateBoxDialog->CreateDefault_TemplateCube();

	App->CL_TabsGroups_Dlg->Fill_ListBox();
	App->CL_TextureDialog->Fill_ListBox();

	App->CL_World->Set_Paths();
	App->CL_World->Reset_Editor();

	App->CLSB_Camera_WE->Reset_Camera_Position();
	App->CLSB_Camera_WE->Reset_Camera_Angles();

	Reset_View(1.0);

	App->CLSB_Doc->IsNewDocument = 0;
	App->m_pDoc->SetModifiedFlag(FALSE);

	//App->CL_CreateBoxDialog->CreateDefault_TemplateCube();
	
	App->Say("New Level Created", PathAndFile);

	return 1;
}

