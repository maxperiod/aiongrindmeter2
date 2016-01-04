#include "Counter.h"

class Items{
public: 
	Counter& getUsed() {return itemsUsed;}
	Counter& getCrafted() {return itemsCrafted;}
	Counter& getAcquired() {return itemsAcquired;}
	Counter& getPurchased() {return itemsPurchased;}
	void reset();
private:
	Counter itemsUsed;
	Counter itemsCrafted;
	Counter itemsAcquired;
	Counter itemsPurchased;
};