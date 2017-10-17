#ifndef __Paddle_h_
#define __Paddle_h_

#include <Ogre.h>
#include "Physics.h"


class Paddle {
private:
	Ogre::SceneNode* paddleNode;
	Ogre::SceneManager* sceneMgr;
	
	// Bullet fields
    Physics* mPhysics;
    btCollisionShape* btShape;
    KinematicMotionState* btMotState;
	btScalar btMass; 
	btRigidBody* btBody; 
	btVector3 btInertia;
	btTransform paddleTransform;

public:
	Paddle(Ogre::SceneManager*, Physics*, int, int);
	~Paddle(void);
	void updateMotionState(void);
	void reset(void);
};

#endif
