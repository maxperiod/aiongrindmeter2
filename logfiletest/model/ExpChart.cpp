#include "ExpChart.h"
ExpChart::ExpChart(int levelCap){
	this->levelCap = levelCap;
	values = new long long[levelCap];
	cumulativeValues = new long long[levelCap];
}

ExpChart::~ExpChart(){
	delete values;
	delete cumulativeValues;
}

void ExpChart::initCumulativeValuesTable(){
	cumulativeValues[0] = 0;
	for (int i = 1; i < levelCap; i ++){
		if (cumulativeMode) cumulativeValues[i] = values[i];
		else cumulativeValues[i] = cumulativeValues[i-1] + values[i-1];
	}
}

long long ExpChart::getCumulativeValueForLevel(int level){
	
	if (level == 1) return 0;
	if (cumulativeMode){
		
		return getMaxValue(level - 1);
	}
	return cumulativeValues[level - 1];
}

long long ExpChart::getMaxValue(int level){
	
	if (level >= 1 && level <= levelCap){
		return values[level - 1];
	}
	else if (level == 0) return 0;
	else return -1;
}

long long ExpChart::getLevelCapValue(){
	if (cumulativeMode){
		return getMaxValue(levelCap - 1);
	}
	else{
		return getCumulativeValueForLevel(levelCap);
	}
}