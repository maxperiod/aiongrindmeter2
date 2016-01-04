#include <Windows.h>
#include "../modules/ProfessionModule.h"
#include "../parser/LogFileUtility.h"

void printExpBar(float percent){
	cout << '[';
	for (int i = 0; i < 20; i ++){
		if (percent - i * 5 >= 5) cout << '=';
		else cout << ' ';
	}
	cout << ']';
	cout << endl;
}

int main(){
	string aionDirectory = "D:/Aion/";
	ProfessionModule app;		
	
	LogFileUtility logFileUtility;
	bool status = logFileUtility.setAionDirectory(aionDirectory);

	if (!status) cout << "UNABLE TO OPEN CHAT.LOG" << endl;

	logFileUtility.registerModule(app);

	while(true){
		
		logFileUtility.parseLogFile();

		system("cls");
				
		cout << formatElapsedTime(app.timer.getElapsedTime()) << endl; 

		GatherCraftRecord& gathers = app.gathers.getResult();
		cout << "Gathering: pass / fail / cancel: "
			<< gathers.getNumSuccess() << " / "
			<< gathers.getNumFailure() << " / "
			<< gathers.getNumCancel() << "\t("
			<< formatKiloMega(app.timer.calculatePerHourRate(gathers.getNumSuccess())) 
			<< " / h)" << endl;
		cout << endl;

		GatherCraftRecord& crafts = app.crafts.getResult();
		cout << "Crafting: pass / fail / cancel [procs]: "
			<< crafts.getNumSuccess() << " / "
			<< crafts.getNumFailure() << " / "
			<< crafts.getNumCancel() << " ["
			<< crafts.getNumProcs() << "]\t("
			<< formatKiloMega(app.timer.calculatePerHourRate(crafts.getNumSuccess())) 
			<< " / h)" << endl;
		cout << endl;		

		IndividualItemGatherCrafts& gathersByItem = app.gathers.getIndividualItemGatherCrafts();

		for (map<string, GatherCraftRecord>::iterator iter = gathersByItem.begin(); iter != gathersByItem.end(); iter ++){
			cout << iter->first << ": "
			<< iter->second.getNumSuccess() << " / "
			<< iter->second.getNumFailure() << " / "
			<< iter->second.getNumCancel() << "\t("
			<< formatKiloMega(app.timer.calculatePerHourRate(iter->second.getNumSuccess())) 
			<< " / h)" << endl;
		}

		IndividualItemGatherCrafts& craftsByItem = app.crafts.getIndividualItemGatherCrafts();

		cout << endl;

		for (map<string, GatherCraftRecord>::iterator iter = craftsByItem.begin(); iter != craftsByItem.end(); iter ++){
			cout << iter->first << ": "
			<< iter->second.getNumSuccess() << " / "
			<< iter->second.getNumFailure() << " / "
			<< iter->second.getNumCancel() << " ["
			<< iter->second.getNumProcs() << "]\t("
			<< formatKiloMega(app.timer.calculatePerHourRate(iter->second.getNumSuccess())) 
			<< " / h)" << endl;
		}

		cout << endl;

		for (int i = 0; i < 2; i ++){
			ProfessionLeveling* professionLeveling;
			ProfessionLevelingHistory* professionLevelingHistory;
			
			if (i == 0){
				professionLeveling = &app.gatherLeveling;
				professionLevelingHistory = &app.gatherLeveling.getProfessionLevelingHistory();
			}
			else if (i == 1){
				professionLeveling = &app.craftLeveling;
				professionLevelingHistory = &app.craftLeveling.getProfessionLevelingHistory();
			}

			cout << "Current Profession: " << professionLeveling->getCurrentProfession() 
				<< " (" << professionLeveling->getCurrentLevel() << "p)" << endl;
		
			cout << "Gathering level ups: " << professionLeveling->getNumLevelUps() 
				<< "\t("<< formatKiloMega(app.timer.calculatePerHourRate(
				professionLeveling->getNumLevelUps() + professionLeveling->getProgressBarValue() / 100)) << " / h)" << endl;	

			cout << "Current / last level: " << professionLeveling->getNumGatheredOrCraftedSinceLevelUp() << " / "
				<< professionLeveling->getNumGatheredOrCraftedForLastLevelUp() << endl;

			cout << "Est. Next Level: " << formatPercent(professionLeveling->getProgressBarValue()) << endl;
			printExpBar(professionLeveling->getProgressBarValue());
			cout << endl;
		
			for (map<int, int>::iterator levelUps = professionLevelingHistory->begin();
				levelUps != professionLevelingHistory->end(); levelUps ++){
				cout << "To " << levelUps->first << ": " << levelUps->second << endl;
			}
			cout << endl;
		}

		Sleep(1000);
	}
}