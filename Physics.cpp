#include "Physics.h"

Physics::Physics(Sound* mSnd) {
	mSound = mSnd;
	isCollidingWall = false;
	isCollidingPaddle = false;
	isCollidingGoal = false;
	collisionConfiguration = new btDefaultCollisionConfiguration(); 
	dispatcher = new btCollisionDispatcher(collisionConfiguration); 
	overlappingPairCache = new btDbvtBroadphase(); 
	solver = new btSequentialImpulseConstraintSolver(); 
	dynamicsWorld = new btDiscreteDynamicsWorld(dispatcher,
		overlappingPairCache,
		solver,
		collisionConfiguration); 
	dynamicsWorld->setGravity(btVector3(0.0, -9.81, 0.0));
}

void Physics::addObject (btRigidBody* b) { 
	dynamicsWorld->addRigidBody(b);       
}

void Physics::removeObject (btRigidBody* b) { 
	dynamicsWorld->removeRigidBody(b);       
}

bool Physics::stepSimulation(const Ogre::Real elapsedTime, int maxSubSteps, const Ogre::Real fixedTimestep) { 
	dynamicsWorld->stepSimulation(elapsedTime,maxSubSteps,fixedTimestep);  
	for(int i = 0; i < dynamicsWorld->getCollisionObjectArray().size(); i++) {
		btCollisionObject* obj = dynamicsWorld->getCollisionObjectArray()[i];
		btRigidBody* body = btRigidBody::upcast(obj);
		if(body && body->getMotionState() && !body->isStaticOrKinematicObject()){
			btTransform trans;
			body->getMotionState()->getWorldTransform(trans);

			void *userPointer = body->getUserPointer();
			if(userPointer) {
				btQuaternion orientation = trans.getRotation();
				Ogre::SceneNode *sceneNode = static_cast<Ogre::SceneNode *>(userPointer);
				sceneNode->setPosition(Ogre::Vector3(trans.getOrigin().getX(), trans.getOrigin().getY(), trans.getOrigin().getZ()));
				sceneNode->setOrientation(Ogre::Quaternion(orientation.getW(), orientation.getX(), orientation.getY(), orientation.getZ()));
			}
		}
	}
	return handleCollisions();
}

bool Physics::handleCollisions() {
	int numManifolds = dynamicsWorld->getDispatcher()->getNumManifolds();
	bool hitWall = false;
    bool hitPaddle = false;
    bool hitGoal = false;
	bool scored = false;
	if(numManifolds > 0) {
    	for(int i = 0; i < numManifolds; i++) {
    	    btPersistentManifold* contactManifold = dynamicsWorld->getDispatcher()->getManifoldByIndexInternal(i);
    	    const btCollisionObject* obA = contactManifold->getBody0();
    	    const btCollisionObject* obB = contactManifold->getBody1();
    	    int aType = obA->getUserIndex();
    	    int bType = obB->getUserIndex();
    	    if(aType == TYPE_BALL)
    	    	aType = bType;
    	    switch(aType) {
    	    	case TYPE_WALL :
    	    		if(!isCollidingWall) {
    	    			mSound->play(Sound::SOUND_BOUNCE);
                        mSound->soundToPlay = Sound::SOUND_BOUNCE;
                    }
    	    		hitWall = true;
    	    		break;
    	    	case TYPE_PADDLE :
    	    		if(!isCollidingPaddle) {
    	    			mSound->play(Sound::SOUND_HIT);
                    }
    	    		hitPaddle = true;
    	    		break;
    	    	case TYPE_GOAL_OFF :
    	    		if(!isCollidingGoal) {
    	    			mSound->play(Sound::SOUND_BOUNCE);
                        mSound->soundToPlay = Sound::SOUND_BOUNCE;
                    }
    	    		hitGoal = true;
    	    		break;
    	    	case TYPE_GOAL_ON :
    	    		if(!isCollidingGoal) {
    	    			mSound->play(Sound::SOUND_SCORE);
    	    			scored = true;
    	    		}
    	    		hitGoal = true;
    	    		break;
    	    }
    	}
    }
    isCollidingWall = hitWall;
    isCollidingPaddle = hitPaddle;
    isCollidingGoal = hitGoal;
    return scored;
}
