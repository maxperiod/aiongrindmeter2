#ifndef EXPCHART_H
#define EXPCHART_H

class ExpChart{
public:
	ExpChart(int levelCap);
	~ExpChart();

	long long getMaxValue(int level);
	
	long long getCumulativeValueForLevel(int level);

	long long getLevelCapValue();

	int getLevelCap() {return levelCap;}
	bool isCumulativeMode() {return cumulativeMode;}

protected:
	int levelCap;
	long long* values;	
	long long* cumulativeValues;
	bool cumulativeMode;	
	
	void initCumulativeValuesTable();
};
#endif