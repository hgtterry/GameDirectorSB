#pragma once
class GD_Utilities
{
public:
	GD_Utilities(void);
	~GD_Utilities(void);

	bool Search_Folder_ForFile(char* Path,char* File);
	float DegreesToRadians(float Degrees);
	bool ReverseBackSlash(char *buf);
	Ogre::Vector3 Get_BoundingBox_World_Centre(int Object_Index);


	char Return_Chr[255];
};

