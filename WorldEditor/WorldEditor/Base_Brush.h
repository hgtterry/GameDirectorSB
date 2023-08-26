#pragma once

typedef struct vertex_type3{ float x, y, z; }vertex_type3;
typedef struct polygon_type3{ int a, b, c, Group; }polygon_type3;
typedef struct mapcoord_type3 { float u, v; }mapcoord_type3;
typedef struct normal_type3 { float x, y, z; }normal_type3;

class Base_Brush
{
public:
	Base_Brush();
	~Base_Brush();

	std::vector<vertex_type3> vertex_Data;		// XYZ
	std::vector<polygon_type3> Face_Data;		// ABC
	std::vector<mapcoord_type3> MapCord_Data;	// UV
	std::vector<normal_type3> Normal_Data;		// XYZ

	int Vertice_Count;
	int Face_Count;
};

