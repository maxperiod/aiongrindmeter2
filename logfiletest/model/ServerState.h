#ifndef SERVERSTATE_H
#define SERVERSTATE_H

//#include "../parser/RuleStrings.h"
#include "../language/LanguageManager.h"
#include "../lookups/MessageRuleEnums.h"

class ServerState{
	
	int currentServer;
public:
	enum servers{STANDARD_SERVER, FAST_TRACK_SERVER, INSTANCE_SERVER};

	ServerState(): currentServer(STANDARD_SERVER){}

	int getCurrentServer() { 
		return currentServer; 
	};

	void moveServer(string server){
		MessageRules& commandRules = LANGUAGE_MANAGER.getCurrentLanguage().getMessageRules();
		if (server == commandRules.getRule(STR_INTERSERVER_ORIGINAL_NAME)){
			currentServer = STANDARD_SERVER;
		}
		else if (server == commandRules.getRule(STR_INTERSERVER_NOVICE_NAME)){
			currentServer = FAST_TRACK_SERVER;
		}		
		else if (server == commandRules.getRule(STR_INSTANCE_DUNGEON_INTER_SERVER)){
			currentServer = INSTANCE_SERVER;
		}
	}
	
	void moveServer(servers server){
		currentServer = server;
	}
	
//private:
	//RuleStrings* ruleStrings;
};

#endif