#include "Brick.h"

Brick::Brick(Ogre::SceneManager* scnMgr, Physics* mPhys) {
    sceneMgr = scnMgr;
    mPhysics = mPhys;
}

void Brick::createBrick(Ogre::Vector3 startPos, int level) {

	if (brick_level == 1){
		brick_material = "Colors/Green";
	} else if (brick_level == 2) {
		brick_material = "Colors/Yellow";
	} else if (brick_level == 3) {
		brick_material = "Colors/Red";
	}

    brick = sceneMgr->createEntity("cube.mesh"); 
    brick->setCastShadows(true);
    brick->setMaterialName(brick_material);
    rootNode = sceneMgr->getRootSceneNode()->createChildSceneNode("Brick"); 
    rootNode->attachObject(brick);
    rootNode->scale(0.07,0.07,0.07); 
    rootNode->setPosition(startPos);
    //create the new physics shape
    btShape = new btBoxShape(btVector3(10, 10, 10));
    mPhysics->getCollisionShapes().push_back(btShape);
    //set the initial position and transform
    btTrans.setRotation(btQuaternion(1.0f, 1.0f, 1.0f, 0));
    //set the mass of the object. a mass of "0" means that it is an immovable object
    btMass = 0;
    btInertia = btVector3(0,0,0);
    btTrans.setOrigin(btVector3(startPos.x,startPos.y,startPos.z));
    btShape->calculateLocalInertia(btMass, btInertia);
    //construct the body and add it to the dynamics world
    btMotionState = new btDefaultMotionState(btTrans);
    btRigidBody::btRigidBodyConstructionInfo rbInfo(btMass, btMotionState, btShape, btInertia);
    btBody = new btRigidBody(rbInfo);
    btBody->setRestitution(0.85);
    btBody->setFriction(0.5);
    btBody->setUserPointer(rootNode);
    btBody->setUserIndex(Physics::TYPE_BRICK);
    mPhysics->getDynamicsWorld()->addRigidBody(btBody);

    brick_level = level;

}

void Brick::hitBrick() {
	brick_level--;
	if (brick_level == 0) {
		sceneMgr->destroyEntity(brick->getname());
	} else if (brick_level == 1){
		brick_material = "Colors/Green";
	} else if (brick_level == 2) {
		brick_material = "Colors/Yellow";
	} else if (brick_level == 3) {
		brick_material = "Colors/Red";
	}

	brick->setMaterialName(brick_material);

}