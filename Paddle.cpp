#include "Paddle.h"

Paddle::Paddle(Ogre::SceneManager* scnMgr, Physics* mPhys, int paddleWidth, int paddleHeight, Ogre::Vector3 pos, int rotation) {
    sceneMgr = scnMgr;
    initialPos = pos;
    initialRot = rotation;

	Ogre::Plane plane(Ogre::Vector3::UNIT_Y, 0);
    Ogre::MeshManager::getSingleton().createPlane(
        "paddleMesh",
        Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME,
        plane, 
        paddleWidth, paddleHeight, 20, 20, 
        true, 
        1, 5, 5, 
        Ogre::Vector3::UNIT_Z);

    Ogre::Entity* paddleEntity = scnMgr->createEntity("paddleMesh");
    paddleEntity->setMaterialName("Colors/RadioactiveGreen");

    paddleNode = scnMgr->getRootSceneNode()->createChildSceneNode();
    paddleNode->attachObject(paddleEntity);
    paddleNode->pitch(Ogre::Radian(Ogre::Degree(initialRot)));
    paddleNode->translate(initialPos);

    mPhysics = mPhys;

    //create the new physics shape
    btShape = new btBoxShape(btVector3(paddleWidth/2,0.f,paddleHeight/2));    
    mPhysics->getCollisionShapes().push_back(btShape);
    paddleTransform.setIdentity();
    paddleTransform.setRotation(btQuaternion(btRadians(0),btRadians(initialRot),btRadians(0)));
    paddleTransform.setOrigin(btVector3(initialPos.x,initialPos.y,initialPos.z));
    btMass = 0; //the mass is 0, because the ground is immovable (static)
    btInertia = btVector3(0, 0, 0);
    btMotState = new KinematicMotionState(paddleTransform, paddleNode);
    btShape->calculateLocalInertia(btMass, btInertia);
    btRigidBody::btRigidBodyConstructionInfo paddleRBInfo(btMass, btMotState, btShape, btInertia);
    btBody = new btRigidBody(paddleRBInfo);
	btBody->setCollisionFlags(btCollisionObject::CF_KINEMATIC_OBJECT);
    btBody->setUserIndex(Physics::TYPE_PADDLE);
    btBody->setRestitution(1);
    
    //add the body to the dynamics world
    mPhysics->getDynamicsWorld()->addRigidBody(btBody);
}

void Paddle::updateMotionState() {
    btMotState->setKinematicPos();
}

void Paddle::reset() {
    paddleNode->setPosition(initialPos);

    btBody->clearForces();
    btBody->setLinearVelocity(btVector3(0, 0, 0));
    btBody->setAngularVelocity(btVector3(0, 0, 0));
    paddleTransform.setOrigin(btVector3(initialPos.x,initialPos.y,initialPos.z));
    paddleTransform.setRotation(btQuaternion(btRadians(0),btRadians(initialRot),btRadians(0)));

    btBody->setWorldTransform(paddleTransform);
    btMotState->setWorldTransform(paddleTransform);
}
