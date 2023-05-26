#include "stdafx.h"
#include "WV_App.h"
#include "CLevel.h"

#include "ram.h"


CLevel::CLevel()
{

}

CLevel::~CLevel()
{

}

// *************************************************************************
// * 						Level_CreateFromFile						   *
// *************************************************************************
Level* CLevel::Level_CreateFromFile(const char* FileName)// , const char** ErrMsg, const char* DefaultHeadersDir, const char* DefaultActorsDir, const char* DefaultPawnIni)
{
	int NumModels = 0;
	int VersionMajor = 0;
	int VersionMinor = 0;
	int NumGroups = 0;
	int NumBrushes = 0;
	int NumEntities = 0;;
	Parse3dt* Parser = NULL;
	const char* Expected = "!*ERROR*!";
	int k = 0;;
	Level* pLevel = NULL;
	char WadPath[MAX_PATH] = { 0 };
	char HeadersDir[MAX_PATH] = { 0 };

	char ActorsDir[MAX_PATH] = { 0 };
	char PawnIniPath[MAX_PATH] = { 0 };


	//	assert(FileName != NULL);

	Parser = Parse3dt_Create(FileName);
	if (Parser == NULL)
	{
		//*ErrMsg = "Can't open file";
		App->Say("Can't open file");
		return NULL;
	}

	Expected = "3dtVersion";
	if (!Parse3dt_GetVersion(Parser, &VersionMajor, &VersionMinor))
	{
		App->Say("Can't get Version");
		//goto DoneLoad;
	}

	//App->Say_Int(VersionMajor);
	//App->Say_Int(VersionMinor);

	if (VersionMajor > LEVEL_VERSION_MAJOR)
	{
		//*ErrMsg = "Version mismatch.";
		return NULL;
	}

	if (VersionMajor <= 1 && VersionMinor < 16)
	{
		char	PalPath[_MAX_PATH];
		if (!Parse3dt_GetPath(Parser, (Expected = "PalLoc"), PalPath))
		{
			App->Say("Wrong Version");
			goto DoneLoad;
			return NULL;
		}
	}

	// texture library path
	if ((VersionMajor <= 1) && (VersionMinor < 18))
	{
		if (!Parse3dt_GetPath(Parser, (Expected = "WadLoc"), WadPath))
		{
			App->Say("Wrong Version");
			goto DoneLoad;
			return NULL;
		}
	}
	else
	{
		if (!Parse3dt_GetLiteral(Parser, (Expected = "TextureLib"), WadPath))
		{
			App->Say("No TextureLib Path");
			goto DoneLoad;
			return NULL;
		}
	}

	//App->Say(WadPath);

	// headers directory
	if ((VersionMajor <= 1) && (VersionMinor < 31))
	{
		//strcpy(HeadersDir, DefaultHeadersDir);
	}
	else
	{
		if (!Parse3dt_GetLiteral(Parser, (Expected = "HeadersDir"), HeadersDir))
		{
			goto DoneLoad;
		}
	}

	// changed QD Actors
		// actors directory
	if ((VersionMajor <= 1) && (VersionMinor < 33))
	{
		//strcpy(ActorsDir, DefaultActorsDir);
	}
	else
	{
		if (!Parse3dt_GetLiteral(Parser, (Expected = "ActorsDir"), ActorsDir))
		{
			goto DoneLoad;
		}
	}

	//	// PawnIni
	if ((VersionMajor <= 1) && (VersionMinor < 33))
	{
		//strcpy(PawnIniPath, DefaultPawnIni);
	}
	else
	{
		if (!Parse3dt_GetLiteral(Parser, (Expected = "PawnIni"), PawnIniPath))
		{
			goto DoneLoad;
		}
	}

	//App->Say(PawnIniPath);
//
	pLevel = Level_Create(WadPath, HeadersDir, ActorsDir, PawnIniPath);
	//	// end change
	if (pLevel == NULL)
	{
		App->Say("Error creating level.");

		return NULL;
	}


	if ((VersionMajor == 1) && (VersionMinor < 15))
	{
		if (!Parse3dt_GetInt(Parser, (Expected = "NumBrushes"), &NumBrushes))
		{
			goto DoneLoad;
		}
	}
	if (!Parse3dt_GetInt(Parser, (Expected = "NumEntities"), &NumEntities))
	{
		goto DoneLoad;
	}

	if (!Parse3dt_GetInt(Parser, (Expected = "NumModels"), &NumModels))
	{
		goto DoneLoad;
	}

	if ((VersionMajor > 1) || ((VersionMajor == 1) && (VersionMinor >= 3)))
	{
		if (!Parse3dt_GetInt(Parser, (Expected = "NumGroups"), &NumGroups))
		{
			goto DoneLoad;
		}
	}


	if ((VersionMajor == 1) && (VersionMinor < 15))
	{
		for (k = 0; k < NumBrushes; k++)
		{
			Brush* pBrush;

			pBrush = Brush_CreateFromFile(Parser, VersionMajor, VersionMinor, &Expected);
			if (pBrush == NULL)
			{
				goto DoneLoad;
			}

			BrushList_Append(pLevel->Brushes, pBrush);
		}


	}
	else
	{
		if (pLevel->Brushes != NULL)
		{
			BrushList_Destroy(&pLevel->Brushes);
		}
		pLevel->Brushes = App->CL_Brushes->BrushList_CreateFromFile(Parser, VersionMajor, VersionMinor, &Expected);
		if (pLevel->Brushes == NULL)
		{
			goto DoneLoad;
		}
	}

	if ((VersionMajor > 1) || ((VersionMajor == 1) && (VersionMinor < 6)))
	{
		//Level_BrushListToTexels(pLevel);
	}

	// collapse model list so numbers are consecutive
	//Level_CollapseModels(pLevel, 1);

	goto AllDone;
	//
DoneLoad:
	//	*ErrMsg = Parse3dt_Error(Parser, "Expected %s", Expected);
	//
	//	//DoneLoad1:
	if (pLevel != NULL)
	{
		App->Say("Failed");
		//Level_Destroy(&pLevel);
	}


AllDone:
	if (Parser != NULL)
	{
		Parse3dt_Destroy(&Parser);
	}

	//	//fixup hollows
	if (pLevel != NULL)
	{
		BrushList_MakeHollowsMulti(pLevel->Brushes);
	}

	return pLevel;
}


// *************************************************************************
// * 						Level_Create								   *
// *************************************************************************
Level* CLevel::Level_Create(const char* pWadName, const char* HeadersDir, const char* ActorsDir, const char* PawnIni)
{
	Level* pLevel = NULL;
	pLevel = GE_RAM_ALLOCATE_STRUCT(Level);

	if (pLevel != NULL)
	{
		pLevel->Brushes = BrushList_Create();
		if (pLevel->Brushes == NULL)
		{
			App->Say("Cant Create BrushList");
			//goto CreateError;
		}

		//pLevel->Entities = new (CEntityArray);
		//if (pLevel->Entities == NULL) goto CreateError;

		//pLevel->Entities->SetSize(0, 20);

		//pLevel->EntTypeNames = EntTypeNameList_Create();
		//if (pLevel->EntTypeNames == NULL) goto CreateError;

		pLevel->Groups = NULL;
		pLevel->Groups = App->CL_CGroup->Group_CreateList();
		if (pLevel->Groups == NULL)
		{
			//goto CreateError;
			App->Say("Cant Create Group List");
		}

		// add the default group
		Group* pGroup = App->CL_CGroup->Group_Create(0, "Default");
		if (pGroup != NULL)
		{
			App->CL_CGroup->GroupList_Add(pLevel->Groups, pGroup);
			
		}

		pLevel->ModelInfo.CurrentModel = 0;
		pLevel->ModelInfo.Models = App->CL_CModel->ModelList_Create();
		if (pLevel->ModelInfo.Models == NULL)
		{
			//goto CreateError;
			App->Say("Cant Create Model List");
		}

		/*pLevel->HeadersDir = NULL;
		pLevel->pEntityDefs = NULL;
		if (Level_LoadEntityDefs(pLevel, HeadersDir) == GE_FALSE)
		{
			goto CreateError;
		}*/

		// changed QD Actors
		//pLevel->ActorsDir = Util_Strdup(ActorsDir);
		//pLevel->ShowActors = GE_TRUE;
		//pLevel->PawnIniPath = Util_Strdup(PawnIni);
		// end change

		pLevel->WadPath = App->CL_CUtil->Util_Strdup(pWadName);
		pLevel->WadFile = NULL;
		pLevel->WadSizeInfos = NULL;

		// initialize sky
		/*geVec3d_Set(&pLevel->SkyRotationAxis, 1.0f, 0.0f, 0.0f);
		pLevel->SkyRotationSpeed = 10.0f;
		pLevel->SkyTextureScale = 1.0f;
		for (int i = 0; i < 6; ++i)
		{
			pLevel->SkyFaces[i].TextureName = NULL;
			pLevel->SkyFaces[i].Apply = GE_FALSE;
		}*/

		// Set default compile dialog params
		/*pLevel->CompileParams.EntitiesOnly = GE_FALSE;
		pLevel->CompileParams.VisDetailBrushes = GE_FALSE;
		pLevel->CompileParams.DoVis = GE_TRUE;
		pLevel->CompileParams.DoLight = GE_TRUE;
		pLevel->CompileParams.RunBsp = GE_TRUE;
		pLevel->CompileParams.RunPreview = GE_TRUE;
		pLevel->CompileParams.UseMinLight = GE_TRUE;
		pLevel->CompileParams.SuppressHidden = GE_FALSE;
		pLevel->CompileParams.Filename[0] = '\0';

		pLevel->CompileParams.Light.Verbose = GE_FALSE;
		pLevel->CompileParams.Light.ExtraSamples = GE_FALSE;
		pLevel->CompileParams.Light.LightScale = 1.0f;
		pLevel->CompileParams.Light.Radiosity = GE_FALSE;
		pLevel->CompileParams.Light.NumBounce = 10;
		pLevel->CompileParams.Light.PatchSize = 128.0f;
		pLevel->CompileParams.Light.FastPatch = GE_FALSE;
		pLevel->CompileParams.Light.ReflectiveScale = 1.0f;
		geVec3d_Set(&pLevel->CompileParams.Light.MinLight, 128.0f, 128.0f, 128.0f);

		pLevel->CompileParams.Bsp.Verbose = GE_FALSE;
		pLevel->CompileParams.Bsp.EntityVerbose = GE_FALSE;

		pLevel->CompileParams.Vis.Verbose = GE_FALSE;
		pLevel->CompileParams.Vis.FullVis = GE_FALSE;
		pLevel->CompileParams.Vis.SortPortals = GE_TRUE;

		pLevel->GroupVisSetting = Group_ShowVisible;

		pLevel->pEntityView = EntityViewList_Create(pLevel->pEntityDefs);*/

		// grid settings
		//default to texel grid and snap
		//with rotational snap of 15
		{
			GridInfo* pGridInfo;

			pGridInfo = &pLevel->GridSettings;
			pGridInfo->UseGrid = GE_TRUE;
			pGridInfo->GridType = GridTexel;
			pGridInfo->SnapType = GridTexel;
			pGridInfo->MetricSnapSize = GridSize_Decimeter;
			pGridInfo->TexelSnapSize = 8;
			pGridInfo->RotationSnap = 15;
		}

		pLevel->BspRebuildFlag = GE_FALSE;
		for (int iView = 0; iView < NUM_VIEWS; ++iView)
		{
			ViewStateInfo* pInfo;

			pInfo = &pLevel->ViewInfo[iView];
			pInfo->IsValid = GE_FALSE;
			pInfo->ZoomFactor = 1.0f;
			geVec3d_Clear(&pInfo->PitchRollYaw);
			geVec3d_Set(&pInfo->CameraPos, 0.0f, 0.0f, 0.0f);
		}

		App->CL_CBrushTemplate->BrushTemplate_ArchDefaults(&pLevel->ArchTemplate);
		App->CL_CBrushTemplate->BrushTemplate_BoxDefaults(&pLevel->BoxTemplate);
		App->CL_CBrushTemplate->BrushTemplate_ConeDefaults(&pLevel->ConeTemplate);
		App->CL_CBrushTemplate->BrushTemplate_CylinderDefaults(&pLevel->CylinderTemplate);
		App->CL_CBrushTemplate->BrushTemplate_SpheroidDefaults(&pLevel->SpheroidTemplate);
		App->CL_CBrushTemplate->BrushTemplate_StaircaseDefaults(&pLevel->StaircaseTemplate);

		geVec3d_Clear(&pLevel->TemplatePos);

		pLevel->DrawScale = 1.0f;
		pLevel->LightmapScale = 2.0f;
	}

	return pLevel;

	//CreateError:
	//	Level_Destroy(&pLevel);
	//	return pLevel;
}

