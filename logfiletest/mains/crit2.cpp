#include "../experimental/CombatModule.h"
#include "../parser/LogFileUtility.h"
//#include "lookups/RuleStringsHardCodedNA.h"
//#include "parser/MaxPeriodParser.h"
//#include "lookups/SkillToClassHardCodedNA.h"

#include <cstdio>
#include <Windows.h>


int main(){

	CombatModule combatModule;
	string aionDirectory = "D:/Aion/";
	
	LogFileUtility logFileUtility;
	bool status = logFileUtility.setAionDirectory(aionDirectory);

	if (!status) cout << "UNABLE TO OPEN CHAT.LOG" << endl;

	logFileUtility.registerModule(combatModule);
	
	int refreshCounter = 0;
	while(true){
		logFileUtility.parseLogFile();
	
		refreshCounter ++;
		if (refreshCounter >= 10){
			refreshCounter = 0;
			system("cls");	
	
			CombatStatsPair combatStatsPair = combatModule.combatStatsManager.getAllTargetsCombatStats();			
			CombatStatsPair individualTargetCombatStatsPair = combatModule.combatStatsManager.getLastTargetCombatStats();			

			
			for (int i = 0; i < 4; i ++){				
				CombatStats* combatStats = (i % 2 == 0) ? &combatStatsPair.first : &combatStatsPair.second;
				if (i >= 2) combatStats = (i % 2 == 0) ? &individualTargetCombatStatsPair.first : &individualTargetCombatStatsPair.second;
				
				if (i == 0) printf("ALL TARGETS\n");
				else if (i == 2) printf("Target: %s\n", combatModule.combatStatsManager.getLastTarget().c_str());

				printf("Set %d:\n\n", i % 2 + 1);

				printf("Hits : %4d\n", combatStats->numHits);
				printf("Crits: %4d (%.2f%%)\n\n", 
					combatStats->numCrits, 
					(float)combatStats->numCrits / combatStats->numHits * 100
				);
				
				printf("Blocked Parried Evaded Shielded Reflected Resisted\n");
				printf("%7d %7d %6d %8d %9d %8d\n", 
					combatStats->enemyBlock,
					combatStats->enemyParry,
					combatStats->enemyEvade,
					combatStats->enemyShield,
					combatStats->enemyReflect,
					combatStats->enemyResist
				);

				
					
				SkillDamageStats* autoAttack[2];					

				autoAttack[0] = &combatStats->autoDamageStats1;
				autoAttack[1] = &combatStats->autoDamageStats2;
				
				printf("Auto Attacks: %dx (%dC)", 
					autoAttack[0]->numUses, 
					autoAttack[0]->crits.numHits + autoAttack[0]->critBlocks.numHits + autoAttack[0]->critParrys.numHits
				);
				if (i >= 2){
					printf(" (normal / crits)\n");

					for (int i = 0; i < 2; i ++){
						printf("%5d-%5d (%7.2f) %5d-%5d (%7.2f)\n", 					
							autoAttack[i]->normals.minDamage,
							autoAttack[i]->normals.maxDamage,
							(float)autoAttack[i]->normals.totalDamage / autoAttack[i]->normals.numHits,
							autoAttack[i]->crits.minDamage,
							autoAttack[i]->crits.maxDamage,
							(float)autoAttack[i]->crits.totalDamage / autoAttack[i]->crits.numHits
						);
					}
				}
				printf("\n1x/2x/3x/4x-hit: %3d/%3d/%3d/%3d\n",	
					combatStats->multiStrikes[0],
					combatStats->multiStrikes[1],
					combatStats->multiStrikes[2],
					combatStats->multiStrikes[3]
				);
				printf("                 %3d/%3d/%3d/%3d\n",	
					combatStats->multiStrikes2[0],
					combatStats->multiStrikes2[1],
					combatStats->multiStrikes2[2],
					combatStats->multiStrikes2[3]
				);
				
				printf("Skills: %dx", combatStats->skillAttacks);
				if (i >= 2){
					printf(" (normal / crits)\n");
					unordered_map<string, SkillDamageStats>& skillDamageStats = combatStats->skillDamageStats;
					for (unordered_map<string, SkillDamageStats>::iterator iter = skillDamageStats.begin(); iter != skillDamageStats.end(); iter ++){
						printf("%25s%3dx(%3dC%3dF)%5d-%5d(%7.2f)%5d-%5d(%7.2f)\n", 
							iter->first.c_str(),							
							iter->second.numUses,							
							iter->second.crits.numHits + iter->second.critBlocks.numHits + iter->second.critParrys.numHits,
							iter->second.numResists,
							iter->second.normals.minDamage,
							iter->second.normals.maxDamage,
							(float)iter->second.normals.totalDamage / iter->second.normals.numHits,
							iter->second.crits.minDamage,
							iter->second.crits.maxDamage,
							(float)iter->second.crits.totalDamage / iter->second.crits.numHits
						);
					}
				}
				printf("\n================================\n");
				
			}
		}
		Sleep(100);
	}		
}