#include "gtest/gtest.h"
//#include "../parser/MaxPeriodParser.h"
//#include "../lookups/RuleStringsHardCodedNA.h"
#include "../modules/SoulHealerModule.h"

#include "../parser/LogFileUtility.h"
#include "testLog/TemporaryLogFile.h"

#include "../lookups/ExpChartNA40.h"

class ExpTest: public ::testing::Test{
protected:
	//MaxPeriodParser parser;
	//RuleStringsHardCodedNA rules;
	shared_ptr<ExpChart> expChart;
	
	ExpModule expModule;
	//ApModule apModule;
	//KinahModule kinahModule;
	//SoulHealerModule soulHealerModule;
	
	TemporaryLogFile logFile;
	
	LogFileUtility logFileUtility;
	

	ExpTest(): logFile("testModule/testLog/tests.log", "testModule/testLog/Chat.log"),  expChart(new ExpChartNA40()), expModule(expChart)//,
		//soulHealerModule(expModule, apModule, kinahModule)
	{
	}

	
	virtual void SetUp(){
		logFile.makeFileCopy();

		//logFileUtility.registerModule(playerIdentificationModule);
		logFileUtility.registerModule(expModule);
		//logFileUtility.registerModule(apModule);
		//logFileUtility.registerModule(kinahModule);
		//logFileUtility.registerModule(soulHealerModule);

		string aionDirectory = "testModule/testLog/";
		
		ASSERT_TRUE(logFileUtility.setAionDirectory(aionDirectory));

		/*
		logFileUtility.registerMessageRuleCode(STR_MSG_COMBAT_MY_ABYSS_POINT_GAIN);
		logFileUtility.registerMessageRuleCode(STR_GET_EXP_VITAL_MAKEUP_BONUS);		
		logFileUtility.registerMessageRuleCode(STR_GET_EXP_VITAL_BONUS);
		logFileUtility.registerMessageRuleCode(STR_GET_EXP_MAKEUP_BONUS);		
		logFileUtility.registerMessageRuleCode(STR_GET_EXP);	
		logFileUtility.registerMessageRuleCode(STR_GET_EXP_VITAL_MAKEUP_BONUS);		
		logFileUtility.registerMessageRuleCode(STR_GET_EXP2_VITAL_BONUS);	
		logFileUtility.registerMessageRuleCode(STR_GET_EXP2_MAKEUP_BONUS);
		logFileUtility.registerMessageRuleCode(STR_GET_EXP2);
		logFileUtility.registerMessageRuleCode(STR_GET_EXP_PCBANG_VITAL_MAKEUP_BONUS);
		logFileUtility.registerMessageRuleCode(STR_GET_EXP_PCBANG_VITAL_BONUS);
		logFileUtility.registerMessageRuleCode(STR_GET_EXP2_PCBANG_VITAL_BONUS);
		logFileUtility.registerMessageRuleCode(STR_GET_EXP2_PCBANG_VITAL_MAKEUP_BONUS);
		logFileUtility.registerMessageRuleCode(STR_CANNOT_GET_PVP_EXP_TARGET_LIMIT);
		logFileUtility.registerMessageRuleCode(STR_CANNOT_GET_PVP_EXP_TIMEBASE_LIMIT);
		logFileUtility.registerMessageRuleCode(STR_MSG_ADDEXP_POINT_USE);
		logFileUtility.registerMessageRuleCode(STR_MSG_EXP_EXTRACTION_USE);
		logFileUtility.registerMessageRuleCode(STR_LEVEL_LIMIT_QUEST_NOT_FINISHED1);
		logFileUtility.registerMessageRuleCode(STR_MSG_CANT_NOVICE_SERVER_ALREADY_MAX_LEVEL);
		*/
	}


	virtual void TearDown(){		
		logFile.deleteFileCopy();
	}
};

TEST_F(ExpTest, gainExpNoInit){
	logFile.appendFile("2013.06.27 23:35:36 : Critical Hit!You inflicted 944 damage on Wori by using Righteous Punishment I. ");
	logFile.appendFile("2013.06.27 23:35:36 : You have gained 1,008 Abyss Points. ");
	logFile.appendFile("2013.06.27 23:35:36 : You have gained 8,867 XP from Wori. ");
	logFile.appendFile("2013.06.27 23:35:36 : You have defeated Wori. ");
	logFile.appendFile("2013.06.27 23:35:36 : Invalid target. ");
	logFileUtility.parseLogFile();

	logFile.appendFile("2013.06.27 22:17:33 : Roadhouse recovered 183 MP due to the effect of Strong Instant Recovery. ");
	logFile.appendFile("2013.06.27 22:17:34 : You have gained 20,052,999 XP from Vard (Energy of Repose 10,405). ");
	logFile.appendFile("2013.06.27 22:17:34 : Quest complete: Kata-where? ");
	logFile.appendFile("2013.06.27 22:17:34 : Quest updated: For the Dead ");
	logFileUtility.parseLogFile();

	EXPECT_EQ(8867 + 20052999, expModule.expGainMeter.getNetGained());
	EXPECT_EQ(20052999, expModule.expGainMeter.getLastChange());

	EXPECT_EQ(-1, expModule.levelUpChecker.getCurrentValue());
	EXPECT_EQ(-1, expModule.levelUpChecker.getCurrentLevelMaxValue());
	EXPECT_EQ(-1, expModule.levelUpChecker.getCumulativeCurrentValue());
	EXPECT_EQ(10405, expModule.expGainMeter.getReposeUsed());
	EXPECT_FLOAT_EQ(0, expModule.levelUpChecker.getPercent());
	EXPECT_FLOAT_EQ(0, expModule.levelUpChecker.getCumulativePercent());
	EXPECT_FLOAT_EQ(0, expModule.levelUpChecker.getNumLevelsGained());
	EXPECT_FLOAT_EQ(0, expModule.levelUpChecker.getLastChangePercent());
}

TEST_F(ExpTest, gainExpWithInit){
	expModule.levelUpChecker.initialize(20, 12000);
	
	EXPECT_EQ(0, expModule.expGainMeter.getNetGained());
	EXPECT_EQ(0, expModule.levelUpChecker.getNumLevelsGained());

	logFile.appendFile("2013.06.26 22:05:44 : You have gained 15,411 XP from Studio Butler (Energy of Repose 3,626, Energy of Salvation 2,719).");
	logFileUtility.parseLogFile();

	EXPECT_EQ(20, expModule.levelUpChecker.getCurrentLevel());
	EXPECT_EQ(15411, expModule.expGainMeter.getNetGained());
	EXPECT_EQ(3626, expModule.expGainMeter.getReposeUsed());
	EXPECT_EQ(2719, expModule.expGainMeter.getSalvationUsed());
	EXPECT_EQ(1, expModule.expGainMeter.getNumPacketsForLastChange());
	EXPECT_NEAR(2.457417, expModule.levelUpChecker.getLastChangePercent(), 0.0001);
}

TEST_F(ExpTest, initAfterGainExp){
			
	logFile.appendFile("2013.06.25 14:46:50 : You have gained 170,177 XP from Terath Warmonger (Energy of Repose 48,622). ");
	logFile.appendFile("2013.06.25 14:46:50 : Quest updated: [Group] Alluna's Crew Cuts ");
	logFile.appendFile("2013.06.25 14:46:50 : Terath Warmonger is no longer shocked. ");
	logFile.appendFile("2013.06.25 14:46:50 : Terath Warmonger restored its attack speed. ");
	logFile.appendFile("2013.06.25 14:46:50 : You have gained 20 points from Terath Warmonger. ");

	logFileUtility.parseLogFile();

	logFile.appendFile("2013.06.25 14:47:06 : You have gained 170,177 XP from Terath Magician (Energy of Repose 48,622). ");
	logFile.appendFile("2013.06.25 14:47:06 : Terath Magician is no longer immobilized. ");
	logFile.appendFile("2013.06.25 14:47:06 : Terath Magician is no longer afraid. ");
	logFile.appendFile("2013.06.25 14:47:06 : Terath Magician is no longer staggering. ");
	logFile.appendFile("2013.06.25 14:47:06 : Terath Magician restored its movement speed. ");
	logFile.appendFile("2013.06.25 14:47:06 : Quest updated: [Group] Alluna's Crew Cuts ");

	logFileUtility.parseLogFile();

	expModule.levelUpChecker.initialize(60, 20000000);

	EXPECT_EQ(60, expModule.levelUpChecker.getCurrentLevel());
	EXPECT_EQ(20000000, expModule.levelUpChecker.getCurrentValue());
	EXPECT_EQ(170177 * 2, expModule.expGainMeter.getNetGained());
	EXPECT_EQ(48622 * 2, expModule.expGainMeter.getReposeUsed());
	EXPECT_EQ(0, expModule.expGainMeter.getSalvationUsed());
	EXPECT_EQ(1, expModule.expGainMeter.getNumPacketsForLastChange());

}

TEST_F(ExpTest, gainExpSalvationOnly){
	
	logFile.appendFile("2013.06.26 22:05:44 : You have gained 13.000.000 XP from s u p e r c h a r g e d (Energy of Salvation 3.000.000).");
	logFileUtility.parseLogFile();

	EXPECT_EQ(-1, expModule.levelUpChecker.getCurrentLevel());
	EXPECT_EQ(13000000, expModule.expGainMeter.getNetGained());
	EXPECT_EQ(0, expModule.expGainMeter.getReposeUsed());
	EXPECT_EQ(3000000, expModule.expGainMeter.getSalvationUsed());
	EXPECT_EQ(1, expModule.expGainMeter.getNumPacketsForLastChange());

}

TEST_F(ExpTest, gainExpFromZero){
	expModule.levelUpChecker.initialize(13, 0);
	
	logFile.appendFile("2013.07.04 18:15:04 : You spent 551 Kinah. ");
	logFile.appendFile("2013.07.04 18:15:04 : You have gained 4,142 XP. ");
	logFile.appendFile("2013.07.04 18:15:04 : You received Soul Healing. ");
	
	logFileUtility.parseLogFile();

	EXPECT_NEAR(3.19, expModule.levelUpChecker.getPercent(), 0.01);
	
	EXPECT_EQ(4142, expModule.expGainMeter.getNetGained());
	EXPECT_EQ(4142, expModule.expGainMeter.getLastChange());
	

}


TEST_F(ExpTest, LevelUp){
	expModule.levelUpChecker.initialize(5, 7000);
	
	logFile.appendFile("2013.06.27 22:17:34 : You have gained 2,000 XP from Vard.");
	logFileUtility.parseLogFile();

	EXPECT_EQ(7000 + 2000 - 8601, expModule.levelUpChecker.getCurrentValue());
	EXPECT_EQ(6, expModule.levelUpChecker.getCurrentLevel());
	EXPECT_EQ(2000, expModule.expGainMeter.getNetGained());
	EXPECT_EQ(2000, expModule.expGainMeter.getTotalGained());
	EXPECT_NEAR(21.608936, expModule.levelUpChecker.getLastChangePercent(), 0.0001);
}


TEST_F(ExpTest, LevelUp2){
	//1522142
	expModule.levelUpChecker.initialize(24, 1430000);
	//expModule.levelUpChecker.initializePercent(24, 93.9);

	logFile.appendFile("2015.10.17 23:41:44 : Quest updated: Scourge of the Elim ");
	logFile.appendFile("2015.10.17 23:41:44 : You have gained 46,628 XP from Swamp Slime. (Energy of Repose 13,322) ");
	logFileUtility.parseLogFile();
	logFile.appendFile("2015.10.17 23:41:52 : You inflicted 149 damage on Marshland Mudthorn. ");
	logFileUtility.parseLogFile();
	logFile.appendFile("2015.10.17 23:41:53 : You inflicted 329 damage on Marshland Mudthorn by using Deadshot. ");
	logFileUtility.parseLogFile();
	logFile.appendFile("2015.10.17 23:41:54 : You inflicted 344 damage on Marshland Mudthorn by using Swift Shot. ");
	logFileUtility.parseLogFile();
	logFile.appendFile("2015.10.17 23:41:55 : You inflicted 107 damage on Marshland Mudthorn. ");
	logFileUtility.parseLogFile();
	logFile.appendFile("2015.10.17 23:41:56 : Critical Hit!You inflicted 747 damage on Marshland Mudthorn by using Arrow Strike. ");
	logFile.appendFile("2015.10.17 23:41:56 : You interrupted the target's skill. ");
	logFileUtility.parseLogFile();
	logFile.appendFile("2015.10.17 23:41:57 : You received 97 damage from Marshland Mudthorn. ");
	logFile.appendFile("2015.10.17 23:41:57 : You inflicted 1,218 damage on Marshland Mudthorn by using Stunning Shot. ");
	logFile.appendFile("2015.10.17 23:41:57 : You stunned Marshland Mudthorn by using Stunning Shot. ");
	logFileUtility.parseLogFile();
	logFile.appendFile("2015.10.17 23:41:58 : Invalid target. ");
	logFile.appendFile("2015.10.17 23:41:58 : Quest updated: Plague of the Elim ");
	logFile.appendFile("2015.10.17 23:41:58 : You have gained 46,628 XP from Marshland Mudthorn. (Energy of Repose 13,322) ");
	logFile.appendFile("2015.10.17 23:41:58 : You learned Boost Bow Range I (Level 1). ");
	logFile.appendFile("2015.10.17 23:41:58 : You learned Advanced Sword Training II (Level 2). ");
	logFile.appendFile("2015.10.17 23:41:58 : You learned Advanced Dagger Training II (Level 2). ");
	logFile.appendFile("2015.10.17 23:41:58 : You learned Advanced Archery Training II (Level 2). ");
	logFile.appendFile("2015.10.17 23:41:58 : You learned Herb Treatment (Level 4). ");
	logFile.appendFile("2015.10.17 23:41:58 : You learned MP Recovery (Level 4). ");
	logFile.appendFile("2015.10.17 23:41:58 : You learned Winged Avenger I (Level 1). ");
	logFile.appendFile("2015.10.17 23:41:58 : You learned Stunning Shot (Level 4). ");
	logFile.appendFile("2015.10.17 23:41:58 : You learned Strong Shots (Level 1). ");
	logFile.appendFile("2015.10.17 23:41:58 : You learned Entangling Shot (Level 4). ");
	logFile.appendFile("2015.10.17 23:41:58 : You learned Swift Shot (Level 4). ");
	logFile.appendFile("2015.10.17 23:41:58 : You learned Deadshot (Level 4). ");
	logFile.appendFile("2015.10.17 23:41:58 : You learned Silence Arrow (Level 1). ");
	logFile.appendFile("2015.10.17 23:41:58 : You learned Seizure Arrow (Level 3). ");
	logFile.appendFile("2015.10.17 23:41:58 : You learned Rupture Arrow (Level 1). ");
	logFile.appendFile("2015.10.17 23:41:58 : You learned Counterattack (Level 5). ");
	logFile.appendFile("2015.10.17 23:41:58 : Quest acquired: Testing Your Mettle ");
	logFileUtility.parseLogFile();
	logFile.appendFile("2015.10.17 23:42:17 : Attack was changed using Strong Shots. ");
	logFileUtility.parseLogFile();
	logFile.appendFile("2015.10.17 23:42:20 : [3.LFG] [charname:ChantyRomanu-SL;1.0000 0.6941 0.6941]: [cmd:ChantyRomanu-SL;7JgSETlYzZqfh8l9/ZValxrA6fiu/iZs15RQv5DYHCo=]FT ");
	logFileUtility.parseLogFile();
	logFile.appendFile("2015.10.17 23:42:29 : Your Attack has been boosted by using Devotion. ");
	logFileUtility.parseLogFile();
	logFile.appendFile("2015.10.17 23:42:31 : You boosted your skill by using Focused Shots. ");
	logFile.appendFile("2015.10.17 23:42:31 : Your Physical Def has been weakened by using Focused Shots. ");
	logFileUtility.parseLogFile();
	logFile.appendFile("2015.10.17 23:42:32 : You inflicted 192 damage on Marshland Mudthorn. ");
	logFile.appendFile("2015.10.17 23:42:32 : You inflicted 555 damage on Marshland Mudthorn by using Deadshot. ");
	logFileUtility.parseLogFile();
	logFile.appendFile("2015.10.17 23:42:34 : Critical Hit!You inflicted 1,076 damage on Marshland Mudthorn by using Swift Shot. ");
	logFileUtility.parseLogFile();
	logFile.appendFile("2015.10.17 23:42:35 : [3.LFG] [charname:MayuyuQCS-KR;1.0000 0.6941 0.6941]: [cmd:MayuyuQCS-KR;GfEGOu13PiDk9RBqahEUI9429U8cF6/cLUS6wB/pzJg=]NTC ");
	logFile.appendFile("2015.10.17 23:42:35 : You inflicted 129 damage on Marshland Mudthorn. ");
	logFile.appendFile("2015.10.17 23:42:35 : You interrupted the target's skill. ");
	logFileUtility.parseLogFile();
	logFile.appendFile("2015.10.17 23:42:36 : You inflicted 547 damage on Marshland Mudthorn by using Arrow Strike. ");
	logFile.appendFile("2015.10.17 23:42:36 : You interrupted the target's skill. ");
	logFile.appendFile("2015.10.17 23:42:36 : You received 150 damage from Marshland Mudthorn. ");
	logFileUtility.parseLogFile();
	logFile.appendFile("2015.10.17 23:42:37 : You inflicted 848 damage on Marshland Mudthorn by using Stunning Shot. ");
	logFile.appendFile("2015.10.17 23:42:37 : You stunned Marshland Mudthorn by using Stunning Shot. ");
	logFileUtility.parseLogFile();
	logFile.appendFile("2015.10.17 23:42:38 : Quest updated: Plague of the Elim ");
	logFile.appendFile("2015.10.17 23:42:38 : You have gained 46,628 XP from Marshland Mudthorn. (Energy of Repose 13,322) ");
	logFileUtility.parseLogFile();

	EXPECT_EQ(1430000 + 46628 * 3 - 1522142, expModule.levelUpChecker.getCurrentValue());
	EXPECT_EQ(25, expModule.levelUpChecker.getCurrentLevel());
	EXPECT_EQ(46628 * 3, expModule.expGainMeter.getNetGained());
	EXPECT_EQ(46628 * 3, expModule.expGainMeter.getTotalGained());
}

TEST_F(ExpTest, PreAscensionExpWaste){
	expModule.levelUpChecker.initialize(9, 10000);

	
	logFile.appendFile("2016.01.01 10:30:32 : Quest updated: Ascension ");
	logFile.appendFile("2016.01.01 10:30:37 : [3.LFG] [charname:Zise-IS;1.0000 0.6941 0.6941]: [cmd:Zise-IS;l8bmyOX1o/qDyso7kL/ob4wjaM4uFPO/1LAKcq5ziRk=]BT Need healer ??? ");
	logFileUtility.parseLogFile();
	logFile.appendFile("2016.01.01 10:30:40 : You learned Advanced Sword Training I (Level 1). ");
	logFile.appendFile("2016.01.01 10:30:40 : Quest updated: Ascension ");
	logFile.appendFile("2016.01.01 10:30:40 : You learned Advanced Mace Training I (Level 1). ");
	logFile.appendFile("2016.01.01 10:30:40 : You learned Advanced Leather Armor Proficiency I (Level 1). ");
	logFile.appendFile("2016.01.01 10:30:40 : You learned Advanced Chain Armor Proficiency I (Level 1). ");
	logFile.appendFile("2016.01.01 10:30:40 : You learned Advanced Shield Training I (Level 1). ");
	logFile.appendFile("2016.01.01 10:30:40 : You learned Advanced Greatsword Training I (Level 1). ");
	logFile.appendFile("2016.01.01 10:30:40 : You learned Advanced Plate Armor Proficiency I (Level 1). ");
	logFile.appendFile("2016.01.01 10:30:40 : You have learned the Essencetapping skill. ");
	logFile.appendFile("2016.01.01 10:30:40 : You have learned the Morph Substances skill. ");
	logFile.appendFile("2016.01.01 10:30:40 : You have learned [recipe_ex:155000001;mooMOOMOoMoomooo-BR]. ");
	logFile.appendFile("2016.01.01 10:30:40 : You have learned [recipe_ex:155000002;mooMOOMOoMoomooo-BR]. ");
	logFile.appendFile("2016.01.01 10:30:40 : You have learned [recipe_ex:155000005;mooMOOMOoMoomooo-BR]. ");
	logFile.appendFile("2016.01.01 10:30:40 : You have learned the Aethertapping skill. ");
	logFileUtility.parseLogFile();
	logFile.appendFile("2016.01.01 10:30:43 : The number of your private channel may have been changed with the deletion of the Gladiator Channel. ");
	logFileUtility.parseLogFile();
	logFile.appendFile("2016.01.01 10:30:49 : [3.LFG] [charname:Kannuki-BR;1.0000 0.6941 0.6941]: [cmd:Kannuki-BR;SNWJbk/VWv2s/LcjARC8z65ytnbXyMZJe2mVD2V8G7M=]ADMA Duo XP Rush ");
	logFileUtility.parseLogFile();
	logFile.appendFile("2016.01.01 10:31:06 : [3.LFG] [charname:iissooo-SL;1.0000 0.6941 0.6941]: [cmd:iissooo-SL;2qo2Y24ndjhr02v1DbaN+hy9VovdfUkvDUcm/zZLggE=]BT exp someone ");
	logFileUtility.parseLogFile();
	logFile.appendFile("2016.01.01 10:31:42 : You have gained 73,200 XP from Pernos. ");
	logFile.appendFile("2016.01.01 10:31:42 : You can advance to level 10 only after you have completed the class change quest. ");
	logFile.appendFile("2016.01.01 10:31:42 : Quest complete: Ascension ");
	logFile.appendFile("2016.01.01 10:31:42 : Quest acquired: A Ceremony in Sanctum ");
	logFileUtility.parseLogFile();
	
	/*
	logFile.appendFile("2013.06.28 09:42:49 : Quest updated: Ascension ");
	logFile.appendFile("2013.06.28 09:42:49 : You have learned the Essencetapping skill. ");
	logFile.appendFile("2013.06.28 09:42:49 : You have learned the Morph Substances skill. ");
	logFile.appendFile("2013.06.28 09:42:49 : You have learned [recipe_ex:155005001;DeleteAfterAscen-IS]. ");
	logFile.appendFile("2013.06.28 09:42:49 : You have learned [recipe_ex:155005002;DeleteAfterAscen-IS]. ");
	logFile.appendFile("2013.06.28 09:42:49 : You have learned [recipe_ex:155005005;DeleteAfterAscen-IS]. ");
	logFile.appendFile("2013.06.28 09:42:49 : You have learned the Aethertapping skill. ");
	logFile.appendFile("2013.06.28 09:42:50 : [3.LFG] [charname:Onimushaz-SL;1.0000 0.6941 0.6941]: [cmd:rGSlNwGJGRxRQv03cJhj8zmbH1pS5sI2+Ojm4GyCo/tFUYOZnylZ5HCClET+4/tCS7qtaOGT6oZDfpuNO+D18g==]Adma Rush Need Cleric at Lannok  ");
	logFile.appendFile("2013.06.28 09:42:57 : [3.LFG] [charname:Draizon-KR;1.0000 0.6941 0.6941]: [cmd:ZuRJ77suA3HGXknXXvlwhpPM8QnGQsOkmk/KeMfcfBdFUYOZnylZ5HCClET+4/tC4UL+Ir0PulB5jOt1gqsgzQ==]NTC need all! ");
	logFile.appendFile("2013.06.28 09:43:01 : [3.LFG] [charname:Demolize-TM;1.0000 0.6941 0.6941]: [cmd:P4LwuGgTZY+ycKKEACMJvuAyWLtXF0rdZGbvQ8Z9+DdFUYOZnylZ5HCClET+4/tCg5pior9yCPYe0vyEXekmgw==]?BT?NEED ALL 59+ ?? Hard Mode ");
	logFile.appendFile("2013.06.28 09:43:04 : You have gained 73,200 XP from Munin. ");
	logFile.appendFile("2013.06.28 09:43:04 : You can advance to level 10 only after you have completed the class change quest. ");

	logFileUtility.parseLogFile();
	*/
	EXPECT_EQ(9, expModule.levelUpChecker.getCurrentLevel());
	EXPECT_EQ(43087, expModule.levelUpChecker.getCurrentValue());
	EXPECT_EQ(33087, expModule.expGainMeter.getNetGained());
	EXPECT_EQ(73200 - 33087, expModule.expGainMeter.getTotalLost());

	logFile.appendFile("2013.06.27 22:17:34 : You have gained 2,000 XP from Vard.");
	logFile.appendFile("2013.06.27 09:43:04 : You can advance to level 10 only after you have completed the class change quest. ");

	logFileUtility.parseLogFile();
	
	EXPECT_EQ(9, expModule.levelUpChecker.getCurrentLevel());
	EXPECT_EQ(43087, expModule.levelUpChecker.getCurrentValue());
	EXPECT_EQ(33087, expModule.expGainMeter.getNetGained());
	EXPECT_EQ(73200 - 33087 + 2000, expModule.expGainMeter.getTotalLost());

	logFile.appendFile("2013.06.27 22:17:34 : You have gained 2,000 XP from Vard.");

	logFileUtility.parseLogFile();

	EXPECT_EQ(10, expModule.levelUpChecker.getCurrentLevel());
	EXPECT_EQ(2000, expModule.levelUpChecker.getCurrentValue());
	EXPECT_EQ(35087, expModule.expGainMeter.getNetGained());
	EXPECT_EQ(73200 - 33087 + 2000, expModule.expGainMeter.getTotalLost());

}

TEST_F(ExpTest, LevelCapExpWaste){
	expModule.levelUpChecker.initialize(65, 584561235);

	logFile.appendFile("2013.06.27 22:17:34 : You have gained 20,052,999 XP from Vard. (Energy of Repose 10,405) ");
	
	logFileUtility.parseLogFile();

	EXPECT_EQ(65, expModule.levelUpChecker.getCurrentLevel());
	EXPECT_EQ(584561235, expModule.levelUpChecker.getCurrentValue());
	EXPECT_EQ(0, expModule.expGainMeter.getNetGained());
	EXPECT_EQ(20052999, expModule.expGainMeter.getTotalGained());
	EXPECT_EQ(20052999, expModule.expGainMeter.getTotalLost());
	//EXPECT_EQ(10405, expModule.expGainMeter.getReposeUsed());

}

TEST_F(ExpTest, PercentGained1){
	expModule.levelUpChecker.initialize(1, 200);

	logFile.appendFile("2013.06.27 22:17:34 : You have gained 50 XP from ABCDE. ");
	logFileUtility.parseLogFile();
	logFile.appendFile("2013.06.27 22:17:34 : You have gained 50 XP from ABCDE. ");
	logFileUtility.parseLogFile();
	logFile.appendFile("2013.06.27 22:17:34 : You have gained 50 XP from ABCDE. ");
	logFileUtility.parseLogFile();
	logFile.appendFile("2013.06.27 22:17:34 : You have gained 50 XP from ABCDE. ");
	logFileUtility.parseLogFile();
	logFile.appendFile("2013.06.27 22:17:34 : You have gained 200 XP from ABCDE. ");
	logFileUtility.parseLogFile();
	logFile.appendFile("2013.06.27 22:17:34 : You have gained 200 XP from ABCDE. ");
	logFileUtility.parseLogFile();
	logFile.appendFile("2013.06.27 22:17:34 : You have gained 200 XP from ABCDE. ");
	logFileUtility.parseLogFile();
	logFile.appendFile("2013.06.27 22:17:34 : You have gained 123 XP from ABCDE. ");
	logFileUtility.parseLogFile();		

	EXPECT_EQ(2, expModule.levelUpChecker.getCurrentLevel());
	EXPECT_EQ(723, expModule.levelUpChecker.getCurrentValue());
	EXPECT_EQ(923, expModule.expGainMeter.getNetGained());
	EXPECT_EQ(923, expModule.expGainMeter.getTotalGained());
	EXPECT_EQ(0, expModule.expGainMeter.getTotalLost());
	EXPECT_EQ(0, expModule.expGainMeter.getReposeUsed());
	EXPECT_FLOAT_EQ(1.199903, expModule.levelUpChecker.getNumLevelsGained());

}

TEST_F(ExpTest, PercentGained2){
	expModule.levelUpChecker.initialize(1, 200);

	logFile.appendFile("2013.06.27 22:17:34 : You have gained 50 XP from ABCDE. ");
	logFileUtility.parseLogFile();	

	EXPECT_EQ(1, expModule.levelUpChecker.getCurrentLevel());
	EXPECT_EQ(250, expModule.levelUpChecker.getCurrentValue());
	EXPECT_EQ(50, expModule.expGainMeter.getNetGained());
	EXPECT_EQ(50, expModule.expGainMeter.getTotalGained());
	EXPECT_EQ(0, expModule.expGainMeter.getTotalLost());
	EXPECT_EQ(0, expModule.expGainMeter.getReposeUsed());
	EXPECT_FLOAT_EQ(0.125, expModule.levelUpChecker.getNumLevelsGained());

}

TEST_F(ExpTest, InitPercentExp1){
	//55: 104,225,345
	expModule.levelUpChecker.initializePercent(55, 81.77);

	EXPECT_EQ(85225065, expModule.levelUpChecker.getCurrentValue());
	EXPECT_NEAR(81.77, expModule.levelUpChecker.getPercent(), 0.01);

	logFile.appendFile("2013.06.27 22:17:34 : You have gained 1,000,000 XP from testtest. ");
	logFileUtility.parseLogFile();	


	EXPECT_EQ(55, expModule.levelUpChecker.getCurrentLevel());
	EXPECT_EQ(85225065 + 1000000, expModule.levelUpChecker.getCurrentValue());
	EXPECT_NEAR(82.72, expModule.levelUpChecker.getPercent(), 0.01);
	
	EXPECT_EQ(1000000, expModule.expGainMeter.getNetGained());
	EXPECT_EQ(1000000, expModule.expGainMeter.getTotalGained());
	EXPECT_EQ(0, expModule.expGainMeter.getTotalLost());
	EXPECT_EQ(0, expModule.expGainMeter.getReposeUsed());
	EXPECT_NEAR(0.0095945953, expModule.levelUpChecker.getNumLevelsGained(), 0.0001);
	

}

TEST_F(ExpTest, InitPercentExpZero){
	//55: 104,225,345
	expModule.levelUpChecker.initializePercent(55, 0);

	logFile.appendFile("2013.06.27 22:17:34 : You have gained 1,000,000 XP from testtest. ");
	logFileUtility.parseLogFile();	


	EXPECT_EQ(55, expModule.levelUpChecker.getCurrentLevel());
	EXPECT_EQ(1000000, expModule.levelUpChecker.getCurrentValue());
	EXPECT_NEAR(0.95945953, expModule.levelUpChecker.getPercent(), 0.01);
	EXPECT_EQ(1000000, expModule.expGainMeter.getNetGained());
	EXPECT_EQ(1000000, expModule.expGainMeter.getTotalGained());
	EXPECT_EQ(0, expModule.expGainMeter.getTotalLost());
	EXPECT_EQ(0, expModule.expGainMeter.getReposeUsed());
	EXPECT_NEAR(0.0095945953, expModule.levelUpChecker.getNumLevelsGained(), 0.0001);

}

TEST_F(ExpTest, InitPercentNewCharacter){
	//1: 400
	expModule.levelUpChecker.initializePercent(1, 0.25);

	EXPECT_EQ(1, expModule.levelUpChecker.getCurrentLevel());
	EXPECT_EQ(1, expModule.levelUpChecker.getCurrentValue());
	EXPECT_NEAR(0.25, expModule.levelUpChecker.getPercent(), 0.01);
	EXPECT_EQ(0, expModule.expGainMeter.getNetGained());
	EXPECT_EQ(0, expModule.expGainMeter.getTotalGained());
	EXPECT_EQ(0, expModule.expGainMeter.getTotalLost());
	EXPECT_EQ(0, expModule.expGainMeter.getReposeUsed());
	EXPECT_NEAR(0, expModule.levelUpChecker.getNumLevelsGained(), 0.0001);

}

/*
TEST_F(ExpTest, PercentlevelUp){
	//55: 104,225,345
	expModule.levelUpChecker.initializePercent(55, 99.1);
	//99.1% est: 103,287,317
	
	logFile.appendFile("2013.06.27 22:17:34 : You have gained 902,754 XP from testtest. ");
	logFile.appendFile("2013.06.27 22:17:34 : You learned Yoki Geri Jodan (Level 9). ");
	logFileUtility.parseLogFile();	


	EXPECT_EQ(56, expModule.levelUpChecker.getCurrentLevel());
	EXPECT_EQ(0, expModule.levelUpChecker.getCurrentValue());
	EXPECT_EQ(902754, expModule.expGainMeter.getNetGained());
	EXPECT_EQ(902754, expModule.expGainMeter.getTotalGained());
	EXPECT_EQ(0, expModule.expGainMeter.getTotalLost());
	EXPECT_EQ(0, expModule.expGainMeter.getReposeUsed());
	EXPECT_NEAR(0.09, expModule.levelUpChecker.getPercent(), 0.01);
	EXPECT_NEAR(0.0086615924, expModule.levelUpChecker.getNumLevelsGained(), 0.0001);

}
*/

TEST_F(ExpTest, PercentlevelUp2){
	//55: 104,225,345
	//56: 124,225,345

	//55 at 99.1%: 103,287,317
	expModule.levelUpChecker.initializePercent(55, 99.1);
	
	logFile.appendFile("2013.06.27 22:17:34 : You have gained 2,000,000 XP from testtest. ");
	logFile.appendFile("2013.06.27 22:17:34 : You learned Yoki Geri Jodan (Level 9). ");
	logFileUtility.parseLogFile();	


	EXPECT_EQ(56, expModule.levelUpChecker.getCurrentLevel());
	EXPECT_EQ(103287317 + 2000000 - 104225345, expModule.levelUpChecker.getCurrentValue());
	EXPECT_EQ(2000000, expModule.expGainMeter.getNetGained());
	EXPECT_EQ(2000000, expModule.expGainMeter.getTotalGained());
	EXPECT_EQ(0, expModule.expGainMeter.getTotalLost());
	EXPECT_EQ(0, expModule.expGainMeter.getReposeUsed());
	EXPECT_NEAR(0.009 + 0.008549, expModule.levelUpChecker.getNumLevelsGained(), 0.0001);
	EXPECT_EQ(124225345, expModule.levelUpChecker.getCurrentLevelMaxValue());

	logFile.appendFile("2013.06.27 22:17:34 : You have gained 100,000 XP from testtest. ");
	logFileUtility.parseLogFile();	

	logFile.appendFile("2013.06.27 22:17:34 : You have gained 100,000 XP from testtest. ");
	logFileUtility.parseLogFile();	

	EXPECT_EQ(56, expModule.levelUpChecker.getCurrentLevel());
	EXPECT_EQ(1261972, expModule.levelUpChecker.getCurrentValue());
	EXPECT_EQ(2200000, expModule.expGainMeter.getNetGained());
	EXPECT_EQ(2200000, expModule.expGainMeter.getTotalGained());
	EXPECT_EQ(0, expModule.expGainMeter.getTotalLost());
	EXPECT_EQ(0, expModule.expGainMeter.getReposeUsed());
	EXPECT_NEAR(0.009 + 0.008549 + 0.001601, expModule.levelUpChecker.getNumLevelsGained(), 0.0001);

}


TEST_F(ExpTest, setCurrentPercent){
	//13, 61851 / 129506
	expModule.levelUpChecker.initializePercent(13, 47.76);
	

	logFile.appendFile("2013.06.27 23:03:19 : You are no longer bleeding. ");
	logFile.appendFile("2013.06.27 23:03:19 : You have died. ");
	
	logFileUtility.parseLogFile();

	EXPECT_FALSE(expModule.levelUpChecker.setCurrentPercent(47.77));

	EXPECT_EQ(0, expModule.expGainMeter.getTotalLost());

	EXPECT_NEAR(47.76, expModule.levelUpChecker.getPercent(), 0.01);


	EXPECT_TRUE(expModule.levelUpChecker.setCurrentPercent(47.76));

	EXPECT_EQ(0, expModule.expGainMeter.getTotalLost());

	EXPECT_NEAR(47.76, expModule.levelUpChecker.getPercent(), 0.01);

	//exp lost 4342

	
	logFile.appendFile("2013.06.27 23:03:19 : You are no longer bleeding. ");
	logFile.appendFile("2013.06.27 23:03:19 : You have died. ");
	
	logFileUtility.parseLogFile();

	EXPECT_TRUE(expModule.levelUpChecker.setCurrentPercent(46.76));

	EXPECT_NEAR(46.76, expModule.levelUpChecker.getPercent(), 0.01);

	

	
/*
	EXPECT_TRUE(soulHealerModule.soulHealer.isExpUpdateNeeded());
	EXPECT_FALSE(soulHealerModule.soulHealer.isApUpdateNeeded());




	EXPECT_FALSE(soulHealerModule.soulHealer.isExpUpdateNeeded());
	EXPECT_TRUE(soulHealerModule.soulHealer.isApUpdateNeeded());
	*/
}