#include "stdafx.h"
#include "WV_App.h"
#include "CRender.h"
#include "units.h"

#define	VectorToSUB(a, b)			(*((((geFloat *)(&a))) + (b)))

static const geVec3d	VecOrigin = { 0.0f, 0.0f, 0.0f };

typedef struct SurfTag
{
	struct	SurfTag* pnext, * pprev;
	int		color, visxstart;
	int		state, Key, sfIdx, RFlag;
} Surf;

typedef struct EdgeTag
{
	int		x, xstep, leading, Key;
	Surf* psurf;
	struct	EdgeTag* pnext, * pprev, * pnextremove;
} Edge;

typedef struct tagBrushDrawData
{
	const Box3d* pViewBox;
	HDC 		pDC2;
	ViewVars* v;
	int GroupId;
	CFusionDoc* pDoc;
	BrushFlagTest FlagTest;
	uint32		Color;
} BrushDrawData;

CRender::CRender()
{
}

CRender::~CRender()
{
}

// *************************************************************************
// *	  						Render_GetHeight		Genesis			   *
// *************************************************************************
int	CRender::Render_GetHeight(const ViewVars* v)
{
	assert(v);

	return	v->Height;
}

// *************************************************************************
// *	  						Render_GetWidth							   *
// *************************************************************************
int	CRender::Render_GetWidth(const ViewVars* v)
{
	assert(v);

	return	v->Width;
}

// *************************************************************************
// *	  						Render_GetInidx							   *
// *************************************************************************
int	CRender::Render_GetInidx(const ViewVars* v)
{
	assert(v);

	return	(v->ViewType >> 3) & 0x3;
}

// *************************************************************************
// *	  						Render_GetFineGrid						   *
// *************************************************************************
geFloat	CRender::Render_GetFineGrid(const ViewVars* v, int GridType)
{
	float dist;
	double Interval;

	assert(v);

	dist = Render_ComputeGridDist(v, GridType);

	switch (GridType)
	{
	case GRID_TYPE_METRIC:
		Interval = pow(10, (int)(log10(dist)));
		break;
	case GRID_TYPE_TEXEL:
		Interval = pow(2, (int)(log2(dist)));
		break;
	default:
		assert(0);
		Interval = 1.0f;
		break;
	}
	return (geFloat)Interval;
}

// *************************************************************************
// *	  						Render_ComputeGridDist					   *
// *************************************************************************
geFloat CRender::Render_ComputeGridDist(const ViewVars* v, int GridType)
{
	geVec3d left, right;
	float dist;

	// determine grid size for minimum 10 pixels between grid lines
	Render_ViewToWorld(v, 0, 0, &left);
	Render_ViewToWorld(v, 10, 0, &right);
	switch (v->ViewType)
	{
	case VIEWTOP:
		dist = right.X - left.X;
		break;
	case VIEWFRONT:
		dist = right.X - left.X;
		break;
	case VIEWSIDE:
		dist = right.Z - left.Z;
		break;
	default:
		dist = 0.0f;
#if 1
		/*
		  This function should be called only by ortho views.
		  Currently, all views call it so this assertion will cause a problem.
		  Need to fix this...
		*/
#pragma message ("This function should not be called by non-ortho views.")
#else
		assert(0);
#endif
		break;
	}

	dist = (float)fabs(dist);
	if (dist < 1.0f)
		dist = 1.0f;
	if (GridType == GRID_TYPE_METRIC)
	{
		dist *= 2.54f;
	}
	return dist;
}



static geBoolean fdocBrushNotDetail(const Brush* b)
{
	return !App->CL_CBrush->Brush_IsDetail(b);
}

//static geBoolean fdocBrushIsSubtract(const Brush* b)
//{
//	return (Brush_IsSubtract(b) && !Brush_IsHollowCut(b));
//}
//
//static geBoolean BrushDrawSelFacesOrtho(Brush* pBrush, void* lParam)
//{
//	BrushDrawData* pData;
//
//	pData = (BrushDrawData*)lParam;
//
//	Render_RenderBrushSelFacesOrtho(pData->v, pBrush, pData->pDC2);
//
//	return	GE_TRUE;
//}
//
//static geBoolean BrushDrawSheetFacesOrtho(Brush* pBrush, void* lParam)
//{
//	BrushDrawData* pData;
//
//	if (Brush_IsSheet(pBrush))
//	{
//		pData = (BrushDrawData*)lParam;
//
//		Render_RenderBrushSheetFacesOrtho(pData->v, pBrush, pData->pDC2);
//	}
//	return	GE_TRUE;
//}

// *************************************************************************
// *	  						RenderOrthoView		Genesis				   *
// *************************************************************************
void CRender::RenderOrthoView(ViewVars* v, HDC* pDC, HDC MemoryhDC) // hgtterry Render to views
{

	App->Flash_Window();
	//CMainFrame* m_pMainFrame;
	//m_pMainFrame = (CMainFrame*)AfxGetMainWnd(); // MFC POO

	//m_pDoc = (CFusionDoc*)m_pMainFrame->GetCurrentDoc();


	int				inidx, i;
	GroupIterator	gi;
	int				GroupId;
	BrushDrawData	brushDrawData;
	BrushList* BList;

	if (App->CL_CFusionDoc->pLevel == NULL)
	{
		return;
	}

	geVec3d		XTemp;
	Box3d ViewBox;
	int GroupVis = App->CL_CLevel->Level_GetGroupVisibility(App->CL_CFusionDoc->pLevel);

	BList = App->CL_CLevel->Level_GetBrushes(App->CL_CFusionDoc->pLevel);
	inidx = Render_GetInidx(v);

	App->CL_CBox3d->Box3d_SetBogusBounds(&ViewBox);

	Render_ViewToWorld(v, 0, 0, &XTemp);

	App->CL_CBox3d->Box3d_AddPoint(&ViewBox, XTemp.X, XTemp.Y, XTemp.Z);

	Render_ViewToWorld(v, Render_GetWidth(v), Render_GetHeight(v), &XTemp);
	App->CL_CBox3d->Box3d_AddPoint(&ViewBox, XTemp.X, XTemp.Y, XTemp.Z);

	VectorToSUB(ViewBox.Min, inidx) = -FLT_MAX;
	VectorToSUB(ViewBox.Max, inidx) = FLT_MAX;

	brushDrawData.pViewBox = &ViewBox;
	brushDrawData.pDC2 = MemoryhDC;
	brushDrawData.v = v;
	brushDrawData.pDoc = App->CL_CFusionDoc;
	brushDrawData.GroupId = 0;
	brushDrawData.FlagTest = NULL;

	// Initialize oldpen.  Don't initialize it anywhere else!

	{
		float GridSize, GridSnapSize;
		//const Prefs* pPrefs = m_pDoc->GetPrefs();

		//CPen	PenGrid (PS_SOLID, 1, Prefs_GetGridColor (pPrefs));
		//CPen	PenSnapGrid (PS_SOLID, 1, Prefs_GetSnapGridColor (pPrefs));


		GridSize = Render_GetFineGrid(v, (App->CL_CLevel->Level_GetGridType(App->CL_CFusionDoc->pLevel) == GridTexel) ? GRID_TYPE_TEXEL : GRID_TYPE_METRIC);
		if (App->CL_CLevel->Level_GetGridType(App->CL_CFusionDoc->pLevel) == GridMetric)
		{
			GridSize /= 2.54f;
		}

		GridSnapSize = App->CL_CLevel->Level_GetGridSnapSize(App->CL_CFusionDoc->pLevel);

		{
			if (GridSnapSize >= GridSize)
			{
				HPEN pen = CreatePen(PS_SOLID, 0, RGB(0, 0, 0));
				SelectObject(MemoryhDC, pen);
				Render_RenderOrthoGridFromSize(v, GridSnapSize, MemoryhDC);
				DeleteObject(pen);
			}

			HPEN pen2 = CreatePen(PS_SOLID, 0, RGB(112, 112, 112));
			SelectObject(MemoryhDC, pen2);
			Render_RenderOrthoGridFromSize(v, 128, MemoryhDC);
			DeleteObject(pen2);

		}
	}

	GroupListType* Groups = App->CL_CLevel->Level_GetGroups(App->CL_CFusionDoc->pLevel);

	GroupId = App->CL_CGroup->Group_GetFirstId(Groups, &gi);
	while (GroupId != NO_MORE_GROUPS)
	{
		brushDrawData.FlagTest = fdocBrushNotDetail;
		brushDrawData.GroupId = GroupId;
//		if ((GroupVis == Group_ShowAll) ||
//			((GroupVis == Group_ShowCurrent) && (GroupId == App->CL_CFusionDoc->mCurrentGroup)) ||
//			((GroupVis == Group_ShowVisible) && (Group_IsVisible(Groups, GroupId)))
//			)
		{
			const GE_RGBA* pRGB;
//			pRGB = Group_GetColor(Groups, GroupId);
			HPEN	PenThisGroup = CreatePen(PS_SOLID, 1, RGB(pRGB->r, pRGB->g, pRGB->b));

			//pDC->SelectObject (&PenThisGroup);
			SelectObject(MemoryhDC, PenThisGroup);

//			Level_EnumLeafBrushes(App->CL_CFusionDoc->pLevel, &brushDrawData, BrushDraw2); // Draw Brushes
//			if (m_pDoc->mShowEntities == GE_TRUE)
			{
				//Level_EnumEntities (m_pDoc->pLevel, &brushDrawData, EntityDraw);
			}

			DeleteObject(PenThisGroup);

			// render cut brushes
//			SelectObject(MemoryhDC, PenCutBrush2);
//			brushDrawData.FlagTest = fdocBrushIsSubtract;
//			Level_EnumLeafBrushes(m_pDoc->pLevel, &brushDrawData, BrushDraw2);

			// details
//			if (m_pDoc->bShowDetailBrushes)
			{
				// detail brushes
//				SelectObject(MemoryhDC, PenDetailBrush2);
//				brushDrawData.FlagTest = App->CL_CBrush->Brush_IsDetail;
//				Level_EnumLeafBrushes(m_pDoc->pLevel, &brushDrawData, BrushDraw2);
			}

			// hints
//			if (m_pDoc->bShowHintBrushes)
			{
				// Hint brushes
//				SelectObject(MemoryhDC, PenHintBrush2);
//				brushDrawData.FlagTest = Brush_IsHint;
//				Level_EnumLeafBrushes(m_pDoc->pLevel, &brushDrawData, BrushDraw2);
			}


			// clip
//			if (m_pDoc->bShowClipBrushes)
			{
				// Hint brushes
//				SelectObject(MemoryhDC, Brush_IsClip);
//				Level_EnumLeafBrushes(m_pDoc->pLevel, &brushDrawData, BrushDraw2);
			}

//			SelectObject(MemoryhDC, PenAllItems2);
		}
//		GroupId = Group_GetNextId(Groups, &gi);
	}

//	brushDrawData.GroupId = fdoc_SHOW_ALL_GROUPS;
	brushDrawData.FlagTest = NULL;
	{
//		CEntityArray* Entities = Level_GetEntities(m_pDoc->pLevel);
//		int NumSelBrushes = SelBrushList_GetSize(m_pDoc->pSelBrushes);

		// render selected brushes and entities
//		SelectObject(MemoryhDC, PenSelected2);

//		for (i = 0; i < NumSelBrushes; i++)
		{
			Brush* pBrush;

//			pBrush = SelBrushList_GetBrush(m_pDoc->pSelBrushes, i);
//			if (m_pDoc->fdocShowBrush(pBrush, &ViewBox))
			{
//				if (Brush_IsMulti(pBrush))
				{
//					BrushList_EnumLeafBrushes(App->CL_Brush->Brush_GetBrushList(pBrush), &brushDrawData, BrushDraw2);
				}
//				else
				{
//					Render_RenderBrushFacesOrtho(v, pBrush, MemoryhDC);
				}
			}
		}

		//	for(i=0;i < Entities->GetSize();i++)
		//	{
		//		CEntity *pEnt;

		//		pEnt = &(*Entities)[i];

		//		if (pEnt->IsSelected ())
		//		{
		//			fdocDrawEntity (pEnt, v, pDC, Level_GetEntityDefs (m_pDoc->pLevel), (i==m_pDoc->mCurrentEntity) ? GE_TRUE : GE_FALSE ) ;
		//		}
		//	}
	}

	{
		// render sheet faces
		//pDC->SelectObject (&PenSheetFaces);
//		SelectObject(MemoryhDC, PenSheetFaces2);
//		BrushList_EnumLeafBrushes(BList, &brushDrawData, BrushDrawSheetFacesOrtho);
	}
	{
		// render selected faces
	//	pDC->SelectObject (&PenSelectedFaces);
//		SelectObject(MemoryhDC, PenSelectedFaces2);
//		BrushList_EnumLeafBrushes(BList, &brushDrawData, BrushDrawSelFacesOrtho);
	}
	{
		// template brush/entity
		//pDC->SelectObject (&PenTemplate);
//		SelectObject(MemoryhDC, PenTemplate2);

//		if ((m_pDoc->mModeTool == ID_TOOLS_TEMPLATE) ||
//			(m_pDoc->mModeTool == ID_TOOLS_CAMERA && m_pDoc->GetSelState() == NOSELECTIONS))
		{
//			if (!m_pDoc->TempEnt)
			{
//				if (Brush_TestBoundsIntersect(m_pDoc->CurBrush, &ViewBox))
				{
//					if (Brush_IsMulti(m_pDoc->CurBrush))
					{
//						BrushList_EnumLeafBrushes(App->CL_Brush->Brush_GetBrushList(m_pDoc->CurBrush), &brushDrawData, BrushDraw2);
					}
//					else
					{
//						Render_RenderBrushFacesOrtho(v, m_pDoc->CurBrush, MemoryhDC);
					}
				}
			}
//			else
			{
				//fdocDrawEntity (&m_pDoc->mRegularEntity, v, pDC, Level_GetEntityDefs (m_pDoc->pLevel), GE_FALSE );
			}
		}
	}

	//// find and render the camera entity
//	CEntity* pCameraEntity = m_pDoc->FindCameraEntity();

//	if ((pCameraEntity != NULL))
	{
//		if (pCameraEntity->IsSelected())
			//pDC->SelectObject (&PenSelected);
//			SelectObject(MemoryhDC, PenSelected2);
//		else
			//pDC->SelectObject (&PenCamera);
//			SelectObject(MemoryhDC, PenCamera2);

//		fdocDrawEntity(pCameraEntity, v, MemoryhDC, Level_GetEntityDefs(m_pDoc->pLevel), GE_TRUE);
	}

	//pDC->SelectObject(oldpen);

}

// *************************************************************************
// * 						Render_RenderOrthoGridFromSize				   *
// *************************************************************************
void CRender::Render_RenderOrthoGridFromSize(ViewVars* v, geFloat Interval, HDC ViewDC)
{
	geVec3d		ystep, xstep, Delt, Delt2;
	int			i, cnt, xaxis, yaxis, inidx;
	static int axidx[3][2] = { 2, 1, 0, 2, 0, 1 };
	geFloat	gsinv;
	Box3d ViewBox;
	POINT		sp;

	inidx = (v->ViewType >> 3) & 0x3;

	xaxis = axidx[inidx][0];
	yaxis = axidx[inidx][1];


	Render_ViewToWorld(v, Units_Round(-Interval), Units_Round(-Interval), &Delt);
	Render_ViewToWorld(v, Units_Round(v->Width + Interval), Units_Round(v->Height + Interval), &Delt2);

	App->CL_CBox3d->Box3d_Set(&ViewBox, Delt.X, Delt.Y, Delt.Z, Delt2.X, Delt2.Y, Delt2.Z);

	VectorToSUB(ViewBox.Min, inidx) = -FLT_MAX;
	VectorToSUB(ViewBox.Max, inidx) = FLT_MAX;

	//snap viewmin and viewmax to grid
	gsinv = 1.0f / (geFloat)Interval;
	for (i = 0; i < 3; i++)
	{
		VectorToSUB(ViewBox.Min, i) = (geFloat)((int)(VectorToSUB(ViewBox.Min, i) * gsinv)) * Interval;
		VectorToSUB(ViewBox.Max, i) = (geFloat)((int)(VectorToSUB(ViewBox.Max, i) * gsinv)) * Interval;
	}

	geVec3d_Copy(&VecOrigin, &xstep);
	geVec3d_Copy(&VecOrigin, &ystep);
	VectorToSUB(ystep, yaxis) = (geFloat)Interval;
	VectorToSUB(xstep, xaxis) = (geFloat)Interval;

	// horizontal lines
	geVec3d_Copy(&ViewBox.Min, &Delt);
	geVec3d_Copy(&ViewBox.Min, &Delt2);
	VectorToSUB(Delt2, xaxis) = VectorToSUB(ViewBox.Max, xaxis);
	cnt = Units_Round((VectorToSUB(ViewBox.Max, yaxis) - VectorToSUB(ViewBox.Min, yaxis)) * gsinv);
	for (i = 0; i <= cnt; i++)
	{
		sp = Render_OrthoWorldToView(v, &Delt);
		MoveToEx(ViewDC, 0, sp.y, NULL);
		sp = Render_OrthoWorldToView(v, &Delt2);
		LineTo(ViewDC, v->Width, sp.y);
		geVec3d_Add(&Delt, &ystep, &Delt);
		geVec3d_Add(&Delt2, &ystep, &Delt2);
	}

	// vertical lines
	geVec3d_Copy(&ViewBox.Min, &Delt);
	geVec3d_Copy(&ViewBox.Min, &Delt2);
	VectorToSUB(Delt2, yaxis) = VectorToSUB(ViewBox.Max, yaxis);
	cnt = Units_Round((VectorToSUB(ViewBox.Max, xaxis) - VectorToSUB(ViewBox.Min, xaxis)) * gsinv);
	for (i = 0; i <= cnt; i++)
	{
		sp = Render_OrthoWorldToView(v, &Delt);
		MoveToEx(ViewDC, sp.x, 0, NULL);
		sp = Render_OrthoWorldToView(v, &Delt2);
		LineTo(ViewDC, sp.x, v->Height);
		geVec3d_Add(&Delt, &xstep, &Delt);
		geVec3d_Add(&Delt2, &xstep, &Delt2);
	}
}

// *************************************************************************
// * 						Render_ViewToWorld							   *
// *************************************************************************
void CRender::Render_ViewToWorld(const ViewVars* v, const int x, const int y, geVec3d* wp)
{
	geFloat	ZoomInv = 1.0f / v->ZoomFactor;

	switch (v->ViewType)
	{
	case VIEWTOP:
	{
		geVec3d_Set(wp, (x - v->XCenter), 0.0f, (y - v->YCenter));
		geVec3d_Scale(wp, ZoomInv, wp);
		geVec3d_Add(wp, &v->CamPos, wp);
		break;
	}
	case VIEWFRONT:
	{

		geVec3d_Set(wp, (x - v->XCenter), -(y - v->YCenter), 0.0f);
		geVec3d_Scale(wp, ZoomInv, wp);
		geVec3d_Add(wp, &v->CamPos, wp);
		break;
	}
	case VIEWSIDE:
	{
		geVec3d_Set(wp, 0.0f, -(y - v->YCenter), (x - v->XCenter));
		geVec3d_Scale(wp, ZoomInv, wp);
		geVec3d_Add(wp, &v->CamPos, wp);
		break;
	}
	default:
	{
		geVec3d_Set
		(
			wp,
			-(x - v->XCenter) * (v->MaxScreenScaleInv),
			-(y - v->YCenter) * (v->MaxScreenScaleInv),
			1.0f
		);
		geVec3d_Normalize(wp);
		break;
	}
	}
}

// *************************************************************************
// * 						Render_OrthoWorldToView						   *
// *************************************************************************
POINT CRender::Render_OrthoWorldToView(const ViewVars* v, geVec3d const* wp)
{
	POINT	sc = { 0, 0 };
	geVec3d ptView;
	switch (v->ViewType)
	{
	case VIEWTOP:
	{
		geVec3d_Subtract(wp, &v->CamPos, &ptView);
		geVec3d_Scale(&ptView, v->ZoomFactor, &ptView);
		sc.x = (int)(v->XCenter + ptView.X);
		sc.y = (int)(v->YCenter + ptView.Z);
		break;
	}
	case VIEWFRONT:
	{
		geVec3d_Subtract(wp, &v->CamPos, &ptView);
		geVec3d_Scale(&ptView, v->ZoomFactor, &ptView);
		sc.x = (int)(v->XCenter + ptView.X);
		sc.y = (int)(v->YCenter - ptView.Y);
		break;
	}
	case VIEWSIDE:
	{
		geVec3d_Subtract(wp, &v->CamPos, &ptView);
		geVec3d_Scale(&ptView, v->ZoomFactor, &ptView);
		sc.x = (int)(v->XCenter + ptView.Z);
		sc.y = (int)(v->YCenter - ptView.Y);
		break;
	}
	default:
		//			assert (0);	// bad view type
					// I should be able to assert here, but I can't.
					// somebody is calling this function for the rendered
					// view.  Bad stuff, really, but I don't have time to change it.
		break;
	}
	return sc;
}



