#include "PlayerIdentificationModule.h"
#include "../language/LanguageManager.h"

PlayerIdentificationModule::PlayerIdentificationModule(){
	DECLARE_MESSAGE_RULE(STR_MSG_GET_ITEM_EXTRA_MULTI);
	DECLARE_CRITABLE_MESSAGE_RULE(STR_SKILL_SUCC_SkillATK_Instant_A_TO_ME);
	DECLARE_CRITABLE_MESSAGE_RULE(STR_SKILL_SUCC_SpellATK_Instant_A_TO_ME);
	DECLARE_CRITABLE_MESSAGE_RULE(STR_SKILL_SUCC_SkillATK_Instant_A_TO_B);
	DECLARE_CRITABLE_MESSAGE_RULE(STR_SKILL_SUCC_SpellATK_Instant_A_TO_B);	
	DECLARE_MESSAGE_RULE(STR_MSG_COMBAT_HOSTILE_DEATH_TO_ME);
	DECLARE_MESSAGE_RULE(STR_MSG_COMBAT_MY_DEATH_TO_B);
	DECLARE_MESSAGE_RULE(STR_MSG_COMBAT_FRIENDLY_DEATH);
	DECLARE_MESSAGE_RULE(STR_MSG_COMBAT_HOSTILE_DEATH);
	DECLARE_MESSAGE_RULE(STR_MSG_COMBAT_HOSTILE_DEATH_TO_B);
	DECLARE_MESSAGE_RULE(STR_MSG_COMBAT_FRIENDLY_DEATH_TO_B);
}

void PlayerIdentificationModule::identifyPlayerClass(string& name, string& skill){			
	string playerClass = LANGUAGE_MANAGER.getCurrentLanguage().getSkillToClassMap().getClass(skill);
	if (playerClass != "") knownPlayers.setPlayerClass(name, playerClass);
}

void PlayerIdentificationModule::executeChatLogCommand(ChatLogCommand& command){
	map<string, string>& params = command.getParams();

	switch(command.getMessageRuleCode()){
	case STR_SKILL_SUCC_SkillATK_Instant_A_TO_ME:
	case STR_SKILL_SUCC_SpellATK_Instant_A_TO_ME:
		identifyPlayerClass(params["[%SkillCaster]"], params["[%SkillName]"]);
		break;
	case STR_SKILL_SUCC_SkillATK_Instant_A_TO_B:
	case STR_SKILL_SUCC_SpellATK_Instant_A_TO_B:
		identifyPlayerClass(params["[%SkillCaster]"], params["[%SkillName]"]);
		break;
	case STR_MSG_COMBAT_HOSTILE_DEATH_TO_ME:
	case STR_MSG_COMBAT_MY_DEATH_TO_B:
	case STR_MSG_COMBAT_FRIENDLY_DEATH:
	case STR_MSG_COMBAT_HOSTILE_DEATH:
		knownPlayers.addPlayer(params["%0"]);
		break;
	case STR_MSG_COMBAT_HOSTILE_DEATH_TO_B:
	case STR_MSG_COMBAT_FRIENDLY_DEATH_TO_B:
		knownPlayers.addPlayer(params["%0"]);
		knownPlayers.addPlayer(params["%1"]);
		break;
	}
}

void PlayerIdentificationModule::endOfTickAction(){

}
/*
void PlayerIdentificationModule::processLines(){
	logFile.readLines(lines);	

	while(!lines.empty()){
			
		string line = lines.front();

		bool critical = parser->isCrit(line);

		
		// Enemy on me
		if (parser->resemblesRule(line, "STR_SKILL_SUCC_SkillATK_Instant_A_TO_ME", params, critical)){
								
			identifyPlayerClass(params["[%SkillCaster]"], params["[%SkillName]"]);
		}
		else if (parser->resemblesRule(line, "STR_SKILL_SUCC_SpellATK_Instant_A_TO_ME", params, critical)){
			identifyPlayerClass(params["[%SkillCaster]"], params["[%SkillName]"]);
		}
			
		//Other on other
		else if (parser->resemblesRule(line, "STR_SKILL_SUCC_SkillATK_Instant_A_TO_B", params, critical)){
			identifyPlayerClass(params["[%SkillCaster]"], params["[%SkillName]"]);
		}		
		else if (parser->resemblesRule(line, "STR_SKILL_SUCC_SpellATK_Instant_A_TO_B", params, critical)){
			identifyPlayerClass(params["[%SkillCaster]"], params["[%SkillName]"]);
		}		

		else if (!critical){
			// Player kills and deaths
			if (parser->resemblesRule(line, "STR_MSG_COMBAT_HOSTILE_DEATH_TO_ME", params)){
				knownPlayers.addPlayer(params["%0"]);

			}
			else if (parser->resemblesRule(line, "STR_MSG_COMBAT_HOSTILE_DEATH_TO_B", params)){
				knownPlayers.addPlayer(params["%0"]);
				knownPlayers.addPlayer(params["%1"]);
			}
			else if (parser->resemblesRule(line, "STR_MSG_COMBAT_MY_DEATH_TO_B", params)){
				knownPlayers.addPlayer(params["%0"]);				
			}
			else if (parser->resemblesRule(line, "STR_MSG_COMBAT_FRIENDLY_DEATH_TO_B", params)){
				knownPlayers.addPlayer(params["%0"]);
				knownPlayers.addPlayer(params["%1"]);				
			}
			else if (parser->resemblesRule(line, "STR_MSG_COMBAT_FRIENDLY_DEATH", params)){
				knownPlayers.addPlayer(params["%0"]);			
			}
			else if (parser->resemblesRule(line, "STR_MSG_COMBAT_HOSTILE_DEATH", params)){
				knownPlayers.addPlayer(params["%0"]);			
			}

			
		}
		lines.pop();
	}
	
}
*/