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

	void Collect_Object_Data(void);

	Ogre::Vector3			Physics_Pos;
	Ogre::Vector3			Physics_Rot;
	Ogre::Vector3			Physics_Scale;

	Ogre::Quaternion		Physics_Quat;

	int Type;
	int Shape;
	int Usage;
	int Folder;
	int Object_ID;  // Unique Number

	bool					Physics_Valid;
};

