#ifndef __Physics_h_
#define __Physics_h_

#include <Ogre.h>
#include "btBulletDynamicsCommon.h"
#include "Sound.h"
#include "KinematicMotionState.h"


class Physics { 
protected:
    Sound* mSound;
    bool isColliding;
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
    static const int TYPE_GOAL = 3;

    Physics(Sound* mSnd);
    ~Physics();
    void addObject(btRigidBody* b);
    void removeObject(btRigidBody* b);
    btAlignedObjectArray<btCollisionShape*>& getCollisionShapes(void) {return collisionShapes;}
    btDiscreteDynamicsWorld* getDynamicsWorld(void) {return dynamicsWorld;}
    void stepSimulation(const Ogre::Real elapsedTime, 
        int maxSubSteps = 1, const Ogre::Real fixedTimestep = 1.0f/60.0f);
    void handleCollisions(void); 
};

#endif
