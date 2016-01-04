#include "ProfessionLeveling.h"

ProfessionLeveling::ProfessionLeveling(): currentProfession(NO_PROFESSION), 
	numGatheredOrCraftedSinceLevelUp(-1), cannotLevelUp(false), isLevelUp(false){

	levelingHistory[currentProfession] = new ProfessionLevelingHistory();
}

void ProfessionLeveling::levelUp(const string& profession, int level){
	currentProfession = profession;
	//currentLevel = level;

	int numGatheredOrCraftedForLastLevelUp = numGatheredOrCraftedSinceLevelUp;
	if (numGatheredOrCraftedSinceLevelUp >= 0) numGatheredOrCraftedForLastLevelUp ++;
	numGatheredOrCraftedSinceLevelUp = -1;
	
	if (levelingHistory.count(profession) == 0){
		levelingHistory[profession] = new ProfessionLevelingHistory();
	}
	levelingHistory[profession]->addLevelUp(level, numGatheredOrCraftedForLastLevelUp);
	isLevelUp = true;
}

void ProfessionLeveling::gainProfessionExp(){
	if (!cannotLevelUp && (numGatheredOrCraftedSinceLevelUp >= 0 || isLevelUp)){
		numGatheredOrCraftedSinceLevelUp ++;
		isLevelUp = false;
	}	
	cannotLevelUp = false;
}

float ProfessionLeveling::getProgressBarValue(){
	int numGatheredOrCraftedForLastLevelUp = levelingHistory[currentProfession]->getNumGatheredOrCraftedForLastLevelUp();

	if (numGatheredOrCraftedForLastLevelUp <= 0) return 0;
	else if (numGatheredOrCraftedSinceLevelUp < numGatheredOrCraftedForLastLevelUp)
		return (float)numGatheredOrCraftedSinceLevelUp * 100 / numGatheredOrCraftedForLastLevelUp;
	else return (float)numGatheredOrCraftedSinceLevelUp * 100 / (numGatheredOrCraftedSinceLevelUp + 1);
}

