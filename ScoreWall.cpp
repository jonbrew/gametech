#include <OgreEntity.h> 
#include <OgreSceneManager.h> 
#include "ScoreWall.h"

ScoreWall::ScoreWall(Ogre::SceneManager* scnMgr, int wallSize) { 
    squareSize = wallSize/3;
    // INCOMPLETE
    goals = std::vector<Goal>;
    goals.push_back(Goal(scnMgr,Ogre::Vector3(-squareSize,squareSize,wallSize/2)));
    goals.push_back(Goal(scnMgr,Ogre::Vector3(-squareSize,0,wallSize/2)));
    goals.push_back(Goal(scnMgr,Ogre::Vector3(-squareSize,-squareSize,wallSize/2)));
    goals.push_back(Goal(scnMgr,Ogre::Vector3(0,squareSize,wallSize/2)));
    goals.push_back(Goal(scnMgr,Ogre::Vector3(0,0,wallSize/2)));
    goals.push_back(Goal(scnMgr,Ogre::Vector3(0,-squareSize,wallSize/2)));
    goals.push_back(Goal(scnMgr,Ogre::Vector3(squareSize,squareSize,wallSize/2)));
    goals.push_back(Goal(scnMgr,Ogre::Vector3(squareSize,0,wallSize/2)));
    goals.push_back(Goal(scnMgr,Ogre::Vector3(squareSize,-squareSize,wallSize/2)));

    pickGoal();
} 

void ScoreWall::pickGoal() { 
    int i = rand()%(goals.size()-0 + 1) + 0;
    if(activeGoal)
        activeGoal->off();
    activeGoal = &(goals[i]);
    activeGoal->on();
}