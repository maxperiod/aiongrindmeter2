#ifndef PROGRESSBAR_H
#define PROGRESSBAR_H

#include <map>
#include "MeterValue.h"
#include "ExpChart.h"
using namespace std;

class LevelUpChecker{
	
public:
	LevelUpChecker();
	//LevelUpChecker(int levelCap);
	//~LevelUpChecker();

	void setReferringMeter(MeterValue& referringMeter) {this->referringMeter = &referringMeter;}
	void setExpChart(ExpChart& expChart) {this->expChart = &expChart;}

	void prohibitLevelUp() {levelUpBlocked = true;}
	void clearLevelUpProhibition() {levelUpBlocked = false;}

	bool initialize(long long currentValue);
	bool initialize(int level, long long currentValue);
	bool initializePercent(int level, float percent);

	bool isInitialized() {return initialized;}

	void increaseValue(long long increase) {if (initialized) currentValue += increase;}
	
	bool setCurrentValue(long long newValue);
	bool setCurrentPercent(float newValue);

	long long getCurrentValue();
	long long getCurrentLevelMaxValue();

	//int getMaxValue(int level);

	long long getCumulativeCurrentValue();
	//long long getCumulativeValueForLevel(int level);

	//long long getLevelCapValue();

	bool checkLevelUp();
	void levelUpLearnSkill();

	int getCurrentLevel();
	float getCurrentDecimalLevel();

	float getPercent();
	float getCumulativePercent();

	float getLastChangePercent();

	float getNumLevelsGained();
	float getProjectedDecimalLevel(long long expGain);

private:
	bool initialized;
	
	bool levelUpBlocked;

	int level;
	long long currentValue;

	//int levelCap;
	//int* values;	
	//long long* cumulativeValues;

	long long manuallyUpdatedChanges;

	ExpChart* expChart;
	//bool cumulativeMode;	

	MeterValue* referringMeter;

	float startingDecimalLevel;

	bool hasSkillLearnedInTick;
	//void initCumulativeValuesTable();
};

#endif