#pragma once
//#include "basetype.h"
//#include "vec3d.h"

struct tag_Box3d
{
	geVec3d Min;
	geVec3d Max;
};

typedef struct tag_Box3d Box3d;

class CBox3d
{
public:
	CBox3d();
	~CBox3d();

	void Box3d_Set(Box3d* b, geFloat x1, geFloat y1, geFloat z1, geFloat x2, geFloat y2, geFloat z2);
	void Box3d_SetBogusBounds(Box3d* b);
	void Box3d_AddPoint(Box3d* b, geFloat px, geFloat py, geFloat pz);
	void Box3d_Union(const Box3d* b1, const Box3d* b2, Box3d* bResult);
};

