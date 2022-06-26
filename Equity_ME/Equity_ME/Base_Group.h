#pragma once

typedef struct vertex_type
{
	float x, y, z;
}vertex_type;

typedef struct polygon_type { int a, b, c, Group; }polygon_type;
typedef struct normal_type { float x, y, z; }normal_type;
typedef struct mapcoord_type { float u, v; }mapcoord_type;
typedef struct int_type { int Index; }int_type;

class Base_Group
{
public:
	Base_Group();
	~Base_Group();

	char GroupName[255];
	char MaterialName[255];
	char Text_FileName[255];			// Just Texture File Name ie Texture.bmp

	char Texture_FolderPath[MAX_PATH];
	char Texture_PathFileName[MAX_PATH];

	int GroupVertCount;	// Group Vertice Count
	int GroupFaceCount;

	int MaterialIndex;

	
	bool Bitmap_Loaded;

	std::vector<vertex_type> vertex_Data;		// XYZ
	std::vector<polygon_type> Face_Data;		// ABC
	std::vector<normal_type> Normal_Data;		// XYZ
	std::vector<mapcoord_type> MapCord_Data;	// UV
	std::vector<int_type> FaceIndex_Data;

	HBITMAP Base_Bitmap;

	HTREEITEM ListView_Item;
};

