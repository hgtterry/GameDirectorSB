/****************************************************************************************/
/*  FusionView.cpp                                                                      */
/*                                                                                      */
/*  Author:       Jim Mischel, Ken Baird, Jeff Lomax, John Moore                        */
/*  Description:  MFC view stuff...  Alot of the editor UI functionality is here        */
/*                                                                                      */
/*  The contents of this file are subject to the Genesis3D Public License               */
/*  Version 1.01 (the "License"); you may not use this file except in                   */
/*  compliance with the License. You may obtain a copy of the License at                */
/*  http://www.genesis3d.com                                                            */
/*                                                                                      */
/*  Software distributed under the License is distributed on an "AS IS"                 */
/*  basis, WITHOUT WARRANTY OF ANY KIND, either express or implied.  See                */
/*  the License for the specific language governing rights and limitations              */
/*  under the License.                                                                  */
/*                                                                                      */
/*  The Original Code is Genesis3D, released March 25, 1999.                            */
/*  Copyright (C) 1996-1999 Eclipse Entertainment, L.L.C. All Rights Reserved           */
/*                                                                                      */
/****************************************************************************************/
#include "stdafx.h"
#include "FUSIONView.h"
#include "FUSIONDoc.h"
#include "KeyEditDlg.h"
#include <assert.h>

#include "FusionTabControls.h"
#include "ChildFrm.h"
#include "units.h"
#include "face.h"
#include "ram.h"

#include "RotateDialog.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define AXIS_X	0x1
#define AXIS_Y	0x2
#define AXIS_Z	0x4

#define MAX_PIXEL_DRAG_START_DIST (12.0f)

int CFusionView::mCY_DRAG = 2 ;
int CFusionView::mCX_DRAG = 2 ;

IMPLEMENT_DYNCREATE(CFusionView, CCaptionView)

BEGIN_MESSAGE_MAP(CFusionView, CCaptionView)
	ON_MESSAGE(WM_USER_COMPILE_MSG, OnCompileMessage)
	ON_MESSAGE(WM_USER_COMPILE_ERR, OnCompileError)
	ON_MESSAGE(WM_USER_COMPILE_DONE, OnCompileDone)
	//{{AFX_MSG_MAP(CFusionView)
	ON_WM_SIZE()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
	ON_WM_KEYDOWN()
	ON_COMMAND(ID_TOOLS_CAMERA, OnToolsCamera)
	ON_UPDATE_COMMAND_UI(ID_TOOLS_CAMERA, OnUpdateToolsCamera)
	ON_WM_RBUTTONDOWN()
	ON_WM_RBUTTONUP()
	ON_COMMAND(ID_AXIS_X, OnAxisX)
	ON_UPDATE_COMMAND_UI(ID_AXIS_X, OnUpdateAxisX)
	ON_COMMAND(ID_AXIS_Y, OnAxisY)
	ON_UPDATE_COMMAND_UI(ID_AXIS_Y, OnUpdateAxisY)
	ON_COMMAND(ID_AXIS_Z, OnAxisZ)
	ON_UPDATE_COMMAND_UI(ID_AXIS_Z, OnUpdateAxisZ)
	ON_COMMAND(ID_TOOLS_BRUSH_MOVEROTATEBRUSH, OnToolsBrushMoverotatebrush)
	ON_UPDATE_COMMAND_UI(ID_TOOLS_BRUSH_MOVEROTATEBRUSH, OnUpdateToolsBrushMoverotatebrush)
	ON_COMMAND(ID_TOOLS_BRUSH_SCALEBRUSH, OnToolsBrushScalebrush)
	ON_UPDATE_COMMAND_UI(ID_TOOLS_BRUSH_SCALEBRUSH, OnUpdateToolsBrushScalebrush)
	ON_COMMAND(ID_TOOLS_BRUSH_SHOWBRUSH, OnToolsBrushShowbrush)
	ON_UPDATE_COMMAND_UI(ID_TOOLS_BRUSH_SHOWBRUSH, OnUpdateToolsBrushShowbrush)
	ON_WM_ERASEBKGND()
	ON_COMMAND(ID_TOOLS_BRUSH_SHEARBRUSH, OnToolsBrushShearbrush)
	ON_UPDATE_COMMAND_UI(ID_TOOLS_BRUSH_SHEARBRUSH, OnUpdateToolsBrushShearbrush)
	ON_UPDATE_COMMAND_UI(ID_GROUPS_MAKENEWGROUP, OnUpdateBrushGroupsMakenewgroup)
	ON_UPDATE_COMMAND_UI(ID_BRUSH_GROUPS_ADDTOGROUP, OnUpdateBrushGroupsAddtogroup)
	ON_COMMAND(ID_TOOLS_BRUSH_ROTATE90, OnToolsBrushRotate45)
	ON_COMMAND(ID_TOOLS_BRUSH_MOVESELECTEDBRUSHES, OnToolsBrushMoveselectedbrushes)
	ON_UPDATE_COMMAND_UI(ID_TOOLS_BRUSH_MOVESELECTEDBRUSHES, OnUpdateToolsBrushMoveselectedbrushes)
//	ON_COMMAND(ID_TOOLS_TEMPLATE, OnToolsTemplate) // hgtterry Needs Looking at
	ON_UPDATE_COMMAND_UI(ID_TOOLS_TEMPLATE, OnUpdateToolsTemplate)
	ON_UPDATE_COMMAND_UI(ID_TOOLS_BRUSH_ROTATE90, OnUpdateToolsBrushRotate45)
	ON_COMMAND(ID_BRUSH_REMOVESELECTEDFROMGROUP, OnBrushRemoveselectedfromgroup)
	ON_UPDATE_COMMAND_UI(ID_BRUSH_REMOVESELECTEDFROMGROUP, OnUpdateBrushRemoveselectedfromgroup)
	ON_COMMAND(ID_BRUSH_GROUPS_ADDTOGROUP, OnBrushGroupsAddtogroup)
	ON_COMMAND(ID_DESELECTALL, OnDeselectall)
	ON_UPDATE_COMMAND_UI(ID_DESELECTALL, OnUpdateDeselectall)
	ON_COMMAND(ID_SELECTALL, OnSelectall)
	ON_UPDATE_COMMAND_UI(ID_SELECTALL, OnUpdateSelectall)
	ON_COMMAND(ID_EDIT_SELECT_BRUSH_ALL, OnSelectAllBrushes)
	ON_UPDATE_COMMAND_UI(ID_EDIT_SELECT_BRUSH_ALL, OnUpdateSelectAllBrushes)
	ON_COMMAND(ID_TOOLS_SCALEWORLD, OnToolsScaleworld)
	ON_COMMAND(ID_TOOLS_SETTEXTURESCALE, OnToolsSettexturescale)
	ON_COMMAND(ID_TOOLS_NEXTBRUSH, OnToolsNextbrush)
	ON_COMMAND(ID_TOOLS_PREVBRUSH, OnToolsPrevbrush)
	ON_COMMAND(ID_TOOLS_ADDTOLEVEL, OnToolsAddtolevel)
	ON_UPDATE_COMMAND_UI(ID_TOOLS_ADDTOLEVEL, OnUpdateToolsAddtolevel)
	ON_COMMAND(ID_VIEW_ZOOMIN, OnViewZoomin)
	ON_UPDATE_COMMAND_UI(ID_VIEW_ZOOMIN, OnUpdateViewZoomin)
	ON_COMMAND(ID_VIEW_ZOOMOUT, OnViewZoomout)
	ON_UPDATE_COMMAND_UI(ID_VIEW_ZOOMOUT, OnUpdateViewZoomout)
	ON_COMMAND(ID_CENTERTHING, OnCenterthing)
	ON_UPDATE_COMMAND_UI(ID_CENTERTHING, OnUpdateCenterthing)
	ON_COMMAND(ID_EDIT_SELECT_FACES_NEXT, OnEditSelectFacesNext)
	ON_COMMAND(ID_EDIT_SELECT_FACES_PREVIOUS, OnEditSelectFacesPrevious)
	ON_COMMAND(ID_EDIT_SELECT_FACES_ALLINSELECTEDBRUSHES, OnEditSelectFacesAllinselectedbrushes)
	ON_COMMAND(ID_EDIT_SELECT_ENTITIES_ALL, OnEditSelectEntitiesAll)
	ON_COMMAND(ID_EDIT_SELECT_ENTITIES_NEXT, OnEditSelectEntitiesNext)
	ON_COMMAND(ID_EDIT_SELECT_ENTITIES_PREVIOUS, OnEditSelectEntitiesPrevious)
	ON_COMMAND(ID_EDIT_DESELECT_BRUSHES, OnEditDeselectBrushes)
	ON_COMMAND(ID_EDIT_DESELECT_ENTITIES, OnEditDeselectEntities)
	ON_COMMAND(ID_EDIT_DESELECT_FACES, OnEditDeselectFaces)
	ON_UPDATE_COMMAND_UI(ID_EDIT_DESELECT_BRUSHES, OnUpdateEditDeselectBrushes)
	ON_UPDATE_COMMAND_UI(ID_EDIT_DESELECT_ENTITIES, OnUpdateEditDeselectEntities)
	ON_UPDATE_COMMAND_UI(ID_EDIT_DESELECT_FACES, OnUpdateEditDeselectFaces)
	ON_WM_KILLFOCUS()
	ON_WM_SETFOCUS()
	ON_COMMAND(ID_VIEWPORT_CENTERONCAMERA, OnViewportCenteroncamera)
	ON_UPDATE_COMMAND_UI(ID_VIEWPORT_CENTERONCAMERA, OnUpdateViewportCenteroncamera)
	ON_COMMAND(ID_VIEWPORT_CENTERONSELECTION, OnViewportCenteronselection)
	ON_UPDATE_COMMAND_UI(ID_VIEWPORT_CENTERONSELECTION, OnUpdateViewportCenteronselection)
	ON_COMMAND(ID_CAMERA_CENTERONVIEW, OnCameraCenteronview)
	ON_UPDATE_COMMAND_UI(ID_CAMERA_CENTERONVIEW, OnUpdateCameraCenteronview)
	ON_COMMAND(ID_VIEWPORT_GOTO, OnViewportGoto)
	ON_UPDATE_COMMAND_UI(ID_VIEWPORT_GOTO, OnUpdateViewportGoto)
	ON_COMMAND(ID_MODIFY_ROTATE, OnModifyRotate)
	ON_UPDATE_COMMAND_UI(ID_MODIFY_ROTATE, OnUpdateModifyRotate)
	ON_WM_MBUTTONUP()
	//}}AFX_MSG_MAP
	ON_COMMAND_RANGE(ID_VIEW_TOPVIEW, ID_VIEW_FRONTVIEW, OnViewType)
	ON_UPDATE_COMMAND_UI_RANGE(ID_VIEW_TOPVIEW, ID_VIEW_FRONTVIEW, OnViewTypeCmdUi)
END_MESSAGE_MAP()


#define SIDE_LEFT 1
#define SIDE_RIGHT 2
#define SIDE_TOP 4
#define SIDE_BOTTOM 8

void CFusionView::OnUpdateCenterthing(CCmdUI* pCmdUI) 
{
	if (mViewIs3d)
	{
		pCmdUI->Enable (FALSE);
		return;
	}

	CFusionDoc *pDoc = GetDocument ();
	if(!pDoc)
	{
		pCmdUI->Enable( FALSE );
		return;
	}

	if ((App->CLSB_Doc->GetSelState()!=NOSELECTIONS) || (App->CLSB_Doc->mModeTool==ID_TOOLS_TEMPLATE))
		pCmdUI->Enable( TRUE );
	else
		pCmdUI->Enable( FALSE );
}

// Center the template brush or entity in the selected view.
// Doesn't work for 3d views...
void CFusionView::OnCenterthing()
{
	if (mViewIs3d)
		return;

	CFusionDoc *pDoc = GetDocument();
	if (!pDoc)
		return;

	pDoc->SetModifiedFlag();

	geVec3d NewWorldPos = Render_GetViewCenter (VCam);

	// Compute delta required to get thing to NewWorldPos.
	// One dimension won't be changed (i.e. in the top view, the Y won't be modified)
	geVec3d MoveDelta;

	geVec3d_Subtract (&NewWorldPos, &App->CLSB_Doc->SelectedGeoCenter, &MoveDelta);

	switch (mViewType)
	{
		case ID_VIEW_TOPVIEW :
			MoveDelta.Y = 0.0f;
			break;

		case ID_VIEW_SIDEVIEW :
			MoveDelta.X = 0.0f;
			break;

		case ID_VIEW_FRONTVIEW :
			MoveDelta.Z = 0.0f;
			break;

		default :
			// don't do nothin!
			assert (0);
	}

	// We've computed the delta, so move the thing...
	if (App->CLSB_Doc->mModeTool == ID_TOOLS_TEMPLATE)
		App->CLSB_Doc->MoveTemplateBrush (&MoveDelta);
	else
		App->CLSB_Doc->MoveSelectedBrushList(App->CLSB_Doc->pSelBrushes, &MoveDelta);

	App->CLSB_Doc->UpdateAllViews( UAV_ALL3DVIEWS, NULL );
}

geBoolean CFusionView::IsKeyDown (int Key)
{
	int KeyState;

	KeyState = ::GetAsyncKeyState (Key);
	return (KeyState & 0x8000);
}

// Prevent axis movement.  View space clipping.
void CFusionView::LockAxisView (int *dx, int *dy)
{
	CFusionDoc *pDoc = GetDocument ();
	int mLockAxis = App->CLSB_Doc->GetLockAxis ();

	switch (mViewType)
	{
		case ID_VIEW_TOPVIEW :
			if (mLockAxis & AXIS_X) *dx = 0;
			if (mLockAxis & AXIS_Z) *dy = 0;
			break;

		case ID_VIEW_SIDEVIEW :
			if (mLockAxis & AXIS_X) *dx = 0;
			if (mLockAxis & AXIS_Y) *dy = 0;
			break;
			
		case ID_VIEW_FRONTVIEW :
			if (mLockAxis & AXIS_Z) *dx = 0;
			if (mLockAxis & AXIS_Y) *dy = 0;
			break;
	}
}

// Prevent axis movement.  World space clipping.
void CFusionView::LockAxis( geVec3d * pWP )
{
	int mLockAxis ;
	CFusionDoc* pDoc = GetDocument();

	mLockAxis = App->CLSB_Doc->GetLockAxis() ;

	if( mLockAxis & AXIS_X )	pWP->X = 0.0f ;
	if( mLockAxis & AXIS_Y )	pWP->Y = 0.0f ;
	if( mLockAxis & AXIS_Z )	pWP->Z = 0.0f ;
}/* CFusionView::LockAxis */

void CFusionView::OnToolsBrushRotate45()
{
	geVec3d	rp;

	CFusionDoc* pDoc = GetDocument();
	if (!pDoc)
		return;

	pDoc->SetModifiedFlag();

	geVec3d_Clear (&rp);
	switch (mViewType)
	{
		case ID_VIEW_TOPVIEW:
			rp.Y = -(M_PI/4.0f);
			break;
		case ID_VIEW_FRONTVIEW :
			rp.Z = -(M_PI/4.0f);
			break;
		case ID_VIEW_SIDEVIEW:
			rp.X = (M_PI/4.0f);
			break;
		default :
			return;
	}

	if(GetModeTool()!=ID_GENERALSELECT)
	{
		App->CLSB_Doc->RotateTemplateBrush(&rp);
		App->CLSB_Doc->UpdateSelected();
		App->CLSB_Doc->UpdateAllViews(UAV_ALL3DVIEWS, NULL);
	}
	else
	{
		pDoc->RotateSelectedBrushesDirect (&rp);
		App->CLSB_Doc->UpdateAllViews(UAV_ALL3DVIEWS | REBUILD_QUICK, NULL);
	}
}


int CFusionView::GetCursorBoxPos (const POINT *ptMousePos)
{
	CFusionDoc *pDoc;
	const Box3d *pBrushBox;
	POINT ptMin, ptMax;
	int dx, dy;
	int x, y;
	int horiz, vert;
	int lookup[4] = {1, 2, 2, 3};

	/*
	  Split the box up into 3 sections vertically and 3 horizontally.
	  The center sections are 1/2 the width and height, and the end sections are
	  each 1/4 of width and height.

	  What we're creating is:

			0	   1       2        3			4
				------------------------
				|     |          |     |
			5	|  6  |    7     |  8  |  9
				------------------------
				|     |          |     |
				|     |          |     | 
	   10	|  11 |   12     |  13 |  14
				|     |          |     |
				------------------------
				|     |          |     | 
		 15	|  16 |   17     |  18 |  19
				------------------------
	   20    21			22				23	  24
	  
	  Then we determine which of the sections the cursor is closest to,
	  and return that index.
	*/

	pDoc = GetDocument ();
	if (!pDoc)
		return 12;

//	Box3d BrushBox;
//	if (pDoc->mModeTool == ID_TOOLS_TEMPLATE)
		pBrushBox = Brush_GetBoundingBox (App->CLSB_Doc->CurBrush);
//	else
//	{
//		SelBrushList_GetBoundingBox(pDoc->pSelBrushes, &BrushBox);
//		pBrushBox = &BrushBox;
//	}

	// obtain screen coordinates for bounding box min and max points
	ptMin = Render_OrthoWorldToView (VCam, &pBrushBox->Min);
	ptMax = Render_OrthoWorldToView (VCam, &pBrushBox->Max);

	// make sure the min and max points are correct...
	if (ptMin.x > ptMax.x)
	{
		int temp;

		temp = ptMin.x;
		ptMin.x = ptMax.x;
		ptMax.x = temp;
	}
	if (ptMin.y > ptMax.y)
	{
		int temp;

		temp = ptMin.y;
		ptMin.y = ptMax.y;
		ptMax.y = temp;
	}

	// compute horizontal first
	x = ptMousePos->x - ptMin.x;
	dx = (ptMax.x - ptMin.x);
	if (dx == 0) horiz = 0; else horiz = (4*x) / dx;
	if (horiz < 0) horiz = 0;
	else if (horiz > 3) horiz = 4;
	else horiz = lookup[horiz];

	// and vertical
	y = ptMousePos->y - ptMin.y;
	dy = (ptMax.y - ptMin.y);
	if (dy == 0) vert = 0; else vert = (4*y)/dy;
	if (vert < 0) vert = 0;
	else if (vert > 3) vert = 3;
	else vert = lookup[vert];

	// return index...
	return (vert * 5) + horiz;
}

void CFusionView::SetEditCursor (int Tool, const POINT *pMousePos)
{
	//for sizing stuff
	static const char *SizeCursors[25]=
	{
		IDC_SIZENWSE,	IDC_SIZENWSE,	IDC_SIZENS,		IDC_SIZENESW,	IDC_SIZENESW,
		IDC_SIZENWSE,	IDC_SIZENWSE,	IDC_SIZENS,		IDC_SIZENESW,	IDC_SIZENESW,	
		IDC_SIZEWE,		IDC_SIZEWE,		IDC_NO,			IDC_SIZEWE,		IDC_SIZEWE,
		IDC_SIZENESW,	IDC_SIZENESW,	IDC_SIZENS,		IDC_SIZENWSE,	IDC_SIZENWSE,
		IDC_SIZENESW,	IDC_SIZENESW,	IDC_SIZENS,		IDC_SIZENWSE,	IDC_SIZENWSE
	};

	static const char *ShearCursors[25]=
	{
		IDC_NO,			IDC_SIZEWE,		IDC_SIZEWE,		IDC_SIZEWE,		IDC_NO,
		IDC_SIZENS,		IDC_NO,			IDC_SIZEWE,		IDC_NO,			IDC_SIZENS,
		IDC_SIZENS,		IDC_SIZENS,		IDC_NO,			IDC_SIZENS,		IDC_SIZENS,
		IDC_SIZENS,		IDC_NO,			IDC_SIZEWE,		IDC_NO,			IDC_SIZENS,
		IDC_NO,			IDC_SIZEWE,		IDC_SIZEWE,		IDC_SIZEWE,		IDC_NO
	};

	const char *WhichCursor = NULL;
	int CursorIndex;

	assert ((Tool == ID_TOOLS_BRUSH_SCALEBRUSH) || (Tool == ID_TOOLS_BRUSH_SHEARBRUSH));

	// Determine where the cursor is on the box surrounding the selected brush,
	// and set the appropriate cursor.
	if (pMousePos->x < 0 || pMousePos->y < 0)
	{
		return;
	}
	CursorIndex = GetCursorBoxPos (pMousePos);
	switch (Tool)
	{
		case ID_TOOLS_BRUSH_SCALEBRUSH :
			// Scaling it's just a simple lookup
			WhichCursor = SizeCursors [CursorIndex];
			break;

		case ID_TOOLS_BRUSH_SHEARBRUSH :
			WhichCursor = ShearCursors[CursorIndex];
			break;
		default :
			assert (0);
			break;
	}
	SetCursor (AfxGetApp()->LoadStandardCursor (WhichCursor));
}

void CFusionView::Pan
	(
	  CFusionDoc *pDoc,
	  int dx, int dy,
	  const geVec3d *dv,
	  BOOL LButtonIsDown, 
	  BOOL RButtonIsDown
	)
{
	pDoc->SetModifiedFlag();

	if(mViewIs3d)
	{
		geVec3d MoveVec;

		if(LButtonIsDown && RButtonIsDown)
		{
			geVec3d_Set (&MoveVec, (float)-dx, (float)-dy, 0.0f);
			Render_MoveCamPos( VCam, &MoveVec ) ;
			pDoc->UpdateCameraEntity( VCam ) ;
		}
		else if (LButtonIsDown)
		{
			geVec3d_Set (&MoveVec, 0.0f, 0.0f, (float)-dy);
			//Render_MoveCamPos( VCam, &MoveVec ) ;

			Render_IncrementPitch(VCam, (float)(dy));

			if (Render_UpIsDown (VCam))
			{
				Render_IncrementPitch(VCam, (float)(-dx));
				//Render_IncrementYaw (VCam, (float)(-dx));
			}
			else
			{
				Render_IncrementYaw(VCam, (float)dx);
			}
			pDoc->UpdateCameraEntity( VCam ) ;
		}
		else if (RButtonIsDown)
		{
			if (Render_UpIsDown (VCam))
			{
				Render_IncrementYaw (VCam, (float)(-dx));
			}
			else
			{
				Render_IncrementYaw(VCam, (float)dx);
			}
			Render_IncrementPitch(VCam, (float)dy);
			pDoc->UpdateCameraEntity( VCam ) ;
		}
	}
	else
	{
		geVec3d dcamv;
		
		geVec3d_Scale (dv, -1.0f, &dcamv);
		if (LButtonIsDown)
		{
			Render_MoveCamPosOrtho(VCam, &dcamv);
			App->CLSB_Doc->LinkViewports();
		}
		else if (RButtonIsDown)
		{
			Render_ZoomChange(VCam, -(((float)dy) * 0.001f));
			pDoc->UpdateGridInformation ();
		}
	}
}

void CFusionView::ScaleSelected (CFusionDoc *pDoc, int dx, int dy)
{
	pDoc->SetModifiedFlag();

	//smooth out the zoom scale curve with a scalar
	float	ZoomInv	=Render_GetZoom(VCam);

	ZoomInv	=(ZoomInv > .5)? 0.5f / ZoomInv : 1.0f;

	// negated here because Brush_Resize is still thinking weird
	App->CLSB_Doc->ResizeSelected (-(((float)dx)*ZoomInv), -(((float)dy)*ZoomInv), sides, Render_GetInidx(VCam));
}

void CFusionView::ShearSelected (CFusionDoc *pDoc, int dx, int dy)
{
	pDoc->SetModifiedFlag();

	//smooth out the zoom scale curve with a scalar
	float	ZoomInv	=Render_GetZoom(VCam);

	ZoomInv	=(ZoomInv > .5)? 0.5f / ZoomInv : 1.0f;

	App->CLSB_Doc->ShearSelected(-(((float)dy)*ZoomInv), -(((float)dx)*ZoomInv), sides, Render_GetInidx(VCam));
}

void CFusionView::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) // hgtterry KeyDown
{
	//App->Get_Current_Document();

	//App->CLSB_Camera_WE->KeyBeingPresed_Flag = 1;

	//switch (nChar)
	//{

	//case 0x57:
	//{
	//	//App->CLSB_Camera_WE->Move_Camera_Forward(1);
	//	break;
	//}
	//case 0x53:
	//{
	//	//App->CLSB_Camera_WE->Move_Camera_Back(1);
	//	break;
	//}
	//case VK_DELETE:
	//{
	//	break;
	//}
	//}

}

#pragma warning (disable:4100)
void CFusionView::OnMouseMove (UINT nFlags, CPoint point) // hgtterry OnMouseMove
{
	int			dx, dy;
	geVec3d		sp, wp, dv;
	CFusionDoc	*pDoc;
	geBoolean	ShiftHeld;
	geBoolean	ControlHeld;
	geBoolean	LButtonIsDown, RButtonIsDown;
//	geBoolean	SpaceHeld;
	BOOL		ThisIsCaptured;
	int			ModeTool, Tool;
	fdocAdjustEnum AdjustMode;
	BOOL		DoRedraw = TRUE;
	POINT		RealCursorPosition;

	pDoc	=GetDocument();

	ThisIsCaptured = (this == GetCapture ());
	ModeTool = GetModeTool ();
	Tool		= GetTool ();
	AdjustMode  = GetAdjustMode ();

	/*
	  The point parameter to this message gives us the mouse position when the
	  message was received.  That could be old.  We really want the *current*
	  position, so we get it here and convert it to client coordinates.  This
	  prevents the panning runaway bug that plauged us for so long.
	*/
	::GetCursorPos (&RealCursorPosition);
	ScreenToClient (&RealCursorPosition);

	if ((!ThisIsCaptured) && (RealCursorPosition.y < 0))
	{
		LButtonIsDown = GE_FALSE;
		RButtonIsDown = GE_FALSE;
		SetCursor (AfxGetApp()->LoadStandardCursor (IDC_ARROW));
		return;
	}

	/*
	  You'll notice here that we don't use the nFlags parameter to get these
	  settings.  Those flags tell what the state of things was when the
	  MouseMove message was received, which could have been several seconds
	  ago (due to delays caused by a mashed key, for example).  What we're
	  really interested is the current state, so we can throw out old messages.
	*/
	ShiftHeld = IsKeyDown (VK_SHIFT);

	if (mViewIs3d)
	{
		ControlHeld = 1;
	}
	else
	{
		ControlHeld = IsKeyDown(VK_CONTROL);
	}
	
	LButtonIsDown = LMouseButtonDown;//IsKeyDown (VK_LBUTTON);
	RButtonIsDown = RMouseButtonDown;//IsKeyDown (VK_RBUTTON);
	//SpaceHeld	= IsKeyDown (VK_SPACE);

	IsPanning =  ((ControlHeld || BeganWithPan) &&
				  (LButtonIsDown | RButtonIsDown) && ThisIsCaptured);


	if(mViewIs3d && !( IsPanning || IsDragging ))
	{
	
		TRACKMOUSEEVENT et;
		et.cbSize = sizeof(TRACKMOUSEEVENT);
		et.dwFlags = TME_HOVER | TME_LEAVE;
		et.hwndTrack = GetSafeHwnd();
		et.dwHoverTime = 300;

		_TrackMouseEvent( &et );
	}

	if (!ThisIsCaptured)
	{
		// Mouse isn't captured.  So we're just moving the mouse around
		// in this view.  If we're not in camera mode and not panning,
		// then set the cursor accordingly and exit.
		if(!((ModeTool == ID_TOOLS_CAMERA) || IsPanning))
		{
			int Tool;

			Tool = GetTool ();
			if (mViewIs3d)
			{
	//			if (ShiftHeld)
				if (RMouseButtonDown && !LMouseButtonDown)
				{
					SetCursor (AfxGetApp()->LoadCursor (IDC_EYEDROPPER));
				}
				else
				{
					SetCursor (AfxGetApp()->LoadStandardCursor (IDC_ARROW));
				}
			}
			else if ((Tool == ID_TOOLS_BRUSH_SCALEBRUSH) || (Tool == ID_TOOLS_BRUSH_SHEARBRUSH))
			{
				SetEditCursor (Tool, &point);
			}
		}
		return;
	}

	pDoc->SetModifiedFlag();
	
	if(this==GetParentFrame()->GetActiveView())
	{
		App->CLSB_Doc->mActiveView	=mViewType;
	}

	dx = (RealCursorPosition.x - mStartPoint.x);
	dy = (RealCursorPosition.y - mStartPoint.y);
	
	if ((dx == 0) && (dy == 0))	// don't do anything if no delta
	{
		return;
	}
	
	Render_ViewToWorld(VCam, mStartPoint.x, mStartPoint.y, &sp);
	Render_ViewToWorld(VCam, RealCursorPosition.x, RealCursorPosition.y, &wp);
	geVec3d_Subtract(&wp, &sp, &dv);	// delta in world space

	//camera and space hold panning
	if ((ModeTool == ID_TOOLS_CAMERA) ||IsPanning)
	{
		int Tolarance1 = 2;
		int Tolarance2 = -2;

		if (dx > Tolarance1 || dy > Tolarance1 || dx < Tolarance2 || dy < Tolarance2)
		{
			Pan(pDoc, dx, dy, &dv, LButtonIsDown, RButtonIsDown);
		}
	}
	else if (!mViewIs3d)
	// none of this stuff should be available in the 3d view.
	{
		
		switch (ModeTool)
		{
			case ID_GENERALSELECT :
				switch (Tool)
				{
					case CURTOOL_NONE :
						// no tool selected.  We're doing a drag select or clone operation
//						if (AdjustMode == ADJUST_MODE_BRUSH)
						{
							// drag select or cloning
							if( IsDragging )
							{
								mDragCurrentPoint.x += (long)dx ;
								mDragCurrentPoint.y += (long)dy ;
								DoRedraw = FALSE;
								Drag(DRAG_CONTINUE);
							}
//							else if( !IsCopying && !ShiftHeld && !RButtonIsDown )
							else if( !RButtonIsDown )
							{
								if((abs(dx) > mCX_DRAG) || (abs(dy) > mCY_DRAG))
								{
									mDragCurrentPoint = RealCursorPosition;
									IsDragging = TRUE ;
									DoRedraw = FALSE;
									Drag(DRAG_BEGIN);
								}
							}// Drag Select
/*							else
							{	// Begin a copy operation			
								if((LButtonIsDown && ShiftHeld)&&(!IsCopying))
								{
									IsCopying	=TRUE;
									pDoc->ResetAllSelectedFaces();
									pDoc->CopySelectedBrushes();
									if (SelBrushList_GetSize (pDoc->pSelBrushes) > 0)
									{
										// make current brush point to first brush in list
										// so we can snap correctly.
										pDoc->CurBrush = SelBrushList_GetBrush (pDoc->pSelBrushes, 0);
									}
								}
								if(IsCopying)
								{
									LockAxis( &dv ) ;
									if(LButtonIsDown)
									{
										pDoc->MoveSelectedClone(&dv);
									}
									SetTool(CURTOOL_NONE);
								}
							}// Not Drag Select
*/
						}
						break;

					case ID_TOOLS_BRUSH_MOVEROTATEBRUSH :
						// moving/rotating brushes and entities
						SetTool(ID_TOOLS_BRUSH_MOVESELECTEDBRUSHES);
						
						if (LButtonIsDown)
						{
							LockAxis( &dv );
							App->CLSB_Doc->MoveSelectedBrushes(&dv);
						}// LButtonDown
						if (RButtonIsDown)
						{
							if(App->CLSB_Doc->GetSelState() == ONEENTITYONLY )	// Angle,Arc,Radius control
							{
//								if( !ShiftHeld && !ControlHeld )
								if( !ShiftHeld )
								{
									pDoc->AdjustEntityAngle( VCam, (float)dx ) ;
								}
/*								else if( ShiftHeld && !ControlHeld )
								{
									pDoc->AdjustEntityArc( VCam, (float)dx ) ;
								}
*/
								else  // if( !ShiftHeld && ControlHeld )
								{
									pDoc->AdjustEntityRadius( &dv ) ;
								}
							}
							else
							{			
								Render_ViewDeltaToRotation (VCam, (float)dx, &dv);
								pDoc->RotateSelectedBrushes(&dv);
							}
						}// RButtonDown
						SetTool(ID_TOOLS_BRUSH_MOVEROTATEBRUSH);
						break;

					case ID_TOOLS_BRUSH_SCALEBRUSH :
						if (LButtonIsDown)
						{
							LockAxisView (&dx, &dy);
							ScaleSelected (pDoc, dx, dy);
						}
						break;

					case ID_TOOLS_BRUSH_SHEARBRUSH :
						if (LButtonIsDown)
						{
							LockAxisView (&dx, &dy);
							ShearSelected (pDoc, dx, dy);
						}
						break;

					default :
						DoRedraw = FALSE;
						break;
				}
				break;

			case ID_TOOLS_TEMPLATE :
				switch (Tool)
				{
					case ID_TOOLS_BRUSH_MOVEROTATEBRUSH :
						if (LButtonIsDown)
						{
							LockAxis (&dv);
							App->CLSB_Doc->MoveTemplateBrush(&dv);
						}
						else if (RButtonIsDown)
						{
							Render_ViewDeltaToRotation (VCam, (float)dx, &dv);
							App->CLSB_Doc->RotateTemplateBrush(&dv);
						}
						break;

					case ID_TOOLS_BRUSH_SCALEBRUSH :
						if (LButtonIsDown)
						{
							LockAxisView (&dx, &dy);
							ScaleSelected (pDoc, dx, dy);
						}
						break;

					case ID_TOOLS_BRUSH_SHEARBRUSH :
						if (LButtonIsDown)
						{
							LockAxisView (&dx, &dy);
							ShearSelected (pDoc, dx, dy);
						}
						break;

					default :
						DoRedraw = FALSE;
						break;
				}
				break;

			default :
				DoRedraw = FALSE;
				break;
		} // Mode Tool
	}// Ortho Views

	if (DoRedraw)
	{
		RedrawWindow();
	}

	POINT pt = mStartPoint;	// The position works on the delta mStartPoint...
	ClientToScreen( &pt ) ;
	SetCursorPos( pt.x, pt.y );	
}
#pragma warning (default:4100)

// Snaps the closest edge to SnapSize.
static float ComputeSnap (float Cur, float Delta, float SnapSize)
{
	float Target;
	float SnapDelta;
	float Remainder;

	Target = Cur + Delta;
	Remainder = (float)fmod (Target, SnapSize);
	if (fabs (Remainder) < (SnapSize / 2.0f))
	{
		SnapDelta = -Remainder;
	}
	else
	{
		if (Target < 0.0f)
		{
			SnapDelta = -(SnapSize + Remainder);
		}
		else
		{
			SnapDelta = SnapSize - Remainder;
		}
	}
	return SnapDelta;
}

static float SnapSide (float CurMin, float CurMax, float Delta, float SnapSize)
{
	float MinDelta, MaxDelta;

	MinDelta = ComputeSnap (CurMin, Delta, SnapSize);
	MaxDelta = ComputeSnap (CurMax, Delta, SnapSize);

	return (fabs (MinDelta) < fabs (MaxDelta)) ? MinDelta : MaxDelta;
}

void CFusionView::DoneMovingBrushes ()
{
	CFusionDoc *pDoc = GetDocument ();
	int ModeTool = GetModeTool ();

	pDoc->SetModifiedFlag();

	if (SelBrushList_GetSize (App->CLSB_Doc->pSelBrushes) > 0 || ModeTool == ID_TOOLS_TEMPLATE)
	{
		geFloat fSnapSize ;
		const geVec3d *vMin, *vMax;
		const Box3d *pBox;
		geVec3d SnapDelta;
		geBoolean SnapX, SnapY, SnapZ;

		fSnapSize = 1.0f;
		if (Level_UseGrid (App->CLSB_Doc->pLevel))
		{
			fSnapSize = Level_GetGridSnapSize (App->CLSB_Doc->pLevel);
		}
		// do the snap thing...
		pBox = Brush_GetBoundingBox (App->CLSB_Doc->CurBrush);
		vMin = Box3d_GetMin (pBox);
		vMax = Box3d_GetMax (pBox);
		geVec3d_Clear (&SnapDelta);
		/*
		  In template mode, the brush is moved directly, so we have to snap to
		  the current position, not current position plus delta.  Since we
		  clear the delta before computing the snap, we have to save these
		  flags.
		*/
		SnapX = (App->CLSB_Doc->FinalPos.X != 0.0f);
		SnapY = (App->CLSB_Doc->FinalPos.Y != 0.0f);
		SnapZ = (App->CLSB_Doc->FinalPos.Z != 0.0f);
		if ((ModeTool == ID_TOOLS_TEMPLATE) || IsCopying)
		{
			geVec3d_Clear (&App->CLSB_Doc->FinalPos);
		}
		if (SnapX)
		{
			SnapDelta.X = ::SnapSide (vMin->X, vMax->X, App->CLSB_Doc->FinalPos.X, fSnapSize);
		}
		if (SnapY)
		{
			SnapDelta.Y = ::SnapSide (vMin->Y, vMax->Y, App->CLSB_Doc->FinalPos.Y, fSnapSize);
		}
		if (SnapZ)
		{
			SnapDelta.Z = ::SnapSide (vMin->Z, vMax->Z, App->CLSB_Doc->FinalPos.Z, fSnapSize);
		}
		if (ModeTool == ID_TOOLS_TEMPLATE)
		{
			App->CLSB_Doc->FinalPos = SnapDelta;
		}
		else
		{
			geVec3d_Add (&App->CLSB_Doc->FinalPos, &SnapDelta, &App->CLSB_Doc->FinalPos);
		}
	}

	App->CLSB_Doc->DoneMove();

	App->CLSB_Doc->UpdateSelected();

	if ((ModeTool == ID_TOOLS_TEMPLATE) ||
		((App->CLSB_Doc->GetSelState() & ANYENTITY) && (!(App->CLSB_Doc->GetSelState() & ANYBRUSH))) )
	{			
		App->CLSB_Doc->UpdateAllViews( UAV_ALL3DVIEWS, NULL );
	}
	else
	{
		App->CLSB_Doc->UpdateAllViews( UAV_ALL3DVIEWS | REBUILD_QUICK, NULL );
	}
}


#pragma warning (disable:4100)
void CFusionView::OnLButtonUp(UINT nFlags, CPoint point)
{
	BOOL ThisIsCaptured = (this == GetCapture ());
	if ((!ThisIsCaptured) && (point.y < 0))
	{
		LMouseButtonDown = GE_FALSE;
		SetCursor (AfxGetApp()->LoadStandardCursor (IDC_ARROW));
		return;
	}
	else if(IsCopying)
	{
		// MS We need to switch to move mode, to
		// correctly place groups of entities. 
		// Switch to move mode
		OnToolsBrushMoverotatebrush();
		// Do what has to be done
		DoneMovingBrushes ();
		// switch bach to Select mode
		App->CLSB_Doc->DoGeneralSelect();
		// ~MS
		IsCopying = FALSE;
	}


	if (!LMouseButtonDown)
		return;

	BOOL		bWasCaptured = FALSE ;
	CFusionDoc* pDoc;
	int ModeTool;
	int Tool;
	fdocAdjustEnum AdjustMode;

	ModeTool = GetModeTool ();
	Tool = GetTool ();
	pDoc = GetDocument ();
	AdjustMode = GetAdjustMode ();

	LMouseButtonDown = GE_FALSE;
	if (!RMouseButtonDown)
	{
		// right mouse button isn't down
		if(ThisIsCaptured)
		{
			bWasCaptured = TRUE ;
			ReleaseCapture();
		}

		if( bWasCaptured )
		{
			ClientToScreen( &mStartPoint ) ;
			SetCursorPos( mStartPoint.x, mStartPoint.y ) ;
		}
		ShowTheCursor ();

//		if (IsKeyDown (VK_SPACE) || IsPanning || ModeTool == ID_TOOLS_CAMERA)
		if (IsKeyDown (VK_CONTROL) || IsPanning || ModeTool == ID_TOOLS_CAMERA)
		{
			/*
			  Ok, here's the scoop.
			  If we're in the middle of a move/rotate and the user mashes the space bar,
			  we all of a sudden end up in panning mode with no context information to
			  tell us that we were previously moving/rotating.  So we end up with the
			  original brushes in the world, and the temporary brushes that are selected
			  and being moved also in the world.  So here we do a TempDeleteSelected to
			  remove those temporary brushes.  Otherwise they'd hang around forever.

			  Ideally, the move/rotate would be separated from the panning so that we could
			  move and pan at the same time.  Of course, I'd like to get rid of the whole
			  temp selected thing, too, but that'll have to wait...
			*/
			App->CLSB_Doc->TempDeleteSelected();

			IsPanning = FALSE;
			ShowTheCursor ();

			if( IsDragging )
			{
				pDoc->SelectOrthoRect( mDragStartPoint, mDragCurrentPoint, VCam );
				App->CLSB_Doc->UpdateAllViews(UAV_ALL3DVIEWS, NULL);
				IsDragging = FALSE ;
				Drag(DRAG_END);
			}
			else
				RedrawWindow();

			return;
		}

		if (mViewIs3d)
		{
			if(ModeTool==ID_TOOLS_TEMPLATE && App->CLSB_Doc->TempEnt)
			{
				pDoc->PlaceTemplateEntity3D(point, VCam);	
				pDoc->SetModifiedFlag();
			}
			else
			{
				switch (AdjustMode)
				{
					case ADJUST_MODE_BRUSH :
					case ADJUST_MODE_FACE :
						pDoc->SelectRay (point, VCam);
						App->CLSB_Doc->UpdateAllViews (UAV_ALL3DVIEWS, NULL);
						break;
					
					default :
						break;
				}
			}
		}
		else
		{
			switch (Tool)
			{
				case CURTOOL_NONE :
					//if (AdjustMode == ADJUST_MODE_BRUSH)
					{
						if( IsDragging )
						{
							pDoc->SelectOrthoRect( mDragStartPoint, mDragCurrentPoint, VCam );
							App->CLSB_Doc->UpdateAllViews(UAV_ALL3DVIEWS, NULL);
							IsDragging = FALSE ;
							Drag(DRAG_END);
						}
						else if(IsCopying)
						{
							DoneMovingBrushes ();
							IsCopying = FALSE;
							pDoc->SetModifiedFlag();
						}
						else
						{
							App->CLSB_Doc->SelectOrtho(point, VCam);
							App->CLSB_Doc->UpdateAllViews( UAV_ALL3DVIEWS, NULL );
						}
					}
/*
					else
					{
						MessageBeep ((UINT)(-1));
					}
*/
					break;

				case ID_TOOLS_BRUSH_MOVEROTATEBRUSH :
				case ID_TOOLS_BRUSH_MOVESELECTEDBRUSHES:
				{
					DoneMovingBrushes();
					pDoc->SetModifiedFlag();
					if (App->CLSB_Brushes->Dimensions_Dlg_Running == 1)
					{
						App->CLSB_Brushes->Update_Pos_Dlg(App->CLSB_Brushes->Dimensions_Dlg_hWnd);
					}

					if (App->CLSB_Equity->EquitySB_Dialog_Visible == 1)
					{
						App->CLSB_Mesh_Mgr->Update_World();
					}
					break;
				}

				case ID_TOOLS_BRUSH_SCALEBRUSH :
					pDoc->SetModifiedFlag();
					SetCursor(AfxGetApp()->LoadStandardCursor(IDC_ARROW));
					pDoc->SnapScaleNearest(sides, Render_GetInidx(VCam), VCam);
					if(App->CLSB_Doc->mLastOp == BRUSH_SCALE)
					{
						App->CLSB_Doc->DoneResize(sides, Render_GetInidx(VCam));

						if (App->CLSB_Brushes->Dimensions_Dlg_Running == 1)
						{
							App->CLSB_Brushes->Update_Pos_Dlg(App->CLSB_Brushes->Dimensions_Dlg_hWnd);
						}

						if (App->CLSB_Equity->EquitySB_Dialog_Visible == 1)
						{
							App->CLSB_Mesh_Mgr->Update_World();
						}
					}

					App->CLSB_Doc->UpdateSelected();
					if((ModeTool == ID_TOOLS_TEMPLATE) ||
					   ((App->CLSB_Doc->GetSelState() & ANYENTITY) && (!(App->CLSB_Doc->GetSelState() & ANYBRUSH))) )
					{			
						App->CLSB_Doc->UpdateAllViews( UAV_ALL3DVIEWS, NULL );
					}
					else
					{
						App->CLSB_Doc->UpdateAllViews( UAV_ALL3DVIEWS | REBUILD_QUICK, NULL );
					}
					break;

				case ID_TOOLS_BRUSH_SHEARBRUSH :
					pDoc->SetModifiedFlag();
					SetCursor(AfxGetApp()->LoadStandardCursor(IDC_ARROW));
					if(App->CLSB_Doc->mLastOp==BRUSH_SHEAR)
						App->CLSB_Doc->DoneShear(sides, Render_GetInidx(VCam));

					if (App->CLSB_Equity->EquitySB_Dialog_Visible == 1)
					{
						App->CLSB_Mesh_Mgr->Update_World();
					}

					App->CLSB_Doc->UpdateSelected();
					if((ModeTool == ID_TOOLS_TEMPLATE) ||
					   ((App->CLSB_Doc->GetSelState() & ANYENTITY) && (!(App->CLSB_Doc->GetSelState() & ANYBRUSH))) )
					{			
						App->CLSB_Doc->UpdateAllViews( UAV_ALL3DVIEWS, NULL );
					}
					else
					{
						App->CLSB_Doc->UpdateAllViews( UAV_ALL3DVIEWS | REBUILD_QUICK, NULL );
					}
					break;

				default :
					break;
			}
		}
	}

	assert( IsCopying == FALSE ) ;
}
#pragma warning (default:4100)


#pragma warning (disable:4100)
void CFusionView::OnLButtonDown(UINT nFlags, CPoint point)
{

	/*
	  These tables convert the index values returned by GetCursorBoxPos
	  into the bitmapped values expected by the brush routines (the "sides" values).
	  These sides values are encode the cursor's position in relation to the box
	  using this:

				   4
	     ----------
			   |		|
			1  |		|  2
			   |		|
			   |		|
	     ----------
				   8

	  So the cursor in the top-left corner of the box will be 5 (left+top = 1+4 = 5).
	*/
	static const int SideLookup[25] =
	{
		5,	5,	4,	6,	6,
		5,	5,	4,	6,	6,
		1,	1,	0,	2,	2,
		9,	9,	8,	10,	10,
		9,	9,	8,	10,	10
	};
	static const int SideLookupShear[25] =
	{
		0,	4,	4,	4,	0,
		1,	0,	4,	0,	2,
		1,	1,	0,	2,	2,
		1,	0,	8,	0,	2,
		0,	8,	8,	8,	0
	};
	int Tool = GetTool ();
	int ModeTool = GetModeTool ();
//	int AdjustMode = GetAdjustMode ();

	BOOL ThisIsCaptured = (this == GetCapture ());
	if ((!ThisIsCaptured) && (point.y < 0))
	{
		LMouseButtonDown = GE_FALSE;
		SetCursor (AfxGetApp()->LoadStandardCursor (IDC_ARROW));
		return;
	}

	CFusionDoc* pDoc = GetDocument();

	LMouseButtonDown = GE_TRUE;

//	geBoolean SpaceIsDown = IsKeyDown (VK_SPACE);
	geBoolean SpaceIsDown = IsKeyDown (VK_CONTROL);

	assert( IsCopying == FALSE ) ;

	if (!RMouseButtonDown)
	{
/*
		if ((mViewIs3d == FALSE) && (AdjustMode == ADJUST_MODE_FACE))
		{
			::MessageBeep( (uint32)-1 ) ;
			return ;
		}
*/

		BeganWithPan = SpaceIsDown;

		SetCapture();
		HideTheCursor ();
		mStartPoint = point;

		if (mViewIs3d || SpaceIsDown)
			return ;

		if ((Tool == CURTOOL_NONE))// && (ModeTool == ID_GENERALSELECT) && (AdjustMode == ADJUST_MODE_BRUSH))
		{
			mDragStartPoint = point ;	// Drag mode is initiated in MouseMove
			mDragCurrentPoint = point ;
		}// Drag Select
		else if (mViewIs3d == FALSE)
		{
			int CursorSide;

			CursorSide = GetCursorBoxPos (&point);
			if (Tool == ID_TOOLS_BRUSH_SHEARBRUSH)
			{
				sides = SideLookupShear[CursorSide];
			}
			else
			{
				sides = SideLookup[CursorSide];
			}

			if(Tool == ID_TOOLS_BRUSH_SCALEBRUSH)
			{
				App->CLSB_Doc->ScaleNum	=0;
			
				geVec3d_Set (&App->CLSB_Doc->FinalScale, 1.0f, 1.0f, 1.0f);
				pDoc->TempCopySelectedBrushes();
			}
			else if(Tool == ID_TOOLS_BRUSH_SHEARBRUSH)
			{
				App->CLSB_Doc->ScaleNum	=0;
			
				geVec3d_Clear (&App->CLSB_Doc->FinalScale);
				if (ModeTool == ID_TOOLS_TEMPLATE)
				{
					App->CLSB_Doc->TempShearTemplate	=Brush_Clone(App->CLSB_Doc->CurBrush);
				}
				else
				{
					pDoc->TempCopySelectedBrushes();
				}
			}
			else if ((Tool == ID_TOOLS_BRUSH_MOVEROTATEBRUSH) || (Tool == ID_TOOLS_BRUSH_MOVESELECTEDBRUSHES))
			{
				geVec3d_Clear (&App->CLSB_Doc->FinalPos);
				pDoc->TempCopySelectedBrushes();
			}
		}// Not Drag-select 
	}// LButtonDown only
}
#pragma warning (default:4100)

#pragma warning (disable:4100)
void CFusionView::OnRButtonDown(UINT nFlags, CPoint point) 
{
	BOOL ThisIsCaptured = (this == GetCapture ());
	if ((!ThisIsCaptured) && (point.y < 0))
	{
		RMouseButtonDown = GE_FALSE;
		SetCursor (AfxGetApp()->LoadStandardCursor (IDC_ARROW));
		return;
	}

	CFusionDoc* pDoc = GetDocument();

	int Tool;
	Tool = GetTool ();

//	geBoolean SpaceIsDown = IsKeyDown (VK_SPACE);
	geBoolean SpaceIsDown = IsKeyDown (VK_CONTROL);

	if (((!LMouseButtonDown) || SpaceIsDown) || ((Tool != ID_TOOLS_BRUSH_SCALEBRUSH) && (Tool != ID_TOOLS_BRUSH_SHEARBRUSH)))
		RMouseButtonDown = GE_TRUE;
	else
		return;

	if (!LMouseButtonDown)
	{

		if (mViewIs3d && !SpaceIsDown)
		{
			SetCursor (AfxGetApp()->LoadCursor (IDC_EYEDROPPER));
			return;
		}

		BeganWithPan = SpaceIsDown;

		SetCapture();

		HideTheCursor ();

		mStartPoint = point;

//		if (mViewIs3d || IsPanning || SpaceIsDown)
		if (IsPanning || SpaceIsDown)
			return ;

		if ((Tool == ID_TOOLS_BRUSH_MOVEROTATEBRUSH) || (Tool == ID_TOOLS_BRUSH_MOVESELECTEDBRUSHES))
		{
			geVec3d_Set (&(App->CLSB_Doc->FinalRot), 0.0f, 0.0f, 0.0f);
			pDoc->TempCopySelectedBrushes();
			pDoc->SetModifiedFlag();
		}

	}
}
#pragma warning (default:4100)

#pragma warning (disable:4100)
void CFusionView::OnRButtonUp(UINT nFlags, CPoint point)
{
	BOOL ThisIsCaptured = (this == GetCapture ());
	if ((!ThisIsCaptured) && (point.y < 0))
	{
		RMouseButtonDown = GE_FALSE;
		SetCursor (AfxGetApp()->LoadStandardCursor (IDC_ARROW));
		return;
	}

	if (!RMouseButtonDown)
		return;

	int Tool = GetTool ();

	RMouseButtonDown = GE_FALSE;
	if (!LMouseButtonDown)
	{
		CFusionDoc* pDoc = GetDocument();

		if(this==GetCapture())
		{
			ReleaseCapture();
		}

		if (mViewIs3d && !IsKeyDown(VK_CONTROL))
		{
			pDoc->SelectTextureFromFace3D (point, VCam);
		}

		pDoc->SetModifiedFlag();

//		if((IsKeyDown (VK_SPACE)) || IsPanning || GetModeTool()==ID_TOOLS_CAMERA)
		if((IsKeyDown (VK_CONTROL)) || IsPanning || GetModeTool()==ID_TOOLS_CAMERA)
		{
			App->CLSB_Doc->TempDeleteSelected();
			IsPanning	=FALSE;

			ShowTheCursor ();

			if( IsDragging )
			{
				pDoc->SelectOrthoRect( mDragStartPoint, mDragCurrentPoint, VCam );
				App->CLSB_Doc->UpdateAllViews(UAV_ALL3DVIEWS, NULL);
				IsDragging = FALSE ;
				Drag(DRAG_END);
			}
			else
				RedrawWindow();
			
			return;
		}
		else if( IsDragging )
		{
			ShowTheCursor ();
			pDoc->SelectOrthoRect( mDragStartPoint, mDragCurrentPoint, VCam );
			App->CLSB_Doc->UpdateAllViews(UAV_ALL3DVIEWS, NULL);
			IsDragging = FALSE ;
			Drag(DRAG_END);
			return;
		}

		ShowTheCursor ();

		if (!mViewIs3d)
		{
			if ((Tool == ID_TOOLS_BRUSH_MOVEROTATEBRUSH) || (Tool == ID_TOOLS_BRUSH_MOVESELECTEDBRUSHES))
			{
				App->CLSB_Doc->UpdateSelected();
				if ((GetModeTool () == ID_GENERALSELECT) || (GetModeTool () == ID_TOOLS_TEMPLATE))
				{
					App->CLSB_Doc->DoneRotate ();
				}
			}

			if (SelBrushList_GetSize (App->CLSB_Doc->pSelBrushes) != 0)
				App->CLSB_Doc->UpdateAllViews(UAV_ALL3DVIEWS | REBUILD_QUICK, NULL);
			else
				App->CLSB_Doc->UpdateAllViews(UAV_ALL3DVIEWS, NULL);
		}
	}

	assert( IsCopying == FALSE ) ;
}
#pragma warning (disable:4100)



void CFusionView::OnDraw(CDC *c)
{

	App->CL_F_View->OnDraw(mViewType, VCam,c);
	
	if (IsDragging)
	{
		Drag(DRAG_BEGIN);
	}
}

void CFusionView::OnInitialUpdate() 
{
	//App->Debug_Message("OnInitialUpdate", 1);
	

	RECT r;
	CFusionDoc*	pDoc = (CFusionDoc*) GetDocument();
	SizeInfo *WadSizeInfos = Level_GetWadSizeInfos (App->CLSB_Doc->pLevel);
	int iView;

	CCaptionView::OnInitialUpdate();
	GetClientRect(&r);

	if(WadSizeInfos)
	{
		Render_SetWadSizes(VCam, WadSizeInfos);
		Render_ResetSettings(VCam, r.right, r.bottom);
	}

	switch(mViewType)
	{
	case ID_VIEW_TEXTUREVIEW:
		Render_SetViewType(VCam, VIEWTEXTURE);
		iView = 0;
		break;
	case ID_VIEW_3DWIREFRAME:
		Render_SetViewType(VCam, VIEWWIRE);
		iView = 0;
		break;
	case ID_VIEW_TOPVIEW:
		Render_SetViewType(VCam, VIEWTOP);
		iView = 1;
		break;
	case ID_VIEW_SIDEVIEW:
		Render_SetViewType(VCam, VIEWSIDE);
		iView = 3;
		break;
	case ID_VIEW_FRONTVIEW:
		Render_SetViewType(VCam, VIEWFRONT);
		iView = 2;
		break;
	default :
		iView = -1;
		break;
	}

	GetParentFrame()->SetWindowText(pDoc->GetTitle());

	if (iView != -1)
	{
		// Update view state information that was saved in level
		ViewStateInfo *pViewStateInfo;

		pViewStateInfo = Level_GetViewStateInfo (App->CLSB_Doc->pLevel, iView);
		if (pViewStateInfo->IsValid)
		{
			Render_SetZoom (VCam, pViewStateInfo->ZoomFactor);
			Render_SetPitchRollYaw (VCam, &pViewStateInfo->PitchRollYaw);
			Render_SetCameraPos (VCam, &pViewStateInfo->CameraPos);
		}
	}

	pDoc->UpdateGridInformation ();
//	pDoc->UpdateAllViews( UAV_ALL3DVIEWS, NULL );
}

/////////////////////////////////////////////////////////////////////////////
// CFusionView construction/destruction
CFusionView::CFusionView()
{
	App->Debug_Message("CFusionView New View",1);
	VCam	= Render_AllocViewVars();
	Render_SetWadSizes(VCam, NULL);

	mStartPoint.x=mStartPoint.y=0;

	mViewType = ID_VIEW_NEW;

	IsDragging = IsCopying = IsPanning = FALSE;
	LMouseButtonDown = GE_FALSE;
	RMouseButtonDown = GE_FALSE;

	mCY_DRAG = ::GetSystemMetrics( SM_CYDRAG ) ;
	mCX_DRAG = ::GetSystemMetrics( SM_CXDRAG ) ;
}

CFusionView::~CFusionView()
{
	Render_FreeViewVars(VCam);
	if (VCam != NULL)
	{
		geRam_Free (VCam);
	}
}

BOOL CFusionView::PreCreateWindow(CREATESTRUCT& cs)
{
	App->Debug_Message("CFusionView::PreCreateWindow",1);
	//App->Debug_Message("CFusionView::PreCreateWindow", 1);

	//get rid of default cursor
	cs.lpszClass = AfxRegisterWndClass( CS_DBLCLKS | CS_HREDRAW | CS_VREDRAW,
		NULL, (HBRUSH)GetStockObject(GRAY_BRUSH));
	
	return CCaptionView::PreCreateWindow(cs);
}

CFusionDoc* CFusionView::GetDocument()
{
	//App->Debug_Message("CFusionView::GetDocument",1);
	CFusionDoc *pDoc;

	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CFusionDoc)));
	pDoc = (CFusionDoc *)m_pDocument;
	ASSERT_VALID (pDoc);

	return pDoc;
}

void CFusionView::OnSize(UINT nType, int cx, int cy) 
{
	App->Debug_Message("CFusionView::OnSize",1);
	/*App->Debug_Message("CFusionView::OnSize", 0);
	App->Debug_Int(cx, 0);
	App->Debug_Int(cy, 1);*/
	

	CFusionDoc* pDoc = GetDocument();
	SizeInfo *WadSizeInfos = Level_GetWadSizeInfos (App->CLSB_Doc->pLevel);

	// call our oldself
	CCaptionView::OnSize(nType, cx, cy);
	
	// make sure that our camera knows our current size
	if(WadSizeInfos)
	{
		Render_SetWadSizes(VCam, WadSizeInfos);
		Render_ResizeView (VCam, cx, cy);
	}
}

void CFusionView::OnToolsCamera() 
{
	SetModeTool(ID_TOOLS_CAMERA);
	App->CLSB_Doc->ConfigureCurrentTool();
}

void CFusionView::OnUpdateToolsCamera(CCmdUI* pCmdUI) 
{
	if( GetModeTool() == ID_TOOLS_CAMERA )
		pCmdUI->SetCheck();
	else
		pCmdUI->SetCheck(0);
}


void CFusionView::OnAxisX() 
{
	App->CLSB_Doc->SetLockAxis(App->CLSB_Doc->GetLockAxis() ^ AXIS_X ) ;
}


void CFusionView::OnUpdateAxisX(CCmdUI* pCmdUI) 
{
	if(App->CLSB_Doc->GetLockAxis() & AXIS_X )
		pCmdUI->SetCheck();
	else
		pCmdUI->SetCheck(0);
}


void CFusionView::OnAxisY() 
{
	App->CLSB_Doc->SetLockAxis(App->CLSB_Doc->GetLockAxis() ^ AXIS_Y ) ;
}


void CFusionView::OnUpdateAxisY(CCmdUI* pCmdUI) 
{
	if(App->CLSB_Doc->GetLockAxis() & AXIS_Y )
		pCmdUI->SetCheck();
	else
		pCmdUI->SetCheck(0);
}


void CFusionView::OnAxisZ() 
{
	App->CLSB_Doc->SetLockAxis(App->CLSB_Doc->GetLockAxis() ^ AXIS_Z ) ;
}


void CFusionView::OnUpdateAxisZ(CCmdUI* pCmdUI) 
{
	if(App->CLSB_Doc->GetLockAxis() & AXIS_Z )
		pCmdUI->SetCheck();
	else
		pCmdUI->SetCheck(0);
}


void CFusionView::OnActivateView(BOOL bActivate, CView* pActivateView, CView* pDeactiveView) 
{
	CFusionDoc* pDoc = GetDocument();

	CCaptionView::OnActivateView(bActivate, pActivateView, pDeactiveView);

	// set our title
	GetParentFrame()->SetWindowText(pDoc->GetTitle());

	// make sure the bar is updated for our doc.
	CMainFrame* pFrame = (CMainFrame*)AfxGetMainWnd();

	//	If the application terminates after running a command line
	//	request, we don't want to update this combo box...
	if( pFrame->IsDestroyingApp )
		pFrame->LoadComboBox();
}


void CFusionView::OnToolsBrushMoverotatebrush() 
{
	int mode=GetModeTool();

	if(mode==ID_TOOLS_TEMPLATE)
	{
		SetTool( ID_TOOLS_BRUSH_MOVEROTATEBRUSH );
		App->CLSB_Doc->ConfigureCurrentTool();
	} 
	else 
	{
		if(GetTool()==ID_TOOLS_BRUSH_MOVEROTATEBRUSH)
		{
			SetTool(CURTOOL_NONE);
//			SetAdjustMode (ADJUST_MODE_BRUSH);
			SetAdjustMode (ADJUST_MODE_FACE);
		} 
		else 
		{
			SetTool(ID_TOOLS_BRUSH_MOVEROTATEBRUSH);
		}
		App->CLSB_Doc->ConfigureCurrentTool();
	}
}

void CFusionView::OnUpdateToolsBrushMoverotatebrush(CCmdUI* pCmdUI) 
{
	//that's a pretty big if
	if(GetModeTool()==ID_TOOLS_TEMPLATE ||
		(GetModeTool()==ID_GENERALSELECT &&
//		GetAdjustMode()==ADJUST_MODE_BRUSH &&
App->CLSB_Doc->GetSelState()!=NOSELECTIONS))
	{
		pCmdUI->Enable();
		if(GetTool()==ID_TOOLS_BRUSH_MOVEROTATEBRUSH)
		{
			pCmdUI->SetCheck();
		}
		else 
		{
			pCmdUI->SetCheck(0);
		}
	} 
	else 
	{
		pCmdUI->Enable(0);
		pCmdUI->SetCheck(0);
	}
}


void CFusionView::OnToolsBrushScalebrush() 
{
	
	int mode=GetModeTool();

	if(mode==ID_TOOLS_TEMPLATE)
	{
		SetTool(ID_TOOLS_BRUSH_SCALEBRUSH);
		App->CLSB_Doc->ConfigureCurrentTool();
	} 
	else 
	{
		if(GetTool()==ID_TOOLS_BRUSH_SCALEBRUSH)
		{
			SetTool(CURTOOL_NONE);
//			SetAdjustMode (ADJUST_MODE_BRUSH);
			SetAdjustMode (ADJUST_MODE_FACE);
		} 
		else 
		{
			SetTool(ID_TOOLS_BRUSH_SCALEBRUSH);
		}
		App->CLSB_Doc->ConfigureCurrentTool();
	}
}

void CFusionView::OnUpdateToolsBrushScalebrush(CCmdUI* pCmdUI) 
{
	//that's a very big if
	if((GetModeTool()==ID_TOOLS_TEMPLATE && !App->CLSB_Doc->TempEnt) ||
		(GetModeTool()==ID_GENERALSELECT &&
//		GetAdjustMode ()==ADJUST_MODE_BRUSH &&
#pragma message ("Can't do multiple brush scaling due to Brush_Resize implementation.")
//		SelBrushList_GetSize (pDoc->pSelBrushes) > 0)) 
		SelBrushList_GetSize (App->CLSB_Doc->pSelBrushes) == 1))
	{
		pCmdUI->Enable();
		if(GetTool()==ID_TOOLS_BRUSH_SCALEBRUSH)
		{
			pCmdUI->SetCheck();
		}
		else 
		{
			pCmdUI->SetCheck(0);
		}
	} 
	else 
	{
		pCmdUI->Enable(0);
		pCmdUI->SetCheck(0);
	}
}

void CFusionView::OnToolsBrushShowbrush() 
{
	// toggle brush
	App->CLSB_Doc->mShowBrush ^= 1;

	// redraw the screen
	App->CLSB_Doc->UpdateAllViews(UAV_ALL3DVIEWS, NULL);
}

void CFusionView::OnUpdateToolsBrushShowbrush(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck (App->CLSB_Doc->mShowBrush);
}


BOOL CFusionView::OnEraseBkgnd(CDC* pDC) 
{
/*
	CRect rect ;
//	CFusionDoc* pDoc = GetDocument();

//	if(!pDoc->mWorldBsp || (mViewType != ID_VIEW_TEXTUREVIEW))
	if ((mViewType == ID_VIEW_TOPVIEW) || (mViewType == ID_VIEW_SIDEVIEW) || (mViewType == ID_VIEW_FRONTVIEW))
	{
		GetClientRect( &rect ) ;
		pDC->FillSolidRect( &rect, Prefs_GetBackgroundColor (((CFusionApp *)AfxGetApp ())->GetPreferences ()));
	}
*/
	return TRUE;
}

// This is the range handler for the types of view that we have
// make sure when we add more view types that we update this.
void CFusionView::OnViewType(UINT nID)
{
	/*App->Debug_Message("CFusionView::OnViewType", 0);
	App->Debug_Int(nID, 1);*/
	
	CFusionDoc	*pDoc	=GetDocument();
	mViewType	=nID;

	SizeInfo *WadSizeInfos = Level_GetWadSizeInfos (App->CLSB_Doc->pLevel);

	if(WadSizeInfos)
	{
		geVec3d SaveCameraPos;
		geVec3d SaveOrientation;
		geFloat ZoomFactor;
		int Width, Height;

		ZoomFactor = Render_GetZoom (VCam);
		Render_GetCameraPos (VCam, &SaveCameraPos);
		Render_GetPitchRollYaw (VCam, &SaveOrientation);
		Width = Render_GetWidth (VCam);
		Height = Render_GetHeight (VCam);

		Render_SetWadSizes(VCam, WadSizeInfos);
		Render_ResetSettings(VCam, Render_GetWidth(VCam), Render_GetHeight(VCam));
		Render_ResizeView (VCam, Width, Height);
		Render_SetCameraPos (VCam, &SaveCameraPos);
		Render_SetPitchRollYaw (VCam, &SaveOrientation);
		if (ZoomFactor != 0.0f)
		{
			Render_SetZoom (VCam, ZoomFactor);
		}
	}
	switch(mViewType)
	{
	case ID_VIEW_TEXTUREVIEW:
		Render_SetViewType(VCam, VIEWTEXTURE);
		SetCaption("Camera - Textured");
		mViewIs3d = TRUE ;
		break;
	case ID_VIEW_3DWIREFRAME:
		Render_SetViewType(VCam, VIEWWIRE);
		SetCaption("Camera - Wireframe");
		mViewIs3d = TRUE ;
		break;
	case ID_VIEW_TOPVIEW:
		Render_SetViewType(VCam, VIEWTOP);
		SetCaption("Viewport - Top ( XZ )");
		mViewIs3d = FALSE ;
		break;
	case ID_VIEW_SIDEVIEW:
		Render_SetViewType(VCam, VIEWSIDE);
		SetCaption("Viewport - Side ( ZY )");
		mViewIs3d = FALSE ;
		break;
	case ID_VIEW_FRONTVIEW:
		Render_SetViewType(VCam, VIEWFRONT);
		SetCaption("Viewport - Front ( XY )");
		mViewIs3d = FALSE ;
		break;
	}
	pDoc->UpdateGridInformation ();

	RedrawWindow();
	GetParentFrame()->SetWindowText(pDoc->GetTitle());
}

void CFusionView::OnViewTypeCmdUi(CCmdUI* pCmdUI)
{
	BOOL	bEnable = TRUE ;

	if( !mViewIs3d )	// If this is an otho view, don't allow mutate to rendered
	{
		if( pCmdUI->m_nID == ID_VIEW_TEXTUREVIEW || 
			pCmdUI->m_nID == ID_VIEW_3DWIREFRAME )
			bEnable = FALSE ;
	}
	else				// If this is a rendered view, don't allow mutate to ortho
	{
		if( pCmdUI->m_nID == ID_VIEW_TOPVIEW || 
			pCmdUI->m_nID == ID_VIEW_SIDEVIEW || 
			pCmdUI->m_nID == ID_VIEW_FRONTVIEW )
			bEnable = FALSE ;
	}
	
	if( mViewType == pCmdUI->m_nID )
		pCmdUI->SetCheck();
	else
		pCmdUI->SetCheck(0);

	pCmdUI->Enable( bEnable ) ;
}

void CFusionView::SetTitle()
{
	switch(mViewType)
	{
	case ID_VIEW_NEW:
		GetParentFrame()->SetWindowText("-Creating New View-");
		break;
	case ID_VIEW_3DWIREFRAME:
		GetParentFrame()->SetWindowText("-3D Wireframe-");
		break;
	case ID_VIEW_TEXTUREVIEW:
		GetParentFrame()->SetWindowText("-Texture View-");
		break;
	case ID_VIEW_TOPVIEW:
		GetParentFrame()->SetWindowText("-Top View-");
		break;
	case ID_VIEW_FRONTVIEW:
		GetParentFrame()->SetWindowText("-Front View-");
		break;
	case ID_VIEW_SIDEVIEW:
		GetParentFrame()->SetWindowText("-Side View-");
		break;
	}
}

void CFusionView::OnToolsBrushShearbrush() 
{
	int mode=GetModeTool();

	if(mode==ID_TOOLS_TEMPLATE)
	{
		SetTool( ID_TOOLS_BRUSH_SHEARBRUSH);
		App->CLSB_Doc->ConfigureCurrentTool();
	} 
	else 
	{
		if(GetTool()==ID_TOOLS_BRUSH_SHEARBRUSH)
		{
			SetTool(CURTOOL_NONE);
//			SetAdjustMode (ADJUST_MODE_BRUSH);
			SetAdjustMode (ADJUST_MODE_FACE);
		}
		else 
		{
			SetTool(ID_TOOLS_BRUSH_SHEARBRUSH);
		}
		App->CLSB_Doc->ConfigureCurrentTool();
	}
}


void CFusionView::OnUpdateToolsBrushShearbrush(CCmdUI* pCmdUI) 
{
	//that's a very big if
	if((GetModeTool()==ID_TOOLS_TEMPLATE && !App->CLSB_Doc->TempEnt) ||
		(GetModeTool()==ID_GENERALSELECT &&
//		GetAdjustMode()==ADJUST_MODE_BRUSH &&
#pragma message ("Can't do multiple brush shear due to Brush_Shear implementation.")
		SelBrushList_GetSize (App->CLSB_Doc->pSelBrushes) == 1))
//		SelBrushList_GetSize (pDoc->pSelBrushes) > 0)) 
	{
		pCmdUI->Enable();
		if(GetTool()==ID_TOOLS_BRUSH_SHEARBRUSH)
		{
			pCmdUI->SetCheck();
		}
		else 
		{
			pCmdUI->SetCheck(0);
		}
	} 
	else 
	{
		pCmdUI->Enable(0);
		pCmdUI->SetCheck(0);
	}
}

int CFusionView::GetTool(void)
{
	return App->CLSB_Doc->mCurrentTool;
}

fdocAdjustEnum CFusionView::GetAdjustMode(void)
{
	return App->CLSB_Doc->mAdjustMode;
}

int CFusionView::GetModeTool(void)
{
	return App->CLSB_Doc->mModeTool;
}

void CFusionView::SetTool(int Tool)
{
	App->CLSB_Doc->mCurrentTool = Tool;
}

void CFusionView::SetAdjustMode(fdocAdjustEnum Mode)
{
//	pDoc->mAdjustMode = Mode;
	App->CLSB_Doc->mAdjustMode = ADJUST_MODE_FACE;
}

void CFusionView::SetModeTool(int Tool)
{
	App->CLSB_Doc->mModeTool = Tool;
}


void CFusionView::OnUpdateBrushGroupsMakenewgroup(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable();
}

void CFusionView::OnBrushGroupsAddtogroup() 
{
	CFusionDoc* pDoc = GetDocument();
	
	pDoc->AddSelToGroup() ;

	App->CLSB_Doc->mpMainFrame->UpdateActiveDoc() ;

	pDoc->SetModifiedFlag();
}

void CFusionView::OnUpdateBrushGroupsAddtogroup(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable (!(App->CLSB_Doc->GetSelState() == NOSELECTIONS));
}

void CFusionView::OnBrushRemoveselectedfromgroup() 
{
	CFusionDoc* pDoc = GetDocument();
	
	pDoc->RemovesSelFromGroup() ;
	App->CLSB_Doc->mpMainFrame->UpdateActiveDoc() ;

	pDoc->SetModifiedFlag();

}/* CFusionView::OnBrushRemoveselectedfromgroup */

void CFusionView::OnUpdateBrushRemoveselectedfromgroup(CCmdUI* pCmdUI) 
{
	if( (App->CLSB_Doc->mCurrentGroup == 0) || (App->CLSB_Doc->GetSelState() == NOSELECTIONS) )
		pCmdUI->Enable( FALSE ) ;
	else
		pCmdUI->Enable( TRUE ) ;
}

void CFusionView::OnToolsBrushMoveselectedbrushes() 
{
	SetTool(ID_TOOLS_BRUSH_MOVESELECTEDBRUSHES);
	App->CLSB_Doc->ConfigureCurrentTool();
}

void CFusionView::OnUpdateToolsBrushMoveselectedbrushes(CCmdUI* pCmdUI) 
{
	if(GetModeTool()!=ID_TOOLS_CAMERA) 
	{
		pCmdUI->Enable();
		pCmdUI->SetCheck (GetTool () == ID_TOOLS_BRUSH_MOVESELECTEDBRUSHES);
	} 
	else 
	{
		pCmdUI->Enable(0);
		pCmdUI->SetCheck(0);
	}
}

void CFusionView::OnToolsTemplate() 
{
	CFusionDoc* pDoc = GetDocument();
	pDoc->OnToolsTemplate();
}

void CFusionView::OnUpdateToolsTemplate(CCmdUI* pCmdUI) 
{
	if( GetModeTool() == ID_TOOLS_TEMPLATE ) pCmdUI->SetCheck();
	else pCmdUI->SetCheck(0);
}

void CFusionView::OnUpdateToolsBrushRotate45(CCmdUI* pCmdUI) 
{
	//that's a pretty big if
	if((GetModeTool()==ID_TOOLS_TEMPLATE && !App->CLSB_Doc->TempEnt) ||
	   (GetModeTool()==ID_GENERALSELECT &&
//		GetAdjustMode()==ADJUST_MODE_BRUSH &&
App->CLSB_Doc->GetSelState()!=NOSELECTIONS))
	{
		pCmdUI->Enable();
	}
	else 
	{
		pCmdUI->Enable(0);
	}
}

void CFusionView::DrawLeakPoints(HDC ViewDC, geVec3d *LeakPoints, int NumLeakPoints)
{
	POINT	pnt = {0,0};
	POINT	nullpnt;
	int		i;
	CPen	PenRed(PS_SOLID, 1, RGB(255,0,0));
	HPEN	oldpen;

	assert(LeakPoints != NULL);
	assert(NumLeakPoints > 0);

	oldpen	=(HPEN)SelectObject(ViewDC, (HPEN)PenRed);

	for(i=0;i < NumLeakPoints-1;i++)
	{
		pnt	=Render_OrthoWorldToView(VCam, &LeakPoints[i]);
		MoveToEx(ViewDC, pnt.x, pnt.y, &nullpnt);

		pnt	=Render_OrthoWorldToView(VCam, &LeakPoints[i+1]);
		LineTo(ViewDC, pnt.x, pnt.y);
	}
	LineTo(ViewDC, pnt.x, pnt.y);

	SelectObject(ViewDC, oldpen);
}

void CFusionView::DrawLeakPoints3D(HDC ViewDC, geVec3d *LeakPoints, int NumLeakPoints)
{
	POINT	nullpnt;
	int		i;
	CPen	PenRed(PS_SOLID, 1, RGB(255,0,0));
	HPEN	oldpen;
	geVec3d	pnt3;

	assert(LeakPoints != NULL);
	assert(NumLeakPoints > 0);

	oldpen	=(HPEN)SelectObject(ViewDC, (HPEN)PenRed);
	geVec3d_Clear (&pnt3);

	for(i=0;i < NumLeakPoints-1;i++)
	{
		pnt3	=Render_XFormVert(VCam, &LeakPoints[i]);

		if(pnt3.Z < 0.0f)
			continue;

		MoveToEx(ViewDC, Units_Round(pnt3.X), Units_Round(pnt3.Y), &nullpnt);

		pnt3	=Render_XFormVert(VCam, &LeakPoints[i+1]);
		LineTo(ViewDC, Units_Round(pnt3.X), Units_Round(pnt3.Y));
	}
	if(pnt3.Z > 1.0f)
		LineTo(ViewDC, Units_Round(pnt3.X), Units_Round(pnt3.Y));

	SelectObject(ViewDC, oldpen);
}


void CFusionView::OnDeselectall() 
{
	App->CLSB_Doc->ResetAllSelections() ;
	App->CLSB_Doc->UpdateSelected();
	App->CLSB_Doc->UpdateAllViews( UAV_ALL3DVIEWS, NULL ) ;
}

void CFusionView::OnUpdateDeselectall(CCmdUI* pCmdUI) 
{
	BOOL		bEnable ;

	bEnable = (App->CLSB_Doc->GetSelState() == NOSELECTIONS ) ? FALSE : TRUE ;
	pCmdUI->Enable( bEnable ) ;
}

void CFusionView::OnSelectall() 
{
	App->CLSB_Doc->SelectAll () ;
	App->CLSB_Doc->UpdateAllViews( UAV_ALL3DVIEWS, NULL ) ;
}

void CFusionView::OnUpdateSelectall(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable( TRUE ) ;
}


void CFusionView::OnSelectAllBrushes() 
{
	CFusionDoc* pDoc = GetDocument();

	if (!(IsKeyDown(VK_SHIFT)))
		App->CLSB_Doc->ResetAllSelections() ;
	
	pDoc->SelectAllBrushes () ;
	App->CLSB_Doc->UpdateAllViews( UAV_ALL3DVIEWS, NULL ) ;
}

void CFusionView::OnUpdateSelectAllBrushes(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable( TRUE ) ;
}

LRESULT CFusionView::OnCompileMessage (WPARAM wParam, LPARAM lParam)
{
	if (wParam == COMPILER_PROCESSID)
	{
		char *msg;

		msg = (char *)lParam;
		geRam_Free (msg);
	}
	return 0;
}

LRESULT CFusionView::OnCompileError (WPARAM wParam, LPARAM lParam)
{
	if (wParam == COMPILER_PROCESSID)
	{
		char *msg;

		msg = (char *)lParam;
		geRam_Free (msg);
	}
	return 0;
}

LRESULT CFusionView::OnCompileDone (WPARAM wParam, LPARAM lParam)
{
	if (wParam == COMPILER_PROCESSID)
	{
		CFusionDoc *pDoc;

		pDoc = GetDocument ();

		if (pDoc != NULL)
		{
			pDoc->CompileDone ((CompilerErrorEnum)lParam);
		}
	}
	return 0;
}

void CFusionView::OnToolsScaleworld() 
{
	App->Say("Deleted");
}

void CFusionView::OnToolsSettexturescale() 
{
	CFusionDoc* pDoc = GetDocument();
	float	scf;
	CString	szKey, szVal;
	int		ModalResult;
	CDialog	*pEditDialog;

	szKey = "Enter texture scale for selected brushes";
	szVal = "1.0";
	pEditDialog = new CFloatKeyEditDlg(this, szKey, &szVal);
	if (pEditDialog != NULL)
	{
		ModalResult = pEditDialog->DoModal();
		delete pEditDialog;
		if(ModalResult == IDOK)
		{
			sscanf((LPCSTR)szVal, "%f", &scf);
			App->CLSB_Doc->SetAllFacesTextureScale(scf);
			pDoc->SetModifiedFlag();
		}
	}
}

void CFusionView::OnToolsNextbrush() 
{

	BrushList *BList = Level_GetBrushes (App->CLSB_Doc->pLevel);

	if(GetModeTool()==ID_GENERALSELECT && !App->CLSB_Doc->IsSelectionLocked())
	{
		if(App->CLSB_Doc->GetSelState()&ONEBRUSH)
		{
			if (!(IsKeyDown(VK_SHIFT)))
				SelBrushList_RemoveAll (App->CLSB_Doc->pSelBrushes);
			SelBrushList_Add (App->CLSB_Doc->pSelBrushes, Brush_GetNextBrush(App->CLSB_Doc->CurBrush, BList));
			App->CLSB_Doc->UpdateSelected();
		
			//update the brush attributes dialog...
//			pDoc->UpdateBrushAttributesDlg ();
			App->CLSB_Doc->UpdateAllViews(UAV_ALL3DVIEWS, NULL);
		}
		else if(!(App->CLSB_Doc->GetSelState() & ANYBRUSH))
		{
			Brush *pBrush;
			BrushIterator bi;

			pBrush = BrushList_GetFirst (BList, &bi);
			if(pBrush != NULL)
			{
				SelBrushList_Add (App->CLSB_Doc->pSelBrushes, pBrush);
				App->CLSB_Doc->UpdateSelected();
				App->CLSB_Doc->UpdateAllViews(UAV_ALL3DVIEWS, NULL);
			}
		}
	}
}

void CFusionView::OnToolsPrevbrush() 
{
	BrushList *BList = Level_GetBrushes (App->CLSB_Doc->pLevel);

	if(GetModeTool()==ID_GENERALSELECT && !App->CLSB_Doc->IsSelectionLocked())
	{
		if(App->CLSB_Doc->GetSelState()&ONEBRUSH)
		{
			if (!(IsKeyDown(VK_SHIFT)))
				SelBrushList_RemoveAll (App->CLSB_Doc->pSelBrushes);
			SelBrushList_Add (App->CLSB_Doc->pSelBrushes, Brush_GetPrevBrush(App->CLSB_Doc->CurBrush, BList));
			App->CLSB_Doc->UpdateSelected();
		
			//update the brush attributes dialog...
//			pDoc->UpdateBrushAttributesDlg ();
			App->CLSB_Doc->UpdateAllViews(UAV_ALL3DVIEWS, NULL);
		}
		else if(!(App->CLSB_Doc->GetSelState() & ANYBRUSH))
		{
			Brush *pBrush;
			BrushIterator bi;

			pBrush = BrushList_GetLast(BList, &bi);
			if (pBrush != NULL)
			{
				SelBrushList_Add (App->CLSB_Doc->pSelBrushes, pBrush);
				App->CLSB_Doc->UpdateSelected();
				App->CLSB_Doc->UpdateAllViews(UAV_ALL3DVIEWS, NULL);
			}
		}
	}
}

void CFusionView::OnToolsAddtolevel() 
{
	CFusionDoc *pDoc = GetDocument ();

	if(GetModeTool()==ID_TOOLS_TEMPLATE)
	{
		App->CLSB_Doc->AddBrushToWorld();
		pDoc->SetModifiedFlag();
	}

	App->CLSB_Doc->DoGeneralSelect();
}

void CFusionView::OnUpdateToolsAddtolevel(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	
}

void CFusionView::DoZoom (float ZoomInc)
{
	if (!mViewIs3d)
	{
		CFusionDoc *pDoc = GetDocument ();

		Render_ZoomChange( VCam, ZoomInc);
		pDoc->UpdateGridInformation ();
		pDoc->SetModifiedFlag();
		RedrawWindow();
	}
}

void CFusionView::OnViewZoomin() 
{
	DoZoom (0.1f);
}

void CFusionView::OnUpdateViewZoomin(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	
}

void CFusionView::OnViewZoomout() 
{
	DoZoom (-0.1f);
}

void CFusionView::OnUpdateViewZoomout(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	
}

void CFusionView::HideTheCursor (void)
{
	while (ShowCursor (FALSE) >= 0)
	{
		;
	}
}

void CFusionView::ShowTheCursor (void)
{
	while (ShowCursor (TRUE) < 0)
	{
		;
	}
}

void CFusionView::Drag(dragtime Now)
{
	CDC* c = GetDC();

	CRect NewRect(mDragStartPoint, mDragCurrentPoint );
	NewRect.NormalizeRect();

	LPCRECT lpRect;
	LPCRECT lpRectLast;

	switch (Now)
	{
		case DRAG_BEGIN:
			lpRect = &NewRect;
			lpRectLast = NULL;
			break;
		case DRAG_CONTINUE:
			lpRect = &NewRect;
			lpRectLast = &LastDragRect;
			break;
		default:
			lpRect = &LastDragRect;
			lpRectLast = NULL;
			break;
	}

	SIZE One;
	One.cx = 1;
	One.cy = 1;

	c->DrawDragRect( lpRect, One, lpRectLast, One, NULL, NULL );

	LastDragRect.CopyRect( &NewRect );

	ReleaseDC(c);
}


void CFusionView::OnEditSelectFacesNext() 
{
	BrushList *BList = Level_GetBrushes (App->CLSB_Doc->pLevel);

	if(GetModeTool()==ID_GENERALSELECT && !App->CLSB_Doc->IsSelectionLocked())
	{
		int nSelectedFaces = SelFaceList_GetSize (App->CLSB_Doc->pSelFaces);
		Face *pFace;

		if (nSelectedFaces == 0)
		{
			BrushIterator bi;

			App->CLSB_Doc->CurBrush = BrushList_GetFirst (BList, &bi);
			pFace = Brush_SelectFirstFace (App->CLSB_Doc->CurBrush);
			SelBrushList_Add (App->CLSB_Doc->pSelBrushes, App->CLSB_Doc->CurBrush);
		}
		else
		{
			Brush *pBrush;

			// get first selected face
			pFace = SelFaceList_GetFace (App->CLSB_Doc->pSelFaces, nSelectedFaces-1);
			// Remove all face selections
			if (!(IsKeyDown(VK_SHIFT)))
			{
				App->CLSB_Doc->ResetAllSelectedFaces();
			}

			Face_SetSelected (pFace, GE_TRUE);
			pBrush = BrushList_FindTopLevelFaceParent (Level_GetBrushes (App->CLSB_Doc->pLevel), pFace);

			// select next face
			if(!Brush_SetNextSelectedFace(pBrush))
			{
				pFace = Brush_SelectFirstFace(pBrush);
			}
			else
			{
				pFace = Brush_GetSelectedFace (pBrush);
			}
		}

		SelFaceList_Add (App->CLSB_Doc->pSelFaces, pFace);
		App->CLSB_Doc->UpdateSelected ();
							
		//pDoc->UpdateFaceAttributesDlg ();
		App->CLSB_Doc->UpdateAllViews(UAV_ALL3DVIEWS, NULL);
	}
}

void CFusionView::OnEditSelectFacesPrevious() 
{
	BrushList *BList = Level_GetBrushes (App->CLSB_Doc->pLevel);

	if(GetModeTool()==ID_GENERALSELECT && !App->CLSB_Doc->IsSelectionLocked())
	{
		int nSelectedFaces = SelFaceList_GetSize (App->CLSB_Doc->pSelFaces);
		Face *pFace;

		if (nSelectedFaces == 0)
		{
			BrushIterator bi;

			App->CLSB_Doc->CurBrush = BrushList_GetFirst (BList, &bi);
			pFace = Brush_SelectFirstFace (App->CLSB_Doc->CurBrush);
			SelBrushList_Add (App->CLSB_Doc->pSelBrushes, App->CLSB_Doc->CurBrush);
		}
		else
		{
			Brush *pBrush;

			// get the last selected face
			pFace = SelFaceList_GetFace (App->CLSB_Doc->pSelFaces, 0);

			// Remove all face selections
			if (!(IsKeyDown(VK_SHIFT)))
			{
				App->CLSB_Doc->ResetAllSelectedFaces();
			}

			// Select the next face in order, using selected brush list...
			pBrush = BrushList_FindTopLevelFaceParent (Level_GetBrushes (App->CLSB_Doc->pLevel), pFace);
			Face_SetSelected (pFace, GE_TRUE);

			// select next face
			if(!Brush_SetPrevSelectedFace(pBrush))
			{
				pFace = Brush_SelectLastFace(pBrush);
			}
			else
			{
				pFace = Brush_GetSelectedFace (pBrush);
			}
		}

		SelFaceList_Add (App->CLSB_Doc->pSelFaces, pFace);
		App->CLSB_Doc->UpdateSelected ();
							
		//pDoc->UpdateFaceAttributesDlg ();
		App->CLSB_Doc->UpdateAllViews(UAV_ALL3DVIEWS, NULL);
	}

}


void CFusionView::OnEditSelectFacesAllinselectedbrushes() 
{
	App->CLSB_Doc->SelectAllFacesInBrushes();
	App->CLSB_Doc->UpdateAllViews( UAV_ALL3DVIEWS, NULL ) ;
}

void CFusionView::OnEditSelectEntitiesAll() 
{
	CFusionDoc* pDoc = GetDocument();

	if (!(IsKeyDown(VK_SHIFT)))
		App->CLSB_Doc->ResetAllSelections() ;
	
	pDoc->SelectAllEntities () ;
	App->CLSB_Doc->UpdateAllViews( UAV_ALL3DVIEWS, NULL ) ;
}


void CFusionView::OnEditSelectEntitiesNext() 
{
	CFusionDoc* pDoc = GetDocument();

	if(GetModeTool()==ID_GENERALSELECT && !App->CLSB_Doc->IsSelectionLocked())
	{

		CEntityArray *Entities;
		Entities = Level_GetEntities (App->CLSB_Doc->pLevel);

		int NumEntities = Entities->GetSize();

		if (NumEntities)
		{
			if (App->CLSB_Doc->NumSelEntities == 0)
			{
				pDoc->SelectEntity(&(*Entities)[0]);
				App->CLSB_Doc->UpdateSelected ();
				App->CLSB_Doc->UpdateAllViews(UAV_ALL3DVIEWS, NULL);
			}
			else
			{
				CEntity *NextEntity = NULL;

				// Find the last selected entity
				for (int i=(NumEntities-1);i>-1;i--)
				{
					if ((*Entities)[i].IsSelected())
					{
						// If the last selected entity is also the last
						// entity, then find the first unselected entity
						if (i==(NumEntities-1))
						{
							for (int j=0;j<NumEntities;j++)
							{
								if (!((*Entities)[j].IsSelected()))
								{
									NextEntity = &(*Entities)[j];
									break;
								}
							}
						}

						// Otherwise, the next entity is the entity after
						// the last selected entity
						else
						{
							NextEntity = &(*Entities)[i+1];
						}

						break;
					}
				}

				if (NextEntity)
				{
					if (!(IsKeyDown(VK_SHIFT)))
						App->CLSB_Doc->ResetAllSelectedEntities();

					pDoc->SelectEntity(NextEntity);
					App->CLSB_Doc->UpdateSelected ();
					App->CLSB_Doc->UpdateAllViews(UAV_ALL3DVIEWS, NULL);
				}
			}
		}
	}
}

void CFusionView::OnEditSelectEntitiesPrevious() 
{
	CFusionDoc* pDoc = GetDocument();

	if(GetModeTool()==ID_GENERALSELECT && !App->CLSB_Doc->IsSelectionLocked())
	{

		CEntityArray *Entities;
		Entities = Level_GetEntities (App->CLSB_Doc->pLevel);

		int NumEntities = Entities->GetSize();

		if (NumEntities)
		{
			if (App->CLSB_Doc->NumSelEntities == 0)
			{
				pDoc->SelectEntity(&(*Entities)[0]);
				App->CLSB_Doc->UpdateSelected ();
				App->CLSB_Doc->UpdateAllViews(UAV_ALL3DVIEWS, NULL);
			}
			else
			{
				CEntity *NextEntity = NULL;

				// Find the first selected entity
				for (int i=0;i<NumEntities;i++)
				{
					if ((*Entities)[i].IsSelected())
					{
						// If the last selected entity is also the last
						// entity, then find the first unselected entity
						if (i==0)
						{
							for (int j=(NumEntities-1);j>-1;j--)
							{
								if (!((*Entities)[j].IsSelected()))
								{
									NextEntity = &(*Entities)[j];
									break;
								}
							}
						}

						// Otherwise, the next entity is the entity after
						// the last selected entity
						else
						{
							NextEntity = &(*Entities)[i-1];
						}

						break;
					}
				}

				if (NextEntity)
				{
					if (!(IsKeyDown(VK_SHIFT)))
						App->CLSB_Doc->ResetAllSelectedEntities();

					pDoc->SelectEntity(NextEntity);
					App->CLSB_Doc->UpdateSelected ();
					App->CLSB_Doc->UpdateAllViews(UAV_ALL3DVIEWS, NULL);
				}
			}
		}
	}
}

void CFusionView::OnEditDeselectBrushes() 
{
	CFusionDoc* pDoc = GetDocument();

	App->CLSB_Doc->ResetAllSelectedBrushes() ;
	App->CLSB_Doc->UpdateSelected();
	App->CLSB_Doc->UpdateAllViews( UAV_ALL3DVIEWS, NULL ) ;
}

void CFusionView::OnEditDeselectEntities() 
{
	CFusionDoc* pDoc = GetDocument();

	App->CLSB_Doc->ResetAllSelectedEntities() ;
	App->CLSB_Doc->UpdateSelected();
	App->CLSB_Doc->UpdateAllViews( UAV_ALL3DVIEWS, NULL ) ;
}

void CFusionView::OnEditDeselectFaces() 
{
	CFusionDoc* pDoc = GetDocument();

	App->CLSB_Doc->ResetAllSelectedFaces() ;
	App->CLSB_Doc->UpdateSelected();
	App->CLSB_Doc->UpdateAllViews( UAV_ALL3DVIEWS, NULL ) ;
}

void CFusionView::OnUpdateEditDeselectBrushes(CCmdUI* pCmdUI) 
{
	BOOL		bEnable ;
	bEnable = (App->CLSB_Doc->GetSelState() & ANYBRUSH ) ? TRUE : FALSE ;
	pCmdUI->Enable( bEnable ) ;	
}

void CFusionView::OnUpdateEditDeselectEntities(CCmdUI* pCmdUI) 
{
	BOOL		bEnable ;
	bEnable = (App->CLSB_Doc->GetSelState() & ANYENTITY ) ? TRUE : FALSE ;
	pCmdUI->Enable( bEnable ) ;
}

void CFusionView::OnUpdateEditDeselectFaces(CCmdUI* pCmdUI) 
{
	BOOL		bEnable ;
	bEnable = (App->CLSB_Doc->GetSelState() & ANYFACE ) ? TRUE : FALSE ;
	pCmdUI->Enable( bEnable ) ;
}

void CFusionView::OnKillFocus(CWnd* pNewWnd) 
{
	CCaptionView::OnKillFocus(pNewWnd);
	
	((CChildFrame*)GetParentFrame())->m_wndSplitter.RefreshSplitBars();
}

void CFusionView::OnSetFocus(CWnd* pOldWnd) 
{
	CCaptionView::OnSetFocus(pOldWnd);
	
	((CChildFrame*)GetParentFrame())->m_wndSplitter.RefreshSplitBars();
}

void CFusionView::OnMouseHover(POINT pt)
{
	
	m_strObjectUnderPoint="";

	CFusionDoc* pDoc = GetDocument();
	if(pDoc)
	{
		if(mViewIs3d)
		{
			m_strObjectUnderPoint = pDoc->GetObjectName3D(pt, VCam);
			if (m_strObjectUnderPoint)
			{
				CMainFrame* pFrame = (CMainFrame*)AfxGetMainWnd();
				pFrame->SetCursorInfo(m_strObjectUnderPoint);
			}

		}
	}
/*
			m_strObjectUnderPoint = pDoc->GetObjectName3D(pt, VCam);

		else
			m_strObjectUnderPoint = pDoc->ReturnThingUnderPoint(pt, VCam);
		
		if( m_strObjectUnderPoint.IsEmpty())
			pDoc->mpMainFrame->m_NameWindow.Hide();
		else
			pDoc->mpMainFrame->m_NameWindow.Show(m_strObjectUnderPoint);
	}
*/
}

BOOL CFusionView::PreTranslateMessage(MSG* pMsg) 
{
	//App->Flash_Window();

	if(pMsg->message == WM_MOUSEHOVER)
	{
		POINTS point = MAKEPOINTS(pMsg->lParam);
		CPoint pt;
		pt.x = point.x;
		pt.y = point.y;
		OnMouseHover(pt);
		return 0;
	}
	else if( pMsg->message == WM_MOUSELEAVE )
	{
/*
		CFusionDoc* pDoc = GetDocument();
		if(pDoc)
			pDoc->mpMainFrame->m_NameWindow.Hide();
*/
		return 0;
	}
	return CCaptionView::PreTranslateMessage(pMsg);
}


void CFusionView::OnViewportCenteroncamera() 
{
	CFusionDoc *pDoc = GetDocument ();
	if(!pDoc)
		return;

	if(mViewIs3d)
	{
		return;
	}
	else
	{

		CEntity *p = App->CLSB_Camera_WE->FindCameraEntity();
		if(!p)
			return;
		
		Render_SetCameraPos(VCam, &p->mOrigin);

		App->CLSB_Doc->LinkViewports();
		pDoc->SetModifiedFlag();
		RedrawWindow();
	}
}

void CFusionView::OnUpdateViewportCenteroncamera(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(!(mViewIs3d));
}



void CFusionView::OnViewportCenteronselection() 
{
	CFusionDoc *pDoc = GetDocument ();
	if(!pDoc)
		return;

	Render_SetCameraPos(VCam, &App->CLSB_Doc->SelectedGeoCenter);

	App->CLSB_Doc->LinkViewports();
	pDoc->SetModifiedFlag();
	RedrawWindow();
}

void CFusionView::OnUpdateViewportCenteronselection(CCmdUI* pCmdUI) 
{
	if (mViewIs3d)
		pCmdUI->Enable( FALSE );
	else
	{
		CFusionDoc *pDoc = GetDocument ();
		if (pDoc) {
			if ((App->CLSB_Doc->GetSelState()!=NOSELECTIONS) || (App->CLSB_Doc->mModeTool == ID_TOOLS_TEMPLATE))
				pCmdUI->Enable( TRUE );
			else
				pCmdUI->Enable( FALSE );
		}
		else
			pCmdUI->Enable( FALSE );
	}
}

void CFusionView::OnCameraCenteronview() 
{
	if (mViewIs3d)
		return;

	CFusionDoc *pDoc = GetDocument ();
	if(!pDoc)
		return;

	CEntity *pCameraEntity = App->CLSB_Camera_WE->FindCameraEntity();

	if (pCameraEntity)
	{
		geVec3d CurrentPosition;
		Render_GetCameraPos(VCam, &CurrentPosition);
		
		geVec3d Angles;
		pCameraEntity->GetAngles( &Angles, Level_GetEntityDefs (App->CLSB_Doc->pLevel) );

		switch (mViewType)
		{
			case ID_VIEW_TOPVIEW :
				pCameraEntity->mOrigin.X = CurrentPosition.X;
				pCameraEntity->mOrigin.Z = CurrentPosition.Z;
				break;

			case ID_VIEW_SIDEVIEW :
				pCameraEntity->mOrigin.X = CurrentPosition.X;
				pCameraEntity->mOrigin.Y = CurrentPosition.Y;
				break;

			case ID_VIEW_FRONTVIEW :
				pCameraEntity->mOrigin.Z = CurrentPosition.Z;
				pCameraEntity->mOrigin.Y = CurrentPosition.Y;
				break;

			default :
				// don't do nothin!
				assert (0);
		}
		
		pDoc->SetRenderedViewCamera( &(pCameraEntity->mOrigin), &Angles) ;
		pDoc->SetModifiedFlag();
		App->CLSB_Doc->UpdateAllViews( UAV_ALLVIEWS, NULL );
	}
}

void CFusionView::OnUpdateCameraCenteronview(CCmdUI* pCmdUI) 
{
	if (mViewIs3d)
		pCmdUI->Enable(FALSE);
	else
		pCmdUI->Enable(TRUE);
}

void CFusionView::OnViewportGoto() 
{
	App->Say("Needs Move Dialog");
	/*geBoolean ShowX = GE_TRUE;
	geBoolean ShowY = GE_TRUE;
	geBoolean ShowZ = GE_TRUE;

	geVec3d CurrentPosition;
	Render_GetCameraPos(VCam, &CurrentPosition);
	geVec3d NewPos = CurrentPosition;
	
	switch (mViewType)
	{
		case ID_VIEW_TOPVIEW :
			ShowY = GE_FALSE;
			break;

		case ID_VIEW_SIDEVIEW :
			ShowX = GE_FALSE;
			break;

		case ID_VIEW_FRONTVIEW :
			ShowZ = GE_FALSE;
			break;

		default :
			assert(0);
	}

	CMoveDialog MoveDialog;

	if (MoveDialog.DoModal(&CurrentPosition, ShowX, ShowY, ShowZ) == IDOK)
	{
		switch (mViewType)
		{
			case ID_VIEW_TOPVIEW :
				NewPos.X = CurrentPosition.X;
				NewPos.Z = CurrentPosition.Z;
				break;

			case ID_VIEW_SIDEVIEW :
				NewPos.Y = CurrentPosition.Y;
				NewPos.Z = CurrentPosition.Z;
				break;

			case ID_VIEW_FRONTVIEW :
				NewPos.X = CurrentPosition.X;
				NewPos.Y = CurrentPosition.Y;
				break;

			default :
				assert(0);
		}

		Render_SetCameraPos(VCam, &NewPos);
		
		CFusionDoc *pDoc = GetDocument();
		if (pDoc)
		{
			pDoc->LinkViewports();
			pDoc->SetModifiedFlag();
		}

		RedrawWindow();
	}*/
}

void CFusionView::OnUpdateViewportGoto(CCmdUI* pCmdUI) 
{
	if (mViewIs3d)
		pCmdUI->Enable(FALSE);
	else
		pCmdUI->Enable(TRUE);
}

void CFusionView::OnModifyRotate() 
{
	CFusionDoc *pDoc = GetDocument ();
	if(!pDoc)
		return;

	geFloat RotateRadians;

	CRotateDialog RotateDialog;

	if (RotateDialog.DoModal(&RotateRadians) == IDOK)
	{

		geVec3d	RotateVector;
		geVec3d_Clear (&RotateVector);

		switch (mViewType)
		{
			case ID_VIEW_TOPVIEW:
				RotateVector.Y = RotateRadians;
				break;
			case ID_VIEW_FRONTVIEW :
				RotateVector.Z = RotateRadians;
				break;
			case ID_VIEW_SIDEVIEW:
				RotateVector.X = -RotateRadians;
				break;
			default :
				assert(0);
				return;
		}

		if(GetModeTool()==ID_TOOLS_TEMPLATE)
		{
			App->CLSB_Doc->RotateTemplateBrush(&RotateVector);
			App->CLSB_Doc->UpdateSelected();
			App->CLSB_Doc->UpdateAllViews(UAV_ALL3DVIEWS, NULL);
		}
		else
		{
			pDoc->RotateSelectedBrushesDirect (&RotateVector);
			pDoc->SetModifiedFlag();
			App->CLSB_Doc->UpdateAllViews(UAV_ALL3DVIEWS | REBUILD_QUICK, NULL);
		}
	}
}

void CFusionView::OnUpdateModifyRotate(CCmdUI* pCmdUI) 
{
	if (mViewIs3d)
	{
		pCmdUI->Enable(FALSE);
		return;
	}

	CFusionDoc *pDoc = GetDocument ();
	if(!pDoc)
	{
		pCmdUI->Enable( FALSE );
		return;
	}

	if ((App->CLSB_Doc->GetSelState()!=NOSELECTIONS) || ((App->CLSB_Doc->mModeTool==ID_TOOLS_TEMPLATE) && !App->CLSB_Doc->PlaceObjectFlag))
		pCmdUI->Enable( TRUE );
	else
		pCmdUI->Enable( FALSE );
}

