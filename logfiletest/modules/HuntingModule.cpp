#include "HuntingModule.h"
#include "../stringFunctions.h"

HuntingModule::HuntingModule(): ticksSinceLastKill(0){
	/*
	DECLARE_MESSAGE_RULE(STR_GET_EXP_VITAL_MAKEUP_BONUS);
	DECLARE_MESSAGE_RULE(STR_GET_EXP_VITAL_BONUS);
	DECLARE_MESSAGE_RULE(STR_GET_EXP_MAKEUP_BONUS);
	*/
	DECLARE_MESSAGE_RULE(STR_GET_EXP);
	/*
	DECLARE_MESSAGE_RULE(STR_MSG_F2P_GET_EXP_BOOST_VITAL_BONUS);
	DECLARE_MESSAGE_RULE(STR_MSG_F2P_GET_EXP_BOOST_VITAL_MAKEUP_BONUS);
	DECLARE_MESSAGE_RULE(STR_GET_EXP_PCBANG_VITAL_MAKEUP_BONUS);
	DECLARE_MESSAGE_RULE(STR_GET_EXP_PCBANG_VITAL_BONUS);
	*/
	DECLARE_MESSAGE_RULE(STR_SKILL_SUCC_SkillATK_Instant_ME_TO_B);
	DECLARE_MESSAGE_RULE(STR_SKILL_SUCC_CarveSignet_ME_TO_B);
	DECLARE_MESSAGE_RULE(STR_SKILL_SUCC_DispelBuffCounterATK_ME_TO_B);
	DECLARE_MESSAGE_RULE(STR_MSG_COMBAT_MY_CRITICAL);
	DECLARE_MESSAGE_RULE(STR_MSG_COMBAT_MY_ATTACK);


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
	case STR_SKILL_SUCC_SkillATK_Instant_ME_TO_B:
	case STR_SKILL_SUCC_CarveSignet_ME_TO_B:
	case STR_SKILL_SUCC_DispelBuffCounterATK_ME_TO_B:
		damageInflicted.inflictDamage(params["[%SkillTarget]"], atoi(stripCommas(params["%num0"]).c_str()));
		break;
	case STR_MSG_COMBAT_MY_CRITICAL:
	case STR_MSG_COMBAT_MY_ATTACK:
		damageInflicted.inflictDamage(params["%0"], atoi(stripCommas(params["%num1"]).c_str()));
		break;
	/*
	case STR_GET_EXP_VITAL_MAKEUP_BONUS:
	case STR_GET_EXP_VITAL_BONUS:
	case STR_GET_EXP_MAKEUP_BONUS:
	*/
	case STR_GET_EXP:
	/*		
	case STR_MSG_F2P_GET_EXP_BOOST_VITAL_BONUS:
	case STR_MSG_F2P_GET_EXP_BOOST_VITAL_MAKEUP_BONUS:
	case STR_GET_EXP_PCBANG_VITAL_MAKEUP_BONUS:
	case STR_GET_EXP_PCBANG_VITAL_BONUS:*/
		checkAndRegisteringKill(params["%0"]);
		ticksSinceLastKill = 0;
		break;

	case STR_MSG_COMBAT_HOSTILE_DEATH_TO_ME:
		//knownPlayers->addPlayer(params["%0"]);
		playersKilled.addKill(params["%0"]);
		monstersKilled.erase(params["%0"]);		
		break;
	case STR_MSG_COMBAT_HOSTILE_DEATH:
		//knownPlayers->addPlayer(params["%0"]);
		monstersKilled.erase(params["%0"]);		
		if (damageInflicted.getInflictedDamage(params["%0"]) >= 0)
					//pvpAssists ++;
					playersKilled.addAssist(params["%0"]);
		break;

	case STR_MSG_COMBAT_HOSTILE_DEATH_TO_B:
		//knownPlayers->addPlayer(params["%0"]);
		//knownPlayers->addPlayer(params["%1"]);	
		monstersKilled.erase(params["%1"]);
		if (damageInflicted.getInflictedDamage(params["%1"]) >= 0)
			playersKilled.addAssist(params["%1"]);
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