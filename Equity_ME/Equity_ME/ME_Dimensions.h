#pragma once
class ME_Dimensions
{
public:
	ME_Dimensions();
	~ME_Dimensions();

	void Centre_Model_Mid(void);
	void Centre_Model_Base(void);

	void Rotate_X_Model(float X);
	void Rotate_Y_Model(float Y);
	void Rotate_Z_Model(float Z);

	void Translate_Model(float X, float Y, float Z);

	float Model_X_Rotation;
	float Model_Y_Rotation;
	float Model_Z_Rotation;

	float Model_X_Position;
	float Model_Y_Position;
	float Model_Z_Position;

protected:

};

