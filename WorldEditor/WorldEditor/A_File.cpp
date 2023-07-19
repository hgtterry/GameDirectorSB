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
//#include "FilePath.h"

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

A_File::A_File(void)
{
	FileName_3dt[0] = 0;
	PathFileName_3dt[0] = 0;
}

A_File::~A_File(void)
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
// *			Open_3dt_File:- Terry and Hazel Flanigan 2023			   *
// *************************************************************************
bool A_File::Open_3dt_File(bool UseDialogLoader)
{
	
	m_pDoc = (CFusionDoc*)App->m_pMainFrame->GetCurrentDoc();

	if (UseDialogLoader == 1)
	{
		bool test = Open_File_Dialog("World File   **.3dt\0*.3dt\0", "World File", NULL);
		if (test == 0)
		{
			return 0;
		}
	}

	
	AfxGetApp()->OpenDocumentFile(PathFileName_3dt);

	App->CL_World->Set_Paths();
	App->CL_TabsGroups_Dlg->Fill_ListBox();
	App->CL_TextureDialog->Fill_ListBox();
	
	App->CLSB_RecentFiles->RecentFile_Files_Update();

	return 1;
}

// *************************************************************************
// *									Load 							   *
// *************************************************************************
bool A_File::Load(const char *FileName)
{
	m_pDoc = (CFusionDoc*)App->m_pMainFrame->GetCurrentDoc();

	//MessageBox(NULL,"ME Know","ME Know",MB_OK);
	
	const char		*Errmsg, *WadPath;
	int				i;
	Level			*NewLevel;
	EntityViewList	*pEntityView;
	const Prefs *pPrefs = m_pDoc->GetPrefs ();

	{
		//char WorkingDir[MAX_PATH];

		//FilePath_GetDriveAndDir (FileName, WorkingDir);
//		::SetCurrentDirectory (WorkingDir);
	}

// changed QD Actors
	NewLevel = Level_CreateFromFile (FileName, &Errmsg, Prefs_GetHeadersList (pPrefs),
		Prefs_GetActorsList(pPrefs), Prefs_GetPawnIni(pPrefs));
// end change
	if (NewLevel == NULL)
	{
		goto LoadError;
	}
	// get fully-qualified path name to texture library
	WadPath = Level_GetWadPath (NewLevel);

	if (!Level_LoadWad (NewLevel))
	{
		CString Msg;

		AfxFormatString1 (Msg, IDS_CANTLOADTXL, WadPath);
		AfxMessageBox (Msg, MB_OK + MB_ICONERROR);
	}
	Level_EnumLeafBrushes (NewLevel, NewLevel, Level_FaceFixupCallback);

	if (m_pDoc->pLevel != NULL)
	{
		Level_Destroy (&m_pDoc->pLevel);
	}

	m_pDoc->pLevel = NewLevel;
//	pCameraEntity = NULL;

	// Validate data, groups are read after entities and brushes, so this must be last
	if(m_pDoc->ValidateEntities( ) == FALSE || m_pDoc->ValidateBrushes( ) == FALSE )
	{
		//m_pDoc->SelectTab( m_pDoc->CONSOLE_TAB ) ;
		AfxMessageBox( IDS_LOAD_WARNING, MB_OK + MB_ICONERROR ) ;
	}

	GroupIterator gi;
	GroupListType *Groups;

	Groups = Level_GetGroups (m_pDoc->pLevel);
	m_pDoc->mCurrentGroup = Group_GetFirstId (Groups, &gi);

	{
		Brush *pBox = BrushTemplate_CreateBox (Level_GetBoxTemplate (m_pDoc->pLevel));
		if (pBox != NULL)
		{
			CreateNewTemplateBrush(pBox);
		}
	}

	// update entity visibility info
	pEntityView	=Level_GetEntityVisibilityInfo (m_pDoc->pLevel);
	for (i = 0; i < pEntityView->nEntries; ++i)
	{
		Level_EnumEntities (m_pDoc->pLevel, &pEntityView->pEntries[i], ::fdocSetEntityVisibility);
	}

	AddCameraEntityToLevel();

	m_pDoc->DoGeneralSelect();
	return GE_TRUE;
LoadError:
	if (NewLevel != NULL)
	{
		Level_Destroy (&NewLevel);
	}
	AfxMessageBox (Errmsg, MB_OK + MB_ICONERROR);
	return GE_FALSE;
}

// *************************************************************************
// * 						CreateNewTemplateBrush						   *
// *************************************************************************
void A_File::CreateNewTemplateBrush(Brush *pBrush)
{
	geVec3d *pTemplatePos;
	geVec3d MoveVec;
	geVec3d BrushPos;

	assert (pBrush != NULL);

	if (m_pDoc->BTemplate != NULL)
	{
		Brush_Destroy (&m_pDoc->BTemplate);
	}

	m_pDoc->BTemplate = pBrush;
	m_pDoc->CurBrush = pBrush;

	m_pDoc->TempEnt	= FALSE;
	m_pDoc->SetDefaultBrushTexInfo (m_pDoc->CurBrush);
	Brush_Bound (m_pDoc->CurBrush);
	Brush_Center (m_pDoc->CurBrush, &BrushPos);

	pTemplatePos = Level_GetTemplatePos (m_pDoc->pLevel);
	geVec3d_Subtract (pTemplatePos, &BrushPos, &MoveVec);
	Brush_Move (m_pDoc->CurBrush, &MoveVec);

	m_pDoc->UpdateAllViews (UAV_ALL3DVIEWS, NULL);
	m_pDoc->SetModifiedFlag ();
}

// *************************************************************************
// * 						AddCameraEntityToLevel						   *
// *************************************************************************
void A_File::AddCameraEntityToLevel(void)
{
	CEntity* pCameraEntity = m_pDoc->FindCameraEntity();
	if (!pCameraEntity)
	{
		// Make default camera entity
		CEntity CameraEntity ;
		CString cstr;

		m_pDoc->CreateEntityFromName( "Camera", CameraEntity ) ;
		cstr.LoadString( IDS_CAMERAENTITYNAME ) ;
		CameraEntity.SetKeyValue ("%name%", cstr );
		CameraEntity.SetOrigin ( 0.0f, 0.0f, 0.0f, Level_GetEntityDefs (m_pDoc->pLevel) );
		Level_AddEntity (m_pDoc->pLevel, CameraEntity);
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

	Index = Level_AddEntity (pData->pDoc->pLevel, Ent);
	Entities = Level_GetEntities (pData->pDoc->pLevel);
	NewEnt = &((*Entities)[Index]);

	pData->pDoc->SelectEntity (NewEnt);
	}

	return GE_TRUE;
}


// *************************************************************************
// * 							ImportFile								   *
// *************************************************************************
bool A_File::ImportFile (const char *PathName, const geVec3d *location)
{
	//Debug
	m_pDoc = (CFusionDoc*)App->m_pMainFrame->GetCurrentDoc();

	m_pDoc->SetModifiedFlag();

	SetCursor(AfxGetApp()->LoadStandardCursor(IDC_WAIT));

	const char		*ErrMsg = "#ERROR#";
	Level			*NewLevel;
	EntityViewList	*pEntityView;
	int				i;
	const Prefs *pPrefs = m_pDoc->GetPrefs ();

	NewLevel = Level_CreateFromFile(PathName, &ErrMsg, Prefs_GetHeadersList (pPrefs),Prefs_GetActorsList (pPrefs), Prefs_GetPawnIni (pPrefs));

	if (NewLevel == NULL)
	{
		SetCursor(AfxGetApp()->LoadStandardCursor(IDC_ARROW));
		AfxMessageBox (ErrMsg, MB_OK + MB_ICONERROR);
		return GE_FALSE;
	}

	// Unselects everything so that brushes/entities can be added
	m_pDoc->ResetAllSelections ();

	// move the object to the new position
	Level_TranslateAll (NewLevel, location);

	{
		// copy any groups (except default...)
		int GroupId;
		GroupListType *NewGroups;
		GroupListType *OldGroups;
		GroupIterator gi;

		OldGroups = Level_GetGroups (m_pDoc->pLevel);
		NewGroups = Level_GetGroups (NewLevel);

		Level_CollapseGroups (m_pDoc->pLevel, 1);
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

		OldModels = Level_GetModelInfo (m_pDoc->pLevel)->Models;
		NewModels = Level_GetModelInfo (NewLevel)->Models;

		Level_CollapseModels (m_pDoc->pLevel, 1);
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

		AddPremadeData.pDoc = m_pDoc;//this;
		AddPremadeData.NewLevel = NewLevel;
		//changed QD Actors
		CEntityArray *Entities;

		Entities = Level_GetEntities (NewLevel);

		for(i=0;i < Entities->GetSize();i++)
		{
			Brush *pBrush = (*Entities)[i].GetActorBrush();

			if(pBrush!=NULL)
			{
				SelBrushList_Remove(m_pDoc->pSelBrushes, pBrush);
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
		Level_EnumLeafBrushes (NewLevel, m_pDoc->pLevel, Level_FaceFixupCallback);

		// Move brushes from loaded level to doc's level
		NewBrushes = Level_GetBrushes (NewLevel);
		pBrush = BrushList_GetFirst (NewBrushes, &bi);
		while (pBrush != NULL)
		{
			NewBrush = pBrush;
			pBrush = BrushList_GetNext (&bi);
			Level_RemoveBrush (NewLevel, NewBrush);
			Level_AppendBrush (m_pDoc->pLevel, NewBrush);
		}
	}

	// update entity visibility info
	pEntityView	=Level_GetEntityVisibilityInfo (m_pDoc->pLevel);
	for (i = 0; i < pEntityView->nEntries; ++i)
	{
		Level_EnumEntities (m_pDoc->pLevel, &pEntityView->pEntries[i], ::fdocSetEntityVisibility);
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
Level* A_File::Level_CreateFromFile (const char *FileName, const char **ErrMsg, const char *DefaultHeadersDir,const char *DefaultActorsDir, const char *DefaultPawnIni)
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
		if (!Parse3dt_GetLiteral (Parser, (Expected = "TextureLib"), WadPath)) goto DoneLoad;
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
// *		Open_File_Dialog:- Terry and Hazel Flanigan 2023			   *
// *************************************************************************
bool A_File::Open_File_Dialog(char* Extension, char* Title, char* StartDirectory)
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
