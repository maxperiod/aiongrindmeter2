#include "MessageRules.h"
#include "../exception/NoSuchRuleStringException.h"

MessageRules* COMMAND_RULES = nullptr;

const string& MessageRules::getRule(MessageRuleCode commandIdentifier){
	//string returnRules(rules[ruleIdentifier.c_str()]);
	//return returnRules;
	
	if (rules.count(commandIdentifier) == 1)
		return rules[commandIdentifier];
	else 
		return string(); //throw NoSuchRuleStringException("String for rule not found!");
	
}