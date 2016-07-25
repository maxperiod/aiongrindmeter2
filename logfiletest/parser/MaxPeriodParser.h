#include <string>
#include <map>
#include "Parser.h"
//#include "RuleStrings.h"
using namespace std;

class MaxPeriodParser: public Parser{
public:	
	MaxPeriodParser();
	string getDate(const string &input);

	bool isCrit(const string &input);
	
	bool resembles(const string &input, const string &rule, map<string, string>& parametersRecovered, bool critical = false, bool additionalTrailingValues = false);
	
	void setCriticalString(const string& criticalString);
	
private:
	int criticalStringLength;
	string criticalString;

	int matchesUntilNextParameterMark(const char* a, const char* b);
	int readParameterMark(const char* input);
	int readParameterValue(const char* input, const char* ruleAfterParameter, bool numericOnly = false);
	bool isParameterNumericOnly(const char* percentMark, int numChars);
};