#include "pvpKillsCounter.h"

//template <class T>
void PvpKillsCounter::addKill(const string& name){
	if (theMap.count(name) == 0){		
		PlayerKill entry = {1, 0};
		theMap[name] = entry;
		uniqueKills ++;
	}
	else {
		if (theMap[name].kills == 0) uniqueKills ++;
		theMap[name].kills ++;
	}
	totalKills ++;
	//theMap[item].kills
}

//template <class T>
void PvpKillsCounter::addAssist(const string& name){
		if (theMap.count(name) == 0){		
		PlayerKill entry = {0, 1};
		theMap[name] = entry;
	}
	else {
		theMap[name].assists ++;
	}
	totalAssists ++;
}
