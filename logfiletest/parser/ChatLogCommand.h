#ifndef COMMAND_H
#define COMMAND_H

#include <string>
#include <map>
#include <ctime>
using namespace std;

#include "../lookups/MessageRuleEnums.h"

class ChatLogCommand{
public:
	ChatLogCommand(MessageRuleCode messageRuleCode, map<string, string>& params, bool critical, time_t timestamp)
		: messageRuleCode(messageRuleCode), params(params), critical(critical), timestamp(timestamp){}

	MessageRuleCode getMessageRuleCode() {return messageRuleCode;}
	map<string, string>& getParams() {return params;}
	bool isCritical() {return critical;}
	time_t getTimestamp() {return timestamp;}
private:
	MessageRuleCode messageRuleCode;	 
	map<string, string> params;
	bool critical;
	time_t timestamp;
};

#endif