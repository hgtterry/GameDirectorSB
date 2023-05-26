#include "stdafx.h"
#include "CBrushTemplate.h"

CBrushTemplate::CBrushTemplate()
{
}

CBrushTemplate::~CBrushTemplate()
{
}

// *************************************************************************
// * 						BrushTemplate_ArchDefaults					   *
// *************************************************************************
void CBrushTemplate::BrushTemplate_ArchDefaults(BrushTemplate_Arch* pArchTemplate)
{
	pArchTemplate->NumSlits = 3;
	pArchTemplate->Thickness = 150;
	pArchTemplate->Width = 100;
	pArchTemplate->Radius = 200;
	pArchTemplate->WallSize = 16;
	pArchTemplate->Style = 0;
	pArchTemplate->EndAngle = 180.0f;
	pArchTemplate->StartAngle = 0.0f;
	pArchTemplate->TCut = GE_FALSE;
	pArchTemplate->Sides = 3;
	pArchTemplate->CW = 0;
	pArchTemplate->Shape = 0;
	pArchTemplate->Radius2 = 64;
	pArchTemplate->Height = 0;
	pArchTemplate->Massive = GE_FALSE;
	pArchTemplate->Steps = GE_FALSE;
}

// *************************************************************************
// * 						BrushTemplate_BoxDefaults					   *
// *************************************************************************
void CBrushTemplate::BrushTemplate_BoxDefaults(BrushTemplate_Box* pBoxTemplate)
{
	pBoxTemplate->Solid = 1;		// hollow
	pBoxTemplate->TCut = GE_FALSE;
	pBoxTemplate->Thickness = 16.0f;
	pBoxTemplate->XSizeBot = 680.0f;
	pBoxTemplate->XSizeTop = 680.0f;
	pBoxTemplate->YSize = 360.0f;
	pBoxTemplate->ZSizeBot = 560.0f;
	pBoxTemplate->ZSizeTop = 560.0f;
}

// *************************************************************************
// * 						BrushTemplate_ConeDefaults					   *
// *************************************************************************
void CBrushTemplate::BrushTemplate_ConeDefaults(BrushTemplate_Cone* pConeTemplate)
{
	pConeTemplate->Style = 0;
	pConeTemplate->Width = 200;
	pConeTemplate->Height = 300;
	pConeTemplate->VerticalStrips = 4;
	pConeTemplate->Thickness = 16;
	pConeTemplate->TCut = GE_FALSE;
}

// *************************************************************************
// * 					BrushTemplate_CylinderDefaults					   *
// *************************************************************************
void CBrushTemplate::BrushTemplate_CylinderDefaults(BrushTemplate_Cylinder* pCylinderTemplate)
{
	pCylinderTemplate->BotXOffset = 0.0;
	pCylinderTemplate->BotXSize = 128.0;
	pCylinderTemplate->BotZOffset = 0.0;
	pCylinderTemplate->BotZSize = 128.0;
	pCylinderTemplate->Solid = 0;
	pCylinderTemplate->Thickness = 16.0;
	pCylinderTemplate->TopXOffset = 0.0;
	pCylinderTemplate->TopXSize = 128.0;
	pCylinderTemplate->TopZOffset = 0.0;
	pCylinderTemplate->TopZSize = 128.0;
	pCylinderTemplate->VerticalStripes = 6;
	pCylinderTemplate->YSize = 512.0;
	pCylinderTemplate->RingLength = 0.0;
	pCylinderTemplate->TCut = GE_FALSE;
}

// *************************************************************************
// * 					BrushTemplate_SpheroidDefaults					   *
// *************************************************************************
void CBrushTemplate::BrushTemplate_SpheroidDefaults(BrushTemplate_Spheroid* pSpheroidTemplate)
{
	pSpheroidTemplate->HorizontalBands = 4;
	pSpheroidTemplate->VerticalBands = 8;
	pSpheroidTemplate->YSize = 256.0;
	pSpheroidTemplate->Solid = 0;
	pSpheroidTemplate->Thickness = 16;
	pSpheroidTemplate->TCut = GE_FALSE;
}

// *************************************************************************
// * 					BrushTemplate_StaircaseDefaults					   *
// *************************************************************************
void CBrushTemplate::BrushTemplate_StaircaseDefaults(BrushTemplate_Staircase* pStaircaseTemplate)
{
	pStaircaseTemplate->Height = 128.0;
	pStaircaseTemplate->Length = 128.0;
	pStaircaseTemplate->NumberOfStairs = 8;
	pStaircaseTemplate->Width = 64.0;
	pStaircaseTemplate->MakeRamp = GE_FALSE;
	pStaircaseTemplate->TCut = GE_FALSE;
}
