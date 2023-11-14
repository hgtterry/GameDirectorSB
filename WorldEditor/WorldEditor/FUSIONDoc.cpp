/****************************************************************************************/
/*  FusionDoc.cpp                                                                       */
/*                                                                                      */
/*  Author:       Jim Mischel, Ken Baird, Jeff Lomax, John Moore, Bruce Cooner          */
/*  Description:  A very large file that does too much to describe                      */
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
#include "FUSIONDoc.h"
#include <float.h>
#include <fstream>

#include "gridsizedialog.h"
#include "Entity.h"
#include "entitiesdialog.h"
#include "FaceAttributesDialog.h"
#include "BrushAttributesDialog.h"
#include "KeyEditDlg.h"
#include "FusionTabControls.h"
#include "EntityVisDlg.h"
#include "LevelOptions.h"
#include "ScaleDialog.h"

#include "FUSIONView.h"
#include "wadfile.h"
#include "XForm3d.h"
#include "gbsplib.h"
#include "render.h"
#include "EntityTable.h"
#include "brush.h"
#include "node.h"
#include "facelist.h"
// changed QD 12/03
#include "Export3dsDialog.h"
// end change

#include <afxole.h>
#pragma warning(disable : 4201 4214 4115 4477)
#include <mmsystem.h>
#pragma warning(default : 4201 4214 4115)
#include <errno.h>
#include <direct.h>
#include <assert.h>
#include "basetype.h"
#include "Vec3d.h"
#include "brush.h"
#include "typeio.h"
#include "units.h"
#include "FilePath.h"
#include <io.h>		// for _access
#include "ram.h"
#include "util.h"
#include "BrushTemplate.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

// Must be within this distance (in pixels) to select anything.
// (Yes, 10,000 is a big number.  Right now we want to select the closest thing,
// no matter how far away it is...)
#define MAX_PIXEL_SELECT_DIST (100)
#define MIN_ENTITY_SELECT_DIST (8.0f)
#define MAX_PIXEL_SELECT_THINGNAME (20)

// Maximum distance from entity in order for it to be selected.
// This is in world space coordinates and is used in rendered view only.
#define MAX_ENTITY_SELECT_DIST (16.0f)

#define CAMERA_MOVEMENT_DISTANCE (32.0f)
#define CAMERA_MOVEMENT_ANGLE (M_PI/16.0f)


IMPLEMENT_SERIAL(CFusionDoc, CDocument, 0);
BEGIN_MESSAGE_MAP(CFusionDoc, CDocument)
    //{{AFX_MSG_MAP(CFusionDoc)
    ON_COMMAND(ID_TOOLS_USEGRID, OnToolsUsegrid)
    ON_UPDATE_COMMAND_UI(ID_TOOLS_USEGRID, OnUpdateToolsUsegrid)
    ON_COMMAND(ID_TOOLS_GRIDSETTINGS, OnToolsGridsettings)
    ON_COMMAND(ID_EDIT_UNDO, OnEditUndo)
    ON_UPDATE_COMMAND_UI(ID_EDIT_UNDO, OnUpdateEditUndo)
    ON_COMMAND(ID_EDIT_REDO, OnEditRedo)
    ON_UPDATE_COMMAND_UI(ID_EDIT_REDO, OnUpdateEditRedo)
    ON_COMMAND(ID_ENTITIES_EDITOR, OnEntitiesEditor)
    ON_COMMAND(ID_ENTITIES_SHOW, OnEntitiesShow)
    ON_UPDATE_COMMAND_UI(ID_ENTITIES_SHOW, OnUpdateEntitiesShow)
    ON_COMMAND(ID_VIEW_SHOW_ALLGROUPS, OnViewShowAllGroups)
    ON_COMMAND(ID_VIEW_SHOW_CURRENTGROUP, OnViewShowCurrentGroup)
    ON_COMMAND(ID_VIEW_SHOW_VISIBLEGROUPS, OnViewShowVisibleGroups)
    ON_UPDATE_COMMAND_UI(ID_VIEW_SHOW_VISIBLEGROUPS, OnUpdateViewShowVisibleGroups)
    ON_UPDATE_COMMAND_UI(ID_VIEW_SHOW_ALLGROUPS, OnUpdateViewShowAllGroups)
    ON_UPDATE_COMMAND_UI(ID_VIEW_SHOW_CURRENTGROUP, OnUpdateViewShowCurrentGroup)
    ON_UPDATE_COMMAND_UI(ID_TOOLS_BRUSH_ADJUSTMENTMODE, OnUpdateBrushAdjustmentmode)
    ON_COMMAND(ID_BRUSH_SELECTED_COPYTOCURRENT, OnBrushSelectedCopytocurrent)
    ON_COMMAND(ID_BRUSH_SELECTED_DELETE, OnBrushSelectedDelete)
    ON_COMMAND(ID_GBSPNOWATER, OnGbspnowater)
    ON_UPDATE_COMMAND_UI(ID_TOOLS_FACE_ADJUSTMENTMODE, OnUpdateFaceAdjustmentmode)
    ON_COMMAND(ID_CONSTRAINHOLLOWS, OnConstrainhollows)
    ON_UPDATE_COMMAND_UI(ID_CONSTRAINHOLLOWS, OnUpdateConstrainhollows)
    ON_COMMAND(ID_GENERALSELECT, OnGeneralselect)
    ON_UPDATE_COMMAND_UI(ID_GENERALSELECT, OnUpdateGeneralselect)
    ON_COMMAND(ID_BRUSH_SUBTRACTFROMWORLD, OnBrushSubtractfromworld)
    ON_COMMAND(ID_EDIT_COPY, OnEditCopy)
    ON_COMMAND(ID_EDIT_PASTE, OnEditPaste)
    ON_UPDATE_COMMAND_UI(ID_EDIT_COPY, OnUpdateEditCopy)
    ON_UPDATE_COMMAND_UI(ID_EDIT_PASTE, OnUpdateEditPaste)
    ON_COMMAND(ID_EDIT_CUT, OnEditCut)
    ON_UPDATE_COMMAND_UI(ID_EDIT_CUT, OnUpdateEditCut)
    ON_COMMAND(ID_COMPILE, OnCompile)
    ON_UPDATE_COMMAND_UI(ID_BRUSH_SUBTRACTFROMWORLD, OnUpdateBrushSubtractfromworld)
    ON_UPDATE_COMMAND_UI(ID_ENTITIES_EDITOR, OnUpdateEntitiesEditor)
    ON_COMMAND(ID_NEW_LIB_OBJECT, OnNewLibObject)
    ON_COMMAND(ID_FILE_OPEN, OnFileOpen)
    ON_COMMAND(ID_TOOLS_BRUSH_ADJUSTMENTMODE, OnToolsBrushAdjustmentmode)
    ON_COMMAND(ID_TOOLS_FACE_ADJUSTMENTMODE, OnToolsFaceAdjustmentmode)
    ON_UPDATE_COMMAND_UI(ID_BRUSH_PRIMITIVES_CUBE, OnUpdateBrushPrimitives)
    ON_COMMAND(ID_BRUSH_PRIMITIVES_CUBE, OnBrushPrimitivesCube)
    ON_COMMAND(ID_BRUSH_PRIMITIVES_SPHEROID, OnBrushPrimitivesSpheroid)
    ON_COMMAND(ID_BRUSH_PRIMITIVES_CYLINDER, OnBrushPrimitivesCylinder)
    ON_COMMAND(ID_BRUSH_PRIMITIVES_STAIRCASE, OnBrushPrimitivesStaircase)
    ON_COMMAND(ID_VIEW_SHOW_CLIP, OnViewShowClip)
    ON_UPDATE_COMMAND_UI(ID_VIEW_SHOW_CLIP, OnUpdateViewShowClip)
    ON_COMMAND(ID_VIEW_SHOW_DETAIL, OnViewShowDetail)
    ON_UPDATE_COMMAND_UI(ID_VIEW_SHOW_DETAIL, OnUpdateViewShowDetail)
    ON_COMMAND(ID_VIEW_SHOW_HINT, OnViewShowHint)
    ON_UPDATE_COMMAND_UI(ID_VIEW_SHOW_HINT, OnUpdateViewShowHint)
    ON_COMMAND(ID_EDIT_DELETE, OnEditDelete)
    ON_COMMAND(ID_BRUSH_PRIMITIVES_ARCH, OnBrushPrimitivesArch)
    ON_COMMAND(ID_BRUSH_PRIMITIVES_CONE, OnBrushPrimitivesCone)
    ON_COMMAND(ID_FILE_IMPORT, OnFileImport)
    ON_COMMAND(ID_IMPORT_GENESIS3DACTOR, OnFileImportActor)
    ON_COMMAND(ID_ENTITYVISIBILITY, OnEntityVisibility)
    ON_COMMAND(IDM_REBUILD_BSP, OnRebuildBsp)
    ON_UPDATE_COMMAND_UI(IDM_REBUILD_BSP, OnUpdateRebuildBsp)
    ON_COMMAND(ID_FILE_SAVE_AS, OnFileSaveAs)
    ON_COMMAND(ID_TOOLS_TOGGLEADJUSTMODE, OnToolsToggleadjustmode)
    ON_UPDATE_COMMAND_UI(ID_TOOLS_TOGGLEADJUSTMODE, OnUpdateToolsToggleadjustmode)
    ON_COMMAND(IDM_LEVELOPTIONS, OnLeveloptions)
    ON_COMMAND(ID_CAMERA_FORWARD, OnCameraForward)
    ON_COMMAND(ID_CAMERA_BACK, OnCameraBack)
    ON_COMMAND(ID_CAMERA_LEFT, OnCameraLeft)
    ON_COMMAND(ID_CAMERA_RIGHT, OnCameraRight)
    ON_COMMAND(ID_CAMERA_LOOK_UP, OnCameraLookUp)
    ON_COMMAND(ID_CAMERA_LOOK_DOWN, OnCameraLookDown)
    ON_COMMAND(ID_CAMERA_UP, OnCameraUp)
    ON_COMMAND(ID_CAMERA_DOWN, OnCameraDown)

    ON_COMMAND(ID_FILE_EXPORT_OLDEXPORT, OnFileExport) // Old Exporter
    ON_UPDATE_COMMAND_UI(ID_FILE_EXPORT_OLDEXPORT, OnUpdateFileExport) // Old Exporter

    ON_COMMAND(ID_FILE_EXPORTGDSB_GAMEDIRECTORG3DS, OnFileExportGDSB) //  hgtterry [100123]
    ON_COMMAND(ID_EXPORT_WAVEFRONTOBJECT, OnFileExportObject) //  WaveFront Object
    ON_COMMAND(ID_OGRE3D_MESH, OnFileExport_Ogre3D_Mesh) //  Ogre3D Mesh
    
    ON_UPDATE_COMMAND_UI(ID_FILE_EXPORTGDSB_GAMEDIRECTORG3DS, OnUpdateFileExportGDSB) //  hgtterry [100123]

    ON_COMMAND( ID_VIEW_3DWIREFRAME, OnViewTypeWireFrame)

    // EquitySB
    ON_COMMAND( ID_VIEW_TEXTUREVIEW, OnViewTypeTexture) // hgtterry Menu Commands
    ON_COMMAND( ID_DEBUG_SETVIEW, OnEquity_SetView) 
    ON_COMMAND( ID_EQUITYSB_ZEROCAMERA, Zero_Camera) 
    ON_COMMAND( ID_WINDOW_QUICKCOMMAND, Start_QuickView) 
    ON_COMMAND(ID_WINDOW_COMMANDPANEL, Start_CommandPanel) 
    ON_COMMAND(ID_FILE_RECENT, Start_RecentFiles)
    ON_COMMAND(ID_FILE_SAVESB, Save_SB)
    
    ON_UPDATE_COMMAND_UI(ID_VIEW_3DWIREFRAME, OnUpdateViewTypeWireFrame)
    ON_UPDATE_COMMAND_UI(ID_VIEW_TEXTUREVIEW, OnUpdateViewTypeTexture)
    ON_COMMAND(ID_CAMERA_CENTERONSELECTION, OnCameraCenteronselection)
    ON_UPDATE_COMMAND_UI(ID_CAMERA_CENTERONSELECTION, OnUpdateCameraCenteronselection)
    ON_COMMAND(ID_ENTITIES_PLACELIGHT, OnPlaceOmniLight)
    ON_COMMAND(ID_TEMPLATE_SPOTLIGHT, OnPlaceSpotLight)
    ON_COMMAND(ID_CAMERA_GOTO, OnCameraGoto)
    ON_COMMAND(ID_MODE_MOVE, OnModifyMove)
    ON_UPDATE_COMMAND_UI(ID_MODE_MOVE, OnUpdateModifyMove)
    ON_COMMAND(ID_MODE_SCALE, OnModifyScale)
    ON_UPDATE_COMMAND_UI(ID_MODE_SCALE, OnUpdateModifyScale)
    ON_COMMAND(ID_TOOLS_BRUSH_MAKENEWEST, OnToolsBrushMakenewest)
    ON_UPDATE_COMMAND_UI(ID_TOOLS_BRUSH_MAKENEWEST, OnUpdateToolsBrushMakenewest)
    ON_COMMAND(ID_VIEWPORT_LINKVIEWPORTS, OnLinkviewports)
    ON_UPDATE_COMMAND_UI(ID_VIEWPORT_LINKVIEWPORTS, OnUpdateLinkviewports)
    ON_COMMAND(ID_TEMPLATE_SUNLIGHT, OnTemplateSunlight)
    ON_UPDATE_COMMAND_UI(ID_EDIT_COPY, OnUpdateEditCopy)
    ON_UPDATE_COMMAND_UI(ID_EDIT_PASTE, OnUpdateEditPaste)
    ON_UPDATE_COMMAND_UI(ID_BRUSH_PRIMITIVES_SPHEROID, OnUpdateBrushPrimitives)
    ON_UPDATE_COMMAND_UI(ID_BRUSH_PRIMITIVES_CYLINDER, OnUpdateBrushPrimitives)
    ON_UPDATE_COMMAND_UI(ID_BRUSH_PRIMITIVES_STAIRCASE, OnUpdateBrushPrimitives)
    ON_UPDATE_COMMAND_UI(ID_BRUSH_PRIMITIVES_ARCH, OnUpdateBrushPrimitives)
    ON_UPDATE_COMMAND_UI(ID_BRUSH_PRIMITIVES_CONE, OnUpdateBrushPrimitives)
    ON_UPDATE_COMMAND_UI(ID_ENTITIES_PLACELIGHT, OnUpdateBrushPrimitives)
    ON_UPDATE_COMMAND_UI(ID_TEMPLATE_SPOTLIGHT, OnUpdateBrushPrimitives)
    ON_UPDATE_COMMAND_UI(ID_TEMPLATE_SUNLIGHT, OnUpdateBrushPrimitives)
// changed QD Actors
    ON_COMMAND(ID_VIEW_SHOW_ACTORS, OnViewShowActors)
    ON_UPDATE_COMMAND_UI(ID_VIEW_SHOW_ACTORS, OnUpdateViewShowActors)
// end change
    //}}AFX_MSG_MAP
    ON_UPDATE_COMMAND_UI_RANGE(  ID_BRUSH_SELECTED_DELETE, ID_BRUSH_SELECTED_COPYTOCURRENT, OnSelectedTypeCmdUI)
END_MESSAGE_MAP()



#pragma warning (disable:4100)
void CFusionDoc::Serialize(CArchive& ar)
{
    _ASSERTE(0);
}
#pragma warning (default:4100)


WadFileEntry* CFusionDoc::GetDibBitmap(const char *Name)
{
    return Level_GetWadBitmap (App->CLSB_Doc->pLevel, Name);
}

const char *CFusionDoc::FindTextureLibrary (char const *WadName)
{
    static char WorkPath[MAX_PATH];
    const Prefs  *pPrefs;

    ::FilePath_AppendName (LastPath, WadName, WorkPath);
    if (_access (WorkPath, 0) == 0)
    {
        return WorkPath;
    }

    pPrefs = GetPrefs ();
    if (FilePath_SearchForFile (WadName, Prefs_GetTxlSearchPath (pPrefs), WorkPath))
    {
        return WorkPath;
    }
// changed QD 01/04
//	return NULL;
// code from RFEdit Pro
    else
    {
        CString	txlPathError = _T("World Editor checks for the default *.txl file when opening new worlds.\n\n");
        txlPathError += _T("World Editor now is looking for:\n\n");
        txlPathError += _T(WorkPath);
        txlPathError += _T("\n\nbut cannot find it.\n\n");
        txlPathError += _T("To avoid this message in the future, place or rename a *.txl file as: ");
        txlPathError += _T(WadName);
        txlPathError += _T("\ninto the above path. Or edit the WrldEdit.ini file to reflect\n");
        txlPathError += _T("the name of your default *.txl file.\n\n");
        txlPathError += _T("For now, please select a valid *.txl file");// or the application will exit.");

        MessageBox(NULL, txlPathError, "World Editor cannot find default *.txl", MB_OK);

        CFileDialog FileDlg (TRUE, "txl", WorkPath,	OFN_FILEMUSTEXIST | OFN_NOCHANGEDIR,
            "Texture Library Files (*.txl)|*.txl||");

        FileDlg.m_ofn.lpstrTitle	="World Editor Texture Finder";

        if (FileDlg.DoModal () == IDOK)
        {
            CString	wadpath = FileDlg.GetPathName();
            CString wadFileName = FileDlg.GetFileName();
            strcpy(WorkPath, wadpath.GetBuffer(260));
            // set the Prefs wadfile to THIS one -- this session only
            Prefs_SetTxlName((Prefs*)pPrefs, wadFileName.GetBuffer(64));
        }

        return WorkPath;
    }
// end change
}

CFusionDoc::CFusionDoc() : CDocument(),

NumLeakPoints(0), bLeakLoaded(FALSE), bShowLeak(TRUE),
bShowClipBrushes(GE_TRUE), bShowDetailBrushes(GE_TRUE), bShowHintBrushes(GE_TRUE), bShowActors(GE_TRUE)/*changed QD*/,
mpActiveViewFrame(NULL)
    
{
    const char *DefaultWadName;
    const Prefs  *pPrefs = GetPrefs ();

    LastTemplateTypeName = "Box";

    DefaultWadName = Prefs_GetTxlName (pPrefs);

    strcpy (LastPath, Prefs_GetProjectDir (pPrefs));

    const char *WadPath = FindTextureLibrary (DefaultWadName);

// changed QD 01/04
/*
    if (WadPath == NULL)
    {
        AfxMessageBox ("Error: Unable to find texture library.", MB_OK + MB_ICONERROR);
    }
*/
// end change
// changed QD Actors
    
    App->CLSB_Doc->pLevel = Level_Create (WadPath, Prefs_GetHeadersList (pPrefs),
        Prefs_GetActorsList (pPrefs), Prefs_GetPawnIni (pPrefs));
// end change
    if (!Level_LoadWad (App->CLSB_Doc->pLevel))
    {
        CString Msg;

        AfxFormatString1 (Msg, IDS_CANTLOADTXL, WadPath);
        AfxMessageBox (Msg, MB_OK + MB_ICONERROR);
    }

    App->CLSB_Doc->mpMainFrame=(CMainFrame*)AfxGetMainWnd();

    App->MainHwnd = AfxGetApp()->m_pMainWnd->m_hWnd; // hgtterry
    App->hInst = AfxGetApp()->m_hInstance;
    App->hMenu_WE = GetMenu(App->MainHwnd);

    App->CLSB_Doc->pSelBrushes = SelBrushList_Create ();
    App->CLSB_Doc->pTempSelBrushes = SelBrushList_Create ();
    App->CLSB_Doc->pSelFaces = SelFaceList_Create ();

    App->CLSB_Doc->SetLockAxis( 0 ) ;	// Start with no axis locked
    
    {
        // create our default box
        BrushTemplate_Box *pBoxTemplate;
        pBoxTemplate = Level_GetBoxTemplate (App->CLSB_Doc->pLevel);

        App->CLSB_Doc->BTemplate = BrushTemplate_CreateBox (pBoxTemplate);
    }

    Brush_Bound(App->CLSB_Doc->BTemplate);
    App->CLSB_Doc->CurBrush	= App->CLSB_Doc->BTemplate;

    geVec3d_Clear(&App->CLSB_Doc->SelectedGeoCenter);

    //AddCameraEntityToLevel ();

}/* CFusionDoc::CFusionDoc */

CFusionDoc::~CFusionDoc()
{
  
//	OpenClipboard(mpMainFrame->GetSafeHwnd());
//	EmptyClipboard();
//	CloseClipboard();

//	DeleteBrushAttributes();
//	DeleteFaceAttributes();
}

/*
void CFusionDoc::DeleteFaceAttributes (void)
{
    if (mpFaceAttributes != NULL)
    {
        delete mpFaceAttributes;
        mpFaceAttributes = NULL;
    }
}

void CFusionDoc::DeleteBrushAttributes (void)
{
    if (mpBrushAttributes != NULL)
    {
        delete mpBrushAttributes;
        mpBrushAttributes = NULL;
    }
}
*/

static void fdocDrawEntity
    (
      CEntity const *	pEnt,
      ViewVars  const *	v,
      CDC			*	pDC,
      EntityTable const *pEntityDefs,
      BOOL				bShowUI
    )
{
#define ENTITY_SIZE (8.0f)  // 16" across
    geVec3d VecOrigin;
    geVec3d EntSizeWorld;	// entity size in world space

    POINT EntPosView;
    POINT EntSizeView;
    POINT EntWidthHeight ;
    POINT OriginView;

    POINT TopLeft, BottomRight;
    POINT TopRight, BottomLeft;

    static const float COS45	= (float)cos (M_PI/4.0f);
    static const float SIN45	= (float)sin (M_PI/4.0f);
    static const float MCOS45	= (float)cos (-(M_PI/4.0f));
    static const float MSIN45	= (float)sin (-(M_PI/4.0f));

    // compute entity size in view coordinates
    geVec3d_Set (&EntSizeWorld, ENTITY_SIZE, ENTITY_SIZE, ENTITY_SIZE);
    EntSizeView = Render_OrthoWorldToView ( v, &EntSizeWorld);
    geVec3d_Clear (&VecOrigin);
    OriginView = Render_OrthoWorldToView ( v, &VecOrigin);
    // This one is the width and height of the Entity
    EntWidthHeight.x = std::max( OriginView.x, EntSizeView.x ) - std::min( OriginView.x, EntSizeView.x ) ;
    EntWidthHeight.y = std::max( OriginView.y, EntSizeView.y ) - std::min( OriginView.y, EntSizeView.y ) ;
    
    // This can have negative numbers
    EntSizeView.x -= OriginView.x;
    EntSizeView.y -= OriginView.y;

    // entity's position in the view
    EntPosView = Render_OrthoWorldToView ( v, &(pEnt->mOrigin));

    {
        // Draw an X at the entity's position...
        TopLeft.x = EntPosView.x - EntSizeView.x;
        TopLeft.y = EntPosView.y - EntSizeView.y;
        BottomRight.x = EntPosView.x + EntSizeView.x;
        BottomRight.y = EntPosView.y + EntSizeView.y;
        TopRight.x = BottomRight.x;
        TopRight.y = TopLeft.y;
        BottomLeft.x = TopLeft.x;
        BottomLeft.y = BottomRight.y;

        pDC->MoveTo (TopLeft);
        pDC->LineTo (BottomRight);
        pDC->MoveTo (TopRight);
        pDC->LineTo (BottomLeft);

    }

    // and then show the aiming arrow and arc stuff...
    if( bShowUI )
    {
        POINT		ArcTopLeft, ArcBottomRight;
        POINT		ptDirSlope ;		// Slope of the "Direction" line
        POINT		ptRotationPoint ;	// Point near end of "Direction" line we rotate to get arrowhead points
        POINT		ptRelRotatePoint ;	// Rotation points about zero
        POINT		ptPlus45 ;			// Final Arrowhead point
        POINT		ptMinus45 ;			// Final Arrowhead point
        POINT		ptStart ;			// Start point for Arc
        POINT		ptEnd ;				// End point of Arc
        float		fPercentIntoLine ;	// Distance into Direction line for rotation point
        float		fDirLength ;		// Direction line length
        float		fEntityLength ;		// Entity length
        float		fAngleToTarget ;	// Radians of arc midpoint
        geFloat		fRadius ;
        geVec3d		Angles ;
        geXForm3d	Xfm ;
        geVec3d		VecTarg ;
        float		fArc ;
        POINT		LineEndView;
        geBoolean	bUIAvailable ;

        // Get the Radius and the Angle  ONE of these must be present to show UI
        bUIAvailable = GE_FALSE ;
        if( pEnt->GetRadius( &fRadius, pEntityDefs ) == GE_FALSE )
            fRadius = 100.0f ;
        else
            bUIAvailable = GE_TRUE ;

        if( pEnt->GetAngles( &Angles, pEntityDefs ) == GE_FALSE )
            geVec3d_Clear( &Angles ) ;
        else
            bUIAvailable = GE_TRUE ;

        if( bUIAvailable == GE_FALSE )
            return ;

        // The camera angles are given in camera coordinates rather than
        // world coordinates (don't ask).
        // So we convert them here.
        if (pEnt->IsCamera ())
        {
            geVec3d_Set(&Angles, Angles.Z, (-Angles.Y-M_PI/2.0f), Angles.X);
        }

        geXForm3d_SetEulerAngles( &Xfm, &Angles ) ;
        geVec3d_Set( &VecTarg, fRadius, 0.0f, 0.0f ) ;
        geXForm3d_Transform( &Xfm, &VecTarg, &VecTarg ) ;
        geVec3d_Add( &(pEnt->mOrigin), &VecTarg, &VecTarg ) ;

        LineEndView = Render_OrthoWorldToView ( v, &VecTarg );

        // Draw to the end point
        pDC->MoveTo( EntPosView ) ;
        pDC->LineTo( LineEndView ) ;

        ptDirSlope.x = LineEndView.x - EntPosView.x ;	// Slope of Direction line
        ptDirSlope.y = LineEndView.y - EntPosView.y ;
                
        fDirLength = sqrt((float) (ptDirSlope.x*ptDirSlope.x) + (ptDirSlope.y*ptDirSlope.y)) ;	// Length of Direction line
        fEntityLength = sqrt((float) (EntSizeView.x*EntSizeView.x)+(EntSizeView.y*EntSizeView.y)) ;
        fEntityLength *= 2 ;	// Arrow 2x entity size
        fPercentIntoLine = 1.0f - (fEntityLength / fDirLength ) ;
        ptRotationPoint.x = (long)(ptDirSlope.x * fPercentIntoLine) ;
        ptRotationPoint.y = (long)(ptDirSlope.y * fPercentIntoLine) ;
        ptRotationPoint.x += EntPosView.x ;
        ptRotationPoint.y += EntPosView.y ;

        ptRelRotatePoint.x = ptRotationPoint.x - LineEndView.x ;
        ptRelRotatePoint.y = ptRotationPoint.y - LineEndView.y ;

        ptPlus45.x = (long)(ptRelRotatePoint.x * COS45 - ptRelRotatePoint.y * SIN45 ) ;
        ptPlus45.y = (long)(ptRelRotatePoint.y * COS45 + ptRelRotatePoint.x * SIN45 ) ;
        ptMinus45.x = (long)(ptRelRotatePoint.x * MCOS45 - ptRelRotatePoint.y * MSIN45 ) ;
        ptMinus45.y = (long)(ptRelRotatePoint.y * MCOS45 + ptRelRotatePoint.x * MSIN45 ) ;

        ptPlus45.x += LineEndView.x ;
        ptPlus45.y += LineEndView.y ;
        ptMinus45.x += LineEndView.x ;
        ptMinus45.y += LineEndView.y ;

        pDC->LineTo( ptPlus45 ) ;
        pDC->LineTo( ptMinus45 ) ;
        pDC->LineTo( LineEndView ) ;

        if( pEnt->GetArc( &fArc, pEntityDefs ) == GE_FALSE )
        {
            fArc = 0.0f ;	// All Directions
        }
        if( fArc != 0.0f )			// Draw the arc
        {
            fArc = 2*M_PI - fArc;
            fArc /= 2.0f ;	// We need half the angle
            EntSizeView.x *= 3; 
            EntSizeView.y *= 3;
            EntWidthHeight.x *= 3 ;
            EntWidthHeight.y *= 3 ;
            // Arc BB is an enlarged Entity BB
            ArcTopLeft.x		= EntPosView.x - EntSizeView.x;
            ArcTopLeft.y		= EntPosView.y - EntSizeView.y;
            ArcBottomRight.x	= EntPosView.x + EntSizeView.x;
            ArcBottomRight.y	= EntPosView.y + EntSizeView.y;
        
            fAngleToTarget = atan2((float) ptDirSlope.y, ptDirSlope.x ) ;	// Angle line leaves
            fAngleToTarget += M_PI ;	// The other side is where the angle starts
            
            ptStart.x = (long)((EntWidthHeight.x) * cos( fAngleToTarget + fArc )) ;
            ptStart.y = (long)((EntWidthHeight.y) * sin( fAngleToTarget + fArc )) ;
            ptEnd.x = (long)((EntWidthHeight.x) * cos( fAngleToTarget - fArc )) ;
            ptEnd.y = (long)((EntWidthHeight.y) * sin( fAngleToTarget - fArc )) ;
            ptStart.x += EntPosView.x ;
            ptStart.y += EntPosView.y ;
            ptEnd.x += EntPosView.x ;
            ptEnd.y += EntPosView.y ;

            // If Start and end point are different
            if( !(ptStart.x == ptEnd.x && ptStart.y == ptEnd.y) )
            {
                pDC->Arc
                ( 
                    ArcTopLeft.x, ArcTopLeft.y, ArcBottomRight.x, ArcBottomRight.y, 
                    ptStart.x, ptStart.y, 
                    ptEnd.x, ptEnd.y
                );
            }

            // Draw the two rays out the same distance as the Direction
            ptStart.x = (long)((fDirLength) * cos( fAngleToTarget + fArc )) ;
            ptStart.y = (long)((fDirLength) * sin( fAngleToTarget + fArc )) ;
            ptStart.x += EntPosView.x ;
            ptStart.y += EntPosView.y ;
            pDC->MoveTo( EntPosView ) ;
            pDC->LineTo( ptStart ) ;

            ptEnd.x = (long)((fDirLength) * cos( fAngleToTarget - fArc )) ;
            ptEnd.y = (long)((fDirLength) * sin( fAngleToTarget - fArc )) ;
            ptEnd.x += EntPosView.x ;
            ptEnd.y += EntPosView.y ;
            pDC->MoveTo( EntPosView ) ;
            pDC->LineTo( ptEnd ) ;
        }// Arc for this entity exists
    }
}/* fdocDrawEntity */


// ENUMERATION FUNCTIONS (File Scope)


    
static geBoolean fdocBrushCSGCallback (const Brush *pBrush, void *lParam)
{
    CFusionDoc *pDoc = (CFusionDoc *)lParam;

    return (pDoc->BrushIsVisible (pBrush) && (!Brush_IsHint(pBrush)) && (!Brush_IsClip(pBrush)));
}



//typedef struct
//{
//    BOOL Select;
//    int WhichGroup;
//    CFusionDoc *pDoc;
//} BrushSelectCallbackData;
//
//// ::BrushList_CB Enumeration function to select/deselect brushes
//static geBoolean BrushSelect( Brush *pBrush, void *lParam)
//{
//    BrushSelectCallbackData *pData;
//
//    pData = (BrushSelectCallbackData *)lParam;
//
//    // select/deselect all group brushes
//    if( Brush_GetGroupId( pBrush ) == pData->WhichGroup )
//    {
//        if( pData->Select )
//        {	// add this brush to the selected list
//            SelBrushList_Add (App->CLSB_Doc->pSelBrushes, pBrush);
//        }
//        else
//        {
//            // remove this brush from the selection list
//            SelBrushList_Remove (App->CLSB_Doc->pSelBrushes, pBrush);
//        }
//    }
//    return GE_TRUE ;	// Continue enumeration
//}/* ::BrushSelect */
//
//// ::EntityList_CB Enumeration function to select/deselect brushes
//static geBoolean EntitySelect( CEntity& Entity, void * lParam )
//{
//    BrushSelectCallbackData *pData;
//    CFusionDoc *pDoc;
//
//    pData = (BrushSelectCallbackData *)lParam;
//    pDoc = pData->pDoc;
//
//    if( Entity.GetGroupId () == pData->WhichGroup )
//    {
//        if( pData->Select )
//        {
//            pDoc->SelectEntity( &Entity );
//        }
//        else
//        {
//            pDoc->DeselectEntity( &Entity );
//        }
//    }
//    return GE_TRUE ;	// Continue enumeration
//}/* ::EntitySelect */

#define fdoc_SHOW_ALL_GROUPS -1

typedef struct tagBrushDrawData
{
    const Box3d	*	pViewBox ;
    CDC *		pDC ;
    ViewVars *	v ;
    int GroupId;
    CFusionDoc *pDoc;
    BrushFlagTest FlagTest;
    Ogre::uint32		Color;
} BrushDrawData ;

static geBoolean BrushDraw( Brush *pBrush, void *lParam)
{
    BrushDrawData * pData = (BrushDrawData*)lParam ;
    CFusionDoc * pDoc = pData->pDoc;

    if ((pData->GroupId == fdoc_SHOW_ALL_GROUPS) || (Brush_GetGroupId (pBrush) == pData->GroupId))
    {
        if ((pData->FlagTest == NULL) || pData->FlagTest (pBrush))
        {
            if (pDoc->fdocShowBrush (pBrush, pData->pViewBox))
            {
                Render_RenderBrushFacesOrtho(pData->v, pBrush, pData->pDC->m_hDC);
            }
        }
    }
    return GE_TRUE ;
}/* ::BrushDraw */


static geBoolean BrushDrawSelFacesOrtho(Brush *pBrush, void *lParam)
{
    BrushDrawData	*pData;

    pData	=(BrushDrawData *)lParam;

    Render_RenderBrushSelFacesOrtho(pData->v, pBrush, pData->pDC->m_hDC);

    return	GE_TRUE;
}

static geBoolean BrushDrawSheetFacesOrtho(Brush *pBrush, void *lParam)
{
    BrushDrawData	*pData;

    if(Brush_IsSheet(pBrush))
    {
        pData	=(BrushDrawData *)lParam;

        Render_RenderBrushSheetFacesOrtho(pData->v, pBrush, pData->pDC->m_hDC);
    }
    return	GE_TRUE;
}

static geBoolean EntityDraw( CEntity& Entity, void * lParam )
{
    BrushDrawData *pData;

    pData = (BrushDrawData *)lParam;

    if( Entity.GetGroupId () != pData->GroupId )
        return GE_TRUE ;

    if ( (Entity.IsSelected() == GE_FALSE ) && pData->pDoc->EntityIsVisible( &Entity ) )
    {
        fdocDrawEntity (&Entity, pData->v, pData->pDC, Level_GetEntityDefs (App->CLSB_Doc->pLevel), GE_FALSE );
    }
    return GE_TRUE ;
}/* ::EntityDraw */

static geBoolean	BrushDrawWire3dCB(Brush *pBrush, void *lParam)
{
    BrushDrawData *pData = (BrushDrawData *)lParam;
    CFusionDoc *pDoc = pData->pDoc;

    if ((pData->GroupId == fdoc_SHOW_ALL_GROUPS) || (Brush_GetGroupId (pBrush) == pData->GroupId))
    {
        if ((pData->FlagTest == NULL) || pData->FlagTest (pBrush))
        {
            if (pDoc->BrushIsVisible (pBrush))
            {
                Render_RenderBrushFaces (pData->v, pBrush, pData->Color);
            }
        }
    }
    return	GE_TRUE ;
}

static geBoolean	BrushDrawWire3dZBufferCB(Brush *pBrush, void *lParam)
{
    BrushDrawData *pData = (BrushDrawData *)lParam;
    CFusionDoc *pDoc = pData->pDoc;

    if ((pData->GroupId == fdoc_SHOW_ALL_GROUPS) || (Brush_GetGroupId (pBrush) == pData->GroupId))
    {
        if ((pData->FlagTest == NULL) || pData->FlagTest (pBrush))
        {
            if (pDoc->BrushIsVisible (pBrush))
            {
                Render_RenderBrushFacesZBuffer(pData->v, pBrush, pData->Color);
            }
        }
    }
    return	GE_TRUE ;
}

static geBoolean	BrushDrawWireSel3dCB(Brush *b, void *lParam)
{
    BrushDrawData *pData;

    pData = (BrushDrawData *)lParam;
    Render_RenderBrushSelFaces(pData->v, b, pData->Color);
    return	GE_TRUE ;
}

// END ENUMERATION FUNCTIONS


geBoolean CFusionDoc::fdocShowBrush
    (
      Brush const *b,
      Box3d const *ViewBox
    )
{
    return (BrushIsVisible (b) && Brush_TestBoundsIntersect(b, ViewBox));
}/* CFusionDoc::fdocShowBrush */


BOOL CFusionDoc::OnNewDocument()
{
    if(!CDocument::OnNewDocument())
    {
        return FALSE;
    }

    App->CLSB_Doc->AddCameraEntityToLevel ();

    SetupDefaultFilename ();

    UpdateGridInformation();

    App->CLSB_Doc->UpdateAllViews( UAV_ALL3DVIEWS, NULL );
    return TRUE;
}

static geBoolean fdocSetEntityVisibility (CEntity &Ent, void *lParam)
{
    EntityViewEntry *pEntry = (EntityViewEntry *)lParam;

    if (Ent.GetClassname () == pEntry->pName)
    {
        Ent.SetVisible (pEntry->IsVisible);
    }
    return GE_TRUE;
}

// *************************************************************************
// * Equity_Load_From_File				CFusionDoc::Load 				   *
// *************************************************************************
geBoolean CFusionDoc::Load(const char *FileName)
{
    //MessageBox(NULL,"HERE Unerla","HERE UNREAL",MB_OK);
    const char		*Errmsg, *WadPath;
    int				i;
    Level			*NewLevel;
    EntityViewList	*pEntityView;
    const Prefs *pPrefs = GetPrefs ();

    {
        char WorkingDir[MAX_PATH];

        FilePath_GetDriveAndDir (FileName, WorkingDir);
//		::SetCurrentDirectory (WorkingDir);
    }

// changed QD Actors
    NewLevel = Level_CreateFromFile (FileName, &Errmsg, Prefs_GetHeadersList (pPrefs),
        Prefs_GetActorsList(pPrefs), Prefs_GetPawnIni(pPrefs));
// end change
    if (NewLevel == NULL)
    {
        goto LoadError;
    }
    // get fully-qualified path name to texture library
    WadPath = Level_GetWadPath (NewLevel);

    if (!Level_LoadWad (NewLevel))
    {
        CString Msg;

        AfxFormatString1 (Msg, IDS_CANTLOADTXL, WadPath);
        AfxMessageBox (Msg, MB_OK + MB_ICONERROR);
    }
    Level_EnumLeafBrushes (NewLevel, NewLevel, Level_FaceFixupCallback);

    if (App->CLSB_Doc->pLevel != NULL)
    {
        Level_Destroy (&App->CLSB_Doc->pLevel);
    }
    App->CLSB_Doc->pLevel = NewLevel;
//	pCameraEntity = NULL;

    // Validate data, groups are read after entities and brushes, so this must be last
    if( ValidateEntities( ) == FALSE || ValidateBrushes( ) == FALSE )
    {
        SelectTab( CONSOLE_TAB ) ;
        AfxMessageBox( IDS_LOAD_WARNING, MB_OK + MB_ICONERROR ) ;
    }

    GroupIterator gi;
    GroupListType *Groups;

    Groups = Level_GetGroups (App->CLSB_Doc->pLevel);
    App->CLSB_Doc->mCurrentGroup = Group_GetFirstId (Groups, &gi);

    {
        Brush *pBox = BrushTemplate_CreateBox (Level_GetBoxTemplate (App->CLSB_Doc->pLevel));
        if (pBox != NULL)
        {
            CreateNewTemplateBrush (pBox);
        }
    }

    // update entity visibility info
    pEntityView	=Level_GetEntityVisibilityInfo (App->CLSB_Doc->pLevel);
    for (i = 0; i < pEntityView->nEntries; ++i)
    {
        Level_EnumEntities (App->CLSB_Doc->pLevel, &pEntityView->pEntries[i], ::fdocSetEntityVisibility);
    }

    App->CLSB_Doc->AddCameraEntityToLevel ();

    App->CLSB_Doc->DoGeneralSelect();
    return GE_TRUE;
LoadError:
    if (NewLevel != NULL)
    {
        Level_Destroy (&NewLevel);
    }
    AfxMessageBox (Errmsg, MB_OK + MB_ICONERROR);
    return GE_FALSE;
}

struct fdocFaceScales
{
    float DrawScale;
    float LightmapScale;
};

static geBoolean fdocSetFaceScales (Face *pFace, void *lParam)
{
    fdocFaceScales *pScales = (fdocFaceScales *)lParam;

    Face_SetTextureScale (pFace, pScales->DrawScale, pScales->DrawScale);
    Face_SetLightScale (pFace, pScales->LightmapScale, pScales->LightmapScale);
    return GE_TRUE;
}

void CFusionDoc::OnBrushAddtoworld() 
{
    geBoolean Placed;

    if(App->CLSB_Doc->mModeTool!=ID_TOOLS_TEMPLATE)
        return;

    Placed = GE_FALSE;
    if(App->CLSB_Doc->TempEnt)
    {
        // here we check to see if the user is placing library objects down
        if (App->CLSB_Doc->PlaceObjectFlag )
        {
            geBoolean GotName;
            char ObjectName[MAX_PATH];

            // get the current object from the library and place it down
            //GotName = mpMainFrame->m_wndTabControls->m_pBrushEntityDialog->GetCurrentObjectName (ObjectName);
            //if (GotName)
            //{
            //	Placed = PlaceObject (ObjectName, &mRegularEntity.mOrigin);
            //	mpMainFrame->m_wndTabControls->GrpTab->UpdateAfterAddBrush();

            //	/*if (App->CL_TabsGroups_Dlg->Groups_Dlg_Created == 1)
            //	{
            //		App->CL_TabsGroups_Dlg->Fill_ListBox();
            //	}*/

            //	UpdateAllViews(UAV_ALL3DVIEWS, NULL);
            //}
        }
        else
        {
            geBoolean GotName;
            CEntity NewEnt;
            char EntityName[MAX_PATH];

            App->CLSB_Doc->mRegularEntity.DoneMove (1, Level_GetEntityDefs (App->CLSB_Doc->pLevel));

            // now create a new entity of the currently-selected type
            //GotName = mpMainFrame->m_wndTabControls->m_pBrushEntityDialog->GetCurrentEntityName (EntityName);
            //if (GotName)
            //{	
            //	if (CreateEntityFromName (EntityName, NewEnt))
            //	{
            //		geVec3d org;
            //		org = mRegularEntity.mOrigin;
            //		// set the new entity's origin
            //		NewEnt.SetOrigin (org.X, org.Y, org.Z, Level_GetEntityDefs (pLevel));
            //		// add to current group
            //		NewEnt.SetGroupId (mCurrentGroup);
            //		Level_AddEntity (pLevel, NewEnt);
            //		Placed = GE_TRUE;
            //		mpMainFrame->m_wndTabControls->GrpTab->UpdateAfterAddBrush();

            //		/*if (App->CL_TabsGroups_Dlg->Groups_Dlg_Created == 1)
            //		{
            //			App->CL_TabsGroups_Dlg->Fill_ListBox();
            //		}*/

            //		UpdateAllViews(UAV_ALL3DVIEWS, NULL);
            //	}
            //}
        }
    }
    else
    {
        Brush	*nb;
        geVec3d *pTemplatePos;

        nb	=Brush_Clone(App->CLSB_Doc->CurBrush);

        SetDefaultBrushTexInfo(nb);
        Brush_Bound (nb);
        pTemplatePos = Level_GetTemplatePos (App->CLSB_Doc->pLevel);
        Brush_Center (nb, pTemplatePos);
        // add to current group
        Brush_SetGroupId (nb, App->CLSB_Doc->mCurrentGroup);

        {
            // set draw scale and lightmap scale defaults for all faces
            fdocFaceScales Scales;

            Scales.DrawScale = Level_GetDrawScale (App->CLSB_Doc->pLevel);
            Scales.LightmapScale = Level_GetLightmapScale (App->CLSB_Doc->pLevel);
            Brush_EnumFaces (nb, &Scales, ::fdocSetFaceScales);

        }

        Level_AppendBrush (App->CLSB_Doc->pLevel, nb);

        if(!Brush_IsHollow(nb) && !Brush_IsMulti(nb))
        {
            App->CLSB_Doc->mWorldBsp	=Node_AddBrushToTree(App->CLSB_Doc->mWorldBsp, nb);
            App->CLSB_Doc->UpdateAllViews(UAV_ALL3DVIEWS, NULL);
        }
        else
        {
            App->CLSB_Doc->UpdateAllViews(UAV_ALL3DVIEWS | REBUILD_QUICK, NULL, TRUE);
        }

        Placed = GE_TRUE;
        //mpMainFrame->m_wndTabControls->GrpTab->UpdateAfterAddBrush();

        if (App->CL_TabsGroups_Dlg->Groups_Dlg_Created == 1)
        {
            App->CL_TabsGroups_Dlg->Fill_ListBox();
        }

    }
    if (Placed)
    {
    // MS: We need to simualate a "move", to finally place 
    // Lib objects to where they were placed in Template mode
    // switch to move mode
    App->CLSB_Doc->mCurrentTool=ID_TOOLS_BRUSH_MOVEROTATEBRUSH;
    App->CLSB_Doc->ConfigureCurrentTool();
    // fake a move
    App->CLSB_Doc->DoneMove();
    // Back to select mode
    App->CLSB_Doc->DoGeneralSelect();
    // ~MS
    SetModifiedFlag();
    }
}

// This code is STILL called from the toolbar button, but the "correct"
// interface is now on the Brush Attributes Dialog
void CFusionDoc::OnBrushSubtractfromworld() 
{
    Brush	*nb;
    BrushList *BList = Level_GetBrushes (App->CLSB_Doc->pLevel);

    if ((App->CLSB_Doc->mModeTool==ID_GENERALSELECT) && (BrushList_Count (BList, BRUSH_COUNT_MULTI | BRUSH_COUNT_LEAF) < 2))
    {
        // cuts shouldn't start the list
        return;
    }

    SetModifiedFlag();

    if(App->CLSB_Doc->mModeTool==ID_GENERALSELECT)
    {
        // put the brush at the very end of the list
        BrushList_Remove (BList, App->CLSB_Doc->CurBrush);
        Brush_SetSubtract(App->CLSB_Doc->CurBrush, GE_TRUE);

        SelBrushList_RemoveAll (App->CLSB_Doc->pSelBrushes);
        BrushList_Append (BList, App->CLSB_Doc->CurBrush);
    }
    else
    {
        nb	=Brush_Clone(App->CLSB_Doc->CurBrush);

        SetDefaultBrushTexInfo(nb);
        Brush_Bound (nb);

        // add to current group
        Brush_SetGroupId (nb, App->CLSB_Doc->mCurrentGroup);

        BrushList_Append (BList, nb);
    }
    App->CLSB_Doc->UpdateSelected();
    App->CLSB_Doc->UpdateAllViews(UAV_ALL3DVIEWS | REBUILD_QUICK, NULL, TRUE);
}

void CFusionDoc::CopySelectedBrushes(void)
{
    int		i;
    int		NumSelBrushes;

    NumSelBrushes = SelBrushList_GetSize (App->CLSB_Doc->pSelBrushes);

    if( NumSelBrushes )
    {
        // create copies of the selected brushes
        for(i=0;i < NumSelBrushes;i++)
        {
            // clone the brush, add copy to level,
            // add copy to select list, and remove original from
            // select list.
            Brush *pBrush;
            Brush *pClone;

            pBrush = SelBrushList_GetBrush (App->CLSB_Doc->pSelBrushes, 0);
// changed QD Actors
// don't copy ActorBrushes
            if(strstr(App->CL_Brush->Brush_GetName(pBrush),".act")!=NULL)
                continue;
// end change
            pClone = Brush_Clone (pBrush);
            Level_AppendBrush (App->CLSB_Doc->pLevel, pClone);
            SelBrushList_Add (App->CLSB_Doc->pSelBrushes, pClone);
            SelBrushList_Remove (App->CLSB_Doc->pSelBrushes, pBrush);
        }
    }// Duplicate selected and delesect original Brushes


    CEntity  TEnt;
    CEntityArray *Entities;
    int cnt;

    Entities = Level_GetEntities (App->CLSB_Doc->pLevel);

    cnt = Entities->GetSize() ;
    for( i=0 ; i < cnt; i++ )
    {
        CEntity *pEnt = &(*Entities)[i];
        if( pEnt->IsCamera() == GE_FALSE  )	// Exclude Cameras
//		if( pEnt!=pCameraEntity )	// Exclude Cameras
        {
            if (pEnt->IsSelected ())
            {
                DeselectEntity (pEnt);
                /*
                  There really is a reason for this oddity.
                  Because Level_AddEntity might cause the entities array to grow,
                  dereferencing the data in the array can cause problems because
                  growing the array might cause the dereferenced data to move.
                  (Fun, huh?)  So I create a temporary entity, copy the contents
                  there, and then use that as cloning material.
                */
                CEntity WorkingEntity;
                int		Index ;

                WorkingEntity = *pEnt;
                Index = Level_AddEntity (App->CLSB_Doc->pLevel, WorkingEntity);

                SelectEntity( &(*Entities)[Index] );
            }
        }
    }

//	ConPrintf("Cloned %d Brushes, %d Entities.\n", NumSelBrushes, NumSelEntities);

    // Copying items places the new items in the same group, so we must update the UI
//	mpMainFrame->m_wndTabControls->GrpTab->UpdateTabDisplay( this ) ;
    App->CL_TabsGroups_Dlg->Fill_ListBox(); // hgtterry App->CL_TabsGroups_Dlg->Fill_ListBox()
    App->CLSB_Doc->UpdateSelected();
    App->CLSB_Doc->UpdateAllViews( UAV_ALL3DVIEWS, NULL );
}

void CFusionDoc::MakeSelectedBrushNewest(void)
{
    if(App->CLSB_Doc->GetSelState()==ONEBRUSHONLY)
    {
        Level_RemoveBrush (App->CLSB_Doc->pLevel, App->CLSB_Doc->CurBrush);
        Level_AppendBrush (App->CLSB_Doc->pLevel, App->CLSB_Doc->CurBrush);
    }
}


void CFusionDoc::TempCopySelectedBrushes(void)
{
    int		i;
    int NumSelBrushes;

    NumSelBrushes = SelBrushList_GetSize (App->CLSB_Doc->pSelBrushes);

    SelBrushList_RemoveAll (App->CLSB_Doc->pTempSelBrushes);

    // make copies of selected brushes
    for(i=0;i < NumSelBrushes;i++)
    {
        Brush	*pBrush, *pClone;

        pBrush = SelBrushList_GetBrush (App->CLSB_Doc->pSelBrushes, i);
        pClone = Brush_Clone (pBrush);
        Level_AppendBrush (App->CLSB_Doc->pLevel, pClone);
        SelBrushList_Add (App->CLSB_Doc->pTempSelBrushes, pClone);
    }
}

typedef struct
{
    CFusionDoc *pDoc;
    const char *TexName;
} BrushTexSetData;

static geBoolean	BrushTexSetCB (Brush *b, void *lParam)
{
    int			i;
    BrushTexSetData *pData;

    pData = (BrushTexSetData *)lParam;

//	Brush_SetName(b, pData->TexName);
    Brush_SetName(b, pData->pDoc->LastTemplateTypeName);
//	char const * const BrushName = Brush_GetName (b);
    const int NumFaces = Brush_GetNumFaces (b);

    //copy face TexInfos
    for(i=0;i < NumFaces;i++)
    {
        Face	*f	=Brush_GetFace(b, i);
        WadFileEntry *pbmp;

//		Face_SetTextureName(f, BrushName);
//		Face_SetTextureDibId(f, Level_GetDibId (pData->pDoc->pLevel, BrushName));
//		pbmp = Level_GetWadBitmap (pData->pDoc->pLevel, BrushName);
        Face_SetTextureName(f, pData->TexName);
        Face_SetTextureDibId(f, Level_GetDibId (App->CLSB_Doc->pLevel, pData->TexName));
        pbmp = Level_GetWadBitmap (App->CLSB_Doc->pLevel, pData->TexName);
        if (pbmp != NULL)
        {
            Face_SetTextureSize (f, pbmp->Width, pbmp->Height);
        }
    }
    Brush_SetFaceListDirty(b);
    return GE_TRUE ;
}

void CFusionDoc::SetDefaultBrushTexInfo(Brush *b)
{
    const char *TexName;
    BrushTexSetData CallbackData;

    TexName = App->CL_TextureDialog->m_CurrentTexture;
    CallbackData.pDoc = this;
    CallbackData.TexName = TexName;

//	Brush_SetName(b, TexName);
    Brush_SetName(b, LastTemplateTypeName);
    if(Brush_IsMulti(b))
    {
        BrushList_EnumLeafBrushes (App->CL_Brush->Brush_GetBrushList(b), &CallbackData, ::BrushTexSetCB) ;
    }
    else
    {
        ::BrushTexSetCB (b, &CallbackData);
    }
}

// Test BOTH group and brush visiblity--group overrides
// User flags for All, Visible, and Current group must be considered
geBoolean CFusionDoc::BrushIsVisible( const Brush * pBrush ) const
{
    int			GroupId ;

    if (!Brush_IsVisible (pBrush))
    {
        return GE_FALSE;
    }
    GroupId = Brush_GetGroupId (pBrush);

    switch (Level_GetGroupVisibility (App->CLSB_Doc->pLevel))
    {
        case Group_ShowAll :
            return GE_TRUE;

        case Group_ShowCurrent :
            return (GroupId == App->CLSB_Doc->mCurrentGroup);
    
        case Group_ShowVisible :
            return Group_IsVisible (Level_GetGroups (App->CLSB_Doc->pLevel), GroupId);
    
        default :
            assert (0);
            return GE_FALSE;
    }
}/* CFusionDoc::BrushIsVisible */


// Test BOTH group and entity visiblity--group overrides
// User flags for All, Visible, and Current group must be considered
geBoolean CFusionDoc::EntityIsVisible( const CEntity *pEntity ) const
{
    int			GroupId ;

    if (pEntity->IsCamera ())
//	if (pEntity==pCameraEntity)
    {
        return pEntity->IsVisible ();
    }
    if ((App->CLSB_Doc->mShowEntities == GE_FALSE) || !pEntity->IsVisible ())
    {
        return GE_FALSE ;
    }

    GroupId = pEntity->GetGroupId( );

    switch (Level_GetGroupVisibility (App->CLSB_Doc->pLevel))
    {
        case Group_ShowAll :
            return GE_TRUE;

        case Group_ShowCurrent :
            return (GroupId == App->CLSB_Doc->mCurrentGroup);

        case Group_ShowVisible :
            return Group_IsVisible (Level_GetGroups (App->CLSB_Doc->pLevel), GroupId);

        default :
            assert (0);
            return GE_FALSE;
    }
}/* CFusionDoc::EntityIsVisible */

void CFusionDoc::CreateNewTemplateBrush(Brush *pBrush)
{
    geVec3d *pTemplatePos;
    geVec3d MoveVec;
    geVec3d BrushPos;

    assert (pBrush != NULL);

    if (App->CLSB_Doc->BTemplate != NULL)
    {
        Brush_Destroy (&App->CLSB_Doc->BTemplate);
    }
    App->CLSB_Doc->BTemplate = pBrush;
    App->CLSB_Doc->CurBrush = pBrush;

    App->CLSB_Doc->TempEnt	= FALSE;
    SetDefaultBrushTexInfo (App->CLSB_Doc->CurBrush);
    Brush_Bound (App->CLSB_Doc->CurBrush);
    Brush_Center (App->CLSB_Doc->CurBrush, &BrushPos);

    pTemplatePos = Level_GetTemplatePos (App->CLSB_Doc->pLevel);
    geVec3d_Subtract (pTemplatePos, &BrushPos, &MoveVec);
    Brush_Move (App->CLSB_Doc->CurBrush, &MoveVec);

    App->CLSB_Doc->UpdateAllViews (UAV_ALL3DVIEWS, NULL);
    SetModifiedFlag ();
}

void CFusionDoc::OnUpdateBrushPrimitives (CCmdUI *pCmdUI)
{
    // This function is used by all the primitive UI OnUpdateXXX's
//	pCmdUI->Enable( (mModeTool == ID_TOOLS_TEMPLATE ) ? TRUE : FALSE ) ;
    pCmdUI->Enable( TRUE ) ;
}

void CFusionDoc::OnBrushPrimitivesCube() 
{
    CreateCube() ;
}


void CFusionDoc::CreateCube() 
{
    App->Say("Gone");
}

void CFusionDoc::OnBrushPrimitivesSpheroid() 
{
    CreateSpheroid() ;
}


void CFusionDoc::CreateSpheroid() 
{
    App->Say("Gone");
}/* CFusionDoc::CreateSpheroid */

void CFusionDoc::OnBrushPrimitivesCylinder() 
{
    CreateCylinder() ;
}


void CFusionDoc::CreateCylinder() 
{
    App->Say("Gone");
}/* CFusionDoc::CreateCylinder */

void CFusionDoc::OnBrushPrimitivesStaircase() 
{
    CreateStaircase() ;
}


void CFusionDoc::CreateStaircase()
{
    App->Say("Gone");
}/* CFusionDoc::CreateStaircase */

void CFusionDoc::OnBrushPrimitivesArch() 
{
    CreateArch ();
}

void CFusionDoc::CreateArch()
{
    App->Say("Gone");
}/* CFusionDoc::CreateArch */

    
void CFusionDoc::OnBrushPrimitivesCone() 
{
    CreateCone ();
}
void CFusionDoc::CreateCone()
{
    App->Say("Gone");
}

geBoolean CFusionDoc::BrushIsSelected
    (
      Brush const *pBrush
    )
{
    assert (pBrush != NULL);

    return SelBrushList_Find (App->CLSB_Doc->pSelBrushes, pBrush);
}



void CFusionDoc::OnToolsUsegrid() 
{
    GridInfo *pGridInfo = Level_GetGridInfo (App->CLSB_Doc->pLevel);

    pGridInfo->UseGrid = !(pGridInfo->UseGrid);

    UpdateGridInformation();
    App->CLSB_Doc->UpdateAllViews(UAV_GRID_ONLY, NULL);
}

void CFusionDoc::OnUpdateToolsUsegrid(CCmdUI* pCmdUI) 
{
    pCmdUI->SetCheck( Level_UseGrid (App->CLSB_Doc->pLevel));
}

void CFusionDoc::OnToolsGridsettings() 
{
    int				gdex[3]={GridSize_Centimeter, GridSize_Decimeter, GridSize_Meter};
    CGridSizeDialog dlg;
    GridInfo *pGridInfo;
    static int TexelSnapValues[] = {1, 2, 4, 8, 16, 32};
    static int nSnapValues = sizeof (TexelSnapValues)/sizeof (int);

    pGridInfo = Level_GetGridInfo (App->CLSB_Doc->pLevel);

    dlg.m_UseSnap			=pGridInfo->UseGrid;
    dlg.m_SnapDegrees		=pGridInfo->RotationSnap;
    
    dlg.MetricOrTexelSnap	=pGridInfo->SnapType;
    dlg.MetricOrTexelGrid	=pGridInfo->GridType;

    if( dlg.MetricOrTexelSnap == 0 )
    {
        switch(pGridInfo->MetricSnapSize)
        {
            case GridSize_Centimeter:
                dlg.m_GridUnits	=0;
                break;
            case GridSize_Decimeter:
                dlg.m_GridUnits	=1;
                break;
            case GridSize_Meter:
                dlg.m_GridUnits	=2;
                break ;
        }
    }
    else
    {
        int i;

        dlg.m_GridUnits = 0;
        for (i = 0; i < nSnapValues; ++i)
        {
            if (pGridInfo->TexelSnapSize == TexelSnapValues[i])
            {
                dlg.m_GridUnits = i;
                break;
            }
        }
// commented here because metric is disabled...
//		dlg.m_GridUnits += 3;	// metric takes up the first 3
    }
    if(dlg.DoModal()==IDOK)
    {
        pGridInfo->GridType = dlg.MetricOrTexelGrid;	// Main Visible Grid mode 
        // must add here 'cause metric grid is disabled
        dlg.m_GridUnits += 3;
        switch( dlg.m_GridUnits ) // SnapGrid RB's 0-2 METRIC 3-5 TEXEL
        {
            case 0:// Centimeter
            case 1:// Decimeter
            case 2:// Meter
                pGridInfo->MetricSnapSize	=gdex[dlg.m_GridUnits];
                pGridInfo->SnapType = GridMetric;
                break ;
            case 3:// 1
            case 4:// 2
            case 5:// 4
            case 6:
            case 7:
            case 8:
                pGridInfo->TexelSnapSize = TexelSnapValues[dlg.m_GridUnits - 3];
                pGridInfo->SnapType = GridTexel;
                break ;
            default :
                assert (0);	// unexpected grid units value!
                break;
        }
        
        pGridInfo->UseGrid = dlg.m_UseSnap;
        pGridInfo->RotationSnap = (int)(dlg.m_SnapDegrees);
        UpdateGridInformation();
        App->CLSB_Doc->UpdateAllViews(UAV_GRID_ONLY, NULL);
    }// DoModal OK
}/* CFusionDoc::OnToolsGridsettings */

void CFusionDoc::OnEditUndo() 
{
#if 0
    // Well, here's the basic idea of undo.
    // It doesn't work 'cause the stack isn't being built.
    UndoStackEntry *pEntry;
    UndoEntryType EntryType;

    pEntry = UndoStack_Pop (pUndoStack);

    EntryType = UndoStackEntry_GetType (pEntry);
    switch (EntryType)
    {
        case UNDO_MOVE :
        {
            int i;
            UndoMoveEntry *pMove;
            geVec3d UndoVec;

            ResetAllSelections ();
            pMove = UndoStackEntry_GetMoveInfo (pEntry);
            geVec3d_Scale (&(pMove->MoveDelta), -1.0f, &UndoVec);
            for (i = 0; i < Array_GetSize (pMove->BrushArray); ++i)
            {
                Brush *pBrush;

                pBrush = (Brush *)Array_ItemPtr (pMove->BrushArray, i);
                Brush_Move (pBrush, &UndoVec);
                SelListAddBrush (pBrush);
            }

            for (i = 0; i < Array_GetSize (pMove->EntityArray); ++i)
            {
                CEntity *pEnt;

                pEnt = (CEntity *)Array_ItemPtr (pMove->EntityArray, i);
                SelectEntity (pEnt);
            }

            UpdateSelected ();

            if (GetSelState() & ANYENTITY)
            {
                DoneMoveEntity();
            }

            UpdateAllViews( UAV_ALL3DVIEWS, NULL );

            break;
        }

        default :
            assert (0);
            break;
    }
    UndoStackEntry_Destroy (&pEntry);
#endif
}

void CFusionDoc::OnUpdateEditUndo(CCmdUI* pCmdUI) 
{
    pCmdUI->Enable (CanUndo ());
}

//unimplemented currently
void CFusionDoc::OnEditRedo() 
{
//	CurBrush->RedoLast();
//	UpdateAllViews(UAV_ALLVIEWS, NULL);
}

void CFusionDoc::OnUpdateEditRedo(CCmdUI* pCmdUI) 
{
    pCmdUI->Enable (CanRedo ());
}


void CFusionDoc::OnEntitiesEditor() 
{
    CEntitiesDialog Dialog (AfxGetMainWnd ());
    CEntityArray *Entities = Level_GetEntities (App->CLSB_Doc->pLevel);

    Dialog.EditEntity( *Entities, App->CLSB_Doc->mCurrentEntity, this);
    UpdateEntityOrigins();
// changed QD Actors
    UpdateEntityActors();
    App->CLSB_Doc->UpdateAllViews(UAV_ALL3DVIEWS | REBUILD_QUICK, NULL);
//	UpdateAllViews(UAV_ALL3DVIEWS, NULL);
// end change
    SetModifiedFlag();
}


void CFusionDoc::CreateEntity
    (
      char const *pEntityType
    )
{
    CEntity NewEnt;
    
    if (App->CLSB_Doc->CreateEntityFromName (pEntityType, NewEnt))
    {
        App->CLSB_Doc->TempEnt = TRUE;

        App->CLSB_Doc->mRegularEntity = NewEnt;
        App->CLSB_Doc->mCurrentEntity = -1;
        // set this flag so that doc knows when enter is pressed that user is NOT adding 
        // objects to level
        App->CLSB_Doc->PlaceObjectFlag = FALSE;

        App->CLSB_Doc->mCurrentTool=ID_TOOLS_BRUSH_MOVEROTATEBRUSH;
        App->CLSB_Doc->ConfigureCurrentTool();

        App->CLSB_Doc->UpdateAllViews(UAV_ALL3DVIEWS, NULL);
        SetModifiedFlag();
    }
}

// creates a template entity with which the user specifies a location for any 
// objects they place
void CFusionDoc::CreateObjectTemplate()
{
    CEntity NewEnt;

    // make an origin
    if (App->CLSB_Doc->CreateEntityFromName ("ModelOrigin", NewEnt))
    {
        App->CLSB_Doc->TempEnt=TRUE;

        NewEnt.SetOrigin (0.0f, 0.0f, 0.0f, Level_GetEntityDefs (App->CLSB_Doc->pLevel));

        App->CLSB_Doc->mRegularEntity=NewEnt;
        App->CLSB_Doc->mCurrentEntity=-1;

        // set this flag so that doc knows when enter is pressed that user is adding objects
        // to level
        App->CLSB_Doc->PlaceObjectFlag = TRUE;

        App->CLSB_Doc->mCurrentTool=ID_TOOLS_BRUSH_MOVEROTATEBRUSH;
        App->CLSB_Doc->ConfigureCurrentTool();

        App->CLSB_Doc->UpdateAllViews(UAV_ALL3DVIEWS, NULL);
        SetModifiedFlag();
    }
}

void CFusionDoc::OnEntitiesShow(void)
{
    App->CLSB_Doc->mShowEntities = !App->CLSB_Doc->mShowEntities;
    App->CLSB_Doc->UpdateAllViews(UAV_ALL3DVIEWS, NULL);
}

void CFusionDoc::OnUpdateEntitiesShow(CCmdUI* pCmdUI) 
{
    pCmdUI->SetCheck(App->CLSB_Doc->mShowEntities );
}

void CFusionDoc::OnViewShowAllGroups() 
{
    App->CLSB_Doc->CurBrush	= App->CLSB_Doc->BTemplate;
    Level_SetGroupVisibility (App->CLSB_Doc->pLevel, Group_ShowAll);

    App->CLSB_Doc->UpdateAllViews(UAV_ALL3DVIEWS, NULL);
}


void CFusionDoc::OnViewShowCurrentGroup() 
{
    App->CLSB_Doc->CurBrush = App->CLSB_Doc->BTemplate;
    Level_SetGroupVisibility (App->CLSB_Doc->pLevel, Group_ShowCurrent);

    App->CLSB_Doc->UpdateAllViews(UAV_ALL3DVIEWS, NULL);
}

void CFusionDoc::OnViewShowVisibleGroups() 
{
    App->CLSB_Doc->CurBrush	= App->CLSB_Doc->BTemplate;
    Level_SetGroupVisibility (App->CLSB_Doc->pLevel, Group_ShowVisible);
    
    App->CLSB_Doc->UpdateAllViews(UAV_ALL3DVIEWS, NULL);
}

void CFusionDoc::OnUpdateViewShowVisibleGroups(CCmdUI* pCmdUI) 
{
    BOOL	bEnable ;
    int Setting;

    Setting = Level_GetGroupVisibility (App->CLSB_Doc->pLevel);
    bEnable = ( Group_GetCount( Level_GetGroups (App->CLSB_Doc->pLevel)) ) ? TRUE : FALSE ;
    
    if (((pCmdUI->m_nID == ID_VIEW_SHOW_ALLGROUPS) && (Setting == Group_ShowAll)) ||
        ((pCmdUI->m_nID == ID_VIEW_SHOW_CURRENTGROUP) && (Setting == Group_ShowCurrent)) ||
        ((pCmdUI->m_nID == ID_VIEW_SHOW_VISIBLEGROUPS) && (Setting == Group_ShowVisible)))
    {
        pCmdUI->SetCheck();
    }
    else
    {
        pCmdUI->SetCheck(0);
    }

    pCmdUI->Enable( bEnable ) ;
}

void CFusionDoc::OnUpdateViewShowAllGroups(CCmdUI* pCmdUI) 
{
    OnUpdateViewShowVisibleGroups( pCmdUI ) ;
}


void CFusionDoc::OnUpdateViewShowCurrentGroup(CCmdUI* pCmdUI) 
{
    OnUpdateViewShowVisibleGroups( pCmdUI ) ;
}


int CFusionDoc::CanUndo()
{
    return !(UndoStack_IsEmpty (App->CLSB_Doc->pUndoStack));
}

void CFusionDoc::SaveBrushUndo()
{
}

int CFusionDoc::CanRedo()
{
    return 0;
}

void CFusionDoc::UpdateEntityOrigins()
{
    int	i;
    CEntityArray *Entities;

    Entities = Level_GetEntities (App->CLSB_Doc->pLevel);

    for(i=0;i < Entities->GetSize();i++)
    {
        (*Entities)[i].UpdateOrigin(Level_GetEntityDefs (App->CLSB_Doc->pLevel));
    }
}

// changed QD Actors
void CFusionDoc::UpdateEntityActors()
{
    int i;
    CEntityArray *Entities;

    Entities = Level_GetEntities (App->CLSB_Doc->pLevel);

    for(i=0;i < Entities->GetSize();i++)
    {
        char ActorFile[256], ActorDir[256], PawnIni[256];
        strcpy(PawnIni, Level_GetPawnIniPath(App->CLSB_Doc->pLevel));
        if((*Entities)[i].HasActor(ActorFile, PawnIni))
        {
            Brush *pBrush = (*Entities)[i].GetActorBrush();

            if(pBrush)
            {
                SelBrushList_Remove(App->CLSB_Doc->pSelBrushes, pBrush);
                Level_RemoveBrush(App->CLSB_Doc->pLevel, pBrush);
                (*Entities)[i].DeleteActorBrush();
            }

            strcpy(ActorDir, Level_GetActorsDirectory(App->CLSB_Doc->pLevel));

            pBrush=(*Entities)[i].CreateActorBrush(ActorFile, ActorDir, PawnIni);
            if(pBrush)
            {
                Level_AppendBrush(App->CLSB_Doc->pLevel,pBrush);
                if((*Entities)[i].IsSelected())
                    SelBrushList_Add(App->CLSB_Doc->pSelBrushes, pBrush);
                if(!bShowActors)
                    Brush_SetVisible(pBrush, GE_FALSE);
            }
        }
        else
        {
            Brush *pBrush = (*Entities)[i].GetActorBrush();
            if(pBrush!=NULL)
            {
                SelBrushList_Remove(App->CLSB_Doc->pSelBrushes, pBrush);
                Level_RemoveBrush(App->CLSB_Doc->pLevel, pBrush);
                (*Entities)[i].DeleteActorBrush();
            }
        }
    }

}
// end change

void CFusionDoc::MoveEntity(geVec3d *v)
{
    assert (v != NULL);

    if(App->CLSB_Doc->mCurrentEntity < 0) //template
    {
        App->CLSB_Doc->mRegularEntity.Move (v);
    }
    else
    {
        CEntityArray *Entities = Level_GetEntities (App->CLSB_Doc->pLevel);

        (*Entities)[App->CLSB_Doc->mCurrentEntity].Move(v);
        SetModifiedFlag();
    }
}

static geBoolean fdocBrushNotDetail (const Brush *b)
{
    return !Brush_IsDetail (b);
}

static geBoolean fdocBrushIsSubtract (const Brush *b)
{
    return (Brush_IsSubtract (b) && !Brush_IsHollowCut (b));
}

void CFusionDoc::OnUpdateBrushAdjustmentmode(CCmdUI* pCmdUI) 
{
    pCmdUI->Enable( TRUE); //( mModeTool == ID_GENERALSELECT ) ? TRUE : FALSE ) ;
    pCmdUI->SetCheck( (App->CLSB_Doc->mAdjustMode == ADJUST_MODE_BRUSH ) ? TRUE : FALSE ) ;
}

void CFusionDoc::OnToolsBrushAdjustmentmode() 
{
    if( /*mModeTool == ID_GENERALSELECT && 
        !IsSelectionLocked() && */
        App->CLSB_Doc->mCurrentTool == CURTOOL_NONE )
    {
//		SetAdjustmentMode( ADJUST_MODE_BRUSH ) ;
        App->CLSB_Doc->SetAdjustmentMode( ADJUST_MODE_FACE ) ;
    }
}

void CFusionDoc::OnUpdateFaceAdjustmentmode(CCmdUI* pCmdUI) 
{
    pCmdUI->Enable( TRUE); //( mModeTool == ID_GENERALSELECT ) ? TRUE : FALSE ) ;
    pCmdUI->SetCheck( (App->CLSB_Doc->mAdjustMode==ADJUST_MODE_FACE) ? TRUE : FALSE ) ;
}

void CFusionDoc::OnToolsFaceAdjustmentmode() 
{
    if( /*mModeTool == ID_GENERALSELECT && 
        !IsSelectionLocked() && */
        App->CLSB_Doc->mCurrentTool == CURTOOL_NONE )
    {
        App->CLSB_Doc->SetAdjustmentMode( ADJUST_MODE_FACE ) ;
    }
}

void CFusionDoc::OnToolsToggleadjustmode() 
{
//MS change to select mode before changing to face adjustment
    App->CLSB_Doc->DoGeneralSelect();
    if( /*mModeTool == ID_GENERALSELECT && 
        !IsSelectionLocked() && */
        App->CLSB_Doc->mCurrentTool == CURTOOL_NONE )
    {
        App->CLSB_Doc->SetAdjustmentMode( ADJUST_MODE_FACE ) ;
    }

}

void CFusionDoc::OnUpdateToolsToggleadjustmode(CCmdUI* pCmdUI) 
{
//MS change to select mode before changing to face adjustment
    App->CLSB_Doc->DoGeneralSelect();
    if( /*mModeTool == ID_GENERALSELECT && 
        !IsSelectionLocked() && */
        App->CLSB_Doc->mCurrentTool == CURTOOL_NONE )
    {
        App->CLSB_Doc->SetAdjustmentMode( ADJUST_MODE_TOGGLE ) ;	// Flip between Brush & face 
    }

}

void CFusionDoc::SelectEntity
    (
      CEntity *pEntity
    )
{
    assert (pEntity != NULL);

    if (!pEntity->IsSelected ())
    {
        pEntity->Select ();
// changed QD Actors
        Brush *pBrush;
        pBrush = pEntity->GetActorBrush();
        if(pBrush!=NULL)
        {
            SelBrushList_Add (App->CLSB_Doc->pSelBrushes, pBrush);
        }
// end change
        ++App->CLSB_Doc->NumSelEntities;
    }
}

void CFusionDoc::DeselectEntity
    (
      CEntity *pEntity
    )
{
    assert (pEntity != NULL);

    if (pEntity->IsSelected ())
    {
        pEntity->DeSelect ();
// changed QD Actors
        Brush *pBrush;
        pBrush = pEntity->GetActorBrush();
        if(pBrush!=NULL)
        {
            SelBrushList_Remove(App->CLSB_Doc->pSelBrushes, pBrush);
        }
// end change
        --App->CLSB_Doc->NumSelEntities;
        assert (NumSelEntities >= 0);
    }
}


static geBoolean fdocSelectEntity (CEntity &Ent, void *lParam)
{
    CFusionDoc *pDoc = (CFusionDoc *)lParam;

    Ent.DeSelect ();
    pDoc->SelectEntity (&Ent);
    return GE_TRUE;
}

static geBoolean fdocSelectBrush (Brush *pBrush, void *lParam)
{
    CFusionDoc *pDoc = (CFusionDoc *)lParam;

    SelBrushList_Add(App->CLSB_Doc->pSelBrushes, pBrush);
   
    return GE_TRUE;
}

static geBoolean SelAllBrushFaces (Brush *pBrush, void *lParam)
{
    int iFace, nFaces;
    CFusionDoc *pDoc = (CFusionDoc *)lParam;

    nFaces = Brush_GetNumFaces (pBrush);
    for (iFace = 0; iFace < nFaces; ++iFace)
    {
        Face *pFace;

        pFace = Brush_GetFace (pBrush, iFace);
        Face_SetSelected (pFace, GE_TRUE);
        SelFaceList_Add (App->CLSB_Doc->pSelFaces, pFace);
    }
    return GE_TRUE;
}

void CFusionDoc::SelectAllBrushes (void)
{
    App->CLSB_Doc->DoGeneralSelect ();

    Level_EnumBrushes (App->CLSB_Doc->pLevel, this, ::fdocSelectBrush);

    App->CLSB_Doc->UpdateSelected();
}

void CFusionDoc::SelectAllEntities (void)
{
    App->CLSB_Doc->DoGeneralSelect ();

    App->CLSB_Doc->NumSelEntities = 0;
    Level_EnumEntities (App->CLSB_Doc->pLevel, this, ::fdocSelectEntity);

    App->CLSB_Doc->UpdateSelected();
}

void CFusionDoc::SelectAllFacesInBrushes (void)
{
    App->CLSB_Doc->DoGeneralSelect ();

    // Select all faces on all selected brushes
    int iBrush;
    int NumSelBrushes = SelBrushList_GetSize (App->CLSB_Doc->pSelBrushes);

    for (iBrush = 0; iBrush < NumSelBrushes; ++iBrush)
    {
        Brush *pBrush;

        pBrush = SelBrushList_GetBrush (App->CLSB_Doc->pSelBrushes, iBrush);
        if (Brush_IsMulti (pBrush))
        {
            BrushList_EnumLeafBrushes (App->CL_Brush->Brush_GetBrushList (pBrush), this, ::SelAllBrushFaces);
        }
        else
        {
            ::SelAllBrushFaces (pBrush, this);
        }
    }
    App->CLSB_Doc->UpdateSelected ();

    App->CLSB_Doc->ConfigureCurrentTool();
}

BOOL CFusionDoc::IsEntitySelected(void)
{
    CEntityArray *Entities;

    Entities = Level_GetEntities (App->CLSB_Doc->pLevel);

    for( int Ent = 0; Ent < Entities->GetSize(); Ent++ )
    {
        if ((*Entities)[ Ent ].IsSelected ())
        {
            return TRUE;
        }
    }

    return FALSE;
}

//	CHANGE!	04/16/97	John Moore
//	Sets the entity with the designated ID as the current entity...
void CFusionDoc::SetSelectedEntity( int ID )
{
    CEntityArray *Entities;

    Entities = Level_GetEntities (App->CLSB_Doc->pLevel);
    App->CLSB_Doc->ResetAllSelectedEntities();
    App->CLSB_Doc->mCurrentEntity = ID;
    SelectEntity (&(*Entities)[ID]);
    App->CLSB_Doc->UpdateSelected() ;
}
//	End of CHANGE

void CFusionDoc::AdjustEntityAngle( const ViewVars * v, const geFloat dx )
{
    CEntity *	pEnt ;
    geVec3d		Vec ;
    geVec3d		Angles ;
    CEntityArray *Entities;

    Entities = Level_GetEntities (App->CLSB_Doc->pLevel);

    pEnt = &(*Entities)[App->CLSB_Doc->mCurrentEntity];

    
    if (pEnt->IsCamera ())
//	if (pEnt==pCameraEntity)
    {
        Render_ViewDeltaToRotation ( v, -dx, &Vec);
        // disallow roll for camera
        Vec.Z = 0.0f;
        // if the camera is upside down, then negate yaw
        if (Render_UpIsDown (v))
        {
            Vec.Y = -Vec.Y;
        }
    }
    else
    {
        Render_ViewDeltaToRotation ( v, dx, &Vec);
    }

    pEnt->GetAngles( &Angles, Level_GetEntityDefs (App->CLSB_Doc->pLevel) ) ;
    geVec3d_Add (&Angles, &Vec, &Angles);
    pEnt->SetAngles( &Angles, Level_GetEntityDefs (App->CLSB_Doc->pLevel) ) ;
}

void CFusionDoc::AdjustEntityArc( const ViewVars * v, const geFloat dx )
{
    CEntity *	pEnt ;
    geFloat		fArc ;
    geFloat		fArcDelta ;
    CEntityArray *Entities = Level_GetEntities (App->CLSB_Doc->pLevel);

    pEnt = &(*Entities)[App->CLSB_Doc->mCurrentEntity];

    pEnt->GetArc( &fArc, Level_GetEntityDefs (App->CLSB_Doc->pLevel) ) ;
    
    fArcDelta = Render_ViewDeltaToRadians( v, dx ) ;
    fArc -= fArcDelta;
    if (fArc > 2*M_PI)
    {
        fArc -= 2*M_PI;
    }
    if (fArc < 0)
    {
        fArc += 2*M_PI;
    }

    pEnt->SetArc( fArc, Level_GetEntityDefs (App->CLSB_Doc->pLevel) ) ;
}

void  CFusionDoc::AdjustEntityRadius( const geVec3d *pVec )
{
    CEntity *	pEnt ;
    geFloat		fRadius ;
    CEntityArray *Entities = Level_GetEntities (App->CLSB_Doc->pLevel);

    pEnt = &(*Entities)[App->CLSB_Doc->mCurrentEntity];

    pEnt->GetRadius( &fRadius, Level_GetEntityDefs (App->CLSB_Doc->pLevel) ) ;
    fRadius += geVec3d_Length (pVec);
    if( fRadius < 0.0f )
    {
        fRadius = 0.0f ;
    }
    pEnt->SetRadius( fRadius, Level_GetEntityDefs (App->CLSB_Doc->pLevel) ) ;
}

void CFusionDoc::SelectOrthoRect(CPoint ptStart, CPoint ptEnd, ViewVars *v)
{
    Brush		*	pBrush;
    CEntity		*	pEnt;
    int				i ;
    BrushIterator	bi;
    POINT			Min ;
    POINT			Max ;
    POINT			EntPosView;
    geBoolean		bSelectedSomething = GE_FALSE ;
    CRect			viewRect( ptStart, ptEnd ) ;		//Selection Rect in view coords
    BrushList	*	BList = Level_GetBrushes (App->CLSB_Doc->pLevel);

    viewRect.NormalizeRect() ;

    if(App->CLSB_Doc->IsSelectionLocked())
    {
        return;
    }

    // if Control key isn't pressed, then clear all current selections
    if ((GetAsyncKeyState(VK_SHIFT) & 0x8000) == 0)
    {
        App->CLSB_Doc->ResetAllSelections();
    }

    // Should use ENUM function here
    pBrush = BrushList_GetFirst (BList, &bi);
    while (pBrush != NULL)
    {
        if (BrushIsVisible (pBrush))
        {
            const Box3d	*bbox	=Brush_GetBoundingBox(pBrush);
            Min = Render_OrthoWorldToView ( v, &bbox->Min ); // Get Brush BB in View Coords
            Max = Render_OrthoWorldToView ( v, &bbox->Max );
            if( viewRect.PtInRect( Min ) && viewRect.PtInRect( Max ) )		// If Brush ENTIRELY in rect...
            {			
                App->CLSB_Doc->DoBrushSelection( pBrush, brushSelAlways ) ;
                bSelectedSomething = GE_TRUE ;
            }
        }
        pBrush = BrushList_GetNext (&bi);
    }

    CEntityArray *Entities = Level_GetEntities (App->CLSB_Doc->pLevel);

    for( i = 0; i < Entities->GetSize(); ++i)
    {

        pEnt = &(*Entities)[i];
        if (EntityIsVisible( pEnt) )
        {
            EntPosView = Render_OrthoWorldToView (v, &pEnt->mOrigin);
            if( pEnt->IsSelected () == GE_FALSE )
            {
                if( viewRect.PtInRect( EntPosView ) )
                {
                    App->CLSB_Doc->DoEntitySelection( pEnt );
                    bSelectedSomething = GE_TRUE ;
                }
            }
        }
    }

    if( bSelectedSomething )
        App->CLSB_Doc->UpdateSelected ();

}/* CFusionDoc::SelectOrthoRect */

void CFusionDoc::ScaleSelectedBrushes(geVec3d *ScaleVector)
{
    App->CLSB_Doc->mLastOp				=BRUSH_SCALE;

    geVec3d	VecOrigin	={ 0.0f, 0.0f, 0.0f };

    geVec3d MoveTo;
    geVec3d MoveBack;
    geVec3d_Subtract(&VecOrigin, &App->CLSB_Doc->SelectedGeoCenter, &MoveTo);
    geVec3d_Subtract(&App->CLSB_Doc->SelectedGeoCenter, &VecOrigin, &MoveBack);

    if(App->CLSB_Doc->mModeTool == ID_TOOLS_TEMPLATE)
    {
        Brush_Scale3d(App->CLSB_Doc->CurBrush, ScaleVector);
        if(Brush_IsMulti(App->CLSB_Doc->CurBrush))
        {
            BrushList_ClearCSGAndHollows((BrushList *)App->CL_Brush->Brush_GetBrushList(App->CLSB_Doc->CurBrush), Brush_GetModelId(App->CLSB_Doc->CurBrush));
            BrushList_RebuildHollowFaces((BrushList *)App->CL_Brush->Brush_GetBrushList(App->CLSB_Doc->CurBrush), Brush_GetModelId(App->CLSB_Doc->CurBrush), ::fdocBrushCSGCallback, this);
        }
    }
    else
    {
        int i;
        int NumSelBrushes = SelBrushList_GetSize (App->CLSB_Doc->pSelBrushes);

        for (i = 0; i < NumSelBrushes; ++i)
        {
            Brush *pBrush;
            
            pBrush = SelBrushList_GetBrush (App->CLSB_Doc->pSelBrushes, i);

            Brush_Move(pBrush, &MoveTo);
            Brush_Scale3d(pBrush, ScaleVector);
            Brush_Move(pBrush, &MoveBack);

            if (Brush_IsMulti(pBrush))
            {
                BrushList_ClearCSGAndHollows((BrushList *)App->CL_Brush->Brush_GetBrushList(pBrush), Brush_GetModelId(pBrush));
                BrushList_RebuildHollowFaces((BrushList *)App->CL_Brush->Brush_GetBrushList(pBrush), Brush_GetModelId(pBrush), ::fdocBrushCSGCallback, this);
            }
        }

        CEntityArray *Entities = Level_GetEntities (App->CLSB_Doc->pLevel);
        const EntityTable *EntityDefs = Level_GetEntityDefs (App->CLSB_Doc->pLevel);
        int NumEntities = Entities->GetSize();
        for(i=0;i < NumEntities;i++)
        {
            if ((*Entities)[i].IsSelected())
            {
                (*Entities)[i].Move(&MoveTo);
                (*Entities)[i].Scale3d(ScaleVector, EntityDefs);
                (*Entities)[i].Move(&MoveBack);
            }
        }

    }
}

typedef struct
{
    geVec3d	vp, wp;
    geFloat	MinBDist, CurDist;
    Face	*HitFace, *CurFace;
    Brush	*CurBrush;
    CFusionDoc *pDoc;
} SelectBrush3DCBData;

static geBoolean SelectBrush3DCB(Brush *b, void * lParam)
{
    SelectBrush3DCBData	*pData	=(SelectBrush3DCBData *)lParam;

    if (pData->pDoc->BrushIsVisible (b))
    {
        if(!(Brush_IsSubtract(b)))
        {
            Face *HitFace;
            float CurDist;

            HitFace	=Brush_RayCast(b, &pData->vp, &pData->wp, &CurDist);
            if (HitFace != NULL)
            {
                pData->HitFace = HitFace;
                if (CurDist < pData->MinBDist)
                {
                    pData->CurDist = CurDist;
                    pData->MinBDist	=pData->CurDist;
                    pData->CurBrush	=b;
                    pData->CurFace	=pData->HitFace;
                }
            }
        }
    }
    return	GE_TRUE;
}

void CFusionDoc::PlaceTemplateEntity3D(CPoint point, ViewVars *v)
{
    BrushList	*BList = Level_GetBrushes (App->CLSB_Doc->pLevel);
    SelectBrush3DCBData	bdat;
    geVec3d ClickPosWorld;
    const GPlane	*p;

    Render_ViewToWorld(v, point.x, point.y, &bdat.vp);
    Render_BackRotateVector(v, &bdat.vp, &bdat.wp);
    Render_GetCameraPos(v, &bdat.vp);

    bdat.MinBDist	=999999.0f;
    bdat.CurBrush	=NULL;
    bdat.pDoc		= this;
    BrushList_EnumCSGBrushes(BList, &bdat, SelectBrush3DCB);
    
    if(bdat.CurBrush)
    {
        if(bdat.CurFace)
        {
            geFloat	pDist;

            //find the dist ratio from click ray to plane normal
            p		=Face_GetPlane(bdat.CurFace);
            pDist	=geVec3d_DotProduct(&bdat.wp, &p->Normal);
            if(pDist != 0.0f)
            {
                //grab plane distance and move inward by 16
                pDist	=(Face_PlaneDistance(bdat.CurFace, &bdat.vp) - 16.0f) / pDist;
            }

            geVec3d_Scale(&bdat.wp, pDist, &ClickPosWorld);

            //add in distances from the camera, and current entity position
            geVec3d_Subtract(&ClickPosWorld, &bdat.vp, &ClickPosWorld);

            geVec3d_Inverse (&ClickPosWorld);
            App->CLSB_Doc->mRegularEntity.mOrigin = ClickPosWorld;
            App->CLSB_Doc->UpdateAllViews( UAV_ALL3DVIEWS, NULL );
        }
    }
}

struct FaceSearchCallbackData
{
    const GPlane *pFacePlane;
    geBoolean Found;
    geVec3d ImpactPoint;
    Face *pFoundFace;
    Brush *pFoundBrush;
};
static geBoolean fdocPointOnFace 
    (
      const Face *pFace,
      const geVec3d *pPoint
    )
{
    int pt1, pt2;
    int iVert, NumVerts;
    geVec3d const *Verts;

    NumVerts = Face_GetNumPoints (pFace);
    Verts = Face_GetPoints (pFace);
    pt1 = NumVerts-1;
    pt2 = 0;
    for (iVert = 0; iVert < NumVerts; ++iVert)
    {
        geFloat Dot;
        geVec3d VertToPoint, VertToVert;

        geVec3d_Subtract (&Verts[pt2], &Verts[pt1], &VertToVert);
        geVec3d_Subtract (pPoint, &Verts[pt1], &VertToPoint);

        Dot = geVec3d_DotProduct (&VertToVert, &VertToPoint);
        if (Dot < 0)
        {
            return GE_FALSE;
        }
        pt1 = pt2;
        ++pt2;
    }
    return GE_TRUE;
}

static geBoolean fdocPointInBrushFace
    (
      Brush *pBrush,
      const GPlane *pPlane,
      const geVec3d *pPoint,
      Face **ppFoundFace
    )
{
    int NumFaces;
    int i;

    NumFaces = Brush_GetNumFaces (pBrush);
    for (i = 0; i < NumFaces; ++i)
    {
        Face *pFace;
        const GPlane *pFacePlane;

        pFace = Brush_GetFace (pBrush, i);
        pFacePlane = Face_GetPlane (pFace);

        if(geVec3d_Compare(&pPlane->Normal, &pFacePlane->Normal, 0.01f) &&
           (fabs (pPlane->Dist - pFacePlane->Dist) < 0.01f))
        {
            // if the face plane matches the passed plane
            // then see if the ImpactPoint is within the bounds of the face
            if (::fdocPointOnFace (pFace, pPoint))
            {
                *ppFoundFace = pFace;
                return GE_TRUE;
            }
        }
    }
    return GE_FALSE;
}

static geBoolean fdocFindLeafFace (Brush *pBrush, void *lParam)
{
    if (!Brush_IsSubtract (pBrush))		// don't want cut brushes
    {
        FaceSearchCallbackData *pData;

        pData = (FaceSearchCallbackData *)lParam;
        if (::fdocPointInBrushFace (pBrush, pData->pFacePlane, &(pData->ImpactPoint), &(pData->pFoundFace)))
        {
            pData->pFoundBrush = pBrush;
            pData->Found = GE_TRUE;
            return GE_FALSE;	// found it, so quit...
        }
    }
    return GE_TRUE;
}

static geBoolean fdocFindCutFace (Brush *pBrush, void *lParam)
{
    if (Brush_IsSubtract (pBrush))		// want only cut brushes
    {
        FaceSearchCallbackData *pData;
        GPlane PlaneInv;

        pData = (FaceSearchCallbackData *)lParam;
#pragma message ("Need to reverse plane?")
        PlaneInv = *pData->pFacePlane;
        geVec3d_Inverse (&PlaneInv.Normal);
        PlaneInv.Dist = -PlaneInv.Dist;

        pData = (FaceSearchCallbackData *)lParam;
        if (::fdocPointInBrushFace (pBrush, &PlaneInv, &(pData->ImpactPoint), &(pData->pFoundFace)))
        {
            pData->pFoundBrush = pBrush;
            pData->Found = GE_TRUE;
            return GE_FALSE;	// found it, so quit...
        }
    }
    return GE_TRUE;
}

//slow version checking brushes
void CFusionDoc::SelectRay(CPoint point, ViewVars *v) // hgtterry Select Ray
{
    int			CurEnt = 0;
    geFloat		MinEDist;
    CEntityArray *Entities = Level_GetEntities (App->CLSB_Doc->pLevel);
    BrushList	*BList = Level_GetBrushes (App->CLSB_Doc->pLevel);
    SelectBrush3DCBData	bdat;
    geVec3d ClickPosWorld;
    geBoolean	EntitySelected	=FALSE;

    Render_ViewToWorld(v, point.x, point.y, &bdat.vp);
    Render_BackRotateVector(v, &bdat.vp, &bdat.wp);
    Render_GetCameraPos(v, &bdat.vp);

    Render_ViewToWorld (v, point.x, point.y, &ClickPosWorld);

    MinEDist = bdat.MinBDist = 999999.0f;

    for(int i=0;i < Entities->GetSize();i++)
    {
        CEntity *pEnt;

        pEnt = &(*Entities)[i];
        if (EntityIsVisible (pEnt))
        {
            bdat.CurDist=pEnt->RayDistance (point, v);
            if ((bdat.CurDist < 900.0f)
                && (bdat.CurDist < MinEDist)
                && (bdat.CurDist > MIN_ENTITY_SELECT_DIST))
            {
                MinEDist=bdat.CurDist;
                CurEnt	=i;
            }
        }
    }
    bdat.CurBrush	= NULL;
    bdat.CurFace	= NULL;
    bdat.pDoc		= this;
    BrushList_EnumCSGBrushes(BList, &bdat, SelectBrush3DCB);
        
    if ((bdat.MinBDist < 999999.0f) && (MinEDist > MIN_ENTITY_SELECT_DIST))
    {
        //check the distance of the hit wall
        //see if the closest entity is occluded
        if(bdat.CurBrush)
        {
            if(bdat.CurFace)
            {
                geFloat		pDist;
                const GPlane	*p;

                //find the dist ratio from click ray to plane normal
                p		=Face_GetPlane(bdat.CurFace);
                pDist	=geVec3d_DotProduct(&bdat.wp, &p->Normal);

                if(pDist != 0.0f)
                {
                    pDist	=(Face_PlaneDistance(bdat.CurFace, &bdat.vp)  / pDist);
                }
                geVec3d_Scale(&bdat.wp, pDist, &ClickPosWorld);
                pDist	=geVec3d_Length(&ClickPosWorld);

                if(MinEDist < pDist)
                {
                    if((GetAsyncKeyState(VK_SHIFT) & 0x8000) == 0)
                    {
                        App->CLSB_Doc->ResetAllSelections();
                    }
                    App->CLSB_Doc->DoEntitySelection(&(*Entities)[CurEnt]);
                    EntitySelected	=GE_TRUE;
                }
            }
        }

    }
    if(!EntitySelected && bdat.CurBrush)
    {
        // if Control key isn't pressed, then clear all current selections
        if ((GetAsyncKeyState(VK_SHIFT) & 0x8000) == 0)
        {
            App->CLSB_Doc->ResetAllSelections();
        }
        /*
          At this point, bdat.CurBrush points to the CSG brush that contains
          the hit face.  We want the leaf brush that contains the CSG face
          that was hit.

          So, we search the entire brush list looking for a leaf face (non-cut)
          that has a face that's coplanar with the hit face, and that contains
          the impact point.  If none is found, we then search for a matching 
          cut brush face (again, in leafs) that contains the point.
        */
        {
            const GPlane *p;
            geFloat pDist;
            geVec3d ClickPosWorld;
            FaceSearchCallbackData fsData;

            if (Brush_GetType (bdat.CurBrush) == BRUSH_LEAF)
            {
                // if the found face is on a leaf brush, then skip the rest of the search
                fsData.pFoundFace = bdat.CurFace;
                fsData.Found = GE_TRUE;
                fsData.pFoundBrush = bdat.CurBrush;
            }
            else
            {
                // determine the impact point
                p		=Face_GetPlane(bdat.CurFace);
                pDist	=geVec3d_DotProduct(&bdat.wp, &p->Normal);
                if(pDist != 0.0f)
                {
                    //grab plane distance and move inward by 16
                    pDist	=(Face_PlaneDistance(bdat.CurFace, &bdat.vp)) / pDist;
                }

                geVec3d_Scale(&bdat.wp, pDist, &ClickPosWorld);

                //add in distance from the camera
                geVec3d_Subtract(&ClickPosWorld, &bdat.vp, &ClickPosWorld);
                geVec3d_Inverse (&ClickPosWorld);

                // OK, now search list for a face that contains this point and
                // is coplanar with the matched face.
                fsData.pFacePlane = p;
                fsData.Found = GE_FALSE;
                fsData.pFoundFace = NULL;
                fsData.pFoundBrush = NULL;
                fsData.ImpactPoint = ClickPosWorld;

                BrushList_EnumLeafBrushes (BList, &fsData, ::fdocFindLeafFace);
                if (!fsData.Found)
                {
                    BrushList_EnumLeafBrushes (BList, &fsData, ::fdocFindCutFace);
                }
            }
            if (fsData.Found)
            {
                // We found the hit face.
                if (App->CLSB_Doc->mAdjustMode == ADJUST_MODE_BRUSH)
                {
                    App->CLSB_Doc->DoBrushSelection (fsData.pFoundBrush, brushSelToggle);
                }
                else
                {
                    App->CLSB_Doc->DoBrushSelection (fsData.pFoundBrush, brushSelAlways);
                    // if the face is already in the list, then remove it
                    if (SelFaceList_Remove (App->CLSB_Doc->pSelFaces, fsData.pFoundFace))
                    {
                        Face_SetSelected (fsData.pFoundFace, GE_FALSE);
                    }
                    else
                    {
                        Face_SetSelected (fsData.pFoundFace, GE_TRUE);
                        SelFaceList_Add (App->CLSB_Doc->pSelFaces, fsData.pFoundFace);

                        SelectTextureFromFace3D(point, v);
                        //App->Say("k");
                    }
                    // Deselect any brush that doesn't have selected faces
                    int NumSelBrushes = SelBrushList_GetSize (App->CLSB_Doc->pSelBrushes);
                    for (int i = NumSelBrushes-1; i >= 0; --i)
                    {
                        Brush *pBrush;

                        pBrush = SelBrushList_GetBrush (App->CLSB_Doc->pSelBrushes, i);

                        if (Brush_GetSelectedFace (pBrush) == NULL)
                        {
                            SelBrushList_Remove (App->CLSB_Doc->pSelBrushes, pBrush);
                        }
                    }
                }
            }
        }
    }

    App->CLSB_Doc->UpdateSelected();

/*
    if ((bdat.CurFace == NULL) ||
        ((mAdjustMode == ADJUST_MODE_FACE) && (SelFaceList_GetSize (pSelFaces) == 0)))
    {
        DeleteFaceAttributes ();
        DeleteBrushAttributes ();
    }
    else
    {
        UpdateFaceAttributesDlg ();
        UpdateBrushAttributesDlg ();
    }
*/
}

//selects the texture of the face clicked (doesn't select the face)
void CFusionDoc::SelectTextureFromFace3D(CPoint point, ViewVars *v)
{
    BrushList	*BList = Level_GetBrushes (App->CLSB_Doc->pLevel);
    SelectBrush3DCBData	bdat;

    Render_ViewToWorld(v, point.x, point.y, &bdat.vp);
    Render_BackRotateVector(v, &bdat.vp, &bdat.wp);
    Render_GetCameraPos(v, &bdat.vp);

    bdat.MinBDist	=999999.0f;
    bdat.CurBrush	=NULL;
    bdat.pDoc		= this;
    BrushList_EnumCSGBrushes(BList, &bdat, SelectBrush3DCB);
    
    if(bdat.CurBrush)
    {
        if(bdat.CurFace)
        {
            char TextName[MAX_PATH];
            strcpy(TextName, Face_GetTextureName(bdat.CurFace));
            App->CLSB_Doc->mpMainFrame->m_wndTabControls->SelectTexture(Face_GetTextureDibId(bdat.CurFace));
           
            App->CL_TabsControl->Select_Texture_Tab(Face_GetTextureDibId(bdat.CurFace), TextName);

        }
    }

}

void CFusionDoc::UpdateFaceAttributesDlg (void)
{
//	if (mpFaceAttributes != NULL)
    if (App->CLSB_Doc->mpMainFrame->mpFaceAttributes != NULL)
    {
//		mpFaceAttributes->UpdatePolygonFocus ();
        App->CLSB_Doc->mpMainFrame->mpFaceAttributes->UpdatePolygonFocus();

        if (App->CL_FaceDialog->f_FaceDlg_Active == 1)
        {
            App->CL_FaceDialog->UpdatePolygonFocus();
            App->CL_FaceDialog->UpdateDialog(App->CL_FaceDialog->FaceDlg_Hwnd);
        }
        
    }
}

void CFusionDoc::UpdateBrushAttributesDlg (void)
{
//	if (mpBrushAttributes != NULL)
    if (App->CLSB_Doc->mpMainFrame->mpBrushAttributes != NULL)
    {
//		mpBrushAttributes->UpdateBrushFocus ();
        App->CLSB_Doc->mpMainFrame->mpBrushAttributes->UpdateBrushFocus ();
    }
}

void CFusionDoc::UpdateCameraEntity( const ViewVars *v )
{
    CEntity *	pEnt ;
    geVec3d		Vec ;

    pEnt = EntityList_FindByClassName( Level_GetEntities (App->CLSB_Doc->pLevel), "Camera" ) ;
//	pEnt = pCameraEntity;
    if( pEnt )
    {
        Render_GetCameraPos( v, &Vec ) ;
        pEnt->SetOrigin( Vec.X, Vec.Y, Vec.Z, Level_GetEntityDefs (App->CLSB_Doc->pLevel) ) ;
        Render_GetPitchRollYaw( v, &Vec ) ;
        pEnt->SetAngles( &Vec, Level_GetEntityDefs (App->CLSB_Doc->pLevel) ) ;
        App->CLSB_Doc->UpdateAllViews( UAV_ALL3DVIEWS, NULL );
    }

}/* CFusionDoc::MoveCamera */

void CFusionDoc::SetRenderedViewCamera( const geVec3d * pVec, const geVec3d * pPRY )
{
    POSITION		pos;
    CFusionView	*	pView;

    pos = GetFirstViewPosition();
    while( pos != NULL )
    {
        pView = (CFusionView*)GetNextView(pos) ;
        if( Render_GetViewType( pView->VCam ) & (VIEWSOLID|VIEWTEXTURE|VIEWWIRE) )
        {
            Render_SetPitchRollYaw( pView->VCam, pPRY ) ;
            Render_SetCameraPos( pView->VCam, pVec ) ;
            break ;	// Only 1 rendered view for now
        }
    }
}/* CFusionDoc::SetRenderedViewCamera */

geBoolean CFusionDoc::GetCursorInfo(char *info, int MaxSize)
{
    CFusionView	*pView;
    CPoint		CursorPos, ViewCursorPos;
    CRect		ClientRect;
    POSITION	pos;

    pos		=GetFirstViewPosition();
    info[0]	=0;

    GetCursorPos(&CursorPos);
    HWND CursorWindow = WindowFromPoint(CursorPos);

    while (pos)
    {
        pView	=(CFusionView*)GetNextView(pos);
        if (CursorWindow == pView->m_hWnd)
        {
            pView->GetClientRect(&ClientRect);
            pView->ClientToScreen(&ClientRect);
            if(ClientRect.PtInRect(CursorPos))
            {
/*
                if(pView->mViewType!=(unsigned)mActiveView)
                {
                    if(!pView->IsPanning && mCurrentTool!=ID_TOOLS_BRUSH_SCALEBRUSH
                        && mCurrentTool!=ID_TOOLS_BRUSH_SHEARBRUSH)
                    {
                        if (mCurrentTool==ID_TOOLS_BRUSH_MOVEROTATEBRUSH)
                            SetCursor(AfxGetApp()->LoadStandardCursor(IDC_SIZEALL));
                        else
                            SetCursor(AfxGetApp()->LoadStandardCursor(IDC_ARROW));
                    }
                    return;
                }
*/
                ViewCursorPos=CursorPos;
                pView->ScreenToClient(&ViewCursorPos);

                if(Render_GetViewType(pView->VCam) < VIEWTOP) //3d?
                {
                    if (pView->RMouseButtonDown && !pView->LMouseButtonDown && !pView->IsKeyDown(VK_CONTROL))
                    {
                        SetCursor (AfxGetApp()->LoadCursor(IDC_EYEDROPPER));
                    }
                    else
                    if(!pView->IsPanning)
                    {
                        SetCursor(AfxGetApp()->LoadStandardCursor(IDC_ARROW));
                    }
                    return GE_FALSE;
                }
                else
                {
                    if(!pView->IsPanning && App->CLSB_Doc->mCurrentTool!=ID_TOOLS_BRUSH_SCALEBRUSH
                        && App->CLSB_Doc->mCurrentTool!=ID_TOOLS_BRUSH_SHEARBRUSH)
                    {

                        int FoundThingType;
                        Brush *pMinBrush;
                        CEntity *pMinEntity;
                        geFloat Dist;
                        FoundThingType = App->CLSB_Doc->FindClosestThing (&ViewCursorPos, pView->VCam, &pMinBrush, &pMinEntity, &Dist);
                        if (App->CLSB_Doc->mCurrentTool==ID_TOOLS_BRUSH_MOVEROTATEBRUSH)
                            SetCursor(AfxGetApp()->LoadStandardCursor(IDC_SIZEALL));
                        else
                            SetCursor(AfxGetApp()->LoadStandardCursor(IDC_ARROW));
                        if ((FoundThingType == fctNOTHING) || (Dist > MAX_PIXEL_SELECT_DIST) || (App->CLSB_Doc->mCurrentTool != CURTOOL_NONE))
                        {
                        }
                        else
                        {
                            switch (FoundThingType)
                            {
                                case fctBRUSH :
                                    strncpy (info, App->CL_Brush->Brush_GetName(pMinBrush), MaxSize);
                                    break;
                                case fctENTITY :
                                    strncpy (info, pMinEntity->GetName (), MaxSize);
                                    break;
                                default :
                                    // bad value returned from FindClosestThing
                                    assert (0);
                            }
                        }
                    }
                }
            }
        }
        else
            if ( pView->IsKindOf( RUNTIME_CLASS (CFusionView)) )
            {
                if	(Render_GetViewType(pView->VCam) < VIEWTOP) //3d?
                {
                    pView->RMouseButtonDown = GE_FALSE;
                }
            }
    }
    return GE_TRUE;
}

void CFusionDoc::OnSelectedTypeCmdUI(CCmdUI* pCmdUI)
{
/*
    if(mModeTool==ID_TOOLS_BRUSH_ADJUSTMENTMODE) pCmdUI->Enable();
    else pCmdUI->Enable(0);
*/
    pCmdUI->Enable();
}

// NO UI EXISTS FOR THIS FUNCTION
void CFusionDoc::OnBrushSelectedCopytocurrent() 
{

    return;
    // make the current brush a copy of the other brush 
//	BTemplate = *CurBrush;
//	CurBrush = &BTemplate;
//	UpdateAllViews(UAV_ALL3DVIEWS, NULL);
//	mModeTool=ID_TOOLS_TEMPLATE;
//	ConfigureCurrentTool();
}

void CFusionDoc::OnBrushSelectedDelete() 
{
    App->CLSB_Doc->DeleteSelectedBrushes();
}


void CFusionDoc::SetupDefaultFilename (void)
{
    const CString DocPath = GetPathName ();

    if (DocPath == "")
    {
        // new file...
        char NewFileName[MAX_PATH];
        char NewTitle[MAX_PATH];
        CString titl = GetTitle ();
        strcpy (NewFileName, LastPath);
        ::FilePath_AppendName (NewFileName, titl, NewFileName);
        ::FilePath_SetExt (NewFileName, ".3dt", NewFileName);
        ::FilePath_SetExt (titl, ".3dt", NewTitle);
        //strlwr (NewFileName);
        SetTitle(NewTitle);
        SetPathName(NewFileName, FALSE);
    }
}


void CFusionDoc::OnFileSave() 
{
    if (App->CLSB_Doc->IsNewDocument)
    {
        OnFileSaveAs ();
    }
    else
    {
        SetupDefaultFilename ();
        CDocument::OnFileSave ();
    }
}

void CFusionDoc::OnFileSaveAs() 
{
    SetupDefaultFilename ();
    CDocument::OnFileSaveAs ();
}

// *************************************************************************
// *	            Save_SB:- Terry and Hazel Flanigan 2023	               *
// *************************************************************************
void CFusionDoc::Save_SB()
{
    App->CLSB_File_WE->Save_Document();
}

// *************************************************************************
// * Equity_Load_From_File				OnOpenDocument	 				   *
// *************************************************************************
BOOL CFusionDoc::OnOpenDocument(LPCTSTR lpszPathName) 
{
    ::FilePath_GetDriveAndDir (lpszPathName, LastPath);	

    bool test = App->CLSB_File_WE->Load_File(lpszPathName);
    if (test == 0)
    {
        return FALSE;
    }

    UpdateGridInformation();

    App->CLSB_Doc->IsNewDocument = 0;
    SetModifiedFlag(FALSE);

//	CFusionView* pFusionView = GetCameraView();
//	if (!pFusionView)
//		return FALSE;

//	pFusionView->OnViewType(ID_VIEW_TEXTUREVIEW);

//	RebuildTrees();
//	UpdateAllViews(UAV_ALL3DVIEWS, NULL);
    return TRUE;
}


typedef struct
{
    CFusionDoc	*pDoc;
    int			CurId;
    GNode		**pTree;
    geBoolean	bAddFlocking;	//set for adding flocking brushes
} AddBrushCBData;

static geBoolean AddBrushToBspCB(Brush *pBrush, void * lParam)
{
    AddBrushCBData *pData;
    GNode **tree;
    CFusionDoc *pDoc;

    pData = (AddBrushCBData *)lParam;
    tree = pData->pTree;
    pDoc = pData->pDoc;

    assert(tree);

    if(pData->bAddFlocking ^ Brush_IsFlocking(pBrush))
    {
        if((Brush_GetModelId(pBrush)==pData->CurId) && !Brush_IsSubtract(pBrush))
        {
            if(pDoc)
            {
                if(pDoc->BrushIsVisible(pBrush)
                    && (!Brush_IsClip(pBrush)) && (!Brush_IsHint(pBrush)))
                {
                    *tree	=Node_AddBrushToTree(*tree, pBrush);
                }
            }
            else
            {
                *tree	=Node_AddBrushToTree(*tree, pBrush);
            }
        }
    }
    return	GE_TRUE;
}

//blasts away the OGFaces of the changed trees (makes em draw solid)
void	CFusionDoc::InvalidateDrawTreeOriginalFaces(void)
{
    ModelIterator	mi;
    int				i;
    GNode			*n;
    ModelInfo_Type	*ModelInfo;
    Model			*pMod;

    Node_InvalidateTreeOGFaces(App->CLSB_Doc->mWorldBsp);

    ModelInfo	=Level_GetModelInfo(App->CLSB_Doc->pLevel);
    pMod		=ModelList_GetFirst(ModelInfo->Models, &mi);
    n			=NULL;
    for(i=0;i < ModelList_GetCount(ModelInfo->Models);i++, n=NULL)
    {
        n	=Model_GetModelTree(pMod);
        if(n)
        {
            Node_InvalidateTreeOGFaces(n);
        }
        pMod	=ModelList_GetNext(ModelInfo->Models, &mi);
    }
}

void	CFusionDoc::RebuildTrees(void)
{
    CWaitCursor w;

    ModelIterator	mi;
    int				i, CurId = 0;
    GNode			*n;
    AddBrushCBData	BspCallbackData;
    ModelInfo_Type	*ModelInfo;
    BrushList		*BList;
    Model			*pMod;

// changed QD 11/03 Actors
    UpdateEntityActors();
// end change

    BList = Level_GetBrushes (App->CLSB_Doc->pLevel);
    SetModifiedFlag();

    
    //do the world csg list and tree first
    Node_ClearBsp(App->CLSB_Doc->mWorldBsp);
    App->CLSB_Doc->mWorldBsp	=NULL;

    BrushList_ClearAllCSG (BList);

    BrushList_DoCSG(BList, CurId, ::fdocBrushCSGCallback, this);

    BspCallbackData.pDoc		=this;
    BspCallbackData.CurId		=CurId;
    BspCallbackData.pTree		=&App->CLSB_Doc->mWorldBsp;
    BspCallbackData.bAddFlocking=GE_FALSE;

    BrushList_EnumCSGBrushes (BList, &BspCallbackData, ::AddBrushToBspCB) ;
    BspCallbackData.bAddFlocking=GE_TRUE;
    BrushList_EnumCSGBrushes (BList, &BspCallbackData, ::AddBrushToBspCB) ;

    //build individual model mini trees
    ModelInfo = Level_GetModelInfo (App->CLSB_Doc->pLevel);
    pMod = ModelList_GetFirst (ModelInfo->Models, &mi);
    n		=NULL;
    for(i=0;i < ModelList_GetCount(ModelInfo->Models);i++, n=NULL)
    {
        CurId = Model_GetId (pMod);

        BrushList_DoCSG(BList, CurId, ::fdocBrushCSGCallback, this);

        //change pvoid from this to null to skip the BrushIsVisible check
        BspCallbackData.CurId		=CurId;
        BspCallbackData.pTree		=&n;
        BspCallbackData.bAddFlocking=GE_FALSE;
        BrushList_EnumCSGBrushes (BList, &BspCallbackData, ::AddBrushToBspCB) ;

        BspCallbackData.bAddFlocking=GE_TRUE;
        BrushList_EnumCSGBrushes (BList, &BspCallbackData, ::AddBrushToBspCB) ;

        Node_ClearBsp (Model_GetModelTree(pMod));
        Model_SetModelTree(pMod, n);
        pMod = ModelList_GetNext(ModelInfo->Models, &mi);
    }
    if(App->CLSB_Doc->mAdjustMode==ADJUST_MODE_FACE)
    {
        UpdateFaceAttributesDlg ();
    }

}

void CFusionDoc::OnGbspnowater() 
{
    RebuildTrees();
    App->CLSB_Doc->UpdateAllViews(UAV_ALL3DVIEWS, NULL);
}

//===============================================
// this function will update the information on the status bar
// about the grid
//===============================================
void CFusionDoc::UpdateGridInformation()
{
    if(App->CLSB_Doc->mpMainFrame )
    {
        CMDIChildWnd	*pMDIChild	=(CMDIChildWnd *)App->CLSB_Doc->mpMainFrame->MDIGetActive();
        if(pMDIChild)
        {
            CFusionView	*cv	=(CFusionView *)pMDIChild->GetActiveView();
            if(cv)
            {
                GridInfo *pGridInfo = Level_GetGridInfo (App->CLSB_Doc->pLevel);

                App->CLSB_Doc->mpMainFrame->UpdateGridSize(
                    Render_GetFineGrid(cv->VCam, (pGridInfo->GridType == GridMetric) ? GRID_TYPE_METRIC : GRID_TYPE_TEXEL),
                    pGridInfo->UseGrid,
                    ((pGridInfo->SnapType == GridMetric) ? pGridInfo->MetricSnapSize : pGridInfo->TexelSnapSize),
                    pGridInfo->GridType,
                    pGridInfo->SnapType);
            }
        }
    }
}/* CFusionDoc::UpdateGridInformation */

static geBoolean	IsBrushNotClipOrHint(const Brush *b)
{
    assert(b != NULL);
    
    return	(Brush_IsHint(b) || Brush_IsClip(b))? GE_FALSE : GE_TRUE;
}


static void DrawEntity (CEntity *pEnt, ViewVars *v, const EntityTable *pEntityDefs)
{
    const geBitmap *pBitmap;

    pBitmap = pEnt->GetBitmapPtr (pEntityDefs);

    Render_3DTextureZBuffer(v, &pEnt->mOrigin, pBitmap);
}

void CFusionDoc::RenderWorld(ViewVars *v, CDC *pDC) // hgtterry RenderWorld
{
#define PEN_WHITE_COLOR RGB(255,255,255)
#define PEN_CYAN_COLOR  RGB(0,255,0)
#define PEN_BLUE_COLOR  RGB(0,0,255)
#define PEN_PURPLE_COLOR RGB(255,0,255)
#define PEN_YELLOW_COLOR RGB(255,255,0)
#define PEN_HINT_COLOR  RGB(0,100,0)
#define PEN_CLIP_COLOR  RGB(128,0,128)

    int				i;
    GNode			*n;
    ModelIterator	mi;
    Model			*pModel;
    geBoolean		DoBlit	=GE_FALSE;
    BrushDrawData	brushDrawData;
    BrushList		*BList;


    // Temporary Hack for not updating
//#pragma message ("This temporary hack needs to be fixed.  Perhaps a 'force redraw' flag?")
/*
    if (Level_RebuildBspAlways (pLevel) == GE_FALSE)
    {
        return ;
    }
*/
    if (App->CLSB_Doc->pLevel == NULL)
    {
        // must not be loaded yet...
        return ;
    }

    BList = Level_GetBrushes (App->CLSB_Doc->pLevel);
    Render_UpdateViewPos(v);
    Render_SetUpFrustum(v);

    brushDrawData.pViewBox = NULL ;
    brushDrawData.pDC = pDC ;
    brushDrawData.v = v ;
    brushDrawData.pDoc = this;
    brushDrawData.GroupId = fdoc_SHOW_ALL_GROUPS;
    brushDrawData.FlagTest = NULL;
    brushDrawData.Color = PEN_WHITE_COLOR;

    if((Render_GetViewType(v) & (VIEWSOLID|VIEWTEXTURE)) && App->CLSB_Doc->mWorldBsp)
    {
        Render_RenderTree(v, App->CLSB_Doc->mWorldBsp, pDC->m_hDC, ZFILL);
        DoBlit	=TRUE;
    }
    else
    {
        Render_ClearViewDib (v);
        brushDrawData.FlagTest = IsBrushNotClipOrHint;
        BrushList_EnumLeafBrushes(BList, &brushDrawData, ::BrushDrawWire3dCB);
    }
    if(bShowClipBrushes)
    {
        brushDrawData.Color	=PEN_CLIP_COLOR;
        brushDrawData.FlagTest = Brush_IsClip;
        BrushList_EnumLeafBrushes(BList, &brushDrawData, ::BrushDrawWire3dZBufferCB);
    }
    if(bShowHintBrushes)
    {
        brushDrawData.Color	=PEN_HINT_COLOR;
        brushDrawData.FlagTest = Brush_IsHint;
        BrushList_EnumLeafBrushes(BList, &brushDrawData, ::BrushDrawWire3dZBufferCB);
    }

    CEntityArray *Entities = Level_GetEntities (App->CLSB_Doc->pLevel);

    for(i=0;i < Entities->GetSize();i++)
    {
        CEntity *pEnt;

        pEnt = &(*Entities)[i];

        if( !Render_PointInFrustum(v, &pEnt->mOrigin ) )
            continue ;

        if( EntityIsVisible( pEnt ) == GE_FALSE )
            continue;

        if (pEnt->IsSelected ())
            continue;

        ::DrawEntity (pEnt, v, Level_GetEntityDefs (App->CLSB_Doc->pLevel));
    }

    if(!(App->CLSB_Doc->GetSelState() & NOENTITIES))
    {
        for(i=0;i < Entities->GetSize();i++)
        {
            CEntity *pEnt = &(*Entities)[i];

            if(!(pEnt->IsSelected () && EntityIsVisible( pEnt )) )
                continue;

            if(!Render_PointInFrustum(v, &pEnt->mOrigin))
                continue;

            const geBitmap *pBitmap;

            pBitmap = pEnt->GetBitmapPtr (Level_GetEntityDefs (App->CLSB_Doc->pLevel));

            Render_3DTextureZBufferOutline(v, &pEnt->mOrigin, pBitmap, RGB(0,255,255));
        }
    }

    if(DoBlit)
    {
        ModelInfo_Type *ModelInfo = Level_GetModelInfo (App->CLSB_Doc->pLevel);

        //render the models
        pModel = ModelList_GetFirst (ModelInfo->Models, &mi);
        while (pModel != NULL)
        {
            n = Model_GetModelTree (pModel);
            if (n != NULL)
            {
                Render_RenderTree(v, n, pDC->m_hDC, ZBUFFER);
                DoBlit	=TRUE;
            }
            pModel = ModelList_GetNext (ModelInfo->Models, &mi);
        }
    }


    brushDrawData.FlagTest = NULL;
    brushDrawData.Color = PEN_CYAN_COLOR;

    int NumSelBrushes = SelBrushList_GetSize (App->CLSB_Doc->pSelBrushes);
    for(i=0;i < NumSelBrushes;i++)
    {
        Brush *pBrush;

        pBrush = SelBrushList_GetBrush (App->CLSB_Doc->pSelBrushes, i);
// changed QD Actors
        if(!bShowActors)
            if(strstr(App->CL_Brush->Brush_GetName(pBrush),".act")!=NULL)
                continue;
// end change
        if(Brush_IsMulti(pBrush))
        {
            BrushList_EnumLeafBrushes(App->CL_Brush->Brush_GetBrushList(pBrush), &brushDrawData, ::BrushDrawWire3dCB);
        }
        else
        {
            Render_RenderBrushFaces(v, pBrush, brushDrawData.Color);
        }
    }

    if(!(App->CLSB_Doc->GetSelState() & NOFACES))
    {
        brushDrawData.Color = PEN_PURPLE_COLOR;
        BrushList_EnumLeafBrushes(BList, &brushDrawData, ::BrushDrawWireSel3dCB);
    }

    if((App->CLSB_Doc->mModeTool==ID_TOOLS_TEMPLATE)||
        (App->CLSB_Doc->mModeTool==ID_TOOLS_CAMERA && App->CLSB_Doc->GetSelState()==NOSELECTIONS))
    {
        brushDrawData.Color = PEN_BLUE_COLOR;
        if(!App->CLSB_Doc->TempEnt)
        {
            if(Brush_IsMulti(App->CLSB_Doc->CurBrush))
            {
                BrushList_EnumLeafBrushes(App->CL_Brush->Brush_GetBrushList(App->CLSB_Doc->CurBrush), &brushDrawData, ::BrushDrawWire3dCB);
            }
            else
            {
                Render_RenderBrushFaces(v, App->CLSB_Doc->CurBrush, brushDrawData.Color);
            }
        }
        else
        {
            if(Render_PointInFrustum(v, &App->CLSB_Doc->mRegularEntity.mOrigin))
            {
                ::DrawEntity (&App->CLSB_Doc->mRegularEntity, v, Level_GetEntityDefs (App->CLSB_Doc->pLevel));
            }
        }
    }

//	if (DoBlit)
    {
        Render_BlitViewDib(v, pDC->m_hDC);
    }
}

void CFusionDoc::GetRotationPoint
    (
      geVec3d *pVec
    )
{
    Model *pModel;
    ModelInfo_Type *ModelInfo = Level_GetModelInfo (App->CLSB_Doc->pLevel);

    pModel = ModelList_GetAnimatingModel (ModelInfo->Models);
    if (pModel != NULL)
    {
        CModelDialog *ModelTab;
        geVec3d Xlate;

        // we're animating a model, so use its current position
        Model_GetCurrentPos (pModel, pVec);
        // We have to add the current move translation
        ModelTab = App->CLSB_Doc->mpMainFrame->GetModelTab ();
        if (ModelTab != NULL)
        {
            //ModelTab->GetTranslation (&Xlate);
        }
        else
        {
            geVec3d_Clear (&Xlate);
        }
        geVec3d_Add (pVec, &Xlate, pVec);
    }
    else
    {
        *pVec = App->CLSB_Doc->SelectedGeoCenter;
    }
}

void CFusionDoc::RotateSelectedBrushList
    (
      SelBrushList *pList,
      geVec3d const *v
    )
{
    int i;
    geXForm3d rm;
    geVec3d RotationPoint;
    int NumBrushes = SelBrushList_GetSize (pList);

    App->CLSB_Doc->mLastOp = BRUSH_ROTATE;

    // if we're animating a model, we want to rotate about the
    // model's current rotation origin--taking into account any
    // current translations.
    GetRotationPoint (&RotationPoint);

    
    geVec3d_Add(v, &App->CLSB_Doc->FinalRot, &App->CLSB_Doc->FinalRot);
    geXForm3d_SetEulerAngles(&rm, v);

    for(i=0;i < NumBrushes;i++)
    {
        Brush *pBrush = SelBrushList_GetBrush (pList, i);
// changed QD Actors
// don't rotate ActorBrushes
        if(strstr(App->CL_Brush->Brush_GetName(pBrush),".act")!=NULL)
            continue;
// end change
        Brush_Rotate (pBrush, &rm, &RotationPoint);
    }

    CEntityArray *Entities = Level_GetEntities (App->CLSB_Doc->pLevel);
    const EntityTable *EntityTable = Level_GetEntityDefs (App->CLSB_Doc->pLevel);
    for(i=0;i < Entities->GetSize();i++)
    {
        if ((*Entities)[i].IsSelected ())
        {
            (*Entities)[i].DoneRotate(&rm, &RotationPoint, EntityTable);
        }
    }

}/* CFusionDoc::RotateSelectedBrushList */

void CFusionDoc::RotateSelectedBrushes(geVec3d const *v)
{
    RotateSelectedBrushList (App->CLSB_Doc->pTempSelBrushes, v);
}

void CFusionDoc::RotateSelectedBrushesDirect(geVec3d const *v)
{
    RotateSelectedBrushList (App->CLSB_Doc->pSelBrushes, v);
    UpdateSelectedModel (BRUSH_ROTATE, v);
    geVec3d_Clear (&App->CLSB_Doc->FinalRot);
}

void CFusionDoc::UpdateSelectedModel
    (
      int MoveRotate,
      geVec3d const *pVecDelta
    )
{
    ModelIterator mi;
    Model *pModel;
    ModelInfo_Type *ModelInfo = Level_GetModelInfo (App->CLSB_Doc->pLevel);
    BrushList *BList = Level_GetBrushes (App->CLSB_Doc->pLevel);

    // notify model dialog so that it can update animation deltas if required
    App->CLSB_Doc->mpMainFrame->UpdateSelectedModel (MoveRotate, pVecDelta);

    // For each model that is fully selected, update its reference position.
    pModel = ModelList_GetFirst (ModelInfo->Models, &mi);
    while (pModel != NULL)
    {
        // don't mess with models that are animating
        if (Model_IsAnimating (pModel) != GE_TRUE)
        {
            if (Model_IsSelected (pModel, App->CLSB_Doc->pSelBrushes, BList))
            {
                Model_UpdateOrigin (pModel, MoveRotate, pVecDelta);
            }
        }
        pModel = ModelList_GetNext (ModelInfo->Models, &mi);
    }
}

// ME Terry
//void CFusionDoc::UpdateAllViews(int Mode, CView* pSender, BOOL Override)
//{
//    //App->Say("UpdateAllViews");
//    if(IsModified() && ((Mode & REBUILD_QUICK ) && (Level_RebuildBspAlways (App->CLSB_Doc->pLevel)))||(Override))
//    {
//        RebuildTrees();
//    }
//    else if((Mode & REBUILD_QUICK) && (!Level_RebuildBspAlways (App->CLSB_Doc->pLevel)))
//    {
//        InvalidateDrawTreeOriginalFaces();
//    }
//
//    if(Mode & REBUILD_QUICK)
//        Mode &= ~REBUILD_QUICK;
//
//    //	Do we want to redraw everything?
//    if (Mode & UAV_ALLVIEWS)
//    {
//        CDocument::UpdateAllViews(pSender);
//        return;
//    }
//
//    POSITION pos = GetFirstViewPosition();
//
//    while (pos != NULL)
//    {
//        CView* pView = GetNextView(pos);
//
//        if ( pView->IsKindOf( RUNTIME_CLASS (CFusionView)) )
//        {
//            CFusionView* pFusionView = (CFusionView*) pView;
//            CDC* pDC = pFusionView->GetDC();
//
//            switch(Mode)
//            {
//            case UAV_ACTIVE3DVIEW_ONLY:
//
//                if( pFusionView->GetParentFrame() == mpActiveViewFrame )
//                    pFusionView->Invalidate( TRUE );
//                break;
//
//            case UAV_NONACTIVE3DVIEWS_ONLY:
//
//                if( pFusionView->GetParentFrame() != mpActiveViewFrame )
//                    pFusionView->Invalidate( TRUE );
//                break;
//
//            case UAV_TEXTUREVIEW_ONLY:
//
//                if (pFusionView->mViewType == ID_VIEW_TEXTUREVIEW)
//                    pFusionView->Invalidate(TRUE);
//                break;
//
//            case UAV_RENDER_ONLY:
//
//                switch(pFusionView->mViewType)
//                {
//                case ID_VIEW_3DWIREFRAME:
//                case ID_VIEW_TEXTUREVIEW:
//
//                    pFusionView->Invalidate(TRUE);
//                    break;
//
//                default:
//                    break;
//                }
//                break;
//
//            case UAV_GRID_ONLY:
//
//                switch(pFusionView->mViewType)
//                {
//                case ID_VIEW_TOPVIEW:
//                case ID_VIEW_SIDEVIEW:
//                case ID_VIEW_FRONTVIEW:
//
//                    pFusionView->Invalidate(TRUE);
//                    break;
//                }
//                break;
//
//
//            case UAV_THIS_GRID_ONLY:
//                if( pFusionView == pSender )
//                {
//                    switch(pFusionView->mViewType)
//                    {
//                    case ID_VIEW_TOPVIEW:
//                    case ID_VIEW_SIDEVIEW:
//                    case ID_VIEW_FRONTVIEW:
//                        pFusionView->Invalidate(TRUE);
//                        break;
//                    }
//                }
//                break;
//
//            case UAV_ALL3DVIEWS:
//
//                pFusionView->Invalidate(TRUE);
//                break;
//
//            default:
//                break;
//            }
//
//            pFusionView->ReleaseDC(pDC);
//        }
//    }
//}

/*
void CFusionDoc::FaceAttributesDialog ()
{
    //	Has a face been selected?  Are we selecting faces...
//	if ((mAdjustMode == ADJUST_MODE_FACE) && (SelFaceList_GetSize (pSelFaces) > 0))
    {
        if (mpFaceAttributes == NULL)
        {
            mpFaceAttributes = new CFaceAttributesDialog (this);
        }
    }
}

void CFusionDoc::NullFaceAttributes()
{
    mpFaceAttributes = NULL;
}
*/

//void CFusionDoc::NullBrushAttributes(void){  mpBrushAttributes=NULL;  }

#pragma warning (disable:4100)
#pragma warning (default:4100)

static geBoolean FindSelectedFaceCB (Brush *b, void *lParam)
{
    Face **ppSelectedFace = (Face **)lParam;
    int i;

    for (i = 0; i < Brush_GetNumFaces (b); ++i)
    {
        Face *pFace;

        pFace = Brush_GetFace (b, i);
        if (Face_IsSelected (pFace))
        {
            *ppSelectedFace = pFace;
            return GE_FALSE;
        }
    }
    return GE_TRUE;
}

Face *CFusionDoc::FindSelectedFace (void)
{
    Face *pSelectedFace;

    pSelectedFace = NULL;
    BrushList_EnumLeafBrushes (Level_GetBrushes (App->CLSB_Doc->pLevel), &pSelectedFace, ::FindSelectedFaceCB);
    return pSelectedFace;
}

void CFusionDoc::OnConstrainhollows()
{
    App->CLSB_Doc->mConstrainHollows = !App->CLSB_Doc->mConstrainHollows ;
    SetModifiedFlag();
}

void CFusionDoc::OnUpdateConstrainhollows(CCmdUI* pCmdUI)
{
    pCmdUI->SetCheck(App->CLSB_Doc->mConstrainHollows );
}

void CFusionDoc::OnGeneralselect()
{
    App->CLSB_Doc->DoGeneralSelect ();
}

void CFusionDoc::OnUpdateGeneralselect(CCmdUI* pCmdUI)
{
    pCmdUI->SetCheck ((App->CLSB_Doc->mModeTool == ID_GENERALSELECT) ? 1 : 0);
}

void CFusionDoc::OnCloseDocument() // hgtterry Exit Aplication
{
   
    if (App->CLSB_Ogre->OgreIsRunning == 1)
    {
        delete App->CLSB_Ogre->mRoot;
        App->CLSB_Ogre->mRoot = NULL;
    }

    delete App->CLSB_Doc;

    App->CLSB_Mesh_Mgr->Delete_Brush_List();
    App->CLSB_Mesh_Mgr->Delete_Group_Brushes();

    //App->Say("Last Close");
    CDocument::OnCloseDocument();
}

/*
void CFusionDoc::OnThingAttributes() 
{
    switch( mAdjustMode )
    {
        case ADJUST_MODE_BRUSH :
            OnToolsBrushAttributes ();
            break;

        case ADJUST_MODE_FACE :
            OnToolsFaceAttributes ();
            break;

        default :
            assert (0);  // bad...
            break;
    }
}
*/

void CFusionDoc::OnUpdateEditCopy(CCmdUI* pCmdUI) 
{
    if(App->CLSB_Doc->GetSelState()!=NOSELECTIONS)	pCmdUI->Enable( TRUE );
    else pCmdUI->Enable( FALSE );
}

void CFusionDoc::OnUpdateEditPaste(CCmdUI* pCmdUI) 
{
/*	COleDataObject dobj;

    dobj.AttachClipboard();

    //	Is there any data available?
    if( dobj.IsDataAvailable( (unsigned short)(mpMainFrame->m_CB_FUSION_BRUSH_FORMAT) ) ||
        dobj.IsDataAvailable( (unsigned short)(mpMainFrame->m_CB_FUSION_ENTITY_FORMAT) ) )
        pCmdUI->Enable( TRUE );
    else
        pCmdUI->Enable( FALSE );
*/
    if ( (((CFusionApp *)AfxGetApp())->NumCopiedBrushes) ||	(((CFusionApp *)AfxGetApp())->NumCopiedEntities) )
        pCmdUI->Enable( TRUE );
    else
        pCmdUI->Enable( FALSE );
}

//	Place selected brushes on clipboard and then delete them...
void CFusionDoc::OnEditCut() 
{
    BOOL	Flag	=(App->CLSB_Doc->GetSelState() & ANYBRUSH);

    OnEditCopy();
    App->CLSB_Doc->DeleteSelectedBrushes();

    if( Flag )
        App->CLSB_Doc->UpdateAllViews(UAV_ALL3DVIEWS | REBUILD_QUICK, NULL);
    else
        App->CLSB_Doc->UpdateAllViews( UAV_ALL3DVIEWS, NULL );

    SetModifiedFlag();
}

void CFusionDoc::OnEditDelete() 
{
    App->CLSB_Doc->OnEditDelete();
}

void CFusionDoc::OnUpdateEditCut(CCmdUI* pCmdUI) 
{
    if(App->CLSB_Doc->GetSelState()!=NOSELECTIONS)	pCmdUI->Enable( TRUE );
    else pCmdUI->Enable( FALSE );
}

//	Place selected brushes on clipboard
void CFusionDoc::OnEditCopy() 
{
    int	*NumCopiedBrushes = &(((CFusionApp *)AfxGetApp())->NumCopiedBrushes);
    int	*NumCopiedEntities = &(((CFusionApp *)AfxGetApp())->NumCopiedEntities);
    Brush ***CopiedBrushes = &((CFusionApp *)AfxGetApp())->CopiedBrushes;
    CEntity ***CopiedEntities = &((CFusionApp *)AfxGetApp())->CopiedEntities;
    
    ((CFusionApp *)AfxGetApp())->ClearClipboard();

    int		i;
    int		NumSelBrushes;

    NumSelBrushes = SelBrushList_GetSize (App->CLSB_Doc->pSelBrushes);
    
    if( NumSelBrushes )
    {
        (*CopiedBrushes) = (Brush**)malloc(sizeof(Brush*) * NumSelBrushes);

        if (*CopiedBrushes) {

            for(i=0;i < NumSelBrushes;i++)
            {
                Brush *pBrush;
                Brush *pClone;

                pBrush = SelBrushList_GetBrush (App->CLSB_Doc->pSelBrushes, i);
// changed QD Actors
// don't copy ActorBrushes
                if(strstr(App->CL_Brush->Brush_GetName(pBrush),".act")!=NULL)
                {
                    (*CopiedBrushes)[i] = NULL;
                    continue;
                }
// end change
                pClone = Brush_Clone (pBrush);

                (*CopiedBrushes)[i] = pClone;
            }

            *NumCopiedBrushes = NumSelBrushes;
        }
    }


    CEntity  TEnt;
    CEntityArray *Entities;
    int cnt;
    CEntity *pEnt;

    int		NumSelEntities = 0;

    Entities = Level_GetEntities (App->CLSB_Doc->pLevel);

    cnt = Entities->GetSize() ;
    for( i=0 ; i < cnt; i++ )
    {
        pEnt = &(*Entities)[i];
        if( pEnt->IsCamera() == GE_FALSE  )	// Exclude Cameras
        {
            if (pEnt->IsSelected ())
            {
                NumSelEntities++;
            }
        }
    }

    if (NumSelEntities) {

        (*CopiedEntities) = (CEntity**)malloc(sizeof(CEntity*) * NumSelEntities);

        if (*CopiedEntities) {

            *NumCopiedEntities = NumSelEntities;
            NumSelEntities = 0;

            for( i=0 ; i < cnt; i++ )
            {
                pEnt = &(*Entities)[i];
                if( pEnt->IsCamera() == GE_FALSE  )	// Exclude Cameras
                {
                    if (pEnt->IsSelected ())
                    {
                        (*CopiedEntities)[NumSelEntities] = new CEntity;
                        if ((*CopiedEntities)[NumSelEntities])
                        {
                            (*(*CopiedEntities)[NumSelEntities]) = *pEnt;
                            (*CopiedEntities)[NumSelEntities]->DeSelect();
                        }

                        NumSelEntities++;
                    }
                }
            }
        }
    }
}


void CFusionDoc::OnEditPaste() 
{

    int	*NumCopiedBrushes = &(((CFusionApp *)AfxGetApp())->NumCopiedBrushes);
    int	*NumCopiedEntities = &(((CFusionApp *)AfxGetApp())->NumCopiedEntities);
    Brush ***CopiedBrushes = &((CFusionApp *)AfxGetApp())->CopiedBrushes;
    CEntity ***CopiedEntities = &((CFusionApp *)AfxGetApp())->CopiedEntities;

    if ((*NumCopiedBrushes) || (*NumCopiedEntities)) {
        
        App->CLSB_Doc->ResetAllSelections();
    
        int		i;

        for(i=0;i < (*NumCopiedBrushes);i++)
        {
            if ((*CopiedBrushes)[i])
            {

                Brush *pClone;
                pClone = Brush_Clone ((*CopiedBrushes)[i]);
                Level_AppendBrush (App->CLSB_Doc->pLevel, pClone);
                SelBrushList_Add (App->CLSB_Doc->pSelBrushes, pClone);
            }
        }

        CEntityArray *Entities;
        Entities = Level_GetEntities (App->CLSB_Doc->pLevel);

        for(i=0;i < (*NumCopiedEntities);i++)
        {
            if ((*CopiedEntities)[i]) {

                CEntity CloneEntity;
                int		Index;

                CloneEntity = (*(*CopiedEntities)[i]);

                Index = Level_AddEntity(App->CLSB_Doc->pLevel, CloneEntity);

                SelectEntity( &(*Entities)[Index] );
            }
        }
    }
    // Copying items places the new items in the same group, so we must update the UI
//	mpMainFrame->m_wndTabControls->GrpTab->UpdateTabDisplay( this ) ;
    App->CL_TabsGroups_Dlg->Fill_ListBox(); // hgtterry App->CL_TabsGroups_Dlg->Fill_ListBox()
    App->CLSB_Doc->UpdateSelected();
    App->CLSB_Doc->UpdateAllViews( UAV_ALL3DVIEWS, NULL );
    
    SetModifiedFlag();
}

int CFusionDoc::DoCompileDialog(void)
{
    //CompileParamsType *CompileParams;

    //CompileParams = Level_GetCompileParams (pLevel);
    //// Build output file if none there...
    //if (CompileParams->Filename[0] == '\0')
    //{
    //	FilePath_SetExt (GetPathName (), ".prebsp", CompileParams->Filename);
    //}

    ////CCompileDialog CompileDlg (AfxGetMainWnd (), CompileParams);

    return 0;//CompileDlg.DoModal ();

//	SetModifiedFlag();
}

static char *SkyFaceNames[6] =
    {"SkyLeft", "SkyRight", "SkyTop", "SkyBottom", "SkyFront", "SkyBack"};

typedef struct
{
    geBoolean SuppressHidden;
    geBoolean VisDetail;
    CFusionDoc *pDoc;
    int BrushCount;
    FILE *f;
} fdocBrushEnumData;

static geBoolean fdocBrushCountCallback(Brush *b, void * pVoid)
{
    fdocBrushEnumData *pData;

    pData = (fdocBrushEnumData *)pVoid;

    if ((Brush_GetModelId(b) == 0) && (!Brush_IsSubtract(b)) &&
        ((pData->SuppressHidden == GE_FALSE) || (pData->pDoc->BrushIsVisible (b))))
    {
        ++(pData->BrushCount);
    }
    return	GE_TRUE;
}


static geBoolean fdocBrushWriteCallback(Brush *b, void * pVoid)
{
    fdocBrushEnumData *pData;

    pData = (fdocBrushEnumData *)pVoid;

    if ((Brush_GetModelId(b) == 0) && (!Brush_IsSubtract(b)) &&
        ((pData->SuppressHidden == GE_FALSE) || (pData->pDoc->BrushIsVisible (b))))
    {
        Brush_WriteToMap (b, pData->f, pData->VisDetail);
    }
    return	GE_TRUE;
}

typedef struct
{
    FILE *f;
    ModelList *Models;
    CEntityArray *Entities;
    CFusionDoc	*pDoc;
} fdocEntityToMapData;

static geBoolean fdocEntityToMap (CEntity &Ent, void *lParam)
{
    fdocEntityToMapData *pData;

    pData = (fdocEntityToMapData *)lParam;
    if (!Ent.IsCamera ())
    {
        CompileParamsType *CompileParams = Level_GetCompileParams (App->CLSB_Doc->pLevel);
        if(CompileParams->SuppressHidden)
        {
            if(pData->pDoc->EntityIsVisible(&Ent))
            {
                Ent.WriteToMap (pData->f, pData->Models, pData->Entities, Level_GetEntityDefs (App->CLSB_Doc->pLevel));
            }
        }
        else
        {
            Ent.WriteToMap (pData->f, pData->Models, pData->Entities, Level_GetEntityDefs (App->CLSB_Doc->pLevel));
        }
    }
    return GE_TRUE;
}

typedef geBoolean (*EntityCount_CB)(const class CEntity *);
typedef struct fdocEntityCountDataTag
{
    int				Count;
    CFusionDoc		*pDoc;
} fdocEntityCountData;

static geBoolean fdocCountNonCameraEntities (CEntity &Ent, void *lParam)
{
    fdocEntityCountData	*ecnt	=(fdocEntityCountData *)lParam;
    if(!Ent.IsCamera())
    {
        CompileParamsType *CompileParams = Level_GetCompileParams (App->CLSB_Doc->pLevel);
        if(CompileParams->SuppressHidden)
        {
            if(ecnt->pDoc->EntityIsVisible(&Ent))
            {
                ecnt->Count++;
            }
        }
        else
        {
            ecnt->Count++;
        }
    }
    return GE_TRUE;
}

// Write level data to map file for compiling
geBoolean CFusionDoc::WriteLevelToMap
    (
      const char *Filename
    )
{
    static const int Version = 1;
    static const int ftag = 0x4642434E; // NCBF
    int NumEntities, i;
    FILE *exfile;
    ModelInfo_Type *ModelInfo;
    BrushList *BList;
    fdocEntityCountData	ecnt;
    CompileParamsType *CompileParams = Level_GetCompileParams (App->CLSB_Doc->pLevel);

// changed QD Actors
// don't want to compile ActorBrushes
    CEntityArray *Entities;
    Entities = Level_GetEntities (App->CLSB_Doc->pLevel);

    for(i=0;i < Entities->GetSize();i++)
    {
        Brush *pBrush = (*Entities)[i].GetActorBrush();

        if(pBrush!=NULL)
            Level_RemoveBrush(App->CLSB_Doc->pLevel, pBrush);
    }
// end change
    BList = Level_GetBrushes (App->CLSB_Doc->pLevel);

    assert (BList != NULL);


    exfile = fopen (Filename, "wb");
    if (exfile == NULL)
    {
        return GE_FALSE;
    }

    ModelInfo = Level_GetModelInfo (App->CLSB_Doc->pLevel);
    // write header information
    TypeIO_WriteInt (exfile, Version);
    TypeIO_WriteInt (exfile, ftag);
    /*
      Number of entities to be written is the sum of:
        World Entity		one
        Regular entities	one for each regular entity that isn't a camera
        Models				one for each model
        Type Information	one entity for each type
        ----------------
    */
    ecnt.Count	= 1;		// world entity
    ecnt.pDoc	= this;
    Level_EnumEntities(App->CLSB_Doc->pLevel, &ecnt, ::fdocCountNonCameraEntities);

    NumEntities = ecnt.Count + ModelList_GetCount (ModelInfo->Models) +	// models
                   EntityTable_GetTypeCount (Level_GetEntityDefs (App->CLSB_Doc->pLevel));			// type information

    TypeIO_WriteInt (exfile, NumEntities);

    //write the world entity first
    {
        BrushList *BList;

        // count brushes and write count to file
        fdocBrushEnumData EnumData;
            
        EnumData.SuppressHidden = CompileParams->SuppressHidden;
        EnumData.VisDetail = CompileParams->VisDetailBrushes;
        EnumData.pDoc = this;
        EnumData.BrushCount = 0;
        EnumData.f = exfile;

        BList = Level_GetBrushes (App->CLSB_Doc->pLevel);

        BrushList_EnumCSGBrushes (BList, &EnumData, ::fdocBrushCountCallback);
    
        TypeIO_WriteInt (exfile, EnumData.BrushCount);

        // and write the model 0 brushes
        BrushList_EnumCSGBrushes (BList, &EnumData, ::fdocBrushWriteCallback);
    }

    {
        int nSkyFaces;
        int iFace;
        SkyFaceTexture *SkyFaces;
        geVec3d SkyRotationAxis;
        geFloat SkyRotationSpeed, SkyTextureScale;

        SkyFaces = Level_GetSkyInfo (App->CLSB_Doc->pLevel, &SkyRotationAxis, &SkyRotationSpeed, &SkyTextureScale);

        // determine how many sky faces to write...
        nSkyFaces = 0;
        for (iFace = 0; iFace < 6; ++iFace)
        {
            SkyFaceTexture *pFace;

            pFace = &SkyFaces[iFace];
            if (pFace->Apply && (pFace->TextureName != NULL) && (*pFace->TextureName != '\0'))
            {
                ++nSkyFaces;
            }
        }

        TypeIO_WriteInt (exfile, 0);  // no motion data for this model
        TypeIO_WriteInt (exfile, 4+nSkyFaces);  // numfields = #sky faces + TextureLibrary + SkyAxis + SkyRotation + SkyScaling
        TypeIO_WriteString (exfile, "TextureLib");
        TypeIO_WriteString (exfile, Level_GetWadPath (App->CLSB_Doc->pLevel));
        
        // write sky information
        {
            char s[100];

            sprintf (s, "%f %f %f", SkyRotationAxis.X, SkyRotationAxis.Y, SkyRotationAxis.Z);
            TypeIO_WriteString (exfile, "SkyAxis");
            TypeIO_WriteString (exfile, s);

            sprintf (s, "%f", SkyRotationSpeed);
            TypeIO_WriteString (exfile, "SkyRotation");
            TypeIO_WriteString (exfile, s);

            TypeIO_WriteString (exfile, "SkyDrawScale");
            sprintf (s, "%f", SkyTextureScale);
            TypeIO_WriteString (exfile, s);
        }

        for (iFace = 0; iFace < 6; ++iFace)
        {
            SkyFaceTexture *pFace;

            pFace = &SkyFaces[iFace];
            if (pFace->Apply && (pFace->TextureName != NULL) && (*pFace->TextureName != '\0'))
            {
                TypeIO_WriteString (exfile, SkyFaceNames[iFace]);
                TypeIO_WriteString (exfile, pFace->TextureName);
            }
        }
    }

    // write the models
    ModelList_WriteToMap (ModelInfo->Models, exfile, BList, CompileParams->SuppressHidden, CompileParams->VisDetailBrushes);

    // and the entities
    {
        fdocEntityToMapData etmData;

        etmData.f = exfile;
        etmData.Models = ModelInfo->Models;
        etmData.Entities = Level_GetEntities (App->CLSB_Doc->pLevel);
        etmData.pDoc	=this;

        Level_EnumEntities (App->CLSB_Doc->pLevel, &etmData, ::fdocEntityToMap);
    }
        
    EntityTable_WriteTypesToMap (Level_GetEntityDefs (App->CLSB_Doc->pLevel), exfile);
    fclose(exfile);

// changed QD Actors
    for(i=0;i < Entities->GetSize();i++)
    {
        Brush *pBrush = (*Entities)[i].GetActorBrush();

        if(pBrush!=NULL)
            Level_AppendBrush(App->CLSB_Doc->pLevel, pBrush);
    }
// end change

    return GE_TRUE;
}


void CFusionDoc::OnCompile() 
{
    App->Say("Deleted");
}

void CFusionDoc::CompileDone (CompilerErrorEnum CompileRslt)
{
    static const char SuccessMessage[] = "Compile completed successfully.";
    static const char ErrorMessage[] = "Error: Unable to compile.";
    static const char PreviewMessage[] = "Run preview?";
    static const char CancelMessage[] = "Compile cancelled by user.";
    CompileParamsType *CompileParams = Level_GetCompileParams (App->CLSB_Doc->pLevel);

    switch (CompileRslt)
    {
        case COMPILER_ERROR_NONE :
        {
            if (CompileParams->RunPreview)
            {
                char BigMessage[sizeof (SuccessMessage) + sizeof (PreviewMessage)];
                sprintf (BigMessage, "%s\r%s", SuccessMessage, PreviewMessage);
                if (AfxMessageBox (BigMessage, MB_YESNO + MB_ICONQUESTION) == IDYES)
                {
                    char BspFilename[_MAX_PATH];
                    char MotionFilename[_MAX_PATH];

                    FilePath_SetExt (CompileParams->Filename, ".bsp", BspFilename);
                    FilePath_SetExt (CompileParams->Filename, ".mot", MotionFilename);

                    Compiler_RunPreview (BspFilename, MotionFilename, Prefs_GetPreviewPath (GetPrefs ()));
                }
            }
            else
            {
                AfxMessageBox (SuccessMessage);
            }
            break;
        }
        case COMPILER_ERROR_USERCANCEL :
            AfxMessageBox (CancelMessage);
            break;
        default :
            AfxMessageBox (ErrorMessage, MB_OK + MB_ICONERROR);
            break;
    }
}

struct ScaleEntityInfo
{
    const EntityTable *pEntityDefs;
    float ScaleValue;
};

static geBoolean fdocScaleEntityCallback (CEntity &Ent, void *lParam)
{
    ScaleEntityInfo *pInfo = (ScaleEntityInfo *)lParam;

    Ent.Scale (pInfo->ScaleValue, pInfo->pEntityDefs);
    return GE_TRUE;
}

//typedef struct
//{
//    int ModelId;
//    BOOL Select;
//    CFusionDoc *pDoc;
//} fdocBrushSelectData;
//
//static geBoolean fdocSelectBrushCallback (Brush *pBrush, void *lParam)
//{
//    fdocBrushSelectData *pData;
//
//    pData = (fdocBrushSelectData *)lParam;
//    if (Brush_GetModelId (pBrush) == pData->ModelId)
//    {
//        if (pData->Select)
//        {
//            SelBrushList_Add (App->CLSB_Doc->pSelBrushes, pBrush);
//        }
//        else
//        {
//            SelBrushList_Remove (App->CLSB_Doc->pSelBrushes, pBrush);
//        }
//    }
//    return GE_TRUE;
//}


/******************************************************
     BRUSH GROUP SUPPORT
*******************************************************/
BOOL CFusionDoc::MakeNewBrushGroup
    (
        CWnd * pParent
    )
// create a new brush group and add all currently-selected
// brushes and entities to the new group.
{
    CString	szName ;
    CString	szDefault ;
    int		NewGroupId = 0 ;
    int		ModalResult ;
    GroupListType *Groups = Level_GetGroups (App->CLSB_Doc->pLevel);

    szDefault.LoadString( IDS_NEWGROUP ) ;
    CKeyEditDlg * GNameDlg = new CKeyEditDlg( pParent, szDefault, &szName ) ;

    ModalResult = GNameDlg->DoModal() ;
    delete GNameDlg ;

    if( ModalResult == IDOK )
    {
        SetModifiedFlag();

        szName.TrimLeft() ;
        szName.TrimRight() ;
        if( szName.IsEmpty() == FALSE )
        {
            NewGroupId = Group_AddToList( Groups );
            if( NewGroupId != 0 ) // You can't add the default group
            {
                Group_SetName( Groups, NewGroupId, szName ) ;
                App->CLSB_Doc->mCurrentGroup = NewGroupId;
                AddSelToGroup() ;
            }//Good new Group ID
            else
            {
                AfxMessageBox( IDS_CREATEGROUPFAILED, MB_OK + MB_ICONERROR ) ;
            }
        }//Not empty name
    }// OK return from name dialog

    return NewGroupId ; // 0 for failed or new non-default group number

}/* CFusionDoc::MakeNewBrushGroup */

int CFusionDoc::FillBrushGroupCombo 
    (
      CComboBox &cb
    )
{// Fill brush group combo box with group names and IDs
    int CurSel = LB_ERR;
    GroupList_FillCombobox( Level_GetGroups (App->CLSB_Doc->pLevel), &cb, App->CLSB_Doc->mCurrentGroup ) ;
    return CurSel;
}

typedef struct
{
    GroupListType *Groups;
    int CurrentGroup;
} fdocAddEntityData;
geBoolean fdocAddEntityToGroupCallback (CEntity &Ent, void *lParam)
{
    if (Ent.IsSelected ())
    {
        fdocAddEntityData *pData;

        pData = (fdocAddEntityData *)lParam;
        Group_AddEntity (pData->Groups, pData->CurrentGroup, &Ent);
    }
    return GE_TRUE;
}


void CFusionDoc::AddSelToGroup
    (
      void
    )
// add selected brushes/entities to current group, no UI
{
    fdocAddEntityData entData;
    int NumSelBrushes = SelBrushList_GetSize (App->CLSB_Doc->pSelBrushes);

    entData.Groups = Level_GetGroups (App->CLSB_Doc->pLevel);
    entData.CurrentGroup = App->CLSB_Doc->mCurrentGroup;

    // tag all selected brushes with this group id...
    for (int i = 0; i < NumSelBrushes; i++)
    {
        Brush *pBrush;

        pBrush = SelBrushList_GetBrush (App->CLSB_Doc->pSelBrushes, i);
// changed QD Actors
        if(strstr(App->CL_Brush->Brush_GetName(pBrush),".act")!=NULL)
            continue;
// end change
        Group_AddBrush (entData.Groups, App->CLSB_Doc->mCurrentGroup, pBrush);
    }
    // tag all selected entities with this group id...
    Level_EnumEntities (App->CLSB_Doc->pLevel, &entData, ::fdocAddEntityToGroupCallback);

    SetModifiedFlag();
}

static geBoolean fdocRemoveEntityFromGroupCallback (CEntity &Ent, void *lParam)
{
    fdocAddEntityData *pData;

    pData = (fdocAddEntityData *)lParam;
    if (Ent.IsSelected () && (Ent.GetGroupId () == pData->CurrentGroup))
    {
        Group_RemoveEntity (pData->Groups, pData->CurrentGroup, &Ent);
    }
    return GE_TRUE;
}

void CFusionDoc::RemovesSelFromGroup
    (
      void
    )
// removed selected brushes/entities from current group, do no UI
{
//	Brush	*	b;
    SetModifiedFlag();

    fdocAddEntityData entData;
    int NumSelBrushes = SelBrushList_GetSize (App->CLSB_Doc->pSelBrushes);

    entData.Groups = Level_GetGroups (App->CLSB_Doc->pLevel);
    entData.CurrentGroup = App->CLSB_Doc->mCurrentGroup;

    for(int i = 0; i < NumSelBrushes; i++)
    {
        Brush *pBrush;

        pBrush = SelBrushList_GetBrush (App->CLSB_Doc->pSelBrushes, i);
        if( Brush_GetGroupId(pBrush) == App->CLSB_Doc->mCurrentGroup )
        {
            Group_RemoveBrush( entData.Groups, App->CLSB_Doc->mCurrentGroup, pBrush );
        }
    }

    Level_EnumEntities (App->CLSB_Doc->pLevel, &entData, ::fdocRemoveEntityFromGroupCallback);
}


BOOL CFusionDoc::OneBrushSelectedOnly(void)
{
    return ((App->CLSB_Doc->mModeTool==ID_TOOLS_TEMPLATE) ||
            ((SelBrushList_GetSize (App->CLSB_Doc->pSelBrushes)==1) && (App->CLSB_Doc->NumSelEntities == 0) &&
             (SelFaceList_GetSize (App->CLSB_Doc->pSelFaces) == 0)));
}

void CFusionDoc::OnUpdateBrushSubtractfromworld(CCmdUI* pCmdUI) 
{
    BOOL EnableFlag;

    EnableFlag = ((App->CLSB_Doc->mModeTool==ID_GENERALSELECT) &&
                  (SelBrushList_GetSize (App->CLSB_Doc->pSelBrushes)==1) &&
                  (SelFaceList_GetSize (App->CLSB_Doc->pSelFaces) == 0) &&
                  (App->CLSB_Doc->NumSelEntities == 0));
    pCmdUI->Enable (EnableFlag);
}

void CFusionDoc::OnUpdateEntitiesEditor(CCmdUI* pCmdUI) 
{
    BOOL	bEnable ;

    bEnable = (	Level_GetEntities (App->CLSB_Doc->pLevel)->GetSize() ) ? TRUE : FALSE ;
    pCmdUI->Enable( bEnable ) ;
}

static geBoolean GetObjectName (char *Name, char *Path, CFusionDoc *pDoc)
{
    CKeyEditDlg *pEditDlg;
    CString ObjName;
    char ObjectsDir[MAX_PATH];
    char WorkPath[MAX_PATH];
    int rslt;

    strcpy (ObjectsDir, Prefs_GetObjectsDir (pDoc->GetPrefs ()));

    do
    {
        rslt = IDYES;
        pEditDlg = new CKeyEditDlg (AfxGetMainWnd (), "Object Name", &ObjName);
        if (pEditDlg->DoModal () != IDOK)
        {
            return GE_FALSE;
        }
        // see if an object of this name already exists
        ::FilePath_AppendName (ObjectsDir, ObjName, WorkPath);
        ::FilePath_SetExt (WorkPath, ".3dt", WorkPath);
        if (_access (WorkPath, 0) == 0)
        {
            static const char Prompt[] =
                "An object of that name already exists in the library.\r"
                "Do you want to replace it?";

            rslt = AfxMessageBox (Prompt, MB_ICONQUESTION + MB_YESNOCANCEL + MB_DEFBUTTON2);
        }
    } while (rslt == IDNO);

    if (rslt == IDYES)
    {
        strcpy (Path, WorkPath);
        ::FilePath_GetName (Path, Name);
        return GE_TRUE;
    }
    else
    {
        return GE_FALSE;
    }
}	

typedef struct
{
    Level *NewLevel;
    Level *OldLevel;
} AddPremadeEnumData;

static void fdocAddReferencedGroup (AddPremadeEnumData *pData, int GroupId)
{

    if (Level_GetGroup (pData->NewLevel, GroupId) == NULL)
    {
        // group doesn't exist in the new level, so add it
        Group *OldGroup, *NewGroup;

        OldGroup = Level_GetGroup (pData->OldLevel, GroupId);
        NewGroup = Group_Clone (OldGroup);
        Level_AddGroup (pData->NewLevel, NewGroup);
    }
}

static void fdocAddReferencedModel (AddPremadeEnumData *pData, int ModelId)
{
    if ((ModelId != 0) && (Level_GetModel (pData->NewLevel, ModelId) == NULL))
    {
        Model *OldModel, *NewModel;

        OldModel = Level_GetModel (pData->OldLevel, ModelId);
        NewModel = Model_Clone (OldModel);
        Level_AddModel (pData->NewLevel, NewModel);
    }
}

static geBoolean fdocAddSelectedEntities (CEntity &Ent, void *lParam)
{
    AddPremadeEnumData *pData;

    pData = (AddPremadeEnumData *)lParam;

    if (Ent.IsSelected ())
    {
        Level_AddEntity (pData->NewLevel, Ent);
        ::fdocAddReferencedGroup (pData, Ent.GetGroupId ());
    }
    return GE_TRUE;
}

void CFusionDoc::OnNewLibObject() 
{
    // save currently-selected stuff to named lib object.
    Level *NewLevel;
    char NewObjectName[MAX_PATH];
    char NewObjectFullPath[MAX_PATH];
    int i;
    AddPremadeEnumData EnumData;

    if (!::GetObjectName (NewObjectName, NewObjectFullPath, this))
    {
        return;
    }

// changed QD Actors
    NewLevel = Level_Create (Level_GetWadPath (App->CLSB_Doc->pLevel), Level_GetHeadersDirectory (App->CLSB_Doc->pLevel),
        Level_GetActorsDirectory (App->CLSB_Doc->pLevel), Level_GetPawnIniPath (App->CLSB_Doc->pLevel));
// end change
    if (NewLevel == NULL)
    {
        AfxMessageBox ("Error: Unable to create object.", MB_OK + MB_ICONERROR);
        return;
    }

    EnumData.NewLevel = NewLevel;
    EnumData.OldLevel = App->CLSB_Doc->pLevel;

    int NumSelBrushes = SelBrushList_GetSize (App->CLSB_Doc->pSelBrushes);
    // add all selected brushes and entities to the new level
    for (i = 0; i < NumSelBrushes; ++i)
    {
        Brush *NewBrush;
        Brush *OldBrush;

        OldBrush = SelBrushList_GetBrush (App->CLSB_Doc->pSelBrushes, i);
// changed QD Actors
        if(strstr(App->CL_Brush->Brush_GetName(OldBrush),".act")!=NULL)
            continue;
// end change
        NewBrush = Brush_Clone (OldBrush);
        Level_AppendBrush (NewLevel, NewBrush);

        // add any group or model that's referenced
        ::fdocAddReferencedModel (&EnumData, Brush_GetModelId (NewBrush));
        ::fdocAddReferencedGroup (&EnumData, Brush_GetGroupId (NewBrush));
    }

    Level_EnumEntities (App->CLSB_Doc->pLevel, &EnumData, ::fdocAddSelectedEntities);

    // SelectedGeoCenter contains center.  We're going to translate
    // the center to the origin.  That means that every brush and
    // entity will be moved so that the SelectedGeoCenter of the premade
    // object will be the origin.
    {
        geVec3d VecXlate;

        geVec3d_Scale (&App->CLSB_Doc->SelectedGeoCenter, -1.0f, &VecXlate);
        Level_TranslateAll (NewLevel, &VecXlate);
    }

    // ok, everything's added.  Write it to the file.
    if (!Level_WriteToFile (NewLevel, NewObjectFullPath))
    {
        AfxMessageBox ("Error: Unable to write object to file.", MB_OK + MB_ICONERROR);
    }
    else
    {
        // add level name to objects list...
        //mpMainFrame->m_wndTabControls->m_pBrushEntityDialog->SetupObjectListCombo ();
    }

    Level_Destroy (&NewLevel);
}

typedef struct
{
    CFusionDoc *pDoc;
    Level *NewLevel;
} fdocAddPremadeData;

static geBoolean fdocAddPremadeEntity (CEntity &Ent, void *lParam)
{
    fdocAddPremadeData *pData;
    CEntityArray *Entities;
    CEntity *NewEnt;
    int Index;

    if (!(Ent.IsCamera()))
    {
    pData = (fdocAddPremadeData *)lParam;

    Index = Level_AddEntity (App->CLSB_Doc->pLevel, Ent);
    Entities = Level_GetEntities (App->CLSB_Doc->pLevel);
    NewEnt = &((*Entities)[Index]);

    pData->pDoc->SelectEntity (NewEnt);
    }

    return GE_TRUE;
}

// -------------------------------------------------------------------------------
// places the specified object down into the level at the specified location
// TODO: later want to make it so that newly added brushes/entities are all placed
// in a single group and selected so the user can immediately begin to move
// and adjust the object within the level		
geBoolean CFusionDoc::PlaceObject( const char *ObjectName, const geVec3d *location )
{
    char WorkPath[MAX_PATH];

    ::FilePath_AppendName (Prefs_GetObjectsDir (GetPrefs ()), ObjectName, WorkPath);
    ::FilePath_SetExt (WorkPath, ".3dt", WorkPath);

    SetModifiedFlag();

    return ImportFile (WorkPath, location);
}

geBoolean CFusionDoc::ImportFile (const char *PathName, const geVec3d *location) // hgterry ImportFile
{
    App->CLSB_File_WE->ImportFile(PathName,location);

    App->CL_World->Reset_Editor();
    App->Say("Imported",App->CL_World->mCurrent_3DT_File);

    return GE_TRUE;
}


// -----------------------------------------------------------------------------
// insures all of the Dib ID's in the brush are correct
// I would like to have put this in the brush.cpp module,  but fixing up the dib ID's requires
// a function here in the doc and I wanted to avoid coupling brush.cpp to 
// fusiondoc.cpp
// returns 1 on success,  0 on failure
geBoolean CFusionDoc::FixUpBrushDibIDs(Brush *b)
{
    ASSERT(b);
    geBoolean NoErrors;

    NoErrors = GE_TRUE;
    // flags failure to find a particular texture

    // loop over all the faces in the brush
    for (int i = 0; i < Brush_GetNumFaces(b); i++ )
    {
        Face *pFace;
        const char *pName;
        Ogre::uint16 DibId;

        pFace = Brush_GetFace (b, i);
        pName = Face_GetTextureName (pFace);
        DibId = Level_GetDibId (App->CLSB_Doc->pLevel, pName);
        if (DibId == 0xffff)
        {
            DibId = 1;
            NoErrors = GE_FALSE;
        }
        Face_SetTextureDibId (pFace, DibId);
        if (NoErrors)
        {
            const WadFileEntry * const pbmp = Level_GetWadBitmap (App->CLSB_Doc->pLevel, pName);

            Face_SetTextureSize (pFace, pbmp->Width, pbmp->Height);
        }
    }

    return NoErrors;
}

#pragma warning (disable:4100)
void CFusionDoc::SnapScaleNearest(int sides, int inidx, ViewVars *v)
{
    geFloat	bsnap;

    SetModifiedFlag();

    App->CLSB_Doc->mLastOp		=BRUSH_SCALE;

    bsnap = 1.0f ;
    if (Level_UseGrid (App->CLSB_Doc->pLevel))
    {
        bsnap = Level_GetGridSnapSize (App->CLSB_Doc->pLevel);
    }

    if(App->CLSB_Doc->mModeTool == ID_TOOLS_TEMPLATE)
    {
        Brush_SnapScaleNearest(App->CLSB_Doc->CurBrush, bsnap, sides, inidx, &App->CLSB_Doc->FinalScale, &App->CLSB_Doc->ScaleNum);
    }
    else
    {
        int i;
        int NumBrushes = SelBrushList_GetSize (App->CLSB_Doc->pTempSelBrushes);

        for (i = 0; i < NumBrushes; ++i)
        {
            Brush *pBrush = SelBrushList_GetBrush (App->CLSB_Doc->pTempSelBrushes, i);
            Brush_SnapScaleNearest(pBrush, bsnap, sides, inidx, &App->CLSB_Doc->FinalScale, &App->CLSB_Doc->ScaleNum);
        }
    }
}
#pragma warning (default:4100)

typedef struct
{
    GroupListType *Groups;
    geBoolean AllGood;
    const EntityTable *pEntityTable;
} fdocEntityValidateData;

static geBoolean fdocValidateEntity (CEntity &Ent, void *lParam)
{
    fdocEntityValidateData *pData;
    int			nGroupId ;
    CString		cstr ;

    pData = (fdocEntityValidateData *)lParam;

    // Validate the entity type (Class)	
    cstr = Ent.GetClassname() ;
    if (!EntityTable_IsValidEntityType (pData->pEntityTable, cstr))
    {
        cstr = Ent.GetName() ;
        pData->AllGood = GE_FALSE ;
    }

    nGroupId = Ent.GetGroupId() ;
    if (nGroupId != 0)
    {
        if (GroupList_IsValidId (pData->Groups, nGroupId) == FALSE)
        {
            cstr = Ent.GetName() ;
            Ent.SetGroupId( 0 ) ;
            pData->AllGood = GE_FALSE;
        }
    }

    return GE_TRUE;
}

geBoolean CFusionDoc::ValidateEntities( void )
{
    fdocEntityValidateData evData;

    evData.Groups = Level_GetGroups (App->CLSB_Doc->pLevel);
    evData.AllGood = GE_TRUE;
    evData.pEntityTable = Level_GetEntityDefs (App->CLSB_Doc->pLevel);

    Level_EnumEntities (App->CLSB_Doc->pLevel, &evData, ::fdocValidateEntity);

    return evData.AllGood;
}

typedef struct
{
    GroupListType *Groups;
    geBoolean AllGood;
} fdocBrushValidateData;

geBoolean fdocValidateBrush (Brush *pBrush, void *lParam)
{
    fdocBrushValidateData *pData;
    int nGroupId;

    pData = (fdocBrushValidateData *)lParam;
    nGroupId = Brush_GetGroupId( pBrush ) ;
    if( nGroupId != 0 )
    {
        if( GroupList_IsValidId( pData->Groups, nGroupId ) == FALSE )
        {
            char const *pName;

            pName = App->CL_Brush->Brush_GetName (pBrush);
            Brush_SetGroupId( pBrush, 0 ) ;
            pData->AllGood = GE_FALSE ;
        }
    }
    return GE_TRUE;
}

geBoolean CFusionDoc::ValidateBrushes( void )
{
    fdocBrushValidateData bvData;
    
    bvData.Groups = Level_GetGroups (App->CLSB_Doc->pLevel);
    bvData.AllGood = GE_TRUE;
        
    Level_EnumBrushes (App->CLSB_Doc->pLevel, &bvData, ::fdocValidateBrush);

    return bvData.AllGood ;
}


void CFusionDoc::SelectTab( int nTabIndex )
{
    if(App->CLSB_Doc->mpMainFrame )
    {
        App->CLSB_Doc->mpMainFrame->SelectTab( nTabIndex ) ;
    }
}/* CFusionDoc::SelectTab */

/* EOF: FusionDoc.cpp */

void CFusionDoc::OnFileOpen() // hgtterry On File Open from menu
{
    bool test = App->CLSB_File_WE->Start_Load("",1);
    if (test == 0)
    {
        return;
    }
}

void CFusionDoc::OnFileImportActor()
{
    App->CLSB_Loader->Load_ActorWorld();
}

void CFusionDoc::OnFileImport() 
{
    static const char FDTitle[] = "Import";
    CFileDialog dlg(TRUE, "3dt", NULL, (OFN_HIDEREADONLY	| OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST),
                                    "World Files (*.3dt)|*.3dt|Map Files (*.map)|*.map|BSP Leak Files (*.pnt)|*.pnt|All Files (*.*)|*.*||");

    dlg.m_ofn.lpstrTitle = FDTitle;	
    if (dlg.DoModal () == IDOK)
    {
        switch(dlg.m_ofn.nFilterIndex)
        {
        case 1 :
            char Name[MAX_PATH];
            geVec3d loc;

            geVec3d_Clear (&loc);
            ::FilePath_SetExt (dlg.GetPathName (), ".3dt", Name);
            ImportFile (Name, &loc);
            break;
        case 2 :
            LoadMapFile(dlg.GetPathName());
            break;
        case 3 :
            bLeakLoaded	=LoadLeakFile(dlg.GetPathName());
        }

        SetModifiedFlag();

        App->CLSB_Doc->UpdateAllViews(UAV_ALLVIEWS | REBUILD_QUICK, FALSE);

//		mpMainFrame->m_wndTabControls->GrpTab->UpdateAfterAddBrush();

        if (App->CL_TabsGroups_Dlg->Groups_Dlg_Created == 1)
        {
            App->CL_TabsGroups_Dlg->Fill_ListBox();
        }

        if (App->CL_TextureDialog->f_TextureDlg_Active == 1)
        {
            App->CL_TextureDialog->Fill_ListBox();
        }

    }
}

geBoolean	CFusionDoc::LoadLeakFile(const char *Filename)
{
    SetCursor(AfxGetApp()->LoadStandardCursor(IDC_WAIT));

    CFile	Infile;
    int		sig;
    int		PointsToRead;

    if(!Infile.Open(Filename, CFile::modeRead))
    {
        SetCursor(AfxGetApp()->LoadStandardCursor(IDC_ARROW));
        AfxMessageBox("Error: Unable to read the leak file!", MB_OK + MB_ICONERROR);
        return FALSE;
    }

    Infile.Read(&sig, sizeof(int));

    if(sig!=0x4b41454c)
    {
        SetCursor(AfxGetApp()->LoadStandardCursor(IDC_ARROW));
        AfxMessageBox("File is not a leak file!", MB_OK + MB_ICONEXCLAMATION);
        return FALSE;
    }

    Infile.Read(&PointsToRead, sizeof(int));

//	ConPrintf("Loaded leak file %s with %d Points...\n", Filename, PointsToRead);

    NumLeakPoints = (PointsToRead > 1) ? PointsToRead : 2;
    App->CLSB_Doc->LeakPoints	=(geVec3d *)geRam_Allocate(sizeof(geVec3d)*NumLeakPoints);

    if (!App->CLSB_Doc->LeakPoints)
    {
        SetCursor(AfxGetApp()->LoadStandardCursor(IDC_ARROW));
        return FALSE;
    }

    Infile.Read(App->CLSB_Doc->LeakPoints, sizeof(geVec3d)*PointsToRead);
    if (PointsToRead == 1)
    {
        geVec3d_Clear (&App->CLSB_Doc->LeakPoints[1]);
    }

    SetShowLeakFinder(GE_TRUE);

    SetCursor(AfxGetApp()->LoadStandardCursor(IDC_ARROW));

    return TRUE;
}
// Quake 2 flag sets for importing
enum	Q2ContentsFlags
{
    CONTENTS_SOLID			=0x1,
    CONTENTS_WINDOW			=0x2,
    CONTENTS_EMPTY			=0x4,
    CONTENTS_SUBTRACT		=0x8,
    CONTENTS_WAVY			=0x10,
    CONTENTS_DETAIL			=0x20,
    CONTENTS_CLIP			=0x40,
    CONTENTS_HINT			=0x80,
    CONTENTS_AREA			=0x100,
    CONTENTS_FLOCKING		=0x200,
    CONTENTS_SHEET			=0x400,
    CONTENTS_AIR			=0x800,
    CONTENTS_WATER			=0x1000,
    CONTENTS_LAVA			=0x2000,
    CONTENTS_TOXICGAS		=0x4000,
    CONTENTS_ZEROG			=0x8000,
    CONTENTS_FROZEN			=0x10000,
    CONTENTS_SLUDGE			=0x20000,
    CONTENTS_SLOWMOTION		=0x40000,
    CONTENTS_FASTMOTION		=0x80000,
    CONTENTS_LADDER			=0x100000,
    CONTENTS_IMPENETRABLE	=0x200000,
    CONTENTS_UNCLIMBABLE	=0x400000,
};

enum	Q2SurfaceFlags
{
    SURF_LIGHT		=0x8,		// value will hold the light strength
    SURF_SKY		=0x100,		// don't draw, but add to skybox
    SURF_TRANS33	=0x10,
    SURF_TRANS66	=0x20,
    SURF_TRANS		=0x40,
    SURF_MIRROR		=0x80,
    SURF_FULLBRIGHT	=0x1,
    SURF_GOURAUD	=0x2,
    SURF_FLAT		=0x4,
    SURF_TEXTURELOCK =0x200,
    SURF_NODRAW		=0x400,
};

static geBoolean fdocCheckAddFace (FaceList **ppList, Face *f)
{
    if (FaceList_GetNumFaces (*ppList) >= FaceList_GetFaceLimit (*ppList))
    {
        if (!FaceList_Grow (ppList))
        {
            return GE_FALSE;
        }
    }
    FaceList_AddFace (*ppList, f);
    return GE_TRUE;
}


geBoolean	CFusionDoc::LoadMapFile(const char *FileName)
{
    SetModifiedFlag();

    CWaitCursor w;

    FaceList	*fl, *mfl;
    Face		*f;
    Brush		*b;
    FILE		*mf;

    geVec3d		FaceVerts[3];
    int			i, k, bc, sx, sy, contents, surfflags, value;// changed QD
    geFloat		scx, scy, rot;// changed QD
    char		*sp = NULL;
    char		szTex[_MAX_PATH];
    Ogre::uint16		dibid;

//MRB BEGIN
    geBoolean IsHintBrush;
//MRB END

    assert (FileName != NULL);

    mf	=fopen(FileName, "r");
    mfl	=FaceList_Create(64);

    if(!mf)
    {
        SetCursor(AfxGetApp()->LoadStandardCursor(IDC_ARROW));
        AfxMessageBox (IDS_CANT_OPEN_FILE, MB_OK + MB_ICONERROR);
        return GE_FALSE;
    }
    //get open brace
    for(bc=fgetc(mf);bc!=EOF && bc!='{';bc=fgetc(mf));
    if(bc=='{')
    {
        for(;;)
        {
            //get open brace
            for(bc=fgetc(mf);bc!=EOF && bc!='{' && bc!='}';bc=fgetc(mf));
            if(bc=='{')
            {
                surfflags	=value=0;
                contents	=CONTENTS_SOLID;	//default
//MRB BEGIN
                IsHintBrush = GE_FALSE;
//MRB END
                for(k=0;;)
                {

                    for(i=0;i<3;i++)
                    {
                        //get ( or }
                        for(bc=fgetc(mf);bc!=EOF && bc!='}' && bc!='(';bc=fgetc(mf));
                        if(bc=='(')
                        {
                            fscanf(mf, "%f%f%f", &FaceVerts[i].X, &FaceVerts[i].Z, &FaceVerts[i].Y);
                            FaceVerts[i].Z	=-FaceVerts[i].Z;
                        }
                        else
                        {
                            break;
                        }
                    }
                    if(i==3)
                    {
                        //get )
                        for(bc=fgetc(mf);bc!=EOF && bc!=')';bc=fgetc(mf));
                        fscanf(mf, "%s %i %i %f %f %f", szTex, &sx, &sy, &rot, &scx, &scy);// changed QD
                        dibid	=Level_GetDibId(App->CLSB_Doc->pLevel, szTex);
                        if(dibid == 0xffff)
                        {
                            //try stripping /
                            sp	=strrchr(szTex, '/');
                            if(sp)
                            {
                                sp++;
                                dibid	=Level_GetDibId(App->CLSB_Doc->pLevel, sp);
                            }
                        }
                        if(!sp)
                        {
                            sp	=szTex;
                        }
                        f	=Face_Create(3, FaceVerts, dibid);
                        for(;*sp=='#' || *sp=='*' || *sp=='+';sp++);	//strip illegal chars
                        if(f)
                        {
                            Face_SetTextureName(f, sp);
                            Face_SetTextureScale(f, scx, scy);
                            Face_SetTextureShift(f, sx, sy);
                            Face_SetTextureRotate(f, rot);// changed QD
                        }
                        //look for flags
                        for(bc=fgetc(mf);bc!=EOF && bc <=32 && bc && bc!='\n';bc=fgetc(mf));
                        if(bc!='\n' && bc)
                        {
                            ungetc(bc, mf);
                            fscanf(mf, "%i %i %i", &contents, &surfflags, &value);
                            if(f)
                            {
                                Face_SetLight(f, (surfflags	&	SURF_LIGHT));
                                Face_SetSky(f, (surfflags	&	SURF_SKY));
                                Face_SetLightIntensity(f, value);

//MRB BEGIN
                                Face_SetMirror(f, (surfflags	&	SURF_MIRROR));
                                Face_SetFullBright(f, (surfflags	&	SURF_FULLBRIGHT));
                                Face_SetGouraud(f, (surfflags	&	SURF_GOURAUD));
                                Face_SetFlat(f, (surfflags	&	SURF_FLAT));
                                Face_SetTextureLock(f, (surfflags	&	SURF_TEXTURELOCK));
                                Face_SetVisible(f, (!(surfflags & SURF_NODRAW)));
                                
                                geFloat Translucency = 255;
                                if (surfflags	&	SURF_TRANS33)
                                    Translucency = 85;
                                if (surfflags	&	SURF_TRANS66)
                                    Translucency = 170;
                                if (surfflags	&	SURF_TRANS)
                                    Translucency = 0;
                                Face_SetTranslucency(f, Translucency);

                                if ((Translucency < 255) && (!(surfflags & SURF_MIRROR)))
                                {
                                    Face_SetTransparent(f, GE_TRUE);
                                }

//MRB END

                            }
                        }
                        if(f)
                        {
                            if (!fdocCheckAddFace (&mfl, f))
                            {
                                // this is pretty ugly.
                                // If we can't add the face, then set num faces to 0 and exit.
                                k = 0;
                                break;
                            }
//							FaceList_AddFace(mfl, f);
                            k++;
                        }
                    }
                    else
                    {
                        break;
                    }
                }
                if(k > 3)
                {
                    fl	=FaceList_Create(k);
                    for(i=0;i<k;i++)
                    {
                        FaceList_AddFace(fl, Face_Clone(FaceList_GetFace(mfl, i)));
                    }
                    FaceList_Destroy(&mfl);
                    mfl	=FaceList_Create(64);
                    b	=Brush_Create(BRUSH_LEAF, fl, NULL);
                    Brush_SealFaces(&b);
                    if(b)
                    {
                        Level_AppendBrush	(App->CLSB_Doc->pLevel, b);
                        Brush_SetSolid		(b, (contents	&	CONTENTS_SOLID));
                        Brush_SetEmpty		(b, (contents	&	CONTENTS_EMPTY));
                        Brush_SetWindow		(b, (contents	&	CONTENTS_WINDOW));
                        Brush_SetWavy		(b, (contents	&	CONTENTS_WAVY));
                        Brush_SetClip		(b, (contents	&	CONTENTS_CLIP));
                        Brush_SetDetail		(b, (contents	&	CONTENTS_DETAIL));
//						Brush_SetTranslucent(b, (contents	&	CONTENTS_TRANSLUCENT));
//MRB BEGIN
                        Brush_SetSubtract		(b, (contents	&	CONTENTS_SUBTRACT));
                        Brush_SetArea		(b, (contents	&	CONTENTS_AREA));
                        Brush_SetFlocking		(b, (contents	&	CONTENTS_FLOCKING));
                        Brush_SetSheet		(b, (contents	&	CONTENTS_SHEET));
                        IsHintBrush = IsHintBrush || (contents & CONTENTS_HINT);
                        Brush_SetHint		(b, (IsHintBrush));
                        Brush_SetUserFlags (b, contents);
                        if(!((contents & CONTENTS_EMPTY) || (contents	& CONTENTS_WINDOW) || (contents	& CONTENTS_CLIP) ||
                            (contents & CONTENTS_HINT) || (contents	& CONTENTS_SUBTRACT)))
                            Brush_SetSolid(b, GE_TRUE);
//MRB END
                    }
                }
            }
            else if(bc=='}')
            {
                break;
            }
        }
    }
    char	Key[255], Value[255];
    //get open brace
    for(bc=fgetc(mf);bc!=EOF && bc!='{';bc=fgetc(mf));
    if(bc=='{')
    {
        for(;;)
        {
            CEntity	NewEnt;
            for(;;)
            {
                for(bc=fgetc(mf);bc!=EOF && bc!='"' && bc!='}' && bc!='{';bc=fgetc(mf));
                if(bc=='"')
                {
                    for(i=0;;i++)
                    {
                        bc		=fgetc(mf);
                        if(bc!='"')
                        {
                            Key[i]	=(char)bc;	//hope theres no high nibble info
                        }
                        else
                        {
                            Key[i]	=(char)0;
                            break;
                        }
                    }
                    for(bc=fgetc(mf);bc!=EOF && bc!='"' && bc!='}';bc=fgetc(mf));
                    if(bc!='"')
                    {
                        break;
                    }
                    for(i=0;;i++)
                    {
                        bc		=fgetc(mf);
                        if(bc!='"')
                        {
                            Value[i]=(char)bc;
                        }
                        else
                        {
                            Value[i]=(char)0;
                            break;
                        }
                    }
//					ConPrintf("Key: %s : Value: %s\n", Key, Value);
                    if(!stricmp(Key, "_color"))
                    {
                        strcpy(Key, "color");
                        geVec3d	TempVec;
                        sscanf((char const *)Value, "%f %f %f", &TempVec.X, &TempVec.Y, &TempVec.Z);
                        sprintf(Value, "%d %d %d",
                            Units_Round(TempVec.X * 255.0f),
                            Units_Round(TempVec.Y * 255.0f),
                            Units_Round(TempVec.Z * 255.0f));					
                    }
                    else if(!strnicmp(Value, "info_player", 11))
                    {
                        strcpy(Value, "PlayerStart");
                    }
                    else if(!stricmp(Key, "origin"))
                    {
                        geVec3d	TempVec;
                        sscanf((char const *)Value, "%f %f %f", &TempVec.X, &TempVec.Z, &TempVec.Y);
                        TempVec.Z	=-TempVec.Z;
                        sprintf(Value, "%d %d %d", Units_Round(TempVec.X), Units_Round(TempVec.Y), Units_Round(TempVec.Z));					
                    }
                    NewEnt.SetKeyValue(Key, Value);
                }
                else if(bc=='{' && NewEnt.GetNumKeyValuePairs())	//brush models
                {
                    geXForm3d	XfmDelta;
                    for(;;)
                    {
                        if(bc=='{')
                        {
                            surfflags	=value=0;
                            contents	=CONTENTS_SOLID;	//default
//MRB BEGIN
                            IsHintBrush = GE_FALSE;
//MRB END
                            for(k=0;;)
                            {
                                for(i=0;i<3;i++)
                                {
                                    //get ( or }
                                    for(bc=fgetc(mf);bc!=EOF && bc!='}' && bc!='(';bc=fgetc(mf));
                                    if(bc=='(')
                                    {
                                        fscanf(mf, "%f%f%f", &FaceVerts[i].X, &FaceVerts[i].Z, &FaceVerts[i].Y);
                                        FaceVerts[i].Z	=-FaceVerts[i].Z;
                                    }
                                    else
                                    {
                                        break;
                                    }
                                }
                                if(i==3)
                                {
                                    //get )
                                    for(bc=fgetc(mf);bc!=EOF && bc!=')';bc=fgetc(mf));
                                    fscanf(mf, "%s %i %i %f %f %f", szTex, &sx, &sy, &rot, &scx, &scy);//changed QD
                                    dibid	=Level_GetDibId(App->CLSB_Doc->pLevel, szTex);
                                    if(dibid == 0xffff)
                                    {
                                        //try stripping /
                                        sp	=strrchr(szTex, '/');
                                        if(sp)
                                        {
                                            sp++;
                                            dibid	=Level_GetDibId(App->CLSB_Doc->pLevel, sp);
                                        }
                                    }
                                    if(!sp)
                                    {
                                        sp	=szTex;
                                    }
                                    f	=Face_Create(3, FaceVerts, dibid);
                                    for(;*sp=='#' || *sp=='*' || *sp=='+';sp++);	//strip illegal chars
                                    if (f)
                                    {
                                        Face_SetTextureName(f, sp);
                                        Face_SetTextureScale(f, scx, scy);
                                        Face_SetTextureShift(f, sx, sy);
                                        Face_SetTextureRotate(f, rot);// changed QD
                                    }

                                    //look for flags
                                    for(bc=fgetc(mf);bc!=EOF && bc <=32 && bc && bc!='\n';bc=fgetc(mf));
                                    if(bc!='\n' && bc)
                                    {
                                        ungetc(bc, mf);
                                        fscanf(mf, "%i %i %i", &contents, &surfflags, &value);
                                        if (f)
                                        {
                                            Face_SetLight(f, (surfflags	&	SURF_LIGHT));
                                            Face_SetSky(f, (surfflags	&	SURF_SKY));
                                            Face_SetLightIntensity(f, value);
//MRB BEGIN
                                            Face_SetMirror(f, (surfflags	&	SURF_MIRROR));
                                            Face_SetFullBright(f, (surfflags	&	SURF_FULLBRIGHT));
                                            Face_SetGouraud(f, (surfflags	&	SURF_GOURAUD));
                                            Face_SetFlat(f, (surfflags	&	SURF_FLAT));
                                            Face_SetTextureLock(f, (surfflags	&	SURF_TEXTURELOCK));
                                            Face_SetVisible(f, (!(surfflags & SURF_NODRAW)));
                                            
                                            geFloat Translucency = 255;
                                            if (surfflags	&	SURF_TRANS33)
                                                Translucency = 85;
                                            if (surfflags	&	SURF_TRANS66)
                                                Translucency = 170;
                                            if (surfflags	&	SURF_TRANS)
                                                Translucency = 0;
                                            Face_SetTranslucency(f, Translucency);

                                            if ((Translucency < 255) && (!(surfflags & SURF_MIRROR)))
                                            {
                                                Face_SetTransparent(f, GE_TRUE);
                                            }
//MRB END
                                        }
                                    }
                                    if (f)
                                    {
                                        if (!fdocCheckAddFace (&mfl, f))
                                        {
                                            k = 0;
                                            break;
                                        }
                                        k++;
                                    }
                                }
                                else
                                {
                                    break;
                                }
                            }
                            if(k > 3)
                            {
                                fl	=FaceList_Create(k);
                                for(i=0;i<k;i++)
                                {
                                    FaceList_AddFace(fl, Face_Clone(FaceList_GetFace(mfl, i)));
                                }
                                FaceList_Destroy(&mfl);
                                mfl	=FaceList_Create(64);
                                b	=Brush_Create(BRUSH_LEAF, fl, NULL);
                                Brush_SealFaces(&b);
                                Brush_SealFaces(&b);
                                if(b)
                                {
                                    Level_AppendBrush	(App->CLSB_Doc->pLevel, b);
                                    Brush_SetSolid		(b, (contents	&	CONTENTS_SOLID));
                                    Brush_SetWindow		(b, (contents	&	CONTENTS_WINDOW));
                                    Brush_SetWavy		(b, (contents	&	CONTENTS_WAVY));
                                    Brush_SetClip		(b, (contents	&	CONTENTS_CLIP));
                                    Brush_SetDetail		(b, (contents	&	CONTENTS_DETAIL));
                                    //						Brush_SetTranslucent(b, (contents	&	CONTENTS_TRANSLUCENT));
                                    //MRB BEGIN
                                    Brush_SetSubtract		(b, (contents	&	CONTENTS_SUBTRACT));
                                    Brush_SetArea		(b, (contents	&	CONTENTS_AREA));
                                    Brush_SetFlocking		(b, (contents	&	CONTENTS_FLOCKING));
                                    Brush_SetSheet		(b, (contents	&	CONTENTS_SHEET));
                                    IsHintBrush = IsHintBrush || (contents & CONTENTS_HINT);
                                    Brush_SetHint		(b, (IsHintBrush));
                                    Brush_SetUserFlags (b, contents);
                                    if(!((contents & CONTENTS_EMPTY) || (contents	& CONTENTS_WINDOW) || (contents	& CONTENTS_CLIP) ||
                                        (contents & CONTENTS_HINT) || (contents	& CONTENTS_SUBTRACT)))
                                        Brush_SetSolid(b, GE_TRUE);
                                    //MRB END
                                }
                                SelBrushList_Add (App->CLSB_Doc->pSelBrushes, b);
                            }
                        }
                        else if(bc=='}')
                        {
                            break;
                        }
                    }
                    //strcpy(Key, NewEnt.GetClassname());
                    i	=0;
                    sprintf(Key, "%s%d", NewEnt.GetClassname(), i++);

                    ModelInfo_Type *ModelInfo = Level_GetModelInfo (App->CLSB_Doc->pLevel);
                    while (ModelList_FindByName (ModelInfo->Models, Key) != NULL)
                    {
                        sprintf(Key, "%s%d", NewEnt.GetClassname(), i++);
                    }
                    // add the new model to the list.
                    // This will set the model id fields in the model's brushes
                    if (ModelList_Add (ModelInfo->Models, Key, App->CLSB_Doc->pSelBrushes))
                    {
                        Model *m;

                        // get current model and update its object-to-world transform
                        m = ModelList_FindByName (ModelInfo->Models, Key);
                        assert (m != NULL);
                        ModelInfo->CurrentModel	= Model_GetId (m);

//						UpdateModelsList ();
                        geXForm3d_SetIdentity (&XfmDelta);
                        // we add the first key (identity)
                        // (and don't allow it to be edited/deleted)
                        Model_AddKeyframe(m, 0.0f, &XfmDelta);
                    }
                    SelBrushList_RemoveAll (App->CLSB_Doc->pSelBrushes);
                }
                else if(bc==EOF || bc=='}')
                {
                    break;
                }
            }
            if(bc==EOF)
            {
                break;
            }
            else if(bc=='}')
            {
                NewEnt.SetGroupId ( 0 );
                NewEnt.UpdateOrigin (Level_GetEntityDefs (App->CLSB_Doc->pLevel));
                Level_AddEntity (App->CLSB_Doc->pLevel, NewEnt);
            }
        }
    }

    fclose(mf);
    if (mfl != NULL)
    {
        FaceList_Destroy (&mfl);
    }

    return	TRUE;
}

void CFusionDoc::OnViewShowClip() 
{
    bShowClipBrushes	=!(bShowClipBrushes);	
    App->CLSB_Doc->UpdateAllViews(UAV_ALL3DVIEWS, NULL);
}

void CFusionDoc::OnUpdateViewShowClip(CCmdUI* pCmdUI) 
{
    pCmdUI->SetCheck(bShowClipBrushes);
}

void CFusionDoc::OnViewShowDetail() 
{
    bShowDetailBrushes	=!(bShowDetailBrushes);	
    App->CLSB_Doc->UpdateAllViews(UAV_ALL3DVIEWS, NULL);
}

void CFusionDoc::OnUpdateViewShowDetail(CCmdUI* pCmdUI) 
{
    pCmdUI->SetCheck(bShowDetailBrushes);
}

void CFusionDoc::OnViewShowHint() 
{
    bShowHintBrushes	=!(bShowHintBrushes);	
    App->CLSB_Doc->UpdateAllViews(UAV_ALL3DVIEWS, NULL);
}

void CFusionDoc::OnUpdateViewShowHint(CCmdUI* pCmdUI) 
{
    pCmdUI->SetCheck(bShowHintBrushes);
}

/*
void CFusionDoc::OnToolsBrushAttributes() 
{
    if ((mModeTool == ID_GENERALSELECT) && (mAdjustMode == ADJUST_MODE_BRUSH))
    {
        if ((SelBrushList_GetSize (pSelBrushes) > 0) && 
            (mAdjustMode == ADJUST_MODE_BRUSH) && (mpBrushAttributes == NULL))
        if (!mpBrushAttributes)
        {
            mpBrushAttributes = new CBrushAttributesDialog (this);
        }
        SetModifiedFlag ();
    }	
}
*/

/*
void CFusionDoc::OnUpdateToolsBrushAttributes(CCmdUI* pCmdUI) 
{
    pCmdUI->Enable ((mModeTool == ID_GENERALSELECT) && 
                    (mAdjustMode == ADJUST_MODE_BRUSH) && 
                    (SelBrushList_GetSize (pSelBrushes) > 0));
}
*/

/*
void CFusionDoc::OnToolsFaceAttributes() 
{
//	if ((mModeTool == ID_GENERALSELECT) && (mAdjustMode == ADJUST_MODE_FACE))
    {
        FaceAttributesDialog ();
        SetModifiedFlag ();
    }	
    
}
*/

/*

void CFusionDoc::OnUpdateToolsFaceAttributes(CCmdUI* pCmdUI) 
{
    pCmdUI->Enable ((mModeTool == ID_GENERALSELECT) && 
                    (mAdjustMode == ADJUST_MODE_FACE) && 
                    (SelFaceList_GetSize (pSelFaces) > 0));
}
*/

void CFusionDoc::OnEntityVisibility() 
{
    SetModifiedFlag();

    EntityViewList *pListCopy;
    EntityViewList *pEntityView;

    pEntityView = Level_GetEntityVisibilityInfo (App->CLSB_Doc->pLevel);

    // copy existing...
    pListCopy = EntityViewList_Copy (pEntityView);
    
    if (pListCopy != NULL)
    {
        CEntityVisDlg Dlg;
        geBoolean Changed;

        Changed = GE_FALSE;

        // call dialog...
        if (Dlg.DoModal (pEntityView) == IDOK)
        {
            int i;

            // update changes
            for (i = 0; i < pEntityView->nEntries; ++i)
            {
                EntityViewEntry *pEntry;

                pEntry = &pEntityView->pEntries[i];
                if ((pEntry->IsVisible ^ pListCopy->pEntries[i].IsVisible) != 0)
                {
                    Changed = GE_TRUE;

                    Level_EnumEntities (App->CLSB_Doc->pLevel, pEntry, ::fdocSetEntityVisibility);
                }
            }
        }

        // get rid of copy
        EntityViewList_Destroy (&pListCopy);

        // redraw views if any changes made
        if (Changed)
        {
            App->CLSB_Doc->UpdateAllViews (UAV_ALL3DVIEWS, NULL);
        }
    }
}

void CFusionDoc::OnRebuildBsp() 
{
    SetModifiedFlag();

    Level_SetBspRebuild (App->CLSB_Doc->pLevel, !Level_RebuildBspAlways (App->CLSB_Doc->pLevel));

    if (Level_RebuildBspAlways (App->CLSB_Doc->pLevel))
    {
        RebuildTrees();
        App->CLSB_Doc->UpdateAllViews(UAV_ALL3DVIEWS, NULL);
    }
}

void CFusionDoc::OnUpdateRebuildBsp(CCmdUI* pCmdUI) 
{
    pCmdUI->SetCheck (Level_RebuildBspAlways (App->CLSB_Doc->pLevel));
}

const Prefs *CFusionDoc::GetPrefs (void)
{
    return ((CFusionApp *)AfxGetApp ())->GetPreferences ();
}

typedef geBoolean (*Brush_FaceCallback)(Face *pFace, void *lParam);

static geBoolean fdocUpdateFaceTextures (Face *pFace, void *lParam)
{
    CFusionDoc *pDoc = (CFusionDoc *)lParam;


    Face_SetTextureDibId (pFace, Level_GetDibId (App->CLSB_Doc->pLevel, Face_GetTextureName (pFace)));
// changed QD 12/03
    const WadFileEntry * const pbmp = Level_GetWadBitmap (App->CLSB_Doc->pLevel, Face_GetTextureName (pFace));
    if(pbmp)
        Face_SetTextureSize (pFace, pbmp->Width, pbmp->Height);
// end change
    return GE_TRUE;
}

static geBoolean fdocUpdateBrushFaceTextures (Brush *pBrush, void *pVoid)
{
    Brush_EnumFaces (pBrush, pVoid, ::fdocUpdateFaceTextures);
    return GE_TRUE;
}

void CFusionDoc::OnLeveloptions() 
{
    SetModifiedFlag();
    App->CL_Dialogs->Start_Properties();

    return;
    

    CLevelOptions  Dlg;

    Dlg.m_DrawScale = Level_GetDrawScale (App->CLSB_Doc->pLevel);
    Dlg.m_LightmapScale = Level_GetLightmapScale (App->CLSB_Doc->pLevel);
    Dlg.m_TextureLib = Level_GetWadPath (App->CLSB_Doc->pLevel);
    Dlg.m_HeadersDir = Level_GetHeadersDirectory (App->CLSB_Doc->pLevel);
// changed QD Actors
    Dlg.m_ActorsDir = Level_GetActorsDirectory (App->CLSB_Doc->pLevel);
    Dlg.m_PawnIni = Level_GetPawnIniPath (App->CLSB_Doc->pLevel);
    
// end change

    if (Dlg.DoModal () == IDOK)
    {
        Level_SetDrawScale (App->CLSB_Doc->pLevel, Dlg.m_DrawScale);
        Level_SetLightmapScale (App->CLSB_Doc->pLevel, Dlg.m_LightmapScale);
        if (Dlg.m_TxlChanged)
        {
            Level_SetWadPath (App->CLSB_Doc->pLevel, Dlg.m_TextureLib);
            UpdateAfterWadChange();
        }
        if (Dlg.m_HeadersChanged)
        {
            Level_LoadEntityDefs (App->CLSB_Doc->pLevel, Dlg.m_HeadersDir);
            if (ValidateEntities( ) == FALSE)
            {
                SelectTab( CONSOLE_TAB ) ;
                AfxMessageBox( IDS_ENTITY_WARNING, MB_OK + MB_ICONEXCLAMATION ) ;
            }
            //mpMainFrame->m_wndTabControls->UpdateTabs ();
        }
// changed QD Actors
        if (Dlg.m_ActorsChanged)
        {
            Level_SetActorsDir(App->CLSB_Doc->pLevel, Dlg.m_ActorsDir);
            UpdateEntityActors();
            App->CLSB_Doc->UpdateAllViews(UAV_ALL3DVIEWS | REBUILD_QUICK, NULL);
        }
        if (Dlg.m_PawnIniChanged)
        {
            Level_SetPawnIniPath (App->CLSB_Doc->pLevel, Dlg.m_PawnIni);
            UpdateEntityActors();
            App->CLSB_Doc->UpdateAllViews(UAV_ALL3DVIEWS | REBUILD_QUICK, NULL);
        }
// end change

    }
}

void CFusionDoc::UpdateAfterWadChange()
{
    SetModifiedFlag();

    if (!Level_LoadWad (App->CLSB_Doc->pLevel))
    {
        CString Msg;

        AfxFormatString1 (Msg, IDS_CANTLOADTXL, Level_GetWadPath(App->CLSB_Doc->pLevel));
        AfxMessageBox (Msg, MB_OK + MB_ICONERROR);
    }

    // update textures tab
    App->CLSB_Doc->mCurTextureSelection = 0;
    App->CL_TextureDialog->Fill_ListBox();

    // update all brush faces
    BrushList_EnumLeafBrushes (Level_GetBrushes (App->CLSB_Doc->pLevel), this, ::fdocUpdateBrushFaceTextures);
    {
        // find the rendered view and set the wad size infos for it
        POSITION		pos;
        CFusionView	*	pView;

        pos = GetFirstViewPosition();
        while( pos != NULL )
        {
            pView = (CFusionView*)GetNextView(pos) ;
            if( Render_GetViewType( pView->VCam ) & (VIEWSOLID|VIEWTEXTURE|VIEWWIRE) )
            {
                Render_SetWadSizes (pView->VCam, Level_GetWadSizeInfos (App->CLSB_Doc->pLevel));
                break ;	// Only 1 rendered view for now
            }
        }
    }

    if (Level_RebuildBspAlways (App->CLSB_Doc->pLevel))
    {
        RebuildTrees();
        App->CLSB_Doc->UpdateAllViews (UAV_ALL3DVIEWS, NULL);
    }

}

void CFusionDoc::OnCameraForward()
{
    SetModifiedFlag();

    CEntity *pCameraEntity = App->CLSB_Camera_WE->FindCameraEntity();

    if (pCameraEntity)
    {
        geVec3d Angles;
        pCameraEntity->GetAngles( &Angles, Level_GetEntityDefs (App->CLSB_Doc->pLevel) );

        geXForm3d TransformOrigin;
        geXForm3d_SetIdentity(&TransformOrigin);

        geXForm3d_RotateZ(&TransformOrigin, Angles.X);
        geXForm3d_RotateX(&TransformOrigin, Angles.Z);
        geXForm3d_RotateY(&TransformOrigin, (-Angles.Y-M_PI/2.0f));

        geXForm3d_Translate(&TransformOrigin, pCameraEntity->mOrigin.X, pCameraEntity->mOrigin.Y, pCameraEntity->mOrigin.Z);

        geXForm3d Delta;
        geXForm3d_SetTranslation(&Delta, CAMERA_MOVEMENT_DISTANCE, 0, 0);

        geXForm3d_Multiply(&TransformOrigin, &Delta, &TransformOrigin);

        geVec3d_Copy(&(TransformOrigin.Translation), &(pCameraEntity->mOrigin));

        SetRenderedViewCamera( &(pCameraEntity->mOrigin), &Angles) ;
        App->CLSB_Doc->UpdateAllViews( UAV_ALLVIEWS, NULL );
    }
}

void CFusionDoc::OnCameraBack()
{
    SetModifiedFlag();

    CEntity *pCameraEntity = App->CLSB_Camera_WE->FindCameraEntity();

    if (pCameraEntity)
    {
        geVec3d Angles;
        pCameraEntity->GetAngles( &Angles, Level_GetEntityDefs (App->CLSB_Doc->pLevel) );

        geXForm3d TransformOrigin;
        geXForm3d_SetIdentity(&TransformOrigin);

        geXForm3d_RotateZ(&TransformOrigin, Angles.X);
        geXForm3d_RotateX(&TransformOrigin, Angles.Z);
        geXForm3d_RotateY(&TransformOrigin, (-Angles.Y-M_PI/2.0f));

        geXForm3d_Translate(&TransformOrigin, pCameraEntity->mOrigin.X, pCameraEntity->mOrigin.Y, pCameraEntity->mOrigin.Z);

        geXForm3d Delta;
        geXForm3d_SetTranslation(&Delta, -CAMERA_MOVEMENT_DISTANCE, 0, 0);

        geXForm3d_Multiply(&TransformOrigin, &Delta, &TransformOrigin);

        geVec3d_Copy(&(TransformOrigin.Translation), &(pCameraEntity->mOrigin));

        SetRenderedViewCamera( &(pCameraEntity->mOrigin), &Angles) ;
        App->CLSB_Doc->UpdateAllViews( UAV_ALLVIEWS, NULL );
    }
}

void CFusionDoc::OnCameraLeft()
{
    SetModifiedFlag();

    CEntity *pCameraEntity = App->CLSB_Camera_WE->FindCameraEntity();

    if (pCameraEntity)
    {
        geVec3d Angles;
        pCameraEntity->GetAngles( &Angles, Level_GetEntityDefs (App->CLSB_Doc->pLevel) );
        Angles.Y = Render_NormalizeAngle(Angles.Y - CAMERA_MOVEMENT_ANGLE);
        pCameraEntity->SetAngles( &Angles, Level_GetEntityDefs (App->CLSB_Doc->pLevel) ) ;
        SetRenderedViewCamera( &(pCameraEntity->mOrigin), &Angles) ;
        App->CLSB_Doc->UpdateAllViews( UAV_ALLVIEWS, NULL );
    }
}

void CFusionDoc::OnCameraRight()
{
    SetModifiedFlag();

    CEntity *pCameraEntity = App->CLSB_Camera_WE->FindCameraEntity();

    if (pCameraEntity)
    {
        geVec3d Angles;
        pCameraEntity->GetAngles( &Angles, Level_GetEntityDefs (App->CLSB_Doc->pLevel) );
        Angles.Y = Render_NormalizeAngle(Angles.Y + CAMERA_MOVEMENT_ANGLE);
        pCameraEntity->SetAngles( &Angles, Level_GetEntityDefs (App->CLSB_Doc->pLevel) ) ;
        SetRenderedViewCamera( &(pCameraEntity->mOrigin), &Angles) ;
        App->CLSB_Doc->UpdateAllViews( UAV_ALLVIEWS, NULL );
    }
}

void CFusionDoc::OnCameraLookUp()
{
    SetModifiedFlag();

    CEntity *pCameraEntity = App->CLSB_Camera_WE->FindCameraEntity();

    if (pCameraEntity)
    {
        geVec3d Angles;
        pCameraEntity->GetAngles( &Angles, Level_GetEntityDefs (App->CLSB_Doc->pLevel) );
        Angles.X = Angles.X - CAMERA_MOVEMENT_ANGLE;
        if (Angles.X < (M_PI / 2))
            Angles.X = (M_PI / 2);
        Render_NormalizeAngle(Angles.X);
        pCameraEntity->SetAngles( &Angles, Level_GetEntityDefs (App->CLSB_Doc->pLevel) ) ;
        SetRenderedViewCamera( &(pCameraEntity->mOrigin), &Angles) ;
        App->CLSB_Doc->UpdateAllViews( UAV_ALLVIEWS, NULL );
    }
}

void CFusionDoc::OnCameraLookDown()
{
    SetModifiedFlag();

    CEntity *pCameraEntity = App->CLSB_Camera_WE->FindCameraEntity();

    if (pCameraEntity)
    {
        geVec3d Angles;
        pCameraEntity->GetAngles( &Angles, Level_GetEntityDefs (App->CLSB_Doc->pLevel) );
        Angles.X = Angles.X + CAMERA_MOVEMENT_ANGLE;
        if (Angles.X > (3 * M_PI / 2))
            Angles.X = (3 * M_PI / 2);
        Render_NormalizeAngle(Angles.X);
        pCameraEntity->SetAngles( &Angles, Level_GetEntityDefs (App->CLSB_Doc->pLevel) ) ;
        SetRenderedViewCamera( &(pCameraEntity->mOrigin), &Angles) ;
        App->CLSB_Doc->UpdateAllViews( UAV_ALLVIEWS, NULL );
    }
}

void CFusionDoc::OnCameraUp()
{
    SetModifiedFlag();

    CEntity *pCameraEntity = App->CLSB_Camera_WE->FindCameraEntity();

    if (pCameraEntity)
    {
        geVec3d Angles;
        pCameraEntity->GetAngles( &Angles, Level_GetEntityDefs (App->CLSB_Doc->pLevel) );
        pCameraEntity->mOrigin.Y = pCameraEntity->mOrigin.Y + CAMERA_MOVEMENT_DISTANCE;
        SetRenderedViewCamera( &(pCameraEntity->mOrigin), &Angles) ;
        App->CLSB_Doc->UpdateAllViews( UAV_ALLVIEWS, NULL );
    }
}

void CFusionDoc::OnCameraDown()
{
    SetModifiedFlag();

    CEntity *pCameraEntity = App->CLSB_Camera_WE->FindCameraEntity();

    if (pCameraEntity)
    {
        geVec3d Angles;
        pCameraEntity->GetAngles( &Angles, Level_GetEntityDefs (App->CLSB_Doc->pLevel) );
        pCameraEntity->mOrigin.Y = pCameraEntity->mOrigin.Y - CAMERA_MOVEMENT_DISTANCE;
        SetRenderedViewCamera( &(pCameraEntity->mOrigin), &Angles) ;
        App->CLSB_Doc->UpdateAllViews( UAV_ALLVIEWS, NULL );
    }
}


void CFusionDoc::ExportWorldFile(const char *FileName)
{

    SetCursor(AfxGetApp()->LoadStandardCursor(IDC_WAIT));

    Level *NewLevel;
    int i;
    AddPremadeEnumData EnumData;

// changed QD Actors
    NewLevel = Level_Create (Level_GetWadPath (App->CLSB_Doc->pLevel), Level_GetHeadersDirectory (App->CLSB_Doc->pLevel),
        Level_GetActorsDirectory (App->CLSB_Doc->pLevel), Level_GetPawnIniPath (App->CLSB_Doc->pLevel));
// end change
    if (NewLevel == NULL)
    {
        SetCursor(AfxGetApp()->LoadStandardCursor(IDC_ARROW));
        AfxMessageBox ("Error: Unable to export objects.", MB_OK + MB_ICONERROR);
        return;
    }

    EnumData.NewLevel = NewLevel;
    EnumData.OldLevel = App->CLSB_Doc->pLevel;

    int NumSelBrushes = SelBrushList_GetSize (App->CLSB_Doc->pSelBrushes);

    // add all selected brushes and entities to the new level
    for (i = 0; i < NumSelBrushes; ++i)
    {
        Brush *NewBrush;
        Brush *OldBrush;

        OldBrush = SelBrushList_GetBrush (App->CLSB_Doc->pSelBrushes, i);
// changed QD Actors
        if(strstr(App->CL_Brush->Brush_GetName(OldBrush),".act")!=NULL)
            continue;
// end change
        NewBrush = Brush_Clone (OldBrush);
        Level_AppendBrush (NewLevel, NewBrush);

        // add any group or model that's referenced
        ::fdocAddReferencedModel (&EnumData, Brush_GetModelId (NewBrush));
        ::fdocAddReferencedGroup (&EnumData, Brush_GetGroupId (NewBrush));
    }

    Level_EnumEntities (App->CLSB_Doc->pLevel, &EnumData, ::fdocAddSelectedEntities);

    // ok, everything's added.  Write it to the file.
    if (!Level_WriteToFile (NewLevel, FileName))
    {
        SetCursor(AfxGetApp()->LoadStandardCursor(IDC_ARROW));
        AfxMessageBox ("Error: Unable to export objects to file.", MB_OK + MB_ICONERROR);
    }
    else
    {
        // possibly add level name to objects list...
        //mpMainFrame->m_wndTabControls->m_pBrushEntityDialog->SetupObjectListCombo ();
    }

    Level_Destroy (&NewLevel);

    SetCursor(AfxGetApp()->LoadStandardCursor(IDC_ARROW));
}

static geBoolean ExportBrushToMapFile( Brush *pBrush, void *lParam)
{
    std::ofstream *pMapFile = (std::ofstream*)lParam ;

  int NumFaces;
    int NumPoints;

    int FaceIndex;
    int TriangleIndex;

    Face *pFace;
    const geVec3d *pPoints;

    const char *pTextureName;
    geFloat TextureRotate;
    int TextureOffsetX;
    int TextureOffsetY;
    geFloat TextureScaleX;
    geFloat TextureScaleY;

    int Contents;
    int Surface;
    int Value;

    geFloat Translucency;

    Contents = 0;
    if (Brush_IsSolid(pBrush))
        Contents += CONTENTS_SOLID;
    if (Brush_IsWindow(pBrush))
        Contents += CONTENTS_WINDOW;
    if (Brush_IsWavy(pBrush))
        Contents += CONTENTS_WAVY;
    if (Brush_IsDetail(pBrush))
        Contents += CONTENTS_DETAIL;
    if (Brush_IsSubtract(pBrush))
        Contents += CONTENTS_SUBTRACT;
    if (Brush_IsClip(pBrush))
        Contents += CONTENTS_CLIP;
    if (Brush_IsArea(pBrush))
        Contents += CONTENTS_AREA;
    if (Brush_IsFlocking(pBrush))
        Contents += CONTENTS_FLOCKING;
    if (Brush_IsSheet(pBrush))
        Contents += CONTENTS_SHEET;
    if (Brush_IsHint(pBrush))
        Contents += CONTENTS_HINT;
    Contents += Brush_GetUserFlags(pBrush);

    (*pMapFile) << "{\n";
    
    NumFaces = Brush_GetNumFaces(pBrush);

    for (FaceIndex = 0; FaceIndex < NumFaces; ++FaceIndex)
    {
        pFace = Brush_GetFace(pBrush, FaceIndex);

        NumPoints = Face_GetNumPoints(pFace);

        if (NumPoints > 2)
        {

            pPoints = Face_GetPoints(pFace);

            pTextureName = Face_GetTextureName(pFace);
            Face_GetTextureShift(pFace, &TextureOffsetX, &TextureOffsetY);
            TextureRotate = Face_GetTextureRotate(pFace);
            Face_GetTextureScale(pFace, &TextureScaleX, &TextureScaleY);

            Surface = 0;
            if (Face_IsLight(pFace))
                Surface += SURF_LIGHT;
            if (Face_IsMirror(pFace))
                Surface += SURF_MIRROR;
            if (Face_IsFullBright(pFace))
                Surface += SURF_FULLBRIGHT;
            if (Face_IsSky(pFace))
                Surface += SURF_SKY;
            if (Face_IsGouraud(pFace))
                Surface += SURF_GOURAUD;
            if (Face_IsFlat(pFace))
                Surface += SURF_FLAT;
            if (Face_IsTextureLocked(pFace))
                Surface += SURF_TEXTURELOCK;
            if ((!(Face_IsVisible(pFace))) || Brush_IsClip(pBrush))
                Surface += SURF_NODRAW;
            if (Face_IsTransparent(pFace) || Face_IsMirror(pFace))
            {
                Translucency = Face_GetTranslucency(pFace);
                if (Translucency > 127)
                {
                    Surface += SURF_TRANS66;
                }
                else if (Translucency > 0)
                {
                    Surface += SURF_TRANS33;
                }
                else
                    Surface += SURF_TRANS;
            }

            Value = Face_GetLightIntensity(pFace);

            for (TriangleIndex = 1; TriangleIndex < (NumPoints - 1); ++TriangleIndex)
            {
                (*pMapFile) << "( ";
                (*pMapFile) << pPoints[0].X;
                (*pMapFile) << " ";
                (*pMapFile) << -(pPoints[0].Z);
                (*pMapFile) << " ";
                (*pMapFile) << pPoints[0].Y;
                (*pMapFile) << " ) ";

                (*pMapFile) << "( ";
                (*pMapFile) << pPoints[TriangleIndex].X;
                (*pMapFile) << " ";
                (*pMapFile) << -(pPoints[TriangleIndex].Z);
                (*pMapFile) << " ";
                (*pMapFile) << pPoints[TriangleIndex].Y;
                (*pMapFile) << " ) ";

                (*pMapFile) << "( ";
                (*pMapFile) << pPoints[TriangleIndex+1].X;
                (*pMapFile) << " ";
                (*pMapFile) << -(pPoints[TriangleIndex+1].Z);
                (*pMapFile) << " ";
                (*pMapFile) << pPoints[TriangleIndex+1].Y;
                (*pMapFile) << " ) ";

                (*pMapFile) << pTextureName;
                (*pMapFile) << " ";

                (*pMapFile) << TextureOffsetX;
                (*pMapFile) << " ";
                (*pMapFile) << TextureOffsetY;
                (*pMapFile) << " ";

                (*pMapFile) << TextureRotate;
                (*pMapFile) << " ";

                (*pMapFile) << TextureScaleX;
                (*pMapFile) << " ";
                (*pMapFile) << TextureScaleY;
                (*pMapFile) << " ";

                (*pMapFile) << Contents;
                (*pMapFile) << " ";
                (*pMapFile) << Surface;
                (*pMapFile) << " ";
                (*pMapFile) << Value;
                (*pMapFile) << "\n";
            }
        }
    }
    (*pMapFile) << "}\n";

    return GE_TRUE ;
}

void CFusionDoc::ExportMapFile(const char *FileName)
{
//	try {
//
//		SetCursor(AfxGetApp()->LoadStandardCursor(IDC_WAIT));
//
//		std::ofstream MapFile( FileName, std::ofstream::out | std::ofstream::trunc );
//
//		int BrushIndex;
//		
//		int NumSelBrushes = SelBrushList_GetSize (pSelBrushes);
//
//		if (NumSelBrushes)
//		{
//			MapFile << "{\n";
//			MapFile << "\"classname\" \"worldspawn\"\n";
//			
//			Brush *pBrush;
//
//			// add all selected brushes and entities to the new level
//			for (BrushIndex = 0; BrushIndex < NumSelBrushes; ++BrushIndex)
//			{
//				pBrush = SelBrushList_GetBrush (pSelBrushes, BrushIndex);
//// changed QD Actors
//				if(strstr(App->CL_Brush->Brush_GetName(pBrush),".act")!=NULL)
//					continue;
//// end change
//				if(Brush_IsMulti(pBrush))
//				{
//					BrushList_EnumLeafBrushes(App->CL_Brush->Brush_GetBrushList(pBrush), &MapFile, ::ExportBrushToMapFile);
//				}
//				else
//				{
//					::ExportBrushToMapFile(pBrush, &MapFile);
//				}
//			}
//			MapFile << "}\n";
//		}
//
//		int EntityIndex;
//		int NumEntityKeyValuePairs;
//		int KeyValuePairIndex;
//		CString Key;
//		CString Value;
//
//		CEntityArray *Entities = Level_GetEntities (pLevel);
//		int NumEntities = Entities->GetSize() ;
//
//		for (EntityIndex = 0 ; EntityIndex < NumEntities; EntityIndex++)
//		{
//
//			CEntity *pEntity = &(*Entities)[EntityIndex];
//
//			if (pEntity->IsCamera() == GE_FALSE)	// Exclude Cameras
//			{
//				if (pEntity->IsSelected())
//				{
//
//					MapFile << "{\n";
//
//					NumEntityKeyValuePairs = pEntity->GetNumKeyValuePairs();
//					for (KeyValuePairIndex = 0; KeyValuePairIndex < NumEntityKeyValuePairs; KeyValuePairIndex++)
//					{
//						pEntity->GetKeyValuePair(KeyValuePairIndex, Key, Value);
//
//						MapFile << '"';
//						MapFile << Key;
//						MapFile << '"';
//
//						MapFile << ' ';
//
//						MapFile << '"';
//						MapFile << Value;
//						MapFile << '"';
//
//						MapFile << '\n';
//					}
//
//					MapFile << "}\n";
//				}
//			}
//		}
//
//		SetCursor(AfxGetApp()->LoadStandardCursor(IDC_ARROW));
//	}
//	catch(CException e)
//	{
//		SetCursor(AfxGetApp()->LoadStandardCursor(IDC_ARROW));
//
//		AfxMessageBox ("Error: Unable to export objects to file.", MB_OK + MB_ICONERROR);
//	}

}

// changed QD 11/03
void CFusionDoc::ExportTo3dtv1_32(const char *FileName)
{
    {
        // update view information in level
        ViewStateInfo *pViewStateInfo;
        POSITION		pos;
        CFusionView	*	pView;
        int iView;

        pos = GetFirstViewPosition();
        while( pos != NULL )
        {
            pView = (CFusionView*)GetNextView(pos) ;
            switch (Render_GetViewType (pView->VCam))
            {
                case VIEWSOLID :
                case VIEWTEXTURE :
                case VIEWWIRE :
                    iView = 0;
                    break;
                case VIEWTOP :
                    iView = 1;
                    break;
                case VIEWFRONT :
                    iView = 2;
                    break;
                case VIEWSIDE :
                    iView = 3;
                    break;
                default :
                    iView = -1;
            }
            if (iView != -1)
            {
                pViewStateInfo = Level_GetViewStateInfo (App->CLSB_Doc->pLevel, iView);
                pViewStateInfo->IsValid = GE_TRUE;
                pViewStateInfo->ZoomFactor = Render_GetZoom (pView->VCam);
                Render_GetPitchRollYaw (pView->VCam, &pViewStateInfo->PitchRollYaw);
                Render_GetCameraPos (pView->VCam, &pViewStateInfo->CameraPos);
            }
        }
    }

    // and then write the level info to the file
    geBoolean fResult = Level_ExportTo3dtv1_32(App->CLSB_Doc->pLevel, FileName);

    if(fResult == GE_FALSE)
    {
    
    }
}

// *************************************************************************
// * Equity_Export_3DS				ExportTo3ds							   *
// *************************************************************************
void CFusionDoc::ExportTo3ds(const char *FileName, int ExpSelected, geBoolean ExpLights, geBoolean ExpFiles)
{
    {
        // update view information in level
        ViewStateInfo *pViewStateInfo;
        POSITION		pos;
        CFusionView	*	pView;
        int iView;

        pos = GetFirstViewPosition();
        while( pos != NULL )
        {
            pView = (CFusionView*)GetNextView(pos) ;
            switch (Render_GetViewType (pView->VCam))
            {
                case VIEWSOLID :
                case VIEWTEXTURE :
                case VIEWWIRE :
                    iView = 0;
                    break;
                case VIEWTOP :
                    iView = 1;
                    break;
                case VIEWFRONT :
                    iView = 2;
                    break;
                case VIEWSIDE :
                    iView = 3;
                    break;
                default :
                    iView = -1;
            }
            if (iView != -1)
            {
                pViewStateInfo = Level_GetViewStateInfo (App->CLSB_Doc->pLevel, iView);
                pViewStateInfo->IsValid = GE_TRUE;
                pViewStateInfo->ZoomFactor = Render_GetZoom (pView->VCam);
                Render_GetPitchRollYaw (pView->VCam, &pViewStateInfo->PitchRollYaw);
                Render_GetCameraPos (pView->VCam, &pViewStateInfo->CameraPos);
            }
        }
    }

// changed QD 12/03
    BrushList *BList;
    geBoolean fResult;

    BList = Level_GetBrushes (App->CLSB_Doc->pLevel);
    if(!ExpSelected&&!ExpFiles)
        fResult = Level_ExportTo3ds(App->CLSB_Doc->pLevel, FileName, BList, ExpSelected, ExpLights, -1);
    else
    {
        int i, GroupID, GroupCount;
        char NewFileName[MAX_PATH];
        strcpy(NewFileName, FileName);
        GroupID=-1;
        GroupCount=1;

        if(ExpFiles)
        {
            GroupListType *GroupList;

            GroupList=Level_GetGroups(App->CLSB_Doc->pLevel);
            GroupCount=Group_GetCount(GroupList);
        }

        for(i=0;i<GroupCount;i++)
        {
            BrushList *SBList;
            Brush *pBrush;
            BrushIterator bi;

            SBList=BrushList_Create();

            pBrush = BrushList_GetFirst (BList, &bi);
            while (pBrush != NULL)
            {
                if(!strstr(App->CL_Brush->Brush_GetName(pBrush),".act"))
                {
                    if(!ExpSelected || SelBrushList_Find(App->CLSB_Doc->pSelBrushes, pBrush))
                    {
                        if(!ExpFiles || Brush_GetGroupId(pBrush)==i)
                        {
                            Brush *pClone =	Brush_Clone(pBrush);
                            BrushList_Append(SBList, pClone);
                        }
                    }
                }

                pBrush = BrushList_GetNext(&bi);
            }
            // do CSG
            {
                ModelIterator	mi;
                int				i, CurId = 0;
                ModelInfo_Type	*ModelInfo;
                Model			*pMod;

                BrushList_ClearAllCSG (SBList);

                BrushList_DoCSG(SBList, CurId, ::fdocBrushCSGCallback, this);

                //build individual model mini trees
                ModelInfo = Level_GetModelInfo (App->CLSB_Doc->pLevel);
                pMod = ModelList_GetFirst (ModelInfo->Models, &mi);

                for(i=0;i < ModelList_GetCount(ModelInfo->Models);i++)
                {
                    CurId = Model_GetId (pMod);

                    BrushList_DoCSG(SBList, CurId, ::fdocBrushCSGCallback, this);
                }
            }

            if(ExpFiles)
            {
                GroupID=i;

                //build individual filenames
                char Name[MAX_PATH];
                char c[2];
                c[1]='\0';
                ::FilePath_GetName (FileName, Name);
                c[0] = (char)(48+(i-i%100)/100);
                strcat(Name, c);
                c[0] = (char)(48+((i-i%10)/10)%10);
                strcat(Name, c);
                c[0] = (char)(48+i%10);
                strcat(Name, c);

                ::FilePath_ChangeName(FileName, Name, NewFileName);
            }

            fResult = Level_ExportTo3ds(App->CLSB_Doc->pLevel, NewFileName, SBList, ExpSelected, ExpLights, GroupID);
            if(!fResult)
                App->Say("Brush List Fail");
            BrushList_Destroy(&SBList);
        }

    }
// end change 12/03

    if(fResult == GE_FALSE)
    {
        
    }
}

// *************************************************************************
// * Equity_Export_RFW		ExportTo_RFW	// Old Exporter				   *
// *************************************************************************
void CFusionDoc::ExportTo_RFW(const char *FileName, int ExpSelected, geBoolean ExpLights, geBoolean ExpFiles)
{
    {
        // update view information in level
        ViewStateInfo *pViewStateInfo;
        POSITION		pos;
        CFusionView	*	pView;
        int iView;

        pos = GetFirstViewPosition();
        while( pos != NULL )
        {
            pView = (CFusionView*)GetNextView(pos) ;
            switch (Render_GetViewType (pView->VCam))
            {
                case VIEWSOLID :
                case VIEWTEXTURE :
                case VIEWWIRE :
                    iView = 0;
                    break;
                case VIEWTOP :
                    iView = 1;
                    break;
                case VIEWFRONT :
                    iView = 2;
                    break;
                case VIEWSIDE :
                    iView = 3;
                    break;
                default :
                    iView = -1;
            }
            if (iView != -1)
            {
                pViewStateInfo = Level_GetViewStateInfo (App->CLSB_Doc->pLevel, iView);
                pViewStateInfo->IsValid = GE_TRUE;
                pViewStateInfo->ZoomFactor = Render_GetZoom (pView->VCam);
                Render_GetPitchRollYaw (pView->VCam, &pViewStateInfo->PitchRollYaw);
                Render_GetCameraPos (pView->VCam, &pViewStateInfo->CameraPos);
            }
        }
    }

// changed QD 12/03 77
    BrushList *BList;
    geBoolean fResult;

    BList = Level_GetBrushes (App->CLSB_Doc->pLevel);
    if(!ExpSelected&&!ExpFiles)
        fResult = App->CLSB_Export_World->Level_Build_G3ds(reinterpret_cast<tag_Level3 *> (App->CLSB_Doc->pLevel), FileName, BList, ExpSelected, ExpLights, -1);

    else
    {
        int i, GroupID, GroupCount;
        char NewFileName[MAX_PATH];
        strcpy(NewFileName, FileName);
        GroupID=-1;
        GroupCount=1;

        if(ExpFiles)
        {
            GroupListType *GroupList;

            GroupList=Level_GetGroups(App->CLSB_Doc->pLevel);
            GroupCount=Group_GetCount(GroupList);
        }

        for(i=0;i<GroupCount;i++)
        {
            BrushList *SBList;
            Brush *pBrush;
            BrushIterator bi;

            SBList=BrushList_Create();

            pBrush = BrushList_GetFirst (BList, &bi);
            while (pBrush != NULL)
            {
                if(!strstr(App->CL_Brush->Brush_GetName(pBrush),".act"))
                {
                    if(!ExpSelected || SelBrushList_Find(App->CLSB_Doc->pSelBrushes, pBrush))
                    {
                        if(!ExpFiles || Brush_GetGroupId(pBrush)==i)
                        {
                            Brush *pClone =	Brush_Clone(pBrush);
                            BrushList_Append(SBList, pClone);
                        }
                    }
                }

                pBrush = BrushList_GetNext(&bi);
            }
            // do CSG
            {
                ModelIterator	mi;
                int				i, CurId = 0;
                ModelInfo_Type	*ModelInfo;
                Model			*pMod;

                BrushList_ClearAllCSG (SBList);

                BrushList_DoCSG(SBList, CurId, ::fdocBrushCSGCallback, this);

                //build individual model mini trees
                ModelInfo = Level_GetModelInfo (App->CLSB_Doc->pLevel);
                pMod = ModelList_GetFirst (ModelInfo->Models, &mi);

                for(i=0;i < ModelList_GetCount(ModelInfo->Models);i++)
                {
                    CurId = Model_GetId (pMod);

                    BrushList_DoCSG(SBList, CurId, ::fdocBrushCSGCallback, this);
                }
            }

            if(ExpFiles)
            {
                GroupID=i;

                //build individual filenames
                char Name[MAX_PATH];
                char c[2];
                c[1]='\0';
                ::FilePath_GetName (FileName, Name);
                c[0] = (char)(48+(i-i%100)/100);
                strcat(Name, c);
                c[0] = (char)(48+((i-i%10)/10)%10);
                strcat(Name, c);
                c[0] = (char)(48+i%10);
                strcat(Name, c);

                ::FilePath_ChangeName(FileName, Name, NewFileName);
            }

            fResult = App->CLSB_Export_World->Level_Build_G3ds(reinterpret_cast<tag_Level3 *> (App->CLSB_Doc->pLevel), NewFileName, SBList, ExpSelected, ExpLights, GroupID);
            if(!fResult)
                App->Say("Error exporting group");
            BrushList_Destroy(&SBList);
        }

    }
// end change 12/03

    if(fResult == GE_FALSE)
    {
        // Ok, the save was successful.  Gun any ".old" files we
        // ..have laying around for this file.
        App->Say("Error exporting file");
    }
    else
    {
            App->Say("Exported");
    }
}

void CFusionDoc::OnFileExport() // Old Exporter
{
// changed QD 12/03
    static const char FDTitle[] = "Export";
//	CFileDialog dlg(FALSE, "3dt", NULL, (OFN_OVERWRITEPROMPT | OFN_HIDEREADONLY | OFN_NOREADONLYRETURN | OFN_PATHMUSTEXIST | OFN_NOREADONLYRETURN),
                                //	"World Files (*.3dt)|*.3dt|Map Files (*.map)|*.map|World Files v1.32 (*.3dt)|*.3dt|Autodesk (*.3ds)|*.3ds|Equity Room (*.ebr)|*.ebr|All Files (*.*)|*.*||");

    CFileDialog dlg(FALSE, "3dt", NULL, (OFN_OVERWRITEPROMPT | OFN_HIDEREADONLY | OFN_NOREADONLYRETURN | OFN_PATHMUSTEXIST | OFN_NOREADONLYRETURN),
                                    "Equity Room (*.G3ds)|*.G3ds|Map Files (*.map)|*.map|World Files v1.32 (*.3dt)|*.3dt|Autodesk (*.3ds)|*.3ds|World Files (*.3dt)|*.3dt|All Files (*.*)|*.*||");

    dlg.m_ofn.lpstrTitle = FDTitle;	
    if (dlg.DoModal () == IDOK)
    {
        switch(dlg.m_ofn.nFilterIndex)
        {
        case 1 :
            {
                CExport3dsDialog ExpDlg;
                if (ExpDlg.DoModal () == IDOK)
                {
                    ExportTo_RFW(dlg.GetPathName(), 1, 0, 0);
                }
            }
            break;
        case 2 :
            ExportMapFile(dlg.GetPathName());
            break;
        case 3 :
            ExportTo3dtv1_32(dlg.GetPathName());
            break;
// changed QD 12/03
        case 4 :
            {
                CExport3dsDialog ExpDlg;
                if (ExpDlg.DoModal () == IDOK)
                {
                    ExportTo3ds(dlg.GetPathName(), ExpDlg.m_ExportAll, ExpDlg.m_ExportLights, ExpDlg.m_GroupFile);
                    break;
                }
            }
        case 5 :
            {
                ExportWorldFile(dlg.GetPathName());
            }
// end change
        }
    }
}

void CFusionDoc::OnUpdateFileExport(CCmdUI* pCmdUI) 
{
    BOOL		bEnable ;
    
    bEnable = ((App->CLSB_Doc->GetSelState() & ANYBRUSH) ? TRUE : FALSE) || ((App->CLSB_Doc->GetSelState() & ANYENTITY) ? TRUE : FALSE);
    
    pCmdUI->Enable( bEnable ) ;	
    
}

// *************************************************************************
// * 						OnFileExportGDSB:- hgtterry					   *
// *************************************************************************
void CFusionDoc::OnUpdateFileExportGDSB(CCmdUI* pCmdUI) 
{
    BOOL		bEnable ;
    
    bEnable = ((App->CLSB_Doc->GetSelState() & ANYBRUSH) ? TRUE : FALSE) || ((App->CLSB_Doc->GetSelState() & ANYENTITY) ? TRUE : FALSE);
    
    pCmdUI->Enable( bEnable ) ;	
    
}

// *************************************************************************
// * 						OnFileExportGDSB:- hgtterry					   *
// *************************************************************************
void CFusionDoc::OnFileExportGDSB()
{
    App->CLSB_Export_World->Export_World_GD3D(0);
}

// *************************************************************************
// * 					OnFileExportObject:- hgtterry					   *
// *************************************************************************
void CFusionDoc::OnFileExportObject()
{
    App->CLSB_Export_World->Export_World_To_Object();
}

// *************************************************************************
// * 				OnFileExport_Ogre3D_Mesh:- hgtterry					   *
// *************************************************************************
void CFusionDoc::OnFileExport_Ogre3D_Mesh()
{
    App->CLSB_Export_World->Export_World_To_Ogre3D_Mesh();
}

const char* CFusionDoc::GetObjectName3D(CPoint point, ViewVars *v)
{
    int			CurEnt = 0;
    geFloat		MinEDist;
    CEntityArray *Entities = Level_GetEntities (App->CLSB_Doc->pLevel);
    BrushList	*BList = Level_GetBrushes (App->CLSB_Doc->pLevel);
    SelectBrush3DCBData	bdat;
    geVec3d ClickPosWorld;
//	geBoolean	EntitySelected	=FALSE;

    Render_ViewToWorld(v, point.x, point.y, &bdat.vp);
    Render_BackRotateVector(v, &bdat.vp, &bdat.wp);
    Render_GetCameraPos(v, &bdat.vp);

    Render_ViewToWorld (v, point.x, point.y, &ClickPosWorld);

    MinEDist = bdat.MinBDist = 999999.0f;

    for(int i=0;i < Entities->GetSize();i++)
    {

        CEntity *pEnt = &(*Entities)[i];

        if (EntityIsVisible (pEnt))
        {
            bdat.CurDist=pEnt->RayDistance (point, v);
            if ((bdat.CurDist < 900.0f)
                && (bdat.CurDist < MinEDist)
                && (bdat.CurDist > MIN_ENTITY_SELECT_DIST))
            {
                    MinEDist=bdat.CurDist;
                    CurEnt	=i;
            }
        }
    }
    bdat.CurBrush	= NULL;
    bdat.CurFace	= NULL;
    bdat.pDoc		= this;
    BrushList_EnumCSGBrushes(BList, &bdat, SelectBrush3DCB);
        
    if((bdat.MinBDist < 999999.0f) && (MinEDist > MIN_ENTITY_SELECT_DIST))
    {
        //check the distance of the hit wall
        //see if the closest entity is occluded
        if(bdat.CurBrush)
        {
            if(bdat.CurFace)
            {
                geFloat		pDist;
                const GPlane	*p;

                //find the dist ratio from click ray to plane normal
                p		=Face_GetPlane(bdat.CurFace);
                pDist	=geVec3d_DotProduct(&bdat.wp, &p->Normal);

                if(pDist != 0.0f)
                {
                    pDist	=(Face_PlaneDistance(bdat.CurFace, &bdat.vp)  / pDist);
                }
                geVec3d_Scale(&bdat.wp, pDist, &ClickPosWorld);
                pDist	=geVec3d_Length(&ClickPosWorld);

                if(MinEDist < pDist)
                {
                
                    CEntity *pEnt = &(*Entities)[CurEnt];
                    return pEnt->GetName();
                    
                }
            }
        }

    }

    if( bdat.CurBrush)
    {
        
        
        const GPlane *p;
        geFloat pDist;
        geVec3d ClickPosWorld;
        FaceSearchCallbackData fsData;
        
        if (Brush_GetType (bdat.CurBrush) == BRUSH_LEAF)
        {
            // if the found face is on a leaf brush, then skip the rest of the search
            fsData.pFoundFace = bdat.CurFace;
            fsData.Found = GE_TRUE;
            fsData.pFoundBrush = bdat.CurBrush;
        }
        else
        {
            // determine the impact point
            p		=Face_GetPlane(bdat.CurFace);
            pDist	=geVec3d_DotProduct(&bdat.wp, &p->Normal);
            if(pDist != 0.0f)
            {
                //grab plane distance and move inward by 16
                pDist	=(Face_PlaneDistance(bdat.CurFace, &bdat.vp)) / pDist;
            }
            
            geVec3d_Scale(&bdat.wp, pDist, &ClickPosWorld);
            
            //add in distance from the camera
            geVec3d_Subtract(&ClickPosWorld, &bdat.vp, &ClickPosWorld);
            geVec3d_Inverse (&ClickPosWorld);
            
            // OK, now search list for a face that contains this point and
            // is coplanar with the matched face.
            fsData.pFacePlane = p;
            fsData.Found = GE_FALSE;
            fsData.pFoundFace = NULL;
            fsData.pFoundBrush = NULL;
            fsData.ImpactPoint = ClickPosWorld;
            
            BrushList_EnumLeafBrushes (BList, &fsData, ::fdocFindLeafFace);
            if (!fsData.Found)
            {
                BrushList_EnumLeafBrushes (BList, &fsData, ::fdocFindCutFace);
            }
        }
        if (fsData.Found)
        {
            return App->CL_Brush->Brush_GetName(fsData.pFoundBrush);
            
        }
    }


    return "";
}


CEntity* CFusionDoc::GetSelectedEntity()
{
    CEntity* pEnt = NULL;

    if(App->CLSB_Doc->SelState & ONEENTITY)
    {
        CEntityArray *Entities = Level_GetEntities (App->CLSB_Doc->pLevel);

        //for(int i=0;i < Entities->GetSize() && !((CEntity*)(Entities)[i]->IsSelected ());i++);
        
        int i = 0;
        for(i = 0;i < Entities->GetSize(); i++)
        {
            CEntity* p = &(*Entities)[i];
            if(p->IsSelected())
                break;
        }
        App->CLSB_Doc->mCurrentEntity	= i;
        if(App->CLSB_Doc->mCurrentEntity > Entities->GetSize()-1 )
            return NULL;
    
        pEnt = &(*Entities)[App->CLSB_Doc->mCurrentEntity];

        return pEnt;	
    }

    return pEnt;
}

// This is the range handler for the types of view that we have
// make sure when we add more view types that we update this.
void CFusionDoc::OnViewTypeWireFrame()
{
    App->CLSB_Doc->OnViewTypeWireFrame();

}

void CFusionDoc::OnViewTypeTexture()
{
    App->CLSB_Doc->OnViewTypeTexture();
}

void CFusionDoc::OnEquity_SetView() // GD_Terry [090123]
{
    App->CL_Main_View->Start_Main_View_Dlg();
}

void CFusionDoc::Start_QuickView()
{
    App->CLSB_TopTabs->Start_Headers_Tabs();
}

void CFusionDoc::Start_CommandPanel()
{
    App->CL_TabsControl->Start_Tabs_Control_Dlg();
}

void CFusionDoc::Start_RecentFiles()
{
    App->CLSB_RecentFiles->Start_RecentFiles_Dlg();
}

void CFusionDoc::OnUpdateViewTypeWireFrame(CCmdUI* pCmdUI)
{
    OnUpdateViewType(pCmdUI);
}

void CFusionDoc::OnUpdateViewTypeTexture(CCmdUI* pCmdUI)
{
    OnUpdateViewType(pCmdUI);
}

void CFusionDoc::OnUpdateViewType(CCmdUI* pCmdUI)
{
    BOOL	bEnable = FALSE ;

    CFusionView* pFusionView = GetCameraView();
    if (pFusionView)
    {
        if( pFusionView->mViewType == pCmdUI->m_nID )
            pCmdUI->SetCheck();
        else
            pCmdUI->SetCheck(0);

        bEnable = TRUE;
    }

    pCmdUI->Enable( bEnable ) ;
}


CFusionView* CFusionDoc::GetCameraView()
{
    CView* pView;
    CFusionView* pFusionView;
    POSITION pos = GetFirstViewPosition();

    while (pos != NULL)
    {
        pView = GetNextView(pos);

        if ( pView->IsKindOf( RUNTIME_CLASS (CFusionView)) )
        {
            pFusionView = (CFusionView*) pView;

            if ( (pFusionView->mViewType == ID_VIEW_TEXTUREVIEW) || 
                     (pFusionView->mViewType == ID_VIEW_3DWIREFRAME) )
                return pFusionView;
        }
    }

    return NULL;
}

void CFusionDoc::OnCameraCenteronselection() 
{
    CEntity *pCameraEntity = App->CLSB_Camera_WE->FindCameraEntity();
    if (!pCameraEntity)
        return;

    SetModifiedFlag();

    // Get the current thing's position...
    geVec3d CurrentThingPos;

    if (App->CLSB_Doc->TempEnt)
    {
        CurrentThingPos = App->CLSB_Doc->mRegularEntity.mOrigin;
    }
    else
    {
        int NumSelBrushes = SelBrushList_GetSize(App->CLSB_Doc->pSelBrushes );
        
        if ((!NumSelBrushes) && (!App->CLSB_Doc->NumSelEntities))
            return;
        
        geVec3d EntitySelectionCenter = {0.0f,0.0f,0.0f};

        if (App->CLSB_Doc->NumSelEntities)
        {
            CEntityArray *Entities;
            Entities = Level_GetEntities (App->CLSB_Doc->pLevel);
            if (Entities)
            {
                int NumEntities = Entities->GetSize();

                for (int i=0;i<NumEntities;i++)
                {
                    if ((*Entities)[i].IsSelected())
                    {
                        geVec3d_Add(&EntitySelectionCenter, &(*Entities)[i].mOrigin, &EntitySelectionCenter);
                    }
                }
            }
        }

        geVec3d BrushSelectionCenter;
        SelBrushList_Center(App->CLSB_Doc->pSelBrushes, &BrushSelectionCenter);
        geVec3d_Scale(&BrushSelectionCenter, (float)NumSelBrushes, &BrushSelectionCenter);

        geVec3d_Add(&EntitySelectionCenter, &BrushSelectionCenter, &CurrentThingPos);

        geVec3d_Scale(&CurrentThingPos, 1/(float)((App->CLSB_Doc->NumSelEntities)+NumSelBrushes), &CurrentThingPos);
    }
    
    if (geVec3d_DistanceBetween(&CurrentThingPos, &(pCameraEntity->mOrigin)) > 0)
    {
        geVec3d Angles;

        geFloat x = (CurrentThingPos.X - pCameraEntity->mOrigin.X);
        geFloat y = (CurrentThingPos.Y - pCameraEntity->mOrigin.Y);
        geFloat z = (CurrentThingPos.Z - pCameraEntity->mOrigin.Z);

        if ((x == 0) && (z == 0))
        {
            if (y<0)
                Angles.X = 3 * (GE_PI/2);
            else if (y>0)
                Angles.X = (GE_PI/2);
            else
                Angles.X = GE_PI;
        }
        else
        {
            geFloat length = (float)sqrt( (x*x) + (z*z) );
            Angles.X = (float)atan2(-y,length) + GE_PI;
        }

        if (z != 0)
            Angles.Y = (float)atan2(-x, z) + GE_PI;
        else
            Angles.Y = GE_PI / 2;

        Angles.Z = 0;

        Angles.X = Render_NormalizeAngle(Angles.X);
        Angles.Y = Render_NormalizeAngle(Angles.Y);

        pCameraEntity->SetAngles( &Angles, Level_GetEntityDefs (App->CLSB_Doc->pLevel) ) ;

        SetRenderedViewCamera( &(pCameraEntity->mOrigin), &Angles) ;
        App->CLSB_Doc->UpdateAllViews( UAV_ALLVIEWS, NULL );
    }
}

void CFusionDoc::OnUpdateCameraCenteronselection(CCmdUI* pCmdUI) 
{
    if(App->CLSB_Doc->GetSelState()!=NOSELECTIONS)
        pCmdUI->Enable( TRUE );
    else
        pCmdUI->Enable( FALSE );
}

void CFusionDoc::OnToolsTemplate()
{
    App->CLSB_Doc->ResetAllSelectedEntities();
    App->CLSB_Doc->ResetAllSelectedFaces();
    App->CLSB_Doc->ResetAllSelectedBrushes();

    UpdateBrushAttributesDlg();
    UpdateFaceAttributesDlg();

    App->CLSB_Doc->mModeTool = ID_TOOLS_TEMPLATE;

    App->CLSB_Doc->mCurrentTool = ID_TOOLS_BRUSH_MOVEROTATEBRUSH;

    App->CLSB_Doc->SetAdjustmentMode( ADJUST_MODE_FACE ) ;
    //ConfigureCurrentTool();
}

void CFusionDoc::OnPlaceOmniLight()
{
    //mpMainFrame->m_wndTabControls->m_pBrushEntityDialog->PlaceOmniLight();
}

void CFusionDoc::OnPlaceSpotLight()
{
    //mpMainFrame->m_wndTabControls->m_pBrushEntityDialog->PlaceSpotLight();
}

void CFusionDoc::Zero_Camera() 
{
    App->CLSB_Camera_WE->Zero_Camera();
 
}

void CFusionDoc::OnCameraGoto() 
{
    App->CLSB_Camera_WE->Start_Move_Camera();
}

void CFusionDoc::OnModifyMove() 
{

    //App->Say("Needs Move Dialog");
    App->CL_Dialogs->Start_Move_Brush_Dlg();

//SetModifiedFlag();
//
//	geVec3d CenterOfSelection;
//	CenterOfSelection = SelectedGeoCenter;
//
//	CMoveDialog MoveDialog;
//
//	if (MoveDialog.DoModal(&CenterOfSelection, GE_TRUE, GE_TRUE, GE_TRUE) == IDOK)
//	{
//		if ( (CenterOfSelection.X != SelectedGeoCenter.X) ||
//				 (CenterOfSelection.Y != SelectedGeoCenter.Y) ||
//				 (CenterOfSelection.Z != SelectedGeoCenter.Z) )
//		{
//			geVec3d_Subtract(&CenterOfSelection, &SelectedGeoCenter, &CenterOfSelection);
//
//			if (mModeTool==ID_TOOLS_TEMPLATE)
//				MoveTemplateBrush(&CenterOfSelection);
//			else
//				MoveSelectedBrushList(pSelBrushes, &CenterOfSelection);
//
//			UpdateAllViews(UAV_ALL3DVIEWS, NULL);
//		}
//	}
}

void CFusionDoc::OnUpdateModifyMove(CCmdUI* pCmdUI) 
{
    if ((App->CLSB_Doc->GetSelState()!=NOSELECTIONS) || ((App->CLSB_Doc->mModeTool==ID_TOOLS_TEMPLATE) && !App->CLSB_Doc->PlaceObjectFlag))
        pCmdUI->Enable( TRUE );
    else
        pCmdUI->Enable( FALSE );
}

void CFusionDoc::OnModifyScale() 
{
    SetModifiedFlag();

    CScaleDialog ScaleDialog;
    geVec3d ScaleVector = {1.0f, 1.0f, 1.0f};

    if (ScaleDialog.DoModal(&ScaleVector) == IDOK)
    {
        ScaleSelectedBrushes(&ScaleVector);

        App->CLSB_Doc->UpdateAllViews(UAV_ALL3DVIEWS, NULL);

        if (App->CLSB_Brushes->Dimensions_Dlg_Running == 1)
        {
            App->CLSB_Brushes->Update_Pos_Dlg(App->CLSB_Brushes->Dimensions_Dlg_hWnd);
        }
    }
}

void CFusionDoc::OnUpdateModifyScale(CCmdUI* pCmdUI) 
{
    if ((App->CLSB_Doc->GetSelState()!=NOSELECTIONS) || ((App->CLSB_Doc->mModeTool==ID_TOOLS_TEMPLATE) && !App->CLSB_Doc->PlaceObjectFlag))
        pCmdUI->Enable( TRUE );
    else
        pCmdUI->Enable( FALSE );
}

void CFusionDoc::OnToolsBrushMakenewest() 
{
    SetModifiedFlag();
    MakeSelectedBrushNewest();	
}

void CFusionDoc::OnUpdateToolsBrushMakenewest(CCmdUI* pCmdUI) 
{
    if (App->CLSB_Doc->GetSelState()==ONEBRUSHONLY)
        pCmdUI->Enable( TRUE );
    else
        pCmdUI->Enable( FALSE );
}


void CFusionDoc::OnLinkviewports() 
{
    App->CLSB_Doc->OnLinkviewports();
}

void CFusionDoc::OnUpdateLinkviewports(CCmdUI* pCmdUI) 
{
    App->CLSB_Doc->OnUpdateLinkviewports(pCmdUI);
}

void CFusionDoc::OnTemplateSunlight() 
{
    //mpMainFrame->m_wndTabControls->m_pBrushEntityDialog->PlaceSunLight();
}

// changed QD Actors
void CFusionDoc::OnViewShowActors()
{
    bShowActors	=!(bShowActors);
    Level_SetShowActors(App->CLSB_Doc->pLevel, bShowActors);
    CEntityArray *Entities = Level_GetEntities (App->CLSB_Doc->pLevel);
    int i;

    if(!bShowActors)
    {
        for(i=0;i < Entities->GetSize();i++)
        {
            Brush *pBrush = (*Entities)[i].GetActorBrush();
            if(pBrush!=NULL)
            {
                Brush_SetVisible(pBrush, GE_FALSE);
            }
        }
    }
    else
    {
        for(i=0;i < Entities->GetSize();i++)
        {
            Brush *pBrush = (*Entities)[i].GetActorBrush();
            if(pBrush!=NULL)
            {
                Brush_SetVisible(pBrush, GE_TRUE);
            }
        }
    }
    App->CLSB_Doc->UpdateAllViews(UAV_ALL3DVIEWS | REBUILD_QUICK, NULL);
}

void CFusionDoc::OnUpdateViewShowActors(CCmdUI* pCmdUI)
{
    pCmdUI->SetCheck(bShowActors);
}
// end change
