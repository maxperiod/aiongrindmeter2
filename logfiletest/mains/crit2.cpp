#include "../experimental/CombatModule.h"
#include "../parser/LogFileUtility.h"
//#include "lookups/RuleStringsHardCodedNA.h"
//#include "parser/MaxPeriodParser.h"
//#include "lookups/SkillToClassHardCodedNA.h"

#include <cstdio>
#include <sstream>
#include <fstream>

#include <Windows.h>

class SoulHealToSaveToFile: public Module{
private:
	CombatModule& combatModule;

public:
	
	SoulHealToSaveToFile(CombatModule& combatModule): combatModule(combatModule){
		DECLARE_MESSAGE_RULE(STR_SUCCESS_RECOVER_EXPERIENCE);
		DECLARE_MESSAGE_RULE(STR_DONOT_HAVE_RECOVER_EXPERIENCE);
	}


	virtual void endOfTickAction(){
	}
	
	string formatText(bool currentSetOnly = false){
		stringstream output;
		for (int i = 0; i < 4; i ++){	
			if (!currentSetOnly || i % 2 == combatModule.weaponSwitch.getCurrentSet()){
				

				CombatStatsPair combatStatsPair = combatModule.combatStatsManager.getAllTargetsCombatStats();			
				CombatStatsPair individualTargetCombatStatsPair = combatModule.combatStatsManager.getLastTargetCombatStats();			

				CombatStats* combatStats = (i % 2 == 0) ? &combatStatsPair.first : &combatStatsPair.second;
				if (i >= 2) combatStats = (i % 2 == 0) ? &individualTargetCombatStatsPair.first : &individualTargetCombatStatsPair.second;
				
				if (i == 0) output << ("ALL TARGETS\n");
				else if (i == 2) output << "Target: " << combatModule.combatStatsManager.getLastTarget() << endl;

				output << "Set " << i % 2 + 1 << endl << endl;

				output << "Crits / Hits : " << combatStats->numCrits << " / " << combatStats->numHits 
					<< " (" << (float)combatStats->numCrits / combatStats->numHits * 100 << "%)\n";						
				
				//printf("Blocked Parried Evaded Shielded Reflected Resisted\n");
				//printf("%7d %7d %6d %8d %9d %8d\n", 
				if (combatStats->enemyBlock > 0) output << "Blocked: " << combatStats->enemyBlock << endl;
				if (combatStats->enemyParry > 0) output << "Parried: " << combatStats->enemyParry << endl;
				if (combatStats->enemyEvade > 0) output << "Evaded: " << combatStats->enemyEvade << endl;
				if (combatStats->enemyShield > 0) output << "Shielded: " << combatStats->enemyShield << endl;
				if (combatStats->enemyReflect > 0) output << "Reflected: " << combatStats->enemyReflect << endl;
				if (combatStats->enemyResist > 0) output << "Resisted: " << combatStats->enemyResist << endl;
				//);

				
					
				SkillDamageStats* autoAttack[2];					

				autoAttack[0] = &combatStats->autoDamageStats1;
				autoAttack[1] = &combatStats->autoDamageStats2;
				
				int totalCrits = autoAttack[0]->crits.numHits + autoAttack[0]->critBlocks.numHits + autoAttack[0]->critParrys.numHits;
				output << "Auto Attacks: " << autoAttack[0]->numUses
					<< " hits / " << totalCrits << " crits (" << (float)totalCrits / autoAttack[0]->numUses * 100 << "% / "
					<< autoAttack[0]->numResists << " misses (" << (float) autoAttack[0]->numResists / (autoAttack[0]->numResists + autoAttack[0]->numUses) * 100 << "%)" << endl;
			
	

				if (i >= 2){
					//output << " (normal / crits)\n";

					

					for (int i = 0; i < 2; i ++){	

						if (i == 0) output << "mainhand: ";
						if (i == 1) output << "off hand: ";

						output << autoAttack[i]->normals.minDamage << '-' << autoAttack[i]->normals.maxDamage
							<< " (" << (float)autoAttack[i]->normals.totalDamage / autoAttack[i]->normals.numHits << " avg)";

						if (autoAttack[i]->crits.numHits > 0){
							output << " / Crits: " << autoAttack[i]->crits.minDamage << '-' << autoAttack[i]->crits.maxDamage
							<< " (" << (float)autoAttack[i]->crits.totalDamage / autoAttack[i]->crits.numHits << " avg)";
						}
						output << endl;

						if (autoAttack[i]->blocks.numHits > 0){
							output << "\tBlocked (" << autoAttack[i]->blocks.numHits << "x): " << autoAttack[i]->blocks.minDamage << '-' << autoAttack[i]->blocks.maxDamage
							<< " (" << (float)autoAttack[i]->blocks.totalDamage / autoAttack[i]->blocks.numHits << " avg)";

							if (autoAttack[i]->critBlocks.numHits > 0){
								output << " / Crits: " << autoAttack[i]->critBlocks.minDamage << '-' << autoAttack[i]->critBlocks.maxDamage
								<< " (" << (float)autoAttack[i]->critBlocks.totalDamage / autoAttack[i]->critBlocks.numHits << " avg)";
							}
							output << endl;
						}

						if (autoAttack[i]->parrys.numHits > 0){
							output << "\tParried (" << autoAttack[i]->parrys.numHits << "x): " << autoAttack[i]->parrys.minDamage << '-' << autoAttack[i]->parrys.maxDamage
							<< " (" << (float)autoAttack[i]->parrys.totalDamage / autoAttack[i]->parrys.numHits << " avg)";

							if (autoAttack[i]->critParrys.numHits > 0){
								output << " / Crits: " << autoAttack[i]->critParrys.minDamage << '-' << autoAttack[i]->critParrys.maxDamage
								<< " (" << (float)autoAttack[i]->critParrys.totalDamage / autoAttack[i]->critParrys.numHits << " avg)";
							}
							output << endl;
						}
					}
				}
				output << "\n1x/2x/3x/4x-hit: "
					<< combatStats->multiStrikes[0] << '/'
					<< combatStats->multiStrikes[1] << '/'
					<< combatStats->multiStrikes[2] << '/'
					<< combatStats->multiStrikes[3];
				
				output << "\n1x/2x/3x/4x-hit: "
					<< combatStats->multiStrikes2[0] << '/'
					<< combatStats->multiStrikes2[1] << '/'
					<< combatStats->multiStrikes2[2] << '/'
					<< combatStats->multiStrikes2[3] << endl;
				
				
				output << endl << "Skills: " << combatStats->skillAttacks << endl;
				
				if (i >= 2){
					
					unordered_map<string, SkillDamageStats>& skillDamageStats = combatStats->skillDamageStats;
					for (unordered_map<string, SkillDamageStats>::iterator iter = skillDamageStats.begin(); iter != skillDamageStats.end(); iter ++){
						//printf("%25s%3dx(%3dC%3dF)%5d-%5d(%7.2f)%5d-%5d(%7.2f)\n", 
						output << iter->first						
							<< " x" << iter->second.numUses << " - "
							<< iter->second.crits.numHits + iter->second.critBlocks.numHits + iter->second.critParrys.numHits << " crits";
							if (iter->second.numUses >= 10 && iter->second.crits.numHits >= 3) output << " (" << (float)(iter->second.crits.numHits + iter->second.critBlocks.numHits + iter->second.critParrys.numHits) / iter->second.numUses * 100 << "%)";
							output << ", " << iter->second.numResists << " misses";

							if (iter->second.numUses >= 10 && iter->second.numResists >= 3) output << " (" << (float)iter->second.numResists / (iter->second.numResists + iter->second.numUses) * 100 << "%)";
							output << ": " << endl; 

							output << iter->second.normals.minDamage << '-' << iter->second.normals.maxDamage
							<< " (" << (float)iter->second.normals.totalDamage / iter->second.normals.numHits << " avg)";

						if (iter->second.crits.numHits > 0){
							output << " / Crits: " << iter->second.crits.minDamage << '-' << iter->second.crits.maxDamage
							<< " (" << (float)iter->second.crits.totalDamage / iter->second.crits.numHits << " avg)";
						}
						output << endl;
						
						if (iter->second.blocks.numHits > 0){
							output << "\tBlocked (" << iter->second.blocks.numHits << "x): " << iter->second.blocks.minDamage << '-' << iter->second.blocks.maxDamage
							<< " (" << (float)iter->second.blocks.totalDamage / iter->second.blocks.numHits << " avg)";

							if (iter->second.critBlocks.numHits > 0){
								output << " / Crits: " << iter->second.critBlocks.minDamage << '-' << iter->second.critBlocks.maxDamage
								<< " (" << (float)iter->second.critBlocks.totalDamage / iter->second.critBlocks.numHits << " avg)";
							}
							output << endl;
						}

						if (iter->second.parrys.numHits > 0){
							output << "\tParried (" << iter->second.parrys.numHits << "x): " << iter->second.parrys.minDamage << '-' << iter->second.parrys.maxDamage
							<< " (" << (float)iter->second.parrys.totalDamage / iter->second.parrys.numHits << " avg)";

							if (iter->second.critParrys.numHits > 0){
								output << " / Crits: " << iter->second.critParrys.minDamage << '-' << iter->second.critParrys.maxDamage
								<< " (" << (float)iter->second.critParrys.totalDamage / iter->second.critParrys.numHits << " avg)";
							}
							output << endl;
						}

						output << endl;
					}
				}
				output << "================================\n";
			}
		}
		return output.str();
	}

	string detailedDamageTally(){
		stringstream output;
		for (int i = 0; i < 4; i ++){	
			
				

			CombatStatsPair combatStatsPair = combatModule.combatStatsManager.getAllTargetsCombatStats();			
			CombatStatsPair individualTargetCombatStatsPair = combatModule.combatStatsManager.getLastTargetCombatStats();			

			CombatStats* combatStats = (i % 2 == 0) ? &combatStatsPair.first : &combatStatsPair.second;
			if (i >= 2) combatStats = (i % 2 == 0) ? &individualTargetCombatStatsPair.first : &individualTargetCombatStatsPair.second;
			
			SkillDamageStats* autoAttack[2];					

			autoAttack[0] = &combatStats->autoDamageStats1;
			autoAttack[1] = &combatStats->autoDamageStats2;
				
			
			if (i >= 2){
				//output << " (normal / crits)\n";

					

				for (int i = 0; i < 2; i ++){	

					if (i == 0) output << "mainhand: ";
					if (i == 1) output << "off hand: ";


					if (autoAttack[i]->normals.numHits > 0){
						output << "Clean normal hits (" << autoAttack[i]->normals.numHits << "x):\n";
						for (map<int, CounterEntry>::iterator iter = autoAttack[i]->normals.damageAmountsCounter.begin(); 
							iter != autoAttack[i]->normals.damageAmountsCounter.end(); iter ++){
								output << iter->first << ":\t";
								for (int i = 0; i < iter->second.numGained; i ++) output << '#';
								output << endl;

						}
						output << endl << endl;
					}

					if (autoAttack[i]->crits.numHits > 0){
						output << "Clean critical hits (" << autoAttack[i]->crits.numHits << "x):\n";
						for (map<int, CounterEntry>::iterator iter = autoAttack[i]->crits.damageAmountsCounter.begin(); 
							iter != autoAttack[i]->crits.damageAmountsCounter.end(); iter ++){
								output << iter->first << ":\t";
								for (int i = 0; i < iter->second.numGained; i ++) output << '#';
								output << endl;

						}
						output << endl << endl;
					}

					if (autoAttack[i]->blocks.numHits > 0){
						output << "Blocked normal hits (" << autoAttack[i]->blocks.numHits << "x):\n";
						for (map<int, CounterEntry>::iterator iter = autoAttack[i]->blocks.damageAmountsCounter.begin(); 
							iter != autoAttack[i]->blocks.damageAmountsCounter.end(); iter ++){
								output << iter->first << ":\t";
								for (int i = 0; i < iter->second.numGained; i ++) output << '#';
								output << endl;

						}
						output << endl << endl;
					}

					if (autoAttack[i]->critBlocks.numHits > 0){
						output << "Blocked critical hits (" << autoAttack[i]->critBlocks.numHits << "x):\n";
						for (map<int, CounterEntry>::iterator iter = autoAttack[i]->critBlocks.damageAmountsCounter.begin(); 
							iter != autoAttack[i]->critBlocks.damageAmountsCounter.end(); iter ++){
								output << iter->first << ":\t";
								for (int i = 0; i < iter->second.numGained; i ++) output << '#';
								output << endl;

						}
						output << endl << endl;
					}

					if (autoAttack[i]->parrys.numHits > 0){
						output << "Parried normal hits (" << autoAttack[i]->parrys.numHits << "x):\n";
						for (map<int, CounterEntry>::iterator iter = autoAttack[i]->parrys.damageAmountsCounter.begin(); 
							iter != autoAttack[i]->parrys.damageAmountsCounter.end(); iter ++){
								output << iter->first << ":\t";
								for (int i = 0; i < iter->second.numGained; i ++) output << '#';
								output << endl;

						}
						output << endl << endl;
					}

					if (autoAttack[i]->critParrys.numHits > 0){
						output << "Parried critical hits (" << autoAttack[i]->critParrys.numHits << "x):\n";
						for (map<int, CounterEntry>::iterator iter = autoAttack[i]->critParrys.damageAmountsCounter.begin(); 
							iter != autoAttack[i]->critParrys.damageAmountsCounter.end(); iter ++){
								output << iter->first << ":\t";
								for (int i = 0; i < iter->second.numGained; i ++) output << '#';
								output << endl;

						}
						output << endl << endl;
					}
					

				}

				unordered_map<string, SkillDamageStats>& skillDamageStats = combatStats->skillDamageStats;
				for (unordered_map<string, SkillDamageStats>::iterator iter2 = skillDamageStats.begin(); iter2 != skillDamageStats.end(); iter2 ++){
					output << iter2->first << ':' << endl;

					if (iter2->second.normals.numHits > 0){
						output << "Clean normal hits (" << iter2->second.normals.numHits << "x):\n";
						for (map<int, CounterEntry>::iterator iter = iter2->second.normals.damageAmountsCounter.begin(); 
							iter != iter2->second.normals.damageAmountsCounter.end(); iter ++){
								output << iter->first << ":\t";
								for (int i = 0; i < iter->second.numGained; i ++) output << '#';
								output << endl;

						}
						output << endl << endl;
					}

					if (iter2->second.crits.numHits > 0){
						output << "Clean critical hits (" << iter2->second.crits.numHits << "x):\n";
						for (map<int, CounterEntry>::iterator iter = iter2->second.crits.damageAmountsCounter.begin(); 
							iter != iter2->second.crits.damageAmountsCounter.end(); iter ++){
								output << iter->first << ":\t";
								for (int i = 0; i < iter->second.numGained; i ++) output << '#';
								output << endl;

						}
						output << endl << endl;
					}

					if (iter2->second.blocks.numHits > 0){
						output << "Blocked normal hits (" << iter2->second.blocks.numHits << "x):\n";
						for (map<int, CounterEntry>::iterator iter = iter2->second.blocks.damageAmountsCounter.begin(); 
							iter != iter2->second.blocks.damageAmountsCounter.end(); iter ++){
								output << iter->first << ":\t";
								for (int i = 0; i < iter->second.numGained; i ++) output << '#';
								output << endl;

						}
						output << endl << endl;
					}

					if (iter2->second.critBlocks.numHits > 0){
						output << "Blocked critical hits (" << iter2->second.critBlocks.numHits << "x):\n";
						for (map<int, CounterEntry>::iterator iter = iter2->second.critBlocks.damageAmountsCounter.begin(); 
							iter != iter2->second.critBlocks.damageAmountsCounter.end(); iter ++){
								output << iter->first << ":\t";
								for (int i = 0; i < iter->second.numGained; i ++) output << '#';
								output << endl;

						}
						output << endl << endl;
					}

					if (iter2->second.parrys.numHits > 0){
						output << "Parried normal hits (" << iter2->second.parrys.numHits << "x):\n";
						for (map<int, CounterEntry>::iterator iter = iter2->second.parrys.damageAmountsCounter.begin(); 
							iter != iter2->second.parrys.damageAmountsCounter.end(); iter ++){
								output << iter->first << ":\t";
								for (int i = 0; i < iter->second.numGained; i ++) output << '#';
								output << endl;

						}
						output << endl << endl;
					}

					if (iter2->second.critParrys.numHits > 0){
						output << "Parried critical hits (" << iter2->second.critParrys.numHits << "x):\n";
						for (map<int, CounterEntry>::iterator iter = iter2->second.critParrys.damageAmountsCounter.begin(); 
							iter != iter2->second.critParrys.damageAmountsCounter.end(); iter ++){
								output << iter->first << ":\t";
								for (int i = 0; i < iter->second.numGained; i ++) output << '#';
								output << endl;

						}
						output << endl << endl;
					}
				}
			}				
				/*
			output << endl << "Skills: " << combatStats->skillAttacks << endl;
				
			if (i >= 2){
					
				unordered_map<string, SkillDamageStats>& skillDamageStats = combatStats->skillDamageStats;
				for (unordered_map<string, SkillDamageStats>::iterator iter = skillDamageStats.begin(); iter != skillDamageStats.end(); iter ++){
					//printf("%25s%3dx(%3dC%3dF)%5d-%5d(%7.2f)%5d-%5d(%7.2f)\n", 
					output << iter->first						
						<< " x" << iter->second.numUses << " ("
						<< iter->second.crits.numHits + iter->second.critBlocks.numHits + iter->second.critParrys.numHits << " crits"
						<< " / " << iter->second.numResists << " misses"
						<< "): " << endl 
						<< iter->second.normals.minDamage << '-' << iter->second.normals.maxDamage
						<< " (" << (float)iter->second.normals.totalDamage / iter->second.normals.numHits << " avg)";

					if (iter->second.crits.numHits > 0){
						output << " / Crits: " << iter->second.crits.minDamage << '-' << iter->second.crits.maxDamage
						<< " (" << (float)iter->second.crits.totalDamage / iter->second.crits.numHits << " avg)";
					}
					output << endl << endl;
						
					if (iter->second.blocks.numHits > 0){
						output << "\tBlocked (" << iter->second.blocks.numHits << "x): " << iter->second.blocks.minDamage << '-' << iter->second.blocks.maxDamage
						<< " (" << (float)iter->second.blocks.totalDamage / iter->second.blocks.numHits << " avg)";

						if (iter->second.critBlocks.numHits > 0){
							output << " / Crits: " << iter->second.critBlocks.minDamage << '-' << iter->second.critBlocks.maxDamage
							<< " (" << (float)iter->second.critBlocks.totalDamage / iter->second.critBlocks.numHits << " avg)";
						}
						output << endl;
					}

					if (iter->second.parrys.numHits > 0){
						output << "\tParried (" << iter->second.parrys.numHits << "x): " << '-' << iter->second.parrys.maxDamage
						<< " (" << (float)iter->second.parrys.totalDamage / iter->second.parrys.numHits << " avg)";

						if (iter->second.critParrys.numHits > 0){
							output << " / Crits: " << iter->second.critParrys.minDamage << '-' << iter->second.critParrys.maxDamage
							<< " (" << (float)iter->second.critParrys.totalDamage / iter->second.critParrys.numHits << " avg)";
						}
						output << endl;
					}
				}
			}
			*/
			output << "================================\n";
			
		}
		return output.str();
	}

	void saveToFile(){
		ofstream ofs;
		ofs.open("crit2test.txt");

	ofs << "Attacker Lvl: " << endl;
	ofs << "Class: " << endl;
	ofs << endl;
	ofs << "Mainhand" << endl;
	ofs << "Weapon type: " << endl;
	ofs << "Char Screen Attack: " << endl;
	ofs << "Min-max damage: " << endl;
	ofs << "Accuracy: " << endl;
	ofs << "Crit Strike: " << endl;
	ofs << endl;
	ofs << "Offhand" << endl;
	ofs << "Weapon type: " << endl;
	ofs << "Char Screen Attack: " << endl;
	ofs << "Min-max damage: " << endl;
	ofs << "Accuracy: " << endl;
	ofs << "Crit Strike: " << endl;
	ofs << endl;
	ofs << "Armor/wing enchant dmg: " << endl;
	ofs << "Green Attack less mastery and % skills: " << endl;
	ofs << "Power Shard: " << endl;
	ofs << endl;
	ofs << "Magic Boost: " << endl;
	ofs << "Magic Acc: " << endl;
	ofs << "Crit Spell: " << endl;
	ofs << endl;
	ofs << "Flying: " << endl;
	ofs << endl;
	ofs << "Buffs: " << endl;
	ofs << endl;
	ofs << "PvE Attack: " << endl;
	ofs << "PvP Attack: " << endl;
	ofs << endl;
	ofs << "--------------------------------------------------" << endl;
	ofs << endl;
	ofs << "Defender Lvl: " << endl;
	ofs << "Class / Mob: " << endl;
	ofs << endl;
	ofs << "Physical Defense: " << endl;
	ofs << "Block: " << endl;
	ofs << "Parry: " << endl;
	ofs << "Evasion: " << endl;
	ofs << "Strike Resist: " << endl;
	ofs << "Strike Fortitude: " << endl;
	ofs << endl;
	ofs << "Magical Defense: " << endl;
	ofs << "Magic Suppression: " << endl;
	ofs << "Magic Resist: " << endl;
	ofs << "Spell Resist: " << endl;
	ofs << "Spell Fortitude: " << endl;
	ofs << endl;
	ofs << "Fire Resist: " << endl;
	ofs << "Wind Resist: " << endl;
	ofs << "Water Resist: " << endl;
	ofs << "Earth Resist: " << endl;
	ofs << endl;
	ofs << "PvP Defense: " << endl;
	ofs << endl;
	ofs << "--------------------------------------------------" << endl;

		ofs << formatText();
		ofs << detailedDamageTally();
		ofs.close();
	}

	void executeChatLogCommand(ChatLogCommand& command){
		switch(command.getMessageRuleCode()){
		case STR_DONOT_HAVE_RECOVER_EXPERIENCE:
		case STR_SUCCESS_RECOVER_EXPERIENCE:
			saveToFile();
			break;
		}

	}




};

int main(){
	CombatModule combatModule;
	SoulHealToSaveToFile soulHealToSaveToFile(combatModule);

	
	string aionDirectory = "D:/Aion/";
	
	LogFileUtility logFileUtility;
	bool status = logFileUtility.setAionDirectory(aionDirectory);

	if (!status) cout << "UNABLE TO OPEN CHAT.LOG" << endl;

	logFileUtility.registerModule(combatModule);
	logFileUtility.registerModule(soulHealToSaveToFile);
	
	int refreshCounter = 0;
	while(true){
		logFileUtility.parseLogFile();
	
		refreshCounter ++;
		if (refreshCounter >= 10){
			refreshCounter = 0;
			system("cls");	
	
			cout << soulHealToSaveToFile.formatText(true) << endl;
			//cout << soulHealToSaveToFile.detailedDamageTally() << endl;
			/*
			CombatStatsPair combatStatsPair = combatModule.combatStatsManager.getAllTargetsCombatStats();			
			CombatStatsPair individualTargetCombatStatsPair = combatModule.combatStatsManager.getLastTargetCombatStats();			

			
			for (int i = 0; i < 4; i ++){	
				if (i % 2 == combatModule.weaponSwitch.getCurrentSet()){

					CombatStats* combatStats = (i % 2 == 0) ? &combatStatsPair.first : &combatStatsPair.second;
					if (i >= 2) combatStats = (i % 2 == 0) ? &individualTargetCombatStatsPair.first : &individualTargetCombatStatsPair.second;
				
					if (i <= 1) printf("ALL TARGETS\n");
					else if (i >= 2) printf("Target: %s\n", combatModule.combatStatsManager.getLastTarget().c_str());

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
				
					printf("Auto Attacks: %dx (%dC%3dF)", 
						autoAttack[0]->numUses, 
						autoAttack[0]->crits.numHits + autoAttack[0]->critBlocks.numHits + autoAttack[0]->critParrys.numHits,
						autoAttack[0]->numResists
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
			*/
		}
		Sleep(100);
	}		
}