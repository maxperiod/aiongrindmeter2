#ifndef PROF_MDL_H
#define PROF_MDL_H

#include <string>
using namespace std;

#include "../Module.h"
#include "../model/GatherCraft.h"
#include "../model/GatherCraftRecord.h"
#include "../model/ProfessionLeveling.h"

#include "../parser/ItemIDReader.h"
#include "../Timer.h"
#include "../stringFunctions.h"


class ProfessionModule: public Module{
public:
	Timer timer;

	GatherCraft gathers;
	GatherCraft crafts;
	ProfessionLeveling gatherLeveling;
	ProfessionLeveling craftLeveling;
	
	enum ProfessionMode{NONE, GATHER, CRAFT};
	ProfessionMode professionMode;

	ProfessionModule();
	/*
	void reset(){		
		professionMode = NONE;
		timer.start();
	}
	*/
	void executeChatLogCommand(ChatLogCommand& command);

	void endOfTickAction();

private:

};

#endif