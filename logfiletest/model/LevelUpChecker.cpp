#include "LevelUpChecker.h"


LevelUpChecker::LevelUpChecker(){
	referringMeter = nullptr;
	initialized = false;
	levelUpBlocked = false;
	currentValue = -1;
	level = -1;			
	manuallyUpdatedChanges = 0;
	startingDecimalLevel = -1;
	hasSkillLearnedInTick = false;
}

bool LevelUpChecker::initialize(long long currentValue){
	if (!expChart->isCumulativeMode()) return false;

	if (currentValue >= 0) { 
		//int i = 0;
		level = 1;
		while (currentValue >= expChart->getMaxValue(level) && level < expChart->getLevelCap()) level ++;
		
		this->currentValue = currentValue;
		initialized = true;
		startingDecimalLevel = getCurrentDecimalLevel();
		return true;
	}
	return false;
}

bool LevelUpChecker::initialize(int level, long long currentValue){
	if (expChart->isCumulativeMode()){
		return initialize(currentValue);
	}
	else if (level >= 1 && level <= expChart->getLevelCap() 
		&& currentValue >= 0 && currentValue <= expChart->getMaxValue(level)){
		this->level = level;
		this->currentValue = currentValue;
		initialized = true;
		startingDecimalLevel = getCurrentDecimalLevel();
		return true;
	}

	else return false;
}

bool LevelUpChecker::initializePercent(int level, float percent){
	//percentage displayed ingame are truncated past 2 decimal places
	//if (percent < 0) percent = 0;

	if (level >= 1 && level <= expChart->getLevelCap() 
		&& percent >= 0 && percent <= 100){
		this->level = level;
		this->currentValue = percent * expChart->getMaxValue(level) / 100 + 0.5;
		initialized = true;
		startingDecimalLevel = getCurrentDecimalLevel();
		return true;
	}
}

long long LevelUpChecker::getCurrentValue(){
	return currentValue;
}

long long LevelUpChecker::getCumulativeCurrentValue(){	
	if (!initialized) return -1;
	if (expChart->isCumulativeMode()) return currentValue;
	else return expChart->getCumulativeValueForLevel(level) + currentValue;
}

long long LevelUpChecker::getCurrentLevelMaxValue(){
	return expChart->getMaxValue(level);
}

int LevelUpChecker::getCurrentLevel(){
	return level;
}

float LevelUpChecker::getCurrentDecimalLevel(){
	if (expChart->isCumulativeMode() && level >= expChart->getLevelCap())
		return level;
	
	return level + getPercent() / 100;
}

float LevelUpChecker::getPercent(){

	if (!initialized) return 0;
	// AP chart is cumulative since 9th kyu
	if (expChart->isCumulativeMode()){
			
		if (level >= expChart->getLevelCap()){
			return 100;
		}
		else if (currentValue >= 0){
			long long max = expChart->getMaxValue(level);
			long long last = expChart->getMaxValue(level - 1);			

			if (max != -1) 
				return (float)(currentValue - last) * 100 / (max - last);

			else return 0;
		}
		else return 0;
	}
	// XP chart is amount since last level up
	else{
		long long max = expChart->getMaxValue(level);
		if (max != -1) return (float)currentValue * 100 / max;
		else return 0;
	}
}

float LevelUpChecker::getCumulativePercent(){
	if (!initialized) return 0;
	if (expChart->isCumulativeMode()){
		return (float)currentValue / expChart->getLevelCapValue();
	}
	else {
		return (float)getCumulativeCurrentValue() * 100 / expChart->getLevelCapValue();
	}
}

float LevelUpChecker::getLastChangePercent(){
	if (!initialized) return 0;
	//if (!expChart->isCumulativeMode()){
		return ((getCurrentDecimalLevel() - getProjectedDecimalLevel(-referringMeter->getLastChange())) * 100);
		
	//}
	return -1;
}

bool LevelUpChecker::checkLevelUp(){
	if (!initialized) return false;
	if (!expChart->isCumulativeMode()){		
		long long maxValue = expChart->getMaxValue(level);
		if (!levelUpBlocked && level < expChart->getLevelCap()){
			
			while (currentValue > maxValue){
				hasSkillLearnedInTick = false;
				//expGained -= currentExp - getLevelUpCheckerEntry(level);
				currentValue -= maxValue;
				level ++;
				
				return true;
				
			}
			if (hasSkillLearnedInTick && currentValue <= maxValue){
				startingDecimalLevel += (maxValue - currentValue) / maxValue;
				currentValue = 0;
				level ++;
				hasSkillLearnedInTick = false;
				return true;
			}
		}		
		else {
			if (currentValue > maxValue){
				if (referringMeter != nullptr) referringMeter->lose(currentValue - maxValue);
				currentValue = maxValue;
				return false;
			}
		}


	}
	else {		
		//int i = 0;
		int tempLevel = 1;
		while (currentValue >= expChart->getMaxValue(tempLevel) && tempLevel < expChart->getLevelCap()) tempLevel ++;
		if (level != tempLevel){
			level = tempLevel;
			return true;		
		}
		else return false;
		
	}
	return false;
}

void LevelUpChecker::levelUpLearnSkill(){
	hasSkillLearnedInTick = true;
}

bool LevelUpChecker::setCurrentValue(long long newValue){
	referringMeter->applyFromBuffer();
	if (initialized){
		long long change = newValue - currentValue;
		if (newValue >= 0 && newValue <= currentValue + manuallyUpdatedChanges){
			referringMeter->lose(-change);
			referringMeter->applyFromBuffer();
			manuallyUpdatedChanges -= change;
			return true;
		}
		else return false;
	}
	return true;
}

bool LevelUpChecker::setCurrentPercent(float newValue){
	float percent = newValue;// - 0.005f;
	//if (percent < 0) percent = 0;
	if (percent < 0 || percent > 100) return false;

	long long resultExp = expChart->getMaxValue(level) * percent / 100 + 0.5;
	
	return setCurrentValue(resultExp);
	
}

float LevelUpChecker::getNumLevelsGained(){
	if (!initialized) return 0;
	else return getCurrentDecimalLevel() - startingDecimalLevel;
}

float LevelUpChecker::getProjectedDecimalLevel(long long expGain){
	if (!initialized) return -1;
	

	int newLevel = 1;
	long long newCumulativeExp = getCumulativeCurrentValue() + expGain;
	while (newLevel < expChart->getLevelCap() 
		&& newCumulativeExp > expChart->getCumulativeValueForLevel(newLevel + 1)) 
		newLevel ++;
	
	long long cumulativeExpRequirementForNewLevel = expChart->getCumulativeValueForLevel(newLevel);
	long long newExp = newCumulativeExp - cumulativeExpRequirementForNewLevel;
	
	if (!expChart->isCumulativeMode()){
		return newLevel + (float)newExp / expChart->getMaxValue(newLevel);
	}
	else {		
		return newLevel + (float)newExp / 
			(expChart->getMaxValue(newLevel) - expChart->getMaxValue(newLevel - 1));
	}
	
}