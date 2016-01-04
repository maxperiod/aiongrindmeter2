#ifndef GATHERCRAFTRECORD_H
#define GATHERCRAFTRECORD_H

class GatherCraftRecord{
public:
	GatherCraftRecord(): numSuccess(0), numFailure(0), numCancel(0), 
		numProc(0), numFailedProc(0), totalAttempts(0), procable(false){}
	
	void success();
	void fail();
	void cancel();
	void proc(bool isIndividualRecord = false);
	void procFail();
	
	int getNumSuccess() {return numSuccess;}
	int getNumFailure() {return numFailure;}
	int getNumCancel() {return numCancel;}
	int getNumProcs() {return numProc;}

	int getTotalAttempts() {return totalAttempts;}

	bool isProcable(){return procable;}

private:
	bool procable; 

	int totalAttempts;

	int numSuccess;
	int numFailure;
	int numCancel;
	int numProc;
	int numFailedProc;
};

#endif