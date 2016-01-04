#include <string>
#include <vector>
using namespace std;

#include "Parser.h"

class UserCommandFactory{
public:
	/*
	 * Set the chat log parser engine to be used by this factory.
	 * setParser must be called first before calling setMessageRules, or the app will crash!
	 */
	void setParser(Parser& parser) {this->parser = &parser;}

	vector<string> getUserCommand(const string& chatLine);

private:
	Parser* parser;
};