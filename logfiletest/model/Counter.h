#ifndef COUNTER_H
#define COUNTER_H

#include <string>
#include <list>
using namespace std;

#include "AbstractCounter.h"


struct CounterEntry{
	int numGained;
	int numPackets;	
	//CounterEntry(int numGained, int numPackets): numGained(numGained), numPackets(numPackets){}
};

template <class T>
class Counter: public AbstractCounter<T, CounterEntry>{
public:
	Counter(): totalCount(0), lastUpdated(theMap.end()), lastlastUpdated(theMap.end()) {}
	void add(const T& item);
	void add(const T& item, int count);
	void erase(const T& item);
	
	void eraseAll();

	typename map<T, CounterEntry>::iterator getLastUpdated() {return lastUpdated;}
	
	//typename map<T, CounterEntry>::iterator get(const T& item) {return theMap.find(item);}
	CounterEntry get(const T& item) {return theMap[item];}
	//CounterEntry get(const T& item);

	bool empty() {return theMap.empty();}

	int getTotalCount() {
		return totalCount;
	}
private:	
	typename map<T, CounterEntry>::iterator lastUpdated;
	typename map<T, CounterEntry>::iterator lastlastUpdated;
	int totalCount;

};

template <class T>
void Counter<T>::add(const T& item){
	add(item, 1);
}

template <class T>
void Counter<T>::add(const T& item, int count){
	
	map<T, CounterEntry>::iterator iter = theMap.find(item);

	if (iter == theMap.end()){
	//if (theMap.count(item) == 0){
		CounterEntry entry = {count, 1};	
		iter = theMap.insert(pair<T, CounterEntry>(item, entry)).first;	
	}
	else {	
		iter->second.numGained += count;//theMap.at(item).numGained += count;
		iter->second.numPackets ++;//theMap.at(item).numPackets ++;
	}
	lastlastUpdated = lastUpdated;
	lastUpdated = iter;
	totalCount += count;
}
/*
template <class T>
CounterEntry Counter<T>::get(const T& item) {
	if (theMap.count(item) > 0) return theMap[item];	
	else return {0, 0};
}
*/
/*
template <class T>
void Counter<T>::erase(const T& item){
	//totalCount -= theMap[item];
	if (theMap.count(item) > 0){
		totalCount -= theMap[item].numGained;
		theMap.erase(item);
	}
}
*/

template <class T>
void Counter<T>::erase(const T& item){
	map<T, CounterEntry>::iterator iter = theMap.find(item);
	
	if (iter != theMap.end()){
		
		if (iter == lastUpdated){
			lastUpdated = lastlastUpdated;
		}
		else if (iter == lastlastUpdated){
			lastlastUpdated = lastUpdated;
		}
		totalCount -= iter->second.numGained;
		theMap.erase(iter);
	}

	/*
	if (lastUpdated != theMap.end()){
		totalCount -= lastUpdated->second.numGained;				

		theMap.erase(lastUpdated);
		lastUpdated = lastlastUpdated;		
	}
	*/
	//totalCount -= theMap[item];
	/*
	if (theMap.count(*lastUpdated) > 0){
		totalCount -= theMap[*lastUpdated].numGained;
		theMap.erase(*lastUpdated);
	}
	*/
}

template <class T>
void Counter<T>::eraseAll(){
	theMap.clear();
	lastUpdated = theMap.end();
	lastlastUpdated = theMap.end();
	totalCount = 0;
}

#endif