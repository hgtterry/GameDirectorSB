#pragma once
class Base_Camera
{
public:
	Base_Camera();
	~Base_Camera();

	void Init_Camera(void);

	Ogre::Vector3 CamPos;
	Ogre::Vector3 LookAt;

	char Camera_Name[MAX_PATH];

	HTREEITEM FileViewItem;
};

