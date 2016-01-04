
#include <Windows.h>

#include "../modules/HuntingModule.h"
#include "../modules/ItemAcquisitionModule.h"

#include "../parser/ItemIDFileReader.h"

#include "../parser/LogFileUtility.h"

//#include "lookups/RuleStringsHardCodedNA.h"
//#include "parser/MaxPeriodParser.h"
//#include "lookups/SkillToClassHardCodedNA.h"

#include "../stringFunctions.h"

int main(){

	HuntingModule huntingModule;
	ItemAcquisitionModule itemAcquisitionModule;

	LogFileUtility logFileUtility;

	ItemIDFileReader itemIDReader("file.txt");

	string aionDirectory = "D:/Aion/";
	bool status = logFileUtility.setAionDirectory(aionDirectory);
	
	if (!status) cout << "UNABLE TO OPEN CHAT.LOG" << endl;
	
	logFileUtility.registerModule(huntingModule);
	logFileUtility.registerModule(itemAcquisitionModule);

	while(true){
		
		logFileUtility.parseLogFile();

		system("cls");	
				
		cout << formatElapsedTime(huntingModule.timer.getElapsedTime()); 
		cout << '\t';
		cout << formatElapsedTime(itemAcquisitionModule.timer.getElapsedTime()); 
		
		cout << endl << endl;
		cout << "Items acquired" << endl;
		for (map<int, CounterEntry>::iterator iter = itemAcquisitionModule.itemsAcquired.begin(); 
			iter != itemAcquisitionModule.itemsAcquired.end(); iter ++)
		{
			cout << iter->first << " " << itemIDReader.getItemName(iter->first) << " x" << iter->second.numGained;
				if (iter->second.numPackets >= 3) 
					cout <<"\t(" << formatKiloMega(itemAcquisitionModule.timer.calculatePerHourRate(iter->second.numGained)) << " / h)";
			cout << endl;
		}
		cout << endl;
		cout << "Items rolled for [" 
			<< itemAcquisitionModule.itemRolls.getNumItemsRolled() << " rolls / "
			<< itemAcquisitionModule.itemRolls.getNumItemsWon() << " wins / "
			<< itemAcquisitionModule.itemRolls.getNumItemsPassed() << " passes / "			
			<< itemAcquisitionModule.itemRolls.getAverageOfMyRolls() << " Avg Roll]"
			<< endl;		
		for (int i = 0; i < itemAcquisitionModule.itemRolls.getItemRolls().size(); i ++){			
			ItemDiceRoll entry = itemAcquisitionModule.itemRolls.getItemRolls()[i];
			cout << entry.yourRoll << '/';
			cout << entry.winningRoll << " - ";
			cout << entry.item << ' ';
			cout << itemIDReader.getItemName(entry.item) << " <";
			cout << entry.winner << ">";
			cout << endl;
		}

		cout << endl;
		cout << "Containers Opened" << endl;
		for (map<string, CounterEntry>::iterator iter = itemAcquisitionModule.containersOpened.begin();
				iter != itemAcquisitionModule.containersOpened.end(); iter ++)
		{
			cout << iter->first << " x" << iter->second.numGained;
				if (iter->second.numPackets >= 3) 
					cout <<"\t(" << formatKiloMega(huntingModule.timer.calculatePerHourRate(iter->second.numGained)) << " / h)";
			cout << endl;

			Counter<int>& contentsMap = itemAcquisitionModule.itemsFromContainers[iter->first];
			for (map<int, CounterEntry>::iterator iter2 = contentsMap.begin(); 
					iter2 != contentsMap.end(); iter2 ++) {
				cout << "\t" << iter2->first << " " << itemIDReader.getItemName(iter2->first) << " x" << iter2->second.numGained;
				/*if (iter->second.numPackets >= 3) 
					cout <<"\t(" << formatKiloMega(itemAcquisitionModule.timer.calculatePerHourRate(iter->second.numGained)) << " / h)";*/
				cout << endl;
			}
		}

		cout << endl;
		cout << "Items used" << endl;
		for (map<string, CounterEntry>::iterator iter = itemAcquisitionModule.itemsConsumed.begin(); 
				iter != itemAcquisitionModule.itemsConsumed.end(); iter ++)
		{
			cout << iter->first << " x" << iter->second.numGained;
				if (iter->second.numPackets >= 3) 
					cout <<"\t(" << formatKiloMega(huntingModule.timer.calculatePerHourRate(iter->second.numGained)) << " / h)";
			cout << endl;
		}
		cout << endl;
		
		int totalMobsKilled = huntingModule.monstersKilled.getTotalCount();
		cout << "Monsters killed (" << totalMobsKilled << ")";
		if (totalMobsKilled >= 3)
			cout << " (" << formatKiloMega(huntingModule.timer.calculatePerHourRate(totalMobsKilled)) << " / h)";
		cout << endl;
		for (map<string, CounterEntry>::iterator iter = huntingModule.monstersKilled.begin(); 
			iter != huntingModule.monstersKilled.end(); iter ++)
		{
			cout << iter->first << " x" << iter->second.numGained;
				if (iter->second.numPackets >= 3) 
					cout <<"\t(" << formatKiloMega(huntingModule.timer.calculatePerHourRate(iter->second.numGained)) << " / h)";
			cout << endl;
		}


		Sleep(500);
		logFileUtility.parseLogFile();
		Sleep(500);
	}
}