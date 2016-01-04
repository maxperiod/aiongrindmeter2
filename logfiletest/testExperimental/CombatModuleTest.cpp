#include "gtest/gtest.h"
//#include "../parser/MaxPeriodParser.h"
//#include "../lookups/RuleStringsHardCodedNA.h"
//#include "../modules/SoulHealerModule.h"

#include "../parser/LogFileUtility.h"
#include "../testModule/testLog/TemporaryLogFile.h"
#include "../experimental/CombatModule.h"

class CombatModuleTest: public ::testing::Test{
protected:
	//MaxPeriodParser parser;
	//RuleStringsHardCodedNA rules;
	
	//ExpModule expModule;
	CombatModule combatModule;
	
	TemporaryLogFile logFile;
	
	LogFileUtility logFileUtility;
	

	CombatModuleTest(): logFile("testModule/testLog/tests.log", "testModule/testLog/Chat.log")//,
		//soulHealerModule(expModule, apModule, kinahModule)
	{
	}

	
	virtual void SetUp(){
		logFile.makeFileCopy();

		logFileUtility.registerModule(combatModule);
	
		string aionDirectory = "testModule/testLog/";
		
		ASSERT_TRUE(logFileUtility.setAionDirectory(aionDirectory));
	
	}


	virtual void TearDown(){		
		logFile.deleteFileCopy();
	}
};

TEST_F(CombatModuleTest, regularAttack1){
	logFile.appendFile("2014.05.10 11:52:43 : You inflicted 659 damage on Supraklaw Forager. ");
	logFile.appendFile("2014.05.10 11:52:43 : You inflicted 65 damage on Supraklaw Forager. ");
	
	logFileUtility.parseLogFile();
	logFileUtility.parseLogFile();
	
	CombatStats& cs = combatModule.combatStatsManager.getAllTargetsCombatStats().first;

	EXPECT_EQ(1,cs.numHits);
	EXPECT_EQ(0,cs.numCrits);
	
	EXPECT_EQ(0,cs.enemyBlock);
	EXPECT_EQ(0,cs.enemyParry);
	EXPECT_EQ(0,cs.enemyEvade);
	
	EXPECT_EQ(0,cs.multiStrikes[0]);
	EXPECT_EQ(1,cs.multiStrikes[1]);
	EXPECT_EQ(0,cs.multiStrikes[2]);
	EXPECT_EQ(0,cs.multiStrikes[3]);

	EXPECT_EQ(659+65,cs.totalDamageInflicted); 

	SkillDamageStats& sc = cs.autoDamageStats1;
	

	EXPECT_EQ(659, sc.normals.minDamage);
	EXPECT_EQ(659, sc.normals.maxDamage);
	EXPECT_EQ(659, sc.normals.totalDamage);
	EXPECT_EQ(1, sc.normals.numHits);

	CombatStats& cs2 = combatModule.combatStatsManager.getIndividualTargetCombatStats("Supraklaw Forager").first;
	
	EXPECT_EQ(1,cs2.numHits);
	EXPECT_EQ(0,cs2.numCrits);
	
	EXPECT_EQ(0,cs2.enemyBlock);
	EXPECT_EQ(0,cs2.enemyParry);
	EXPECT_EQ(0,cs2.enemyEvade);
	
	EXPECT_EQ(0,cs2.multiStrikes[0]);
	EXPECT_EQ(1,cs2.multiStrikes[1]);
	EXPECT_EQ(0,cs2.multiStrikes[2]);
	EXPECT_EQ(0,cs2.multiStrikes[3]);

	EXPECT_EQ(659+65,cs2.totalDamageInflicted); 

	SkillDamageStats& sc2 = cs2.autoDamageStats1;
	
	EXPECT_EQ(659, sc2.normals.minDamage);
	EXPECT_EQ(659, sc2.normals.maxDamage);
	EXPECT_EQ(659, sc2.normals.totalDamage);
	EXPECT_EQ(1, sc2.normals.numHits);

}

TEST_F(CombatModuleTest, regularAttack2){
	logFile.appendFile("2014.07.15 21:26:18 : You inflicted 776 damage on Training Dummy. ");
	logFile.appendFile("2014.07.15 21:26:18 : You inflicted 77 damage on Training Dummy. ");
	logFileUtility.parseLogFile();
	logFile.appendFile("2014.07.15 21:26:18 : You inflicted 77 damage on Training Dummy. ");
	logFileUtility.parseLogFile();
	logFile.appendFile("2014.07.15 21:26:19 : You inflicted 720 damage on Training Dummy. ");
	logFile.appendFile("2014.07.15 21:26:19 : You inflicted 72 damage on Training Dummy. ");
	logFile.appendFile("2014.07.15 21:26:19 : You inflicted 72 damage on Training Dummy. ");
	logFileUtility.parseLogFile();
	logFileUtility.parseLogFile();
	logFile.appendFile("2014.07.15 21:26:21 : Critical Hit! You inflicted 1,547 critical damage on Training Dummy. ");
	logFile.appendFile("2014.07.15 21:26:21 : You inflicted 154 damage on Training Dummy. ");
	logFileUtility.parseLogFile();
	logFileUtility.parseLogFile();

	CombatStats& cs = combatModule.combatStatsManager.getAllTargetsCombatStats().first;
	
	EXPECT_EQ(3,cs.numHits);
	EXPECT_EQ(1,cs.numCrits);
	
	EXPECT_EQ(0,cs.enemyBlock);
	EXPECT_EQ(0,cs.enemyParry);
	EXPECT_EQ(0,cs.enemyEvade);
	
	EXPECT_EQ(0,cs.multiStrikes[0]);
	EXPECT_EQ(1,cs.multiStrikes[1]);
	EXPECT_EQ(2,cs.multiStrikes[2]);
	EXPECT_EQ(0,cs.multiStrikes[3]);

	EXPECT_EQ(776+77+77+720+72+72+1547+154,cs.totalDamageInflicted);
	
	SkillDamageStats& sc = cs.autoDamageStats1;	

	EXPECT_EQ(720, sc.normals.minDamage);
	EXPECT_EQ(776, sc.normals.maxDamage);
	EXPECT_EQ(720+776, sc.normals.totalDamage);
	EXPECT_EQ(2, sc.normals.numHits);

	EXPECT_EQ(1547, sc.crits.minDamage);
	EXPECT_EQ(1547, sc.crits.maxDamage);
	EXPECT_EQ(1547, sc.crits.totalDamage);
	EXPECT_EQ(1, sc.crits.numHits);

}

TEST_F(CombatModuleTest, attackAndSkills){

	logFile.appendFile("2014.06.18 17:41:13 : Your Physical Def has been weakened by using Reroute Power I. ");
	logFile.appendFile("2014.06.18 17:41:13 : You received the effect by using Reroute Power I. ");
	logFileUtility.parseLogFile();
	logFile.appendFile("2014.06.18 17:41:15 : You inflicted 1,840 damage on Sprawling Agrint by using Inquisitor's Blow IV. ");
	
	logFile.appendFile("2014.06.18 17:41:15 : Reroute Power Effect has been activated. ");
	logFile.appendFile("2014.06.18 17:41:15 : Sprawling Agrint received 235 damage due to the effect of Reroute Power Effect. ");

	logFile.appendFile("2014.06.18 17:41:15 : Critical Hit! You inflicted 1,588 critical damage on Sprawling Agrint. ");
	logFile.appendFile("2014.06.18 17:41:15 : You inflicted 158 damage on Sprawling Agrint. ");
	logFileUtility.parseLogFile();
	logFile.appendFile("2014.06.18 17:41:16 : You parried Sprawling Agrint's attack. ");
	logFile.appendFile("2014.06.18 17:41:16 : You received 228 damage from Sprawling Agrint. ");
	
	logFile.appendFile("2014.06.18 17:41:16 : You inflicted 2,791 damage on Sprawling Agrint by using Shining Slash V. ");
	
	logFile.appendFile("2014.06.18 17:41:16 : Reroute Power Effect has been activated. ");
	logFile.appendFile("2014.06.18 17:41:16 : Sprawling Agrint received 235 damage due to the effect of Reroute Power Effect. ");

	logFile.appendFile("2014.06.18 17:41:16 : Reroute Power Effect has been activated. ");
	logFile.appendFile("2014.06.18 17:41:16 : Sprawling Agrint received 235 damage due to the effect of Reroute Power Effect. ");
	
	logFile.appendFile("2014.06.18 17:41:16 : Critical Hit!You inflicted 3,085 damage on Sprawling Agrint by using Blood Pact I. ");
	logFileUtility.parseLogFile();
	logFile.appendFile("2014.06.18 17:41:17 : Reroute Power Effect has been activated. ");
	logFile.appendFile("2014.06.18 17:41:17 : Sprawling Agrint received 235 damage due to the effect of Reroute Power Effect. ");

	logFile.appendFile("2014.06.18 17:41:17 : Critical Hit! You inflicted 1,395 critical damage on Sprawling Agrint. ");
	logFile.appendFile("2014.06.18 17:41:17 : You inflicted 139 damage on Sprawling Agrint. ");
	logFileUtility.parseLogFile();
	logFile.appendFile("2014.06.18 17:41:18 : [3.LFG] [charname:Stoia;1.0000 0.6941 0.6941]:           WTS             [item:110501514;ver6;;;Oppye 0;][item:111501414;ver6;;;Oppye 0;] PM OFFER ");
	
	logFile.appendFile("2014.06.18 17:41:18 : You inflicted 1,574 damage on Sprawling Agrint by using Blood Pact I. ");
	
	logFile.appendFile("2014.06.18 17:41:18 : Reroute Power Effect has been activated. ");
	logFile.appendFile("2014.06.18 17:41:18 : Sprawling Agrint received 235 damage due to the effect of Reroute Power Effect. ");
	
	logFile.appendFile("2014.06.18 17:41:18 : Reroute Power Effect has been activated. ");
	logFile.appendFile("2014.06.18 17:41:18 : Sprawling Agrint received 235 damage due to the effect of Reroute Power Effect. ");
	
	logFile.appendFile("2014.06.18 17:41:18 : Sprawling Agrint is no longer shocked. ");
	
	logFile.appendFile("2014.06.18 17:41:18 : You inflicted 1,566 damage on Sprawling Agrint by using Blood Pact I. ");
	logFileUtility.parseLogFile();
	logFile.appendFile("2014.06.18 17:41:19 : Reroute Power Effect has been activated. ");
	logFile.appendFile("2014.06.18 17:41:19 : Sprawling Agrint received 235 damage due to the effect of Reroute Power Effect. ");
	
	logFile.appendFile("2014.06.18 17:41:19 : You received 364 damage from Sprawling Agrint. ");
	
	logFile.appendFile("2014.06.18 17:41:19 : You inflicted 782 damage on Sprawling Agrint. ");
	logFile.appendFile("2014.06.18 17:41:19 : You inflicted 78 damage on Sprawling Agrint. ");
	
	logFile.appendFile("2014.06.18 17:41:19 : You inflicted 862 damage on Sprawling Agrint by using Dazing Severe Blow IV. ");
	logFile.appendFile("2014.06.18 17:41:19 : Sprawling Agrint's attack speed has decreased because Momomomoo used Dazing Severe Blow IV. ");
	logFileUtility.parseLogFile();
	logFile.appendFile("2014.06.18 17:41:20 : Reroute Power Effect has been activated. ");
	logFile.appendFile("2014.06.18 17:41:20 : Sprawling Agrint received 235 damage due to the effect of Reroute Power Effect. ");
	
	logFile.appendFile("2014.06.18 17:41:20 : Reroute Power Effect has been activated. ");
	logFile.appendFile("2014.06.18 17:41:20 : Sprawling Agrint received 235 damage due to the effect of Reroute Power Effect. ");
	
	logFile.appendFile("2014.06.18 17:41:20 : You inflicted 1,134 damage on Sprawling Agrint by using Divine Blow IV. ");
	
	logFile.appendFile("2014.06.18 17:41:20 : Reroute Power Effect has been activated. ");
	logFile.appendFile("2014.06.18 17:41:20 : Sprawling Agrint received 235 damage due to the effect of Reroute Power Effect. ");
	logFileUtility.parseLogFile();
	logFile.appendFile("2014.06.18 17:41:21 : [3.LFG] [charname:Zombiemastor;1.0000 0.6941 0.6941]: ??[kvalue:0;BlueBird;str]?? Is recruiting active and HARDCORE SIEGERS lvl 60+ to join our Family!, For [where:PVP], [where:PVE], [where:SIEGES!] AND other fun shenanigans!.L8 Legion with TS3, Whisper m ");
	logFile.appendFile("2014.06.18 17:41:21 : You received 314 damage from Sprawling Agrint. ");
	
	logFile.appendFile("2014.06.18 17:41:21 : You inflicted 772 damage on Sprawling Agrint. ");
	logFile.appendFile("2014.06.18 17:41:21 : You inflicted 77 damage on Sprawling Agrint. ");
	logFile.appendFile("2014.06.18 17:41:21 : You inflicted 77 damage on Sprawling Agrint. ");
	
	logFile.appendFile("2014.06.18 17:41:21 : You inflicted 1,074 damage on Sprawling Agrint by using Provoking Severe Blow V. ");
	
	logFile.appendFile("2014.06.18 17:41:21 : Momomomoo Increased Sprawling Agrint's enmity Increase by using Provoking Severe Blow V. ");
	logFileUtility.parseLogFile();
	logFile.appendFile("2014.06.18 17:41:22 : Reroute Power Effect has been activated. ");
	logFile.appendFile("2014.06.18 17:41:22 : Sprawling Agrint received 235 damage due to the effect of Reroute Power Effect. ");
	
	logFile.appendFile("2014.06.18 17:41:22 : Reroute Power Effect has been activated. ");
	
	logFile.appendFile("2014.06.18 17:41:22 : Quest updated: [Coin] Settle the Road ");
	logFile.appendFile("2014.06.18 17:41:22 : You have gained 111,235 XP from Sprawling Agrint (Energy of Repose 31,781). ");
	logFile.appendFile("2014.06.18 17:41:22 : Sprawling Agrint restored its attack speed. ");
	logFile.appendFile("2014.06.18 17:41:22 : You have gained 37 Abyss Points. ");

	logFileUtility.parseLogFile();
	logFileUtility.parseLogFile();

	CombatStats& cs = combatModule.combatStatsManager.getAllTargetsCombatStats().first;
	
	EXPECT_EQ(12,cs.numHits);
	EXPECT_EQ(3,cs.numCrits);
	
	EXPECT_EQ(0,cs.enemyBlock);
	EXPECT_EQ(0,cs.enemyParry);
	EXPECT_EQ(0,cs.enemyEvade);
	
	EXPECT_EQ(0,cs.multiStrikes[0]);
	EXPECT_EQ(3,cs.multiStrikes[1]);
	EXPECT_EQ(1,cs.multiStrikes[2]);
	EXPECT_EQ(0,cs.multiStrikes[3]);

	EXPECT_EQ(1, combatModule.combatStatsManager.getAllTargetsCombatStats().first.skillDamageStats.count("Inquisitor's Blow IV"));
	SkillDamageStats& skill1 = combatModule.combatStatsManager.getAllTargetsCombatStats().first.skillDamageStats["Inquisitor's Blow IV"];
	
	EXPECT_EQ(1840, skill1.normals.minDamage);
	EXPECT_EQ(1840, skill1.normals.maxDamage);
	EXPECT_EQ(1840, skill1.normals.totalDamage);
	EXPECT_EQ(1, skill1.normals.numHits);
	
	EXPECT_EQ(1, combatModule.combatStatsManager.getAllTargetsCombatStats().first.skillDamageStats.count("Shining Slash V"));
	SkillDamageStats& skill2 = combatModule.combatStatsManager.getAllTargetsCombatStats().first.skillDamageStats["Shining Slash V"];
	EXPECT_EQ(1, skill2.normals.numHits);
	
	EXPECT_EQ(1, combatModule.combatStatsManager.getAllTargetsCombatStats().first.skillDamageStats.count("Blood Pact I"));
	SkillDamageStats& skill3 = combatModule.combatStatsManager.getAllTargetsCombatStats().first.skillDamageStats["Blood Pact I"];
	EXPECT_EQ(1, skill3.crits.numHits);
	EXPECT_EQ(2, skill3.normals.numHits);	

	//EXPECT_EQ(0, cs.skillAttacks);

}

TEST_F(CombatModuleTest, assassin){

	logFile.appendFile("2014.11.21 22:14:53 : You received 323 damage from Steel Rake Watcher. ");
	logFileUtility.parseLogFile();
	logFile.appendFile("2014.11.21 22:14:54 : You inflicted 198 damage on Steel Rake Watcher. ");
	logFile.appendFile("2014.11.21 22:14:54 : You inflicted 150 damage on Steel Rake Watcher. ");
	logFileUtility.parseLogFile();
	logFile.appendFile("2014.11.21 22:14:55 : You inflicted 501 damage on Steel Rake Watcher by using Swift Edge IV. ");
	
	logFile.appendFile("2014.11.21 22:14:55 : You received 342 damage from Steel Rake Watcher. ");
	logFileUtility.parseLogFile();
	logFile.appendFile("2014.11.21 22:14:56 : You inflicted 214 damage on Steel Rake Watcher. ");
	logFile.appendFile("2014.11.21 22:14:56 : You inflicted 143 damage on Steel Rake Watcher. ");

	logFile.appendFile("2014.11.21 22:14:56 : You inflicted 446 damage on Steel Rake Watcher by using Soul Slash IV. ");
	logFileUtility.parseLogFile();
	logFile.appendFile("2014.11.21 22:14:57 : You evaded Steel Rake Watcher's attack. ");

	logFile.appendFile("2014.11.21 22:14:57 : You inflicted 219 damage on Steel Rake Watcher. ");
	logFile.appendFile("2014.11.21 22:14:57 : You inflicted 190 damage on Steel Rake Watcher. ");
	logFile.appendFile("2014.11.21 22:14:57 : You inflicted 19 damage on Steel Rake Watcher. ");
	
	logFile.appendFile("2014.11.21 22:14:57 : You inflicted 231 damage and the rune carve effect on Steel Rake Watcher by using Rune Carve III. ");
	logFileUtility.parseLogFile();
	logFile.appendFile("2014.11.21 22:14:58 : You inflicted 198 damage on Steel Rake Watcher. ");
	logFile.appendFile("2014.11.21 22:14:58 : You inflicted 183 damage on Steel Rake Watcher. ");
	logFile.appendFile("2014.11.21 22:14:58 : You inflicted 18 damage on Steel Rake Watcher. ");
	
	logFile.appendFile("2014.11.21 22:14:58 : You inflicted 249 damage and the rune carve effect on Steel Rake Watcher by using Sigil Strike II. ");
	logFileUtility.parseLogFile();
	logFile.appendFile("2014.11.21 22:14:59 : You evaded Steel Rake Watcher's attack. ");
	
	logFile.appendFile("2014.11.21 22:14:59 : Critical Hit! You inflicted 480 critical damage on Steel Rake Watcher. ");
	logFile.appendFile("2014.11.21 22:14:59 : Critical Hit! You inflicted 346 critical damage on Steel Rake Watcher. ");
	logFile.appendFile("2014.11.21 22:14:59 : You inflicted 34 damage on Steel Rake Watcher. ");
	logFileUtility.parseLogFile();
	logFile.appendFile("2014.11.21 22:15:00 : You inflicted 317 damage and the rune carve effect on Steel Rake Watcher by using Fang Strike III. ");
	
	logFile.appendFile("2014.11.21 22:15:00 : Critical Hit! You inflicted 512 critical damage on Steel Rake Watcher. ");
	logFile.appendFile("2014.11.21 22:15:00 : Critical Hit! You inflicted 480 critical damage on Steel Rake Watcher. ");
	logFile.appendFile("2014.11.21 22:15:00 : You inflicted 48 damage on Steel Rake Watcher. ");
	logFileUtility.parseLogFile();
	logFile.appendFile("2014.11.21 22:15:01 : You inflicted 344 damage and the rune carve effect on Steel Rake Watcher by using Beast Kick II. ");
	
	logFile.appendFile("2014.11.21 22:15:01 : You received 312 damage from Steel Rake Watcher. ");
	logFileUtility.parseLogFile();
	logFile.appendFile("2014.11.21 22:15:02 : You inflicted 212 damage on Steel Rake Watcher. ");
	logFile.appendFile("2014.11.21 22:15:02 : You inflicted 142 damage on Steel Rake Watcher. ");
	
	logFile.appendFile("2014.11.21 22:15:02 : Critical Hit!You inflicted 899 damage and the rune carve effect on Steel Rake Watcher by using Beast Swipe I. ");
	logFileUtility.parseLogFile();
	logFile.appendFile("2014.11.21 22:15:03 : You boosted your skill by using Killer's Eye I. ");
	logFile.appendFile("2014.11.21 22:15:03 : Your Accuracy,Magical Acc,Stun Penetration has been boosted by using Killer's Eye I. ");
	logFile.appendFile("2014.11.21 22:15:03 : Your Aerial Thrust Resistance Penetration,Spin Penetration has been boosted by using Killer's Eye I. ");
	
	logFile.appendFile("2014.11.21 22:15:03 : You received 321 damage from Steel Rake Watcher. ");
	
	logFile.appendFile("2014.11.21 22:15:03 : You inflicted 903 damage on Steel Rake Watcher by using Blood Rune I. ");
	logFileUtility.parseLogFile();
	logFileUtility.parseLogFile();
	logFile.appendFile("2014.11.21 22:15:05 : You inflicted 207 damage on Steel Rake Watcher. ");
	logFile.appendFile("2014.11.21 22:15:05 : You inflicted 203 damage on Steel Rake Watcher. ");
	
	logFile.appendFile("2014.11.21 22:15:05 : Steel Rake Watcher received 956 damage due to the effect of Blood Rune I Bonus Effect. ");
	logFile.appendFile("2014.11.21 22:15:05 : You recovered 956 HP by using Blood Rune I Bonus Effect. ");
	
	logFile.appendFile("2014.11.21 22:15:05 : You inflicted 777 damage on Steel Rake Watcher by using Swift Edge IV. ");
	
	logFile.appendFile("2014.11.21 22:15:05 : You received 356 damage from Steel Rake Watcher. ");
	logFileUtility.parseLogFile();
	logFile.appendFile("2014.11.21 22:15:06 : Critical Hit! You inflicted 496 critical damage on Steel Rake Watcher. ");
	logFile.appendFile("2014.11.21 22:15:06 : Critical Hit! You inflicted 454 critical damage on Steel Rake Watcher. ");
	logFile.appendFile("2014.11.21 22:15:06 : You inflicted 45 damage on Steel Rake Watcher. ");
	
	logFile.appendFile("2014.11.21 22:15:06 : You inflicted 431 damage on Steel Rake Watcher by using Soul Slash IV. ");

	logFileUtility.parseLogFile();
	logFileUtility.parseLogFile();

	
	CombatStats& cs = combatModule.combatStatsManager.getAllTargetsCombatStats().first;
	
	EXPECT_EQ(10+9,cs.numHits);
	EXPECT_EQ(4,cs.numCrits);
	
	EXPECT_EQ(0,cs.enemyBlock);
	EXPECT_EQ(0,cs.enemyParry);
	EXPECT_EQ(0,cs.enemyEvade);
	
	EXPECT_EQ(9,cs.multiStrikes[0]);
	EXPECT_EQ(0,cs.multiStrikes[1]);
	EXPECT_EQ(0,cs.multiStrikes[2]);
	EXPECT_EQ(0,cs.multiStrikes[3]);

	EXPECT_EQ(4,cs.multiStrikes2[0]);
	EXPECT_EQ(5,cs.multiStrikes2[1]);
	EXPECT_EQ(0,cs.multiStrikes2[2]);
	EXPECT_EQ(0,cs.multiStrikes2[3]);

	SkillDamageStats& autoAttack1 = combatModule.combatStatsManager.getAllTargetsCombatStats().first.autoDamageStats1;
	SkillDamageStats& autoAttack2 = combatModule.combatStatsManager.getAllTargetsCombatStats().first.autoDamageStats2;
	
	EXPECT_EQ(9, autoAttack1.numUses);	
	EXPECT_EQ(198, autoAttack1.normals.minDamage);
	EXPECT_EQ(219, autoAttack1.normals.maxDamage);
	EXPECT_EQ(198+214+219+198+212+207, autoAttack1.normals.totalDamage);
	EXPECT_EQ(6, autoAttack1.normals.numHits);

	EXPECT_EQ(9, autoAttack2.numUses);	
	EXPECT_EQ(142, autoAttack2.normals.minDamage);
	EXPECT_EQ(203, autoAttack2.normals.maxDamage);
	EXPECT_EQ(150+143+190+183+142+203, autoAttack2.normals.totalDamage);
	EXPECT_EQ(6, autoAttack2.normals.numHits);


	unordered_map<string, SkillDamageStats>& sds = combatModule.combatStatsManager.getAllTargetsCombatStats().first.skillDamageStats;
	EXPECT_EQ(2, sds.at("Swift Edge IV").numUses);

	EXPECT_EQ(2, sds.at("Swift Edge IV").numUses);	
	EXPECT_EQ(501, sds.at("Swift Edge IV").normals.minDamage);
	EXPECT_EQ(777, sds.at("Swift Edge IV").normals.maxDamage);
	EXPECT_EQ(501+777, sds.at("Swift Edge IV").normals.totalDamage);
	EXPECT_EQ(2, sds.at("Swift Edge IV").normals.numHits);


	EXPECT_EQ(2, sds.at("Soul Slash IV").numUses);

	EXPECT_EQ(431, sds.at("Soul Slash IV").normals.minDamage);
	EXPECT_EQ(446, sds.at("Soul Slash IV").normals.maxDamage);
	EXPECT_EQ(431+446, sds.at("Soul Slash IV").normals.totalDamage);
	EXPECT_EQ(2, sds.at("Soul Slash IV").normals.numHits);

}

TEST_F(CombatModuleTest, evasion){

	logFile.appendFile("2014.11.26 22:09:57 : Dragonmagic-IS evaded the attack. ");
	logFileUtility.parseLogFile();
	
	CombatStats& cs = combatModule.combatStatsManager.getAllTargetsCombatStats().first;
	CombatStats& cs2 = combatModule.combatStatsManager.getIndividualTargetCombatStats("Dragonmagic-IS").first;
	
	EXPECT_EQ(1, cs.enemyEvade);
	EXPECT_EQ(1, cs2.enemyEvade);

	logFile.appendFile("2014.11.26 22:09:36 : Dragonmagic-IS evaded Shield Counter VI. ");
	logFileUtility.parseLogFile();

	EXPECT_EQ(2, cs.enemyEvade);
	EXPECT_EQ(2, cs2.enemyEvade);

	logFile.appendFile("2014.11.25 23:46:10 : Ikarosx-TM evaded Omniknight-SL's Hallowed Strike IV. ");
	logFileUtility.parseLogFile();

	EXPECT_EQ(2, cs.enemyEvade);
	EXPECT_EQ(2, cs2.enemyEvade);
}

TEST_F(CombatModuleTest, resist){

	logFile.appendFile("2014.10.15 16:19:22 : Tursin Outlaw resisted your attack. ");
	logFileUtility.parseLogFile();
	
	CombatStats& cs = combatModule.combatStatsManager.getAllTargetsCombatStats().first;
	CombatStats& cs2 = combatModule.combatStatsManager.getIndividualTargetCombatStats("Tursin Outlaw").first;
	
	EXPECT_EQ(1, cs.enemyResist);
	EXPECT_EQ(1, cs2.enemyResist);

	logFile.appendFile("2014.11.20 15:06:10 : Tursin Outlaw resisted Divine Justice VII. ");
	logFileUtility.parseLogFile();

	EXPECT_EQ(2, cs.enemyResist);
	EXPECT_EQ(2, cs2.enemyResist);

	logFile.appendFile("2014.10.13 14:26:25 : Tursin Outlaw resisted Enyscha-SL's Sonic Gust I. ");
	logFileUtility.parseLogFile();

	EXPECT_EQ(2, cs.enemyResist);
	EXPECT_EQ(2, cs2.enemyResist);

	logFile.appendFile("2014.10.22 11:54:24 : You resisted Ice Trap's Ice Trap. ");
	logFileUtility.parseLogFile();

	EXPECT_EQ(2, cs.enemyResist);
	EXPECT_EQ(2, cs2.enemyResist);
}