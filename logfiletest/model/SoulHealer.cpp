#include "SoulHealer.h"

#include "../language/LanguageManager.h"
#include "../model/PlayerClassManager.h"

void SoulHealer::PvEDeath(){
	if (lastReceivedPvpHitTime != 0 && (clock() - lastReceivedPvpHitTime) / CLOCKS_PER_SEC < 60){
		PvPDeath();
	}
	else{
		expUpdateNeeded = true;
	}
	//apUpdateNeeded = false;
}

void SoulHealer::PvPDeath(){
	if (currentApChecker->isInitialized() && 
		(server->getCurrentServer() == server->STANDARD_SERVER || 
			server->getCurrentServer() == server->FAST_TRACK_SERVER)){
		apUpdateNeeded = true;
		lastDeathIsPk = true;
	}
}
bool SoulHealer::manualExpUpdate(long long newValue){
	if (currentExpChecker->setCurrentValue(newValue)){
		expUpdateNeeded = false;
		if (expGainMeter->getLastSingleChange() == 0){
			apUpdateNeeded = true;
			
		}
		return true;
	}
	return false;
}

bool SoulHealer::manualApUpdate(long long newValue){
	if (currentApChecker->setCurrentValue(newValue)){
		apUpdateNeeded = false;
		return true;
	}
	return false;
}

void SoulHealer::soulHeal(){
	int lastKinahTransaction = kinahMeter->getLastSingleChange();
	if (lastKinahTransaction != -1 && expUpdateNeeded){
		int expLoss = floor((float) expGainMeter->getLastSingleChange() * 1.5);
		expGainMeter->lose(expLoss);
		
	}
	else if (lastKinahTransaction == -1 && !lastDeathIsPk && currentApChecker->isInitialized()){
		apUpdateNeeded = true;
	}
	expGainMeter->applyFromBuffer();		
	kinahMeter->applyFromBuffer();
	expUpdateNeeded = false;
}

void SoulHealer::checkReceivedDamageIsPvp(string& skillName){
	const string& playerClass = 
		LANGUAGE_MANAGER.getCurrentLanguage().getSkillToClassMap().getClass(skillName);
	
	if (playerClass != "" && playerClass != PlayerClassManager::PC_AND_NPC_SKILL){
		lastReceivedPvpHitTime = clock();
	}
	
}

void SoulHealer::apUpdateNotNeeded(){
	apUpdateNeeded = false;
	lastDeathIsPk = false;
}