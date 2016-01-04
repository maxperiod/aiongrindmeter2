#include "GatherCraftRecord.h"

void GatherCraftRecord::success() {
	numSuccess ++;
	totalAttempts ++;
}

void GatherCraftRecord::fail() {
	numFailure ++;
	totalAttempts ++;
}

void GatherCraftRecord::cancel() {
	numCancel ++;
	totalAttempts ++;
}

void GatherCraftRecord::proc(bool isIndividualRecord) {
	numProc ++;		
	if (isIndividualRecord) totalAttempts ++;
	procable = true;
}

void GatherCraftRecord::procFail() {
	numProc --;	
	numSuccess ++;
}
	