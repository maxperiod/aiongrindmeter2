#include "ExpModule.h"
#include "../stringFunctions.h"

ExpModule::ExpModule(): expGainMeter(levelUpChecker) 
	{
		levelUpChecker.setExpChart(expChart);		
		//expGainMeter.setObserver(valueGainObserver);		
		DECLARE_MESSAGE_RULE(STR_GET_EXP_VITAL_MAKEUP_BONUS);
		DECLARE_MESSAGE_RULE(STR_GET_EXP_VITAL_BONUS);
		DECLARE_MESSAGE_RULE(STR_GET_EXP_MAKEUP_BONUS);
		DECLARE_MESSAGE_RULE(STR_GET_EXP);

		DECLARE_MESSAGE_RULE(STR_GET_EXP2_VITAL_MAKEUP_BONUS);
		DECLARE_MESSAGE_RULE(STR_GET_EXP2_VITAL_BONUS);
		DECLARE_MESSAGE_RULE(STR_GET_EXP2_MAKEUP_BONUS);
		DECLARE_MESSAGE_RULE(STR_GET_EXP2);
		
		DECLARE_MESSAGE_RULE(STR_MSG_F2P_GET_EXP_BOOST_VITAL_MAKEUP_BONUS);
		DECLARE_MESSAGE_RULE(STR_MSG_F2P_GET_EXP_BOOST_VITAL_BONUS);				
		DECLARE_MESSAGE_RULE(STR_MSG_F2P_GET_EXP2_BOOST_VITAL_MAKEUP_BONUS);
		DECLARE_MESSAGE_RULE(STR_MSG_F2P_GET_EXP2_BOOST_VITAL_BONUS);		

		DECLARE_MESSAGE_RULE(STR_GET_EXP_PCBANG_VITAL_MAKEUP_BONUS);
		DECLARE_MESSAGE_RULE(STR_GET_EXP_PCBANG_VITAL_BONUS);
		DECLARE_MESSAGE_RULE(STR_GET_EXP2_PCBANG_VITAL_MAKEUP_BONUS);		
		DECLARE_MESSAGE_RULE(STR_GET_EXP2_PCBANG_VITAL_BONUS);

		DECLARE_MESSAGE_RULE(STR_CANNOT_GET_PVP_EXP_TARGET_LIMIT);
		DECLARE_MESSAGE_RULE(STR_CANNOT_GET_PVP_EXP_TIMEBASE_LIMIT);
		DECLARE_MESSAGE_RULE(STR_MSG_ADDEXP_POINT_USE);
		DECLARE_MESSAGE_RULE(STR_MSG_EXP_EXTRACTION_USE);
		DECLARE_MESSAGE_RULE(STR_LEVEL_LIMIT_QUEST_NOT_FINISHED1);
		DECLARE_MESSAGE_RULE(STR_MSG_CANT_NOVICE_SERVER_ALREADY_MAX_LEVEL);

		DECLARE_MESSAGE_RULE(STR_SKILL_LEARNED_NEW_SKILL);

		timer.start();
	}

void ExpModule::executeChatLogCommand(ChatLogCommand& command){
	map<string, string>& params = command.getParams();

	switch(command.getMessageRuleCode()){
	// EXP from a monster/player/NPC
	case STR_GET_EXP_VITAL_MAKEUP_BONUS:
		expGainMeter.gain(stringToInt(params["%num1"]));
		expGainMeter.useRepose(stringToInt(params["%num2"]));
		expGainMeter.useSalvation(stringToInt(params["%num3"]));
		break;
	case STR_GET_EXP_VITAL_BONUS:
		expGainMeter.gain(stringToInt(params["%num1"]));
		expGainMeter.useRepose(stringToInt(params["%num2"]));
		break;
	case STR_GET_EXP_MAKEUP_BONUS:
		expGainMeter.gain(stringToInt(params["%num1"]));
		expGainMeter.useSalvation(stringToInt(params["%num2"]));	
		break;
	case STR_GET_EXP:
		expGainMeter.gain(stringToInt(params["%num1"]));
		break;

	// EXP from no target (gathering/crafting)
	case STR_GET_EXP2_VITAL_MAKEUP_BONUS:
		expGainMeter.gain(stringToInt(params["%num0"]));
		expGainMeter.useRepose(stringToInt(params["%num1"]));
		expGainMeter.useSalvation(stringToInt(params["%num2"]));
		break;
	case STR_GET_EXP2_VITAL_BONUS:
		expGainMeter.gain(stringToInt(params["%num0"]));
		expGainMeter.useRepose(stringToInt(params["%num1"]));
		break;
	case STR_GET_EXP2_MAKEUP_BONUS:
		expGainMeter.gain(stringToInt(params["%num0"]));
		expGainMeter.useSalvation(stringToInt(params["%num1"]));
		break;
	case STR_GET_EXP2:
		expGainMeter.gain(stringToInt(params["%num0"]));
		break;

	// PC Cafe - from a target
	case STR_GET_EXP_PCBANG_VITAL_MAKEUP_BONUS:
		expGainMeter.gain(stringToInt(params["%num1"]));
		expGainMeter.useRepose(stringToInt(params["%num2"]));
		expGainMeter.useSalvation(stringToInt(params["%num3"]));
		break;
	case STR_GET_EXP_PCBANG_VITAL_BONUS:
		expGainMeter.gain(stringToInt(params["%num1"]));
		expGainMeter.useRepose(stringToInt(params["%num2"]));
		break;

	// PC Cafe - gathering/crafting
	case STR_GET_EXP2_PCBANG_VITAL_BONUS:
		expGainMeter.gain(stringToInt(params["%num0"]));
		expGainMeter.useRepose(stringToInt(params["%num1"]));	
		break;
	case STR_GET_EXP2_PCBANG_VITAL_MAKEUP_BONUS:
		expGainMeter.gain(stringToInt(params["%num0"]));
		expGainMeter.useRepose(stringToInt(params["%num1"]));
		expGainMeter.useSalvation(stringToInt(params["%num2"]));
		break;
	
	// PvP XP Cap
	case STR_CANNOT_GET_PVP_EXP_TARGET_LIMIT:
	case STR_CANNOT_GET_PVP_EXP_TIMEBASE_LIMIT:
		expGainMeter.gain(0);

	// Item Exp
	case STR_MSG_ADDEXP_POINT_USE:
		expGainMeter.gain(stringToInt(params["%num1"]));
		break;
	case STR_MSG_EXP_EXTRACTION_USE:
		expGainMeter.spend(stringToInt(params["%num1"]));
		break;

	// Level capped
	case STR_LEVEL_LIMIT_QUEST_NOT_FINISHED1:
	case STR_MSG_CANT_NOVICE_SERVER_ALREADY_MAX_LEVEL:
		levelUpChecker.prohibitLevelUp();
		break;	

	// Level up automatic skill learn
	case STR_SKILL_LEARNED_NEW_SKILL:
		levelUpChecker.levelUpLearnSkill();
		break;
	}

}

void ExpModule::endOfTickAction(){
	expGainMeter.applyFromBuffer();
}


float ExpModule::getWeightedLevelUpsPerHour(){
	if (!levelUpChecker.isInitialized()) return 0;

	float hours = (float)timer.getElapsedTime() / 3600;
	float levelsGainedWeight = 1;
	if (hours >= 1) return timer.calculatePerHourRate(levelUpChecker.getNumLevelsGained());

	levelsGainedWeight = hours;

	float expPerHour = timer.calculatePerHourRate(expGainMeter.getNetGained());
	float projectedDecimalLevelAfterOneHour = levelUpChecker.getProjectedDecimalLevel(expPerHour);	
	/*
	float weightedLevelsGainedPerHour = timer.calculatePerHourRate(
		levelUpChecker.getNumLevelsGained() * levelsGainedWeight);		
	*/
	float weightedLevelUpProjectionPerHour = (projectedDecimalLevelAfterOneHour - levelUpChecker.getCurrentDecimalLevel())
		* (1 - levelsGainedWeight);
		

	return levelUpChecker.getNumLevelsGained() + weightedLevelUpProjectionPerHour;
}
