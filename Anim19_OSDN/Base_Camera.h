#pragma once
class Base_Camera
{
public:
	Base_Camera();
	~Base_Camera();

	void Init_Camera(void);

	Ogre::Vector3 CamPos;
	Ogre::Vector3 LookAt;

	Ogre::Quaternion Cam_Quat;

	char Camera_Name[MAX_PATH];

	HTREEITEM FileViewItem;
};

