#ifndef ITEM_ID_FILE_READER_H
#define ITEM_ID_FILE_READER_H

#include <string>
#include <map>
using namespace std;
#include "../parser/ItemIDReader.h"

class ItemIDFileReader: public ItemIDReader{
public:
	ItemIDFileReader(string file);
	//string getItemName(int ID);
	//int getItemID(string name);
	//string getItemName(string bracketedItemIdFromChatLog);
	bool isItemIDFileSuccessfullyRead() {return readFileStatus;}

private:
	bool readFileStatus;
	//map<int, string> itemIDToName;
	//map<string, int> itemStringToID;
};
#endif