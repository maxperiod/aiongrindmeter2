#include "ApModule.h"
#include "../stringFunctions.h"
#include "../parser/BracketValueReader.h"

ApModule::ApModule(shared_ptr<ApChart> apChart)
	: apGainMeter(abyssRankChecker, relicAp), isItemSale(false){		
	abyssRankChecker.setExpChart(apChart);
	//apGainMeter.setObserver(valueGainObserver);		

	DECLARE_MESSAGE_RULE(STR_MSG_COMBAT_MY_ABYSS_POINT_GAIN);
	DECLARE_MESSAGE_RULE(STR_MSG_USE_ABYSSPOINT);
	DECLARE_MESSAGE_RULE(STR_CANNOT_GET_AP_TARGET_LIMIT);
	DECLARE_MESSAGE_RULE(STR_CANNOT_GET_AP_TIMEBASE_LIMIT);
	DECLARE_MESSAGE_RULE(STR_MSG_COMBAT_HOSTILE_DEATH_TO_ME);
	DECLARE_MESSAGE_RULE(STR_MSG_COMBAT_HOSTILE_DEATH_TO_B);
	DECLARE_MESSAGE_RULE(STR_MSG_COMBAT_HOSTILE_DEATH);
	DECLARE_MESSAGE_RULE(STR_MSG_GET_SCORE);
	
	DECLARE_MESSAGE_RULE(STR_MSG_GET_ITEM_EXTRA_MULTI);
	DECLARE_MESSAGE_RULE(STR_MSG_GET_ITEM_EXTRA);
	DECLARE_MESSAGE_RULE(STR_MSG_GET_ITEM_MULTI);
	DECLARE_MESSAGE_RULE(STR_MSG_GET_ITEM);

	DECLARE_MESSAGE_RULE(STR_REWARD_ITEM_USER_REWARD_ITEMS);

	//timer.start();
}


int ApModule::parseBracketedItem(const string& item){
	vector<string> bracketValues;
	BracketValueReader::readValues(item, bracketValues);
	
	if (!bracketValues.empty() && bracketValues[0] == "item"){
		return stringToInt(bracketValues[1]);		
	}
		
	return -1;
}


void ApModule::executeChatLogCommand(ChatLogCommand& command){
	map<string, string>& params = command.getParams();

	switch(command.getMessageRuleCode()){
	case STR_MSG_COMBAT_MY_ABYSS_POINT_GAIN:
		if (isItemSale)
			apGainMeter.sellRelic(stringToInt(params["%num0"]));			
		else 
			apGainMeter.gain(stringToInt(params["%num0"]));
		break;

	case STR_MSG_USE_ABYSSPOINT:
		apGainMeter.spend(stringToInt(params["%num0"]));
		break;

	case STR_CANNOT_GET_AP_TARGET_LIMIT:
	case STR_CANNOT_GET_AP_TIMEBASE_LIMIT:
		apGainMeter.gain(0);
		break;

	case STR_MSG_COMBAT_HOSTILE_DEATH_TO_ME:
	case STR_MSG_COMBAT_HOSTILE_DEATH_TO_B:
	case STR_MSG_COMBAT_HOSTILE_DEATH:
		apGainMeter.registerPvpApFromLastGain();
		break;

	case STR_MSG_GET_SCORE:
		apGainMeter.applyFromBuffer();
		break;

	case STR_MSG_GET_ITEM_MULTI:
		apGainMeter.acquireRelic(parseBracketedItem(params["%0"]), stringToInt(params["%num1"])); 
		break;

	case STR_MSG_GET_ITEM:
		apGainMeter.acquireRelic(parseBracketedItem(params["%0"])); 
		break;

	case STR_REWARD_ITEM_USER_REWARD_ITEMS:
		isItemSale = true;
		break;
	}
	

}

void ApModule::endOfTickAction(){
	apGainMeter.applyFromBuffer();	
	isItemSale = false;
}
