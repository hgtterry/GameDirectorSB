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
};

