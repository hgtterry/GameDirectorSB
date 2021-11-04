// SB_App.h: interface for the SB_App class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SB_APP_H__32FF1015_03E8_4EB9_BE5C_D9E4748043B5__INCLUDED_)
#define AFX_SB_APP_H__32FF1015_03E8_4EB9_BE5C_D9E4748043B5__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class SB_App  
{
public:
	SB_App();
	virtual ~SB_App();

	void Say(const char* Message);

};

extern SB_App* App;

#endif // !defined(AFX_SB_APP_H__32FF1015_03E8_4EB9_BE5C_D9E4748043B5__INCLUDED_)
