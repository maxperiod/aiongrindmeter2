#include "ChatLogCommandFactory.h"


void ChatLogCommandFactory::addParsableMessageRuleCode(MessageRuleCode command, bool critable){
	bool ruleAlreadyExists = false;
	for (vector<MessageRuleCode>::iterator iter = rulesToBeParsed.begin(); iter != rulesToBeParsed.end(); iter ++){
			
		if (command == *iter) ruleAlreadyExists = true;
	}

	if (!ruleAlreadyExists){
		rulesToBeParsed.push_back(command);
		if (critable) critableRules.insert(command);
	}
}

unique_ptr<ChatLogCommand> ChatLogCommandFactory::getChatLogCommand(const string& chatLine){			
	for (vector<MessageRuleCode>::iterator iter = rulesToBeParsed.begin(); iter != rulesToBeParsed.end(); iter ++){
		
		bool critical = false;
		if (critableRules.count(*iter) == 1) critical = parser->isCrit(chatLine);

		if (parser->resembles(chatLine, commandRules->getRule(*iter), params, critical)){					
			string& timestamp = params["_TIME"];
			struct tm timeTm;
			timeTm.tm_year = atoi(timestamp.substr(0, 4).c_str()) - 1900;
			timeTm.tm_mon = atoi(timestamp.substr(5, 2).c_str()) - 1;
			timeTm.tm_mday = atoi(timestamp.substr(8, 2).c_str());
			timeTm.tm_hour = atoi(timestamp.substr(11, 2).c_str());
			timeTm.tm_min = atoi(timestamp.substr(14, 2).c_str());
			timeTm.tm_sec = atoi(timestamp.substr(17, 2).c_str());

			unique_ptr<ChatLogCommand> command(new ChatLogCommand(*iter, params, critical, mktime(&timeTm)/*clock()*/));
			return command;
		}				
	}
		
	unique_ptr<ChatLogCommand> emptyChatLogCommand;
	return emptyChatLogCommand;
}

void ChatLogCommandFactory::setMessageRules(MessageRules& commandRules){
	this->commandRules = &commandRules;
	parser->setCriticalString(commandRules.getCriticalString());
}
