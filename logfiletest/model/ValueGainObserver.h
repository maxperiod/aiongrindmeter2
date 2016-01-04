#ifndef VALUEGAINOBSERVER_H
#define VALUEGAINOBSERVER_H

#include "Observer.h"

class ValueGainObserver: public Observer{
public:
	ValueGainObserver(): hasSomethingChanged(false){}
	void notify() {hasSomethingChanged = true;}
	void reset() {hasSomethingChanged = false;}
private:
	bool hasSomethingChanged;
};
#endif