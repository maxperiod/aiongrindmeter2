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
			unique_ptr<ChatLogCommand> command(new ChatLogCommand(*iter, params, critical, clock()));
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
