#ifndef KINAHMODULE_H
#define KINAHMODULE_H

#include <string>
#include <map>
using namespace std;

#include "../Module.h"

#include "../model/KinahGainMeter.h"

#include "../model/ValueGainObserver.h"

#include "../Timer.h"

class KinahModule: public Module{
public:

	KinahGainMeter kinahGainMeter;

	Timer timer;

	KinahModule();

	//ValueGainObserver valueGainObserver;

	void executeChatLogCommand(ChatLogCommand& command);

	void endOfTickAction();

};
#endif