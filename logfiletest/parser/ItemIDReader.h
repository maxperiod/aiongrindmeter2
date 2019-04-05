#ifndef ITEM_ID_READER_H
#define ITEM_ID_READER_H

#include <string>
#include <map>
using namespace std;

class ItemIDReader{
public:
	//ItemIDReader(string file);
	string getItemName(int ID);
	int getItemIDFromName(string& name);
	//int getItemID(string name);
	string getItemName(string bracketedItemIdFromChatLog);
	//bool isItemIDFileSuccessfullyRead() {return readFileStatus;}
	virtual ~ItemIDReader() = 0;
protected:
	//bool readFileStatus;
	map<int, string> itemIDToName;
	//map<string, int> itemStringToID;
};

inline ItemIDReader::~ItemIDReader() {}

#endif