#pragma once
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

	Level* pLevel;
};

