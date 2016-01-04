#ifndef COMMANDRULES_H
#define COMMANDRULES_H

#include <unordered_map>
#include <string>
//using namespace std;

#include "../lookups/MessageRuleEnums.h"
#include "ChatLogCommand.h"

/*
 * Base abstract class where the contents of the rules map are to be hard-coded in a subclass
 */
class MessageRules{
public:	
	const string& getRule(MessageRuleCode commandIdentifier);
	const string& getCriticalString() {return getRule(STR_SKILL_EFFECT_MSG_CRITICAL);}
	virtual ~MessageRules() = 0;

protected:
	string NULL_STRING;
	unordered_map<MessageRuleCode, string> rules;	
};

inline MessageRules::~MessageRules(){}

extern MessageRules* COMMAND_RULES;
#endif