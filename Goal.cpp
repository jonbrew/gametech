#include "Goal.h"

Goal::Goal(Ogre::SceneManager* scnMgr, double goalSize, Ogre::Vector3 pos) { 
    Ogre::Entity* goalEntity = scnMgr->createEntity("goalMesh");
    goalEntity->setMaterialName("Colors/Red");

    goalNode = scnMgr->getSceneNode("scoreWall")->createChildSceneNode();
    goalNode->attachObject(goalEntity);
    goalNode->setPosition(pos);

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
