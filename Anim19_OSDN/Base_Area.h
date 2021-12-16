#pragma once
class Base_Area
{
public:
	Base_Area();
	~Base_Area();

	Ogre::Entity*		Area_Ent;
	Ogre::SceneNode*	Area_Node;

	btRigidBody *mObject;
	btCollisionShape *mShape;
};

