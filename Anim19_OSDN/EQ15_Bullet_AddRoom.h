#pragma once
class EQ15_Bullet_AddRoom
{
public:
	EQ15_Bullet_AddRoom();
	~EQ15_Bullet_AddRoom();

	void AddToScene(void);
	bool Add_New_Room(void);

protected:
	btBvhTriangleMeshShape* create_New_Trimesh(Ogre::Entity* ent);
};

