#pragma once
class EQ15_WE_Listener
{
public:
	EQ15_WE_Listener();
	~EQ15_WE_Listener();

	bool WE_RenderingQueued(const FrameEvent& evt);

	int			Wheel;
	bool		Pl_LeftMouseDown;
	bool		Pl_RightMouseDown;

	Ogre::Camera* WE_Cam;

protected:

	void ModelMode(float DeltaTime);
	void MoveCamera(void);

	bool Capture_LeftMouse_Model(void);
	bool Capture_RightMouse_Model(void);

	Radian		mRotX;
	Radian		mRotY;
	Vector3		mTranslateVector;
	float		mMoveScale;
	float		mMoveSensitivity;

	float		Pl_DeltaMouse;
	int Pl_MouseX;
	int Pl_MouseY;

	POINT		Pl_pt;
	long		Pl_Cent500X;
	long		Pl_Cent500Y;

	float		mMoveSensitivityMouse;

};

