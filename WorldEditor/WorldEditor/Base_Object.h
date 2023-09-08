#pragma once
class Base_Object
{
public:
	Base_Object(void);
	~Base_Object(void);

	Ogre::SceneNode* Object_Node;
	Ogre::Entity* Object_Ent;
	btRigidBody* Phys_Body;
	btCollisionShape* Phys_Shape;
};

