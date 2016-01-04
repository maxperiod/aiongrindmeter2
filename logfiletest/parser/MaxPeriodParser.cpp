
#include "MaxPeriodParser.h"


MaxPeriodParser::MaxPeriodParser(): 
	criticalString(""), criticalStringLength(0){
}

void MaxPeriodParser::setCriticalString(const string& criticalString){
	this->criticalString = criticalString;
	criticalStringLength = criticalString.length();
}


string MaxPeriodParser::getDate(const string &input){
	return input.substr(0, TIMESTAMP_OFFSET - 3);
}


bool MaxPeriodParser::isCrit(const string &input){
	
	const char* rulePointer = criticalString.c_str();
	const char* inputPointer = input.c_str() + TIMESTAMP_OFFSET;
	for (int i = 0; i < criticalStringLength; i ++){
		if (rulePointer[i] != inputPointer[i]) return false;
	}
	return true;
}


bool MaxPeriodParser::resembles(const string &input, const string &rule, map<string, string>& parameterMap, bool critical){
		
	int totalOffset = TIMESTAMP_OFFSET;
	if (critical) totalOffset += criticalStringLength;

	const char* rulePointer = rule.c_str();
	const char* inputPointer = input.c_str() + totalOffset;	//Chop off the date/time from the chat log line.
	
	parameterMap.clear();

	//Iterators for reading characters through the two C-strings. j is for chat log line, i is for rules line.
	int j = 0;
	for (int i = 0; i < rule.size() && j < (input.size() - totalOffset);){
		
		// Rules string iterator sees a parameter ('%' or '[')
		if (rulePointer[i] == '%' || rulePointer[i] == '['){
			// Unless the parameter-starting character is '[', the character following it cannot be '%'
			if (rulePointer[i+1] != '%' || rulePointer[i] == '['){

				int percentMarkLength = readParameterMark(rulePointer + i);
				if (percentMarkLength != 0){
					const char* percentMarkStart = rulePointer + i;
					const char* parameterStart = inputPointer + j;
					
					//Advance rules string iterator past the parameter mark
					i += percentMarkLength;

					bool numericOnly = isParameterNumericOnly(percentMarkStart, percentMarkLength);
										
					int parameterLength = readParameterValue(inputPointer + j, rulePointer + i, numericOnly);
					
					if (parameterLength == -1) {
						parameterMap.clear();
						return false;
					}					
					
					string parameterName (percentMarkStart, percentMarkLength);
					string parameterValue (parameterStart, parameterLength);
					
					parameterMap.insert(pair<string, string>(parameterName, parameterValue));
					
					//Advance chat log line iterator past the extracted parameter
					j += parameterLength;

				}
			}
			// An "%%" is escape sequence for the '%' character
			else if (inputPointer[j] == '%'){
				i += 2;
				j++;
			}
			else{
				parameterMap.clear();
				return false;
			}			
		}
		//Rules line iterator not on a parameter starting mark. Simple character comparison
		else{
			if (rulePointer[i] != inputPointer[j]){
				parameterMap.clear();
				return false;
			}			
			i ++;
			j ++;
		}
	}
	
	return true;	
}

/*
 * This private method is called while reading text parameter values.
 * 
 * input: position of input line iterator while reading a text parameter's value
 * rule: position of rule line iterator after the current parameter's mark
 * 
 * Returns: If input matches rule (until next parameter mark), number of chars matched,
 * 	or -1 if not a match.
 */
int MaxPeriodParser::matchesUntilNextParameterMark(const char* input, const char* rule){	
	int i = 0;
	int j = 0;
	while(true){
		if (rule[i] == NULL) return i;
		if (input[j] == NULL) return -1;					
		if (rule[i] == '[')
			if (rule[i+1] == '%')
				return i;
		if (rule[i] == '%'){
			if (rule[i+1] == '%') i ++;
			else
				return i;
		}			
		if (rule[i] != input[j]) return -1;				
	
		i++;
		j++;
	}
}

/*
 * Private - "Read" the parameter mark in the rules line.
 * First character starts with a parameter marking character 
 * 
 * rule: Pointer to the parameter marking character ('%' or '[') from the rules line
 * 
 * Returns: Number of the characters of the parameter mark
 */
int MaxPeriodParser::readParameterMark(const char* rule){
	//First character starts with '%'. We assume these must contain a digit near the end.
	//After the ending digit, it may contain a 'd' or a '%' sign.
	if (rule[0] == '%'){
		int numChars = 1;
		for (int i = 1; ; i ++){
			if (rule[i] == NULL) return 0; 			
			numChars ++;
			if (rule[i] >= '0' && rule[i] <= '9'){
				if (rule[i+1] == 'd' || (rule[i+1] == '%' && rule[i+2] != '%')) numChars ++;
				return numChars;
			}
		}
		return numChars;
	}
	//First character starts with '[' A square bracketed, so it's a square bracket parameter
	//Square bracket parameters must end with a ']'
	//For now we assue the second character must be a '%'
	else if (rule[0] == '['){
		int numChars = 2;
		if (rule[1] != '%') return 0;
		for (int i = 2; ; i ++){
			if (rule[i] == NULL) return 0; 			
			numChars ++;
			if (rule[i] == ']') return numChars;
		}
		return numChars;
	}
	return 0;
}

/*
 * Private - "Reads" the value of the parameter from the chat log line.
 * 
 * input: pointer to first character of the supposedly parameter value from the chat log line.
 * ruleAfterParameter: pointer to the character right after the parameter mark in the rules line
 * numericOnly: whether the parameter to be read is numeric only (digits, ',' or '.' or ' ')
 * 
 * Return value: Number of characters for the parameter value, or -1 if nothing matches ruleAfterParameter
 */
int MaxPeriodParser::readParameterValue(const char* input, const char* ruleAfterParameter, bool numericOnly){
	// Case 1: if parameter mark is at the end of the rules line
	if (ruleAfterParameter[0] == NULL){
		for (int i = 0; ; i ++){
			if (input[i] == NULL) return i - 1;
		}
	}	
	// Case 2: numeric-only parameter
	else if (numericOnly){
		if (input[0] < '0' || input[0] > '9') return -1;
		
		int lastDigit = 0;		
		for (int i = 1; ; i ++){			
			if (input[i] >= '0' && input[i] <= '9'){
				lastDigit = i;
			}
			else if (input[i] != ',' && input[i] != '.' && input[i] != ' '){
				return lastDigit + 1;
			}
																			
		}
	}
	// Case 3: Anything else
	else {
		for (int i = 0; ; i ++){
			if (input[i] == NULL) return -1;			
			if (matchesUntilNextParameterMark(input + i, ruleAfterParameter) != -1){
				return i;
			}
		}
	}
}

/*
 * Private - Is this a numeric parameter, where the parameter name is %num0 through %num9?
 * 
 * percentMark: Pointer to the first character of the parameter mark
 * numChars: number of characters for the parameter mark
 */
bool MaxPeriodParser::isParameterNumericOnly(const char* percentMark, int numChars){
	if (numChars != 5) return false;
	if (percentMark[1] == 'n' && percentMark[2] == 'u' && percentMark[3] == 'm') 			
		return true;
	return false;
}
