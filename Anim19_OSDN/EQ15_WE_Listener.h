#pragma once
class EQ15_WE_Listener
{
public:
	EQ15_WE_Listener();
	~EQ15_WE_Listener();

	bool WE_RenderingQueued(const FrameEvent& evt);

	Ogre::Camera* WE_Cam;

protected:

	void ModelMode(float DeltaTime);
	void MoveCamera(void);


	Radian		mRotX;
	Radian		mRotY;
	Vector3		mTranslateVector;
	float		mMoveScale;
	float		mMoveSensitivity;

};

