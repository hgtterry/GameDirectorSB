#include "stdafx.h"
#include "WV_App.h"
#include "CUtil.h"
#include "ram.h"

CUtil::CUtil()
{
}

CUtil::~CUtil()
{
}

// *************************************************************************
// * 							Util_Strdup								   *
// *************************************************************************
char* CUtil::Util_Strdup(const char* s)
{
	char* rslt;

	assert(s != NULL);

	rslt = (char*)geRam_Allocate(strlen(s) + 1);
	if (rslt != NULL)
	{
		strcpy(rslt, s);
	}
	return rslt;
}
