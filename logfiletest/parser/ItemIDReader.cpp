#include "ItemIDReader.h"

string ItemIDReader::getItemName(int ID){	
	map<int, string>::iterator iter = itemIDToName.find(ID);
	if (iter != itemIDToName.end())
		return iter->second; //itemIDToName[ID];
	else 
		return to_string(_Longlong(ID));
}

string ItemIDReader::getItemName(string bracketedItemIdFromChatLog){
	const char* cstring = bracketedItemIdFromChatLog.c_str();
	if ((cstring[0] == '[') &&
		(cstring[1] == 'i') &&
		(cstring[2] == 't') &&
		(cstring[3] == 'e') &&
		(cstring[4] == 'm') &&
		(cstring[5] == ':'))
	{
		char newString[21] = {NULL};
		for (int i = 6; cstring[i] != ';' && cstring[i] != NULL; i ++){
			newString[i-6] = cstring[i];
		}
		int ID = atoi(newString);
		return getItemName(ID);
	}
	else return "0";
	
}
