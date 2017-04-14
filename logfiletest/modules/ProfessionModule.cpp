#include "ProfessionModule.h"

ProfessionModule::ProfessionModule(): professionMode(NONE){
	DECLARE_MESSAGE_RULE(STR_MSG_GET_ITEM_MULTI);
	DECLARE_MESSAGE_RULE(STR_MSG_GET_ITEM);
	DECLARE_MESSAGE_RULE(STR_GATHER_START_1_BASIC);
	DECLARE_MESSAGE_RULE(STR_EXTRACT_GATHER_START_1_BASIC);
	DECLARE_MESSAGE_RULE(STR_COMBINE_START);
	DECLARE_MESSAGE_RULE(STR_GATHERING_SUCCESS_GETEXP);
	DECLARE_MESSAGE_RULE(STR_EXTRACT_GATHERING_SUCCESS_GETEXP);
	DECLARE_MESSAGE_RULE(STR_CRAFT_SUCCESS_GETEXP);
	DECLARE_MESSAGE_RULE(STR_GATHER_SUCCESS_1_BASIC);
	DECLARE_MESSAGE_RULE(STR_EXTRACT_GATHER_SUCCESS_1_BASIC);
	DECLARE_MESSAGE_RULE(STR_COMBINE_SUCCESS);
	DECLARE_MESSAGE_RULE(STR_GATHER_FAIL_1_BASIC);
	DECLARE_MESSAGE_RULE(STR_EXTRACT_GATHER_FAIL_1_BASIC);
	DECLARE_MESSAGE_RULE(STR_COMBINE_FAIL);
	DECLARE_MESSAGE_RULE(STR_GATHER_CANCEL_1_BASIC);
	DECLARE_MESSAGE_RULE(STR_EXTRACT_GATHER_CANCEL_1_BASIC);
	DECLARE_MESSAGE_RULE(STR_COMBINE_CANCEL);
	DECLARE_MESSAGE_RULE(STR_COMBINE_COMBO_FAIL_MULTI);
	DECLARE_MESSAGE_RULE(STR_COMBINE_COMBO_FAIL);
	DECLARE_MESSAGE_RULE(STR_GATHER_SKILL_POINT_UP);
	DECLARE_MESSAGE_RULE(STR_COMBINE_SKILL_POINT_UP);
	DECLARE_MESSAGE_RULE(STR_CRAFT_INFO_MAXPOINT_UP);		
	
	DECLARE_MESSAGE_RULE(STR_MSG_HIGHCRAFT_COMPLETE_NOR_STACKABLE);
	DECLARE_MESSAGE_RULE(STR_MSG_HIGHCRAFT_COMPLETE_NOR);	
	DECLARE_MESSAGE_RULE(STR_MSG_HIGHCRAFT_COMPLETE_CRI_STACKABLE);
	DECLARE_MESSAGE_RULE(STR_MSG_HIGHCRAFT_COMPLETE_CRI);
	

	//timer.start();
}

void ProfessionModule::executeChatLogCommand(ChatLogCommand& command){
	map<string, string>& params = command.getParams();

	switch(command.getMessageRuleCode()){
	case STR_MSG_GET_ITEM_MULTI:
	case STR_MSG_GET_ITEM:
		gathers.success();
		break;

	case STR_GATHER_START_1_BASIC:
	case STR_EXTRACT_GATHER_START_1_BASIC:
		gathers.begin(params["%0"]);
		professionMode = GATHER;
		break;
		
	case STR_COMBINE_START:
		crafts.begin(params["%0"]);
		professionMode = CRAFT;
		break;

	case STR_GATHERING_SUCCESS_GETEXP:
	case STR_EXTRACT_GATHERING_SUCCESS_GETEXP:
		gatherLeveling.gainProfessionExp();
		break;

	case STR_CRAFT_SUCCESS_GETEXP:
		craftLeveling.gainProfessionExp();
		crafts.success();
		break;

	case STR_GATHER_SUCCESS_1_BASIC:
	case STR_EXTRACT_GATHER_SUCCESS_1_BASIC:
		gathers.success();
		break;

	case STR_COMBINE_SUCCESS:
		crafts.success();
		break;

	case STR_GATHER_FAIL_1_BASIC:
	case STR_EXTRACT_GATHER_FAIL_1_BASIC:
		gathers.fail();
		break;

	case STR_COMBINE_FAIL:
		crafts.fail();
		break;

	case STR_GATHER_CANCEL_1_BASIC:
	case STR_EXTRACT_GATHER_CANCEL_1_BASIC:
		gathers.cancel();
		break;

	case STR_COMBINE_CANCEL:
		crafts.cancel();
		break;

	case STR_COMBINE_COMBO_FAIL_MULTI:
	case STR_COMBINE_COMBO_FAIL:
		crafts.fail();
		break;
	

	case STR_GATHER_SKILL_POINT_UP:
	case STR_COMBINE_SKILL_POINT_UP:
		if (professionMode == GATHER)
			gatherLeveling.levelUp(params["%0"], stringToInt(params["%1"]));
		else if (professionMode == CRAFT)
			craftLeveling.levelUp(params["%0"], stringToInt(params["%1"]));
		break;

	case STR_CRAFT_INFO_MAXPOINT_UP:
		if (professionMode == GATHER)
			gatherLeveling.levelCapped();
		else if (professionMode == CRAFT)
			craftLeveling.levelCapped();
		break;
		
	case STR_MSG_HIGHCRAFT_COMPLETE_NOR_STACKABLE:
	case STR_MSG_HIGHCRAFT_COMPLETE_NOR:
	case STR_MSG_HIGHCRAFT_COMPLETE_CRI_STACKABLE:
	case STR_MSG_HIGHCRAFT_COMPLETE_CRI:
		crafts.begin(params["%0"]);
		professionMode = CRAFT;
		crafts.success();
		break;
	
	}

}

void ProfessionModule::endOfTickAction(){
}

/*
void ProfessionModule::processLines(){
	
	//queue<string> lines = logFile.readLines();
	logFile.readLines(lines);	

	while(!lines.empty()){
			
		string line = lines.front();

		bool critical = parser->isCrit(line);

		if (!critical){

			if (parser->resemblesRule(line, "STR_MSG_COMBAT_OTHER_FRIENDLY_ATTACK", params)){
			}

			//Acquire item
			else if (parser->resemblesRule(line, "STR_GET_ITEM", params)){
				gathers.success();
			}

			// Start gather/craft
			else if (parser->resemblesRule(line, "STR_GATHER_START_1_BASIC", params)){
				gathers.begin(params["%0"]);
				professionMode = GATHER;
			}
			else if (parser->resemblesRule(line, "STR_EXTRACT_GATHER_START_1_BASIC", params)){
				gathers.begin(params["%0"]);
				professionMode = GATHER;
			}	
			else if (parser->resemblesRule(line, "STR_COMBINE_START", params)){
				crafts.begin(params["%0"]);
				professionMode = CRAFT;
			}	
				
				
			// Gain exp
			else if (parser->resemblesRule(line, "STR_GATHERING_SUCCESS_GETEXP", params)){
				gatherLeveling.gainProfessionExp();
			}
			else if (parser->resemblesRule(line, "STR_EXTRACT_GATHERING_SUCCESS_GETEXP", params)){
				gatherLeveling.gainProfessionExp();
			}
			else if (parser->resemblesRule(line, "STR_CRAFT_SUCCESS_GETEXP", params)){
				craftLeveling.gainProfessionExp();
				crafts.success();
			}

			// Success
			
			else if (parser->resemblesRule(line, "STR_GATHER_SUCCESS_1_BASIC", params)){

			}
			else if (parser->resemblesRule(line, "STR_EXTRACT_GATHER_SUCCESS_1_BASIC", params)){

			}
			else if (parser->resemblesRule(line, "STR_COMBINE_SUCCESS", params)){
				crafts.success();
			}
					

			// Fail
			else if (parser->resemblesRule(line, "STR_GATHER_FAIL_1_BASIC", params)){
				gathers.fail();
			}
			else if (parser->resemblesRule(line, "STR_EXTRACT_GATHER_FAIL_1_BASIC", params)){
				gathers.fail();
			}
			else if (parser->resemblesRule(line, "STR_COMBINE_FAIL", params)){
				crafts.fail();
			}

			// Cancel
			else if (parser->resemblesRule(line, "STR_GATHER_CANCEL_1_BASIC", params)){
				gathers.cancel();
			}
			else if (parser->resemblesRule(line, "STR_EXTRACT_GATHER_CANCEL_1_BASIC", params)){
				gathers.cancel();
			}
			else if (parser->resemblesRule(line, "STR_COMBINE_CANCEL", params)){
				crafts.cancel();
			}

			// Proc failure
			else if (parser->resemblesRule(line, "STR_COMBINE_COMBO_FAIL_MULTI", params)){
				crafts.fail();
			}
			else if (parser->resemblesRule(line, "STR_COMBINE_COMBO_FAIL", params)){
				crafts.fail();
			}

			else if (parser->resemblesRule(line, "STR_GATHER_SKILL_POINT_UP", params)
				|| parser->resemblesRule(line, "STR_COMBINE_SKILL_POINT_UP", params))
			{					
				if (professionMode == GATHER)
					gatherLeveling.levelUp(params["%0"], stringToInt(params["%1"]));
				else if (professionMode == CRAFT)
					craftLeveling.levelUp(params["%0"], stringToInt(params["%1"]));
			}
				
	
			// Level capped
			else if (parser->resemblesRule(line, "STR_CRAFT_INFO_MAXPOINT_UP", params)){
				if (professionMode == GATHER)
					gatherLeveling.levelCapped();
				else if (professionMode == CRAFT)
					craftLeveling.levelCapped();
			}		
		


		}
		lines.pop();
	
	}
}
*/