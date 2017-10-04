#include <OgreEntity.h> 
#include <OgreSceneManager.h> 
#include "Goal.h"

Goal::Goal(Ogre::SceneManager* scnMgr, Ogre::Vector3 pos) { 
    Ogre::Entity* goal = scnMgr->createEntity("sphere.mesh"); 

    rootNode = scnMgr->createSceneNode(); 
    rootNode->attachObject(goal); 
    rootNode->setPosition(pos);
    rootNode->scale(0.1,0.1,0.1);

    isActive = false;
} 

void Goal::on() { 
    isActive = true;
    // TODO change appearance
}

void Goal::off() { 
    isActive = false;
    // TODO change appearance
}