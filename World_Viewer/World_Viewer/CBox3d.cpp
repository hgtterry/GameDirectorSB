#include "stdafx.h"
#include "CBox3d.h"

CBox3d::CBox3d()
{
}

CBox3d::~CBox3d()
{
}

// *************************************************************************
// * 							Box3d_Set								   *
// *************************************************************************
void CBox3d::Box3d_Set(Box3d* b, geFloat x1, geFloat y1, geFloat z1, geFloat x2, geFloat y2, geFloat z2)
{
	assert(b != NULL);

	geVec3d_Set
	(
		&b->Min,
		std::min(x1, x2),
		std::min(y1, y2),
		std::min(z1, z2)
	);
	geVec3d_Set
	(
		&b->Max,
		std::max(x1, x2),
		std::max(y1, y2),
		std::max(z1, z2)
	);
}


// *************************************************************************
// * 							Box3d_Set								   *
// *************************************************************************
void CBox3d::Box3d_SetBogusBounds(Box3d* b)
{
	assert(b != NULL);

	geVec3d_Set(&b->Min, FLT_MAX, FLT_MAX, FLT_MAX);
	geVec3d_Set(&b->Max, -FLT_MAX, -FLT_MAX, -FLT_MAX);
}

// *************************************************************************
// * 							Box3d_AddPoint							   *
// *************************************************************************
void CBox3d::Box3d_AddPoint(Box3d* b,geFloat px,geFloat py,geFloat pz)
{
	if (px < b->Min.X) b->Min.X = px;
	if (px > b->Max.X) b->Max.X = px;
	if (py < b->Min.Y) b->Min.Y = py;
	if (py > b->Max.Y) b->Max.Y = py;
	if (pz < b->Min.Z) b->Min.Z = pz;
	if (pz > b->Max.Z) b->Max.Z = pz;
}

// *************************************************************************
// * 							Box3d_Union								   *
// *************************************************************************
void CBox3d::Box3d_Union(const Box3d* b1,const Box3d* b2,Box3d* bResult)
{
	assert(Box3d_IsValid(b1));
	assert(Box3d_IsValid(b2));
	assert(bResult != NULL);

	Box3d_Set
	(
		bResult,
		std::min(b1->Min.X, b2->Min.X),
		std::min(b1->Min.Y, b2->Min.Y),
		std::min(b1->Min.Z, b2->Min.Z),
		std::max(b1->Max.X, b2->Max.X),
		std::max(b1->Max.Y, b2->Max.Y),
		std::max(b1->Max.Z, b2->Max.Z)
	);
}
