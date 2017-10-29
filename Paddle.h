#ifndef __Paddle_h_
#define __Paddle_h_

#include <Ogre.h>
#include "Physics.h"


class Paddle {
private:
	Ogre::SceneNode* paddleNode;
	Ogre::SceneManager* sceneMgr;
	Ogre::Vector3 initialPos;
	int initialRot;
	
	// Bullet fields
    Physics* mPhysics;
    btCollisionShape* btShape;
    KinematicMotionState* btMotState;
	btScalar btMass; 
	btRigidBody* btBody; 
	btVector3 btInertia;
	btTransform paddleTransform;

public:
	Paddle(Ogre::SceneManager*, Physics*, int, int, Ogre::Vector3, int);
	Ogre::SceneNode* getNode(void) { return paddleNode; }
	~Paddle(void);
	void updateMotionState(void);
	void reset(void);
};

#endif
