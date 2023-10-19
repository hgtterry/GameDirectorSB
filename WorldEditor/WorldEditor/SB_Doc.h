#pragma once

#include "SelFaceList.h"
#include "undostack.h"

enum BrushSel
{
	brushSelToggle,
	brushSelAlways,
	brushDeselAlways
};

enum fdocAdjustEnum
{
	ADJUST_MODE_TOGGLE,
	ADJUST_MODE_BRUSH,
	ADJUST_MODE_FACE
};

//class CMainFrame;

class SB_Doc
{
public:
	SB_Doc(void);
	~SB_Doc(void);

	void AddBrushToWorld();

	bool DeleteSelectedBrushes();
	void DeleteCurrentThing();
	void DeleteEntity(int EntityIndex);

	void OnEditDelete();
	void OnViewTypeWireFrame();
	void OnViewTypeTexture();

	void SelectOrtho(CPoint point, ViewVars* v);

	void DoneResize(int sides, int inidx);
	void DoneMove(void);
	void DoneMoveEntity(void);
	void DoneRotate(void);

	void DoGeneralSelect(void);
	void DoEntitySelection(CEntity* pEntity);
	void DoBrushSelection(Brush* pBrush, BrushSel	nSelType); //	brushSelToggle | brushSelAlways)

	void Lock_AllTextures(void);

	void SelectAll(void);
	void UpdateSelected(void);
	void ResetAllSelections(void);
	void ResetAllSelectedFaces(void);
	void ResetAllSelectedBrushes(void);
	void ResetAllSelectedEntities();
	void UpdateAllViews(int Mode, CView* pSender, BOOL Override = FALSE);

	void MoveSelectedBrushes(geVec3d const* v);
	void MoveSelectedBrushList(SelBrushList* pList, geVec3d const* v);
	void MoveTemplateBrush(geVec3d* v);
	void MoveSelectedClone(geVec3d const* v);

	void RotateTemplateBrush(geVec3d* v);

	void AddCameraEntityToLevel(void);
	geBoolean CreateEntityFromName(char const* pEntityType, CEntity& NewEnt);

	void DoneShear(int sides, int inidx);
	BOOL TempDeleteSelected(void);
	void BrushSelect(Brush* pBrush);

	int FindClosestThing(POINT const* ptFrom, ViewVars* v, Brush** ppMinBrush, CEntity** ppMinEntity, geFloat* pDist);
	geBoolean FindClosestBrush(POINT const* ptFrom, ViewVars* v, Brush** ppFoundBrush, geFloat* pMinEdgeDist);
	geBoolean FindClosestEntity(POINT const* ptFrom, ViewVars* v, CEntity** ppMinEntity, geFloat* pMinEntityDist);

	const char* ReturnThingUnderPoint(CPoint point, ViewVars* v);

	DWORD GetSelState(void) { return SelState; }
	int	 GetLockAxis(void) { return mLockAxis; };
	void SetLockAxis(int Lock) { mLockAxis = Lock; };
	void ToggleSelectionLock(void) { SelectLock = !(SelectLock); }
	BOOL IsSelectionLocked(void) { return SelectLock; }
	void SetAdjustmentMode(fdocAdjustEnum nCmdIDMode);
	void ConfigureCurrentTool(void);

	void SelectModelBrushes(BOOL Select, int ModelId);

	void SetAllFacesTextureScale(geFloat ScaleVal);
	void SelectGroupBrushes(BOOL Select, int WhichGroup);

	void ShearSelected(float dx, float dy, int sides, int inidx);
	void ResizeSelected(float dx, float dy, int sides, int inidx);

	geVec3d* GetLeakPoints(void) { assert(LeakPoints); return LeakPoints; }

	void OnUpdateLinkviewports(CCmdUI* pCmdUI);
	void OnLinkviewports();
	void LinkViewports();

	// ----------------------------------------------------------- Varibles

	CMainFrame* mpMainFrame;

	fdocAdjustEnum mAdjustMode;

	int	NumSelEntities;
	int mShowSelectedFaces;
	int mCurrentTool, mCurrentBitmap, mShowBrush, mModeTool;
	int mShowEntities, mCurrentGroup, mCurTextureSelection;
	int IsNewDocument, mActiveView;

	int mLastOp, mCurrentEntity, ScaleNum;

	geVec3d	SelectedGeoCenter, FinalPos, FinalRot, FinalScale;

	SelBrushList* pTempSelBrushes;

	Brush* BTemplate, * CurBrush, * TempShearTemplate;
	SelBrushList* pSelBrushes;
	SelFaceList* pSelFaces;

	int mShowSelectedBrushes;
	int mLockAxis;
	geBoolean	mConstrainHollows;
	BOOL SelectLock, TempEnt;
	BOOL PlaceObjectFlag;
	DWORD SelState;

	GNode* mWorldBsp;
	CEntity	mRegularEntity;

	UndoStack* pUndoStack;
	geVec3d* LeakPoints;

	Level* pLevel;
};

