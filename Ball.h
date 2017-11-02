#ifndef __Ball_h_
#define __Ball_h_

#include <Ogre.h>
#include "Physics.h"

class Ball { 
protected:
    Ogre::SceneManager* sceneMgr;
    Ogre::SceneNode* rootNode; 
    Ogre::Real bRadius; 
    Ogre::Vector3 bDirection; 
    Ogre::Real bSpeed;
    // Bullet fields
    Physics* mPhysics;
    btCollisionShape* btShape;
    btDefaultMotionState *btMotionState;
	btScalar btMass; 
	btRigidBody* btBody; 
	btTransform btTrans; 
	btVector3 btInertia; 
public: 
    Ball(Ogre::SceneManager* scnMgr, Physics* mPhysics);
    void createBall(Ogre::Vector3 startPos);
    Ogre::SceneNode* getNode(void) { return rootNode; }
    btRigidBody* getRigidBody(void) { return btBody; }
    btDefaultMotionState* getMotionState(void) { return btMotionState; }
    void reset(void);
    void resetMultiplayer(int roundNum);
    void printPos(void);
};

#endif
