#include <OgreEntity.h> 
#include <OgreSceneManager.h> 
#include "ScoreWall.h"

ScoreWall::ScoreWall(Ogre::SceneManager* scnMgr, int wallSize) { 
    Ogre::Entity* scoreWall = scnMgr->createEntity(); 

    rootNode = scnMgr->createSceneNode("ScoreWall"); 
    rootNode->attachObject(scoreWall); 
    rootNode->setPosition(Ogre::Vector3(0,0,wallSize/2));
    squareSize = wallSize/3;
    // INCOMPLETE
    goals.add(Goal(scnMgr,Ogre::Vector3(-squareSize,squareSize,wallSize/2)));
    goals.add(Goal(scnMgr,Ogre::Vector3(-squareSize,0,wallSize/2)));
    goals.add(Goal(scnMgr,Ogre::Vector3(-squareSize,-squareSize,wallSize/2)));
    goals.add(Goal(scnMgr,Ogre::Vector3(0,squareSize,wallSize/2)));
    goals.add(Goal(scnMgr,Ogre::Vector3(0,squareSize,wallSize/2)));
    goals.add(Goal(scnMgr,Ogre::Vector3(0,squareSize,wallSize/2)));
    goals.add(Goal(scnMgr,Ogre::Vector3(squareSize,squareSize,wallSize/2)));
    goals.add(Goal(scnMgr,Ogre::Vector3(squareSize,squareSize,wallSize/2)));
    goals.add(Goal(scnMgr,Ogre::Vector3(squareSize,squareSize,wallSize/2)));

    pickGoal();
} 

void ScoreWall::pickGoal() { 
    int i = rand()%(goals.size()-0 + 1) + 0;
}