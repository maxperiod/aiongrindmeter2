#include "RelicAP.h"

long long RelicAp::getRelicApValue(int item){
	if (relicApValues.count(item) == 1 && bestTurnInMultipliers.count(item) == 1){
		return relicApValues[item] * bestTurnInMultipliers[item];
	}
	return 0;
}