#include "SoulHealerModule.h"
#include "../stringFunctions.h"

SoulHealerModule::SoulHealerModule(ExpModule& expModule, ApModule& apModule, KinahModule& kinahModule): 
		soulHealer(
			expModule.expGainMeter, 
			expModule.levelUpChecker, 
			apModule.abyssRankChecker, 
			kinahModule.kinahGainMeter, 
			serverState)
{
	DECLARE_MESSAGE_RULE(STR_SKILL_SUCC_SkillATK_Instant_A_TO_ME);
	DECLARE_MESSAGE_RULE(STR_SKILL_SUCC_SpellATK_INTERVAL_TO_ME);
	DECLARE_MESSAGE_RULE(STR_SUCCESS_RECOVER_EXPERIENCE);
	DECLARE_MESSAGE_RULE(STR_DONOT_HAVE_RECOVER_EXPERIENCE);
	DECLARE_MESSAGE_RULE(STR_MSG_COMBAT_MY_DEATH);
	DECLARE_MESSAGE_RULE(STR_DEATH_MESSAGE_ME);
	DECLARE_MESSAGE_RULE(STR_MSG_COMBAT_MY_DEATH_TO_B);
	DECLARE_MESSAGE_RULE(STR_MSG_PvPZONE_MY_DEATH_TO_B);
	DECLARE_MESSAGE_RULE(STR_MSG_MOVE_SERVER_COMPLETE);
}	

void SoulHealerModule::executeChatLogCommand(ChatLogCommand& command){
	map<string, string>& params = command.getParams();

	switch(command.getMessageRuleCode()){
	case STR_SKILL_SUCC_SkillATK_Instant_A_TO_ME:
	case STR_SKILL_SUCC_SpellATK_INTERVAL_TO_ME:
		soulHealer.checkReceivedDamageIsPvp(params["[%SkillName]"]);
		break;

	case STR_SUCCESS_RECOVER_EXPERIENCE:
		soulHealer.soulHeal();
		break;

	case STR_DONOT_HAVE_RECOVER_EXPERIENCE:
		soulHealer.nothingToRecover();
		break;

	// Death
	case STR_MSG_COMBAT_MY_DEATH:
	case STR_DEATH_MESSAGE_ME:
		soulHealer.PvEDeath();
		break;

	case STR_MSG_COMBAT_MY_DEATH_TO_B:
	case STR_MSG_PvPZONE_MY_DEATH_TO_B:
		soulHealer.PvPDeath();
		break;

	case STR_MSG_MOVE_SERVER_COMPLETE:
		serverState.moveServer(params["%0"]);
		break;
	}
}

void SoulHealerModule::endOfTickAction(){

}
/*
void SoulHealerModule::processLines(){
	//queue<string> lines = logFile.readLines();
	logFile.readLines(lines);

	while(!lines.empty()){
			
		string line = lines.front();

		bool critical = parser->isCrit(line);

		if (!critical){
			if (parser->resemblesRule(line, "STR_MSG_COMBAT_OTHER_FRIENDLY_ATTACK", params)){
			}

			// Soul Healing
			else if (parser->resemblesRule(line, "STR_SUCCESS_RECOVER_EXPERIENCE", params)){
				soulHealer.soulHeal();
			}
			else if (parser->resemblesRule(line, "STR_DONOT_HAVE_RECOVER_EXPERIENCE", params)){
				soulHealer.nothingToRecover();
			}

			// Death
			else if (parser->resemblesRule(line, "STR_MSG_COMBAT_MY_DEATH", params)){
				soulHealer.PvEDeath();
			}
			else if (parser->resemblesRule(line, "STR_DEATH_MESSAGE_ME", params)){
				soulHealer.PvEDeath();
			}			
			else if (parser->resemblesRule(line, "STR_MSG_COMBAT_MY_DEATH_TO_B", params)){
				soulHealer.PvPDeath();
			}
			else if (parser->resemblesRule(line, "STR_MSG_PvPZONE_MY_DEATH_TO_B", params)){
				soulHealer.PvPDeath();
			}


			else if (parser->resemblesRule(line, "STR_CHAT_CHANNEL_JOIN", params)){
				
			}
			else if (parser->resemblesRule(line, "STR_MSG_MOVE_SERVER_COMPLETE", params)){
				serverState.moveServer(params["%0"]);
			}

		}

		lines.pop();
	}

}
*/