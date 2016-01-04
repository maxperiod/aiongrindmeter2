#include "BracketValueReader.h"


void BracketValueReader::readValues(const string& input, vector<string>& values){
		
	const char* inputPointer = input.c_str();
				
	if (input.size() > 0 && inputPointer[0] == '[' && inputPointer[input.size() - 1] == ']'){
		int valueStart = 1;		
		char delimiter = ':';
			
		for (int i = 1; i < input.size() - 1; i ++){
			if (inputPointer[i] == delimiter){
				string value(inputPointer, valueStart, i - valueStart);
				values.push_back(value);
				valueStart = i + 1;
				delimiter = ';';
			}
						
		}
		string value(inputPointer, valueStart, input.size() - 1 - valueStart);
		values.push_back(value);
			 
	}
		
}
