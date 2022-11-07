#include "StdAfx.h"
#include "BT_App.h"
#include "GD_Utilities.h"


GD_Utilities::GD_Utilities(void)
{
	Return_Chr[0] = 0;
}


GD_Utilities::~GD_Utilities(void)
{
}

// *************************************************************************
// *					Search_Folder_ForFile Terry Bernie			 	   *
// *************************************************************************
bool GD_Utilities::Search_Folder_ForFile(char* Path,char* File)
{
	char pSearchPath[1024];

	WIN32_FIND_DATA FindFileData;
	HANDLE hFind;

	strcpy(pSearchPath,Path);
	strcat(pSearchPath,File);
	
	hFind = FindFirstFile(pSearchPath, &FindFileData);
	if(hFind == INVALID_HANDLE_VALUE) 
	{
		return 0;
	}
	else
	{
		FindClose(hFind);
		return 1;
	}

	return 0;
}

// *************************************************************************
// *				ReverseBackSlash  Terry Bernie				  	 	   *
// *************************************************************************
bool GD_Utilities::ReverseBackSlash(char *buf)
{
	strcpy(Return_Chr,"");
	char bufnew[256];
	strcpy(bufnew,"");
	char seps[]   = "\\";
	char *token;
	bool tt = 0;

	token = strtok(buf, seps );
	while( token != NULL )
	{
		tt = 1;
		strcat(bufnew,token);
		strcat(bufnew,"/");
		token = strtok( NULL, seps );
	}

	if(tt == 1)
	{
		int len=strlen(bufnew);
		bufnew[len-1]=0;
		strcpy(Return_Chr,bufnew);
	}
	else
	{
		tt = 0;
		strcpy(Return_Chr,buf);
	}
	return 1;
}

// *************************************************************************
// *					DegreesToRadians Terry	Bernie					   *
// *************************************************************************
float GD_Utilities::DegreesToRadians(float Degrees)
{
	float Radians = 0;//(Degrees * GE_PI)/180;
	return Radians;
}

// *************************************************************************
//					Get_BoundingBox_World_Centre Terry Bernie			   *
// *************************************************************************
Ogre::Vector3 GD_Utilities::Get_BoundingBox_World_Centre(int Object_Index)
{
	AxisAlignedBox worldAAB = App->GDCL_Scene_Data->S_Object[Object_Index]->OgreEntity->getBoundingBox();
	worldAAB.transformAffine( App->GDCL_Scene_Data->S_Object[Object_Index]->OgreNode->_getFullTransform() );
	Ogre::Vector3 Centre = worldAAB.getCenter();

	return Centre;
}