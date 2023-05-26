#pragma once

typedef List ModelList;

struct ModelInfo_Type
{
	int CurrentModel;
	ModelList* Models;
};

class CModel
{
public:
	CModel();
	~CModel();

	ModelList* ModelList_Create(void);
};

