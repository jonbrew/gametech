#include "Physics.h"

Physics::Physics(Sound* mSnd) {
	mSound = mSnd;
	isColliding = false;
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

void Physics::stepSimulation(const Ogre::Real elapsedTime, 
		int maxSubSteps, const Ogre::Real fixedTimestep) { 
	dynamicsWorld->stepSimulation(elapsedTime,maxSubSteps,fixedTimestep);  
	for(int i = 0; i < dynamicsWorld->getCollisionObjectArray().size(); i++) {
		btCollisionObject* obj = dynamicsWorld->getCollisionObjectArray()[i];
		btRigidBody* body = btRigidBody::upcast(obj);

		if(body && body->getMotionState()){
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
	handleCollisions();
}

void Physics::handleCollisions() {
	int numManifolds = dynamicsWorld->getDispatcher()->getNumManifolds();
	if(!isColliding && numManifolds > 0) {
    	for(int i = 0; i < numManifolds; i++) {
    	    btPersistentManifold* contactManifold = dynamicsWorld->getDispatcher()->getManifoldByIndexInternal(i);
    	    const btCollisionObject* obA = contactManifold->getBody0();
    	    const btCollisionObject* obB = contactManifold->getBody1();
    	    int aType = obA->getUserIndex();
    	    int bType = obB->getUserIndex();
    	    switch(aType) {
    	    	case TYPE_BALL :
    	    		// Set check to bType (not the ball) and allow to fall through
    	    		aType = bType;
    	    	case TYPE_WALL :
    	    		mSound->play(Sound::SOUND_BOUNCE);
    	    		break;
    	    	case TYPE_PADDLE :
    	    		mSound->play(Sound::SOUND_HIT);
    	    		break;
    	    	case TYPE_GOAL :
    	    		break;
    	    }
    	}
    }
    isColliding = numManifolds > 0;
}
