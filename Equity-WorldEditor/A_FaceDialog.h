#pragma once

class A_FaceDialog
{
public:
	A_FaceDialog(void);
	~A_FaceDialog(void);

	void Start_FaceDialog();
	void UpdatePolygonFocus();
	void UpdateDialog(HWND hDlg);

	float	m_TextureAngle;

	float m_TextureXScale;
	float m_TextureYScale;

	int m_TextureYOffset;
	int m_TextureXOffset;

	bool f_FaceDlg_Active;

	HWND FaceDlg_Hwnd;

protected:

	static LRESULT CALLBACK FaceDialog_Proc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);

	static geBoolean FlipHorizontal3 (Face *pFace, void *);
	static geBoolean ChangeTextureAngle (Face *pFace, void *lParam);

	bool On_FlipHorizontal();
	void OnKillfocusAngle();

	void AssignCurrentToViews();

	CString m_NumFaces;

	CFusionDoc			*m_pDoc;
};
