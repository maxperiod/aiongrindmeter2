#ifndef HUNTINGMODULE_H
#define HUNTINGMODULE_H

#include <unordered_set>
#include "../Module.h"

#include "../model/Counter.h"
#include "../model/pvpKillsCounter.h"

#include "../model/KnownPlayers.h"
#include "../model/AssistDamage.h"

//#include "../modules/PlayerIdentificationModule.h"

#include "../Timer.h"

#define MAX_TICKS_TO_RECOGNIZE_QUEST_XP 1

class HuntingModule: public Module{
public:
	HuntingModule();

	Timer timer;
	//Counter<int> itemsAcquired;
	Counter<string> monstersKilled;
	PvpKillsCounter playersKilled;

	void executeChatLogCommand(ChatLogCommand& command);

	void endOfTickAction();

private:

	void checkAndRegisteringKill(string& target);

	AssistDamage damageInflicted;

	string lastKill;
	KnownPlayers* knownPlayers;
	unordered_set<string> questNPCs;
	int ticksSinceLastKill;
};
#endif