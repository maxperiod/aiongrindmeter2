#include <memory>


#include "MessageRules.h"
#include "LogFileUtility.h"

#include "../language/LanguageManager.h"

bool isFileExists(string& filename);

LogFileUtility::LogFileUtility(): timestampOfLatestMessage(-1) {

}


bool LogFileUtility::setAionDirectory(const string& aionDirectory){
	this->aionDirectory = aionDirectory;
	logFileReader.setDirectory(aionDirectory);
	return logFileReader.openChatLog(aionDirectory);

	
}

void LogFileUtility::registerModule(Module& module){
	modules.push_back(&module);
	const vector<MessageRuleCode>& commandsDeclared = module.getDeclaredChatLogCommands();
	const vector<MessageRuleCode>& critableChatLogCommands = module.getCritableChatLogCommands();
	
	for (vector<MessageRuleCode>::const_iterator iter = commandsDeclared.begin(); iter != commandsDeclared.end(); iter ++){
		bool critable = false;
		for (vector<MessageRuleCode>::const_iterator critIter = critableChatLogCommands.begin(); critIter != critableChatLogCommands.end(); critIter ++){
			if (*iter == *critIter) critable = true;
		}
		
		registerMessageRuleCode(*iter, critable);
	}
}

void LogFileUtility::parseLogFile(){

	parser.setCriticalString(LANGUAGE_MANAGER.getCurrentLanguage().getMessageRules().getCriticalString());
	commandFactory.setParser(parser);
	commandFactory.setMessageRules(LANGUAGE_MANAGER.getCurrentLanguage().getMessageRules());		

	logFileReader.readLines(lines, false);

	if (!lines.empty()) timestampOfLatestMessage = clock();

	//Parse chatlog lines into command object
	while(!lines.empty()){
		string line = lines.front();
		unique_ptr<ChatLogCommand> command = commandFactory.getChatLogCommand(line);	
		if (command) parsedChatLogCommands.push(*command);
		lines.pop();
	}

	//Send commands to all registered module to be invoked
	while (!parsedChatLogCommands.empty()){
		ChatLogCommand& command = parsedChatLogCommands.front();
		for (vector<Module*>::iterator iter = modules.begin(); iter != modules.end(); iter ++){
			Module* module = *iter;
			module->executeChatLogCommand(command);
		}
		parsedChatLogCommands.pop();
	}

	//Invoke end of tick action for all registered modules
	for (vector<Module*>::iterator iter = modules.begin(); iter != modules.end(); iter ++){
		Module* module = *iter;
		module->endOfTickAction();
	}
}

void LogFileUtility::registerMessageRuleCode(MessageRuleCode messageRuleCode, bool critable){
	commandFactory.addParsableMessageRuleCode(messageRuleCode, critable);
}

bool LogFileUtility::isValidAionDirectory(){
	
	if (logFileReader.isOK() || systemCFG.isReadSuccessful()){
		return true;
	}
	else if (isFileExists(aionDirectory + "/bin32/AION.bin") || isFileExists(aionDirectory + "/bin64/AION.bin"))
		return true;

	return false;
}

bool LogFileUtility::isChatLogEnabled(){
	systemCFG.readCFG(aionDirectory + "system.cfg", true);

	if (!systemCFG.isReadSuccessful()) return false;
	
	const CFGmap& systemCFGEntries = systemCFG.getEntries();
	if (systemCFGEntries.count("g_chatlog") != 1) return false;
	else if (systemCFGEntries.at("g_chatlog") != "1") return false;

	return true;
}



bool LogFileUtility::enableChatLog(){
	return false;
}

bool LogFileUtility::disableChatLog(){
	return false;
}


bool isFileExists(string& filename){
	bool fileExists;
	ifstream file;
	file.open(filename);	
	fileExists = !file.fail();	
	file.close();
	return fileExists;
}
