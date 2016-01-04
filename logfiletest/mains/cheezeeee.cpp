#include <iostream>
#include <string>
#include <queue>

using namespace std;

#include "../model/Counter.h"
#include "../model/KnownPlayers.h"
#include "../model/AssistDamage.h"
#include "../model/pvpKillsCounter.h"
#include "../model/KinahGainMeter.h"
#include "../parser/LogFile.h"
//#include "parser/decipher.h"
#include "../parser/MaxPeriodParser.h"
#include "../lookups/RuleStringsHardCodedNA.h"

#include "../lookups/ItemIDFileReader.h"
//#include "lookups/ItemNamesHardCodedNA.h"


#include "Timer.h"

#include "windows.h"
#include "stringFunctions.h"

#include "AionAddon.h"
/*
struct itemCount{
	string item;
	int count;
};
*/
class Cheezeeee: public AionAddon{
public:

	LogFileReader logFile;

	
	ItemIDFileReader itemIDReader;
	//ItemNamesHardCodedNA itemIDReader;

	map<string, string> params;
	map<string, int> itemUsed;

	Parser* parser;		

	Counter itemsUsed;
	Counter itemsCrafted;
	Counter itemsAcquired;
	Counter itemsPurchased;
	Counter monstersKilled;
	Counter questsCompleted;	
	PvpKillsCounter<string> playersKilled;
	
	RuleStrings *rules;
	
	KnownPlayers knownPlayers;

	AssistDamage damageInflicted;

	KinahGainMeter kinahGained;
	
	int pvpDeaths;	
	
	Timer timer;

	queue<string> lines;

	Cheezeeee(): itemIDReader("file.txt"){
		parser = new MaxPeriodParser();		
		parser->setCriticalString("Critical Hit!");
		rules = new RuleStringsHardCodedNA();//RuleStringsFileReader("output.txt");

		reset();
	}
	void reset(){
		pvpDeaths = 0;
		timer.start();
	}


	void setParserEngine(Parser& parser){
		this->parser = &parser;
	}

	void setRuleStrings(RuleStrings& rules){
		this->rules = &rules;
	}

	bool setAionDirectory(string& directory){
		return logFile.setAionDirectory(directory);
	}

	void processLines(){
		logFile.readLines(lines);
		

		while(!lines.empty()){
			
			string line = lines.front();

			bool critical = parser->isCrit(line);

			if (parser->resembles(line, rules->getRule("STR_SKILL_SUCC_SkillATK_Instant_ME_TO_B"), params, critical)								
				|| parser->resembles(line, rules->getRule("STR_SKILL_SUCC_CarveSignet_ME_TO_B"), params, critical)
				|| parser->resembles(line, rules->getRule("STR_SKILL_SUCC_DispelBuffCounterATK_ME_TO_B"), params, critical)
				)
			{
				//AssistDamage damageInflicted = 
				//	AionGrindMeter::currentInstance().getEnemies().getTargetsDamagedByMe(); 
				damageInflicted.inflictDamage(params["[%SkillTarget]"], atoi(stripCommas(params["%num0"]).c_str()));
			}
			else if (parser->resembles(line, rules->getRule("STR_MSG_COMBAT_MY_CRITICAL"), params)
				|| parser->resembles(line, rules->getRule("STR_MSG_COMBAT_MY_ATTACK"), params)
				)
			{
				//AssistDamage damageInflicted = 
				//	AionGrindMeter::currentInstance().getEnemies().getTargetsDamagedByMe(); 
				damageInflicted.inflictDamage(params["%0"], atoi(stripCommas(params["%num1"]).c_str()));
			}
			else if (parser->resembles(line, rules->getRule("STR_USE_ITEM"), params)){
				//Counter<string> itemsUsed = AionGrindMeter::currentInstance().getItems().getItemsUsed();
				itemsUsed.add(params["%0"]);
				
			}
			else if (parser->resembles(line, rules->getRule("STR_GET_EXP_VITAL_BONUS"), params)
				|| parser->resembles(line, rules->getRule("STR_GET_EXP_MAKEUP_BONUS"), params)
				|| parser->resembles(line, rules->getRule("STR_GET_EXP_VITAL_MAKEUP_BONUS"), params)
				|| parser->resembles(line, rules->getRule("STR_GET_EXP"), params)
				)
			{
				//Counter<string> monstersKilled =
				//	AionGrindMeter::currentInstance().getEnemies().getMonstersKilled();
				monstersKilled.add(params["%0"]);
			}
			
			else if (parser->resembles(line, rules->getRule("STR_MSG_GET_ITEM_EXTRA_MULTI"), params)
				|| parser->resembles(line, rules->getRule("STR_MSG_GET_ITEM_MULTI"), params)
				|| parser->resembles(line, rules->getRule("STR_GET_ITEM"), params) 
				|| parser->resembles(line, rules->getRule("STR_MSG_GET_ITEM_EXTRA"), params)
				)
			{
				string itemName = itemIDReader.getItemName(params["%0"]);
				if (params.count("%num1"))						
					itemsAcquired.add(itemName, atoi(stripCommas(params["%num1"]).c_str()));
				else
					itemsAcquired.add(itemName);
			}
			else if (parser->resembles(line, rules->getRule("STR_MSG_COMBAT_HOSTILE_DEATH_TO_ME"), params)){
				knownPlayers.addPlayer(params["%0"]);				
				monstersKilled.erase(params["%0"]);
				//pvpKills ++;
				playersKilled.addKill(params["%0"]);
			}
			else if (parser->resembles(line, rules->getRule("STR_MSG_COMBAT_HOSTILE_DEATH_TO_B"), params)){
				knownPlayers.addPlayer(params["%0"]);
				knownPlayers.addPlayer(params["%1"]);				
				monstersKilled.erase(params["%1"]);
				if (damageInflicted.getInflictedDamage(params["%1"]) >= 0)
					//pvpAssists ++;
					playersKilled.addAssist(params["%1"]);
			}
			else if (parser->resembles(line, rules->getRule("STR_MSG_COMBAT_HOSTILE_DEATH"), params)){
				knownPlayers.addPlayer(params["%0"]);
				monstersKilled.erase(params["%0"]);
				if (damageInflicted.getInflictedDamage(params["%0"]) >= 0)
					//pvpAssists ++;
					playersKilled.addAssist(params["%0"]);
			}			
			else if (parser->resembles(line, rules->getRule("STR_MSG_COMBAT_MY_DEATH_TO_B"), params)){
				pvpDeaths ++;
			}
			else if (parser->resembles(line, rules->getRule("STR_MSG_BUY_ITEM_MULTI"), params)
				|| parser->resembles(line, rules->getRule("STR_MSG_BUY_ITEM"), params)
				){
				string itemName = itemIDReader.getItemName(params["%0"]);
				if (params.count("%1"))						
					itemsPurchased.add(itemName, atoi(stripCommas(params["%1"]).c_str()));
				else
					itemsPurchased.add(itemName);
			}
			else if (parser->resembles(line, rules->getRule("STR_MSG_COMBINE_ITEM_MULTI"), params)
				|| parser->resembles(line, rules->getRule("STR_MSG_COMBINE_ITEM"), params)
				){
				string itemName = itemIDReader.getItemName(params["%0"]);
				if (params.count("%1"))						
					itemsCrafted.add(itemName, atoi(stripCommas(params["%1"]).c_str()));
				else
					itemsCrafted.add(itemName);
			}			
			else if (parser->resembles(line, rules->getRule("STR_QUEST_SYSTEMMSG_COMPLETE"), params)){
				questsCompleted.add(params["%0"]);
			}
			else if (parser->resembles(line, rules->getRule("STR_MSG_GETMONEY"), params)
				|| parser->resembles(line, "STR_MSG_REFUND_MONEY_SYSTEM", params)					
				)
			{
				//kinahGained += atoi(stripCommas(params["%num0"]).c_str());
				kinahGained.gain(atoi(stripCommas(params["%num0"]).c_str()));
			}
			else if (parser->resembles(line, rules->getRule("STR_MSG_USEMONEY"), params)){
				kinahGained.spend(atoi(stripCommas(params["%num0"]).c_str()));
				//kinahGained -= atoi(stripCommas(params["%num0"]).c_str());
			}
			//You distributed %1 Kinah each to %0 members.
			
			

			lines.pop();
		}
		kinahGained.applyFromBuffer();
	}
};

int main(){
	Cheezeeee app;
	string directory = "G:/Aion/";
	bool status = app.setAionDirectory(directory);
	if (!status) cout << "UNABLE TO OPEN CHAT.LOG" << endl;
	
	while(true){
		app.processLines();

		system("cls");
		
		cout << formatElapsedTime(app.timer.getElapsedTime()); 
		cout << "\tKinah Gained: " << formatNumber(app.kinahGained.getNetGained()) << " (" << formatNumber(app.kinahGained.getLastChange()) << ")";
		if (app.kinahGained.getNumPacketsForLastChange() > 1) cout << " [" << app.kinahGained.getNumPacketsForLastChange() << "]";	
		cout << "\tPvP K/D/A: " << app.playersKilled.getTotalKills() << "/" << app.pvpDeaths << "/" << app.playersKilled.getTotalAssists() << endl;
		
		
		cout << endl;
		cout << "Item acquired" << endl;
		for (map<string, CounterEntry>::iterator iter = app.itemsAcquired.begin(); iter != app.itemsAcquired.end(); iter ++){
			cout << iter->first << " x" << iter->second.numGained;
				if (iter->second.numPackets >= 3) 
					cout <<"\t(" << formatKiloMega(app.timer.calculatePerHourRate(iter->second.numGained)) << " / h)";
			cout << endl;
		}
		
		cout << endl;
		cout << "Item purchased" << endl;
		for (map<string, CounterEntry>::iterator iter = app.itemsPurchased.begin(); iter != app.itemsPurchased.end(); iter ++){
			cout << iter->first << " x" << iter->second.numGained << "\n";
		}
		cout << endl;
		cout << "Item crafted" << endl;
		for (map<string, CounterEntry>::iterator iter = app.itemsCrafted.begin(); iter != app.itemsCrafted.end(); iter ++){
			cout << iter->first << " x" << iter->second.numGained << 
				" (" << formatKiloMega(app.timer.calculatePerHourRate(iter->second.numGained)) << " / h)\n";
		}
		cout << endl;
		
		cout << "Item consumed" << endl;
		for (map<string, CounterEntry>::iterator iter = app.itemsUsed.begin(); iter != app.itemsUsed.end(); iter ++){
			cout << iter->first << " x" << iter->second.numGained;
			if (iter->second.numPackets >= 3)
				cout << "\t(" << formatKiloMega(app.timer.calculatePerHourRate(iter->second.numGained)) << " / h)";			
			cout << endl;
		}
		cout << endl;
		
		cout << "Monsters defeated (" << app.monstersKilled.getTotalCount() << ")" 
			" (" << formatKiloMega(app.timer.calculatePerHourRate(app.monstersKilled.getTotalCount())) << " / h)" << endl;
		for (map<string, CounterEntry>::iterator iter = app.monstersKilled.begin(); iter != app.monstersKilled.end(); iter ++){
			cout << iter->first << " x" << iter->second.numGained;
			if (iter->second.numPackets >= 3)
				cout << "\t(" << formatKiloMega(app.timer.calculatePerHourRate(iter->second.numGained)) << " / h)";			
			cout << endl;
		}
		cout << endl;
		cout << "Players killed (assisted)" << endl;
		for (map<string, PlayerKill>::iterator iter = app.playersKilled.begin(); iter != app.playersKilled.end(); iter ++){
			cout << iter->first << " ";
			if (iter->second.kills > 0) cout << "x" << iter->second.kills << " ";
			if (iter->second.assists > 0) cout << "(x" << iter->second.assists << ")";
			cout << endl;
		}
		cout << endl;
		cout << "Quests completed (" << app.questsCompleted.getTotalCount() << ")" << endl;
		for (map<string, CounterEntry>::iterator iter = app.questsCompleted.begin(); iter != app.questsCompleted.end(); iter ++){
			cout << iter->first << " x" << iter->second.numGained;
			if (iter->second.numPackets >= 3)
				cout << "\t(" << formatKiloMega(app.timer.calculatePerHourRate(iter->second.numGained)) << " / h)";			
			cout << "\n";
		}
		
		Sleep(1000);
	}
}

/*
int main(){

	cout << "Opening chat log..." << endl;
	LogFileReader logFile("G:/Aion/Chat.log");
	if (!logFile.isOK()) cout << "UNABLE TO OPEN CHAT.LOG" << endl;

	cout << "Loading item names..." << endl;
	ItemIDReader itemIDReader("file.txt");

	map<string, string> params;
	map<string, int> itemUsed;

	Parser* parser = new MaxPeriodParser();
	parser->setCriticalString("Critical Hit!");
	
	Counter<string> itemsUsed;
	Counter<string> itemsCrafted;
	Counter<string> itemsAcquired;
	Counter<string> itemsPurchased;
	Counter<string> monstersKilled;
	Counter<string> questsCompleted;	
	PvpKillsCounter<string> playersKilled;
	
	RuleStrings<string> *rules = new RuleStringsFileReader("output.txt");
	
	KnownPlayers knownPlayers;

	AssistDamage damageInflicted;

	MeterValue kinahGained;
	//int kinahGained = 0;

	//int pvpKills = 0;
	int pvpDeaths = 0;
	//int pvpAssists = 0;
	
	Timer timer;
	timer.start();

	while(true){
		queue<string> lines = logFile.readLines();
		

		while(!lines.empty()){
			
			string line = lines.front();

			bool critical = parser->isCrit(line);

			if (parser->resembles(line, rules->getRule("STR_SKILL_SUCC_SkillATK_Instant_ME_TO_B"), params, critical)								
				|| parser->resembles(line, rules->getRule("STR_SKILL_SUCC_CarveSignet_ME_TO_B"), params, critical)
				|| parser->resembles(line, rules->getRule("STR_SKILL_SUCC_DispelBuffCounterATK_ME_TO_B"), params, critical)
				)
			{
				//AssistDamage damageInflicted = 
				//	AionGrindMeter::currentInstance().getEnemies().getTargetsDamagedByMe(); 
				damageInflicted.inflictDamage(params["[%SkillTarget]"], atoi(stripCommas(params["%num0"]).c_str()));
			}
			else if (parser->resembles(line, rules->getRule("STR_MSG_COMBAT_MY_CRITICAL"), params)
				|| parser->resembles(line, rules->getRule("STR_MSG_COMBAT_MY_ATTACK"), params)
				)
			{
				//AssistDamage damageInflicted = 
				//	AionGrindMeter::currentInstance().getEnemies().getTargetsDamagedByMe(); 
				damageInflicted.inflictDamage(params["%0"], atoi(stripCommas(params["%num1"]).c_str()));
			}
			else if (parser->resembles(line, rules->getRule("STR_USE_ITEM"), params)){
				//Counter<string> itemsUsed = AionGrindMeter::currentInstance().getItems().getItemsUsed();
				itemsUsed.add(params["%0"]);
				
			}
			else if (parser->resembles(line, rules->getRule("STR_GET_EXP_VITAL_BONUS"), params)
				|| parser->resembles(line, rules->getRule("STR_GET_EXP_MAKEUP_BONUS"), params)
				|| parser->resembles(line, rules->getRule("STR_GET_EXP_VITAL_MAKEUP_BONUS"), params)
				|| parser->resembles(line, rules->getRule("STR_GET_EXP"), params)
				)
			{
				//Counter<string> monstersKilled =
				//	AionGrindMeter::currentInstance().getEnemies().getMonstersKilled();
				monstersKilled.add(params["%0"]);
			}
			
			else if (parser->resembles(line, rules->getRule("STR_MSG_GET_ITEM_EXTRA_MULTI"), params)
				|| parser->resembles(line, rules->getRule("STR_MSG_GET_ITEM_MULTI"), params)
				|| parser->resembles(line, rules->getRule("STR_GET_ITEM"), params) 
				|| parser->resembles(line, rules->getRule("STR_MSG_GET_ITEM_EXTRA"), params)
				)
			{
				cout << "Retrieving item name" << endl;
				string itemName = itemIDReader.getItemName(params["%0"]);
				if (params.count("%num1"))						
					itemsAcquired.add(itemName, atoi(stripCommas(params["%num1"]).c_str()));
				else
					itemsAcquired.add(itemName);
			}
			else if (parser->resembles(line, rules->getRule("STR_MSG_COMBAT_HOSTILE_DEATH_TO_ME"), params)){
				knownPlayers.addPlayer(params["%0"]);				
				monstersKilled.erase(params["%0"]);
				//pvpKills ++;
				playersKilled.addKill(params["%0"]);
			}
			else if (parser->resembles(line, rules->getRule("STR_MSG_COMBAT_HOSTILE_DEATH_TO_B"), params)){
				knownPlayers.addPlayer(params["%0"]);
				knownPlayers.addPlayer(params["%1"]);				
				monstersKilled.erase(params["%1"]);
				if (damageInflicted.getInflictedDamage(params["%1"]) >= 0)
					//pvpAssists ++;
					playersKilled.addAssist(params["%1"]);
			}
			else if (parser->resembles(line, rules->getRule("STR_MSG_COMBAT_HOSTILE_DEATH"), params)){
				knownPlayers.addPlayer(params["%0"]);
				monstersKilled.erase(params["%0"]);
				if (damageInflicted.getInflictedDamage(params["%0"]) >= 0)
					//pvpAssists ++;
					playersKilled.addAssist(params["%0"]);
			}			
			else if (parser->resembles(line, rules->getRule("STR_MSG_COMBAT_MY_DEATH_TO_B"), params)){
				pvpDeaths ++;
			}
			else if (parser->resembles(line, rules->getRule("STR_MSG_BUY_ITEM_MULTI"), params)
				|| parser->resembles(line, rules->getRule("STR_MSG_BUY_ITEM"), params)
				){
				cout << "Retrieving item name" << endl;
				string itemName = itemIDReader.getItemName(params["%0"]);
				if (params.count("%1"))						
					itemsPurchased.add(itemName, atoi(stripCommas(params["%1"]).c_str()));
				else
					itemsPurchased.add(itemName);
			}
			else if (parser->resembles(line, rules->getRule("STR_MSG_COMBINE_ITEM_MULTI"), params)
				|| parser->resembles(line, rules->getRule("STR_MSG_COMBINE_ITEM"), params)
				){
				cout << "Retrieving item name" << endl;
				string itemName = itemIDReader.getItemName(params["%0"]);
				if (params.count("%1"))						
					itemsCrafted.add(itemName, atoi(stripCommas(params["%1"]).c_str()));
				else
					itemsCrafted.add(itemName);
			}			
			else if (parser->resembles(line, rules->getRule("STR_QUEST_SYSTEMMSG_COMPLETE"), params)){
				questsCompleted.add(params["%0"]);
			}
			else if (parser->resembles(line, rules->getRule("STR_MSG_GETMONEY"), params)
				|| parser->resembles(line, "STR_MSG_REFUND_MONEY_SYSTEM", params)					
				)
			{
				//kinahGained += atoi(stripCommas(params["%num0"]).c_str());
				kinahGained.gain(atoi(stripCommas(params["%num0"]).c_str()));
			}
			else if (parser->resembles(line, rules->getRule("STR_MSG_USEMONEY"), params)){
				kinahGained.spend(atoi(stripCommas(params["%num0"]).c_str()));
				//kinahGained -= atoi(stripCommas(params["%num0"]).c_str());
			}
			//You distributed %1 Kinah each to %0 members.
			
			

			lines.pop();
		}
		kinahGained.applyFromBuffer();
	
		system("cls");
		
		cout << formatElapsedTime(timer.getElapsedTime()); 
		cout << "\tKinah Gained: " << formatNumber(kinahGained.getNetGained()) << " (" << formatNumber(kinahGained.getLastChange()) << ")";
		if (kinahGained.getNumPacketsForLastChange() > 1) cout << " [" << kinahGained.getNumPacketsForLastChange() << "]";	
		cout << "\tPvP K/D/A: " << playersKilled.getTotalKills() << "/" << pvpDeaths << "/" << playersKilled.getTotalAssists() << endl;
		
		
		cout << endl;
		cout << "Item acquired" << endl;
		for (map<string, int>::iterator iter = itemsAcquired.begin(); iter != itemsAcquired.end(); iter ++){
			cout << iter->first << " x" << iter->second << "\n";
		}
		cout << endl;
		cout << "Item purchased" << endl;
		for (map<string, int>::iterator iter = itemsPurchased.begin(); iter != itemsPurchased.end(); iter ++){
			cout << iter->first << " x" << iter->second << "\n";
		}
		cout << endl;
		cout << "Item crafted" << endl;
		for (map<string, int>::iterator iter = itemsCrafted.begin(); iter != itemsCrafted.end(); iter ++){
			cout << iter->first << " x" << iter->second << "\n";
		}
		cout << endl;
		
		cout << "Item consumed" << endl;
		for (map<string, int>::iterator iter = itemsUsed.begin(); iter != itemsUsed.end(); iter ++){
			cout << iter->first << " x" << iter->second << "\n";
		}
		cout << endl;
		
		cout << "Monsters defeated (" << monstersKilled.getTotalCount() << ")" << endl;
		for (map<string, int>::iterator iter = monstersKilled.begin(); iter != monstersKilled.end(); iter ++){
			cout << iter->first << " x" << iter->second << "\n";
		}
		cout << endl;
		cout << "Players killed (assisted)" << endl;
		for (map<string, PlayerKill>::iterator iter = playersKilled.begin(); iter != playersKilled.end(); iter ++){
			cout << iter->first << " ";
			if (iter->second.kills > 0) cout << "x" << iter->second.kills << " ";
			if (iter->second.assists > 0) cout << "(x" << iter->second.assists << ")";
			cout << endl;
		}
		cout << endl;
		cout << "Quests completed (" << questsCompleted.getTotalCount() << ")" << endl;
		for (map<string, int>::iterator iter = questsCompleted.begin(); iter != questsCompleted.end(); iter ++){
			cout << iter->first << " x" << iter->second << "\n";
		}
		
		Sleep(1000);
	}

	return 0;
}
*/