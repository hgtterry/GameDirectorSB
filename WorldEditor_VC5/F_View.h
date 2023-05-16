#pragma once

/*
Copyright (c) 2023 World Editor -- HGT Software W.T.Flanigan H.C.Flanigan

This software is provided 'as-is', without any express or implied
warranty. In no event will the authors be held liable for any damages
arising from the use of this software.

Permission is granted to anyone to use this software for any purpose,
including commercial applications, and to alter it and redistribute it
freely, subject to the following restrictions:

1. The origin of this software must not be misrepresented; you must not
claim that you wrote the original software. If you use this software
in a product, an acknowledgment in the product documentation would be
appreciated but is not required.

2. Altered source versions must be plainly marked as such, and must not be
misrepresented as being the original software.

3. This notice may not be removed or altered from any source
distribution.
*/

class F_View
{
public:
	F_View(void);
	~F_View(void);

	void OnDraw(UINT mViewType, ViewVars* VCam, CDC* c);

	void Blit(ViewVars *VCam,CDC *c);

	void Blit_New(ViewVars *VCam, CDC *c);
	void RenderOrthoView(ViewVars *v, CDC *pDC, HDC MemoryhDC); // hgtterry Render to views

	static geBoolean BrushDraw2( Brush *pBrush, void *lParam);
	void Render_RenderBrushFacesOrtho( const ViewVars *Cam, Brush *b, HDC ViewDC);
	POINT F_View::Render_OrthoWorldToView(const ViewVars *v, geVec3d const *wp);

	CFusionDoc			*m_pDoc;

	HPEN	PenAllItems2;
	HPEN	PenCutBrush2;
	HPEN	PenDetailBrush2;
	HPEN	PenSelected2;
	HPEN	PenTemplate2;
	HPEN	PenHintBrush2;
	HPEN	PenClipBrush2;
	HPEN	PenSheetFaces2;
	HPEN	PenSelectedFaces2;
	HPEN	PenCamera2;
};
