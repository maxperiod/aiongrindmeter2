#include <fstream>
using namespace std;

#include "ItemIDFileReader.h"

ItemIDFileReader::ItemIDFileReader(string file){
	ifstream stream;
	readFileStatus = false;

	stream.open(file);
	char line[256];
	
	if (stream.is_open()) readFileStatus = true;
	while (stream.good()){
		char* itemName = NULL;
		stream.getline(line, 256);
		
		for (int i = 0; line[i] != NULL; i ++){
			if (line[i] == '\t'){
				if (itemName == NULL) itemName = line + i + 1;
				line[i] = NULL;

			}
		}
		if (itemName != NULL){
			int id = atoi(line);
			string name = string(itemName);					

			itemIDToName.insert(pair<int, string>(id, name));
		}
		
		/*
		for (int i = 0; line[i] != NULL; i ++){
			if (line[i] == '\t'){
				if (itemID == NULL) itemID = line + i + 1;
				line[i] = NULL;

			}
		}
		if (itemID != NULL){
			int id = atoi(itemID);
			string value = string(line);
			

			itemIDToName[id] = value;
		}
		*/
		//itemStringToID[value] = id;
	}
	

	stream.close();
}


