#ifndef SOULHEALERMODULE_H
#define SOULHEALERMODULE_H

#include <string>
#include <map>
using namespace std;

#include "../Module.h"

#include "ExpModule.h"
#include "ApModule.h"
#include "KinahModule.h"

#include "../model/ExpGainMeter.h"
#include "../model/ApGainMeter.h"

#include "../lookups/ExpChartNA40.h"
#include "../lookups/ApChart.h"
#include "../model/LevelUpChecker.h"

#include "../model/SoulHealer.h"

#include "../model/ValueGainObserver.h"

#include "../Timer.h"

class SoulHealerModule: public Module{
public:

	ServerState serverState;
	SoulHealer soulHealer;

	SoulHealerModule(ExpModule& expModule, ApModule& apModule, KinahModule& kinahModule);

	void executeChatLogCommand(ChatLogCommand& command);

	void endOfTickAction();

};

#endif