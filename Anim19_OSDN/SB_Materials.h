#pragma once
class SB_Materials
{
public:
	SB_Materials(void);
	~SB_Materials(void);

	void Start_Material_Editor();
	void Close_Material_Editor();

	void Material_Editor_Gui();

	bool Show_Material_Editor;

protected:

	void Update_MaterialFile();
	void Copy_Texture();

	int item_current_idx;

	char Material_FileName[MAX_PATH];
	Ogre::Entity* BaseEntity;

	Ogre::MaterialPtr  MatClone[10];
};

