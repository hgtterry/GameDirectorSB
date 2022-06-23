#pragma once
class Base_Group
{
public:
	Base_Group();
	~Base_Group();

	char GroupName[255];
	char MaterialName[255];

	bool Bitmap_Loaded;

	HBITMAP Base_Bitmap;
};

