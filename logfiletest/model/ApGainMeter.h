#ifndef APGAINMETER_H
#define APGAINMETER_H

#include "MeterValue.h"
#include "LevelUpChecker.h"
#include "RelicAp.h"
//#include "ApChart.h"

class ApGainMeter: public MeterValue{
public:
	//ApGainMeter(): apChart(nullptr){}
	ApGainMeter(LevelUpChecker& rankUpChecker, RelicAp& relicApProcessor): 
	  pvpAp(0), relicAp(0){
		rankUpChecker.setReferringMeter(*this);		
		this->rankUpChecker = &rankUpChecker;
		this->relicApProcessor = &relicApProcessor;
	}

	long long getPvpAp() {return pvpAp;}
	long long getRelicAp() {return relicAp;}

	void registerPvpApFromLastGain();
	void acquireRelic(int item, int quantity = 1);
	void sellRelic(int amount);
	
	void applyFromBuffer();

private:
	LevelUpChecker* rankUpChecker;
	RelicAp* relicApProcessor;
	long long pvpAp;
	long long relicAp;
};
#endif