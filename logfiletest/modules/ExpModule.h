#ifndef EXPMODULE_H
#define EXPMODULE_H

#include <string>
#include <map>
using namespace std;

#include "../Module.h"

#include "../model/ExpGainMeter.h"
#include "../model/ApGainMeter.h"

#include "../lookups/ExpChartNA40.h"
#include "../lookups/ApChart.h"
#include "../model/LevelUpChecker.h"

#include "../model/SoulHealer.h"

#include "../model/ValueGainObserver.h"

#include "../Timer.h"

class ExpModule: public Module{
public:
	ExpChartNA40 expChart;

	LevelUpChecker levelUpChecker;

	ExpGainMeter expGainMeter;	

	Timer timer;

	ExpModule(); 

	float getWeightedLevelUpsPerHour();
	//ValueGainObserver valueGainObserver;

	void executeChatLogCommand(ChatLogCommand& command);

	void endOfTickAction();

};
#endif