#ifndef METERVALUE_H
#define METERVALUE_H
//#include "Timer.h"
#include "Observable.h"

class MeterValue: public Observable{
	//const Timer* timer;

public:
	MeterValue(){	
		reset();
	}

	void reset();

	void gain(long long value);
	void spend(long long value);
	void lose(long long value);

	virtual void applyFromBuffer();	

	long long getTotalGained() {return totalGained;}
	long long getTotalSpent() {return totalSpent;}
	long long getTotalLost() {return totalLost;}
	long long getNetGained() {return netGained;}

	long long getLastSingleChange() {return lastSingleChange;}

	long long getLastChange() {return lastChange;}	
	int getNumPacketsForLastChange() {return numPackets;}	

protected:
	
	long long totalGained;
	long long totalSpent;
	long long totalLost;
	long long netGained;
	int numPackets;

	long long lastSingleChange;
	long long lastChange;

	long long tempGained;
	long long tempSpent;
	long long tempLost;
	int tempNumPackets;

	bool lastTickHasChanged;
};
#endif