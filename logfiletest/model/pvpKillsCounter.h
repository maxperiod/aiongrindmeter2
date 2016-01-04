#ifndef PVP_KILLS_COUNTER_H
#define PVP_KILLS_COUNTER_H

#include <string>
#include "AbstractCounter.h"


struct PlayerKill{
	int kills;
	int assists;	
};

//template <class T>
class PvpKillsCounter: public AbstractCounter<string, PlayerKill>{
public:
	PvpKillsCounter(): totalKills(0), totalAssists(0){}
	void addKill(const string& name);
	void addAssist(const string& name);

	int getTotalKills() {return totalKills;}
	int getTotalAssists() {return totalAssists;}
private:
	int totalKills;
	int totalAssists;
};



#endif