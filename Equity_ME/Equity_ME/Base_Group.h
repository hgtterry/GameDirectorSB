#pragma once
class Base_Group
{
public:
	Base_Group();
	~Base_Group();

	char GroupName[255];
	char MaterialName[255];
	char Text_FileName[255];			// Just Texture File Name ie Texture.bmp

	int GroupVertCount;
	int MaterialIndex;

	bool Bitmap_Loaded;

	HBITMAP Base_Bitmap;
};

