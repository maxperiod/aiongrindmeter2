#ifndef MODULE_H
#define MODULE_H

#include <vector>

#include "parser/Parser.h"
//#include "parser/RuleStrings.h"
#include "parser/ChatLogCommand.h"


#define DECLARE_MESSAGE_RULE(messageRuleCode) declaredChatLogCommands.push_back(messageRuleCode)

//This message can include a critical message between the timestamp and the rest of the message
#define DECLARE_CRITABLE_MESSAGE_RULE(messageRuleCode) \
	declaredChatLogCommands.push_back(messageRuleCode); \
	critableChatLogCommands.push_back(messageRuleCode);

class Module{
public:
	virtual void executeChatLogCommand(ChatLogCommand& command) = 0;	
	virtual void endOfTickAction() = 0;
	const vector<MessageRuleCode>& getDeclaredChatLogCommands() {return declaredChatLogCommands;}
	const vector<MessageRuleCode>& getCritableChatLogCommands() {return critableChatLogCommands;}
protected:
	vector<MessageRuleCode> declaredChatLogCommands;
	vector<MessageRuleCode> critableChatLogCommands;
};
#endif