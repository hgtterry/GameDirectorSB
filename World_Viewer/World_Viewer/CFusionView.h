#pragma once

#include "brush.h"
#include "render.h"
#include "resource.h"
//#include "fusiondoc.h"

typedef struct tag_EntityViewList EntityViewList;

enum dragtime
{
	DRAG_BEGIN,
	DRAG_CONTINUE,
	DRAG_END
};

class CFusionView
{
public:
	CFusionView();
	~CFusionView();

	UINT		mViewType;
	int			sides;
	ViewVars* VCam;

	void OnCenterthing();


	//void SetTool(int Tool);
	//void SetAdjustMode(fdocAdjustEnum Mode);
	//void SetModeTool(int Tool);
	//void SetTitle();
	//int GetTool(void);
	//fdocAdjustEnum GetAdjustMode(void);
	//int GetModeTool(void);
	//CFusionDoc* GetDocument();
};

