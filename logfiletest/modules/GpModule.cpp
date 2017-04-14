#include "GpModule.h"
#include "../stringFunctions.h"

GpModule::GpModule(){			
	//apGainMeter.setObserver(valueGainObserver);		
	DECLARE_MESSAGE_RULE(STR_MSG_GLORY_POINT_GAIN);
	DECLARE_MESSAGE_RULE(STR_MSG_GLORY_POINT_LOSE);

	//timer.start();
}

void GpModule::executeChatLogCommand(ChatLogCommand& command){
	map<string, string>& params = command.getParams();

	switch(command.getMessageRuleCode()){
	case STR_MSG_GLORY_POINT_GAIN:
		gpGainMeter.gain(stringToInt(params["%num0"]));
		break;
	case STR_MSG_GLORY_POINT_LOSE:
		gpGainMeter.lose(stringToInt(params["%num0"]));
		break;
	}
}

void GpModule::endOfTickAction(){
	gpGainMeter.applyFromBuffer();
}
/*
void GpModule::processLines(){
	//queue<string> lines = logFile.readLines();
	logFile.readLines(lines);	

	while(!lines.empty()){
			
		string line = lines.front();

		bool critical = parser->isCrit(line);

		if (!critical){
			// EXP from a monster/player/NPC
			//if (parser->resembles(line, rules->getRule("STR_MSG_COMBAT_OTHER_FRIENDLY_ATTACK"), params)){
			//}
			
			// Abyss Points
			if (parser->resemblesRule(line, "STR_MSG_GLORY_POINT_GAIN", params)){
				gpGainMeter.gain(stringToInt(params["%num0"]));
			}
			else if (parser->resemblesRule(line, "STR_MSG_GLORY_POINT_LOSE", params)){
				gpGainMeter.lose(stringToInt(params["%num0"]));
			}


	
		}

		lines.pop();
	}
	
	gpGainMeter.applyFromBuffer();	
		
}*/