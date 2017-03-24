#ifndef TIMER_H
#define TIMER_H

#include <ctime>

class Timer{
	long startTime; 
	long endTime;

	long previousSessionTime;

	bool started;

public:
	Timer(){
		//startTime = clock();
		//endTime = startTime;
		previousSessionTime = 0;
		started = false;
	}

	void start(){
		if (!started) startTime = clock();
		started = true;
	}

	void stop(){
		endTime = clock();
		previousSessionTime += clock() - startTime;
		started = false;
	}

	void stopWithAdjustmentSeconds(float seconds){
		stop();
		previousSessionTime += seconds * CLOCKS_PER_SEC;
	}

	long getElapsedTime(){
		if (started) return (clock() - startTime + previousSessionTime) / CLOCKS_PER_SEC;
		else return previousSessionTime / CLOCKS_PER_SEC; //(clock() - endTime) / CLOCKS_PER_SEC;
	}

	float calculatePerHourRate(float number){
		int elapsedTime = getElapsedTime();
		if (elapsedTime > 0) return (float)number * 3600 / getElapsedTime() ;
		else return 0;
	}
};

#endif