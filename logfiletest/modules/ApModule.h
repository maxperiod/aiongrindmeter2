#ifndef APMODULE_H
#define APMODULE_H

#include <string>
#include <map>
using namespace std;

#include "../Module.h"

#include "../model/ExpGainMeter.h"
#include "../model/ApGainMeter.h"

#include "../lookups/ExpChartNA40.h"
#include "../lookups/ApChart.h"
#include "../model/LevelUpChecker.h"

#include "../lookups/relicAp48.h"

#include "../model/SoulHealer.h"

#include "../model/ValueGainObserver.h"

#include "../Timer.h"

class ApModule: public Module{
public:
	ApChart apChart;
	
	LevelUpChecker abyssRankChecker;
	RelicAp48 relicAp;

	ApGainMeter apGainMeter;
	
	Timer timer;

	ApModule();


	//ValueGainObserver valueGainObserver;

	void executeChatLogCommand(ChatLogCommand& command);
	
	void endOfTickAction();

private:
	int parseBracketedItem(const string& itemBracket);

	bool isItemSale;
};
#endif