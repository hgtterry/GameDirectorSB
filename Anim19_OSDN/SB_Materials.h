#pragma once
class SB_Materials
{
public:
	SB_Materials(void);
	~SB_Materials(void);

	void Start_Material_Editor();
	void Close_Material_Editor();

	void Material_Editor_Gui();

	void Get_Material_Name(Ogre::Entity* mEntity);

	bool Show_Material_Editor;

protected:

	void Update_MaterialFile();
	void Copy_Texture();

	void Scroll_Gui();

	bool Show_Scroll_Editor;
	int item_current_idx;

	char Material_FileName[MAX_PATH];
	Ogre::Entity* BaseEntity;

	Ogre::MaterialPtr MatCurent;
	
	std::vector<MaterialPtr> MatClone;
};

