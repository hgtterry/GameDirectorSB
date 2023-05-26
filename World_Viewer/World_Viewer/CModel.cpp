#include "stdafx.h"
#include "WV_App.h"
#include "CModel.h"

CModel::CModel()
{
}

CModel::~CModel()
{
}

// *************************************************************************
// * 						Level_Create								   *
// *************************************************************************
ModelList* CModel::ModelList_Create(void)
{
	return App->CL_CList->List_Create();
}
