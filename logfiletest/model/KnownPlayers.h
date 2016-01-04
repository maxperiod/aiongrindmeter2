#ifndef KNOWNPLAYERS_H
#define KNOWNPLAYERS_H

#include <unordered_map>
#include <string>
using namespace std;

#include "PlayerClassManager.h"

class KnownPlayers{
public:
	KnownPlayers(): NO_CLASS(""){}

	void addPlayer(const string& name);
	
	void setPlayerClass(const string& name, const string& playerClass);
	
	unordered_map<string, string>::iterator getPlayersList() {return players.begin();}
	unordered_map<string, string>::iterator getPlayersListEnd() {return players.end();}

	bool isPlayer(const string &name);

	const string& getPlayerClass(const string& name);
	/*static KnownPlayers& getInstance(){
		return instance;
	}*/
private:
	const string NO_CLASS;
	unordered_map<string, string> players;

	//static KnownPlayers instance;
};

#endif