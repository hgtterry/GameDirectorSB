/*
Copyright (c) 2022 Equity_ME Model Editor -- HGT Software W.T.Flanigan H.C.Flanigan

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

#ifndef word
typedef unsigned short word;
#endif // word

typedef struct
{
	char    id[10];                                     // always "MS3D000000"
	int     version;                                    // 4
} Cms3d_header_t;

struct Cms3d_Vector3_t
{
	byte    flags;                                      // SELECTED | SELECTED2 | HIDDEN
	float   Vector3[3];                                  // x, y, z
	char    jointId;                                     // -1 = no joint
	byte    referenceCount;
};

struct Cms3d_triangle_t
{
	word    flags;                                      // SELECTED | SELECTED2 | HIDDEN
	word    Vector3Indices[3];                           //
	float   Vector3Normals[3][3];                        //
	float   s[3];                                       // texture coord s 
	float   t[3];                                       // texture coord t
	byte    smoothingGroup;                             // 1 - 32
	byte    groupIndex;                                 //
};

#pragma once
class ME_Export_Milkshape
{
public:
	ME_Export_Milkshape();
	~ME_Export_Milkshape();

	bool Export_To_Milk(bool DoMotions);

protected:

	bool Write_MILKFile_Assimp(void);
	void Write_MILKHeader(void);
	bool WriteMILKMesh_Assimp(void);

	char OutputFolder[MAX_PATH];

	FILE *WriteMILK;
};

