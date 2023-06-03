#include "stdafx.h"
#include "WV_App.h"
#include "resource.h"
#include "CView.h"

CView::CView()
{
	VCam = App->CL_CRender->Render_AllocViewVars();
	App->CL_CRender->Render_SetWadSizes(VCam, NULL);

	mViewIs3d = 0;
}

CView::~CView()
{
}

// *************************************************************************
// * 								OnViewType							   *
// *************************************************************************
void CView::OnViewType(UINT nID)
{
	//CFusionDoc* pDoc = GetDocument();
	mViewType = nID;

	/*SizeInfo* WadSizeInfos = Level_GetWadSizeInfos(pDoc->pLevel);

	if (WadSizeInfos)
	{
		geVec3d SaveCameraPos;
		geVec3d SaveOrientation;
		geFloat ZoomFactor;
		int Width, Height;

		ZoomFactor = Render_GetZoom(VCam);
		Render_GetCameraPos(VCam, &SaveCameraPos);
		Render_GetPitchRollYaw(VCam, &SaveOrientation);
		Width = Render_GetWidth(VCam);
		Height = Render_GetHeight(VCam);

		Render_SetWadSizes(VCam, WadSizeInfos);
		Render_ResetSettings(VCam, Render_GetWidth(VCam), Render_GetHeight(VCam));
		Render_ResizeView(VCam, Width, Height);
		Render_SetCameraPos(VCam, &SaveCameraPos);
		Render_SetPitchRollYaw(VCam, &SaveOrientation);
		if (ZoomFactor != 0.0f)
		{
			Render_SetZoom(VCam, ZoomFactor);
		}
	}*/


	switch (mViewType)
	{
	/*case ID_VIEW_TEXTUREVIEW:
		Render_SetViewType(VCam, VIEWTEXTURE);
		SetCaption("Camera - Textured");
		mViewIs3d = TRUE;
		break;
	case ID_VIEW_3DWIREFRAME:
		Render_SetViewType(VCam, VIEWWIRE);
		SetCaption("Camera - Wireframe");
		mViewIs3d = TRUE;
		break;*/
	case ID_VIEW_TOPVIEW:
		App->CL_CRender->Render_SetViewType(VCam, VIEWTOP);
		//SetCaption("Viewport - Top ( XZ )");
		mViewIs3d = FALSE;
		break;
	case ID_VIEW_SIDEVIEW:
		App->CL_CRender->Render_SetViewType(VCam, VIEWSIDE);
		//SetCaption("Viewport - Side ( ZY )");
		mViewIs3d = FALSE;
		break;
	case ID_VIEW_FRONTVIEW:
		App->CL_CRender->Render_SetViewType(VCam, VIEWFRONT);
		//SetCaption("Viewport - Front ( XY )");
		mViewIs3d = FALSE;
		break;
	}

	/*pDoc->UpdateGridInformation();

	RedrawWindow();
	GetParentFrame()->SetWindowText(pDoc->GetTitle());*/
	//}
}