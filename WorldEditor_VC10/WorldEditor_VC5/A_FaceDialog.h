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

	static geBoolean FlipHorizontal(Face *pFace, void *);
	static geBoolean FlipVertical(Face *pFace, void *);

	static geBoolean ChangeTextureAngle(Face *pFace, void *lParam);

	static geBoolean ChangeYOffset(Face *pFace, void *lParam);
	static geBoolean ChangeXOffset(Face *pFace, void *lParam);

	static geBoolean ChangeTextureYScale(Face *pFace, void *lParam);
	static geBoolean ChangeTextureXScale(Face *pFace, void *lParam);

	bool On_FlipHorizontal();
	void OnFlipvertical();

	void OnKillfocusAngle();

	void OnKillfocusYOffset();
	void OnKillfocusXOffset();

	void OnKillfocusYScale();
	void OnKillfocusXScale();

	void AssignCurrentToViews();

	void Fill_ComboBox_OffSetValues(HWND hDlg);
	void Fill_ComboBox_ScaleValues(HWND hDlg);
	void Fill_ComboBox_AngleValues(HWND hDlg);

	CString m_NumFaces;

	CFusionDoc			*m_pDoc;
};
