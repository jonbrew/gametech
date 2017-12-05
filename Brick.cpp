#include "Brick.h"

Brick::Brick(Ogre::SceneManager* scnMgr, Physics* mPhys) {
    sceneMgr = scnMgr;
    mPhysics = mPhys;
}

void Brick::createBrick(Ogre::Vector3 startPos, int level) {
    brick = sceneMgr->createEntity("cube.mesh"); 
    brick->setCastShadows(true);
    updateColor(level);
    rootNode = sceneMgr->getRootSceneNode()->createChildSceneNode(); 
    rootNode->attachObject(brick);
    rootNode->scale(0.2,0.2,0.2); 
    rootNode->setPosition(startPos);
    //create the new physics shape
    btShape = new btBoxShape(btVector3(9, 9, 9));
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
    btBody->setRestitution(1.0);
    btBody->setFriction(0);
    btBody->setUserPointer(this);
    btBody->setUserIndex(Physics::TYPE_BRICK);
    mPhysics->getDynamicsWorld()->addRigidBody(btBody);

    brick_level = level;

}

bool Brick::hitBrick() {
    brick_level--;
    updateColor(brick_level);
    if(brick_level == 0)
        return true;
    return false;
}

Brick::~Brick(void) {
    sceneMgr->destroySceneNode(rootNode);
    mPhysics->getDynamicsWorld()->removeRigidBody(btBody);
    delete btBody->getMotionState();
    delete btBody;
}

void Brick::updateColor(int health){
    switch (health)
    {
        case 1:
           brick->setMaterialName("Colors/Orange");
            break; 
        case 2:
            brick->setMaterialName("Colors/Yellow");
            break;
        case 3:
            brick->setMaterialName("Colors/Green");
            break;
        default:
            break;
    }
 }
