#include "stdafx.h"
#include "CFusionView.h"

CFusionView::CFusionView()
{
}

CFusionView::~CFusionView()
{
}


// *************************************************************************
// *						OnCenterthing:- Genesis 2023				   *
// *************************************************************************
void CFusionView::OnCenterthing()
{
	//if (mViewIs3d)
	//	return;

	//CFusionDoc* pDoc = GetDocument();

	//if (!pDoc)
	//	return;

	//pDoc->SetModifiedFlag();

	//geVec3d NewWorldPos = Render_GetViewCenter(VCam);

	//// Compute delta required to get thing to NewWorldPos.
	//// One dimension won't be changed (i.e. in the top view, the Y won't be modified)
	//geVec3d MoveDelta;

	//geVec3d_Subtract(&NewWorldPos, &pDoc->SelectedGeoCenter, &MoveDelta);

	//switch (mViewType)
	//{
	//case ID_VIEW_TOPVIEW:
	//	MoveDelta.Y = 0.0f;
	//	break;

	//case ID_VIEW_SIDEVIEW:
	//	MoveDelta.X = 0.0f;
	//	break;

	//case ID_VIEW_FRONTVIEW:
	//	MoveDelta.Z = 0.0f;
	//	break;

	//default:
	//	// don't do nothin!
	//	assert(0);
	//}

	//// We've computed the delta, so move the thing...
	//if (pDoc->mModeTool == ID_TOOLS_TEMPLATE)
	//	pDoc->MoveTemplateBrush(&MoveDelta);
	//else
	//	pDoc->MoveSelectedBrushList(pDoc->pSelBrushes, &MoveDelta);

	//pDoc->UpdateAllViews(UAV_ALL3DVIEWS, NULL);
}
