#pragma once

typedef struct vertex_type4 { float x, y, z; }vertex_type4;
typedef struct polygon_type4 { int a, b, c, Group; }polygon_type4;
typedef struct mapcoord_type4 { float u, v; }mapcoord_type4;
typedef struct normal_type4 { float x, y, z; }normal_type4;
typedef struct TextID4 { int ID; }TextID4;

typedef struct Brush_type 
{ 
	std::vector<vertex_type4> vertex_Data;		// XYZ
	std::vector<polygon_type4> Face_Data;		// ABC
	std::vector<mapcoord_type4> MapCord_Data;	// UV
	std::vector<normal_type4> Normal_Data;		// XYZ
	std::vector<TextID4> TextID_Data;			// ID 

	int Vertice_Count;
	int Face_Count;

}Brush_type;

class Base_XBrush
{
public:
	Base_XBrush(void);
	~Base_XBrush(void);

	bool Create_Brush(int Index);

	Brush_type* B_Brush[112000];

	std::vector<vertex_type4> vertex_Data;		// XYZ
	std::vector<polygon_type4> Face_Data;		// ABC
	std::vector<mapcoord_type4> MapCord_Data;	// UV
	std::vector<normal_type4> Normal_Data;		// XYZ
	std::vector<TextID4> TextID_Data;			// ID 

	int Vertice_Count;
	int Face_Count;
	int SubBrush_Count;
	int Brush_Count;

	char BrushName[MAX_PATH];

};

