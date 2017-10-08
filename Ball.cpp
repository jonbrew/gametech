#include "Ball.h"

Ball::Ball(Ogre::SceneManager* scnMgr, Physics* mPhys) {
    sceneMgr = scnMgr;
    mPhysics = mPhys;
    bRadius = 10.0f; 
    bDirection = Ogre::Vector3(1.0f, 2.0f, 3.0f); 
    bDirection.normalise(); 
    bSpeed = 250.0f; 
}

void Ball::createBall() {
    Ogre::Entity* ball = sceneMgr->createEntity("Sphere", "sphere.mesh"); 
    ball->setCastShadows(true);
    rootNode = sceneMgr->getRootSceneNode()->createChildSceneNode("Ball"); 
    rootNode->attachObject(ball);
    rootNode->scale(0.07,0.07,0.07); 
    rootNode->setPosition(Ogre::Vector3(0, 0, 0));
    //create the new physics shape
    btShape = new btSphereShape(btScalar(bRadius));
    mPhysics->getCollisionShapes().push_back(btShape);
    //set the initial position and transform
    btTrans.setRotation(btQuaternion(1.0f, 1.0f, 1.0f, 0));
    //set the mass of the object. a mass of "0" means that it is an immovable object
    btMass = 0.1f;
    btInertia = btVector3(0,0,0);
    btTrans.setOrigin(btVector3(0,0,0));
    btShape->calculateLocalInertia(btMass, btInertia);
    //actually construct the body and add it to the dynamics world
    btMotionState = new btDefaultMotionState(btTrans);
    btRigidBody::btRigidBodyConstructionInfo rbInfo(btMass, btMotionState, btShape, btInertia);
    btBody = new btRigidBody(rbInfo);
    btBody->setRestitution(1);
    btBody->setUserPointer(rootNode);
    mPhysics->getDynamicsWorld()->addRigidBody(btBody);
}



void Ball::move(const Ogre::FrameEvent& evt) { 
    // Ogre::Vector3 bPosition = rootNode->getPosition(); 
    // if (bPosition.y < bRadius && bDirection.y < 0.0f) bDirection.y = -bDirection.y; 
    // if (bPosition.y > grounds->getHeight() - bRadius && bDirection.y > 0.0f) bDirection.y = -bDirection.y; 
    // if (bPosition.z < -grounds->getLength()/2.0f + bRadius && bDirection.z < 0.0f) bDirection.z = -bDirection.z; 
    // if (bPosition.z > grounds->getLength()/2.0f - bRadius && bDirection.z > 0.0f) bDirection.z = -bDirection.z; 
    // if (bPosition.x < -grounds->getWidth()/2.0f + bRadius && bDirection.x < 0.0f) bDirection.x = -bDirection.x; 
    // if (bPosition.x > grounds->getWidth()/2.0f - bRadius && bDirection.x > 0.0f) bDirection.x = -bDirection.x; 
    // rootNode->translate(bSpeed * evt.timeSinceLastFrame * bDirection); 
}