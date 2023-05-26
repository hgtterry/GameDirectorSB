#pragma once

typedef struct
{
	int			NumSlits;
	geFloat		Thickness;
	geFloat		Width;
	geFloat		Radius;
	geFloat		WallSize;
	int			Style;
	geFloat		EndAngle;
	geFloat		StartAngle;
	geBoolean	TCut;
	// changed QD 11/03
	int			Sides;
	int			CW;
	int			Shape;
	geFloat		Radius2;
	geFloat		Height;
	geBoolean	Massive;
	geBoolean	Steps;
	// end change
} BrushTemplate_Arch;


typedef struct
{
	int			Solid;
	geBoolean	TCut;
	geBoolean	TSheet;
	geFloat		Thickness;
	geFloat		XSizeTop;
	geFloat		XSizeBot;
	geFloat		YSize;
	geFloat		ZSizeTop;
	geFloat		ZSizeBot;
} BrushTemplate_Box;

typedef struct
{
	int			Style;
	geFloat		Width;
	geFloat		Height;
	int			VerticalStrips;
	geFloat		Thickness;
	geBoolean	TCut;
} BrushTemplate_Cone;

typedef struct
{
	geFloat		BotXOffset;
	geFloat		BotXSize;
	geFloat		BotZOffset;
	geFloat		BotZSize;
	int			Solid;
	geFloat		Thickness;
	geFloat		TopXOffset;
	geFloat		TopXSize;
	geFloat		TopZOffset;
	geFloat		TopZSize;
	int			VerticalStripes;
	geFloat		YSize;
	geFloat		RingLength;
	geBoolean	TCut;
} BrushTemplate_Cylinder;

typedef struct
{
	int			HorizontalBands;
	int			VerticalBands;
	geFloat		YSize;
	int			Solid;
	geFloat		Thickness;
	geBoolean	TCut;
} BrushTemplate_Spheroid;

typedef struct
{
	geFloat		Height;
	geFloat		Length;
	int			NumberOfStairs;
	geFloat		Width;
	geBoolean	MakeRamp;
	geBoolean	TCut;
} BrushTemplate_Staircase;

class CBrushTemplate
{
public:
	CBrushTemplate();
	~CBrushTemplate();

	void BrushTemplate_ArchDefaults(BrushTemplate_Arch* pArchTemplate);
	void BrushTemplate_BoxDefaults(BrushTemplate_Box* pBoxTemplate);
	void BrushTemplate_ConeDefaults(BrushTemplate_Cone* pConeTemplate);
	void BrushTemplate_CylinderDefaults(BrushTemplate_Cylinder* pCylinderTemplate);
	void BrushTemplate_SpheroidDefaults(BrushTemplate_Spheroid* pSpheroidTemplate);
	void BrushTemplate_StaircaseDefaults(BrushTemplate_Staircase* pStaircaseTemplate);
};

