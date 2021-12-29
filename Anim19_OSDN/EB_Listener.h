#pragma once
class EB_Listener
{
public:
	EB_Listener();
	~EB_Listener();

	bool RenderingQueued(const FrameEvent& evt); // Comes From Directly From Oger Render Listener [081221]
	bool frameStarted(const FrameEvent& evt); // Comes From Directly From Oger Render Listener [081221]

	int		Wheel;
	bool	Pl_LeftMouseDown;	// Triger Left Mouse Presed [081221]
	bool	Pl_RightMouseDown;	// Triger Right Mouse Presed [081221]

	bool	Show_Model_Data; // Show Model Data ImGui [081221]

	int		View_Height;	// Height of Render Window [081221]
	int		View_Width;		// Width of Render Window [081221]

	float		mMoveSensitivity;
	float		mMoveSensitivityMouse;

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
	

	float		Pl_DeltaMouse;
	int			Pl_MouseX;
	int			Pl_MouseY;

	POINT		Pl_pt;
	long		Pl_Cent500X;
	long		Pl_Cent500Y;

};

