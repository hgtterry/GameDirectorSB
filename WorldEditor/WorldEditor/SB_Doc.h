#pragma once
class SB_Doc
{
public:
	SB_Doc(void);
	~SB_Doc(void);

	bool DeleteSelectedBrushes();
	void DeleteCurrentThing();
	void DeleteEntity(int EntityIndex);

};

