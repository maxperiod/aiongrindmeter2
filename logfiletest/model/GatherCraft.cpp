#include "GatherCraft.h"
void GatherCraft::begin(const string& item){
//void GatherCraft::begin(operation type, string item){
	if (!inProgress){
		//currentMode = type;
		currentItem = item;
		inProgress = true;
	}
	else {
		//individualItemGatheringRecords.success(currentItem);
		individualItemGatheringRecords.proc(currentItem);
		//individualItemGatheringRecords[currentMode].success(currentItem);
		//individualItemGatheringRecords[currentMode].proc(currentItem);
		procBase = currentItem;
		currentItem = item;
		proc = true;
	}
}

void GatherCraft::success(){
	if (inProgress){
		if (proc) {
			//records[currentMode].proc();		
			record.proc();
			
		}
		record.success();
		//records[currentMode].success();
		individualItemGatheringRecords.success(currentItem);
		//individualItemGatheringRecords[currentMode].success(currentItem);
		inProgress = false;
		proc = false;
	}

}

void GatherCraft::fail(){
	if (inProgress){
		if (proc) {
			//record.procFail();
			record.success();

			individualItemGatheringRecords.fail(currentItem);			
			individualItemGatheringRecords.procFail(procBase);
			//individualItemGatheringRecords.success(procBase);
			//records[currentMode].procFail();
			//records[currentMode].success();
		}
		else {
			record.fail();
			//records[currentMode].fail();
			individualItemGatheringRecords.fail(currentItem);
			//individualItemGatheringRecords[currentMode].fail(currentItem);
		}
		inProgress = false;
		proc = false;
	}

}

void GatherCraft::cancel(){
	if (inProgress){
		record.cancel();
		//records[currentMode].cancel();
		individualItemGatheringRecords.cancel(currentItem);
		//individualItemGatheringRecords[currentMode].cancel(currentItem);
		inProgress = false;
		proc = false;
	}
}
/*
void GatherCraft::morphSuccess(){
	if (inProgress){
		records[MORPH].success();
		inProgress = false;
	}
}

GatherCraftRecord* GatherCraft::getResult(operation mode){
	return &records[mode];
}

IndividualItemGatherCrafts* GatherCraft::getIndividualItemGatherCrafts(operation mode){
	return &individualItemGatheringRecords[mode];
}
*/