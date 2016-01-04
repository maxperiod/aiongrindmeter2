#include <unordered_map>
using namespace std;

#include "CombatStats.h"

typedef pair<CombatStats&, CombatStats&> CombatStatsPair;

class CombatStatsManager{

public:
	//CombatStatsManager(): currentSet(0), lastTarget(""){}
	CombatStatsManager(): lastTarget(""){}
	
	CombatStatsPair getAllTargetsCombatStats() {
		return pair<CombatStats&, CombatStats&>(allTargets[0], allTargets[1]);
	};

	CombatStatsPair getIndividualTargetCombatStats(const string& target) {
		if (individualTarget[0].count(target) == 0){
			namesInsertionOrder.push_back(target);
			
			for (int i = 0; i < NUM_WEAPON_STATS; i ++)
				individualTarget[i].insert(pair<string, CombatStats>(target, blankCombatStats));
			
		}

		return CombatStatsPair(individualTarget[0].at(target), individualTarget[1].at(target));		
	}

	CombatStatsPair getLastTargetCombatStats(){
		if (lastTarget == "") return CombatStatsPair(blankCombatStats, blankCombatStats);
		else return getIndividualTargetCombatStats(lastTarget);
	}

	const string& getLastTarget() {return lastTarget;}
	void setLastTarget(const string& target) {lastTarget = target;}

private:
	static const int NUM_WEAPON_STATS = 2;
	string lastTarget;

	CombatStats blankCombatStats;
	//int currentSet;

	CombatStats allTargets[NUM_WEAPON_STATS];	

	vector<string> namesInsertionOrder;
	unordered_map<string, CombatStats> individualTarget[NUM_WEAPON_STATS];
	
};