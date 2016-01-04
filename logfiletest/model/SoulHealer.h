#ifndef SOULHEALER_H
#define SOULHEALER_H

#include <ctime>

#include "ServerState.h"
#include "ExpGainMeter.h"
#include "LevelUpChecker.h"
#include "MeterValue.h"

class SoulHealer{

public:
	
	SoulHealer(ExpGainMeter& expGainMeter, LevelUpChecker& currentExpChecker,
		LevelUpChecker& currentApChecker, MeterValue& kinahMeter, ServerState& serverState): 
			server(&serverState), 
			expGainMeter(&expGainMeter),
			currentExpChecker(&currentExpChecker),
			currentApChecker(&currentApChecker), 
			kinahMeter(&kinahMeter),
			expUpdateNeeded(false),
			apUpdateNeeded(false),
			lastDeathIsPk(false),
			lastReceivedPvpHitTime(0)
			{}

	void PvEDeath();
	void PvPDeath();
	
	void soulHeal();
	void nothingToRecover() {expUpdateNeeded = false;}

	bool manualExpUpdate(long long newValue);
	bool manualApUpdate(long long newValue);

	bool isExpUpdateNeeded() const {return expUpdateNeeded;}
	bool isApUpdateNeeded() const {return apUpdateNeeded;}

	void expUpdateNotNeeded() {expUpdateNeeded = false;}
	void apUpdateNotNeeded();

	void checkReceivedDamageIsPvp(string& skillName);

private:
	
	ServerState* server;
	ExpGainMeter* expGainMeter;
	LevelUpChecker* currentExpChecker;
	LevelUpChecker* currentApChecker;
	MeterValue* kinahMeter;

	bool expUpdateNeeded;
	bool apUpdateNeeded;
	bool lastDeathIsPk ;
	
	time_t lastReceivedPvpHitTime;

};
#endif