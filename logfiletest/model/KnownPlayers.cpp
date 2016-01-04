#include "KnownPlayers.h"

void KnownPlayers::addPlayer(const string& name){
	//players.insert(name);
	if (!isPlayer(name)) players[name] = NO_CLASS;
}
	
void KnownPlayers::setPlayerClass(const string& name, const string& playerClass){
	//if (isPlayer(name)) players
	if (name != ""){
		if (playerClass == PlayerClassManager::MULTI_CLASS_SKILL){
			if (!isPlayer(name)) players[name] = NO_CLASS;
		}
		else if (playerClass == PlayerClassManager::PC_AND_NPC_SKILL){
		}
		else {
			if (!isPlayer(name)) players[name] = playerClass;
			else if (players[name] == NO_CLASS || PlayerClassManager::isSuperClass(players[name])){
				players[name] = playerClass;
			}
		}
	}

}
	

bool KnownPlayers::isPlayer(const string &name){
	return players.count(name) == 1;
}

const string& KnownPlayers::getPlayerClass(const string& name){
	if (players.count(name) == 1) return players[name];
	else return NO_CLASS;
}