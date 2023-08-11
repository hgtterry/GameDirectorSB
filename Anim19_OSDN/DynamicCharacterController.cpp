#include "stdafx.h"
#include "GD19_App.h"
#include "DynamicCharacterController.h"

#include <BulletCollision/CollisionDispatch/btCollisionWorld.h>
#include <BulletCollision/CollisionShapes/btCapsuleShape.h>
#include <BulletDynamics/Dynamics/btDynamicsWorld.h>
#include <BulletDynamics/Dynamics/btRigidBody.h>
#include <LinearMath/btDefaultMotionState.h>
#include <LinearMath/btIDebugDraw.h>

#include <cassert>

namespace {
class FindGroundAndSteps : public btCollisionWorld::ContactResultCallback {
public:
	FindGroundAndSteps(const DynamicCharacterController *controller,
		const btCollisionWorld *world);

	btScalar addSingleResult(btManifoldPoint &cp,
		const btCollisionObjectWrapper *colObj0, int partId0, int index0,
		const btCollisionObjectWrapper *colObj1, int partId1, int index1);
	btVector3 getInvNormal();

	bool mHaveGround = false;
	btVector3 mGroundPoint;
	bool mHaveStep = false;
	btVector3 mStepPoint;
	btVector3 mStepNormal;

private:
	void checkGround(const btManifoldPoint &cp);

	const DynamicCharacterController *mController;
	const btCollisionWorld *mWorld;

	btScalar mStepDist2;
};

class ResolveStepUp {
public:
	ResolveStepUp(const DynamicCharacterController *controller,
		const btCollisionWorld *world, const btManifoldPoint &cp);
	bool mIsStep = false;
	btVector3 mRealPosWorld;
	btScalar mDist2;

private:
	bool checkPreconditions();
	bool findRealPoint();
	bool canFit() const;

	const DynamicCharacterController *mController;
	const btCollisionWorld *mWorld;

	const btVector3 &mStepPos;
	const btVector3 &mStepNormal;
	const btTransform &mTransform;
	btScalar mOriginHeight;
	btVector3 mStepLocal;

	btScalar mNormalTolerance = 0.01;
	btScalar mStepSearchOvershoot = 0.01;
	btScalar mMinDot = 0.3;
};
}

DynamicCharacterController::DynamicCharacterController(btRigidBody *body,
	const btCapsuleShape *shape)
{
	mRigidBody = body;
	AddGravity = 0;
	//mShapeRadius = shape->getRadius();
	//mShapeHalfHeight = shape->getHalfHeight();

	Player_CanJump = 0;
	setupBody();
	resetStatus();
}

DynamicCharacterController::DynamicCharacterController()
{
	mRigidBody = nullptr;
	Player_CanJump = 0;
	resetStatus();
}

void DynamicCharacterController::setupBody()
{
	assert(mRigidBody);
	mRigidBody->setSleepingThresholds(0.0, 0.0);
	mRigidBody->setAngularFactor(0.0);
	mGravity = mRigidBody->getGravity();
}

// *************************************************************************
// *					Get_Height   Terry Bernie						   *
// *************************************************************************
bool DynamicCharacterController::Get_Height(void)
{

	App->CL_Ogre->OgreListener->DistanceToCollision = 0;

	Ogre::SceneNode* mNode;
	
	Vector3 FirstPos1 = Ogre::Vector3(mWorld_Height);
	Vector3 SecondPos1 = Ogre::Vector3(mWorld_Height.getX(), mWorld_Height.getY() -100, mWorld_Height.getZ());

	if (App->CL_Ogre->OgreListener->mCollisionTools->collidesWithEntity(FirstPos1, SecondPos1, 2.5f, 0, -1))
	{
		mNode = App->CL_Ogre->OgreListener->mCollisionTools->pentity->getParentSceneNode();

		App->CL_Ogre->OgreListener->Pl_Entity_Name = App->CL_Ogre->OgreListener->mCollisionTools->pentity->getName();
		App->CL_Ogre->OgreListener->DistanceToCollision = App->CL_Ogre->OgreListener->mCollisionTools->distToColl;

		if (App->CL_Ogre->OgreListener->DistanceToCollision > 12 && mJump == 0)
		{
			AddGravity = 1;
		}
		else
		{
			AddGravity = 0;
		}

		char buff[255];
		strcpy(buff, App->CL_Ogre->OgreListener->Pl_Entity_Name.c_str());

	}

	return 1;
}

// *************************************************************************
// *							updateAction							   *
// *************************************************************************
void DynamicCharacterController::updateAction(btCollisionWorld *collisionWorld,btScalar deltaTimeStep)
{
	Get_Height();
	FindGroundAndSteps groundSteps(this, collisionWorld);
	collisionWorld->contactTest(mRigidBody, groundSteps);

	Is_On_Ground = groundSteps.mHaveGround;
	mGroundPoint = groundSteps.mGroundPoint;
	mWorld_Height = mRigidBody->getWorldTransform().getOrigin();

	App->SBC_Markers->Move_Arrow(Ogre::Vector3(mWorld_Height));

	updateVelocity(deltaTimeStep);
	//if (mStepping || groundSteps.mHaveStep) {
	//	if (!mStepping) {
	//		mSteppingTo = groundSteps.mStepPoint;
	//		mSteppingInvNormal = groundSteps.getInvNormal();
	//	}
	//	stepUp(deltaTimeStep);
	//}

	/*if (mOnGround || mStepping) {
		mRigidBody->setGravity({ 0, 0, 0 });
	} else {
		mRigidBody->setGravity(mGravity);
	}*/
}

// *************************************************************************
// *							updateVelocity							   *
// *************************************************************************
void DynamicCharacterController::updateVelocity(float dt)
{
	btTransform transform;
	mRigidBody->getMotionState()->getWorldTransform(transform);
	btMatrix3x3 &basis = transform.getBasis();
	
	btMatrix3x3 inv = basis.transpose();

	btVector3 linearVelocity = inv * mRigidBody->getLinearVelocity();

	/*if (mMoveDirection.fuzzyZero() && mOnGround2) 
	{
		linearVelocity *= mSpeedDamping;
	} 
	else*/ 
	if (Is_On_Ground == 1 || mJump == 1)
	{
		btVector3 dv = mMoveDirection * (App->SBC_Scene->B_Player[0]->Ground_speed * dt);
		linearVelocity = dv;

		/*btScalar speed2 = pow(linearVelocity.x(), 2)+ pow(linearVelocity.y(), 2);
		if (speed2 > mMaxLinearVelocity2)
		{
			btScalar correction = sqrt(mMaxLinearVelocity2 / speed2);
			linearVelocity[0] *= correction;
			linearVelocity[1] *= correction;
		}*/
	}
	else
	{
		if (AddGravity == 1)
		{
			linearVelocity[1] = 100; 
		}
		else
		{
			linearVelocity[1] = 10;
		}
	}
	
	if (mJump)
	{
		Get_Height();
		linearVelocity += mJumpSpeed * mJumpDir;

		if (App->CL_Ogre->OgreListener->DistanceToCollision > 30)
		{
			mJump = false;
		}
		cancelStep();
	}

	mRigidBody->setLinearVelocity(basis * linearVelocity);
}

// *************************************************************************
// *								stepUp								   *
// *************************************************************************
void DynamicCharacterController::stepUp(float dt)
{
	//btTransform transform;
	//mRigidBody->getMotionState()->getWorldTransform(transform);

	//if (!mStepping) {
	//	mPrestepFlags = mRigidBody->getCollisionFlags();
	//	mRigidBody->setCollisionFlags(
	//		btCollisionObject::CF_KINEMATIC_OBJECT);
	//	mStepping = true;
	//	mSteppingTo[2] += mShapeHalfHeight + mShapeRadius;
	//}

	///* Bullet reacts with velocity also with kinematic bodies, althogh this
	//should not change anything, until we do not go back to dynamic body. */
	//btVector3 linearVelocity(0, 0, 0);

	//btVector3 &origin = transform.getOrigin();
	//btScalar hor = (origin - mSteppingTo).dot(mSteppingInvNormal);

	//btVector3 stepDir = mSteppingTo - origin;
	//stepDir.setZ(0);
	//stepDir.normalize();

	//btScalar speed = stepDir.dot(transform.getBasis() * mMoveDirection)
	//	* mSteppingSpeed;
	//origin[2] += speed * dt;
	//btScalar dv = mSteppingTo[2] - origin[2];

	//if (dv <= 0 || mMoveDirection.fuzzyZero() || speed <= 0) {
	//	if (dv <= 0) {
	//		origin[2] = mSteppingTo[2];
	//		linearVelocity = mMoveDirection * mSteppingSpeed * mSpeedDamping;
	//	}
	//	cancelStep();
	//} else if (dv < mShapeRadius) {
	//	// sqrt(r^2 - (r - dv)^2)
	//	btScalar dh = btSqrt(dv * (2 * mShapeRadius - dv));
	//	if (dh < fabs(hor)) {
	//		btScalar advance = std::min(copysignf(dh, hor) - hor, speed * dt);
	//		origin += mSteppingInvNormal * advance;
	//	}
	//}
	//mRigidBody->getMotionState()->setWorldTransform(transform);
	//mRigidBody->setLinearVelocity(transform.getBasis() * linearVelocity);
}

// *************************************************************************
// *								debugDraw							   *
// *************************************************************************
void DynamicCharacterController::debugDraw(btIDebugDraw *debugDrawer)
{
	/*if (mStepping) {
		debugDrawer->drawContactPoint(mSteppingTo, { 0, 0, 1 }, 0, 1000,{ 0, 0.3, 1 });
	}*/
}

// *************************************************************************
// *						setMovementDirection						   *
// *************************************************************************
void DynamicCharacterController::setMovementDirection(
	const btVector3 &walkDirection)
{
	mMoveDirection = walkDirection;
	mMoveDirection.setZ(0);
	if (!mMoveDirection.fuzzyZero()) {
		mMoveDirection.normalize();
	}
}

// *************************************************************************
// *						getMovementDirection()						   *
// *************************************************************************
const btVector3 &DynamicCharacterController::getMovementDirection() const
{
	return mMoveDirection;
}

// *************************************************************************
// *							resetStatus								   *
// *************************************************************************
void DynamicCharacterController::resetStatus()
{
	mMoveDirection.setValue(0, 0, 0);
	mJump = false;
	Is_On_Ground = false;
	cancelStep();
}

// *************************************************************************
// *							canJump									   *
// *************************************************************************
bool DynamicCharacterController::canJump() const
{
	return Is_On_Ground;
}

// *************************************************************************
// *							jump									   *
// *************************************************************************
void DynamicCharacterController::jump(const btVector3 &dir)
{

	if (Player_CanJump == 0)
	{
		return;
	}

	if (!canJump())
	{
		return;
	}

	mJump = true;

	mJumpDir = dir;
	if (dir.fuzzyZero()) {
		mJumpDir.setValue(0, -1, 0);
	}
	mJumpDir.normalize();
}

// *************************************************************************
// *							getBody									   *
// *************************************************************************
const btRigidBody *DynamicCharacterController::getBody() const
{
	return mRigidBody;
}

// *************************************************************************
// *							cancelStep								   *
// *************************************************************************
void DynamicCharacterController::cancelStep()
{
	if (mRigidBody) {
		if (mStepping) {
			mRigidBody->setCollisionFlags(mPrestepFlags);
		}
		// Sometimes when going back to rigid body there are strange effects
		mRigidBody->setAngularVelocity({ 0, 0, 0 });
	}
	mStepping = false;
}


// *****************************************************************************************************************
// *											FindGroundAndSteps Class			                           	   *
// *****************************************************************************************************************
namespace {
FindGroundAndSteps::FindGroundAndSteps(
	const DynamicCharacterController *controller, const btCollisionWorld *world)
{
	mController = controller;
	mWorld = world;
}

// *************************************************************************
// *				FindGroundAndSteps - addSingleResult				   *
// *************************************************************************
btScalar FindGroundAndSteps::addSingleResult(btManifoldPoint &cp,
	const btCollisionObjectWrapper *colObj0, int partId0, int index0,
	const btCollisionObjectWrapper *colObj1, int partId1, int index1)
{
	mGroundPoint = cp.m_positionWorldOnB;

	if (colObj0->m_collisionObject == mController->getBody()) {
		/* The first object should always be the rigid body of the
		controller, but check anyway.
		In case the body is the second object, we cannot use the collision
		information, because Bullet provides only the normal of the second
		point. */

		mHaveGround = 1;
		checkGround(cp);

		/*ResolveStepUp resolve(mController, mWorld, cp);
		if (resolve.mIsStep) {
			if (!mHaveStep || resolve.mDist2 < mStepDist2) {
				mStepPoint = resolve.mRealPosWorld;
				mStepNormal = cp.m_normalWorldOnB;
				mStepDist2 = resolve.mDist2;
			}
			mHaveStep = true;
		}*/
	}
	else
	{
		mHaveGround = 0;
	}

	// By looking at btCollisionWorld.cpp, it seems Bullet ignores this value
	return 0;
}

// *************************************************************************
// *				FindGroundAndSteps - checkGround					   *
// *************************************************************************
void FindGroundAndSteps::checkGround(const btManifoldPoint &cp)
{

	//App->SBC_DCC->Get_Height();
	mGroundPoint = cp.m_positionWorldOnB;
	//App->SBC_Grid->Move_Arrow(Ogre::Vector3(mGroundPoint));

	/*if (mHaveGround) {
		return;
	}*/

	/*btTransform inverse = mController->getBody()->getWorldTransform().inverse();
	btVector3 localPoint = inverse(cp.m_positionWorldOnB);
	localPoint[2] += mController->mShapeHalfHeight;

	float r = localPoint.length();
	float cosTheta = localPoint[2] / r;

	if (fabs(r - mController->mShapeRadius) <= mController->mRadiusThreshold && cosTheta < mController->mMaxCosGround)
	{
		mHaveGround = true;
		mGroundPoint = cp.m_positionWorldOnB;
	}*/
}

// *************************************************************************
// *				FindGroundAndSteps - getInvNormal					   *
// *************************************************************************
btVector3 FindGroundAndSteps::getInvNormal()
{
	if (!mHaveStep) {
		return btVector3(0, 0, 0);
	}

	btMatrix3x3 frame;
	// Build it as step to world
	frame[2].setValue(0, 0, 1);
	frame[1] = mStepNormal;
	frame[0] = frame[1].cross(frame[2]);
	frame[0].normalize();
	// Convert it to world to step
	frame = frame.transpose();
	return frame[1];
}

// *************************************************************************
// *				FindGroundAndSteps - ResolveStepUp					   *
// *************************************************************************
ResolveStepUp::ResolveStepUp(const DynamicCharacterController *controller,
	const btCollisionWorld *world, const btManifoldPoint &cp) :
	mStepPos(cp.m_positionWorldOnB), mStepNormal(cp.m_normalWorldOnB),
	mTransform(controller->getBody()->getWorldTransform())
{
	mController = controller;
	mWorld = world;
	mOriginHeight = mController->mShapeHalfHeight + mController->mShapeRadius;

	mIsStep = checkPreconditions() && findRealPoint() && canFit();
	if (mIsStep) {
		btVector3 origin = mTransform.getOrigin();
		origin[2] -= mOriginHeight;
		mDist2 = origin.distance2(mRealPosWorld);
	}
}

// *************************************************************************
// *				FindGroundAndSteps - checkPreconditions				   *
// *************************************************************************
bool ResolveStepUp::checkPreconditions()
{
	if (mController->getMovementDirection().fuzzyZero()) {
		return false;
	}

	/* A step has little vertical component in its normal.
	 * This strategy is not perfect, as it does not work with end points of the
	 * ramps, but I do not have a solution for this, at the moment.
	 *
	 * Nice trick by https://cobertos.com/blog/post/how-to-climb-stairs-unity3d/
	 */
	if (fabs(mStepNormal.z()) > mNormalTolerance) {
		return false;
	}
	/* We can step only when we are on ground, but since while we are doing
	this check the characater cannot move, if we consider the lowest point of
	the capsule as center, we have a constant error, that might be negligible.
	On the other hand, we could also just store the various collisions and use
	the correct ground point after we detected it. */
	const btVector3 &origin = mTransform.getOrigin();
	{
		btScalar approximateHeight = mStepPos.z() - origin.z()
			+ mOriginHeight;
		if (approximateHeight >= mController->mMaxStepHeight) {
			return false;
		}
	}

	btTransform toLocal = mTransform.inverse();
	/* Don't step if it's in a direction opposite to our movement.
	 * This is a quick test, but likely not enough accurate. */
	mStepLocal = toLocal(mStepPos);
	if (mStepLocal.fuzzyZero()) {
		return false;
	}
	btVector3 stepDir = mStepLocal / mStepLocal.length();
	if (stepDir.dot(mController->getMovementDirection()) < mMinDot) {
		return false;
	}

	btCollisionWorld::ClosestRayResultCallback callback(origin, mStepPos);
	mWorld->rayTest(origin, mStepPos, callback);
	if (callback.hasHit()
			&& (1 - callback.m_closestHitFraction) > SIMD_EPSILON) {
		return false;
	}

	return true;
}

// *************************************************************************
// *				FindGroundAndSteps - findRealPoint					   *
// *************************************************************************
bool ResolveStepUp::findRealPoint()
{
	/* Look for the real height of the step.
	 * Move a bit along the ground-collision direction, horizontally,
	 * and vertically use 0 and the max step height. */
	btVector3 minTargetPoint(mStepLocal[0], mStepLocal[1], 0);
	minTargetPoint *= 1 + mStepSearchOvershoot / minTargetPoint.length();
	// As above: we are using capsule lowest point, rather than ground
	minTargetPoint[2] -= mOriginHeight;

	btVector3 maxTargetPoint = minTargetPoint;
	maxTargetPoint[2] += mController->mMaxStepHeight + mStepSearchOvershoot;
	minTargetPoint = mTransform(minTargetPoint);
	maxTargetPoint = mTransform(maxTargetPoint);

	btCollisionWorld::ClosestRayResultCallback callback(maxTargetPoint,
		minTargetPoint);
	mWorld->rayTest(maxTargetPoint, minTargetPoint, callback);
	if (!callback.hasHit()) {
		return false;
	}
	if ((btScalar(1) - callback.m_closestHitFraction) < SIMD_EPSILON) {
		// Almost at the minimum point, can walk normally
		return false;
	}

	mRealPosWorld = callback.m_hitPointWorld;
	return true;
}

// *************************************************************************
// *					FindGroundAndSteps - canFit						   *
// *************************************************************************
bool ResolveStepUp::canFit() const
{
	// Not very robust test, but still better than nothing
	btVector3 horFrom = mRealPosWorld;
	horFrom[2] += mOriginHeight;
	btVector3 horTo(mStepLocal[0], mStepLocal[1], 0);
	horTo *= mController->mShapeRadius / horTo.length();
	horTo = horFrom + mTransform.getBasis() * horTo;
	const btVector3 &vertFrom = mRealPosWorld;
	btVector3 vertTo = horFrom;
	vertTo[2] += mOriginHeight;

	{
		btCollisionWorld::ClosestRayResultCallback callback(vertFrom, vertTo);
		mWorld->rayTest(vertFrom, vertTo, callback);
		if (callback.hasHit()) {
			return false;
		}
	}

	{
		btCollisionWorld::ClosestRayResultCallback callback(horFrom, horTo);
		mWorld->rayTest(horFrom, horTo, callback);
		if (callback.hasHit()) {
			return false;
		}
	}

	return true;
}
}
