#ifndef __Physics_h_
#define __Physics_h_

#include <Ogre.h>
#include "btBulletDynamicsCommon.h"


class Physics { 
protected: 
    btDefaultCollisionConfiguration* collisionConfiguration;
	btCollisionDispatcher* dispatcher;
	btBroadphaseInterface* overlappingPairCache;
	btSequentialImpulseConstraintSolver* solver;
    btDiscreteDynamicsWorld* dynamicsWorld;
	btAlignedObjectArray<btCollisionShape*> collisionShapes;

public: 
    Physics();
    ~Physics();
    void addObject(btRigidBody* b);
    void removeObject(btRigidBody* b);
    btAlignedObjectArray<btCollisionShape*>& getCollisionShapes(void) {return collisionShapes;}
    btDiscreteDynamicsWorld* getDynamicsWorld(void) {return dynamicsWorld;}
    void stepSimulation(const Ogre::Real elapsedTime, 
        int maxSubSteps = 1, const Ogre::Real fixedTimestep = 1.0f/60.0f); 
};

#endif
