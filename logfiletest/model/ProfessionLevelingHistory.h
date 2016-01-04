#ifndef PROF_LVLNG_HIST_H
#define PROF_LVLNG_HIST_H

#include <map>
#include <string>
using namespace std;

#include "AbstractCounter.h"

class ProfessionLevelingHistory: public AbstractCounter<int, int>{
public:
	ProfessionLevelingHistory();

	int getCurrentLevel() {return currentLevel;}
	int getNumLevelUps() {return numLevelUps;}
	int getNumGatheredOrCraftedForLastLevelUp() {return numGatheredOrCraftedForLastLevelUp;}

	void addLevelUp(int level, int numGatheredOrCraftedForLastLevelUp);

private:
	int numLevelUps;
	int currentLevel;
	int numGatheredOrCraftedForLastLevelUp;

	//map<int, int> history;
};

#endif