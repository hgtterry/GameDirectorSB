// AB_Export_RFW.h: interface for the AB_Export_RFW class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_AB_EXPORT_RFW_H__A1009AFC_78B0_43E7_BCA5_5366946ED7A5__INCLUDED_)
#define AFX_AB_EXPORT_RFW_H__A1009AFC_78B0_43E7_BCA5_5366946ED7A5__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "level.h"
#include "entity.h"
#include "brush.h"
#include "model.h"
#include "group.h"
#include "wadfile.h"
#include "compiler.h"
#include "EntView.h"
#include "BrushTemplate.h"
#include "EntityTable.h"

typedef struct tag_Level2 Level2;

class AB_Export_RFW  
{
public:
	AB_Export_RFW();
	virtual ~AB_Export_RFW();

	bool Level_ExportTo_RFW(Level2 *pLevel, const char *Filename, BrushList *BList,int ExpSelected, geBoolean ExpLights, int GroupID);

};

#endif // !defined(AFX_AB_EXPORT_RFW_H__A1009AFC_78B0_43E7_BCA5_5366946ED7A5__INCLUDED_)
