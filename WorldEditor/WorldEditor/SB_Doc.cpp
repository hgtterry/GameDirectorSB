#include "stdafx.h"
#include "AB_App.h"
#include "SB_Doc.h"

#include "FUSIONView.h"

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
