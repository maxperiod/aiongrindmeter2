#ifndef PVP_KILLS_COUNTER_H
#define PVP_KILLS_COUNTER_H

#include <string>
#include "AbstractCounter.h"


struct PlayerKill{
	int kills;
	int assists;	
};

typedef map<string, PlayerKill> PvPMap;

//template <class T>
class PvpKillsCounter: public AbstractCounter<string, PlayerKill>{
public:
	PvpKillsCounter(): totalKills(0), totalAssists(0), uniqueKills(0){}
	void addKill(const string& name);
	void addAssist(const string& name);

	int getTotalKills() const {return totalKills;}
	int getTotalAssists() const {return totalAssists;}
	int getUniqueKills() const {return uniqueKills;}
private:
	int totalKills;
	int totalAssists;
	int uniqueKills;
};



#endif