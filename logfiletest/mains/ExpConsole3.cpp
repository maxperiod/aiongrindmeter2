#include <Windows.h>
#include "../modules/ExpModule.h"
#include "../modules/ApModule.h"
#include "../modules/KinahModule.h"
#include "../modules/SoulHealerModule.h"
#include "../modules/GpModule.h"

#include "../parser/LogFileUtility.h"
#include "../stringFunctions.h"

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
	

	
	ExpModule expApp;
	ApModule apApp;
	KinahModule kinahApp;
	SoulHealerModule soulHealerApp(expApp, apApp, kinahApp);	
	GpModule gpApp;

	LogFileUtility logFileUtility;
	bool status = logFileUtility.setAionDirectory(aionDirectory);
	if (!status) cout << "UNABLE TO OPEN CHAT.LOG" << endl;
	
	logFileUtility.registerModule(expApp);
	logFileUtility.registerModule(apApp);
	logFileUtility.registerModule(kinahApp);
	logFileUtility.registerModule(soulHealerApp);
	logFileUtility.registerModule(gpApp);

	string levelInput;
	string expInput;
	string apInput;

	cout << "Enter your level" << endl;
	cin >> levelInput;
	cout << "Enter your exp" << endl;
	cin >> expInput;
	expApp.levelUpChecker.initialize(verifyNumericInput(levelInput), verifyNumericInput(expInput));
	cout << "Enter your ap" << endl;
	cin >> apInput;	
	apApp.abyssRankChecker.initialize(verifyNumericInput(apInput));

	while(true){
		logFileUtility.parseLogFile();
	
		system("cls");
		cout << formatElapsedTime(expApp.timer.getElapsedTime()); 
		cout << endl << endl;
		//if (true){/*
		if (expApp.levelUpChecker.isInitialized() && soulHealerApp.soulHealer.isExpUpdateNeeded()){
			
			string expInput;
			cout << "Enter your exp (" << expApp.levelUpChecker.getCurrentValue() << "before death )" << endl;
			cin >> expInput;
			int newExp = verifyNumericInput(expInput);
			soulHealerApp.soulHealer.manualExpUpdate(newExp);
			
		}
		else if (apApp.abyssRankChecker.isInitialized() && soulHealerApp.soulHealer.isApUpdateNeeded()){
			string apInput;
			cout << "Enter your ap (" << apApp.abyssRankChecker.getCurrentValue() << "before death )" << endl;
			cin >> apInput;
			int newAp = verifyNumericInput(apInput);
			soulHealerApp.soulHealer.manualApUpdate(newAp);
		}
		else{
		
			int level = expApp.levelUpChecker.getCurrentLevel();
			long long exp = expApp.levelUpChecker.getCurrentValue();
			long long nextLevel = expApp.levelUpChecker.getCurrentLevelMaxValue();
			float percent = expApp.levelUpChecker.getPercent();
			long long cumulativeExp = expApp.levelUpChecker.getCumulativeCurrentValue();
			long long levelCapExp = expApp.expChart.getLevelCapValue();
			float cumulativePercent = expApp.levelUpChecker.getCumulativePercent();

			bool expIsInitialized = expApp.levelUpChecker.isInitialized();
			if (expIsInitialized){
				cout << "Level: " << level << endl;		
				cout << "Exp: " << exp << " / " << nextLevel << 
					" (" << formatPercent(percent) << ")" << endl;
				cout << endl;
				printExpBar(percent);
			}
			long long expGained = expApp.expGainMeter.getNetGained();
			float expPerHour = expApp.timer.calculatePerHourRate(expGained);

			cout << "Exp Gained: " << expGained << " (" << formatKiloMega(expPerHour) << " / h)" << endl;
			if (expIsInitialized){
				float levelsGained = expApp.levelUpChecker.getNumLevelsGained();
				if (levelsGained < 1) cout << "% gained: " << formatPercent(levelsGained * 100);
				else cout << "Levels gained: " << formatDecimal(levelsGained);

				float levelsPerHour = expApp.getWeightedLevelUpsPerHour();
				if (levelsPerHour < 1) cout << " (" << formatPercent(levelsPerHour * 100) << " / h)";
				else cout << " (" << formatDecimal(levelsPerHour) << " Lv / h)";
				cout << endl;
			}
			cout << endl;
		
			int lastChange = expApp.expGainMeter.getLastChange();
		
			cout << "Last: " << lastChange;
			if (expApp.levelUpChecker.isInitialized()) {
				cout << " (" << formatPercentChange(expApp.levelUpChecker.getLastChangePercent()) << ")" << endl;
				cout << endl;
		
				cout << "Cumulative: " << cumulativeExp << " / " << levelCapExp <<
					" (" << formatPercent(cumulativePercent) << ")";  
				cout << endl;
				printExpBar(cumulativePercent);
			}
			cout << endl;

			cout << "Repose: " << expApp.expGainMeter.getReposeUsed() << endl;
			cout << "Salvation: " << expApp.expGainMeter.getSalvationUsed() << endl;
			cout << endl;
			
			long long ap = apApp.abyssRankChecker.getCurrentValue();
			int abyssRank = apApp.abyssRankChecker.getCurrentLevel();
			long long apLastChange = apApp.apGainMeter.getLastChange();

			if (apApp.abyssRankChecker.isInitialized()){
				cout << "Abyss Points: " << ap;			
				if (abyssRank < 9){
					long long nextRank = apApp.abyssRankChecker.getCurrentLevelMaxValue();
					float percent = apApp.abyssRankChecker.getPercent();
					cout << " / " << nextRank;
					cout << " (" << formatPercent(percent) << ")" << endl;
					cout << "Abyss Rank: " << 10 - abyssRank;
					cout << endl;
					printExpBar(percent);
				}
				else {
					cout << endl;
					cout << "AP available to spend without dropping rank: " << ap - apApp.apChart.getLevelCapValue();
					cout << endl;
				}						
				cout << endl;
			}
			
			long long apGained = apApp.apGainMeter.getTotalGained();
			long long apSpent = apApp.apGainMeter.getTotalSpent();
			long long apLost = apApp.apGainMeter.getTotalLost();
			long long apNetIncome = apApp.apGainMeter.getNetGained();
			
			long long pvpAp = apApp.apGainMeter.getPvpAp();
			long long relicAp = apApp.apGainMeter.getRelicAp();

			float apPerHour = apApp.timer.calculatePerHourRate(apNetIncome);
			float relicApPerHour = apApp.timer.calculatePerHourRate(relicAp);
			
			cout << "AP Revenue: " << apGained << endl;
			cout << "AP Spent: " << apSpent << endl;
			cout << "AP Lost: " << apLost << endl;
			cout << "AP Net Income: " << apNetIncome 
				<< " (" << formatKiloMega(apPerHour) << " / h)"
				<< " +" << apLastChange;
			if (apApp.abyssRankChecker.isInitialized() && abyssRank < 9){
				cout << " (" << formatPercentChange(apApp.abyssRankChecker.getLastChangePercent()) << ")";
			}

			cout << endl << endl;
			cout << "Relic AP: " << relicAp 
				<< " (" << formatKiloMega(relicApPerHour) << " / h)";

			cout << endl << endl;
			cout << "PvP AP: " << pvpAp;

			cout << endl << endl;

			long long kinahGained = kinahApp.kinahGainMeter.getTotalGained();
			long long kinahSpent = kinahApp.kinahGainMeter.getTotalSpent();			
			long long kinahNetIncome = kinahApp.kinahGainMeter.getNetGained();

			long long kinahNpcSales = kinahApp.kinahGainMeter.getNpcSales();

			cout << "Kinah Revenue: " << kinahGained << endl;
			cout << "Kinah Spent: " << kinahSpent << endl;			
			cout << "Kinah Net Income: " << kinahNetIncome << endl;
			cout << endl;
			cout << "NPC Sales: " << kinahNpcSales << endl;
			cout << endl;

			long long gpGained = gpApp.gpGainMeter.getTotalGained();
			long long gpLost = gpApp.gpGainMeter.getTotalLost();
			long long gpNetIncome = gpApp.gpGainMeter.getNetGained();
			long long gpLastChange = gpApp.gpGainMeter.getLastChange();

			float gpPerHour = apApp.timer.calculatePerHourRate(gpNetIncome);

			cout << "GP Revenue: " << gpGained << endl;
			cout << "GP Deducted: " << gpLost << endl;			
			cout << "GP Net Income: " << gpNetIncome
				<< " (" << formatKiloMega(gpPerHour) << " / h)"
				<< " +" << gpLastChange;
			cout << endl;
			
		}
		Sleep(1000);
	}
}