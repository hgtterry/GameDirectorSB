#pragma once

enum ViewTypes
{
	VIEWSOLID = 1,
	VIEWTEXTURE = 2,
	VIEWWIRE = 4,
	VIEWTOP = 8,
	VIEWFRONT = 16,
	VIEWSIDE = 32
};

enum
{
	GRID_TYPE_TEXEL,
	GRID_TYPE_METRIC
};

typedef struct EdgeTag Edge;
//typedef struct FPlane vPlane;

typedef struct SizeInfoTag
{
	long	TexWidth, TexHeight;
	long	ScreenWidth, ScreenHeight;
	Ogre::uint8* TexData, * ScreenData;
	Ogre::uint32* ZData;
} SizeInfo;

typedef struct ViewVarsTag
{
	struct
	{
		BITMAPINFOHEADER	bmiHeader;
		RGBQUAD				bmiColors[256];
	} ViewBMI;

	HBITMAP		hDibSec;
	Ogre::uint32		Flags;
	Ogre::uint8* pBits;
	Ogre::uint32* pZBuffer;
	Ogre::uint32		ViewType;
	geFloat	ZoomFactor;//, GridInterval;

	geVec3d		Vpn, Vright, Vup, CamPos;
	geFloat	roll, pitch, yaw;
	//FPlane	(FPlane*)FrustPlanes;
	geFloat	MaxScreenScaleInv, FieldOfView;
	geFloat	XCenter, YCenter, MaxScale;
	geFloat	SpeedScale, YScreenScale, XScreenScale;
	long		Width, Height;
	SizeInfo* WadSizes;
	Edge* NewEdges, ** RemoveEdges;
	long		FacesDone;
} ViewVars;

class CRender
{
public:
	CRender();
	~CRender();

	void Render_ResizeView(ViewVars* v, long vx, long vy);
	void Render_ResetSettings(ViewVars* v, long vx, long vy);

	void Render_SetZoom(ViewVars* v, const geFloat zf);
	void Render_SetViewType(ViewVars* v, const int vt);
	ViewVars* Render_AllocViewVars(void);
	void Render_SetWadSizes(ViewVars* v, SizeInfo* ws);

	int	Render_GetHeight(const ViewVars* v);
	int	Render_GetWidth(const ViewVars* v);
	int	Render_GetInidx(const ViewVars* v);

	geFloat	Render_GetFineGrid(const ViewVars* v, int GridType);
	geFloat Render_ComputeGridDist(const ViewVars* v, int GridType);

	
	void RenderOrthoView(ViewVars* v, HDC* pDC, HDC MemoryhDC);

	void Render_RenderOrthoGridFromSize(ViewVars* v, geFloat Interval, HDC ViewDC);
	void Render_ViewToWorld(const ViewVars* v, const int x, const int y, geVec3d* wp);
	POINT Render_OrthoWorldToView(const ViewVars* v, geVec3d const* wp);
};

