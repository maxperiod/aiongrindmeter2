#include "MeterValue.h"

void MeterValue::applyFromBuffer(){
	if (lastTickHasChanged){
		lastChange = (tempGained - tempSpent - tempLost);

		totalGained += tempGained;
		totalSpent += tempSpent;
		totalLost += tempLost;
		netGained = totalGained - totalSpent - totalLost;
		numPackets = tempNumPackets;

		tempGained = 0;
		tempSpent = 0;
		tempLost = 0;
		tempNumPackets = 0;

		lastTickHasChanged = false;
	}
}

void MeterValue::reset(){
	totalGained = 0;
	totalSpent = 0;
	totalLost = 0;
	netGained = 0;
	numPackets = 0;

	lastChange = 0;	
	lastSingleChange = 0;

	tempGained = 0;
	tempSpent = 0;
	tempLost = 0;
	tempNumPackets = 0;

	lastTickHasChanged = false;
}

void MeterValue::gain(long long value){
		tempGained += value;		
		tempNumPackets ++;
		lastTickHasChanged = true;
		lastSingleChange = value;
		notifyObserver();
	}

void MeterValue::spend(long long value){		
		tempSpent += value;
		tempNumPackets ++;
		lastTickHasChanged = true;
		lastSingleChange = -value;
		notifyObserver();
	}

void MeterValue::lose(long long value){		
		tempLost += value;		
		tempNumPackets ++;
		lastTickHasChanged = true;
		lastSingleChange = -value;
		notifyObserver();
	}