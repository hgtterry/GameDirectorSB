#pragma once

class CFusionDoc
{
public:
	CFusionDoc();
	~CFusionDoc();

	bool Load(const char* FileName);

	Level* pLevel;
};

