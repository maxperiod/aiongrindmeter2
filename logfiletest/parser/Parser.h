#ifndef PARSER_H
#define PARSER_H

#include <string>
#include <map>
using namespace std;
//#include "RuleStrings.h"

class Parser{
public:
	/*
	 * The timestamp header is in the format of "YYYY.MM.DD HH:MM:SS : "
	 * which is 22 characters before start of message body
	 */
	static const int TIMESTAMP_OFFSET = 22;	

	/*
	 * Extracts the timestamp from the input message line as a string.
	 */
	virtual string getDate(const string& input) = 0;	

	/*
	 * Checks that whether the input message from chat log is a critical hit.
	 * 
	 * For example, if criticalString is "Critical Hit!", the following message returns true:
	 * "2014.10.28 21:14:05 : Critical Hit!You inflicted 716 damage on Nochsana Picket by using Soul Slash III. "
	 * 
	 * And the following message returns false:
	 * "2014.05.24 21:19:20 : Enos Destroyer received 414 damage due to the effect of Reroute Power Effect. "
	 */
	virtual bool isCrit(const string& input) = 0;

	/*
	 * Checks that whether the input message from chat log resembles the rule string.
	 * 
	 * input: The message line received from the chat log
	 * rule: The message to be tested against, with parameters (e.g. %num0, %1, [%SkillName], %0%, %1d)
	 * parameterMap: Parameter values extracted from the chat log message line are added to this map.
	 * critical: Whether the message is a critical hit and should be parsed as such (from isCrit() method)
	 * 
	 * Returns:
	 * True if the input string resembles the rule string.
	 * False otherwise.
	 */
	virtual bool resembles(const string& input, const string &rule, 
		map<string, string>& parametersRecovered, bool critical = false, bool additionalTrailingValues = false) = 0;

	/*
	 * Set the string which indicate a critical hit. For example, for English language it is "Critical Hit!".
	 */
	virtual void setCriticalString(const string& criticalString) = 0;	

};

#endif