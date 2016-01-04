#include <string>
#include <memory>
#include <unordered_set>
using namespace std;

#include "ChatLogCommand.h"
#include "Parser.h"
#include "MessageRules.h"

class ChatLogCommandFactory{
public:
	/*
	 * Add a command code where each chat log message to be parsed against. Only command types registered
	 * through this method will be parsed against. 
	 * 
	 * It takes too much computing power to match many chat log lines against every possible message rule
	 * definition in Aion (4,400+ entries in ChatLogCommandStringsNAEnglish)
	 */
	void addParsableMessageRuleCode(MessageRuleCode command, bool critable = false);
	
	/*
	 * Extract the command and its parameters from the chat log line. The chat log line is compared against
	 * every command rule registered through addParseableMessageRuleCode.
	 */
	unique_ptr<ChatLogCommand> getChatLogCommand(const string& chatLine);
	
	/*
	 * Set the chat log parser engine to be used by this factory.
	 * setParser must be called first before calling setMessageRules, or the app will crash!
	 */
	void setParser(Parser& parser) {this->parser = &parser;}

	/*
	 * The actual rule strings are harded coded in a subclass of commandRules, mapped to
	 * enum keys which allows parsings to be done in 25% less time than string keys.
	 * Attach the rule string-
	 * 
	 * setParser must be called first before calling setMessageRules, 
	 * or the app will crash!
	 */
	void setMessageRules(MessageRules& commandRules); 

protected:
	Parser* parser;
	MessageRules* commandRules;
	vector<MessageRuleCode> rulesToBeParsed;
	unordered_set<MessageRuleCode> critableRules;
	map<string, string> params;
};