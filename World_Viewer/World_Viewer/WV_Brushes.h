#pragma once

class WV_Brushes
{
public:
	WV_Brushes();
	~WV_Brushes();

	BrushList* BrushList_CreateFromFile(Parse3dt* Parser, int VersionMajor, int VersionMinor, const char** Expected);
	Brush* Brush_CreateFromFile(Parse3dt* Parser, int VersionMajor, int VersionMinor, const char** Expected);

	int Get_Brush_Count();
	Brush* Get_Brush_ByIndex(int Index);

};

