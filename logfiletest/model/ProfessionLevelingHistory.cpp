#include "ProfessionLevelingHistory.h"

ProfessionLevelingHistory::ProfessionLevelingHistory():
	numLevelUps(0), currentLevel(-1), numGatheredOrCraftedForLastLevelUp(-1){

}

void ProfessionLevelingHistory::addLevelUp(int level, int numGatheredOrCraftedForLastLevelUp){
	theMap[level] = numGatheredOrCraftedForLastLevelUp;
	this->numGatheredOrCraftedForLastLevelUp = numGatheredOrCraftedForLastLevelUp;
	currentLevel = level;
	numLevelUps ++;
}