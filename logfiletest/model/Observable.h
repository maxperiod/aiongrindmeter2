#include "Observer.h"

class Observable{
public:
	Observable(): observer(nullptr){}
	

	void setObserver(Observer& observer){
		this->observer = &observer;
	}

	void notifyObserver(){
		if (observer != nullptr) observer->notify();
	}
private:
	Observer* observer;
};