#ifndef PROF_LVLNG_H
#define PROF_LVLNG_H

#include <string>
#include <map>
using namespace std;

#include "ProfessionLevelingHistory.h"
#define NO_PROFESSION "N/A"

class ProfessionLeveling{
public:	
	ProfessionLeveling();

	void levelUp(const string& profession, int level);
	void gainProfessionExp();
	
	string& getCurrentProfession() {return currentProfession;}

	ProfessionLevelingHistory& getProfessionLevelingHistory() {
		return *levelingHistory[currentProfession];
	}
	ProfessionLevelingHistory& getProfessionLevelingHistory(const string& profession){
		if (levelingHistory.count(profession) == 1)
			return *levelingHistory[profession];
		else
			return *levelingHistory[NO_PROFESSION];
	}
		

	float getProgressBarValue();

	void levelCapped() {cannotLevelUp = true;}

	int getNumGatheredOrCraftedSinceLevelUp() {return numGatheredOrCraftedSinceLevelUp;}
	//int getNumGatheredOrCraftedForLastLevelUp() {return numGatheredOrCraftedForLastLevelUp;}

	int getCurrentLevel() {return levelingHistory[currentProfession]->getCurrentLevel();}
	int getNumLevelUps(){ return levelingHistory[currentProfession]->getNumLevelUps();}
	int getNumGatheredOrCraftedForLastLevelUp() {return levelingHistory[currentProfession]->getNumGatheredOrCraftedForLastLevelUp();}

private:	
	
	string currentProfession;
	//int currentLevel;
	int numGatheredOrCraftedSinceLevelUp;
	//int numGatheredOrCraftedForLastLevelUp;
	
	map<string, ProfessionLevelingHistory*> levelingHistory;

	bool cannotLevelUp;
	bool isLevelUp;
};

#endif