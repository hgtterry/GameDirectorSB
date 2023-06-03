#pragma once
class CView
{
public:
	CView();
	~CView();

	void OnViewType(UINT nID);

	UINT		mViewType;
	ViewVars*	VCam;

	geBoolean	mViewIs3d;
};

