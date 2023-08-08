#include "stdafx.h"
#include "AB_App.h"
#include "SB_Doc.h"

#include "FUSIONView.h"
#include "units.h"

#define MAX_PIXEL_SELECT_DIST (100)

SB_Doc::SB_Doc(void)
{
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

    if (App->m_pDoc->TempEnt || !Brush_IsSubtract(App->m_pDoc->CurBrush))
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

    if (App->m_pDoc->mModeTool == ID_GENERALSELECT)
    {
        // set wait cursor
        SetCursor(AfxGetApp()->LoadStandardCursor(IDC_WAIT));

        App->m_pDoc->ResetAllSelectedFaces();
        ReBuild = (App->m_pDoc->GetSelState() & ANYBRUSH);

        DeleteSelectedBrushes();

        if (ReBuild && Level_RebuildBspAlways(App->m_pDoc->pLevel))
        {
            App->m_pDoc->UpdateAllViews(UAV_ALL3DVIEWS | REBUILD_QUICK, NULL, TRUE);
        }
        else
        {
            App->m_pDoc->UpdateAllViews(UAV_ALL3DVIEWS, NULL);
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
    CEntityArray* Entities = Level_GetEntities(App->m_pDoc->pLevel);

    for (int Ent = 0; Ent < Entities->GetSize() && (!(App->m_pDoc->GetSelState() & NOENTITIES)); Ent++)
    {
        if ((*Entities)[Ent].IsSelected())
        {
            if ((*Entities)[Ent].IsCamera() == GE_FALSE)	// Exclude Cameras
            {
                if ((*Entities)[Ent].GetGroupId() == App->m_pDoc->mCurrentGroup)
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
        int NumSelBrushes = SelBrushList_GetSize(App->m_pDoc->pSelBrushes);
        for (int i = 0; i < NumSelBrushes; i++)
        {
            Brush* pBrush;

            pBrush = SelBrushList_GetBrush(App->m_pDoc->pSelBrushes, 0);
           
            if (strstr(App->CL_Brush->Brush_GetName(pBrush), ".act") != NULL)
                continue;
        
            if (Brush_GetGroupId(pBrush) == App->m_pDoc->mCurrentGroup)
            {
                bAlteredCurrentGroup = GE_TRUE;
            }

            Level_RemoveBrush(App->m_pDoc->pLevel, pBrush);
            SelBrushList_Remove(App->m_pDoc->pSelBrushes, pBrush);
            Brush_Destroy(&pBrush);
        }

        //turn off any operation tools
        App->m_pDoc->mCurrentTool = CURTOOL_NONE;

        App->m_pDoc->SetModifiedFlag();
    }

    // Deleting items removed group members so we must update the UI
    if (bAlteredCurrentGroup)
    {
        App->CL_TabsGroups_Dlg->Fill_ListBox();
    }

    App->m_pDoc->UpdateSelected();

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
    Entities = Level_GetEntities(App->m_pDoc->pLevel);

    App->m_pDoc->DeselectEntity(&(*Entities)[EntityIndex]);
    // changed QD Actors
    Brush* b = (*Entities)[EntityIndex].GetActorBrush();
    if (b != NULL)
    {
        SelBrushList_Remove(App->m_pDoc->pSelBrushes, b);
        Level_RemoveBrush(App->m_pDoc->pLevel, b);
    }
    // end change
    Entities->RemoveAt(EntityIndex);
    App->m_pDoc->SelState &= (~ENTITYCLEAR);
    App->m_pDoc->SelState |= (App->m_pDoc->NumSelEntities > 1) ? MULTIENTITY : (App->m_pDoc->NumSelEntities + 1) << 7;
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
		App->m_pDoc->ResetAllSelections();
	}

	FoundThingType = App->m_pDoc->FindClosestThing(&point, v, &pMinBrush, &pMinEntity, &Dist);

	if ((FoundThingType != fctNOTHING) && (Dist <= MAX_PIXEL_SELECT_DIST))
	{
		switch (FoundThingType)
		{
		case fctBRUSH:
		{
			App->m_pDoc->DoBrushSelection(pMinBrush, brushSelToggle);
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

	/*
		if (SelBrushList_GetSize (pSelBrushes) == 0)
		{
			DeleteBrushAttributes ();
		}
	*/

	App->m_pDoc->UpdateSelected();

	App->CL_TabsControl->Select_Brushes_Tab(0);
	App->CL_TabsGroups_Dlg->Get_Index(App->m_pDoc->CurBrush);

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

    App->m_pDoc->mLastOp = BRUSH_SCALE;

    App->m_pDoc->TempDeleteSelected();

    if (App->m_pDoc->mModeTool == ID_TOOLS_TEMPLATE)
    {
        if (Brush_IsMulti(App->m_pDoc->CurBrush))
        {
            BrushList_ClearCSGAndHollows((BrushList*)App->CL_Brush->Brush_GetBrushList(App->m_pDoc->CurBrush), Brush_GetModelId(App->m_pDoc->CurBrush));
            BrushList_RebuildHollowFaces((BrushList*)App->CL_Brush->Brush_GetBrushList(App->m_pDoc->CurBrush), Brush_GetModelId(App->m_pDoc->CurBrush), fdocBrushCSGCallback, NULL);
        }
        return;
    }

    int NumSelBrushes = SelBrushList_GetSize(App->m_pDoc->pSelBrushes);
    for (int i = 0; i < NumSelBrushes; ++i)
    {
        Brush* pBrush;

        pBrush = SelBrushList_GetBrush(App->m_pDoc->pSelBrushes, i);
       
        if (strstr(App->CL_Brush->Brush_GetName(pBrush), ".act") != NULL)
            continue;
       
        Brush_ResizeFinal(pBrush, sides, inidx, &App->m_pDoc->FinalScale);
        if (Brush_IsMulti(pBrush))
        {
            BrushList_ClearCSGAndHollows((BrushList*)App->CL_Brush->Brush_GetBrushList(pBrush), Brush_GetModelId(pBrush));
            BrushList_RebuildHollowFaces((BrushList*)App->CL_Brush->Brush_GetBrushList(pBrush), Brush_GetModelId(pBrush), fdocBrushCSGCallback, NULL);
        }
    }

    App->m_pDoc->UpdateSelected();
}

// *************************************************************************
// *			                 DoneMove                           	   *
// *************************************************************************
void SB_Doc::DoneMove(void)
{
    int	i;
    //	BrushList *BList = Level_GetBrushes (pLevel);

    App->m_pDoc->mLastOp = BRUSH_MOVE;

    App->m_pDoc->TempDeleteSelected();

    if (App->m_pDoc->mModeTool == ID_TOOLS_TEMPLATE)
    {
        if (App->m_pDoc->TempEnt)
        {
            App->m_pDoc->DoneMoveEntity();
        }
        else
        {
            Brush_Move(App->m_pDoc->CurBrush, &App->m_pDoc->FinalPos);
        }
        return;
    }
    else
    {
        int NumSelBrushes = SelBrushList_GetSize(App->m_pDoc->pSelBrushes);
        for (i = 0; i < NumSelBrushes; i++)
        {
            Brush* pBrush;

            pBrush = SelBrushList_GetBrush(App->m_pDoc->pSelBrushes, i);
           
            if (strstr(App->CL_Brush->Brush_GetName(pBrush), ".act") != NULL)
                continue;
            
            Brush_Move(pBrush, &App->m_pDoc->FinalPos);
        }

        if (App->m_pDoc->GetSelState() & ANYENTITY)
        {
            App->m_pDoc->DoneMoveEntity();
        }

        App->m_pDoc->UpdateSelected();

        App->m_pDoc->UpdateSelectedModel(BRUSH_MOVE, &App->m_pDoc->FinalPos);
    }
   
    geVec3d_Clear(&App->m_pDoc->FinalPos);

}