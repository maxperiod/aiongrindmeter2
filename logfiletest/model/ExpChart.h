#ifndef EXPCHART_H
#define EXPCHART_H

#include <string>
using namespace std;

class ExpChart{
public:
	ExpChart(int levelCap);
	~ExpChart();

	long long getMaxValue(int level);
	
	long long getCumulativeValueForLevel(int level);

	long long getLevelCapValue();

	int getLevelCap() {return levelCap;}
	bool isCumulativeMode() {return cumulativeMode;}

	void addMilestone(int level, string description);

protected:
	int levelCap;
	long long* values;	
	long long* cumulativeValues;
	bool cumulativeMode;

	//int* levelMilestones;
	//string* levelMilestoneNames;
	
	void initCumulativeValuesTable();
};
#endif