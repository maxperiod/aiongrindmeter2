#include "../Module.h"

#include "../parser/SkillToClassMap.h"
#include "../model/KnownPlayers.h"


class PlayerIdentificationModule: public Module{
public:
	PlayerIdentificationModule();

	KnownPlayers knownPlayers;

	void executeChatLogCommand(ChatLogCommand& command);
	
	void endOfTickAction();

private:	
	void identifyPlayerClass(string& name, string& skill);
};