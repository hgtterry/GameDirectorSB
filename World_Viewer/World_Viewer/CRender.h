#pragma once

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


	void Render_RenderOrthoGridFromSize(ViewVars* v, geFloat Interval, HDC ViewDC);
};

