#ifndef INDIVIDUALITEMGATHERCRAFTS_H
#define INDIVIDUALITEMGATHERCRAFTS_H

#include "AbstractCounter.h"
#include "GatherCraftRecord.h"

//template <class T>
class IndividualItemGatherCrafts: public AbstractCounter<string, GatherCraftRecord>{
public:
	void success(const string& item){
		addEntryToMapIfNecessary(item);
		theMap[item].success();
	}

	void fail(const string& item){
		addEntryToMapIfNecessary(item);
		theMap[item].fail();
	}

	void cancel(const string& item){
		addEntryToMapIfNecessary(item);
		theMap[item].cancel();
	}

	void proc(const string& item){
		theMap[item].proc(true);
	}

	void procFail(const string& procBase){
		theMap[procBase].procFail();
	}

	GatherCraftRecord& getEntry(const string& item){
		return theMap[item];
	}
private:
	bool addEntryToMapIfNecessary(const string &item){
		if (theMap.count(item) == 0){
			GatherCraftRecord record;	
			theMap[item] = record;
			return true;
		}
		return false;
	}
};
#endif