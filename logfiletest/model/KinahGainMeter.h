#include "MeterValue.h"

class KinahGainMeter: public MeterValue{
public:
	KinahGainMeter(): saleMode(false), npcSales(0){}
	
	void setSaleMode() {
		MeterValue::applyFromBuffer(); 
		saleMode = true;
	}
	long long getNpcSales() {return npcSales;}

	void applyFromBuffer();

private:
	bool saleMode;
	long long npcSales;
};