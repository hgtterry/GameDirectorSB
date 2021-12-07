#pragma once
class EB_Listener
{
public:
	EB_Listener();
	~EB_Listener();

	bool WE_RenderingQueued(const FrameEvent& evt);
	bool frameStarted(const FrameEvent& evt);

	int		Wheel;
	bool	Pl_LeftMouseDown;
	bool	Pl_RightMouseDown;

	bool	Show_Model_Data;

	int		View_Height;
	int		View_Width;

	Ogre::Camera* WE_Cam;

protected:

	void ModelMode(float DeltaTime);
	void MoveCamera(void);

	bool Capture_LeftMouse_Model(void);
	bool Capture_RightMouse_Model(void);

	void ImGui_Model_Data(void);
	void Render_ImGui(void);

	Radian		mRotX;
	Radian		mRotY;
	Vector3		mTranslateVector;
	float		mMoveScale;
	float		mMoveSensitivity;

	float		Pl_DeltaMouse;
	int			Pl_MouseX;
	int			Pl_MouseY;

	POINT		Pl_pt;
	long		Pl_Cent500X;
	long		Pl_Cent500Y;

	float		mMoveSensitivityMouse;
};

