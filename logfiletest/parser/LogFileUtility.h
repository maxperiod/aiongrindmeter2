#include <string>
#include <vector>
using namespace std;

#include "LogFileReader.h"
#include "MaxPeriodParser.h"
#include "ChatLogCommandFactory.h"
#include "ChatLogCommand.h"
#include "MessageRules.h"
#include "SystemCFG.h"

#include "../language/Language.h"

#include "../Module.h"

class LogFileUtility{
public:
	bool setAionDirectory(const string& aionDirectory);

	bool isValidAionDirectory();
	bool isChatLogEnabled();

	bool enableChatLog();
	bool disableChatLog();
	
	void registerMessageRuleCode(MessageRuleCode messageRuleCode, bool critable = false);
	
	void registerModule(Module& module);

	void parseLogFile();

private:
	string aionDirectory;

	LogFileReader logFileReader;
	ChatLogCommandFactory commandFactory;
	MaxPeriodParser parser;
	SystemCFG systemCFG;

	queue<string> lines;
	queue<ChatLogCommand> parsedChatLogCommands;

	vector<Module*> modules;
};