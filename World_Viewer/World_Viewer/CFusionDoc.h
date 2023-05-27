#pragma once

typedef geBoolean(*BrushFlagTest)(const Brush* pBrush);

class CFusionDoc
{
public:
	CFusionDoc();
	~CFusionDoc();

	bool Load(const char* FileName);

	Level* pLevel;
};

