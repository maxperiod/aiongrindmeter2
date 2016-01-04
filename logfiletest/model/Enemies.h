
class Enemies{
public:
	Counter& getMonstersKilled() {return monstersKilled;}
	DamageInflicted& getTargetsDamagedByMe() {return targetsDamagedByMe;}
	
	KnownPlayers& getKnownPlayers() {return knownPlayers;}
	PvpKillsCounter<string>& getPlayersKilled() {return playersKilled;}
	
	int getNumPvPKills() {return playersKilled.getTotalKills();}
	int getNumPvPDeaths() {return pvpDeaths;}
	int getNumPvPAssists() {return playersKilled.getTotalAssists();}

private:

	Counter monstersKilled;
	DamageInflicted targetsDamagedByMe;

	KnownPlayers knownPlayers;
	PvpKillsCounter<string> playersKilled;
	int pvpDeaths;
};