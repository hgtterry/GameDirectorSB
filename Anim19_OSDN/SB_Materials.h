#pragma once
class SB_Materials
{
public:
	SB_Materials(void);
	~SB_Materials(void);

	void Start_Material_Editor();
	void Material_Editor_Gui();

	bool Show_Material_Editor;

	Ogre::Entity* BaseEntity;
};

