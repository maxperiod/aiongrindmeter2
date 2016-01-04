
#include <Windows.h>

#include "modules/PlayerIdentificationModule.h"
#include "lookups/RuleStringsHardCodedNA.h"
#include "parser/MaxPeriodParser.h"
#include "lookups/SkillToClassHardCodedNA.h"
#include "model/PlayerClassManager.h"

int main(){

	string aionDirectory = "G:/Aion/";
	PlayerIdentificationModule app;
	bool status = app.setAionDirectory(aionDirectory);
	if (!status) cout << "UNABLE TO OPEN CHAT.LOG" << endl;
	
	RULE_STRINGS = new RuleStringsHardCodedNA();
	CLASS_SKILLS = new SkillToClassHardCodedNA();

	MaxPeriodParser parser;	
	parser.setRuleStrings(*RULE_STRINGS);

	app.setParserEngine(parser);

	while(true){
		app.processLines();

		system("cls");
				
		for (unordered_map<string, string>::iterator players = app.knownPlayers.getPlayersList(); 
			players != app.knownPlayers.getPlayersListEnd(); players ++)
		{
			cout << players->first << " (" << PlayerClassManager::getClassName(players->second) << ")" << endl;
		}
		

		Sleep(1000);
	}
}