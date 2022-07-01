#pragma once
class ME_Dimensions
{
public:
	ME_Dimensions();
	~ME_Dimensions();

	void Centre_Model_Mid(void);
	void Centre_Model_Base(void);

	void ME_Dimensions::Rotate_X_Model(float X);
	void ME_Dimensions::Rotate_Y_Model(float Y);
	void ME_Dimensions::Rotate_Z_Model(float Z);

protected:

};

