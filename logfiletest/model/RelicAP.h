#ifndef RELIC_AP_H
#define RELIC_AP_H

#include <unordered_map>
using namespace std;

class RelicAp{
public:
	long long getRelicApValue(int item);
protected:
	unordered_map<int, long long> relicApValues;
	unordered_map<int, float> bestTurnInMultipliers;
};
#endif