#ifndef DYNAMIC_CHARACTER_CONTROLLER_H
#define DYNAMIC_CHARACTER_CONTROLLER_H

#include <BulletDynamics/Dynamics/btActionInterface.h>
class btCapsuleShape;
class btRigidBody;

/**
 * Character controller for a rigid body with locked rotations.
 *
 * This class is hardcoded for Z-up characters.
 */
class DynamicCharacterController : public btActionInterface
{
public:


	// -------------------------------------------------- Terry

	bool Get_Height(void);
	
	
	DynamicCharacterController(btRigidBody *body, const btCapsuleShape *shape);

	virtual ~DynamicCharacterController() = default;

	void updateAction(btCollisionWorld *collisionWorld, btScalar deltaTimeStep);
	void debugDraw(btIDebugDraw *debugDrawer);

	
	void setMovementDirection(const btVector3 &walkDirection);

	
	const btVector3 &getMovementDirection() const;

	/// Reset the movement status, but not the position.
	void resetStatus();

	/// Tell if the character can jump
	bool canJump() const;

	
	void jump(const btVector3 &dir = btVector3(0, 0, 0));

	
	const btRigidBody *getBody() const;

	btScalar mMaxLinearVelocity2 = pow(15 / 3.6, 2);

	/// The acceleration to use when starting walking
	btScalar mWalkAccel = 25.0;

	btScalar mJumpSpeed = 14.5;

	/// The damp to use to stop movements
	btScalar mSpeedDamping = 0.1;

	/// The maximum step to automatically climb to
	btScalar mMaxStepHeight = 0.5;

	/// The speed to step stairs
	btScalar mSteppingSpeed = 3;

	/// The radius of the capsule
	btScalar mShapeRadius;

	/// Half of the height of the capsule
	btScalar mShapeHalfHeight;

	btVector3 mMoveDirection;
	btVector3 mGroundPoint;
	btVector3 mWorld_Height;

	bool Is_On_Ground = false;
	bool AddGravity = false;
	bool Player_CanJump;

	btVector3 mGravity;

	btScalar mMaxCosGround = -SIMDSQRT12;

	btScalar mRadiusThreshold = 1e-2;

protected:

	/**
	 * Default constructor, to be used by child classes.
	 * \warning The child classes must set the rigid body when using this, and
	 * set the shape dimensions.
	 */
	DynamicCharacterController();

	/// Setup the internally pointed body
	void setupBody();

	/**
	 * Update the character velocity
	 * \param dt The time elapsed since the last step
	 */
	void updateVelocity(float dt);

	/**
	 * Make the character step up stairs
	 * \param dt The time elapsed since the last step
	 */
	void stepUp(float dt);

	/// Cancel auto stepping
	inline void cancelStep();

	/// The controlled rigid body
	btRigidBody *mRigidBody;

	/**
	 * The walking direction. It must be an unitary vector or 0.
	 * It can be set through setWalkDirection, that will normalize, or child
	 * classes can set it directly, as long as they keep it normalized.
	 */
	

	/// Tell whether to jump at next update
	bool mJump;

	/// Tell the jump direction (should be normalized)
	btVector3 mJumpDir;

	/// Tell whether the character is on the ground
	

	/**
	 * The contact point of the character to ground
	 * This vector is valid only when mOnGround is true.
	 */


	/// Tells whether the character is auto stepping
	bool mStepping;

	/// Tells the point the character is stepping to
	btVector3 mSteppingTo;

	/// The normal of the step we are stepping to, seen from the stepping point
	btVector3 mSteppingInvNormal;

	/// Tells the flag to restore to make the character dynamic again after step
	int mPrestepFlags;
};

#endif
