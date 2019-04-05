#include "ItemIDReader.h"

string ItemIDReader::getItemName(int ID){	
	map<int, string>::iterator iter = itemIDToName.find(ID);
	if (iter != itemIDToName.end())
		return iter->second; //itemIDToName[ID];
	else 
		return to_string(_Longlong(ID));
}

int ItemIDReader::getItemIDFromName(string& name){
	for (map<int, string>::iterator iter = itemIDToName.begin(); iter != itemIDToName.end(); iter ++){
		if (name.compare(iter->second) == 0) return iter->first;
	}
	return -1;
}

string ItemIDReader::getItemName(string bracketedItemIdFromChatLog){
	const char* cstring = bracketedItemIdFromChatLog.c_str();
	if ((cstring[0] == '[') &&
		(cstring[1] == '@') &&
		(cstring[2] == 'i') &&
		(cstring[3] == 't') &&
		(cstring[4] == 'e') &&
		(cstring[5] == 'm') &&
		(cstring[6] == ':'))
	{
		char newString[21] = {NULL};
		for (int i = 7; cstring[i] != ';' && cstring[i] != NULL; i ++){
			newString[i-7] = cstring[i];
		}
		int ID = atoi(newString);
		return getItemName(ID);
	}
	else return "0";
	
}
