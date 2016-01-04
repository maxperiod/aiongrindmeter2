#ifndef TIMER_H
#define TIMER_H

#include <ctime>

class Timer{
	long startTime; 
	long endTime;

	bool started;

public:
	Timer(){
		startTime = clock();
		endTime = startTime;
		started = false;
	}

	void start(){
		startTime = clock();
		started = true;
	}

	void stop(){
		endTime = clock();
		started = false;
	}

	long getElapsedTime(){
		if (started) return (clock() - startTime) / CLOCKS_PER_SEC;
		else return (clock() - endTime) / CLOCKS_PER_SEC;
	}

	float calculatePerHourRate(float number){
		return (float)number * 3600 / getElapsedTime() ;
	}
};

#endif