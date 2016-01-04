#ifndef GPMODULE_H
#define GPMODULE_H

#include <string>
#include <map>
using namespace std;

#include "../Module.h"

#include "../model/MeterValue.h"

#include "../model/ValueGainObserver.h"

#include "../Timer.h"

class GpModule: public Module{
public:
	
	MeterValue gpGainMeter;
	
	Timer timer;

	GpModule();

	void executeChatLogCommand(ChatLogCommand& command);

	void endOfTickAction();

private:

};
#endif