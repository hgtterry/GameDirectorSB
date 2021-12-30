// SB_App.h: interface for the SB_App class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SB_APP_H__F1CE337E_1C46_4F80_9639_566F8F7DFBD6__INCLUDED_)
#define AFX_SB_APP_H__F1CE337E_1C46_4F80_9639_566F8F7DFBD6__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000



#include "AB_Export_RFW.h"

class AB_App  
{
public:

	AB_Export_RFW*			ABC_Export_RFW;


	AB_App();
	virtual ~AB_App();

	bool AB_App::InitApp(void);
	void Say(const char* Message);

};

extern AB_App* App;

#endif // !defined(AFX_SB_APP_H__F1CE337E_1C46_4F80_9639_566F8F7DFBD6__INCLUDED_)