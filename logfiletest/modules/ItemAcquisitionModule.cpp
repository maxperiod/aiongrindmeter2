#include "ItemAcquisitionModule.h"
#include "../stringFunctions.h"
#include "../parser/BracketValueReader.h"
#include "../language/LanguageManager.h"

ItemAcquisitionModule::ItemAcquisitionModule(): idleTicks(0), isContainerOpened(false), diceRollWin(false){
	DECLARE_MESSAGE_RULE(STR_MSG_GET_ITEM_EXTRA_MULTI);
	DECLARE_MESSAGE_RULE(STR_MSG_GET_ITEM_EXTRA);
	DECLARE_MESSAGE_RULE(STR_MSG_GET_ITEM_MULTI);
	DECLARE_MESSAGE_RULE(STR_MSG_GET_ITEM);
	DECLARE_MESSAGE_RULE(STR_MSG_EXP_EXTRACTION_USE);
	DECLARE_MESSAGE_RULE(STR_USE_ITEM);
	DECLARE_MESSAGE_RULE(STR_MSG_ENCHANT_TYPE1_ENCHANT_FAIL);
	DECLARE_MESSAGE_RULE(STR_MSG_STIGMA_ENCHANT_FAIL);
	DECLARE_MESSAGE_RULE(STR_DECOMPOSE_ITEM_SUCCEED);
	DECLARE_MESSAGE_RULE(STR_UNCOMPRESS_COMPRESSED_ITEM_SUCCEEDED);
	DECLARE_MESSAGE_RULE(STR_MSG_DICE_RESULT_ME);
	DECLARE_MESSAGE_RULE(STR_MSG_GET_ITEM_PARTYNOTICE_DICE);
	DECLARE_MESSAGE_RULE(STR_MSG_GET_ITEM_PARTYNOTICE_DICE_GIVEUP_ROLL);
	DECLARE_MESSAGE_RULE(STR_MSG_GET_ITEM_PARTYNOTICE_DICE_WIN);
	DECLARE_MESSAGE_RULE(STR_MSG_GET_ITEM_PARTYNOTICE_DICE_GIVEUP_ROLL_ALL);
	DECLARE_MESSAGE_RULE(STR_PARTY_ITEM_WIN);
}

void ItemAcquisitionModule::acquireItem(const string& item, int quantity){
	vector<string> bracketValues;
	BracketValueReader::readValues(item, bracketValues);
	
	if (!bracketValues.empty() && bracketValues[0] == "@item"){
		int itemNumber = stringToInt(bracketValues[1]);
		//itemsAcquired.add(itemNumber, quantity);
		itemsBuffer.add(itemNumber, quantity);

		if (diceRollWin == true){
			itemRolls.winItem(itemNumber);
			diceRollWin = false;
		}
	}
	idleTicks = 0;	
	//myLastRoll = -1;
}

void ItemAcquisitionModule::otherPlayerWinsItem(const string& winner, const string& item){
	vector<string> bracketValues;
	BracketValueReader::readValues(item, bracketValues);
	itemRolls.didNotWinItem(stringToInt(bracketValues[1]), winner);			
}

void ItemAcquisitionModule::endOfTickAction(){
	idleTicks ++;
	if (idleTicks >= 2){	
		clearTemporaryStates();		
	}
}

void ItemAcquisitionModule::clearTemporaryStates(){
	applyFromBuffer();
	isContainerOpened = false;
	diceRollWin = false;
	idleTicks = 0;
}

void ItemAcquisitionModule::applyFromBuffer(){
	//if (isContainerOpened) containersOpened.add(openedContainerName);
	for (map<int, CounterEntry>::iterator iter = itemsBuffer.begin(); iter != itemsBuffer.end(); iter ++){
		
		if (isContainerOpened){
			itemsFromContainers[openedContainerName].add(iter->first, iter->second.numGained);
			
		}
		else{
			itemsAcquired.add(iter->first, iter->second.numGained);
		}
		//itemsBuffer.erase(iter->first);
	}
	itemsBuffer.eraseAll();
}

void ItemAcquisitionModule::executeChatLogCommand(ChatLogCommand& command){
	map<string, string>& params = command.getParams();

	switch(command.getMessageRuleCode()){
		// get item
		case STR_MSG_GET_ITEM_EXTRA_MULTI:
		case STR_MSG_GET_ITEM_MULTI:
			acquireItem(params["%0"], stringToInt(params["%num1"]));
			break;
				
		case STR_MSG_GET_ITEM_EXTRA:
		case STR_MSG_GET_ITEM:
			acquireItem(params["%0"], 1);
			break;

		// Use exp extraction item
		case STR_MSG_EXP_EXTRACTION_USE:
			//string extractionItem = params["%0"];
			
			containersOpened.add(params["%0"]);			
			itemsFromContainers[params["%0"]].add(LANGUAGE_MANAGER.getCurrentLanguage().getItemIDFileReader().getItemIDFromName(params["%2"]));
			break;

		// use item
		case STR_USE_ITEM:
			//if (!isContainerOpened)
			itemsConsumed.add(params["%0"]);
			break;
		/*
		case STR_MSG_ENCHANT_TYPE1_ENCHANT_FAIL:
			itemsConsumed.add(params["%0"]);
			break;

		case STR_MSG_STIGMA_ENCHANT_FAIL:
			itemsConsumed.add(params["%0"]);
			break;
		*/
		// extract 
		case STR_DECOMPOSE_ITEM_SUCCEED:
			itemsConsumed.add(params["%0"]);
			break;
			
		// open container
		case STR_UNCOMPRESS_COMPRESSED_ITEM_SUCCEEDED:
			isContainerOpened = true;			
			openedContainerName = params["%0"];
			containersOpened.add(openedContainerName);
			if (itemsBuffer.empty()) idleTicks = -4;
			else idleTicks = 0;
			//%0
			break;

		// I roll for item
		case STR_MSG_DICE_RESULT_ME:
			itemRolls.rollForItem(stringToInt(params["%0"]));
			break;

		// roll for item result
		case STR_MSG_GET_ITEM_PARTYNOTICE_DICE:
			itemRolls.addItemRoll(stringToInt(params["%2"]), stringToInt(params["%1"]), params["%0"]);
			break;
		case STR_MSG_GET_ITEM_PARTYNOTICE_DICE_GIVEUP_ROLL:
			itemRolls.addItemRoll(-1, stringToInt(params["%1"]), params["%0"]);
			break;
		case STR_MSG_GET_ITEM_PARTYNOTICE_DICE_WIN:
			clearTemporaryStates();
			itemRolls.addWinningItemRoll();
			diceRollWin = true;
			break;
		case STR_MSG_GET_ITEM_PARTYNOTICE_DICE_GIVEUP_ROLL_ALL:
			break;

		// Other party member wins item
		case STR_PARTY_ITEM_WIN:
			otherPlayerWinsItem(params["%0"], params["%1"]);
			
			break;		

		default:
			clearTemporaryStates();
			break;

	}
	
}