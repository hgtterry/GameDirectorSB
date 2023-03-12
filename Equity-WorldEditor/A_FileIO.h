// A_FileIO.h: interface for the A_FileIO class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_A_FILEIO_H__9F7DDFC3_E8DA_4580_8C8D_6D8C4839E168__INCLUDED_)
#define AFX_A_FILEIO_H__9F7DDFC3_E8DA_4580_8C8D_6D8C4839E168__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class A_FileIO  
{
public:
	A_FileIO();
	virtual ~A_FileIO();

	bool Open_File_Model(char* Extension, char* Title, char* StartDirectory);

	bool SaveSelectedFile(char* Extension,char* TszFile);
	bool CheckExtention(char *FileName);


	char FileName[MAX_PATH];
	char PathFileName[MAX_PATH];

};

#endif // !defined(AFX_A_FILEIO_H__9F7DDFC3_E8DA_4580_8C8D_6D8C4839E168__INCLUDED_)
