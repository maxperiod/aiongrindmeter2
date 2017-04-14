#include "KinahModule.h"
#include "../stringFunctions.h"

 KinahModule::KinahModule(){		
	//kinahGainMeter.setObserver(valueGainObserver);
	DECLARE_MESSAGE_RULE(STR_MSG_GETMONEY);
	DECLARE_MESSAGE_RULE(STR_MSG_GET_POLL_REWARD_MONEY);
	DECLARE_MESSAGE_RULE(STR_MSG_REFUND_MONEY_SYSTEM);
	DECLARE_MESSAGE_RULE(STR_MSG_USEMONEY);
	DECLARE_MESSAGE_RULE(STR_PARTY_DISTRIBUTE_GOLD);
	DECLARE_MESSAGE_RULE(STR_MSG_PAY_DISTRIBUTE);
	DECLARE_MESSAGE_RULE(STR_BUY_SELL_USER_SELL_ITEMS);

	//timer.start();
}

void KinahModule::executeChatLogCommand(ChatLogCommand& command){
	map<string, string>& params = command.getParams();

	switch(command.getMessageRuleCode()){
	case STR_MSG_GETMONEY:
	case STR_MSG_GET_POLL_REWARD_MONEY:
	case STR_MSG_REFUND_MONEY_SYSTEM:
		kinahGainMeter.gain(stringToInt(params["%num0"]));
		break;

	case STR_MSG_USEMONEY:
		kinahGainMeter.spend(stringToInt(params["%num0"]));
		break;

	case STR_PARTY_DISTRIBUTE_GOLD:
		kinahGainMeter.spend(stringToInt(params["%1"]));
		break;

	case STR_MSG_PAY_DISTRIBUTE:
		kinahGainMeter.gain(stringToInt(params["%num2"]));
		break;

	case STR_BUY_SELL_USER_SELL_ITEMS:
		kinahGainMeter.setSaleMode();
		break;
	}
}

void KinahModule::endOfTickAction(){
	kinahGainMeter.applyFromBuffer();
}
/*
void KinahModule::processLines(){
	//queue<string> lines = logFile.readLines();
	logFile.readLines(lines);
		
	while(!lines.empty()){
			
		string line = lines.front();

		bool critical = parser->isCrit(line);

		if (!critical){
		
			// Kinah
			if (parser->resemblesRule(line, "STR_MSG_GETMONEY", params)){
				kinahGainMeter.gain(stringToInt(params["%num0"]));
			}
			else if (parser->resemblesRule(line, "STR_MSG_USEMONEY", params)){
				kinahGainMeter.spend(stringToInt(params["%num0"]));
			}
			else if (parser->resemblesRule(line, "STR_MSG_REFUND_MONEY_SYSTEM", params)){
				kinahGainMeter.gain(stringToInt(params["%num0"]));
			}
			else if (parser->resemblesRule(line, "STR_MSG_GET_POLL_REWARD_MONEY", params)){
				kinahGainMeter.gain(stringToInt(params["%num0"]));
			}
			else if (parser->resemblesRule(line, "STR_PARTY_DISTRIBUTE_GOLD", params)){
				kinahGainMeter.spend(stringToInt(params["%0"]));
			}
			else if (parser->resemblesRule(line, "STR_BUY_SELL_USER_SELL_ITEMS", params)){
				kinahGainMeter.setSaleMode();
			}
			
		}

		lines.pop();
	}

	kinahGainMeter.applyFromBuffer();
		
}
*/