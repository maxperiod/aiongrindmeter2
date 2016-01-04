#ifndef GATHER_CRAFT_H
#define GATHER_CRAFT_H

#include <string>
#include "GatherCraftRecord.h"
#include "IndividualItemGatherCrafts.h"
using namespace std;


class GatherCraft{
public:
	GatherCraft(): inProgress(false), proc(false){}
	//enum operation{GATHER, CRAFT, MORPH};

	void begin(const string& item);
	//void begin(operation type, string item);
	void success();
	void fail();
	void cancel();
	//void morphSuccess();

	bool isInProgress() {return inProgress;}
	
	GatherCraftRecord& getResult() {return record;}
	IndividualItemGatherCrafts& getIndividualItemGatherCrafts(){
		return individualItemGatheringRecords;
	}
	
	//GatherCraftRecord* getResult(operation mode);
	//IndividualItemGatherCrafts* getIndividualItemGatherCrafts(operation mode);

private:
	GatherCraftRecord record;
	//GatherCraftRecord records[3];
	IndividualItemGatherCrafts individualItemGatheringRecords;
	//IndividualItemGatherCrafts individualItemGatheringRecords[3];

	//operation currentMode;

	string currentItem;	
	string procBase;

	bool inProgress;
	bool proc;
};

#endif