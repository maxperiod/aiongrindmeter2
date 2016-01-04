#include "ApGainMeter.h"

void ApGainMeter::applyFromBuffer(){
	if (rankUpChecker != nullptr){
		rankUpChecker->increaseValue(tempGained - tempSpent - tempLost);
		rankUpChecker->checkLevelUp();
	}
	MeterValue::applyFromBuffer();
}

void ApGainMeter::registerPvpApFromLastGain(){
	if (tempGained > 0) {
		pvpAp += lastSingleChange;
		applyFromBuffer();
	}
}

void ApGainMeter::acquireRelic(int item, int quantity){
	relicAp += relicApProcessor->getRelicApValue(item) * quantity;
}

void ApGainMeter::sellRelic(int amount){
	relicAp -= amount;
	gain(amount);
}