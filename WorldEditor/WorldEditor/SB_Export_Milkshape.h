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

#include <pshpack1.h>

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

typedef struct
{
	byte            flags;                              // SELECTED | HIDDEN
	char            name[32];                           //
	word            numtriangles;                       //
	word			triangleIndices[65535];					// the groups group the triangles
	char            materialIndex;                      // -1 = no material
} Cms3d_group_t;

typedef struct
{
	char            name[32];                           //
	float           ambient[4];                         //
	float           diffuse[4];                         //
	float           specular[4];                        //
	float           emissive[4];                        //
	float           shininess;                          // 0.0f - 128.0f
	float           transparency;                       // 0.0f - 1.0f
	char            mode;                               // 0, 1, 2 is unused now
	char            texture[128];                        // texture.bmp
	char            alphamap[128];                       // alpha.bmp
} Cms3d_material_t;

#include <poppack.h>

class SB_Export_Milkshape
{
public:
	SB_Export_Milkshape();
	~SB_Export_Milkshape();

	bool Export_To_Milk(bool DoMotions);

private:

	bool Write_MILK_File(void);
	void Write_MILK_Header(void);
	void Convert_To_GlobalMesh(void);
	bool Write_MILK_Mesh(void);
	bool Write_MILK_Groups(void);
	bool Sort_Groups(void);
	bool Write_MILK_Texures(void);
	bool Get_Material_Name(int Loop);
	inline void SetVec4(float* target, float x, float y, float z, float w);

	char OutputFolder[MAX_PATH];
	char Text_FileName[MAX_PATH];
	char MaterialName[MAX_PATH];

	Cms3d_group_t* TGroup[200];

	FILE* WriteMILK;
};

