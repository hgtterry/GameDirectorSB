#pragma once
class GD_Environment
{
public:
	GD_Environment(void);
	~GD_Environment(void);

	void Load_Environment(void);

protected:

	bool EnableFog();
	void SetSky(bool Enable);

	int SelectedProperties;

};

