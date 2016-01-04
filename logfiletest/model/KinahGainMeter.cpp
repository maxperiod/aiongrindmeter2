#include "KinahGainMeter.h"

void KinahGainMeter::applyFromBuffer(){
	MeterValue::applyFromBuffer();
	if (saleMode) npcSales += lastSingleChange;
	saleMode = false;
}