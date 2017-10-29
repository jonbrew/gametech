#ifndef __ScoreWall_h_
#define __ScoreWall_h_

#include <Ogre.h>
#include <vector>
#include "Goal.h"


class ScoreWall { 
protected:
	Ogre::SceneManager* scnMgr;
	int wallSize;
    double squareSize;
    std::vector<Goal> goals;
    Goal* activeGoal;
 	Physics* mPhysics;
 	int score;

public: 
    ScoreWall(Ogre::SceneManager* scnMgr, Physics* mPhys, int wallSize);
    void createScoreWall();
    void allOff();
    void pickGoal(); 
    Goal* getActiveGoal() { return activeGoal; } 
    void increaseScore();
    int getScore();
    void resetScore();
};

#endif
