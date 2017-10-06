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

public: 
    ScoreWall(Ogre::SceneManager* scnMgr, int wallSize);
    void createScoreWall();
    void pickGoal(); 
    Goal* getActiveGoal() { return activeGoal; } 
};

#endif
