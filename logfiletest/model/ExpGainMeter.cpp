#include "ExpGainMeter.h"
/*
void ExpGainMeter::checkLevelUp(){
	expChart.checkLevelUp();
}
*/
void ExpGainMeter::applyFromBuffer(){
	
	if (expChart != nullptr){
		expChart->increaseValue(tempGained - tempSpent - tempLost);
		
		if (tempGained > 0){
			expChart->checkLevelUp();
			expChart->clearLevelUpProhibition();
		}
	}
	MeterValue::applyFromBuffer();
}
/*
bool ExpGainMeter::setCurrentExp(int newValue){
	
	bool success = expChart.setCurrentValue(newValue);
	if (success){
		lastTickHasChanged = true;
		applyFromBuffer();
		return true;
	}
	
	return false;
}
*/