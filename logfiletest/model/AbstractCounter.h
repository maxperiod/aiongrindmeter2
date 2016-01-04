#ifndef ABSTRACT_COUNTER_H
#define ABSTRACT_COUNTER_H

#include <map>
using namespace std;

template <class T, class Y>
class AbstractCounter{
public:
	typename map<T, Y>::iterator begin(){
		return theMap.begin();
	}
	typename map<T, Y>::iterator end(){
		return theMap.end();
	}
	virtual ~AbstractCounter() = 0;
protected:
	map<T, Y> theMap;
};

template <class T, class Y>
AbstractCounter<T, Y>::~AbstractCounter() {
}

#endif

