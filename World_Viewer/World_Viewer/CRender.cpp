#include "stdafx.h"
#include "CRender.h"

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

CRender::CRender()
{
}

CRender::~CRender()
{
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
	//Box3d ViewBox;
	POINT		sp;

	inidx = (v->ViewType >> 3) & 0x3;

	xaxis = axidx[inidx][0];
	yaxis = axidx[inidx][1];


	//Render_ViewToWorld(v, Units_Round(-Interval), Units_Round(-Interval), &Delt);
	//Render_ViewToWorld(v, Units_Round(v->Width + Interval), Units_Round(v->Height + Interval), &Delt2);

	//Box3d_Set(&ViewBox, Delt.X, Delt.Y, Delt.Z, Delt2.X, Delt2.Y, Delt2.Z);

	//VectorToSUB(ViewBox.Min, inidx) = -FLT_MAX;
	//VectorToSUB(ViewBox.Max, inidx) = FLT_MAX;

	////snap viewmin and viewmax to grid
	//gsinv = 1.0f / (geFloat)Interval;
	//for (i = 0; i < 3; i++)
	//{
	//	VectorToSUB(ViewBox.Min, i) = (geFloat)((int)(VectorToSUB(ViewBox.Min, i) * gsinv)) * Interval;
	//	VectorToSUB(ViewBox.Max, i) = (geFloat)((int)(VectorToSUB(ViewBox.Max, i) * gsinv)) * Interval;
	//}

	//geVec3d_Copy(&VecOrigin, &xstep);
	//geVec3d_Copy(&VecOrigin, &ystep);
	//VectorToSUB(ystep, yaxis) = (geFloat)Interval;
	//VectorToSUB(xstep, xaxis) = (geFloat)Interval;

	//// horizontal lines
	//geVec3d_Copy(&ViewBox.Min, &Delt);
	//geVec3d_Copy(&ViewBox.Min, &Delt2);
	//VectorToSUB(Delt2, xaxis) = VectorToSUB(ViewBox.Max, xaxis);
	//cnt = Units_Round((VectorToSUB(ViewBox.Max, yaxis) - VectorToSUB(ViewBox.Min, yaxis)) * gsinv);
	for (i = 0; i <= cnt; i++)
	{
		//sp = Render_OrthoWorldToView(v, &Delt);
		MoveToEx(ViewDC, 0, sp.y, NULL);
		//sp = Render_OrthoWorldToView(v, &Delt2);
		LineTo(ViewDC, v->Width, sp.y);
		geVec3d_Add(&Delt, &ystep, &Delt);
		geVec3d_Add(&Delt2, &ystep, &Delt2);
	}

	//// vertical lines
	//geVec3d_Copy(&ViewBox.Min, &Delt);
	//geVec3d_Copy(&ViewBox.Min, &Delt2);
	//VectorToSUB(Delt2, yaxis) = VectorToSUB(ViewBox.Max, yaxis);
	//cnt = Units_Round((VectorToSUB(ViewBox.Max, xaxis) - VectorToSUB(ViewBox.Min, xaxis)) * gsinv);
	for (i = 0; i <= cnt; i++)
	{
		//sp = Render_OrthoWorldToView(v, &Delt);
		MoveToEx(ViewDC, sp.x, 0, NULL);
		//sp = Render_OrthoWorldToView(v, &Delt2);
		LineTo(ViewDC, sp.x, v->Height);
		geVec3d_Add(&Delt, &xstep, &Delt);
		geVec3d_Add(&Delt2, &xstep, &Delt2);
	}
}
