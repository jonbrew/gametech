#include "Physics.h"

Physics::Physics() { 
	collisionConfiguration = new btDefaultCollisionConfiguration(); 
	dispatcher = new btCollisionDispatcher(collisionConfiguration); 
	overlappingPairCache = new btDbvtBroadphase(); 
	solver = new btSequentialImpulseConstraintSolver(); 
	dynamicsWorld = new btDiscreteDynamicsWorld(dispatcher,
		overlappingPairCache,
		solver,
		collisionConfiguration); 
	dynamicsWorld->setGravity(btVector3(0.0, -0.098, 0.0));
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
	for (int i = 0; i < dynamicsWorld->getCollisionObjectArray().size(); i++) {
		btCollisionObject* obj = dynamicsWorld->getCollisionObjectArray()[i];
		btRigidBody* body = btRigidBody::upcast(obj);

		if (body && body->getMotionState()){
			btTransform trans;
			body->getMotionState()->getWorldTransform(trans);

			void *userPointer = body->getUserPointer();
			if (userPointer) {
				btQuaternion orientation = trans.getRotation();
				Ogre::SceneNode *sceneNode = static_cast<Ogre::SceneNode *>(userPointer);
				sceneNode->setPosition(Ogre::Vector3(trans.getOrigin().getX(), trans.getOrigin().getY(), trans.getOrigin().getZ()));
				sceneNode->setOrientation(Ogre::Quaternion(orientation.getW(), orientation.getX(), orientation.getY(), orientation.getZ()));
			}
		}
	}
}