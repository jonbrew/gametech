#ifndef __Physics_h_
#define __Physics_h_

#include <Ogre.h>
#include "btBulletDynamicsCommon.h"
#include "Sound.h"
#include "KinematicMotionState.h"

class Physics { 
protected:
    Sound* mSound;
    bool isCollidingWall;
    bool isCollidingPaddle;
    bool isCollidingGoal;
    btDefaultCollisionConfiguration* collisionConfiguration;
	btCollisionDispatcher* dispatcher;
	btBroadphaseInterface* overlappingPairCache;
	btSequentialImpulseConstraintSolver* solver;
    btDiscreteDynamicsWorld* dynamicsWorld;
	btAlignedObjectArray<btCollisionShape*> collisionShapes;

public:
    static const int TYPE_BALL = 0;
    static const int TYPE_WALL = 1;
    static const int TYPE_PADDLE = 2;
    static const int TYPE_GOAL_OFF = 3;
    static const int TYPE_GOAL_ON = 4;

    Physics(Sound* mSnd);
    void addObject(btRigidBody* b);
    void removeObject(btRigidBody* b);
    btAlignedObjectArray<btCollisionShape*>& getCollisionShapes(void) {return collisionShapes;}
    btDiscreteDynamicsWorld* getDynamicsWorld(void) {return dynamicsWorld;}
    bool stepSimulation(const Ogre::Real elapsedTime, 
        int maxSubSteps = 1, const Ogre::Real fixedTimestep = 1.0f/60.0f);
    bool handleCollisions(void); 
};

#endif
