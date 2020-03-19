#pragma once
class GD19_Player
{
public:
	GD19_Player(void);
	~GD19_Player(void);

	void Initialize_New(const Ogre::Vector3 p, float mass, float radius, float height);

	void SetUp(void);
	void Load_Player(void);

	void Move_Right(void);
	void Move_Left(void);

	void Stop(void);
	void Forward(float delta);
	void Back(void);
	void Rotate(const Ogre::Vector3 axis,bool normalize);
	void Rotate_FromCam(const Ogre::Vector3 axis, float delta, bool normalize);
	void Jump(const Ogre::Vector3 axis, float force);
	bool OnGround() const;

	void Adjust_Capsule(void);

	void PostStep(btCollisionWorld *collisionWorld);
	void Check_Collisions(void);

	void Save_Location(char* name);
	void Goto_Location(int Index);

	btRigidBody *mObject;
	btCollisionShape *mShape;

	Ogre::Camera*		CameraPitch;
	Ogre::Entity*		Player_Ent; 
	Ogre::SceneNode*	Player_Node;

	char PlayerName[255];
	bool mOnGround;
	bool IsMOving;
	bool IsMOving_Back;
	bool IsMOving_Right;
	bool IsMOving_Left;

	int Round;
	float Distance;
	int Life_Time;
	int ColisionIndex;
	int Last_ColisionIndex;

	Ogre::Vector3 StartPos;

	bool is_Animated;

	bool ShowDebug;
	bool PlayerAdded;
	float Ground_speed;

	float PlayerHeight;
	float TurnRate;

	float Capsule_Mass;
	float Capsule_Radius;
	float Capsule_Height;

	float Forward_Timer;

	// Strucure to be
	Ogre::Vector3 Current_Position;
	btVector3 Physics_Position;
	btQuaternion Physics_Rotation;

	HTREEITEM ListViewItem;


protected:

	void Initialize(const Ogre::Vector3 p, float mass, float radius, float height);

};

// --------------------------------------
class ClosestNotMeRayResultCallback : public btCollisionWorld::ClosestRayResultCallback {
public:
	ClosestNotMeRayResultCallback(btCollisionObject *self)
		: btCollisionWorld::ClosestRayResultCallback(btVector3(0, 0, 0), btVector3(0., 0., 0))
		, mSelf(self) {}

	virtual btScalar addSingleResult(btCollisionWorld::LocalRayResult &rayResult, bool normalInWorldSpace) {
		if(rayResult.m_collisionObject == mSelf) 
			return 1.0;
		return ClosestRayResultCallback::addSingleResult(rayResult, normalInWorldSpace);
	}
protected:
	btCollisionObject *mSelf;
};

// ==============================

class ClosestNotMeConvexResultCallback : public btCollisionWorld::ClosestConvexResultCallback {
public:
 ClosestNotMeConvexResultCallback(btCollisionObject *self, const btVector3 &up, btScalar minSlopeDot)
 : btCollisionWorld::ClosestConvexResultCallback(btVector3(0.0, 0.0, 0.0), btVector3(0.0, 0.0, 0.0))
 , mSelf(self) , mUp(up) , mMinSlopeDot(minSlopeDot) {}

 virtual btScalar addSingleResult(btCollisionWorld::LocalConvexResult &convexResult, bool normalInWorldSpace) {
  if(convexResult.m_hitCollisionObject == mSelf)
   return btScalar(1.0);

  btVector3 hitNormalWorld;
  if(normalInWorldSpace) {
   hitNormalWorld = convexResult.m_hitNormalLocal;
  } else {
   hitNormalWorld = convexResult.m_hitCollisionObject->getWorldTransform().getBasis() * convexResult.m_hitNormalLocal;
  }
#if 0
  btScalar dotUp = mUp.dot(hitNormalWorld);
  if(dotUp < mMinSlopeDot) {
   return btScalar(1.0);
  }
#endif
  return ClosestConvexResultCallback::addSingleResult(convexResult, normalInWorldSpace);
 }
protected:
 btCollisionObject *mSelf;
 const btVector3 mUp;
 btScalar mMinSlopeDot;
};


