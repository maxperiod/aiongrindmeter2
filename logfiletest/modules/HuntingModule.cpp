#include "HuntingModule.h"

HuntingModule::HuntingModule(): ticksSinceLastKill(0){
	DECLARE_MESSAGE_RULE(STR_GET_EXP_VITAL_MAKEUP_BONUS);
	DECLARE_MESSAGE_RULE(STR_GET_EXP_VITAL_BONUS);
	DECLARE_MESSAGE_RULE(STR_GET_EXP_MAKEUP_BONUS);
	DECLARE_MESSAGE_RULE(STR_GET_EXP);
	DECLARE_MESSAGE_RULE(STR_GET_EXP_PCBANG_VITAL_MAKEUP_BONUS);
	DECLARE_MESSAGE_RULE(STR_GET_EXP_PCBANG_VITAL_BONUS);

	DECLARE_MESSAGE_RULE(STR_MSG_COMBAT_HOSTILE_DEATH_TO_ME);
	DECLARE_MESSAGE_RULE(STR_MSG_COMBAT_HOSTILE_DEATH);
	DECLARE_MESSAGE_RULE(STR_MSG_COMBAT_HOSTILE_DEATH_TO_B);
	DECLARE_MESSAGE_RULE(STR_QUEST_SYSTEMMSG_COMPLETE);
}

void HuntingModule::checkAndRegisteringKill(string& target){
	
	//if (!knownPlayers->isPlayer(target) && questNPCs.count(target) == 0){
	lastKill = target;
	if (questNPCs.count(target) == 0){		
		monstersKilled.add(lastKill);
	}
}


void HuntingModule::executeChatLogCommand(ChatLogCommand& command){
	map<string, string>& params = command.getParams();

	switch(command.getMessageRuleCode()){
	case STR_GET_EXP_VITAL_MAKEUP_BONUS:
	case STR_GET_EXP_VITAL_BONUS:
	case STR_GET_EXP_MAKEUP_BONUS:
	case STR_GET_EXP:
	case STR_GET_EXP_PCBANG_VITAL_MAKEUP_BONUS:
	case STR_GET_EXP_PCBANG_VITAL_BONUS:
		checkAndRegisteringKill(params["%0"]);
		ticksSinceLastKill = 0;
		break;

	case STR_MSG_COMBAT_HOSTILE_DEATH_TO_ME:
	case STR_MSG_COMBAT_HOSTILE_DEATH:
		monstersKilled.erase(params["%0"]);
		break;

	case STR_MSG_COMBAT_HOSTILE_DEATH_TO_B:
		monstersKilled.erase(params["%1"]);
		break;

	case STR_QUEST_SYSTEMMSG_COMPLETE:
		if (ticksSinceLastKill <= MAX_TICKS_TO_RECOGNIZE_QUEST_XP){
			questNPCs.insert(lastKill);
			monstersKilled.erase(lastKill);
		}
		break;
	}
	
}

void HuntingModule::endOfTickAction(){
	if (ticksSinceLastKill <= MAX_TICKS_TO_RECOGNIZE_QUEST_XP) ticksSinceLastKill ++;
}

/*
void HuntingModule::processLines(){
	logFile.readLines(lines);

	while(!lines.empty()){
			
		string line = lines.front();

		bool critical = parser->isCrit(line);

		if (!critical){
			// EXP from a monster/player/NPC
			if (parser->resemblesRule(line, "STR_MSG_COMBAT_OTHER_FRIENDLY_ATTACK", params)){
			}
			//else if (parser->resemblesRule(line, "STR_GET_EXP_VITAL_MAKEUP_BONUS"), params)){
			else if (parser->resemblesRule(line, "STR_GET_EXP_VITAL_MAKEUP_BONUS", params)){
				checkAndRegisteringKill(params["%0"]);
			}
			else if (parser->resemblesRule(line, "STR_GET_EXP_VITAL_BONUS", params)){
				checkAndRegisteringKill(params["%0"]);
			}
			else if (parser->resemblesRule(line, "STR_GET_EXP_MAKEUP_BONUS", params)){
				checkAndRegisteringKill(params["%0"]);
			}
			else if (parser->resemblesRule(line, "STR_GET_EXP", params)){				
				checkAndRegisteringKill(params["%0"]);
			}	
			
			// PC Cafe - from a target
			else if (parser->resemblesRule(line, "STR_GET_EXP_PCBANG_VITAL_MAKEUP_BONUS", params)){
				checkAndRegisteringKill(params["%0"]);
			}
			else if (parser->resemblesRule(line, "STR_GET_EXP_PCBANG_VITAL_BONUS", params)){
				checkAndRegisteringKill(params["%0"]);
			}
			
			else if (parser->resemblesRule(line, "STR_MSG_COMBAT_HOSTILE_DEATH_TO_ME", params)){
				monstersKilled.erase(params["%0"]);
			}
			else if (parser->resemblesRule(line, "STR_MSG_COMBAT_HOSTILE_DEATH_TO_B", params)){
				monstersKilled.erase(params["%1"]);
			}
			else if (parser->resemblesRule(line, "STR_MSG_COMBAT_HOSTILE_DEATH", params)){
				monstersKilled.erase(params["%0"]);
			}

			// Quest complete - last "kill" was a quest reward"
			else if (parser->resemblesRule(line, "STR_QUEST_SYSTEMMSG_COMPLETE", params)){
				questNPCs.insert(lastKill);
				monstersKilled.erase(lastKill);
			}
			
		
		}

		lines.pop();
	}
	
		
}
*/