#include "stdafx.h"
#include "AB_App.h"
#include "A_Render_App.h"

#include "FUSIONView.h"

A_Render_App::A_Render_App(void)
{
}

A_Render_App::~A_Render_App(void)
{
}

// *************************************************************************
// *	  				Render3D_Mode Terry Flanigan					   *
// *************************************************************************
void A_Render_App::Render3D_Mode(UINT nID)
{
	CFusionDoc* pDoc;

	pDoc = (CFusionDoc*)App->m_pMainFrame->GetCurrentDoc();
	CFusionView* pView = pDoc->GetCameraView();


	pDoc->SetModifiedFlag();

	if (!pView)
	{
		return;
	}

	pView->OnViewType(nID);

	Level_SetBspRebuild (App->CLSB_Doc->pLevel, !Level_RebuildBspAlways (App->CLSB_Doc->pLevel));

	if (Level_RebuildBspAlways (App->CLSB_Doc->pLevel))
	{
		pDoc->RebuildTrees();
		App->CLSB_Doc->UpdateAllViews(UAV_ALL3DVIEWS, NULL);
	}

}
