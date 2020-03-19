#pragma once
class GD_Keyboard
{
public:
	GD_Keyboard();
	~GD_Keyboard();

	void Keyboard_Monitor(float deltaTime);

	Ogre::Real Rate;
	Ogre::Vector3 OldPos;
	Ogre::Camera* mCamera;
};

