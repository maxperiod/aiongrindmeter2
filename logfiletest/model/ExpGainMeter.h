#ifndef EXPGAINMETER_H
#define EXPGAINMETER_H

#include "MeterValue.h"
#include "LevelUpChecker.h"

class ExpGainMeter: public MeterValue{	
public:
	ExpGainMeter(LevelUpChecker& expChart): repose(0), salvation(0){
		expChart.setReferringMeter(*this);
		this->expChart = &expChart;
		//expChart.setReferringMeter(this);
	}
	/*
	void setExpChart(LevelUpChecker& expChart){
		expChart.setReferringMeter(*this);
		this->expChart = &expChart;
		
	}
	*/
	void useRepose(int amount) {repose += amount;}
	void useSalvation(int amount) {salvation += amount;}

	long getReposeUsed() {return repose;}
	long getSalvationUsed() {return salvation;}

	/*
	bool init(int level, int exp){
		return expChart.initialize(level, exp);
	};



	int getCurrentLevel() {return expChart.getCurrentLevel();}
	int getCurrentExp() {return expChart.getCurrentValue();}
	int getNextLevelExp() {return expChart.getCurrentLevelMaxValue();}

	bool setCurrentExp(int newValue);

	void prohibitLevelUp() {expChart.prohibitLevelUp();}

	//void checkLevelUp();	
	*/
	void applyFromBuffer();

private:
	
	LevelUpChecker* expChart;

	long repose;
	long salvation;
};

#endif