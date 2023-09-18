#include "stdafx.h"
#include "AB_App.h"
#include "SB_Doc.h"

#include "FUSIONView.h"
#include "units.h"

#define MAX_PIXEL_SELECT_DIST (50)

SB_Doc::SB_Doc(void)
{
    pTempSelBrushes = NULL;
    mCurrentEntity = -1;
    mShowSelectedFaces = FALSE;
    IsNewDocument = 1;
    mShowEntities = GE_TRUE;
    mCurTextureSelection = 1;
    mActiveView = -1;
    mModeTool = ID_TOOLS_TEMPLATE;
    mShowBrush = TRUE;
    mCurrentTool = ID_TOOLS_BRUSH_MOVEROTATEBRUSH;
    mCurrentBitmap = 0;
    NumSelEntities = 0;
    mCurrentGroup = 0;

    TempShearTemplate = NULL;
    pSelFaces = NULL;
    pSelBrushes = NULL;
}

SB_Doc::~SB_Doc(void)
{
}

// *************************************************************************
// *			        	AddBrushToWorld	                           	   *
// *************************************************************************
void SB_Doc::AddBrushToWorld()
{
    App->Get_Current_Document();

    if (App->m_pDoc->TempEnt || !Brush_IsSubtract(CurBrush))
    {
        App->m_pDoc->OnBrushAddtoworld();
    }
    else
    {
        App->m_pDoc->OnBrushSubtractfromworld();
    }

    App->m_pDoc->SetModifiedFlag();
}

// *************************************************************************
// *			        	DeleteCurrentThing	                    	   *
// *************************************************************************
void SB_Doc::DeleteCurrentThing()
{
    App->Get_Current_Document();

    BOOL	ReBuild;

    if (mModeTool == ID_GENERALSELECT)
    {
        // set wait cursor
        SetCursor(AfxGetApp()->LoadStandardCursor(IDC_WAIT));

        ResetAllSelectedFaces();
        ReBuild = (App->m_pDoc->GetSelState() & ANYBRUSH);

        DeleteSelectedBrushes();

        if (ReBuild && Level_RebuildBspAlways(pLevel))
        {
            UpdateAllViews(UAV_ALL3DVIEWS | REBUILD_QUICK, NULL, TRUE);
        }
        else
        {
            UpdateAllViews(UAV_ALL3DVIEWS, NULL);
        }

        // put cursor back
        SetCursor(AfxGetApp()->LoadStandardCursor(IDC_ARROW));
    }
}

// *************************************************************************
// *			        	DeleteSelectedBrushes	                	   *
// *************************************************************************
bool SB_Doc::DeleteSelectedBrushes()
{
    App->Get_Current_Document();

    geBoolean	bAlteredCurrentGroup = GE_FALSE;
    CEntityArray* Entities = Level_GetEntities(pLevel);

    for (int Ent = 0; Ent < Entities->GetSize() && (!(App->m_pDoc->GetSelState() & NOENTITIES)); Ent++)
    {
        if ((*Entities)[Ent].IsSelected())
        {
            if ((*Entities)[Ent].IsCamera() == GE_FALSE)	// Exclude Cameras
            {
                if ((*Entities)[Ent].GetGroupId() == mCurrentGroup)
                {
                    bAlteredCurrentGroup = GE_TRUE;
                }

                App->CLSB_Doc->DeleteEntity(Ent--);
                App->m_pDoc->SetModifiedFlag();
            }
        }
    }

    if (App->m_pDoc->GetSelState() & ANYBRUSH)
    {
        int NumSelBrushes = SelBrushList_GetSize(pSelBrushes);
        for (int i = 0; i < NumSelBrushes; i++)
        {
            Brush* pBrush;

            pBrush = SelBrushList_GetBrush(pSelBrushes, 0);
           
            if (strstr(App->CL_Brush->Brush_GetName(pBrush), ".act") != NULL)
                continue;
        
            if (Brush_GetGroupId(pBrush) == mCurrentGroup)
            {
                bAlteredCurrentGroup = GE_TRUE;
            }

            Level_RemoveBrush(pLevel, pBrush);
            SelBrushList_Remove(pSelBrushes, pBrush);
            Brush_Destroy(&pBrush);
        }

        //turn off any operation tools
        mCurrentTool = CURTOOL_NONE;

        App->m_pDoc->SetModifiedFlag();
    }

    // Deleting items removed group members so we must update the UI
    if (bAlteredCurrentGroup)
    {
        App->CL_TabsGroups_Dlg->Fill_ListBox();
    }

    UpdateSelected();

	return FALSE;
}

// *************************************************************************
// *			            	DeleteEntity	                    	   *
// *************************************************************************
void SB_Doc::DeleteEntity(int EntityIndex)
{
    App->Get_Current_Document();

    CEntityArray* Entities;

    // now delete the entity, we'll do the fixups later
    Entities = Level_GetEntities(pLevel);

    App->m_pDoc->DeselectEntity(&(*Entities)[EntityIndex]);
    // changed QD Actors
    Brush* b = (*Entities)[EntityIndex].GetActorBrush();
    if (b != NULL)
    {
        SelBrushList_Remove(pSelBrushes, b);
        Level_RemoveBrush(pLevel, b);
    }
    // end change
    Entities->RemoveAt(EntityIndex);
    App->m_pDoc->SelState &= (~ENTITYCLEAR);
    App->m_pDoc->SelState |= (NumSelEntities > 1) ? MULTIENTITY : (NumSelEntities + 1) << 7;
}

// *************************************************************************
// *			        	    OnEditDelete                           	   *
// *************************************************************************
void SB_Doc::OnEditDelete()
{
    App->Get_Current_Document();

    DeleteCurrentThing();
    App->m_pDoc->SetModifiedFlag();
}

// *************************************************************************
// *			        	    OnViewTypeWireFrame                    	   *
// *************************************************************************
void SB_Doc::OnViewTypeWireFrame()
{
    App->Get_Current_Document();

    App->m_pDoc->SetModifiedFlag();

    CFusionView* pFusionView = App->m_pDoc->GetCameraView();
    if (!pFusionView)
        return;

    pFusionView->OnViewType(ID_VIEW_3DWIREFRAME);
   
}

// *************************************************************************
// *			        	    OnViewTypeTexture                    	   *
// *************************************************************************
void SB_Doc::OnViewTypeTexture()
{
    App->Get_Current_Document();

    App->m_pDoc->SetModifiedFlag();

    CFusionView* pFusionView = App->m_pDoc->GetCameraView();
    if (!pFusionView)
        return;

    pFusionView->OnViewType(ID_VIEW_TEXTUREVIEW);

}


// *************************************************************************
// *			        	   SelectOrtho                             	   *
// *************************************************************************
void SB_Doc::SelectOrtho(CPoint point, ViewVars* v)
{
	App->Get_Current_Document();

	Brush* pMinBrush;
	CEntity* pMinEntity;
	geFloat Dist;
	int FoundThingType;

	if (App->m_pDoc->IsSelectionLocked())
	{
		return;
	}

	// if Control key isn't pressed, then clear all current selections
	if ((GetAsyncKeyState(VK_SHIFT) & 0x8000) == 0)
	{
		ResetAllSelections();
	}

	FoundThingType = App->m_pDoc->FindClosestThing(&point, v, &pMinBrush, &pMinEntity, &Dist);

	if ((FoundThingType != fctNOTHING) && (Dist <= MAX_PIXEL_SELECT_DIST))
	{
		switch (FoundThingType)
		{
		case fctBRUSH:
		{
			App->m_pDoc->DoBrushSelection(pMinBrush, brushSelToggle);
            if (App->CLSB_Brushes->Dimensions_Dlg_Running == 1)
            {
                App->CLSB_Brushes->Update_Pos_Dlg(App->CLSB_Brushes->Dimensions_Dlg_hWnd);
            }
			break;
		}
		case fctENTITY:
			App->m_pDoc->DoEntitySelection(pMinEntity);
			break;
		default:
			// bad value returned from FindClosestThing
			assert(0);
		}
	}

	UpdateSelected();

	App->CL_TabsControl->Select_Brushes_Tab(0);
	App->CL_TabsGroups_Dlg->Get_Index(CurBrush);

	App->CL_TabsGroups_Dlg->Update_Dlg_Controls();
    App->CLSB_TopTabs->Update_Dlg_Controls();

}

static geBoolean fdocBrushCSGCallback(const Brush* pBrush, void* lParam)
{
    App->Get_Current_Document();

    return (App->m_pDoc->BrushIsVisible(pBrush) && (!Brush_IsHint(pBrush)) && (!Brush_IsClip(pBrush)));
}

// *************************************************************************
// *			                     DoneResize                       	   *
// *************************************************************************
void SB_Doc::DoneResize(int sides, int inidx)
{
    App->Get_Current_Document();

    mLastOp = BRUSH_SCALE;

    App->m_pDoc->TempDeleteSelected();

    if (mModeTool == ID_TOOLS_TEMPLATE)
    {
        if (Brush_IsMulti(CurBrush))
        {
            BrushList_ClearCSGAndHollows((BrushList*)App->CL_Brush->Brush_GetBrushList(CurBrush), Brush_GetModelId(CurBrush));
            BrushList_RebuildHollowFaces((BrushList*)App->CL_Brush->Brush_GetBrushList(CurBrush), Brush_GetModelId(CurBrush), fdocBrushCSGCallback, NULL);
        }
        return;
    }

    int NumSelBrushes = SelBrushList_GetSize(pSelBrushes);
    for (int i = 0; i < NumSelBrushes; ++i)
    {
        Brush* pBrush;

        pBrush = SelBrushList_GetBrush(pSelBrushes, i);
       
        if (strstr(App->CL_Brush->Brush_GetName(pBrush), ".act") != NULL)
            continue;
       
        Brush_ResizeFinal(pBrush, sides, inidx, &FinalScale);
        if (Brush_IsMulti(pBrush))
        {
            BrushList_ClearCSGAndHollows((BrushList*)App->CL_Brush->Brush_GetBrushList(pBrush), Brush_GetModelId(pBrush));
            BrushList_RebuildHollowFaces((BrushList*)App->CL_Brush->Brush_GetBrushList(pBrush), Brush_GetModelId(pBrush), fdocBrushCSGCallback, NULL);
        }
    }

    UpdateSelected();
}

// *************************************************************************
// *			                 DoneMove                           	   *
// *************************************************************************
void SB_Doc::DoneMove(void)
{
    int	i;
    //	BrushList *BList = Level_GetBrushes (pLevel);

    mLastOp = BRUSH_MOVE;

    App->m_pDoc->TempDeleteSelected();

    if (mModeTool == ID_TOOLS_TEMPLATE)
    {
        if (App->m_pDoc->TempEnt)
        {
            App->m_pDoc->DoneMoveEntity();
        }
        else
        {
            Brush_Move(CurBrush, &FinalPos);
        }
        return;
    }
    else
    {
        int NumSelBrushes = SelBrushList_GetSize(pSelBrushes);
        for (i = 0; i < NumSelBrushes; i++)
        {
            Brush* pBrush;

            pBrush = SelBrushList_GetBrush(pSelBrushes, i);
           
            if (strstr(App->CL_Brush->Brush_GetName(pBrush), ".act") != NULL)
                continue;
            
            Brush_Move(pBrush, &FinalPos);
        }

        if (App->m_pDoc->GetSelState() & ANYENTITY)
        {
            App->m_pDoc->DoneMoveEntity();
        }

        UpdateSelected();

        App->m_pDoc->UpdateSelectedModel(BRUSH_MOVE, &FinalPos);
    }
   
    geVec3d_Clear(&FinalPos);

}

// *************************************************************************
//          Lock_AllTextures:- Terry and Hazel Flanigan 2023           	   *
// *************************************************************************
void SB_Doc::Lock_AllTextures(void)
{
    // Texture Lock All Faces

    App->Get_Current_Document();

    SelectAll();
    UpdateAllViews(UAV_ALL3DVIEWS, NULL);

    Face* pFace;
    int NumberOfFaces;

    NumberOfFaces = SelFaceList_GetSize(pSelFaces);

    for (int i = 0; i < NumberOfFaces; ++i)
    {
        pFace = SelFaceList_GetFace(pSelFaces, i);
        Face_SetTextureLock(pFace, true);
    }

    ResetAllSelections();
    UpdateSelected();
    UpdateAllViews(UAV_ALL3DVIEWS, NULL);

}

static geBoolean fdocSelectEntity(CEntity& Ent, void* lParam)
{
    Ent.DeSelect();
    App->m_pDoc->SelectEntity(&Ent);
    return GE_TRUE;
}

static geBoolean fdocSelectBrush(Brush* pBrush, void* lParam)
{
    
    SelBrushList_Add(App->CLSB_Doc->pSelBrushes, pBrush);

    return GE_TRUE;
}

static geBoolean SelAllBrushFaces(Brush* pBrush, void* lParam)
{
    int iFace, nFaces;
    
    nFaces = Brush_GetNumFaces(pBrush);
    for (iFace = 0; iFace < nFaces; ++iFace)
    {
        Face* pFace;

        pFace = Brush_GetFace(pBrush, iFace);
        Face_SetSelected(pFace, GE_TRUE);
        SelFaceList_Add(App->CLSB_Doc->pSelFaces, pFace);
    }
    return GE_TRUE;
}

// *************************************************************************
// *              SelectAll:- Terry and Hazel Flanigan 2023           	   *
// *************************************************************************
void SB_Doc::SelectAll(void)
{
    App->Get_Current_Document();

    App->m_pDoc->DoGeneralSelect();

    NumSelEntities = 0;
    Level_EnumEntities(pLevel, this, fdocSelectEntity);
    Level_EnumBrushes(pLevel, this, fdocSelectBrush);

    // Select all faces on all selected brushes
    int iBrush;
    int NumSelBrushes = SelBrushList_GetSize(pSelBrushes);

    for (iBrush = 0; iBrush < NumSelBrushes; ++iBrush)
    {
        Brush* pBrush;

        pBrush = SelBrushList_GetBrush(pSelBrushes, iBrush);

        if (Brush_IsMulti(pBrush))
        {
            BrushList_EnumLeafBrushes(App->CL_Brush->Brush_GetBrushList(pBrush), this, SelAllBrushFaces);
        }
        else
        {
            SelAllBrushFaces(pBrush, this);
        }

    }

    UpdateSelected();

    App->m_pDoc->ConfigureCurrentTool();
}

// *************************************************************************
// *             UpdateSelected:- Terry and Hazel Flanigan 2023            *
// *************************************************************************
void SB_Doc::UpdateSelected(void)
{
    App->Get_Current_Document();

    int		i;
    int NumSelFaces = SelFaceList_GetSize(pSelFaces);
    int NumSelBrushes = SelBrushList_GetSize(pSelBrushes);

    App->m_pDoc->SelState = (NumSelBrushes > 1) ? MULTIBRUSH : NumSelBrushes;
    App->m_pDoc->SelState |= (NumSelFaces > 1) ? MULTIFACE : (NumSelFaces + 1) << 3;
    App->m_pDoc->SelState |= (NumSelEntities > 1) ? MULTIENTITY : (NumSelEntities + 1) << 7;


    if (mModeTool == ID_GENERALSELECT)
    {
        if (App->m_pDoc->GetSelState() & ONEBRUSH)
        {
            CurBrush = SelBrushList_GetBrush(pSelBrushes, 0);
        }
        else
        {
            CurBrush = BTemplate;
        }
    }

    geVec3d_Clear(&SelectedGeoCenter);

    if (mModeTool == ID_TOOLS_TEMPLATE)
    {
        if (App->m_pDoc->TempEnt)
        {
            SelectedGeoCenter = App->m_pDoc->mRegularEntity.mOrigin;
        }
        else
        {
            Brush_Center(CurBrush, &SelectedGeoCenter);
        }
    }
    else if (App->m_pDoc->SelState != NOSELECTIONS)
    {
        Model* pModel;
        ModelInfo_Type* ModelInfo = Level_GetModelInfo(pLevel);

        pModel = ModelList_GetAnimatingModel(ModelInfo->Models);
        if (pModel != NULL)
        {
            // we're animating a model, so use its current position
            Model_GetCurrentPos(pModel, &SelectedGeoCenter);
        }
        else
        {
            if (NumSelBrushes)
            {
                SelBrushList_Center(pSelBrushes, &SelectedGeoCenter);
            }
            else if (NumSelEntities)
            {
                geVec3d EntitySelectionCenter = { 0.0f,0.0f,0.0f };

                CEntityArray* Entities;
                Entities = Level_GetEntities(pLevel);
                if (Entities)
                {
                    int NumEntities = Entities->GetSize();

                    for (int i = 0; i < NumEntities; i++)
                    {
                        if ((*Entities)[i].IsSelected())
                        {
                            geVec3d_Add(&EntitySelectionCenter, &(*Entities)[i].mOrigin, &EntitySelectionCenter);
                        }
                    }
                }

                geVec3d_Scale(&EntitySelectionCenter, 1 / (float)(NumSelEntities), &SelectedGeoCenter);
            }
        }
    }

    if (App->m_pDoc->SelState & ONEENTITY)
    {
        CEntityArray* Entities = Level_GetEntities(pLevel);

        for (i = 0; i < Entities->GetSize() && !((*Entities)[i].IsSelected()); i++);
        mCurrentEntity = i;
    }
    else
    {
        mCurrentEntity = -1;
    }

    App->m_pDoc->UpdateFaceAttributesDlg();
    App->m_pDoc->UpdateBrushAttributesDlg();

    //assert( mpMainFrame->m_wndTabControls ) ;
    //assert( mpMainFrame->m_wndTabControls->GrpTab ) ;
    //mpMainFrame->m_wndTabControls->GrpTab->UpdateGroupSelection( ) ;

}

// *************************************************************************
// *           ResetAllSelections:- Terry and Hazel Flanigan 2023          *
// *************************************************************************
void SB_Doc::ResetAllSelections(void)
{
    ResetAllSelectedFaces();
    ResetAllSelectedBrushes();
    ResetAllSelectedEntities();
}


#pragma warning (disable:4100)
static geBoolean ResetSelectedFacesCB(Brush* b, void* pVoid)
{
    int	i;

    for (i = 0; i < Brush_GetNumFaces(b); i++)
    {
        Face* pFace;

        pFace = Brush_GetFace(b, i);
        Face_SetSelected(pFace, GE_FALSE);
    }
    return GE_TRUE;
}
#pragma warning (default:4100)

// *************************************************************************
// *          ResetAllSelectedFaces:- Terry and Hazel Flanigan 2023        *
// *************************************************************************
void SB_Doc::ResetAllSelectedFaces(void)
{
    BrushList_EnumLeafBrushes(Level_GetBrushes(pLevel), NULL, ResetSelectedFacesCB);
    SelFaceList_RemoveAll(pSelFaces);
}

// *************************************************************************
// *         ResetAllSelectedBrushes:- Terry and Hazel Flanigan 2023       *
// *************************************************************************
void SB_Doc::ResetAllSelectedBrushes(void)
{
    SelBrushList_RemoveAll(pSelBrushes);
    CurBrush = BTemplate;
}

static geBoolean fdocDeselectEntity(CEntity& Ent, void* lParam)
{
    CFusionDoc* pDoc = (CFusionDoc*)lParam;

    pDoc->DeselectEntity(&Ent);
    return GE_TRUE;
}

// *************************************************************************
// *         ResetAllSelectedEntities:- Terry and Hazel Flanigan 2023      *
// *************************************************************************
void SB_Doc::ResetAllSelectedEntities()
{
    App->Get_Current_Document();

    App->m_pDoc->DoGeneralSelect();

    Level_EnumEntities(pLevel, this, fdocDeselectEntity);
}

// *************************************************************************
// *         UpdateAllViews:- Terry and Hazel Flanigan 2023                *
// *************************************************************************
void SB_Doc::UpdateAllViews(int Mode, CView* pSender, BOOL Override)
{
    App->Get_Current_Document();

    if (App->m_pDoc->IsModified() && ((Mode & REBUILD_QUICK) && (Level_RebuildBspAlways(App->CLSB_Doc->pLevel))) || (Override))
    {
        App->m_pDoc->RebuildTrees();
    }
    else if ((Mode & REBUILD_QUICK) && (!Level_RebuildBspAlways(App->CLSB_Doc->pLevel)))
    {
        App->m_pDoc->InvalidateDrawTreeOriginalFaces();
    }

    if (Mode & REBUILD_QUICK)
        Mode &= ~REBUILD_QUICK;

    //	Do we want to redraw everything?
    if (Mode & UAV_ALLVIEWS)
    {
        App->m_pDoc->CDocument::UpdateAllViews(pSender);
        return;
    }

    POSITION pos = App->m_pDoc->GetFirstViewPosition();

    while (pos != NULL)
    {
        CView* pView = App->m_pDoc->GetNextView(pos);

        if (pView->IsKindOf(RUNTIME_CLASS(CFusionView)))
        {
            CFusionView* pFusionView = (CFusionView*)pView;
            CDC* pDC = pFusionView->GetDC();

            switch (Mode)
            {
            case UAV_ACTIVE3DVIEW_ONLY:

                if (pFusionView->GetParentFrame() == App->m_pDoc->mpActiveViewFrame)
                    pFusionView->Invalidate(TRUE);
                break;

            case UAV_NONACTIVE3DVIEWS_ONLY:

                if (pFusionView->GetParentFrame() != App->m_pDoc->mpActiveViewFrame)
                    pFusionView->Invalidate(TRUE);
                break;

            case UAV_TEXTUREVIEW_ONLY:

                if (pFusionView->mViewType == ID_VIEW_TEXTUREVIEW)
                    pFusionView->Invalidate(TRUE);
                break;

            case UAV_RENDER_ONLY:

                switch (pFusionView->mViewType)
                {
                case ID_VIEW_3DWIREFRAME:
                case ID_VIEW_TEXTUREVIEW:

                    pFusionView->Invalidate(TRUE);
                    break;

                default:
                    break;
                }
                break;

            case UAV_GRID_ONLY:

                switch (pFusionView->mViewType)
                {
                case ID_VIEW_TOPVIEW:
                case ID_VIEW_SIDEVIEW:
                case ID_VIEW_FRONTVIEW:

                    pFusionView->Invalidate(TRUE);
                    break;
                }
                break;


            case UAV_THIS_GRID_ONLY:
                if (pFusionView == pSender)
                {
                    switch (pFusionView->mViewType)
                    {
                    case ID_VIEW_TOPVIEW:
                    case ID_VIEW_SIDEVIEW:
                    case ID_VIEW_FRONTVIEW:
                        pFusionView->Invalidate(TRUE);
                        break;
                    }
                }
                break;

            case UAV_ALL3DVIEWS:

                pFusionView->Invalidate(TRUE);
                break;

            default:
                break;
            }

            pFusionView->ReleaseDC(pDC);
        }
    }
}

// *************************************************************************
// *         MoveSelectedBrushes:- Terry and Hazel Flanigan 2023           *
// *************************************************************************
void SB_Doc::MoveSelectedBrushes(geVec3d const* v)
{
    MoveSelectedBrushList(pTempSelBrushes, v);
}

// *************************************************************************
// *         MoveSelectedBrushList:- Terry and Hazel Flanigan 2023         *
// *************************************************************************
void SB_Doc::MoveSelectedBrushList(SelBrushList* pList,geVec3d const* v)
{
    int		i;
    int NumBrushes;
    mLastOp = BRUSH_MOVE;

    geVec3d_Add(&SelectedGeoCenter, v, &SelectedGeoCenter);
    geVec3d_Add(v, &FinalPos, &FinalPos);

    NumBrushes = SelBrushList_GetSize(pList);
    for (i = 0; i < NumBrushes; i++)
    {
        Brush* pBrush;

        pBrush = SelBrushList_GetBrush(pList, i);
        // changed QD Actors
        if (strstr(App->CL_Brush->Brush_GetName(pBrush), ".act") != NULL)
            continue;
        // end change
        Brush_Move(pBrush, v);
    }

    CEntityArray* Entities = Level_GetEntities(pLevel);
    int NumEntities = Entities->GetSize();
    for (i = 0; i < NumEntities; i++)
    {
        if ((*Entities)[i].IsSelected())
        {
            (*Entities)[i].Move(v);
        }
    }
}

// *************************************************************************
// *         AddCameraEntityToLevel:- Terry and Hazel Flanigan 2023        *
// *************************************************************************
void SB_Doc::AddCameraEntityToLevel(void)
{
    CEntity* pCameraEntity = App->CLSB_Camera_WE->FindCameraEntity();
    if (!pCameraEntity)
    {
        // Make default camera entity
        CEntity CameraEntity;
        CString cstr;

        CreateEntityFromName("Camera", CameraEntity);
        cstr.LoadString(IDS_CAMERAENTITYNAME);
        CameraEntity.SetKeyValue("%name%", cstr);
        CameraEntity.SetOrigin(0.0f, 0.0f, 0.0f, Level_GetEntityDefs(App->CLSB_Doc->pLevel));
        Level_AddEntity(App->CLSB_Doc->pLevel, CameraEntity);

        //		pCameraEntity = FindCameraEntity();
    }
}

// *************************************************************************
// *         CreateEntityFromName:- Terry and Hazel Flanigan 2023          *
// *************************************************************************
geBoolean SB_Doc::CreateEntityFromName(char const* pEntityType, CEntity& NewEnt)
{
    assert(pEntityType != NULL);
    // get all properties for this entity type...
    EntityPropertiesList* pProps;

    pProps = EntityTable_GetEntityPropertiesFromName(Level_GetEntityDefs(App->CLSB_Doc->pLevel), pEntityType, ET_ALL);
    if (pProps == NULL)
    {
        return FALSE;
    }

    // Add key/value pairs for all of the properties...
    for (int PropNo = 0; PropNo < pProps->NumProps; ++PropNo)
    {
        EntityProperty* p = &(pProps->Props[PropNo]);

        NewEnt.SetKeyValue(p->pKey, p->pValue);

    }

    EntityTable_ReleaseEntityProperties(pProps);

    NewEnt.SetGroupId(0);
    NewEnt.UpdateOrigin(Level_GetEntityDefs(App->CLSB_Doc->pLevel));
    return TRUE;
}
