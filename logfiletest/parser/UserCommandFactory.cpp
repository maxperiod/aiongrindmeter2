#include <map>
using namespace std;

#include "UserCommandFactory.h"


vector<string> UserCommandFactory::getUserCommand(const string& chatLine){
	vector<string> arguments;
	map<string, string> params;

	if (parser->resembles(chatLine, "%0: .%1", params)){					
		string& name = params["%0"];
		string& message = params["%1"];
		const char* rawName = name.c_str();
		const char* rawParams = message.c_str();

		int stage = 0;
		if (name[0] != '['){
			for (int i = 1; i < message.length(); i ++){
				if (rawParams[i] == ' '){
					if (stage == 0) {
						string command(rawParams, i);
						arguments.push_back(command);
						
						stage = i + 1;
						//if (rawParams[i] == NULL) return arguments;
					}
					else if (rawParams[i-1] == ' '){
						stage = i + 1;
						//if (rawParams[i] == NULL) return arguments;
					}
					
				}
			}
			string argument(rawParams + stage, message.length() - stage);
			arguments.push_back(argument);
		}
	}
	return arguments;
}