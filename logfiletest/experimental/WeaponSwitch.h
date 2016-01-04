#ifndef WEAPONSWITCH_H
#define WEAPONSWITCH_H

#include <string>
#include <unordered_map>
using namespace std;

//#include "CombatStats.h"

class WeaponSwitch{
public:
	WeaponSwitch(): set(0){}
	
	void switchWeapons(){
		if (set == 0) set = 1;
		else set = 0;
	}	

	int getCurrentSet() {return set;}
	//CombatStats& getCurrentSet() {return weaponSet[set];}
	//CombatStats& getCurrentSetByTarget(string& mob) {return combatStatsByMob[set][mob];}

	//CombatStats& getWeaponSet(int num) {return weaponSet[num];}
	
	
private:
	
	//CombatStats weaponSet[2];	
	int set;
};

#endif
